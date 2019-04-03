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
#include "common_cxt.h"
#include "qurt_error.h"

#ifdef CONFIG_DAEMON_MODE

/* Processing entry point for received data.
 * Data is put in different queues depending on the service queue ID.
 * For QAPIs, queue 0 should be used in future, currently there are separate queues for each module. */
uint32_t mmlEnq(void *Buf, uint32_t Dir)
{
    queue_t *q = NULL;
    qurt_signal_t *event = NULL;
    uint32_t mask = 0, retVal = MML_SUCCESS_E;
    uint8_t sqId = 0;
	char *data = (char *)Buf;

    if(Dir == MML_DIR_SEND) {
        q = QH_MML_SERVICE_TXCOMPLETEQUEUE(qsCommonCxt);
        mask = TX_COMPLETE_EVENT;
        event = &qsCommonCxt->mmlCxt->event;

    } else if(Dir == MML_DIR_RCV) {
        sqId = GET_Q_ID(READ_UNALIGNED_LITTLE_ENDIAN_UINT8(&data[QS_HTC_HEADER_LEN]));
        q = QH_MML_SERVICE_RXQUEUE(qsCommonCxt, sqId);
        mask = RX_EVENT;

        switch(sqId)
        {
#ifdef CONFIG_TARGET_QAPI
            case QAPI_SQ_ID:
                /* QAPI packets from host have different handling from other cases */
                return QsEnqQapi(data);
#endif

#ifdef CONFIG_TARGET_DATAMGR
            case BLE_DATA_SQ_ID:
                /* Intentional fall through */
            case WLAN_DATA_SQ_ID:
                /* Intentional fall through */
            case THREAD_DATA_SQ_ID:
                /* Intentional fall through */
                event = QH_DATAMGR_SIGNAL(qsCommonCxt);
                break;
#endif

#ifdef CONFIG_TARGET_IOTDMGR
            case MGMT_SQ_ID:
                event = QH_MGMT_SIGNAL(qsCommonCxt);
                break;
#endif

#ifdef CONFIG_TARGET_DIAGMGR
            case DIAG_SQ_ID:
                event = QH_DIAG_SIGNAL(qsCommonCxt);
                break;
#endif

            default:
                return MML_FAILURE_E;
        }
    } else {
        return MML_FAILURE_E;
    }

    if(!q || !event)
    {
        return MML_FAILURE_E;
    }

    retVal = QsEnq(q, Buf);
    if(ssSuccess != retVal)
    {
        return MML_FAILURE_E;
    }

    qurt_signal_set(event, mask);
    return MML_SUCCESS_E;
}


/* Data is put in different queues depending on the service queue ID, dequeue packets as per
 * given service queue.
 * For QAPIs, queue 0 should be used in future, currently there are separate queues for each module. */
uint32_t mmlDeq(uint8_t SqId, void **BufPtr, uint32_t Dir, uint8_t *Arg)
{
    queue_t *q = NULL;

    if(!BufPtr)
    {
        return MML_FAILURE_E;
    }

    switch(SqId)
    {
#ifdef CONFIG_TARGET_QAPI
        case QAPI_SQ_ID:
            /* QAPI packets from host have different handling from other cases */
            if(Dir == MML_DIR_RCV)
            {
                return QsDeqQapi(*Arg, BufPtr);
            }
            break;
#endif

#ifdef CONFIG_TARGET_DATAMGR
        case BLE_DATA_SQ_ID:
            /* Intentional fall through */
        case WLAN_DATA_SQ_ID:
            /* Intentional fall through */
        case THREAD_DATA_SQ_ID:
            break;
#endif

#ifdef CONFIG_TARGET_IOTDMGR
        case MGMT_SQ_ID:
            break;
#endif

#ifdef CONFIG_TARGET_DIAGMGR
        case DIAG_SQ_ID:
            break;
#endif

        default:
            *BufPtr = NULL;
            return MML_FAILURE_E;
    }

    if(Dir == MML_DIR_RCV)
    {
        q = QH_MML_SERVICE_RXQUEUE(qsCommonCxt, SqId);
    }
    else if(Dir == MML_DIR_SEND)
    {
        q = QH_MML_SERVICE_TXCOMPLETEQUEUE(qsCommonCxt);
    }
    return QsDeq(q, (void **)BufPtr);
}


uint32_t mmlServiceRetrieveCb(uint8_t SqId, uint8_t direction, void *cb, void **serviceCxt)
{
    serviceQueue_t *serviceInfo = QH_MML_SERVICE_INFO(qsCommonCxt, SqId);
    if(serviceInfo && cb && serviceCxt)
    {
        switch(direction)
        {
            case MML_DIR_SEND:
                *(mmlCb_t *)cb = serviceInfo->msgSentCb;
                break;

            case MML_DIR_RCV:
                *(mmlCb_t *)cb = serviceInfo->msgRcvdCb;
                break;

            default:
                *(mmlCb_t *)cb = (mmlCb_t)NULL;
                return MML_FAILURE_E;
                
        }

        *serviceCxt = serviceInfo->serviceCxt;
        return MML_SUCCESS_E;
    }
    return MML_FAILURE_E;
}


/* This thread waits for TX_COMPLETE_EVENTs and calls service specified callback for each packet */
void mmlTxCompleteThread(void *cxt)
{
    uint32_t signal_Set = 0;
    int32_t result = 0;
    uint8_t q_id = 0, index = 0;
    char *buf = NULL;
    mmlCb_t msgSentCb;
    void *serviceCxt = NULL;
	uint16_t bufLen = 0;

    while(1)
    {
        result = qurt_signal_wait_timed(&qsCommonCxt->mmlCxt->event, TX_COMPLETE_EVENT, QURT_SIGNAL_ATTR_CLEAR_MASK,
                (uint32 *)&signal_Set, QURT_TIME_WAIT_FOREVER);
        if(result != QURT_EOK)
        {
            /* This case will be TRUE when qurt_signal_destroy() is called. */
            break;
        }

        for(index = 0; index < NUM_SQ_ID; index++)
        {
            /* Dequeue packet from UART queue. */
            while((MML_SUCCESS_E == mmlDeq(index, (void **)&buf, MML_DIR_SEND, NULL)) && buf)
            {
                q_id = GET_Q_ID(READ_UNALIGNED_LITTLE_ENDIAN_UINT8(&buf[QS_HTC_HEADER_LEN]));
                if((MML_SUCCESS_E == mmlServiceRetrieveCb(q_id, MML_DIR_SEND, \
                                                          (void *)&msgSentCb, &serviceCxt)) \
                                                          && msgSentCb)
                {
                    bufLen = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(buf);
                    msgSentCb(q_id, bufLen, buf, serviceCxt, NULL);
                }

                buf = NULL;
                msgSentCb = NULL;
            }
        }
    }
    qurt_thread_stop();
}


uint32_t mmlDeInit(void *cxt)
{
    int i = 0;
    qsCommonCxt_t *commonCxt = QH_COMMON_CXT(cxt);

    if(!QH_MML_CXT(commonCxt))
    {
        return MML_FAILURE_E;
    }

    QsDeInitQueue(QH_MML_SERVICE_TXCOMPLETEQUEUE(cxt));
    qurt_signal_delete(&qsCommonCxt->mmlCxt->event);

    for(i = 0; i < NUM_SQ_ID; i++)
    {
        QsDeInitQueue(QH_MML_SERVICE_RXQUEUE(commonCxt, i));
        memset(commonCxt->mmlCxt->sq[i], 0, sizeof(serviceQueue_t));
        free(commonCxt->mmlCxt->sq[i]);
        commonCxt->mmlCxt->sq[i] = NULL;
    }

    free(commonCxt->mmlCxt);
    commonCxt->mmlCxt = NULL;
    return MML_SUCCESS_E;
}

uint32_t mmlInit(void *cxt)
{
    int i = 0, result = -1;
    qurt_thread_attr_t attr;
    qsCommonCxt_t *commonCxt = QH_COMMON_CXT(cxt);
    uint32_t retVal = MML_SUCCESS_E;

    if(QH_MML_CXT(commonCxt))
    {
        return MML_SUCCESS_E;
    }

    do
    {
        commonCxt->mmlCxt = (mmlCxt_t *)malloc(sizeof(mmlCxt_t));
        if(!commonCxt->mmlCxt)
        {
            return MML_MEMORY_FAILURE_E;
        }
        memset(commonCxt->mmlCxt, 0, sizeof(mmlCxt_t));

        /* Initialize service queues.
         * Each service ID has 2 queues associated, one for Tx and one for Rx */
        for(i = 0; i < NUM_SQ_ID; i++)
        {
            commonCxt->mmlCxt->sq[i] = (serviceQueue_t *)malloc(sizeof(serviceQueue_t));
            if(!commonCxt->mmlCxt->sq[i])
            {
                retVal = MML_MEMORY_FAILURE_E;
                break;
            }

            memset(commonCxt->mmlCxt->sq[i], 0, sizeof(serviceQueue_t));
            retVal = QsInitQueue(QH_MML_SERVICE_RXQUEUE(commonCxt, i));
        }

        if(MML_SUCCESS_E != retVal)
        {
            break;
        }

        if(QURT_EOK != qurt_signal_create(&QH_MML_CXT(commonCxt)->event))
        {
            return ssFailure;
        }

        if(QURT_EOK != QsInitQueue(&commonCxt->mmlCxt->txCompleteQueue))
        {
            return ssFailure;
        }

        /* Start a thread waiting for Tx complete events. */
        qurt_thread_attr_init(&attr);
        qurt_thread_attr_set_name(&attr, "MMLSendComplete");
        qurt_thread_attr_set_priority(&attr, MML_THREAD_PRIORITY);
        qurt_thread_attr_set_stack_size(&attr, MML_STACK_SIZE);
        result = qurt_thread_create(&QH_MML_CXT(commonCxt)->txCompleteThread, &attr, mmlTxCompleteThread, cxt);
        if (QURT_EOK != result)
        {
            retVal = MML_FAILURE_E;
            break;
        }

        return MML_SUCCESS_E;
    } while(0);

    /* Error */
    mmlDeInit(cxt);
    return MML_FAILURE_E;
}

#endif /* CONFIG_DAEMON_MODE */

