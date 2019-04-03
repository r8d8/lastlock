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

/* Thread to receive command responses and data from the host */
static void DiagRcvThread(void *Param)
{
    diagCxt_t *diagCxt = NULL;
    char *buf = NULL;
    uint32_t signalSet = 0;
    int result = -1;
    mmlCb_t msgRcvdCb = NULL;
    void *serviceCxt = NULL;

    diagCxt = QH_DIAG_CXT(Param);
    if(!diagCxt)
    {
        qurt_thread_stop();
    }

    qurt_signal_set(&diagCxt->signal, QS_THREAD_READY);
    do
    {

        result = qurt_signal_wait_timed(&diagCxt->signal, RX_EVENT, QURT_SIGNAL_ATTR_CLEAR_MASK,
                                        (uint32 *)&signalSet, QURT_TIME_WAIT_FOREVER);
        if(-1 == result)
        {
            break;
        }

        while((MML_SUCCESS_E == mmlDeq(DIAG_SQ_ID, (void **)&buf, MML_DIR_RCV, NULL)) && buf)
        {
            mmlServiceRetrieveCb(DIAG_SQ_ID, MML_DIR_RCV, (void *)&msgRcvdCb, &serviceCxt);
			if(msgRcvdCb && (QsSizeOf(buf) > QS_IOTD_HEADER_LEN))
            {
				/* Call the set callback.
				 * RCV callbacks should free the memory irrespective of success or failure.
				 * These callbacks must use mmlReleaseBuf() and not QsReleaseBuf(). */
                msgRcvdCb(DIAG_SQ_ID, QsSizeOf(buf) - QS_IOTD_HEADER_LEN, 
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
    } while(1);
    qurt_thread_stop();
}

/* Deinitialize data manager context. */
void DiagDeInit(void *Cxt)
{
    diagCxt_t *diagCxt = QH_DIAG_CXT(Cxt);
    (void)qapi_diag_tr_service_deregister(diagCxt->cxt);
    qurt_signal_destroy(&diagCxt->signal);
    free(diagCxt->cxt);
    free(diagCxt);
    QH_COMMON_CXT(Cxt)->diagCxt = NULL;
}

/* Initialize data manager context. */
uint32_t DiagInit(void *Cxt)
{
    qurt_thread_attr_t attr;
    int32_t result = QURT_EOK;
    uint32_t signalSet = 0, retVal = DIAG_SUCCESS_E;
    diagCxt_t *diagCxt = QH_DIAG_CXT(Cxt);

    if(QH_DIAG_CXT(Cxt))
    {
        return DIAG_SUCCESS_E;
    }

    do
    {
        QH_COMMON_CXT(Cxt)->diagCxt = (diagCxt_t *)malloc(sizeof(diagCxt_t));
        diagCxt = QH_DIAG_CXT(Cxt);
        if(!diagCxt)
        {
            retVal = DIAG_MEMORY_ERROR_E;
            break;
        }

        memset(diagCxt, 0, sizeof(diagCxt_t));
        /* Register the MML APIs with diag framework. */
        diagCxt->cxt = (qapi_diag_tr_service_context_t *)malloc(sizeof(qapi_diag_tr_service_context_t));
        memset(diagCxt->cxt, 0, sizeof(qapi_diag_tr_service_context_t));
        diagCxt->cxt->service_id = DIAG_SQ_ID;
        diagCxt->cxt->diag_tr_register = (qapi_diag_tr_service_register_fn_type)mmlServiceRegisterCb;
        diagCxt->cxt->diag_tr_deregister = (qapi_diag_tr_service_deregister_fn_type)mmlServiceDeregisterCb;
        diagCxt->cxt->diag_tr_tx = (qapi_diag_tr_service_tx_fn_type)mmlServiceQueueSend;
        diagCxt->cxt->diag_tr_rx_buf_free = (qapi_diag_tr_service_rx_buf_free_fn_type)mmlReleaseBuf;
        if(true != qapi_diag_tr_service_register(diagCxt->cxt))
        {
            retVal = DIAG_FAILURE_E;
            break;
        }

        if(QURT_EOK != qurt_signal_create(&diagCxt->signal))
        {
            retVal = DIAG_FAILURE_E;
            break;
        }

        /* Diag messages between host and Quartz will be enqueued by MML to service ID DIAG_SQ_ID.
         * Following thread is the Rx thread for data agent which will process these incoming packets. */
        qurt_thread_attr_init(&attr);
        qurt_thread_attr_set_name(&attr, "DIAG_RCV");
        qurt_thread_attr_set_priority(&attr, DIAG_PRIORITY);
        qurt_thread_attr_set_stack_size(&attr, DIAG_STACK_SIZE);
        result = qurt_thread_create(&diagCxt->rxThread, &attr, DiagRcvThread, Cxt);
        if (QURT_EOK != result)
        {
            retVal = DIAG_FAILURE_E;
            break;
        }

        /* Wait for the new thread to start */
        result = qurt_signal_wait_timed(&diagCxt->signal, QS_THREAD_READY, QURT_SIGNAL_ATTR_CLEAR_MASK,
                &signalSet, QURT_TIME_WAIT_FOREVER);
        if(QURT_EOK != result)
        {
            retVal = DIAG_FAILURE_E;
            break;
        }

        return DIAG_SUCCESS_E;
    } while(0);

    (void)DiagDeInit(Cxt);
    return retVal;
}

#endif /* CONFIG_DAEMON_MODE */


