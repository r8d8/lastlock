/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 */
// Copyright (c) 2018 Qualcomm Technologies, Inc.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without modification, are permitted (subject to the limitations in the disclaimer below) 
// provided that the following conditions are met:
// Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// Neither the name of Qualcomm Technologies, Inc. nor the names of its contributors may be used to endorse or promote products derived 
// from this software without specific prior written permission.
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE. 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifdef CONFIG_DAEMON_MODE
#include <stdlib.h>
#include "common_cxt.h"
#include "qsOSAL.h"
#include "qsConfig.h"
#include "qsPack.h"
#include "idlist.h"
#include "filelist.h"
#include "qurt_error.h"
#include "qurt_thread.h"

/* Processing entry point for received data.
 * Data is put in different queues depending on the module type.
 * A separate worker thread for each module dequeues and processes
 * the request and sends response. */
SerStatus_t QsEnqQapi(void *Buf)
{
    uint8_t module = 0;
    moduleCxt_t *cxt = NULL;
    qsQapiReq_t *command = NULL;

    /* Common module context */
    moduleCommonCxt_t *moduleCxt = QH_MODULE_CMN_CXT(qsCommonCxt);
    if(!moduleCxt || !Buf)
    {
        return ssFailure;
    }

    /* Find the context for the required module */
    command = (qsQapiReq_t *)(QSPACKET_HEADER(Buf));
    module = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(&command->Header.ModuleID);

    qurt_mutex_lock(&moduleCxt->mutex);
    cxt = QH_MODULE_INFO_CXT(qsCommonCxt, module);
    if(!cxt)
    {
        qurt_mutex_unlock(&moduleCxt->mutex);
        return ssFailure;
    }
    qurt_mutex_unlock(&moduleCxt->mutex);

    /* Enqueue the request at the end of module specific queue */
    if(ssSuccess == QsEnq(&cxt->queue, (void *)Buf))
    {
        /* Signal the worker thread and release the mutex */
        qurt_signal_set(&cxt->event, cxt->mask);
        return ssSuccess;
    }
    return ssFailure;
}

/* Return first packet from module specific queue */
SerStatus_t QsDeqQapi(uint8_t ModuleID, void **ReqBufPtr)
{
    moduleCommonCxt_t *moduleCmnCxt = QH_MODULE_CMN_CXT(qsCommonCxt);
    moduleCxt_t *cxt = QH_MODULE_INFO_CXT(qsCommonCxt, ModuleID);

    if(!moduleCmnCxt || !cxt || !ReqBufPtr)
    {
        return ssFailure;
    }

    qurt_mutex_lock(&qsCommonCxt->moduleCxt->mutex);
    cxt = QH_MODULE_INFO_CXT(qsCommonCxt, ModuleID);
    if(!cxt)
    {
        qurt_mutex_unlock(&qsCommonCxt->moduleCxt->mutex);
        return ssFailure;
    }
    qurt_mutex_unlock(&qsCommonCxt->moduleCxt->mutex);

    /* Dequeue a packet from module specific queue */
    if(ssSuccess != QsDeq(&cxt->queue, ReqBufPtr))
    {
        return ssFailure;
    }
    return ssSuccess;
}

static void QapiRcvCompleteCb(uint8_t SqId, uint16_t ReqBufLen, char *ReqBuf, void *ServiceCxt, void *ServiceData)
{
    SerStatus_t        Result = ssFailure;
    uint8_t            UID[8] = {0};
    uint8_t            ModuleID = 0;
    uint16_t           FileID = 0;
    uint16_t           CmdID = 0;
    uint32_t           CommandLength = 0;
    PackedBuffer_t     OutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint8_t           *CommandData = NULL;
    FileEntry_t       *CurrFileEntry = NULL;
    FunctionHandler_t *FunctionHandler = NULL;
    int                i = 0;
    uint16_t          Len = 0;
    char              *RespBuf = NULL;

    /* Check the input paramters. */
    if(ReqBuf)
    {
        /* Get the command parameters. */
        qsQapiReq_t *Command = (qsQapiReq_t *)ReqBuf;
        CommandData   = QSCOMMAND_DATA(ReqBuf);
        ModuleID      = READ_UNALIGNED_LITTLE_ENDIAN_UINT8( &Command->Header.ModuleID);
        for(i = 0; i < 8; i++)
        {
            UID[i] = Command->Header.UID[i];
        }
        FileID        = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&Command->Header.FileID);
        CmdID         = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&Command->Header.FunctionID);
        CommandLength = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&Command->Header.DataLength);

        /* Make sure the ID does not exceed the list size. */
        if(FILE_LIST_SIZE > FileID)
        {
            /* Hack to get BSC functions. */
            CurrFileEntry = &(FileList[FileID]);

            if(CmdID < CurrFileEntry->FunctionCount)
            {
                /* Get the function handler. */
                FunctionHandler = &CurrFileEntry->FunctionList[CmdID];

                /* Call the QAPI function.
                 * The response packet (if required) gets created here irrespective of whether 
                 * the API succeeds or fails. */
                Result = (*FunctionHandler)(CommandData, (uint16_t)CommandLength, &OutputBuffer, UID);
            }
        }

        /* Call the MML API to release received buffer for both success and failure. */
        mmlReleaseBuf(SqId, ReqBuf);

        /* This case is true only when input command has invalid parameters hence QAPI function is not found.
         * Create a packet with datalength set to 0 which will inform the host that there was an error finding the function.*/
        if((Result != ssSuccess) && !OutputBuffer.Packet)
        {
            if(FALSE == AllocatePackedBuffer(UID, QS_RETURN_E, ModuleID, FileID, CmdID, &OutputBuffer, 0))
                return;
        }

        if(OutputBuffer.Packet)
        {
            /* Send QAPI response */
            RespBuf = (char *)OutputBuffer.Packet;
            Len = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&((qsQapiPacketHeader_t *)QSPACKET_HEADER(RespBuf))->TotalLength);

            if(MML_SUCCESS_E != mmlServiceQueueSend(QAPI_SQ_ID, QS_TOTAL_LEN(Len), RespBuf, ServiceData))
            {
                /* Free buffer in case of error */
				mmlReleaseBuf(QAPI_SQ_ID, &RespBuf[QS_IOTD_HEADER_LEN]);
            }

            /* Note: In case of success free the buffer only when registered callback is called. */
        }
    }
    return;
}

static void QapiSendCompleteCb(uint8_t SqId, uint16_t BufLen, char *Buf, void *ServiceCxt, void *ServiceData)
{
    if(Buf)
        mmlReleaseBuf(SqId, &Buf[QS_IOTD_HEADER_LEN]);

    return;
}

static void QapiRcvThread(void *Param)
{
    int32_t result = 0;
    uint32_t signal_Set = 0, cookie = 0;
    mmlCb_t msgRcvdCb = NULL;
    void *serviceCxt = NULL;
    char *buf = NULL;
    uint8_t module = (uint32_t)Param;
	uint16_t bufLen;
    moduleCxt_t *moduleCxt = QH_MODULE_INFO_CXT(qsCommonCxt, module);

    qurt_signal_set(&moduleCxt->event, QS_THREAD_READY);
    do
    {
        result = qurt_signal_wait_timed(&moduleCxt->event, moduleCxt->mask,
                (QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK),
                (uint32 *)&signal_Set, QURT_TIME_WAIT_FOREVER);

        if(QURT_EOK != result)
        {
            /* qurt_signal_destroy() is called. */
            break;
        }

        while((MML_SUCCESS_E == mmlDeq(QAPI_SQ_ID, (void **)&buf, MML_DIR_RCV, &module)) && buf)
        {
            mmlServiceRetrieveCb(QAPI_SQ_ID, MML_DIR_RCV, (void *)&msgRcvdCb, &serviceCxt);
			bufLen = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(buf);
			if(msgRcvdCb && (bufLen > QS_IOTD_HEADER_LEN))
            {
                cookie = READ_UNALIGNED_LITTLE_ENDIAN_UINT32(QSPACKET_COOKIE(buf));

				/* Call the set callback.
				 * RCV callbacks should free the memory irrespective of success or failure.
				 * These callbacks must use mmlReleaseBuf() and not QsReleaseBuf(). */
                msgRcvdCb(QAPI_SQ_ID, bufLen - QS_IOTD_HEADER_LEN, 
                          &buf[QS_IOTD_HEADER_LEN], serviceCxt, (void *)cookie);
                msgRcvdCb = NULL;
            }
            else
            {
				/* Release buffer in case RCV callback not found */
                QsReleaseBuf(buf);
            }
            buf = NULL;
        }
    } while(TRUE);
    qurt_thread_stop();
}


static SerStatus_t CreateThread(void *cxt, uint32_t ModuleID, const char *Name)
{
    qurt_thread_attr_t attr;
    qurt_thread_t handle;
    int32_t result = QURT_EOK;
    uint32 signal_Set = 0;
    moduleCxt_t *moduleCxt = NULL;
    moduleCommonCxt_t *moduleCommonCxt = QH_MODULE_CMN_CXT(cxt);

    qurt_mutex_lock(&moduleCommonCxt->mutex);
    moduleCxt = QH_MODULE_INFO_CXT(cxt, ModuleID);
    qurt_mutex_unlock(&moduleCommonCxt->mutex);

    if(!moduleCxt)
    {
        return ssFailure;
    }

    qurt_thread_attr_init(&attr);
    qurt_thread_attr_set_name(&attr, Name);
    qurt_thread_attr_set_priority(&attr, QS_PRIORITY);
    qurt_thread_attr_set_stack_size(&attr, QS_STACK);
    result = qurt_thread_create(&handle, &attr, QapiRcvThread, (void *)ModuleID);
    if (QURT_EOK != result)
    {
        return ssFailure;
    }

    /* Wait for the new thread to start */
    result = qurt_signal_wait_timed(&moduleCxt->event, QS_THREAD_READY,
            (QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK),
            &signal_Set, QURT_TIME_WAIT_FOREVER);
    if(QURT_EOK != result)
    {
        return ssFailure;
    }
    return ssSuccess;
}

static SerStatus_t ModuleInit(void *cxt, uint8_t ModuleID)
{
    uint32_t ret_Val = ssFailure;
    moduleCommonCxt_t *moduleCommonCxt = NULL;
    moduleCxt_t *moduleCxt = NULL;

    moduleCommonCxt = QH_MODULE_CMN_CXT(cxt);
    qurt_mutex_lock(&moduleCommonCxt->mutex);
    /* If module is invalid or if it is already initialized, return error */
    if(QH_MODULE_INFO_CXT(cxt, ModuleID))
    {
        qurt_mutex_unlock(&moduleCommonCxt->mutex);
        return ssFailure;
    }

    /* Initialize the module specific attributes */
    moduleCommonCxt->cxts[ModuleID] = (moduleCxt_t *)malloc(sizeof(moduleCxt_t));
    moduleCxt = moduleCommonCxt->cxts[ModuleID];
    if(!moduleCxt)
    {
        qurt_mutex_unlock(&moduleCommonCxt->mutex);
        return ssFailure;
    }
    memset(moduleCxt, 0, sizeof(moduleCxt_t));
    qurt_mutex_unlock(&moduleCommonCxt->mutex);

    if(ssSuccess != QsInitQueue(&moduleCxt->queue))
    {
        return ssFailure;
    }

    if(QURT_EOK != qurt_mutex_create(&moduleCxt->mutex))
    {
        return ssFailure;
    }

    if(QURT_EOK != qurt_signal_create(&moduleCxt->event))
    {
        return ssFailure;
    }

    switch(ModuleID)
    {
        case QS_MODULE_WLAN:
            moduleCxt->mask = QS_WLAN_SIG;
            ret_Val = CreateThread(cxt, QS_MODULE_WLAN, "QS_WLAN");
            break;

        case QS_MODULE_BLE:
            moduleCxt->mask = QS_BLE_SIG;
            ret_Val = CreateThread(cxt, QS_MODULE_BLE, "QS_BLE");
            break;

        case QS_MODULE_HMI:
            moduleCxt->mask = QS_HMI_SIG;
            ret_Val = CreateThread(cxt, QS_MODULE_HMI, "QS_HMI");
            break;

        case QS_MODULE_THREAD:
            moduleCxt->mask = QS_TWN_SIG;
            ret_Val = CreateThread(cxt, QS_MODULE_THREAD, "QS_THREAD");
            break;

        case QS_MODULE_ZIGBEE:
            moduleCxt->mask = QS_ZB_SIG;
            ret_Val = CreateThread(cxt, QS_MODULE_ZIGBEE, "QS_ZIGBEE");
            break;

        case QS_MODULE_HERH:
            moduleCxt->mask = QS_HERH_SIG;
            ret_Val = CreateThread(cxt, QS_MODULE_HERH, "QS_HERH");
            break;

        case QS_MODULE_COEX:
            moduleCxt->mask = QS_COEX_SIG;
            ret_Val = CreateThread(cxt, QS_MODULE_COEX, "QS_COEX");
            break;

        case QS_MODULE_FWUPGRADE:
            moduleCxt->mask = QS_FWUPGRADE_SIG;
            qurt_mutex_unlock(&moduleCxt->mutex);
            ret_Val = CreateThread(cxt, QS_MODULE_FWUPGRADE, "QS_FWUPGRADE");
            break;

        case QS_MODULE_TLMM:
            moduleCxt->mask = QS_TLMM_SIG;
            qurt_mutex_unlock(&moduleCxt->mutex);
            ret_Val = CreateThread(cxt, QS_MODULE_TLMM, "QS_TLMM");
            break;

        default:
            return ssFailure;
    }

    return ret_Val;
}

SerStatus_t QapiInit(void *cxt)
{
    qsCommonCxt_t *commonCxt = (qsCommonCxt_t *)cxt;
    uint8_t ModuleID = 0;

    /* Register for MML queue for QAPI module. */
    if(MML_SUCCESS_E != mmlServiceRegisterCb(QAPI_SQ_ID, QapiRcvCompleteCb, QapiSendCompleteCb, NULL))
    {
        return ssFailure;
    }

    /* Create QAPI module context */
    commonCxt->moduleCxt = (moduleCommonCxt_t *)malloc(sizeof(moduleCommonCxt_t));
    if(!commonCxt->moduleCxt)
    {
        return ssFailure;
    }
    memset(commonCxt->moduleCxt, 0, sizeof(moduleCommonCxt_t));

    if(QURT_EOK != qurt_mutex_create(&commonCxt->moduleCxt->mutex))
    {
        return ssFailure;
    }

    /* Currently each module has its own thread and hence initialization is done per module.
     * This will change. */
    for(ModuleID = 0; ModuleID < QS_MODULE_MAX; ModuleID++)
    {
        /* Initialized specified module */
        if(ssSuccess != ModuleInit(commonCxt, ModuleID))
        {
            break;
        }
    }

    if(QS_MODULE_MAX == ModuleID)
        return ssSuccess;
    else
        return ssFailure;
}

static void ModuleDeInit(void *cxt, uint8_t ModuleID)
{
    moduleCommonCxt_t *moduleCommonCxt = NULL;
    moduleCxt_t *moduleCxt = NULL;

    /* Common module context */
    moduleCommonCxt = QH_MODULE_CMN_CXT(cxt);
    if(!moduleCommonCxt)
    {
        return;
    }

    qurt_mutex_lock(&moduleCommonCxt->mutex);
    /* Module specific context */
    moduleCxt = QH_MODULE_INFO_CXT(cxt, ModuleID);
    if(!moduleCxt)
    {
        return;
    }

    qurt_mutex_lock(&moduleCxt->mutex);

    /* qurt_signal_destroy() will wake up the threads waiting on the event. */
    QsDeInitQueue(&moduleCxt->queue);
    qurt_signal_delete(&moduleCxt->event);
    qurt_mutex_unlock(&moduleCxt->mutex);
    qurt_mutex_delete(&moduleCxt->mutex);
    free(moduleCxt);
    moduleCommonCxt->cxts[ModuleID] = NULL;

    qurt_mutex_unlock(&moduleCommonCxt->mutex);
    return;
}


void QapiDeInit(void *cxt)
{
    qsCommonCxt_t *commonCxt = (qsCommonCxt_t *)cxt;
    uint8_t ModuleID = 0;

    for(ModuleID = 0; ModuleID < QS_MODULE_MAX; ModuleID++)
    {
        ModuleDeInit(commonCxt, ModuleID);
    }

    qurt_mutex_delete(&commonCxt->moduleCxt->mutex);
    free(commonCxt->moduleCxt);
    commonCxt->moduleCxt = NULL;
    mmlServiceDeregisterCb(QAPI_SQ_ID, NULL);
    return;
}

static Boolean_t MapQSModuleID(uint8_t ModuleID, uint8_t *QtModule)
{
    Boolean_t RetVal = TRUE;

    /* Map the module ID to the QT module type depending on the mux */
    /* configuration. */
    switch (ModuleID)
    {
        case MODULE_WLAN:
            *QtModule = QS_MODULE_WLAN;
            break;

        case MODULE_BLE:
#if QS_WPAN_BLE_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD
            *QtModule = QS_MODULE_BLE;
#elif QS_WPAN_BLE_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD
            *QtModule = QS_MODULE_HMI;
#elif QS_WPAN_BLE_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD
            *QtModule = QS_MODULE_THREAD;
#elif QS_WPAN_BLE_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD
            *QtModule = QS_MODULE_ZIGBEE;
#elif QS_WPAN_BLE_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD
            *QtModule = QS_MODULE_HERH;
#elif QS_WPAN_BLE_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD
            *QtModule = QS_MODULE_COEX;
#elif QS_WPAN_BLE_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD
            *QtModule = QS_MODULE_FWUPGRADE;
#elif QS_WPAN_BLE_MODULE_MAPPING == QS_WPAN_USE_TLMM_THREAD
            *QtModule = QS_MODULE_TLMM;
#else
            RetVal = FALSE;
#endif
            break;

        case MODULE_HMI:
#if QS_WPAN_HMI_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD
            *QtModule = QS_MODULE_BLE;
#elif QS_WPAN_HMI_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD
            *QtModule = QS_MODULE_HMI;
#elif QS_WPAN_HMI_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD
            *QtModule = QS_MODULE_THREAD;
#elif QS_WPAN_HMI_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD
            *QtModule = QS_MODULE_ZIGBEE;
#elif QS_WPAN_HMI_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD
            *QtModule = QS_MODULE_HERH;
#elif QS_WPAN_HMI_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD
            *QtModule = QS_MODULE_COEX;
#elif QS_WPAN_HMI_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD
            *QtModule = QS_MODULE_FWUPGRADE;
#elif QS_WPAN_HMI_MODULE_MAPPING == QS_WPAN_USE_TLMM_THREAD
            *QtModule = QS_MODULE_TLMM;
#else
            RetVal = FALSE;
#endif
            break;

        case MODULE_ZB:
#if QS_WPAN_ZB_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD
            *QtModule = QS_MODULE_BLE;
#elif QS_WPAN_ZB_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD
            *QtModule = QS_MODULE_HMI;
#elif QS_WPAN_ZB_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD
            *QtModule = QS_MODULE_THREAD;
#elif QS_WPAN_ZB_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD
            *QtModule = QS_MODULE_ZIGBEE;
#elif QS_WPAN_ZB_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD
            *QtModule = QS_MODULE_HERH;
#elif QS_WPAN_ZB_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD
            *QtModule = QS_MODULE_COEX;
#elif QS_WPAN_ZB_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD
            *QtModule = QS_MODULE_FWUPGRADE;
#elif QS_WPAN_ZB_MODULE_MAPPING == QS_WPAN_USE_TLMM_THREAD
            *QtModule = QS_MODULE_TLMM;
#else
            RetVal = FALSE;
#endif
            break;

        case MODULE_TWN:
#if QS_WPAN_TWN_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD
            *QtModule = QS_MODULE_BLE;
#elif QS_WPAN_TWN_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD
            *QtModule = QS_MODULE_HMI;
#elif QS_WPAN_TWN_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD
            *QtModule = QS_MODULE_THREAD;
#elif QS_WPAN_TWN_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD
            *QtModule = QS_MODULE_ZIGBEE;
#elif QS_WPAN_TWN_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD
            *QtModule = QS_MODULE_HERH;
#elif QS_WPAN_TWN_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD
            *QtModule = QS_MODULE_COEX;
#elif QS_WPAN_TWN_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD
            *QtModule = QS_MODULE_FWUPGRADE;
#elif QS_WPAN_TWN_MODULE_MAPPING == QS_WPAN_USE_TLMM_THREAD
            *QtModule = QS_MODULE_TLMM;
#else
            RetVal = FALSE;
#endif
            break;

        case MODULE_HERH:
#if QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD
            *QtModule = QS_MODULE_BLE;
#elif QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD
            *QtModule = QS_MODULE_HMI;
#elif QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD
            *QtModule = QS_MODULE_THREAD;
#elif QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD
            *QtModule = QS_MODULE_ZIGBEE;
#elif QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD
            *QtModule = QS_MODULE_HERH;
#elif QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD
            *QtModule = QS_MODULE_COEX;
#elif QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD
            *QtModule = QS_MODULE_FWUPGRADE;
#elif QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_TLMM_THREAD
            *QtModule = QS_MODULE_TLMM;
#else
            RetVal = FALSE;
#endif
            break;

        case MODULE_COEX:
#if QS_WPAN_COEX_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD
            *QtModule = QS_MODULE_BLE;
#elif QS_WPAN_COEX_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD
            *QtModule = QS_MODULE_HMI;
#elif QS_WPAN_COEX_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD
            *QtModule = QS_MODULE_THREAD;
#elif QS_WPAN_COEX_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD
            *QtModule = QS_MODULE_ZIGBEE;
#elif QS_WPAN_COEX_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD
            *QtModule = QS_MODULE_HERH;
#elif QS_WPAN_COEX_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD
            *QtModule = QS_MODULE_COEX;
#elif QS_WPAN_COEX_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD
            *QtModule = QS_MODULE_FWUPGRADE;
#elif QS_WPAN_COEX_MODULE_MAPPING == QS_WPAN_USE_TLMM_THREAD
            *QtModule = QS_MODULE_TLMM;
#else
            RetVal = FALSE;
#endif
            break;

        case MODULE_FIRMWARE_UPGRADE_EXT:
#if QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD
            *QtModule = QS_MODULE_BLE;
#elif QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD
            *QtModule = QS_MODULE_HMI;
#elif QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD
            *QtModule = QS_MODULE_THREAD;
#elif QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD
            *QtModule = QS_MODULE_ZIGBEE;
#elif QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD
            *QtModule = QS_MODULE_HERH;
#elif QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD
            *QtModule = QS_MODULE_COEX;
#elif QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD
            *QtModule = QS_MODULE_FWUPGRADE;
#elif QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_TLMM_THREAD
            *QtModule = QS_MODULE_TLMM;
#else
            RetVal = FALSE;
#endif
            break;

        case MODULE_TLMM:
#if QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD
            *QtModule = QS_MODULE_BLE;
#elif QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD
            *QtModule = QS_MODULE_HMI;
#elif QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD
            *QtModule = QS_MODULE_THREAD;
#elif QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD
            *QtModule = QS_MODULE_ZIGBEE;
#elif QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD
            *QtModule = QS_MODULE_HERH;
#elif QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD
            *QtModule = QS_MODULE_COEX;
#elif QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD
            *QtModule = QS_MODULE_FWUPGRADE;
#elif QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_TLMM_THREAD
            *QtModule = QS_MODULE_TLMM;
#else
            RetVal = FALSE;
#endif
            break;

        default:
            RetVal = FALSE;
            break;
    }

    return(RetVal);
}

static Boolean_t AllocateResponsePacket(uint8_t *UID, uint8_t ModuleID, uint16_t FileID, uint16_t FunctionID, PackedBuffer_t *PackedBuffer, uint16_t Size)
{
    Boolean_t        RetVal = TRUE;
    qsQapiResp_t     *Response = NULL;
    uint8_t          Module;
    int              i = 0;
    char             *RespBuf = NULL;

    /* Map the QS module ID to the qt_qapi_Module_e type. */
    RetVal = MapQSModuleID(ModuleID, &Module);
    if(FALSE == RetVal) {
        return RetVal;
    }
//hostLog("Sending resp %d\n",Size);
    /* Get a buffer. */
//    RespBuf = (char *)malloc(QS_TOTAL_LEN(QSRESPONSE_T_SIZE(Size)));
    QsGetBuf(&RespBuf, QS_TOTAL_LEN(QSRESPONSE_T_SIZE(Size)), BUF_TYPE_RESP);
    if(RespBuf)
    {
        memset(RespBuf, 0, QS_TOTAL_LEN(QSRESPONSE_T_SIZE(Size)));
        PackedBuffer->Packet = (uint8_t *)RespBuf;
        Response = (qsQapiResp_t *)(QSPACKET_HEADER(RespBuf));

        /* Set the packed buffer parameters. */
        PackedBuffer->PacketType = QS_RETURN_E;
        PackedBuffer->Length = Size;
        PackedBuffer->Start = QSRESPONSE_DATA(Response);
        InitializePackedBuffer(PackedBuffer, PackedBuffer->Start, Size);

        /* Write the packet parameters. */
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Response->Header.TotalLength, QSRESPONSE_T_SIZE(Size));
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8( &Response->Header.ModuleID,    Module);
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8( &Response->Header.PacketType,  QS_RETURN_E);
        for(i = 0; i < 8; i++)
        {
            Response->Header.UID[i] = UID[i];
        }
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Response->Header.FileID,      FileID);
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Response->Header.FunctionID,  FunctionID);
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Response->Header.DataLength,  Size);
        RetVal = TRUE;
    }
    else
    {
        RetVal = FALSE;
    }

    return(RetVal);
}

static Boolean_t AllocateEventPacket(uint8_t ModuleID, uint16_t FileID, uint16_t FunctionID, PackedBuffer_t *PackedBuffer, uint16_t Size)
{
    Boolean_t          RetVal = TRUE;
    qsEvent_t          *Event = NULL;
    uint8_t            Module;
    char               *EventBuf = NULL;
    int                i = 0;

    /* Map the QS module ID to the qt_qapi_Module_e type. */
    RetVal = MapQSModuleID(ModuleID, &Module);
    if(FALSE == RetVal) {
        return RetVal;
    }

    /* Get a buffer. */
//    EventBuf = (char *)malloc(QS_TOTAL_LEN(QSEVENT_T_SIZE(Size)));
    QsGetBuf(&EventBuf, QS_TOTAL_LEN(QSEVENT_T_SIZE(Size)), BUF_TYPE_ASYNC);
    if(EventBuf)
    {
        memset(EventBuf, 0, QS_TOTAL_LEN(QSEVENT_T_SIZE(Size)));
        PackedBuffer->Packet = (uint8_t *)EventBuf;
        Event = (qsEvent_t *)(QSPACKET_HEADER(EventBuf));

        /* Set the packed buffer parameters. */
        PackedBuffer->PacketType = QS_ASYNC_E;
        PackedBuffer->Length = Size;
        PackedBuffer->Start = QSEVENT_DATA(Event);
        InitializePackedBuffer(PackedBuffer, PackedBuffer->Start, Size);

        /* Write the packet parameters. */
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Event->Header.TotalLength, QSEVENT_T_SIZE(Size));
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8( &Event->Header.ModuleID,    Module);
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8( &Event->Header.PacketType,  QS_ASYNC_E);
        for(i = 0; i < 8; i++)
        {
            Event->Header.UID[i] = 0;
        }
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Event->Header.FileID,      FileID);
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Event->Header.FunctionID,  FunctionID);
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Event->Header.DataLength,  Size);

        RetVal = TRUE;
    }
    else
    {
        RetVal = FALSE;
    }

    return(RetVal);
}

/**
  Allocates a packed buffer.

  @param ModuleID     ID of the module sending this packet.
  @param FileID       ID of the file sending this packet.
  @param FunctionID   ID of the function sending this packet.
  @param PackedBuffer Pointer to the packed buffer to be allocated.
  @param Size         Required size of the buffer.

  @return the status result of the allocation.
  */
Boolean_t AllocatePackedBuffer(uint8_t *UID, qsPacketType_t PacketType, uint8_t ModuleID, uint16_t FileID, uint16_t FunctionID, PackedBuffer_t *PackedBuffer, uint16_t Size)
{
    Boolean_t RetVal = TRUE;

    switch (PacketType)
    {
        case QS_RETURN_E:
            RetVal = AllocateResponsePacket(UID, ModuleID, FileID, FunctionID, PackedBuffer, Size);
            break;
        case QS_ASYNC_E:
            RetVal = AllocateEventPacket(ModuleID, FileID, FunctionID, PackedBuffer, Size);
            break;
        default:
            RetVal = FALSE;
    }

    return(RetVal);
}

/**
  Sends an event packet.

  @param InputBuffer Pointer to the packed buffer to send.
  */
SerStatus_t SendEvent(PackedBuffer_t *InputBuffer)
{
    SerStatus_t RetVal = ssSuccess;
    uint16_t len = 0;
    char *buf = (char *)InputBuffer->Packet;

    len = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&((qsQapiPacketHeader_t *)QSPACKET_HEADER(buf))->TotalLength);
    if(MML_SUCCESS_E != mmlServiceQueueSend(QAPI_SQ_ID, QS_TOTAL_LEN(len), buf, NULL))
    {
        //free(buf);
		mmlReleaseBuf(QAPI_SQ_ID, &buf[QS_IOTD_HEADER_LEN]);
        RetVal = ssFailure;
    }

    return RetVal;
}

/**
  Creates an error callback packet to send to the host.

  @param ModuleID     ID of the module sending this packet.
  @param FileID       ID of the file sending this packet.
  @param CallbackID   ID of the callback sending this packet.
  @param PackedBuffer Pointer to the packed buffer to send.
  */
void SendErrorCallback(uint8_t ModuleID, uint8_t FileID, uint16_t CallbackID)
{
    PackedBuffer_t     qsInputBuffer;
    SerStatus_t        qsResult = ssSuccess;

    if(AllocatePackedBuffer(NULL, QS_ASYNC_E, MODULE_HERH, QSDEBUGEVENT_FILEID, QSDEBUGEVENT_EVENTID, &qsInputBuffer, QSDEBUGEVENT_T_SIZE))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_8(&qsInputBuffer, &ModuleID);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_8(&qsInputBuffer, &FileID);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_16(&qsInputBuffer, &CallbackID);

        /* Send the event. */
        if(qsResult == ssSuccess)
            qsResult = SendEvent(&qsInputBuffer);

    }
}

#endif /* CONFIG_DAEMON_MODE */

