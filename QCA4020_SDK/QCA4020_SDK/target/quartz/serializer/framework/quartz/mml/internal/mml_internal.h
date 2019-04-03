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

#ifndef __TARGET_MML_INTERNAL_H__
#define __TARGET_MML_INTERNAL_H__

#include "common.h"
#include "mml_api.h"

#define GET_Q_ID(sqid)        ((sqid) & 0x0F)
#define MML_THREAD_PRIORITY   10
#define MML_STACK_SIZE        1024


/* Directions */
typedef enum
{
    MML_DIR_SEND, /* Packets going from Quartz to host */
    MML_DIR_RCV, /* Packets coming from host to Quartz */
} MMLQueueDir_t;


/* Structure used for each service queue */
typedef struct serviceQueue_s {
    queue_t rxQueue;   /* Queues in Tx and Rx direction. */
    mmlCb_t msgRcvdCb; /* Callback to be invoked when a packet is received from external host */
    mmlCb_t msgSentCb; /* Callback to be invoked when a packet is sent to an external host */
    void *serviceCxt;  /* Service specific context to be returned in callbacks */
} serviceQueue_t;

/* Message management layer context */
typedef struct mmlCxt_s {
    serviceQueue_t *sq[MML_NUM_SQ_ID]; /* Service queuees */
    qurt_signal_t event;              /* Signal for synchronization between MML and data agent */
    qurt_thread_t txCompleteThread;   /* Thread to call callback functions on send complete */
    queue_t txCompleteQueue;          /* Queues for Tx complete packets. */
} mmlCxt_t;


/*
 * Initialize message management layer context.
 *
 * @param       Cxt       Pointers to the common context.
 *
 * @return      0 for success, non-zero for failure.
 */
uint32_t mmlInit(void *Cxt);


/*
 * Deinitialize message management layer context.
 *
 * @param       Cxt       Pointers to the common context.
 *
 * @return      0 for success, non-zero for failure.
 */
uint32_t mmlDeInit(void *Cxt);


/*
 * Enqueue buffer in the given queue.
 *
 * @param       Buf               Object to be enqueued.
 * @param       Dir               Queue direction - MML_DIR_SEND or MML_DIR_RCV.
 *
 * @return      0 for success, non-zero for failure.
 */
uint32_t mmlEnq(void *Buf, uint32_t Dir);


/*
 * Dequeue reqeust from given queue.
 *
 * @param       SqId              Service ID.
 * @param       BufPtr            Pointer to retrieve dequeued buffer.
 * @param       Dir               Queue direction - MML_DIRECTION_SEND or MML_DIR_RCV.
 * @param       Arg               Used only for QsDeqQapi() as it needs ModuleID, set to NULL otherwise.
 *
 * @return      0 for success, non-zero for failure.
 */
uint32_t mmlDeq(uint8_t SqId, void **BufPtr, uint32_t Dir, uint8_t *Arg);

/*
 * (Internal use) This API is used to retrive set callbacks.
 *
 * @param       SqId              Service ID.
 * @param       direction         MML_DIR_SEND:Quartz to host, MML_DIR_RCV:Host to Quartz
 * @param       cb                Pointer to receive callback function
 * @param       appCxt            Application context.
 *
 * @return      0 for success, non-zero for failure.
 */
uint32_t mmlServiceRetrieveCb(uint8_t SqId, uint8_t direction, void *cb, void **appCxt);


#endif /* __TARGET_MML_INTERNAL_H__ */
#endif /* CONFIG_DAEMON_MODE */

