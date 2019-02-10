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
#ifndef __TARGET_COMMMON_H__
#define __TARGET_COMMMON_H__

#include <stdint.h>

#include "qsCommon.h"
#include "qurt_mutex.h"
#include "qurt_signal.h"
#include "qurt_thread.h"

/* Events for Tx and Rx */
#define RX_EVENT           0x02
#define TX_EVENT           0x04
#define TX_COMPLETE_EVENT  0x08

/* Buffer pool */
#define QS_BUFPOOL_WAIT_TIME  (5) /*Time in ticks to suspend when buf pools are empty*/

/* Multiple buffer lists of with buffer sizes 64, 128, 256, 512, 1024 and 2048 bytes will be allocated during
 * initialization. Depending on the required size, appropriate buffer will be given to the applications */
#define BUF_NUM_LISTS      6

#define BUF_SIZE_64        64
#define BUF_NUM_64         16
#define BUF_INDEX_64       0

#define BUF_SIZE_128       128
#define BUF_NUM_128        48
#define BUF_INDEX_128      1

#define BUF_SIZE_256       256
#define BUF_NUM_256        4
#define BUF_INDEX_256      2

#define BUF_SIZE_512       512
#define BUF_NUM_512        2
#define BUF_INDEX_512      3

#define BUF_SIZE_1024      1024
#define BUF_NUM_1024       2
#define BUF_INDEX_1024     4

#define BUF_SIZE_2048      2048
#define BUF_NUM_2048       3
#define BUF_INDEX_2048     5

#define RX_BUF_MIN_THRESHOLD     2
#define RESP_BUF_MIN_THRESHOLD   8

#define BUF_TYPE_ASYNC  (0)
#define BUF_TYPE_RESP   (1)
#define BUF_TYPE_RX     (2)

/* Structure to for a queue. Enqueue and dequeue APIs use 'mutex' for atoic operations */
typedef struct queue_s {
    void         *head; /* queue head */
    void         *tail; /* queue tail */
    qurt_mutex_t mutex; /* Mutex for atomic operations on the queue */
} queue_t;

/* This structure defines buffers used for resquests and responses */
typedef struct bufInfo_s {
    char *buf;              /* Character buffer */
    struct bufInfo_s* next; /* Next buffer in the list */
} bufInfo_t;

/* Linked list of buffers */
typedef struct bufPool_s {
    qurt_mutex_t mutex;  /* Mutex to ensure atomic operations on the count */
    uint16_t threshold;  /* Maximum buffers in a given buffer pool */
    volatile uint16_t count;      /* Number of available free buffers */
    queue_t queue;       /* Queue of free buffers */
} bufPool_t;


/*
 * Initialize target for hosted mode.
 *
 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsInit();


/*
 * Deinitialize target for hosted mode.
 *
 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsDeInit();


/*
 * Initialize given queue serializer feature.
 *
 * @param       Q                 Pointer to the queue to be initialized.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsInitQueue(queue_t *Q);


/*
 * Delete all entries from given queue.
 *
 * @param       Q                 Pointer to the queue to be freed.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsFreeQueue(queue_t *Q);


/*
 * Deinitialize given queue serializer feature.
 * This functions first frees the items in the queue and then deletes the queue.
 *
 * @param       Q                 Pointer to the queue to be deinitialized.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsDeInitQueue(queue_t *Q);


/*
 * Enqueue buffer in the given queue.
 *
 * @param       Q                 Pointer to the queue.
 * @param       Buf               Object to be enqueued.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsEnq(queue_t *Q, void *Buf);


/*
 * Dequeue reqeust from given queue.
 *
 * @param       Q                 Pointer to the queue.
 * @param       BufPtr            Pointer to retrieve the dequeued buffer.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsDeq(queue_t *Q, void **BufPtr);


/*
 * Get a character buffer from the pre-allocated buffer pool.
 *
 * @param       BufPtr           Pointer to retrieve buffer.
 * @param       Size             Required buffer size.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsGetBuf(char **BufPtr, uint16_t Size, uint8_t type);


/*
 * Release a character buffer.
 *
 * @param       BufPtr           Buffer to be freed.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsReleaseBuf(char *BufPtr);

/*
 * Get size of the passed buffer.
 * This will be used by only the internal code and only for the buffers
 * returned by QsGetBuf().
 *
 * @param       Buf           Buffer whose size is required.

 * @return      Size of the passed buffer, 0 in case error.
 */
uint16_t QsSizeOf(char *Buf);

#endif /* __TARGET_COMMMON_H__ */
#endif /* CONFIG_DAEMON_MODE */
