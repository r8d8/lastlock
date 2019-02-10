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
#include <errno.h>
#include <pthread.h>
#include "qurt_timer.h"
#include "qurt_mutex.h"
#include "qurt_error.h"

//extern uint32 qurt_system_get_ipsr( void );

int qurt_mutex_init(qurt_mutex_t *lock)
{
    pthread_mutex_t *pMutex = NULL;
    pthread_mutexattr_t pMattr;
    int ret = 0;

    if(!lock)
    {
        return QURT_EINVALID;
    }

    ret = pthread_mutexattr_init(&pMattr);
    if(0 != ret)
    {
        return QURT_EINVALID;
    }

    ret = pthread_mutexattr_settype(&pMattr, PTHREAD_MUTEX_RECURSIVE);
    if(0 != ret)
    {
        return QURT_EINVALID;
    }

    /* Allocate memory for mutex object */
    pMutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if(NULL == pMutex)
    {
        return QURT_EMEM;
    }

    ret = pthread_mutex_init(pMutex, &pMattr);
    switch(ret)
    {
        case 0:
            *lock = (qurt_mutex_t)pMutex;
            ret = QURT_EOK;
            break;

        case EINVAL:
            ret = QURT_EINVALID;
            break;

        case EAGAIN:
            /* Intentional fall through */
        case ENOMEM:
            ret = QURT_EMEM;
            break;

        case EBUSY:
            /* Intentional fall through */
        case EPERM:
            ret = QURT_ENOTALLOWED;
            break;

        default:
            ret = QURT_EFAILED;
            break;
    }

    if(QURT_EOK != ret)
    {
        free(pMutex);
    }
    return ret;
}

void qurt_mutex_lock(qurt_mutex_t *lock)
{
    pthread_mutex_t *pMutex = NULL;
    if(lock && *lock)
    {
        pMutex = (pthread_mutex_t *)(*lock);
        pthread_mutex_lock(pMutex);
    }

    /* mutex lock timed is not supported from ISR */
    //   ASSERT(0 == qurt_system_get_ipsr());
    return;
}

int qurt_mutex_lock_timed(qurt_mutex_t *lock, qurt_time_t timeout)
{
    pthread_mutex_t *pMutex = NULL;
    struct timespec ts = {0,0};
    int ret = QURT_EFAILED;

    timeout = qurt_timer_convert_ticks_to_time(timeout, QURT_TIME_MSEC);
    ts.tv_sec = timeout / 1000;
    ts.tv_nsec = (timeout % 1000) * 1000000;

    if(!lock || !(*lock))
    {
        return QURT_EINVALID;
    }

    /* mutex lock timed is not supported from ISR */
    // ASSERT(0 == qurt_system_get_ipsr());
    pMutex = (pthread_mutex_t *)(*lock);
    ret = pthread_mutex_timedlock(pMutex , (struct timespec *)&ts);
    switch(ret)
    {
        case 0:
            ret = QURT_EOK;
            break;

        case EAGAIN:
            /* Intentional fall through */
        case EINVAL:
            ret = QURT_EINVALID;
            break;

        case EDEADLK:
            ret = QURT_ENOTALLOWED;
            break;

        case ETIMEDOUT:
            ret = QURT_EFAILED_TIMEOUT;
            break;

        default:
            ret = QURT_EFAILED;
            break;
    }

    return ret;
}

void qurt_mutex_unlock(qurt_mutex_t *lock)
{
    pthread_mutex_t *pMutex = NULL;
    if(lock && *lock)
    {
        pMutex = (pthread_mutex_t *)(*lock);
        pthread_mutex_unlock(pMutex);
    }
    return;
}

void qurt_mutex_destroy(qurt_mutex_t *lock)
{
    pthread_mutex_t *pMutex = NULL;
    if(lock && *lock)
    {
        pMutex = (pthread_mutex_t *)(*lock);
        pthread_mutex_destroy(pMutex);
        free(pMutex);
    }
    return;
}
