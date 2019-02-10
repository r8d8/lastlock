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
#include <queue.h>
#include "iotd_context.h"


void* node_alloc()
{
    NODE_T* node = malloc(sizeof(NODE_T));
    return (void*)node;
}

void node_free(NODE_T* node)
{
    if(node)
    {
        free(node);
    }
}

void queue_init(QUEUE_T* q)
{
    q->head = q->tail = NULL;
    q->count = 0;
    q->notify_sem = NULL;
    pthread_mutex_init(&q->lock, NULL);
}


int queue_enq(QUEUE_T* q, void* buf)
{

    NODE_T *temp = node_alloc();

    if(temp != NULL)
    {
        temp->pBuf = buf;
        temp->next = NULL;
    }
    else
    {
        return -1;
    }

    pthread_mutex_lock(&q->lock);

    if (q->tail == NULL)
    {
        q->tail = q->head = temp;
        pthread_mutex_unlock(&q->lock);
        return 0;
    }

    /* Add the new node at the end of queue and change tail*/
    q->tail->next = temp;
    q->tail = temp;
    pthread_mutex_unlock(&q->lock);
    return 0;
}

void* queue_deq(QUEUE_T* q)
{
    NODE_T* temp;
    void* buf;

    pthread_mutex_lock(&q->lock);
    /* If queue is empty, return NULL.*/
    if (q->head == NULL)
    {
        pthread_mutex_unlock(&q->lock);
        return NULL;
    }

    /* Store previous front and move front one node ahead*/
    temp = q->head;
    q->head = q->head->next;

    /* If front becomes NULL, then change rear also as NULL*/
    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    buf = temp->pBuf;
    node_free(temp);
    pthread_mutex_unlock(&q->lock);
    return buf;

}

int32_t queue_register_sem(QUEUE_T* q, sem_t* sem)
{

    if(q == NULL){
        return IOTD_ERROR;
    }

    if(!q->notify_sem)
    {
        q->notify_sem = sem;
        return IOTD_OK;
    }
    return IOTD_ERROR;
}

