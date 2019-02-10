/*
 * Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
 * Copyright (c) 2004-2005 Qualcomm Atheros, Inc.
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

/* Implementation of Host Target Communication tasks,
 * WorkTask and compl_task, which are used to manage
 * the Mbox Pending Queues.
 *
 * A mailbox Send request is queued in arrival order on
 * a per-mailbox Send queue until a credit is available
 * from the Target. Requests in this queue are
 * waiting for the Target to provide tx credits (i.e. recv
 * buffers on the Target-side).
 *
 * A mailbox Recv request is queued in arrival order on
 * a per-mailbox Recv queue until a message is available
 * to be read. So requests in this queue are waiting for
 * the Target to provide rx data.
 *
 * htca_work_task dequeues requests from the SendPendingQueue
 * (once credits are available) and dequeues requests from
 * the RecvPendingQueue (once rx data is available) and
 * hands them to HIF for processing.
 *
 * htca_compl_task handles completion processing after
 * HIF completes a request.
 *
 * The main purpose of these tasks is to provide a
 * suitable suspendable context for processing requests
 * and completions.
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "qapi/qurt_error.h"
#include "qapi/qurt_mutex.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_thread.h"
#include "qapi/qapi_types.h"

#include "common_defs.h"

#include "hif/hif.h"
#include "htca.h"
#include "htca_mbox_internal.h"

#define HTCA_WORK_TASK_NAME "htcaWork"
#define HTCA_WORK_TASK_PRIO 19
#define HTCA_WORK_TASK_STK_SIZE (2*1024)

#define HTCA_COMPL_TASK_NAME "htcaCompl"
#define HTCA_COMPL_TASK_PRIO 19
#define HTCA_COMPL_TASK_STK_SIZE (2*1024)

#define HTCA_REORDER_BARRIER() __asm volatile ("dsb")

/* Wakeup the htca_work_task.
 *
 * Invoked whenever send/recv state changes:
 * new Send buffer added to the send_pending_queue
 * new Recv buffer added to the recv_pending_queue
 * tx credits are reaped
 * rx data available recognized
 */
void htca_work_task_poke(struct htca_target *target)
{
    qurt_signal_set(&target->work_task_wait, HTCA_WORK_TASK_HAS_WORK_FLAG);
}

/*
 * Signal the htca_work_task when there are no outstanding HIF operations.
 */
void htca_idle_poke(struct htca_target *target)
{
    if ((target->outstanding_data == 0)
        && (target->outstanding_update_intr == 0)
        && (target->outstanding_credit_refresh == 0)
        && (target->outstanding_register_refresh == 0))
    {
        qurt_signal_set(&target->work_task_wait, HTCA_WORK_TASK_HIF_IS_IDLE_FLAG);
    }
}

/* Body of the htca_work_task, which hands Send and
 * Receive requests to HIF.
 */
static int htca_work_task_core(struct htca_target *target)
{
    int ep;
    int work_done = 0;

    /* TBD: We might consider alternative ordering policies, here,
     * between Sends and Recvs and among mailboxes. The current
     * algorithm is simple.
     */

    /* Process sends/recvs */
    for (ep = 0; ep < HTCA_NUM_MBOX; ep++) {
        work_done += htca_manage_pending_sends(target, ep);
        work_done += htca_manage_pending_recvs(target, ep);
    }

    return work_done;
}

/* Only this work_task is permitted to update
 * interrupt enables. That restriction eliminates
 * complex race conditions.
 */
static void htca_work_task(void *param)
{
    struct htca_target *target = (struct htca_target *)param;
    uint32 signals;
    int hif_is_idle = 1;

    for (;;) {
        htcadebug("%s: top of loop (%d).\r\n", __FUNCTION__, target->is_host_intr_enabled);
        /* Wait for htca_work_task_poke */
        signals = qurt_signal_wait(&target->work_task_wait,
                                   HTCA_WORK_TASK_HAS_WORK_FLAG
                                   | HTCA_WORK_TASK_SHUTDOWN_FLAG
                                   | HTCA_WORK_TASK_HIF_IS_IDLE_FLAG,
                                   QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);

        if (signals & HTCA_WORK_TASK_SHUTDOWN_FLAG) {
            break;              /* htcaTaskStop invoked */
        }

        HTCA_REORDER_BARRIER();

        hif_is_idle = (signals & HTCA_WORK_TASK_HIF_IS_IDLE_FLAG) ? 1 : 0;

        if (hif_is_idle && !(signals & HTCA_WORK_TASK_HAS_WORK_FLAG)) {
            /* As long as we are constantly refreshing register
             * state and processing, there is no need to enable
             * interrupts. We are essentially polling (over SDIO/SPI;
             * not in a tight CPU loop) for changes to Target state.
             * We avoid the overhead associated with interupts.
             *
             * Once HIF is idle -- no sends, receives, credit updates,
             * register refreshes -- then we update Target-side interrupt
             * disposition, re-enable Host-side interrupts and wait for
             * a DSR (and subsequent register refresh) to wake us.
             */
            htca_update_intr_enbs(target, 1);
            continue;
        }

        while (htca_work_task_core(target)) ;

        /* If additional work has arrived since we last checked,
         * make another pass.
         */
        if (qurt_signal_get(&target->work_task_wait) & HTCA_WORK_TASK_HAS_WORK_FLAG) {
            continue;
        }

        if (target->pending_recv_mask || target->outstanding_register_refresh) {
            /* When either of these completes, we'll be woken. */
            continue;
        }

        /* When a Recv completes, it sets need_register_refresh=1
         * and pokes the work_task.
         *
         * We won't actually initiate a register refresh until
         * pending recvs on ALL eps have completed. This may
         * increase latency slightly but it increases efficiency
         * and reduces chatter.
         *
         * Note that even though we don't initiate the register
         * refresh immediately, the interconnect is still 100%
         * busy doing useful work.
         */
#if 0
        /*
         * EXPERIMENTAL - "POLLING" instead of interrupts.
         * SDIO/SPI throughput may improve, but the cost is much
         * higher CPU utilization. Not recommended.
         */

#else
        if (target->need_register_refresh)
#endif
        {
            /* Continue to poll. When the RegsiterRefresh
             * completes, the WorkTask will be poked.
             */
            target->need_register_refresh = 0;
            htca_register_refresh_start(target, POLLING_REFRESH);
            continue;
        }

        htca_idle_poke(target);
    }
    qurt_signal_set(&target->work_task_wait, HTCA_WORK_TASK_EXIT_FLAG);
}

int htca_work_task_start(struct htca_target *target)
{
    int status = HTCA_ERROR;

    qurt_mutex_lock(&target->task_mutex);
    if (target->work_task) {
        goto done;              /* already started */
    }

    qurt_signal_create(&target->work_task_wait);
    {
        qurt_thread_attr_t thread_attr;
        int rv;

        qurt_thread_attr_set_name(&thread_attr, HTCA_WORK_TASK_NAME);
        qurt_thread_attr_set_priority(&thread_attr, HTCA_WORK_TASK_PRIO);
        qurt_thread_attr_set_stack_size(&thread_attr, HTCA_WORK_TASK_STK_SIZE);

        rv = qurt_thread_create(&target->work_task, &thread_attr, htca_work_task, (void *)target);

        if (rv != QURT_EOK) {
            goto done;          /* Failed to create work task */
        }
    }

    status = HTCA_OK;

 done:
    qurt_mutex_unlock(&target->task_mutex);
    return status;
}

void htca_work_task_stop(struct htca_target *target)
{
    qurt_mutex_lock(&target->task_mutex);

    if (!target->work_task) {
        goto done;
    }

    qurt_signal_set(&target->work_task_wait, HTCA_WORK_TASK_SHUTDOWN_FLAG);
    (void)qurt_signal_wait(&target->work_task_wait, HTCA_WORK_TASK_EXIT_FLAG, QURT_SIGNAL_ATTR_CLEAR_MASK);
    target->work_task = 0;

 done:
    qurt_mutex_unlock(&target->task_mutex);
}

#if defined(CONFIG_HTCA_COMPLETION_TASK)
/* Wakeup the compl_task.
 * Invoked after adding a new completion to the compl_queue.
 */
void htca_compl_task_poke(struct htca_target *target)
{
    qurt_signal_set(&target->compl_task_wait, HTCA_COMPL_TASK_HAS_WORK_FLAG);
}

int htca_manage_compl(struct htca_target *target)
{
    struct htca_request *req;

    /* Pop a request from the completion queue */
    INTR_BLOCK(target->compl_queue_lock);
    req = htca_request_deq_head(&target->compl_queue);
    INTR_UNBLOCK(target->compl_queue_lock);

    if (!req) {
        return 0;               /* nothing to do */
    }

    /* Invoke request's corresponding completion function */
    ASSERT(req->completion_cb);
    req->completion_cb(req, req->status);

    return 1;
}

static void htca_compl_task(void *param)
{
    struct htca_target *target = (struct htca_target *)param;
    uint32_t signals;

    for (;;) {
        /* Wait for htca_compl_task_poke */
        signals = qurt_signal_wait(&target->compl_task_wait,
                                   HTCA_COMPL_TASK_HAS_WORK_FLAG | HTCA_COMPL_TASK_SHUTDOWN_FLAG,
                                   QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);
        if (signals & HTCA_COMPL_TASK_SHUTDOWN_FLAG) {
            break;              /* htcaTaskStop invoked */
        }

        ASSERT(signals & HTCA_COMPL_TASK_HAS_WORK_FLAG);

        HTCA_REORDER_BARRIER();

        /* TBD: We could try to prioritize completions rather than
         * handle them strictly in order. Could use separate queues for
         * register completions and mailbox completion on each endpoint.
         * In general, completion processing is expected to be short
         * so this probably isn't worth the additional complexity.
         */
        {
            int did_work;

            do {
                did_work = htca_manage_compl(target);
            } while (did_work);
        }
    }
    qurt_signal_set(&target->compl_task_wait, HTCA_COMPL_TASK_SHUTDOWN_FLAG);
    (void)qurt_signal_wait(&target->compl_task_wait, HTCA_COMPL_TASK_EXIT_FLAG, QURT_SIGNAL_ATTR_CLEAR_MASK);
}

int htca_compl_task_start(struct htca_target *target)
{
    int status = HTCA_ERROR;

    qurt_mutex_lock(&target->task_mutex);

    if (target->compl_task) {
        goto done;              /* already started */
    }

    qurt_signal_create(&target->compl_task_wait);

    {
        qurt_thread_attr_t thread_attr;
        int rv;

        qurt_thread_attr_set_name(&thread_attr, HTCA_COMPL_TASK_NAME);
        qurt_thread_attr_set_priority(&thread_attr, HTCA_COMPL_TASK_PRIO);
        qurt_thread_attr_set_stack_size(&thread_attr, HTCA_COMPL_TASK_STK_SIZE);

        rv = qurt_thread_create(&target->compl_task, &thread_attr, htca_compl_task, (void *)target);

        if (rv != QURT_EOK) {
            goto done;          /* Failed to create completion task */
        }
    }

    status = HTCA_OK;

 done:
    qurt_mutex_unlock(&target->task_mutex);
    return status;
}

void htca_compl_task_stop(struct htca_target *target)
{
    qurt_mutex_lock(&target->task_mutex);

    if (!target->compl_task) {
        goto done;
    }

    qurt_signal_set(&target->compl_task_wait, HTCA_WORK_TASK_SHUTDOWN_FLAG);
    (void)qurt_signal_wait(&target->compl_task_wait, HTCA_WORK_TASK_EXIT_FLAG, QURT_SIGNAL_ATTR_CLEAR_MASK);
    target->compl_task = 0;

 done:
    qurt_mutex_unlock(&target->task_mutex);
}
#endif
