/*======================================================================
  Copyright (c) 2015-2017, The Linux Foundation. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted (subject to the limitations in the
  disclaimer below) provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following
 disclaimer in the documentation and/or other materials provided
 with the distribution.

 * Neither the name of The Linux Foundation nor the names of its
 contributors may be used to endorse or promote products derived
 from this software without specific prior written permission.

 NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 qurt_thread.c

 GENERAL DESCRIPTION
 QuRT thread functions
 ======================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include "qurt_error.h"
#include "qurt_thread.h"
#include "qurt_timer.h"

#define QURT_THREAD_MIN_PRIORITIES  0
#define QURT_THREAD_MAX_PRIORITIES 32

/** Thread attributes */
typedef struct _qurt_thread_attr {
    char name[QURT_THREAD_ATTR_NAME_MAXLEN]; /**< Thread name. */
    unsigned short priority;                 /**< Thread priority.   */
    unsigned int   stack_size;               /**< Thread stack size. */
    void *stack_addr;                        /**< Stack address base */
}_qurt_thread_attr;

typedef void* (*thread_handler)(void *param);

/*======================================================================
  FUNCTIONS
  =======================================================================*/
#if 0
static int qurt_to_pthread_priority(int policy, int qpriority)
{
    int qrange = 0, pthread_min_prio = 0, pthread_max_prio = 0, prange = 0, ppriority = 0;

    /* Obtain current pthread scheduling parameters and current minimum-maximum priorities */
    pthread_min_prio = sched_get_priority_min(policy);
    pthread_max_prio = sched_get_priority_max(policy);
    prange = pthread_max_prio - pthread_min_prio;


    //    printf("Valid priority range for SCHED_FIFO: %d - %d\n",
    //                   pthread_min_prio,
    //                 pthread_max_prio);

    qrange = QURT_THREAD_MAX_PRIORITIES - QURT_THREAD_MIN_PRIORITIES;
    ppriority = ((qpriority * prange) / qrange) + pthread_min_prio;

    if (ppriority < pthread_min_prio)
        ppriority = pthread_min_prio;

    if (ppriority > pthread_max_prio)
        ppriority = pthread_max_prio;

    return ppriority;
}
#endif

void qurt_thread_attr_init (qurt_thread_attr_t *attr)
{
    _qurt_thread_attr *qurt_attr = (_qurt_thread_attr *)attr;
    qurt_attr->name[0] = 0;
    qurt_attr->priority = QURT_THREAD_ATTR_PRIORITY_DEFAULT;
    qurt_attr->stack_size = 0;
    qurt_attr->stack_addr = 0;
    return;
}

void qurt_thread_attr_set_name (qurt_thread_attr_t *attr, const char *name)
{
    _qurt_thread_attr *qurt_attr = (_qurt_thread_attr *)attr;
    memset(qurt_attr->name, 0, QURT_THREAD_ATTR_NAME_MAXLEN);
    strncpy(qurt_attr->name, name, QURT_THREAD_ATTR_NAME_MAXLEN-1);
    return;
}

void qurt_thread_attr_set_priority (qurt_thread_attr_t *attr, uint16 priority)
{
    _qurt_thread_attr *qurt_attr = (_qurt_thread_attr *)attr;
    qurt_attr->priority = (QURT_THREAD_MAX_PRIORITIES -1) - priority;
    return;
}

void qurt_thread_attr_set_stack_size (qurt_thread_attr_t *attr, uint32 stack_size)
{
    _qurt_thread_attr *qurt_attr = (_qurt_thread_attr *)attr;
    qurt_attr->stack_size = stack_size;
    return;
}

int qurt_thread_create(qurt_thread_t *thread_id, qurt_thread_attr_t *attr,
        void (*entrypoint) (void *), void *arg)
{
    _qurt_thread_attr *qurt_attr = (_qurt_thread_attr *)attr;
    int ret = 0;
    pthread_t pthread_id;
    pthread_attr_t pthread_attr;
    //    struct sched_param param;

    if(!thread_id || !qurt_attr || (qurt_attr->priority > (QURT_THREAD_MAX_PRIORITIES - 1)))
    {
        return QURT_EINVALID;
    }

    pthread_attr_init(&pthread_attr);
    //    memset(&param, 0, sizeof(param));
    //    param.sched_priority = qurt_to_pthread_priority(SCHED_FIFO, qurt_attr->priority);
#if 0
    ret = pthread_attr_setschedparam(&pthread_attr, &param);
    if(0 == ret)
    {
        ret = pthread_attr_setschedpolicy(&pthread_attr, policy);
        if(0 == ret)
        {
#endif
            ret = pthread_create(&pthread_id, &pthread_attr, (thread_handler)entrypoint, arg);
#if 0
            if(0 == ret)
            {
                ret = pthread_attr_setstacksize(&pthread_attr, qurt_attr->stack_size);
            }
        }
    }
#endif
    switch(ret)
    {
        case 0:
            *thread_id = pthread_id;
            return QURT_EOK;

        case EAGAIN:
            return QURT_EMEM;

        case EINVAL:
            return QURT_EINVALID;

        case EPERM:
            return QURT_ENOTALLOWED;

        default:
            return QURT_EFAILED;
    }
}

qurt_thread_t qurt_thread_get_id (void)
{
    return (qurt_thread_t)pthread_self();
}

void qurt_thread_stop (void)
{
    pthread_exit(NULL);
}

void qurt_thread_sleep (qurt_time_t duration)
{
    unsigned int seconds = qurt_timer_convert_ticks_to_time(duration, QURT_TIME_SEC);
    sleep(seconds);
}

