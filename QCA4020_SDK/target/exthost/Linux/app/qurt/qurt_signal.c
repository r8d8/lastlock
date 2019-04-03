/*
 * Copyright (c) 2015-2018 Qualcomm Technologies, Inc.
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
#include <string.h>
#include <semaphore.h>
#include "qurt_signal.h"

/* This part is taken from Tarik's implementation */
typedef struct
{
    sem_t *mutex;
    sem_t *cond_var;
} qol_sem_ptr;


void qurt_signal_init(qurt_signal_t *signal)
{
#ifdef QOL_DEBUG
    printf("qurt_signal_init called\n");
#endif

    qol_sem_ptr *sem_obj_ptrs = NULL;

    signal->signals = 0; /* 32 signal bits */
    signal->waiting = 0; /* Mask of signals to wait for */
    signal->attribute = 0; /* QURT_SIGNAL_ATTR_WAIT_ANY or QURT_SIGNAL_ATTR_WAIT_ALL */

    /* The queue element is used to store a pointer to a structure which holds pointers to two semaphore objects */
    /* Create pointer data structure */
    sem_obj_ptrs = (qol_sem_ptr *)malloc(sizeof(qol_sem_ptr));
    memset(sem_obj_ptrs, 0, sizeof(qol_sem_ptr));

    /* Create semaphore object which will be used as mutex during set operations */
    sem_obj_ptrs->mutex = (sem_t *)malloc(sizeof(sem_t));
    memset(sem_obj_ptrs->mutex, 0, sizeof(sem_t));
    sem_init(sem_obj_ptrs->mutex, 0, 1);

    /* Create semaphore object 1 - used to suspend waiting thread */
    sem_obj_ptrs->cond_var = (sem_t *)malloc(sizeof(sem_t));
    memset(sem_obj_ptrs->cond_var, 0, sizeof(sem_t));

    /* Initialize semaphore
     * First 0 indicates it will not be shared with forked processes
     * Second 0 sets the initial value */
    sem_init(sem_obj_ptrs->cond_var, 0, 0);

    signal->queue = (uint32)sem_obj_ptrs;
    return;
}


void qurt_signal_destroy(qurt_signal_t *signal)
{
#ifdef QOL_DEBUG
    printf("qurt_signal_destroy called\n");
#endif

    qol_sem_ptr *sem_obj_ptrs = NULL;

    /* Extract pointer to qol_sem_ptr structure */
    sem_obj_ptrs = (qol_sem_ptr *)signal->queue;

    /* Free two semaphore objects */
    free(sem_obj_ptrs->cond_var);
    free(sem_obj_ptrs->mutex);

    /* Free main pointer structure */
    free(sem_obj_ptrs);

    return;
}

int qurt_signal_wait_timed(qurt_signal_t *signal, uint32 mask,
        uint32 attribute, uint32 *curr_signals, qurt_time_t timeout)
{
#ifdef QOL_DEBUG
    printf("qurt_signal_wait called\n");
#endif

    qol_sem_ptr *sem_obj_ptrs = NULL;
    int signals_present = 0;
    uint32 tmp_signals = 0;

    /* Extract pointer to qol_sem_ptr structure */
    sem_obj_ptrs = (qol_sem_ptr *)signal->queue;

    /* Protect access to signal object with mutex */
    sem_wait(sem_obj_ptrs->mutex);

    signal->waiting = mask;
    signal->attribute = attribute;

    if(attribute == QURT_SIGNAL_ATTR_WAIT_ANY)
    {
        signals_present = signal->signals & mask;
    }

    if (attribute == QURT_SIGNAL_ATTR_WAIT_ALL)
    {
        signals_present = (signal->signals & mask) == mask;
    }

    sem_post(sem_obj_ptrs->mutex);

    /* If required signals are not present yet, suspend thread, using semaphore 1 */
    /* Otherwise, reset semaphore if skipping sem_wait() */
    if (signals_present == 0)
    {
        sem_wait(sem_obj_ptrs->cond_var);   /* suspend */
    }
    else
    {
        sem_trywait(sem_obj_ptrs->cond_var);    /* reset semaphore */
    }

    /* Return current signals */
    /* Protect signal object access */
    sem_wait(sem_obj_ptrs->mutex);
    tmp_signals = signal->signals;
    sem_post(sem_obj_ptrs->mutex);

    return tmp_signals;
}

uint32 qurt_signal_wait(qurt_signal_t *signal, uint32 mask, uint32 attribute)
{
    uint32 set_signal = 0;
    /* signal wait is not supported from ISR */
    ASSERT(0 == qurt_system_get_ipsr());
    qurt_signal_wait_timed(signal, mask, attribute, &set_signal, QURT_TIME_WAIT_FOREVER);
    
    return (set_signal);
}

void qurt_signal_set(qurt_signal_t *signal, uint32 mask)
{
#ifdef QOL_DEBUG
    printf("qurt_signal_set called\n");
#endif

    qol_sem_ptr *sem_obj_ptrs = NULL;
    int signals_present = 0;

    if (!signal || !mask)
    {
        return;
    }

    /* Extract pointer to qol_sem_ptr structure */
    sem_obj_ptrs = (qol_sem_ptr *)signal->queue;

    /* Protect access to signal object with mutex */
    sem_wait(sem_obj_ptrs->mutex);

    signal->signals = signal->signals | mask;
    if (signal->attribute == QURT_SIGNAL_ATTR_WAIT_ANY)
    {
        signals_present = signal->signals & signal->waiting;
    }

    if (signal->attribute == QURT_SIGNAL_ATTR_WAIT_ALL)
    {
        signals_present = (signal->signals & signal->waiting) == signal->waiting;
    }

    /* If required signals are present, release waiting thread, using semaphore 1 */

    /* However, only release waiting thread and clear "waiting" mask, if the mask
     * is not 0 to start with.  A 0 mask indicates that qurt_signal_wait() has not
     * been called yet.  In taht case, simply collect the signals and continue.
     * When qurt_sgnal_wait() is called, it will first check whether the wait condition
     * has been satisfied, and it will avoid suspending in that case. */
    if (signals_present)
    {
        if (signal->waiting != 0)
        {
            signal->waiting = 0;
            sem_post(sem_obj_ptrs->cond_var);
        }
    }

    sem_post(sem_obj_ptrs->mutex);
    return;
}

void qurt_signal_clear(qurt_signal_t *signal, uint32 mask)
{
#ifdef QOL_DEBUG
    printf("qurt_signal_clear called\n");
#endif

    qol_sem_ptr	*sem_obj_ptrs;

    if (signal == NULL)
    {
        return;
    }

    /* Extract pointer to qol_sem_ptr structure */
    sem_obj_ptrs = (qol_sem_ptr *)signal->queue;

    /* Protect access to signal object with mutex */
    sem_wait(sem_obj_ptrs->mutex);

    mask = ~mask;
    signal->signals = signal->signals & mask;

    sem_post(sem_obj_ptrs->mutex);
    return;
}

