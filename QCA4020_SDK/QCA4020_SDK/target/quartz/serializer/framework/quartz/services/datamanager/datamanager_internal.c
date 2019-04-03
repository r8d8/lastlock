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

#include <stdlib.h>
#include "qurt_error.h"
#include "common_cxt.h"

#ifdef CONFIG_DAEMON_MODE

#define RESP_TIMEOUT 30000 /* milliseconds */

static int8_t DMFindFreeEntry()
{
    int8_t i = 0;

    dataIfCxt_t *dataMgrIfCxt = QH_DATAMGR_IF_CXT(qsCommonCxt);
    if(!dataMgrIfCxt)
    {
        return -1;
    }

    for(i = 0; i < QS_IOTD_MAX_DATA_INTERFACE; i++)
    {
        if(dataMgrIfCxt[i].inUse == 0)
        {
            dataMgrIfCxt[i].inUse = 1;
            return i;
        }
    }
    return -1;
}

static int8_t DMFindIfEntry(uint32_t IfId)
{
    int8_t i = 0;

    dataIfCxt_t *dataMgrIfCxt = QH_DATAMGR_IF_CXT(qsCommonCxt);
    if(!dataMgrIfCxt)
    {
        return -1;
    }

    for(i = 0; i < QS_IOTD_MAX_DATA_INTERFACE; i++)
    {
        if(dataMgrIfCxt[i].ifId == IfId)
        {
            return i;
        }
    }
    return -1;
}

static void DMResetIfEntry(int8_t Index)
{
    dataIfCxt_t *dataMgrIfCxt = NULL;
    dataMgrCxt_t *dataMgrCxt = QH_DATAMGR_CXT(qsCommonCxt);
    if(!dataMgrCxt)
    {
        return;
    }

    dataMgrIfCxt = &dataMgrCxt->interfaces[Index];
    dataMgrIfCxt->cmdInProgess = 0;
    dataMgrIfCxt->inUse = 0;
    dataMgrIfCxt->type = 0;
    dataMgrIfCxt->nameLen = 0;
    dataMgrIfCxt->ifId = 0;
    dataMgrIfCxt->cb = NULL;
    dataMgrIfCxt->name[0] = '\0';
    QsFreeQueue(&dataMgrIfCxt->rxQueue);
    return;
}

static uint32_t DMCreateIf(uint8_t SqId, DmIfInitReq_t *Input, uint32_t *Output)
{
    uint32_t ret_Val = DM_SUCCESS_E, signal_Set = 0;
    uint16_t name_len = 0, total_Len = 0;
    int8_t i = 0;
    int result = -1;
    char *reqBuf = NULL, *respBuf = NULL;
    DmIfInitReq_t *cmd = NULL;
    DmHeader_t *respHeader = NULL;

    dataMgrCxt_t *dataMgrCxt = QH_DATAMGR_CXT(qsCommonCxt);
    dataIfCxt_t *dataMgrIfCxt = QH_DATAMGR_IF_CXT(qsCommonCxt);

    if(!dataMgrCxt || !dataMgrIfCxt || !Input->Cb || !Output)
    {
        return DM_FAILURE_E;
    }

    qurt_mutex_lock(&dataMgrCxt->mutex);
    if(dataMgrCxt->createInProgress >= 0)
    {
        /* Create interface in progress, cannot create another interface until the first one completes */
        qurt_mutex_unlock(&dataMgrCxt->mutex);
        return DM_CREATE_IF_IN_PROGRESS_E;
    }

    i = DMFindFreeEntry(qsCommonCxt);
    if(-1 == i)
    {
        qurt_mutex_unlock(&dataMgrCxt->mutex);
        return DM_FAILURE_E;
    }

    dataMgrCxt->createInProgress = i;
    qurt_mutex_unlock(&dataMgrCxt->mutex);

    name_len = ((Input->NameLen > IFNAME_MAX_LENGTH) ? IFNAME_MAX_LENGTH : Input->NameLen);
    total_Len = QS_TOTAL_LEN(DM_TOTAL_LEN(DM_IFINITREQ_T_SIZE(name_len)));
    reqBuf = (char *)malloc(total_Len);
    if(!reqBuf)
    {
        return DM_FAILURE_E;
    }

    /* Create request packet with HTC, MML, data headers and the data. */
    cmd = (DmIfInitReq_t *)QSPACKET_HEADER(reqBuf);
    cmd->Header.CmdId = Input->Header.CmdId;
    cmd->Header.Reserved = 0;
    cmd->Header.IfId = 0;
    cmd->IfType = Input->IfType;
    memcpy(cmd->Mac, Input->Mac, DM_MAC_LENGTH);
    cmd->NameLen = name_len;
    memcpy(cmd->Name, Input->Name, cmd->NameLen);

    if(MML_SUCCESS_E != mmlServiceQueueSend(SqId, total_Len, reqBuf, NULL))
    {
        /* Free the buffer in case of error */
        free(reqBuf);
        return DM_FAILURE_E;
    }
    /* Note: In case of success, free the buffer only when registered callback is called. */

    /* Sent interface create request, wait for response */
     result = qurt_signal_wait_timed(&dataMgrIfCxt[i].signal, CREATE_RESP_EVENT,
             QURT_SIGNAL_ATTR_CLEAR_MASK, &signal_Set, qurt_timer_convert_time_to_ticks(RESP_TIMEOUT, QURT_TIME_MSEC));
     if(-1 == result)
    {
        return DM_FAILURE_E;
    }

    if((ssSuccess != QsDeq(&dataMgrIfCxt[i].rxQueue, (void **)&respBuf)) || !respBuf)
    {
        return DM_FAILURE_E;
    }

    respHeader = (DmHeader_t *)(respBuf);
    *Output = READ_UNALIGNED_LITTLE_ENDIAN_UINT32(&respHeader->IfId);
    ret_Val = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(DM_RESP(respBuf));

    qurt_mutex_lock(&dataMgrCxt->mutex);
    dataMgrIfCxt = &dataMgrCxt->interfaces[i];
    if(DM_SUCCESS_E == ret_Val)
    {
        dataMgrIfCxt->ifId = *Output;
        dataMgrIfCxt->type = Input->IfType;
        dataMgrIfCxt->cb = Input->Cb;
        dataMgrIfCxt->nameLen = ((Input->NameLen > IFNAME_MAX_LENGTH) ? IFNAME_MAX_LENGTH : Input->NameLen);
        memcpy(dataMgrIfCxt->name, &Input->Name[0], dataMgrIfCxt->nameLen);
    }
    else
    {
        dataMgrCxt->interfaces[i].inUse = 0;
        ret_Val = DM_FAILURE_E;
    }
    dataMgrCxt->createInProgress = -1;
    qurt_mutex_unlock(&dataMgrCxt->mutex);

    /* Call the MML API to release received buffer for both success and failure. */
    mmlReleaseBuf(SqId, respBuf);
    return ret_Val;
}


static uint32_t DMHandleResp(uint8_t SqId, int8_t Index, uint32_t RespType, void *Output)
{
    uint32_t ret_Val = DM_SUCCESS_E;
    char *rcvdResp = NULL;
    dataMgrCxt_t *dataMgrCxt = QH_DATAMGR_CXT(qsCommonCxt);
    dataIfCxt_t *dataMgrIfCxt = QH_DATAMGR_IF_CXT(qsCommonCxt);

    if((ssSuccess != QsDeq(&dataMgrIfCxt[Index].rxQueue, (void **)&rcvdResp)) || !rcvdResp)
    {
        return DM_FAILURE_E;
    }

    do
    {
        ret_Val = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(DM_RESP(rcvdResp));
        qurt_mutex_lock(&dataMgrCxt->mutex);
        dataMgrCxt->interfaces[Index].cmdInProgess = 0;
        qurt_mutex_unlock(&dataMgrCxt->mutex);

        /* Command failed. */
        if(DM_SUCCESS_E != ret_Val)
        {
            break;
        }

        /* Command succeeded */
        switch(RespType)
        {
            case DM_INTERFACE_DESTROY_RESP:
                qurt_mutex_lock(&dataMgrCxt->mutex);
                DMResetIfEntry(Index);
                qurt_mutex_unlock(&dataMgrCxt->mutex);
                break;

            case DM_INTERFACE_QUERY_PREFIX_RESP:
                { ; } /* Intentional empty statement to resolve compilation error */
                uint8_t i = 0;
                DmPrefixQueryResp_t *output = (DmPrefixQueryResp_t *)Output;
                DmPrefixInfo_t *info = NULL;
                output->Status = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(DM_RESP(rcvdResp));
                output->NumPrefix = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(&(DM_RESP(rcvdResp)[1]));
                if(output->NumPrefix)
                {
                    output->Info = (DmPrefixInfo_t *)malloc(DM_PREFIXINFO_T_SIZE * output->NumPrefix);
                    if(!output->Info)
                        break;
                    info = (DmPrefixInfo_t *)&(DM_RESP(rcvdResp)[2]);
                    for(i = 0; i < output->NumPrefix; i++)
                    {
                        output->Info[i].PrefixLength = READ_UNALIGNED_LITTLE_ENDIAN_UINT32(&info->PrefixLength);
                        memcpy(output->Info[i].Prefix.Address, info->Prefix.Address, DM_IPV6_ADDRESS_LENGTH);
                        output->Info[i].ValidLifetime = READ_UNALIGNED_LITTLE_ENDIAN_UINT32(&info->ValidLifetime);
                        output->Info[i].PreferredLifetime = READ_UNALIGNED_LITTLE_ENDIAN_UINT32(&info->PreferredLifetime);
                        output->Info[i].Flags = READ_UNALIGNED_LITTLE_ENDIAN_UINT32(&info->Flags);
                        info++; /* Next prefix info entry */
                    }
                }else{
					output->Info = NULL;
				}
                break;

			case DM_INTERFACE_PREFIX_MATCH:
			{
                DmPrefixMatchResp_t *output = (DmPrefixMatchResp_t *)Output;		
				output->Status = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(DM_RESP(rcvdResp));
                output->matchLen = READ_UNALIGNED_LITTLE_ENDIAN_UINT32(&(DM_RESP(rcvdResp)[1]));
				break;
			}

            default:
                break;
        }
    } while(0);

    /* Call the MML API to release received buffer for both success and failure. */
    mmlReleaseBuf(SqId, rcvdResp);
    return ret_Val;
}


/* This function passes data received from host to the callback function set for the interface */
static void DMHandleData(uint8_t SqId, uint16_t BufLen, char *Buf)
{
    DmHeader_t *header = NULL;
    dataMgrCxt_t* dataMgrCxt = NULL;
    DMCallback_t cb = (DMCallback_t)NULL;
    int8_t i = 0;

    do
    {
        header = (DmHeader_t *)Buf;
        dataMgrCxt = QH_DATAMGR_CXT(qsCommonCxt);

        qurt_mutex_lock(&dataMgrCxt->mutex);
        i = DMFindIfEntry(READ_UNALIGNED_LITTLE_ENDIAN_UINT32(&header->IfId));
        if(-1 == i)
        {
            qurt_mutex_unlock(&dataMgrCxt->mutex);
            break;
        }

        cb = (dataMgrCxt->interfaces[i]).cb;
        qurt_mutex_unlock(&dataMgrCxt->mutex);

        if(cb)
            cb(BufLen - DM_HEADER_LEN, DM_RESP(Buf));
    } while(0);

    /* Call the MML API to release received buffer for both success and failure. */
    mmlReleaseBuf(SqId, Buf);
    return;
}


/* Response received from host for interface init command */
static void DMHandleCreateIfResp(uint8_t SqId, uint16_t BufLen, char *Buf)
{
    int8_t i = 0;
    dataMgrCxt_t *dataMgrCxt = QH_DATAMGR_CXT(qsCommonCxt);
    dataIfCxt_t *dataMgrIfCxt = QH_DATAMGR_IF_CXT(qsCommonCxt);

    do
    {
        /* Find entry for which init is in progress */
        qurt_mutex_lock(&dataMgrCxt->mutex);
        i = dataMgrCxt->createInProgress;
        if(i < 0)
        {
            /* Create not in progress */
            qurt_mutex_unlock(&dataMgrCxt->mutex);
            break;
        }
        qurt_mutex_unlock(&dataMgrCxt->mutex);

		/* Enqueue the received packet, the command thread blocked for the response will
		 * wake up when sinal is set and it will process the packet */
        if(ssSuccess != QsEnq(&dataMgrIfCxt[i].rxQueue, (void *)Buf))
        {
            break;
        }

        /* Success */
        /* The thread waiting on dataMgrIfCxt[i].signal will release the buffer in case of success */
        qurt_signal_set(&dataMgrIfCxt[i].signal, CREATE_RESP_EVENT);
        return;
    } while(0);

    /* Call the MML API to release received buffer for both success and failure. */
    mmlReleaseBuf(SqId, Buf);
    return;
}


/* This function takes action depending on the type of data received */
void DMRcvCompleteCb(uint8_t SqId, uint16_t BufLen, char *Buf, void *ServiceCxt, void *ServiceData)
{
    DmHeader_t *dataHeader = NULL;
    dataMgrCxt_t* dataMgrCxt = NULL;
    dataIfCxt_t* dataMgrIfCxt = NULL;
    int8_t i = 0;
    uint32_t mask = 0;
    uint8_t cmdId = 0;

    dataHeader = (DmHeader_t *)Buf;
    dataMgrCxt = QH_DATAMGR_CXT(qsCommonCxt);
    dataMgrIfCxt = QH_DATAMGR_IF_CXT(qsCommonCxt);
    cmdId = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(dataHeader);

    switch(cmdId)
    {
        case DM_INTERFACE_DATA:
            DMHandleData(SqId, BufLen, Buf);
            return;

        case DM_INTERFACE_CREATE_RESP:
            DMHandleCreateIfResp(SqId, BufLen, Buf);
            return;

        case DM_INTERFACE_DESTROY_RESP:
            mask = DESTROY_RESP_EVENT;
            break;

        case DM_INTERFACE_LINK_STATE_RESP:
            mask = LINK_STATE_RESP_EVENT;
            break;

        case DM_INTERFACE_QUERY_PREFIX_RESP:
            mask = QUERY_PREFIX_RESP_EVENT;
            break;

        case DM_INTERFACE_ADD_IP:
            mask = ADD_IP_RESP_EVENT;
            break;

        case DM_INTERFACE_DEL_IP:
            mask = DEL_IP_RESP_EVENT;
            break;

        case DM_INTERFACE_ADD_ROUTE:
            mask = ADD_ROUTE_RESP_EVENT;
            break;

        case DM_INTERFACE_DEL_ROUTE:
            mask = DEL_ROUTE_RESP_EVENT;
            break;

        case DM_INTERFACE_ADD_MCAST:
            mask = ADD_MCAST_RESP_EVENT;
            break;

        case DM_INTERFACE_DEL_MCAST:
            mask = DEL_MCAST_RESP_EVENT;
            break;

		case DM_INTERFACE_PREFIX_MATCH:
			mask = DEL_PREFIX_MATCH_EVENT;
            break;

        default:
            /* Call the MML API to release received buffer for both success and failure. */
            mmlReleaseBuf(SqId, Buf);
            return;
    }

    do
    {
        /* For DM_INTERFACE_DESTROY_RESP, DM_INTERFACE_LINK_STATE_RESP
         * and DM_INTERFACE_QUERY_PREFIX_RESP */
        qurt_mutex_lock(&dataMgrCxt->mutex);
        i = DMFindIfEntry(READ_UNALIGNED_LITTLE_ENDIAN_UINT32(&dataHeader->IfId));
        if(-1 == i)
        {
            qurt_mutex_unlock(&dataMgrCxt->mutex);
            break;
        }

        qurt_mutex_unlock(&dataMgrCxt->mutex);

		/* Enqueue the received packet, the command thread blocked for the response will
		 * wake up when sinal is set and it will process the packet */
        if(ssSuccess != QsEnq(&dataMgrIfCxt[i].rxQueue, (void *)Buf))
        {
            break;
        }

        /* Success */
        /* The thread waiting on dataMgrIfCxt[i].signal will release the buffer in case of success */
        qurt_signal_set(&dataMgrIfCxt[i].signal, mask);
        return;
    } while(0);

    /* Call the MML API to release received buffer in case of failure. */
    mmlReleaseBuf(SqId, Buf);
    return;
}


/* Thread to receive command responses and data from the host */
static void DMRcvThread(void *Param)
{
    dataMgrCxt_t *dataMgrCxt = NULL;
    char *buf = NULL;
    uint32_t signalSet = 0;
    int result = -1, i = 0;
    mmlCb_t msgRcvdCb = NULL;
    void *serviceCxt = NULL;
	uint16_t bufLen = 0;

    dataMgrCxt = QH_DATAMGR_CXT(Param);
    if(!dataMgrCxt)
    {
        qurt_thread_stop();
    }
    qurt_signal_set(&dataMgrCxt->signal, QS_THREAD_READY);

    do
    {

        result = qurt_signal_wait_timed(&dataMgrCxt->signal, RX_EVENT, QURT_SIGNAL_ATTR_CLEAR_MASK,
                                        (uint32 *)&signalSet, QURT_TIME_WAIT_FOREVER);
        if(-1 == result)
        {
            break;
        }

        /* Process all packets in the 3 data queues, currently there are no priorities */
        for(i = BLE_DATA_SQ_ID; i <= THREAD_DATA_SQ_ID; i++)
        {
            while((MML_SUCCESS_E == mmlDeq(i, (void **)&buf, MML_DIR_RCV, NULL)) && buf)
            {
                (void)mmlServiceRetrieveCb(i, MML_DIR_RCV, (void *)&msgRcvdCb, &serviceCxt);
				/*Obtain length from packet header*/ 
				bufLen = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(buf);
                if(msgRcvdCb && (bufLen > QS_IOTD_HEADER_LEN))
                {
					/* Call the set callback.
					 * RCV callbacks should free the memory irrespective of success or failure.
					 * These callbacks must use mmlReleaseBuf() and not QsReleaseBuf(). */
                    msgRcvdCb(i, bufLen - QS_IOTD_HEADER_LEN, 
                              &buf[QS_IOTD_HEADER_LEN], serviceCxt, NULL);
					msgRcvdCb = NULL;
                }
                else
                {
					/* Release buffer in case RCV callback not found */
                    QsReleaseBuf(buf);
                }
                buf = NULL;
            }
        }
    } while(1);
    qurt_thread_stop();
}

void DMSendCompleteCb(uint8_t SqId, uint16_t BufLen, char *Buf, void *ServiceCxt, void *ServiceData)
{
    if(Buf)
        free(Buf);
    return;
}

/* Deinitialize data manager context. */
void DMDeInit(void *Cxt)
{
    int8_t i = 0;
    dataMgrCxt_t *dataMgrCxt = QH_DATAMGR_CXT(Cxt);
    dataIfCxt_t *dataMgrIfCxt = NULL;

    for(i = 0; i < THREAD_DATA_SQ_ID; i++)
    {
        mmlServiceDeregisterCb(i, NULL);
    }

    qurt_mutex_lock(&dataMgrCxt->mutex);
    for(i = 0; i < QS_IOTD_MAX_DATA_INTERFACE; i++)
    {
        dataMgrIfCxt = &dataMgrCxt->interfaces[i];
        qurt_signal_destroy(&dataMgrIfCxt->signal);
        QsDeInitQueue(&dataMgrIfCxt->rxQueue);
    }

    qurt_signal_destroy(&dataMgrCxt->signal);
    qurt_mutex_unlock(&dataMgrCxt->mutex);
    qurt_mutex_delete(&dataMgrCxt->mutex);
    free(dataMgrCxt);
    QH_COMMON_CXT(Cxt)->dataMgrCxt = NULL;
}

/* Initialize data manager context. */
uint32_t DMInit(void *Cxt)
{
    qurt_thread_attr_t attr;
    int32_t result = QURT_EOK;
    uint32_t signalSet = 0, retVal = DM_SUCCESS_E;
    int8_t i = 0;
    dataMgrCxt_t *dataMgrCxt = QH_DATAMGR_CXT(Cxt);
    dataIfCxt_t *dataMgrIfCxt = NULL;

    if(QH_COMMON_CXT(Cxt)->dataMgrCxt)
    {
        return DM_SUCCESS_E;
    }

    do
    {
        QH_COMMON_CXT(Cxt)->dataMgrCxt = (dataMgrCxt_t *)malloc(sizeof(dataMgrCxt_t));
        dataMgrCxt = QH_DATAMGR_CXT(Cxt);
        if(!dataMgrCxt)
        {
            retVal = DM_MEMORY_ERROR_E;
            break;
        }

        memset(dataMgrCxt, 0, sizeof(dataMgrCxt_t));
        dataMgrCxt->createInProgress = -1;
        if(QURT_EOK != qurt_mutex_create(&dataMgrCxt->mutex))
        {
            retVal = DM_FAILURE_E;
            break;
        }

        if(QURT_EOK != qurt_signal_create(&dataMgrCxt->signal))
        {
            retVal = DM_FAILURE_E;
            break;
        }

        for(i = 0; i < QS_IOTD_MAX_DATA_INTERFACE; i++)
        {
            dataMgrIfCxt = &dataMgrCxt->interfaces[i];
            memset(dataMgrIfCxt, 0, sizeof(dataIfCxt_t));
            if(ssSuccess != QsInitQueue(&dataMgrIfCxt->rxQueue))
            {
                retVal = DM_FAILURE_E;
                break;
            }

            if(QURT_EOK != qurt_signal_create(&dataMgrIfCxt->signal))
            {
                retVal = DM_FAILURE_E;
                break;
            }
        }

        /* Check if queue initializations inside for loop succeeded */
        if(DM_SUCCESS_E != retVal)
        {
            break;
        }

        for(i = BLE_DATA_SQ_ID; i <= THREAD_DATA_SQ_ID; i++)
        {
            /* Register for MML queues. Datamanager callbacks are common for BLE, WLAN and thread data service queues */
            if(MML_SUCCESS_E != mmlServiceRegisterCb(i, DMRcvCompleteCb, DMSendCompleteCb, NULL))
            {
                retVal = DM_FAILURE_E;
                break;
            }
        }

        /* Data messages between host and Quartz will be enqueued by MML to service ID specific queues.
         * Following thread is the Rx thread for data agent which will dequeue data packets from data specific queue
         * and call the callback for respective service queues. */
        qurt_thread_attr_init(&attr);
        qurt_thread_attr_set_name(&attr, "DATAMGR_RCV");
        qurt_thread_attr_set_priority(&attr, DM_PRIORITY);
        qurt_thread_attr_set_stack_size(&attr, DM_STACK_SIZE);
        result = qurt_thread_create(&dataMgrCxt->rxThread, &attr, DMRcvThread, Cxt);
        if (QURT_EOK != result)
        {
            retVal = DM_FAILURE_E;
            break;
        }

        /* Wait for the new thread to start */
        result = qurt_signal_wait_timed(&dataMgrCxt->signal, QS_THREAD_READY, QURT_SIGNAL_ATTR_CLEAR_MASK,
                &signalSet, QURT_TIME_WAIT_FOREVER);
        if(QURT_EOK != result)
        {
            retVal = DM_FAILURE_E;
            break;
        }

        return DM_SUCCESS_E;
    } while(0);

    (void)DMDeInit(Cxt);
    return DM_FAILURE_E;
}


/* This function creates and sends interface init command to the host. */
uint32_t DMSendCmd(uint8_t SqId, const void *Input, void *Output)
{
    uint32_t mask = 0, signal_Set = 0, respType = 0;
    uint16_t total_Len = 0;
    int8_t i = 0, cmdPacket = 1;
    int result = -1;
    char *cmd = NULL, *reqBuf = NULL;

    dataMgrCxt_t *dataMgrCxt = QH_DATAMGR_CXT(qsCommonCxt);
    dataIfCxt_t *dataMgrIfCxt = QH_DATAMGR_IF_CXT(qsCommonCxt);

    if(!dataMgrCxt || !dataMgrIfCxt || !Input)
    {
        return DM_FAILURE_E;
    }

    switch(DM_CMDID(Input))
    {
        case DM_INTERFACE_CREATE_REQ:
            return DMCreateIf(SqId, (DmIfInitReq_t *)Input, (uint32_t *)Output);

        case DM_INTERFACE_DESTROY_REQ:
            total_Len = QS_TOTAL_LEN(DM_IFDESTROYREQ_T_SIZE);
            mask = DESTROY_RESP_EVENT;
            respType = DM_INTERFACE_DESTROY_RESP;
            break;

        case DM_INTERFACE_LINK_STATE_REQ:
            total_Len = QS_TOTAL_LEN(DM_LINKSTATEREQ_T_SIZE);
            mask = LINK_STATE_RESP_EVENT;
            respType = DM_INTERFACE_LINK_STATE_RESP;
            break;

        case DM_INTERFACE_QUERY_PREFIX_REQ:
            total_Len = QS_TOTAL_LEN(DM_PREFIXQUERYREQ_T_SIZE);
            mask = QUERY_PREFIX_RESP_EVENT;
            respType = DM_INTERFACE_QUERY_PREFIX_RESP;
            break;

        case DM_INTERFACE_DATA:
            /* DmData_t contains payload lenth of 2 bytes, it won't be sent to host */
            total_Len = QS_TOTAL_LEN(DM_DATA_T_SIZE(Input)) - 2;
            cmdPacket = 0;
            break;

        case DM_INTERFACE_ADD_IP:
            total_Len = QS_TOTAL_LEN(sizeof(DmAddIPAddress_t));
            mask = ADD_IP_RESP_EVENT;
            respType = DM_INTERFACE_ADD_IP;
            break;

        case DM_INTERFACE_DEL_IP:
            total_Len = QS_TOTAL_LEN(sizeof(DmDelIPAddress_t));
            mask = DEL_IP_RESP_EVENT;
            respType = DM_INTERFACE_DEL_IP;
            break;

        case DM_INTERFACE_ADD_ROUTE:
            total_Len = QS_TOTAL_LEN(sizeof(DmAddRoute_t));
            mask = ADD_ROUTE_RESP_EVENT;
            respType = DM_INTERFACE_ADD_ROUTE;
            break;

        case DM_INTERFACE_DEL_ROUTE:
            total_Len = QS_TOTAL_LEN(sizeof(DmDelRoute_t));
            mask = DEL_ROUTE_RESP_EVENT;
            respType = DM_INTERFACE_DEL_ROUTE;
            break;

        case DM_INTERFACE_ADD_MCAST:
            total_Len = QS_TOTAL_LEN(sizeof(DmAddMcast_t));
            mask = ADD_MCAST_RESP_EVENT;
            respType = DM_INTERFACE_ADD_MCAST;
            break;

        case DM_INTERFACE_DEL_MCAST:
            total_Len = QS_TOTAL_LEN(sizeof(DmDelMcast_t));
            mask = DEL_MCAST_RESP_EVENT;
            respType = DM_INTERFACE_DEL_MCAST;
            break;

		case DM_INTERFACE_PREFIX_MATCH:
		    total_Len = QS_TOTAL_LEN(sizeof(DmPrefixMatch_t));
            mask = DEL_PREFIX_MATCH_EVENT;
            respType = DM_INTERFACE_PREFIX_MATCH;
            break;
        default:
            return DM_FAILURE_E;
    }

    reqBuf = (char *)malloc(total_Len);
    if(!reqBuf)
    {
        return DM_FAILURE_E;
    }

    cmd = QSPACKET_HEADER(reqBuf);
    if(DM_INTERFACE_DATA == DM_CMDID(Input))
    {
        memcpy(cmd, Input, DM_HEADER_LEN);
        memcpy(&cmd[DM_HEADER_LEN], ((DmData_t *)Input)->Payload, ((DmData_t *)Input)->Len);
    }
    else
    {
        memcpy(cmd, Input, total_Len - QS_IOTD_HEADER_LEN);
    }
    qurt_mutex_lock(&dataMgrCxt->mutex);
    i = DMFindIfEntry(((DmHeader_t *)cmd)->IfId);
    if(-1 == i)
    {
        free(reqBuf);
        qurt_mutex_unlock(&dataMgrCxt->mutex);
        return DM_FAILURE_E;
    }

    if(cmdPacket)
    {
        /* Previous command not yet completed */
        if(dataMgrCxt->interfaces[i].cmdInProgess)
        {
            free(reqBuf);
            qurt_mutex_unlock(&dataMgrCxt->mutex);
            return DM_CMD_IN_PROGRESS_E;
        }

        /* Else set cmdInProgess to 1 */
		dataMgrCxt->interfaces[i].cmdInProgess = 1;
    }
    qurt_mutex_unlock(&dataMgrCxt->mutex);

    if(MML_SUCCESS_E != mmlServiceQueueSend(SqId, total_Len, reqBuf, NULL))
    {
        /* Free the buffer in case of error */
        free(reqBuf);
        qurt_mutex_lock(&dataMgrCxt->mutex);
		dataMgrCxt->interfaces[i].cmdInProgess = 0;
        qurt_mutex_unlock(&dataMgrCxt->mutex);
        return DM_FAILURE_E;
    }
    /* Note: In case of success, free the buffer only when registered callback is called. */

    /* Return immediately for data packets as response is not expected */
    if(!cmdPacket)
    {
        /* No response for DM_INTERFACE_DATA, so return. */
        return DM_SUCCESS_E;
    }

    /* Wait for response */
    result = qurt_signal_wait_timed(&dataMgrIfCxt[i].signal, mask, QURT_SIGNAL_ATTR_CLEAR_MASK,
            &signal_Set, qurt_timer_convert_time_to_ticks(RESP_TIMEOUT, QURT_TIME_MSEC));
    if(-1 == result)
    {
        return DM_FAILURE_E;
    }

    return DMHandleResp(SqId, i, respType, Output);
}


#endif /* CONFIG_DAEMON_MODE */


