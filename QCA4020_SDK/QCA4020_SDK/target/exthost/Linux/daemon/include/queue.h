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

#ifndef QUEUE_H
#define QUEUE_H

#include <semaphore.h>
#include <pthread.h>

/* 
1.	Each Service Queue is represented by a pair of queues (TX, RX)

2.	When an interface is initialized, it will take ownership of one or more queues. Ownership means that it will receive packets on these queues only. 

3.	Any module can post to a queue, but only one module can receive on a given queue.

4.	Each queue has an “indicate” function associated with it. At init time, the interface will register a callback function with the queue (that will wake up the interface thread). Any producer posting to the queue will invoke the corresponding callback.

*/

typedef struct _node
{
    void* pBuf;
    struct _node* next;
} NODE_T;


typedef struct _queue
{
    NODE_T* head;
    NODE_T* tail;
    unsigned short count;
    sem_t* notify_sem;    /*Notify semphore is registered by the queue owner*/
    pthread_mutex_t lock;
} QUEUE_T;

void queue_init(QUEUE_T* q);

int queue_enq(QUEUE_T* q, void* buf);

void* queue_deq(QUEUE_T* q);

int32_t queue_register_sem(QUEUE_T* q, sem_t* sem);

#endif
