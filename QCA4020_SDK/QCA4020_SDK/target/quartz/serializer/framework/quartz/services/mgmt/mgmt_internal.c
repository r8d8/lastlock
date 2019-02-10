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
#include "qurt_error.h"
#include "qapi_firmware_upgrade_ext.h"

#ifdef CONFIG_DAEMON_MODE

static void Mgmt_Timer_Start(mgmtCxt_t *mgmtCxt, uint32_t TimerExpirationMS)
{
   qurt_time_t       TimerTickExpiration;
   qurt_timer_attr_t TimerAttributes;

   /* Convert the timer expiration in ms to Ticks.  Add one tick to     */
   /* ensure the timer doesn't expire early.                            */
   TimerTickExpiration = qurt_timer_convert_time_to_ticks(TimerExpirationMS, QURT_TIME_MSEC) + 1;

   /* Configure the timer attributes.                             */
   qurt_timer_attr_init(&TimerAttributes);
   qurt_timer_attr_set_duration(&TimerAttributes, TimerTickExpiration);
   qurt_timer_attr_set_signal(&TimerAttributes, &mgmtCxt->signal, MGMT_TIMER_EVENT);   
   qurt_timer_attr_set_reload(&TimerAttributes, TimerTickExpiration);
   qurt_timer_attr_set_option(&TimerAttributes, (QURT_TIMER_PERIODIC | QURT_TIMER_AUTO_START));

   qurt_timer_create(&(mgmtCxt->timer), &TimerAttributes);
   mgmtCxt->timer_start = 1;
}

static void Mgmt_Timer_Stop(mgmtCxt_t *mgmtCxt)
{
    /* Stop the timer.          */
    if( mgmtCxt->timer_start == 1) {
        qurt_timer_delete(mgmtCxt->timer);
        mgmtCxt->timer_start = 0;
    }
}

/*
 *  MGMT response packet format:
 *       response code:     1 Byte
 *       response status:   1 Byte
 *       response data .....
 */
uint32_t MgmtSendResp(uint8 resp, uint8 status, uint8_t* result, uint16_t result_size)
{
    int pkt_size;
    char *respBuf = NULL, *ptr_buf = NULL;

    pkt_size = QS_IOTD_HEADER_LEN + sizeof(resp) + sizeof(status) + result_size;
    respBuf = (char *)malloc(pkt_size);
    if(!respBuf)
    {
        return ssFailure;
    }

    /* HTC Header */
    WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16((uint16_t *)respBuf, pkt_size);

    /* MML Heater */
    WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8((respBuf + QS_HTC_HEADER_LEN), MGMT_SQ_ID);

    ptr_buf = respBuf + QS_IOTD_HEADER_LEN;
    /* fill packet */
    WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8( ptr_buf, resp);   /* set resp */
    WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8( ptr_buf + sizeof(resp) , status);   /* set status */
    if( result_size > 0 )
        memcpy(ptr_buf + sizeof(resp) + sizeof(status), result, result_size);

    if(MML_SUCCESS_E != mmlServiceQueueSend(MGMT_SQ_ID, pkt_size, respBuf, NULL))
    {
        /* Free the buffer in case of error */
        free(respBuf);
        return ssFailure;
    }
    /* Note: In case of success, free the buffer only when registered callback is called. */

    return ssSuccess;
}

static void MgmtProcessCmd(uint8_t sqId, uint16_t bufLen, char *cmdBuf, void *serviceCxt, void *serviceData)
{
    mgmtCxt_t *mgmtCxt = QH_MGMT_CXT(qsCommonCxt);
    qapi_Exhost_Devcfg_t *devcfgCxt; 
    qapi_FW_Ver_t ver;
    uint8_t respType = 0;

    if(!cmdBuf)
    {
        return;
    }

    respType = *(uint8_t *)cmdBuf;
    switch(respType)
    {
        case MGMT_MSG_HELLO:
            /* send hello resp */
            qapi_Get_FW_Ver(&ver);
            MgmtSendResp(respType, MGMT_RESP_OK, (uint8_t*) &ver, sizeof(ver));
            devcfgCxt = QH_DEVCFG_CXT(qsCommonCxt);
            if(    (devcfgCxt != NULL) 
                && (devcfgCxt->heart_beat_enable != 0) 
                && (mgmtCxt->timer_start == 0) )
            {
                /* start heart beat timer */
                Mgmt_Timer_Start(mgmtCxt, devcfgCxt->heart_beat_interval);
            }

            /* send signal to indicate receive hello */
            qurt_signal_set(&mgmtCxt->signal, QS_THREAD_READY);
            break;
            
        case MGMT_MSG_RESET:
            MgmtSendResp(respType, MGMT_RESP_OK, NULL, 0);
            qapi_Fw_Upgrade_Reboot_System();
            //system reboot here .........
            //never back ........
            break;

        case MGMT_MSG_GET_STATUS:
            MgmtSendResp(respType, MGMT_RESP_OK, &(mgmtCxt->status), 1);
            break;

        case MGMT_MSG_GET_VERSION:
            qapi_Get_FW_Ver(&ver);
            MgmtSendResp(respType, MGMT_RESP_OK, (uint8_t*) &ver, sizeof(ver));
            break;

        case MGMT_MSG_ECHO:
            if( cmdBuf[1] == MGMT_TEST_ECHO_MODE_LOOPBACK )
                MgmtSendResp(respType, MGMT_RESP_OK, (uint8_t*) cmdBuf+1, bufLen-1);
            else if( cmdBuf[1] == MGMT_TEST_ECHO_MODE_SENDONLY ) {
                //just drop the packet
                //no action need
            }
                
            break;

        default:
            MgmtSendResp(respType, MGMT_RESP_UNKNOWN, NULL, 0);
            break;
    }
    /* Call the MML API to release received buffer for both success and failure. */
    mmlReleaseBuf(sqId, cmdBuf);
    return;
}

static void MgmtThread(void *param)
{
    mgmtCxt_t *mgmtCxt = NULL;
    char *buf = NULL;
    uint32_t signalSet = 0;
    int result = -1;
    mmlCb_t msgRcvdCb = NULL;
    void *serviceCxt = NULL;

    mgmtCxt = QH_MGMT_CXT(param);
    if(!mgmtCxt)
    {
        qurt_thread_stop();
    }

    mmlServiceRetrieveCb(MGMT_SQ_ID, MML_DIR_RCV, (void *)&msgRcvdCb, &serviceCxt);
    if(!msgRcvdCb)
    {
        qurt_thread_stop();
    }

    do
    {
        signalSet = 0;
        result = qurt_signal_wait_timed(&mgmtCxt->signal, RX_EVENT|MGMT_TIMER_EVENT|QS_THREAD_READY, QURT_SIGNAL_ATTR_WAIT_ANY,
                (uint32 *)&signalSet, QURT_TIME_WAIT_FOREVER);
        if(-1 == result)
        {
            break;
        }
        
        if( signalSet & MGMT_TIMER_EVENT) 
        {
            qurt_signal_clear(&mgmtCxt->signal, MGMT_TIMER_EVENT);
            MgmtSendResp(MGMT_MSG_HEART_BEAT, MGMT_RESP_OK, NULL, 0);
        }
        
        if( signalSet & RX_EVENT)
        {
            qurt_signal_clear(&mgmtCxt->signal, RX_EVENT);
            /* Process all packets in the queue */
            while((MML_SUCCESS_E == mmlDeq(MGMT_SQ_ID, (void **)&buf, MML_DIR_RCV, NULL)) && buf)
            {
                if(msgRcvdCb && (QsSizeOf(buf) > QS_IOTD_HEADER_LEN))
                {
					/* Call the set callback.
					 * RCV callbacks should free the memory irrespective of success or failure.
					 * These callbacks must use mmlReleaseBuf() and not QsReleaseBuf(). */
                    msgRcvdCb(MGMT_SQ_ID, QsSizeOf(buf) - QS_IOTD_HEADER_LEN, 
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

        if( signalSet & QS_THREAD_READY) 
        {
            /* clear signal mask */
            qurt_signal_clear(&mgmtCxt->signal, QS_THREAD_READY);
        }
         
    } while(1);
    qurt_thread_stop();
}

void MgmtDeInit(void *cxt)
{
    mgmtCxt_t *mgmtCxt = QH_MGMT_CXT(cxt);

    Mgmt_Timer_Stop(mgmtCxt);
    qurt_signal_destroy(&mgmtCxt->signal);
    mmlServiceDeregisterCb(MGMT_SQ_ID, NULL);
    free(mgmtCxt);
    return;
}

void MgmtSendCompleteCb(uint8_t SqId, uint16_t BufLen, char *Buf, void *ServiceCxt, void *ServiceData)
{
    if(Buf)
        free(Buf);
    return;
}

uint32_t MgmtInit(void *cxt)
{
    qurt_thread_attr_t attr;
    int32_t result = QURT_EOK;
    uint32_t signalSet = 0;
    mgmtCxt_t *mgmtCxt;

    if(QH_COMMON_CXT(cxt)->mgmtCxt)
    {
        return ssSuccess;
    }

    QH_COMMON_CXT(cxt)->mgmtCxt = (mgmtCxt_t *)malloc(sizeof(mgmtCxt_t));
    mgmtCxt = QH_MGMT_CXT(cxt);
    if(!mgmtCxt)
    {
        return ssSuccess;
    }

    /* init mgmt context */
    memset(mgmtCxt, 0, sizeof(mgmtCxt_t));

    if(QURT_EOK != qurt_signal_create(&mgmtCxt->signal))
    {
        return ssFailure;
    }

    /* Register for MML queue. */
    if(MML_SUCCESS_E != mmlServiceRegisterCb(MGMT_SQ_ID, MgmtProcessCmd, MgmtSendCompleteCb, NULL))
    {
        return ssFailure;
    }

    /* Data messages between host and Quartz will be enqueued by MML to service ID specific queues.
     * Following thread is the Rx thread for data agent which will dequeue data packets from data specific queue
     * and pass to respective modules. */
    qurt_thread_attr_init(&attr);
    qurt_thread_attr_set_name(&attr, "MGMT_THREAD");
    qurt_thread_attr_set_priority(&attr, MGMT_PRIORITY);
    qurt_thread_attr_set_stack_size(&attr, MGMT_STACK_SIZE);
    result = qurt_thread_create(&mgmtCxt->thread, &attr, MgmtThread, cxt);
    if (QURT_EOK != result)
    {
        MgmtDeInit(cxt);
        return ssFailure;
    }

    /* Wait for the new thread to start */
    result = qurt_signal_wait_timed(&mgmtCxt->signal, QS_THREAD_READY, QURT_SIGNAL_ATTR_CLEAR_MASK,
            &signalSet, QURT_TIME_WAIT_FOREVER);
    if(QURT_EOK != result)
    {
        return ssFailure;
    }

    return ssSuccess;
}

#endif /* CONFIG_DAEMON_MODE */


