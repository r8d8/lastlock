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

#ifndef CONFIG_DAEMON_MODE

#include <stdlib.h>
#include "qsQuartz_NonDaemon.h"
#include "qsQuartzUart.h"
#include "qsDataMgr.h"
#include "qsMgmt.h"
#include "qsMml.h"
#include "qsOSAL.h"
#include "qsConfig.h"
#include "qsPack.h"
#include "idlist.h"
#include "filelist.h"
#include "qurt_error.h"
#include "qurt_thread.h"

/* Data types for managing incoming packets in multiple threads */
#define QS_STACK            2048
#define QS_PRIORITY         10
qsCommonCxt_t *qsCommonCxt = NULL;


SerStatus_t QsInitQueue(queue_t *Q)
{
    if(!Q)
    {
        return ssFailure;
    }

    Q->head = NULL;
    Q->tail = NULL;
    if(QURT_EOK != qurt_mutex_create(&Q->mutex))
    {
        return ssFailure;
    }
    return ssSuccess;
}

SerStatus_t QsFreeQueue(queue_t *Q)
{
    bufInfo_t *buf = NULL;

    qurt_mutex_lock(&Q->mutex);
    while(Q->head)
    {
        buf = (bufInfo_t *)Q->head;
        Q->head = buf->next;
        QsReleaseBuf(buf);
    }

    Q->tail = NULL;
    qurt_mutex_unlock(&Q->mutex);
    return ssSuccess;
}

SerStatus_t QsDeInitQueue(queue_t *Q)
{
    QsFreeQueue(Q);
    qurt_mutex_delete(&Q->mutex);
    return ssSuccess;
}

SerStatus_t QsEnq(queue_t *Q, bufInfo_t *Buf)
{
    if(!Q || !Buf)
    {
        return ssFailure;
    }

    /* Enqueue the buffer at the end of the queue */
    qurt_mutex_lock(&Q->mutex);
    if(!Q->head && !Q->tail)
    {
        Q->head = (void *)Buf;
        Q->tail = (void *)Buf;
    }
    else
    {
        ((bufInfo_t *)Q->tail)->next = Buf;
        Q->tail = (void *)Buf;
    }
    qurt_mutex_unlock(&Q->mutex);
    return ssSuccess;
}

SerStatus_t QsDeq(queue_t *Q, bufInfo_t **BufPtr)
{
    bufInfo_t *buf = NULL;
    uint32_t ret_Val = ssFailure;
    if(!Q || !Q->mutex || !BufPtr)
    {
        return ssFailure;
    }

    /* Dequeue a buffer from the head of the queue */
    qurt_mutex_lock(&Q->mutex);
    if(Q->head)
    {
        buf = (bufInfo_t *)Q->head;
        Q->head = buf->next;
        buf->next = NULL;
        if (!Q->head)
        {
            Q->tail = NULL;
        }
        *BufPtr = buf;
        ret_Val = ssSuccess;
    }
    qurt_mutex_unlock(&Q->mutex);
    return ret_Val;
}

/* Processing entry point for received data.
 * Data is put in different queues depending on the module type.
 * A separate worker thread for each module dequeues and processes
 * the request and sends response. */
SerStatus_t QsEnqQapi(bufInfo_t *Buf)
{
    uint8_t module = 0;
    moduleCxt_t *cxt = NULL;
    qsQapiReq_t *command = NULL;

    moduleCommonCxt_t *moduleCxt = QH_MODULE_CMN_CXT(qsCommonCxt);
    if(!moduleCxt || !Buf || !Buf->buf)
    {
        return ssFailure;
    }

    command = (qsQapiReq_t *)(QSPACKET_HEADER(Buf->buf));
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
    if(ssSuccess == QsEnq(&cxt->queue, Buf))
    {
        /* Signal the worker thread and release the mutex */
        qurt_signal_set(&cxt->event, cxt->mask);
        return ssSuccess;
    }
    return ssFailure;
}

/* Return first packet from module specific queue */
SerStatus_t QsDeqQapi(uint8_t ModuleID, bufInfo_t **ReqBufPtr)
{
    moduleCommonCxt_t *moduleCmnCxt = QH_MODULE_CMN_CXT(qsCommonCxt);
    moduleCxt_t *cxt = QH_MODULE_INFO_CXT(qsCommonCxt, ModuleID);
    //    bufInfo_t *req_Buf = NULL;

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
    if(ssSuccess != QsDeq(&cxt->queue, ReqBufPtr))
    {
        return ssFailure;
    }
    return ssSuccess;
}

static SerStatus_t QsProcessReq(bufInfo_t *ReqBuf, bufInfo_t **RespBuf)
{
    SerStatus_t        Result;
    uint8_t            UID[8] = {0};
    uint8_t            ModuleID;
    uint16_t           FileID;
    uint16_t           CmdID;
    uint32_t           RetVal;
    uint32_t           CommandLength;
    PackedBuffer_t     OutputBuffer;
    uint8_t           *CommandData;
    FileEntry_t       *CurrFileEntry;
    FunctionHandler_t *FunctionHandler;
    int                i;
    char              *Req = NULL;

    /* Check the input paramters. */
    if((ReqBuf) && (RespBuf))
    {
        /* Get the command parameters. */
        *RespBuf = NULL;
        Req = QSPACKET_HEADER(ReqBuf->buf);
        qsQapiReq_t *Command = (qsQapiReq_t *)Req;
        CommandData   = QSCOMMAND_DATA(Req);
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

                /* Call the function. */
                Result = (*FunctionHandler)(CommandData, (uint16_t)CommandLength, &OutputBuffer, UID);

                if(Result == ssSuccess)
                {
                    *RespBuf = (bufInfo_t *)OutputBuffer.Packet;
                    RetVal = ssSuccess;
                }
                else
                    RetVal = ssFailure;
            }
            else
                RetVal = ssFailure;
        }
        else
            RetVal = ssFailure;

        if (RetVal != ssSuccess)
        {
            /* Handle function failure and return an error Response. */
            CreateErrorPacket(ModuleID, FileID, CmdID, &OutputBuffer, UID);
            *RespBuf = (bufInfo_t *)OutputBuffer.Packet;
        }

    }
    else
        RetVal = ssFailure;

    return RetVal;
}

SerStatus_t QsReleaseBuf(bufInfo_t *BufInfo)
{
    bufPool_t *bufPool = NULL;

    if(!BufInfo)
    {
        return ssInvalidParameter;
    }

    switch(BufInfo->size)
    {
        case BUF_SIZE_128:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_128);
            break;

        case BUF_SIZE_256:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_256);
            break;

        case BUF_SIZE_512:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_512);
            break;

        case BUF_SIZE_1024:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_1024);
            break;

        case BUF_SIZE_2048:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_2048);
            break;

        default:
            bufPool = NULL;
            break;
    }

    memset(BufInfo->buf, 0, BufInfo->size);
    if(bufPool)
    {
        qurt_mutex_lock(&bufPool->mutex);
        if(bufPool->count < bufPool->threshold)
        {
            /* Replenish the global free list if it is running low on buffers */
            BufInfo->next = bufPool->queue.head;
            bufPool->queue.head = (void *)BufInfo;
            bufPool->count++;
            qurt_mutex_unlock(&bufPool->mutex);
            return ssSuccess;
        }
        qurt_mutex_unlock(&bufPool->mutex);
    }

    /* If global list has enough buffers, free the buffer. */
    BufInfo->next = NULL;
    free(BufInfo->buf);
    free(BufInfo);
    return ssSuccess;
}

SerStatus_t Transmit(uint16_t len, char *Buf)
{
    uint32_t ret_Val = ssSuccess;
    uint8_t module = 0;
    qsQapiPacketHeader_t *header = NULL;
    moduleCxt_t *moduleCxt = NULL;
    moduleCommonCxt_t *moduleCommonCxt = QH_MODULE_CMN_CXT(qsCommonCxt);

    if(!moduleCommonCxt || !Buf)
    {
        return ssFailure;
    }

    header = (qsQapiPacketHeader_t *)QSPACKET_HEADER(Buf);
    module = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(&header->ModuleID);

    qurt_mutex_lock(&moduleCommonCxt->mutex);
    moduleCxt = QH_MODULE_INFO_CXT(moduleCxt, module);
    if(!moduleCxt)
    {
        qurt_mutex_unlock(&moduleCommonCxt->mutex);
        return ssFailure;
    }
    qurt_mutex_lock(&moduleCxt->mutex);
    qurt_mutex_unlock(&moduleCommonCxt->mutex);

    qurt_mutex_unlock(&moduleCxt->mutex);
    ret_Val = QsUartTransmit(moduleCxt->ifname, len, Buf);

    return ret_Val;
}

static void WorkerThread(void *Param)
{
    int32_t result = 0;
    uint32_t signal_Set = 0;
    uint16_t len = 0;
    bufInfo_t *req_Buf = NULL, *resp_Buf = NULL;
    char *resp = NULL;
    uint8_t module = (uint32_t)Param;
    moduleCxt_t *moduleCxt = QH_MODULE_INFO_CXT(qsCommonCxt, module);

    /* Initialize the global context */
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

        while(1)
        {
            req_Buf = NULL;
            QH_QZ_DEQ(QAPI_SQ_ID, &req_Buf, MML_DIRECTION_RX, &module);
            if(!req_Buf)
            {
                break;
            }

            QsProcessReq(req_Buf, &resp_Buf);
            resp = resp_Buf->buf;

            len = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&((qsQapiPacketHeader_t *)QSPACKET_HEADER(resp))->TotalLength);
            QH_QZ_TRANSMIT(QS_TOTAL_LEN(len), resp_Buf->buf);
            QsReleaseBuf(req_Buf);
            QsReleaseBuf(resp_Buf);
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
    result = qurt_thread_create(&handle, &attr, WorkerThread, (void *)ModuleID);
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

static SerStatus_t BufpoolInit(void *cxt)
{
    bufInfo_t *BufInfo = NULL;
    bufPool_t *BufPool = NULL;
    int index = 0;
    uint16_t Size = 0;
    uint32_t ret_Val = ssSuccess;
    qsCommonCxt_t *commonCxt = QH_COMMON_CXT(cxt);
    int buf_Cnt = 0;

    /* Buffer pools are already initialized */
    if(commonCxt->bufPool[0])
    {
        return ssSuccess;
    }

    for(index = 0; index < BUF_NUM_LISTS; index++)
    {
        commonCxt->bufPool[index] = (bufPool_t *)malloc(sizeof(bufPool_t));
        if(!commonCxt->bufPool[index])
        {
            ret_Val = ssFailure;
            break;
        }

        BufPool = commonCxt->bufPool[index];
        memset(BufPool, 0, sizeof(bufPool_t));

        BufPool->count = 0;
        if(QURT_EOK != qurt_mutex_create(&BufPool->mutex))
        {
            ret_Val = ssFailure;
            break;
        }

        switch(index)
        {
            case BUF_INDEX_128:
                BufPool->threshold = BUF_NUM_128;
                Size = BUF_SIZE_128;
                break;

            case BUF_INDEX_256:
                BufPool->threshold = BUF_NUM_256;
                Size = BUF_SIZE_256;
                break;

            case BUF_INDEX_512:
                BufPool->threshold = BUF_NUM_512;
                Size = BUF_SIZE_512;
                break;

            case BUF_INDEX_1024:
                BufPool->threshold = BUF_NUM_1024;
                Size = BUF_SIZE_1024;
                break;

            case BUF_INDEX_2048:
                BufPool->threshold = BUF_NUM_2048;
                Size = BUF_SIZE_2048;
                break;
        }

        if(ssSuccess != QsInitQueue(&BufPool->queue))
        {
            ret_Val = ssFailure;
            break;
        }

        for (buf_Cnt = 0; buf_Cnt < BufPool->threshold; buf_Cnt++)
        {
            BufInfo = (bufInfo_t *)malloc(sizeof(bufInfo_t));
            if (!BufInfo)
            {
                ret_Val = ssFailure;
                break;
            }

            BufInfo->size = Size;
            BufInfo->buf = (char *)malloc(Size);
            if (!BufInfo->buf)
            {
                free(BufInfo);
                ret_Val = ssFailure;
                break;
            }
            memset(BufInfo->buf, 0, Size);
            BufInfo->next = BufPool->queue.head;
            BufPool->queue.head = (void *)BufInfo;
            BufPool->count++;
        }

        if(ssSuccess != ret_Val)
        {
            break;
        }

        ret_Val = ssSuccess;
    }

    return ret_Val;
}

static void BufpoolDeInit(void *cxt)
{
    bufInfo_t *BufInfo = NULL;
    bufPool_t *BufPool = NULL;
    int index = 0;

    qsCommonCxt_t *commonCxt = QH_COMMON_CXT(cxt);

    for(index = 0; index < BUF_NUM_LISTS; index++)
    {
        BufPool = commonCxt->bufPool[index];
        if(!BufPool)
        {
            continue;
        }

        qurt_mutex_lock(&BufPool->mutex);
        while(BufPool->queue.head)
        {
            BufInfo = (bufInfo_t *)BufPool->queue.head;
            BufPool->queue.head = (void *)BufInfo->next;
            free(BufInfo->buf);
            free(BufInfo);
        }
        qurt_mutex_unlock(&BufPool->mutex);
        qurt_mutex_delete(&BufPool->mutex);
        commonCxt->bufPool[index] = NULL;
    }
    return;
}

SerStatus_t QsGetBuf(bufInfo_t **BufInfoPtr, uint16_t Size)
{
    bufInfo_t *BufInfo = NULL;
    bufPool_t *BufPool = NULL;

    if (!BufInfoPtr)
    {
        return ssInvalidParameter;
    }

    if(Size <= BUF_SIZE_128)
    {
        BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_128);
        Size = BUF_SIZE_128;
    }
    else if(Size <= BUF_SIZE_256)
    {
        BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_256);
        Size = BUF_SIZE_256;
    }
    else if(Size <= BUF_SIZE_512)
    {
        BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_512);
        Size = BUF_SIZE_512;
    }
    else if(Size <= BUF_SIZE_1024)
    {
        BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_1024);
        Size = BUF_SIZE_1024;
    }
    else if(Size <= BUF_SIZE_2048)
    {
        BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_2048);
        Size = BUF_SIZE_2048;
    }
    else
    {
        return ssInvalidParameter;
    }

    if(BufPool)
    {
        if(ssSuccess == QsDeq(&BufPool->queue, BufInfoPtr))
        {
            BufPool->count--;
            return ssSuccess;
        }
    }

    /* free_buf_list is empty or not initialzed */
    BufInfo = (bufInfo_t *)malloc(sizeof(bufInfo_t));
    if (!BufInfo)
    {
        return ssFailure;
    }

    memset(BufInfo, 0, sizeof(bufInfo_t));
    BufInfo->buf = (char *)malloc(Size);
    if (!BufInfo->buf)
    {
        free(BufInfo);
        return ssFailure;
    }
    memset(BufInfo->buf, 0, Size);
    BufInfo->next = NULL;
    *BufInfoPtr = BufInfo;

    return ssSuccess;
}


static SerStatus_t TransportDeInit(uint32_t TransportID, uint32_t Ifname)
{
    uint32_t ret_Val = ssSuccess;
    switch(TransportID)
    {
        case QS_UART_E:
            ret_Val = QsUartDeInit(Ifname);
            break;

        default:
            break;

    }
    return ret_Val;

}

/* Common transport layer initialization */
static SerStatus_t TransportInit(uint32_t TransportID, uint32_t Ifname)
{
    uint32_t ret_Val = ssSuccess;
    switch(TransportID)
    {
        case QS_UART_E:
            ret_Val = QsUartInit(Ifname);
            break;
        default:
            ret_Val = ssFailure;
            break;

    }

    if(ssSuccess != ret_Val)
    {
        (void)TransportDeInit(TransportID, Ifname);
    }
    return ret_Val;
}


static SerStatus_t QsModuleInit(void *cxt, uint8_t ModuleID)
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

        default:
            return ssFailure;
    }

    return ret_Val;
}

SerStatus_t QsInit(uint8_t ModuleID, uint32_t TransportID, uint32_t Ifname)
{
    qsCommonCxt_t *commonCxt = NULL;
    moduleCommonCxt_t *moduleCxt = NULL;
    uint32_t ret_Val = ssFailure;

    do
    {
        if(!qsCommonCxt)
        {
            qsCommonCxt = (qsCommonCxt_t *)malloc(sizeof(qsCommonCxt_t));
            if(!qsCommonCxt)
            {
                return ssFailure;
            }
            commonCxt = qsCommonCxt;
            memset(commonCxt, 0, sizeof(qsCommonCxt_t));

            /* Initialize buffer pool */
            ret_Val = BufpoolInit(commonCxt);
            if(ssSuccess != ret_Val)
            {
                break;
            }

            commonCxt->moduleCxt = (moduleCommonCxt_t *)malloc(sizeof(moduleCommonCxt_t));
            memset(commonCxt->moduleCxt, 0, sizeof(moduleCommonCxt_t));
            if(QURT_EOK != qurt_mutex_create(&commonCxt->moduleCxt->mutex))
            {
                break;
            }
        }

        commonCxt = qsCommonCxt;
        /* Initialized specified module */
        if(ssSuccess != QsModuleInit(commonCxt, ModuleID))
        {
            break;
        }

        /* Initialize specified transport type */
        if(ssSuccess != TransportInit(TransportID, Ifname))
        {
            break;
        }

        /* All initializations succeeded, set the transport ID and interface name */
        moduleCxt = QH_MODULE_CMN_CXT(commonCxt);
        qurt_mutex_lock(&moduleCxt->mutex);
        QH_MODULE_INFO_CXT(commonCxt,ModuleID)->transport = TransportID;
        QH_MODULE_INFO_CXT(commonCxt,ModuleID)->ifname = Ifname;
        QH_MODULE_CMN_CXT(commonCxt)->numModulesInitialized++;
        qurt_mutex_unlock(&moduleCxt->mutex);
        return ssSuccess;
    } while(0);

    QsDeInit(ModuleID);
    return ssFailure;
}


static SerStatus_t QsModuleDeInit(void *cxt, uint8_t ModuleID)
{
    uint32_t ret_Val = ssFailure;
    moduleCommonCxt_t *moduleCommonCxt = NULL;
    moduleCxt_t *moduleCxt = NULL;

    moduleCommonCxt = QH_MODULE_CMN_CXT(cxt);
    if(!moduleCommonCxt)
    {
        return ssFailure;
    }

    do
    {
        qurt_mutex_lock(&moduleCommonCxt->mutex);
        moduleCxt = QH_MODULE_INFO_CXT(cxt, ModuleID);
        if(!moduleCxt)
        {
            break;
        }

        qurt_mutex_lock(&moduleCxt->mutex);

        ret_Val = TransportDeInit(moduleCxt->transport, moduleCxt->ifname);
        if(ssSuccess != ret_Val)
        {
            qurt_mutex_unlock(&moduleCxt->mutex);
            break;
        }

        /* qurt_signal_destroy() will wake up the threads waiting on the event. */
        QsDeInitQueue(&moduleCxt->queue);
        qurt_signal_delete(&moduleCxt->event);
        qurt_mutex_unlock(&moduleCxt->mutex);
        qurt_mutex_delete(&moduleCxt->mutex);
        free(moduleCxt);
        moduleCommonCxt->cxts[ModuleID] = NULL;
        moduleCommonCxt->numModulesInitialized--;
        qurt_mutex_unlock(&moduleCommonCxt->mutex);
        return ssSuccess;
    } while(0);

    qurt_mutex_unlock(&moduleCommonCxt->mutex);
    return ssFailure;

}


SerStatus_t QsDeInit(uint8_t ModuleID)
{
    moduleCommonCxt_t *moduleCommonCxt = NULL;
    qsCommonCxt_t *commonCxt = qsCommonCxt;

    if(!commonCxt)
    {
        return ssFailure;
    }

    do
    {
        if(ssSuccess != QsModuleDeInit(commonCxt, ModuleID))
        {
            break;
        }

        moduleCommonCxt = QH_MODULE_CMN_CXT(commonCxt);
        qurt_mutex_lock(&moduleCommonCxt->mutex);
        if(0 == moduleCommonCxt->numModulesInitialized)
        {
            BufpoolDeInit(commonCxt);
            qurt_mutex_unlock(&commonCxt->moduleCxt->mutex);
            qurt_mutex_delete(&commonCxt->moduleCxt->mutex);

            commonCxt->moduleCxt->mutex = 0;
            free(commonCxt->moduleCxt);
            commonCxt->moduleCxt = NULL;
        }
        else
        {
            qurt_mutex_unlock(&commonCxt->moduleCxt->mutex);
        }
    } while(0);

    //ToDo: Free common context
    return ssFailure;
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
    bufInfo_t        *RespBufInfo = NULL;

    /* Map the QS module ID to the qt_qapi_Module_e type. */
    RetVal = MapQSModuleID(ModuleID, &Module);

    /* Get a buffer. */
    if((RetVal) && (QsGetBuf(&RespBufInfo, QS_TOTAL_LEN(QSRESPONSE_T_SIZE(Size))) == ssSuccess) && (RespBufInfo) && (RespBufInfo->buf))
    {
        PackedBuffer->Packet = (uint8_t *)RespBufInfo;
        Response = (qsQapiResp_t *)(QSPACKET_HEADER(RespBufInfo->buf));

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
    bufInfo_t          *EventBuffer = NULL;
    int                i = 0;

    /* Map the QS module ID to the qt_qapi_Module_e type. */
    RetVal = MapQSModuleID(ModuleID, &Module);

    /* Get a buffer. */
    if((RetVal) && (QsGetBuf(&EventBuffer, QS_TOTAL_LEN(QSEVENT_T_SIZE(Size))) == ssSuccess) && (EventBuffer) && (EventBuffer->buf))
    {
        PackedBuffer->Packet = (uint8_t *)EventBuffer;
        Event = (qsEvent_t *)(QSPACKET_HEADER(EventBuffer->buf));

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
  Frees a packed buffer.

  @param PackedBuffer Pointer to the packed buffer to be freed.
  */
void FreePackedBuffer(PackedBuffer_t *PackedBuffer)
{
    if(PackedBuffer->Packet != NULL)
    {
        /* Free the different packet types. */
        switch(PackedBuffer->PacketType)
        {
            case QS_RETURN_E:
                /* Framework handles this case. */
                break;
            case QS_ASYNC_E:
                QsReleaseBuf((bufInfo_t *)PackedBuffer->Packet);
                break;
            default:
                break;
        }

        PackedBuffer->Packet = NULL;
    }
}

/**
  Sends an event packet.

  @param InputBuffer Pointer to the packed buffer to send.
  */
SerStatus_t SendEvent(PackedBuffer_t *InputBuffer)
{
    SerStatus_t RetVal;
    uint16_t len = 0;
    char *buf = ((bufInfo_t *)InputBuffer->Packet)->buf;

    len = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&((qsQapiPacketHeader_t *)QSPACKET_HEADER(buf))->TotalLength);

    if(QH_QZ_TRANSMIT(QS_TOTAL_LEN(len), buf) == ssSuccess)
    {
        RetVal = ssSuccess;
    }
    else
    {
        RetVal = ssFailure;
    }

    return RetVal;
}

/**
  Creates an error packet to send to the host.

  @param ModuleID     ID of the module sending this packet.
  @param FileID       ID of the file sending this packet.
  @param FunctionID   ID of the function sending this packet.
  @param PackedBuffer Pointer to the packed buffer to send.

  @return TRUE if successful or FALSE upon failure.
  */
Boolean_t CreateErrorPacket(uint8_t ModuleID, uint16_t FileID, uint16_t FunctionID, PackedBuffer_t *PackedBuffer, uint8_t *UID)
{
    Boolean_t    RetVal = TRUE;
    qsQapiResp_t *Response;
    int          i = 0;

    /* Write the packet parameters. */
    if((RetVal) && (PackedBuffer->Packet != NULL))
    {
        /* Set temp values to the packet and TLV. */
        Response = (qsQapiResp_t *)PackedBuffer->Packet;

        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Response->Header.TotalLength, QSRESPONSE_T_SIZE(0));
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8( &Response->Header.ModuleID,    ModuleID);
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8( &Response->Header.PacketType,  QS_RETURN_E);
        for(i = 0; i < 8; i++)
        {
            Response->Header.UID[i] = UID[i];
        }
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Response->Header.FileID,      FileID);
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Response->Header.FunctionID,  FunctionID);
        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&Response->Header.DataLength,  0);
        RetVal = TRUE;
    }
    else
    {
        RetVal = FALSE;
    }

    return(RetVal);
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

        /* Free the buffer. */
        FreePackedBuffer(&qsInputBuffer);
    }
}

#endif  /* CONFIG_DAEMON_MODE */

