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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>
#include <syslog.h>
#include "iotd_context.h"
#include "queue.h"
#include "htc.h"
#include "ipcManager.h"

int mml_init(void* pCxt)
{
    int i, j;
    /*initialize all Service queues*/
    MML_CXT_T* mml_cxt = GET_MML_CXT(pCxt);

    for(i = 0; i < IOTD_MAX_NUM_Q; i++)
    {
        /*There are two queues per Service ID*/
        for(j = 0; j < 2; j++)
        {
            queue_init(&(mml_cxt->sq[i][j].q));
        }
    }
    return(htc_init(pCxt));
}


int mml_deinit(void* pCxt)
{
    return(htc_deinit(pCxt));
}


int32_t mml_enqueue(void* cxt, void* buffer, uint8_t dir)
{
    MML_CXT_T* mml_cxt = GET_MML_CXT(cxt);
    QUEUE_T *q = NULL;
    uint8_t sqid = 0, qid = 0;

    if(!cxt || !buffer || !IS_Q_DIR_VALID(dir))
    {
        IOTD_LOG(LOG_TYPE_CRIT,"MML enqueue: Invalid inputs\n");
        return IOTD_ERROR;
    }

    /* Find Service QID and derive queue ID */
    sqid = *((uint8_t*)buffer + HTC_HEADER_LEN);
    qid = GET_Q_ID(sqid);
    if(qid > IOTD_MAX_NUM_Q)
    {
        IOTD_LOG(LOG_TYPE_CRIT,"MML enqueue: Invalid q id\n");
        return IOTD_ERROR;
    }

    q = &(mml_cxt->sq[qid][dir].q);
    if(!q->notify_sem)
    {
        IOTD_LOG(LOG_TYPE_CRIT,"MML queue for devId %u, sqId %u not in use\n", GET_DEV_ID(sqid), GET_SQ_ID(sqid));
        return IOTD_ERROR;
    }

    /*Enqueue to corresponding queue*/
    if(queue_enq(q, buffer) == -1)
    {
        /*Handle failure*/
        IOTD_LOG(LOG_TYPE_CRIT,"MML %s enqueue failed, Qid\n", (dir ? "Rx":"Tx"), qid);
        return IOTD_ERROR;
    }

    /*Signal handler thread*/
    sem_post(q->notify_sem);
    return IOTD_OK;
}

int mml_open_q(void* cxt, uint8_t qid, uint8_t dir, sem_t* sem)
{
    MML_CXT_T* mml_cxt = GET_MML_CXT(cxt);

    if(qid > IOTD_MAX_NUM_Q){
        IOTD_LOG(LOG_TYPE_CRIT,"MML Open: invalid q id\n");
        return IOTD_ERROR;
    }
    return queue_register_sem(&(mml_cxt->sq[qid][dir].q), sem);
}

int32_t mml_close_q(void* cxt, uint8_t qid, uint8_t dir)
{
    /*To be implemented*/
    return IOTD_OK;
}


void* mml_dequeue(void* cxt, uint8_t qid, uint8_t dir)
{
    MML_CXT_T* mml_cxt = GET_MML_CXT(cxt);

    if(!cxt || !IS_Q_DIR_VALID(dir))
    {
        IOTD_LOG(LOG_TYPE_CRIT,"MML dequeue: Invalid inputs\n");
        return NULL;
    }

    if(qid > IOTD_MAX_NUM_Q)
    {
        IOTD_LOG(LOG_TYPE_CRIT,"MML dequeue: Invalid q id %d\n",qid);
        return NULL;
    }

    return(queue_deq(&(mml_cxt->sq[qid][dir].q)));
}
