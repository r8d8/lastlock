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

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "qapi/qurt_mutex.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_thread.h"
#include "qapi/qapi_types.h"

#include "common_defs.h"
#include "hif/hif.h"
#include "htca.h"
#include "htca_mbox_internal.h"

/* Host Target Communications Completion Management */

/* Top-level callback handler, registered with HIF to be invoked
 * whenever a read/write HIF operation completes. Executed in the
 * context of an HIF task, so we don't want to take much time
 * here. Pass processing to HTCA's compl_task.
 *
 * Used for both reg_requests and mbox_requests.
 */
int htca_rw_completion_handler(void *context, int status)
{
    struct htca_request *req;

    req = (struct htca_request *)context;
    if (!context) {
        /* No completion required for this request.
         * (e.g. Fire-and-forget register write.)
         */
        return HTCA_OK;
    }

    req->status = status;

#if defined(CONFIG_HTCA_COMPLETION_TASK)
    {
        struct htca_target *target;

        target = req->target;
        /* Enqueue this completed request on the
         * Target completion queue.
         */
        INTR_BLOCK(target->compl_queue_lock);
        htca_request_enq_tail(&target->compl_queue, (struct htca_request *)req);
        INTR_UNBLOCK(target->compl_queue_lock);

        /* Notify the completion task that it has work */
        htca_compl_task_poke(target);
    }
#else
    /* Invoke request's corresponding completion function */
    ASSERT(req->completion_cb);
    req->completion_cb(req, req->status);
#endif

    return HTCA_OK;
}

/* Request-specific callback invoked by the HTCA Completion Task
 * when a Mbox Send Request completes. Note: Used for Mbox Send
 * requests; not used for Reg requests.
 *
 * Simply dispatch a BUFFER_SENT event to the originator of the request.
 */
void htca_send_compl(struct htca_request *req, int status)
{
    struct htca_target *target;
    uint8_t end_point_id;
    struct htca_event_info event_info;
    struct htca_endpoint *end_point;
    struct htca_mbox_request *mbox_request = (struct htca_mbox_request *)req;

    end_point = mbox_request->end_point;
    target = end_point->target;
    end_point_id = get_endpoint_id(end_point);

    /* Strip off the HTCA header that was added earlier */
    mbox_request->buffer += HTCA_HEADER_LEN_MAX;

    /* Prepare event frame to notify caller */
    htca_frame_event(&event_info, mbox_request->buffer,
                     mbox_request->buffer_length,
                     mbox_request->actual_length, (status == HIF_OK) ? HTCA_OK : HTCA_ECANCELED, mbox_request->cookie);

    /* Recycle the request */
    INTR_BLOCK(end_point->mbox_queue_lock);
    htca_request_enq_tail(&end_point->send_free_queue, (struct htca_request *)mbox_request);
    INTR_UNBLOCK(end_point->mbox_queue_lock);

    /* Regardless of success/failure, notify caller that HTCA is done
     * with his buffer.
     */
    htca_dispatch_event(target, end_point_id, HTCA_EVENT_BUFFER_SENT, &event_info);
    INTR_BLOCK(target->outstanding_lock);
    ASSERT(target->outstanding_data);
    target->outstanding_data--;
    INTR_UNBLOCK(target->outstanding_lock);
    htca_idle_poke(target);
}

/* Request-specific callback invoked by the HTCA Completion Task
 * when a Mbox Recv Request completes. Note: Used for Mbox Recv
 * requests; not used for Reg requests.
 *
 * Simply dispatch a BUFFER_RECEIVED event to the originator
 * of the request.
 */
void htca_recv_compl(struct htca_request *req, int status)
{
    struct htca_target *target;
    struct htca_event_info event_info;
    uint8_t end_point_id;
    struct htca_endpoint *end_point;
    struct htca_mbox_request *mbox_request = (struct htca_mbox_request *)req;

    end_point = mbox_request->end_point;
    target = end_point->target;
    end_point_id = get_endpoint_id(end_point);

    /* Signaling:
     * Now that we have consumed recv data, clear rx_frame_length so that
     * htca_manage_pending_recvs will not try to re-read the same data.
     *
     * Set need_register_refresh so we can determine whether or not there
     * is additional data waiting to be read.
     *
     * Clear our endpoint from the pending_recv_mask so
     * htca_manage_pending_recvs is free to issue another read.
     *
     * Finally, poke the work_task.
     */
    end_point->rx_frame_length = 0;
    target->need_register_refresh = 1;

    INTR_BLOCK(target->pending_op_lock);
    target->pending_recv_mask &= ~(1 << end_point_id);
    INTR_UNBLOCK(target->pending_op_lock);
    htca_work_task_poke(target);

    if (status == HIF_OK) {
        uint32_t check_length;
        /* Length coming from Target is always LittleEndian */
        check_length = ((mbox_request->buffer[0] << 0) | (mbox_request->buffer[1] << 8));
        ASSERT(mbox_request->actual_length == check_length);
    }

    /* Strip off header */
    mbox_request->buffer += HTCA_HEADER_LEN_MAX;

    htca_frame_event(&event_info, mbox_request->buffer,
                     mbox_request->buffer_length,
                     mbox_request->actual_length, (status == HIF_OK) ? HTCA_OK : HTCA_ECANCELED, mbox_request->cookie);

    /* Recycle the request */
    INTR_BLOCK(end_point->mbox_queue_lock);
    htca_request_enq_tail(&end_point->recv_free_queue, (struct htca_request *)mbox_request);
    INTR_UNBLOCK(end_point->mbox_queue_lock);

    htca_dispatch_event(target, end_point_id, HTCA_EVENT_BUFFER_RECEIVED, &event_info);

    INTR_BLOCK(target->outstanding_lock);
    ASSERT(target->outstanding_data);
    target->outstanding_data--;
    INTR_UNBLOCK(target->outstanding_lock);
    htca_idle_poke(target);
}

/* Request-specific callback invoked when a register read/write
 * request completes. reg_request structures are not used for
 * register WRITE requests so there's not much to do for writes.
 *
 * Note: For Mbox Request completions see htca_send_compl
 * and htca_recv_compl.
 */

/* Request-specific callback invoked by the HTCA Completion Task
 * when a Reg Request completes. Note: Used for Reg requests;
 * not used for Mbox requests.
 */
void htca_reg_compl(struct htca_request *req, int status)
{
    struct htca_target *target;
    struct htca_reg_request *reg_request = (struct htca_reg_request *)req;
    enum htca_req_purpose purpose;

    ASSERT(reg_request);

    purpose = reg_request->purpose;
    htcadebug("%s: purpose=0x%x\r\n", __FUNCTION__, purpose);

    /* Process async register read/write completion */

    target = reg_request->req.target;
    if (status != HIF_OK) {
        /* A register read/write accepted by HIF
         * should never fail.
         */
        ASSERT(0);

#if 0                           /* should never get here. */
        /* Recycle the request */
        INTR_BLOCK(target->outstanding_lock);
        if ((purpose == INTR_REFRESH) || (purpose == POLLING_REFRESH)) {
            ASSERT(target->outstanding_register_refresh);
            target->outstanding_register_refresh--;
            htca_idle_poke(target);
        } else if (purpose == CREDIT_REFRESH) {
            ASSERT(target->outstanding_credit_refresh);
            target->outstanding_credit_refresh--;
            htca_idle_poke(target);
        } else {
            ASSERT(target->outstanding_update_intr);
            target->outstanding_update_intr--;
            // htca_idle_poke(target);
        }
        INTR_UNBLOCK(target->outstanding_lock);

        reg_request->purpose = UNUSED_PURPOSE;
        INTR_BLOCK(target->reg_queue_lock);
        htca_request_enq_tail(&target->reg_free_queue, (struct htca_request *)reg_request);
        INTR_UNBLOCK(target->reg_queue_lock);
#endif
        return;
    }

    switch (purpose) {
    case INTR_REFRESH:
    case POLLING_REFRESH:
        /* Target register state, including interrupt
         * registers, has been fetched.
         */
        INTR_BLOCK(target->outstanding_lock);
        ASSERT(target->outstanding_register_refresh);
        target->outstanding_register_refresh--;
        INTR_UNBLOCK(target->outstanding_lock);
        htca_register_refresh_compl(target, reg_request);
        // htca_idle_poke(target);
        break;

    case CREDIT_REFRESH:
        INTR_BLOCK(target->outstanding_lock);
        ASSERT(target->outstanding_credit_refresh);
        target->outstanding_credit_refresh--;
        INTR_UNBLOCK(target->outstanding_lock);
        htca_credit_refresh_compl(target, reg_request);
        // htca_idle_poke(target);
        break;

    case UPDATE_TARG_INTRS:
    case UPDATE_TARG_AND_ENABLE_HOST_INTRS:
        INTR_BLOCK(target->outstanding_lock);
        ASSERT(target->outstanding_update_intr);
        target->outstanding_update_intr--;
        INTR_UNBLOCK(target->outstanding_lock);
        htca_update_intr_enbs_compl(target, reg_request);
        // htca_idle_poke(target);
        break;

    default:
        ASSERT(0);              /* unhandled request type */
        break;
    }

    /* Recycle this register read/write request */
    reg_request->purpose = UNUSED_PURPOSE;
    INTR_BLOCK(target->reg_queue_lock);
    htca_request_enq_tail(&target->reg_free_queue, (struct htca_request *)reg_request);
    INTR_UNBLOCK(target->reg_queue_lock);
}

/* After a Register Refresh, uppdate tx_credits_to_reap for each end_point.  */
__attribute__ ((noinline))
void htca_update_tx_credits_to_reap(struct htca_target *target, struct htca_reg_request *reg_request)
{
    struct htca_endpoint *end_point;
    int ep;

    for (ep = 0; ep < HTCA_NUM_MBOX; ep++) {
        end_point = &target->end_point[ep];

        if (reg_request->u.reg_table.status.counter_int_status & (0x10 << ep)) {
            end_point->tx_credits_to_reap = true;
        } else {
            end_point->tx_credits_to_reap = false;
        }
    }
}

/* After a Register Refresh, uppdate rx_frame_length for each end_point.  */
__attribute__ ((noinline))
void htca_update_rx_frame_lengths(struct htca_target *target, struct htca_reg_request *reg_request)
{
    struct htca_endpoint *end_point;
    uint32_t rx_lookahead;
    uint32_t frame_length;
    int ep;

    htcadebug("%s: Enter\r\n", __FUNCTION__);
    for (ep = 0; ep < HTCA_NUM_MBOX; ep++) {
        end_point = &target->end_point[ep];

        if (end_point->rx_frame_length != 0) {
            /* NB: Will be cleared in htca_recv_compl after
             * frame is read
             */
            continue;
        }

        if (!(reg_request->u.reg_table.rx_lookahead_valid & (1 << ep))) {
            continue;
        }

        /* The length of the incoming message is contained
         * in the first two (HTCA_HEADER_LEN) bytes in
         * LittleEndian order.
         *
         * This length does NOT include the HTCA header nor block
         * padding.
         */
        rx_lookahead = reg_request->u.reg_table.rx_lookahead[ep];
        frame_length = rx_lookahead & 0x0000ffff;
        ASSERT(frame_length <= HTCA_MESSAGE_SIZE_MAX);

        end_point->rx_frame_length = frame_length;
        htcadebug("%s: ep#%d : %d\r\n", __FUNCTION__, ep, frame_length);
    }
}

/* For debug, count the number of interrupts and spurious interrupts */
unsigned int htca_debug_intr;
unsigned int htca_debug_spurious_intr;

/* Completion for a register refresh.
 *
 * Update rxFrameLengths and tx_credits_to_reap info for
 * each endpoint. Then handle all pending interrupts (o
 * if interrupts are currently masked at the Host, handle
 * all interrupts that would be pending if interrupts
 * were enabled).
 *
 * Called in the context of HIF's completion task whenever
 * results from a register refresh are received.
 */
void htca_register_refresh_compl(struct htca_target *target, struct htca_reg_request *req)
{
    uint8_t host_int_status;
    uint8_t pnd_enb_intrs;      /* pending and enabled interrupts */
    uint8_t pending_int;
    uint8_t enabled_int;

    htcadebug("%s: Enter\r\n", __FUNCTION__);

    htcadebug("%s: REGDUMP: hostis=0x%02x cpuis=0x%02x erris=0x%02x cntris=0x%02x\r\n",
              __FUNCTION__,
              req->u.reg_table.status.host_int_status,
              req->u.reg_table.status.cpu_int_status,
              req->u.reg_table.status.err_int_status, req->u.reg_table.status.counter_int_status);
    htcadebug("%s: mbox_frame=0x%02x lav=0x%02x la0=0x%08x la1=0x%08x la2=0x%08x la3=0x%08x\r\n",
              __FUNCTION__,
              req->u.reg_table.mbox_frame, req->u.reg_table.rx_lookahead_valid,
              req->u.reg_table.rx_lookahead[0], req->u.reg_table.rx_lookahead[1],
              req->u.reg_table.rx_lookahead[2], req->u.reg_table.rx_lookahead[3]);

    /* Update rxFrameLengths */
    htca_update_rx_frame_lengths(target, req);

    /* Update tx_credits_to_reap */
    htca_update_tx_credits_to_reap(target, req);

    /* Process pending Target interrupts. */

    /* Restrict attention to pending interrupts of interest */
    host_int_status = req->u.reg_table.status.host_int_status;

    /* Unexpected and unhandled */
    ASSERT(!(host_int_status & HOST_INT_STATUS_DRAGON_INT_MASK));

    /* Form software's idea of pending and enabled interrupts.
     * Start with ERROR interrupts.
     */
    pnd_enb_intrs = host_int_status & HOST_INT_STATUS_ERROR_MASK;

    /* Add CPU interrupts pending and enabled */
    if (INT_STATUS_ENABLE_CPU_GET(target->enb.int_status_enb)
        && HOST_INT_STATUS_CPU_GET(host_int_status)) {
        pnd_enb_intrs |= HOST_INT_STATUS_CPU_MASK;
    }

    /* Software may have intended to enable/disable credit
     * counter interrupts; but we commit these updates to
     * Target hardware lazily, just before re-enabling
     * interrupts. So registers that we have now may not
     * reflect the intended state of interrupt enables.
     */

    /* Based on software credit enable bits, update pnd_enb_intrs
     * ("pending and enabled interrupts") as if desired interrupt
     * enable state is committed to HW.
     */
    pending_int = req->u.reg_table.status.counter_int_status;
    enabled_int = target->enb.counter_int_status_enb;
    if (pending_int & enabled_int) {
        pnd_enb_intrs |= HOST_INT_STATUS_COUNTER_MASK;
    }

    /* Based on software recv data enable bits, update
     * pnd_enb_intrs AS IF all the recv interrupt enables had
     * been committed to HW.
     */
    pending_int = host_int_status & HOST_INT_STATUS_MBOX_DATA_MASK;
    enabled_int = target->enb.int_status_enb;
    pnd_enb_intrs |= (pending_int & enabled_int);

    if (req->purpose == INTR_REFRESH) {
        if (pnd_enb_intrs) {
            htca_debug_intr++;
        } else {
            /* No enabled interrupts are pending. */
            htca_debug_spurious_intr++;
        }
    }

    /* Invoke specific handlers for each enabled and pending interrupt.
     * The goal of each service routine is to clear interrupts at the
     * source (on the Target).
     *
     * We deal with four types of interrupts in the HOST_INT_STATUS
     * summary register:
     * errors
     * This remains set until bits in ERROR_INT_STATUS are cleared
     *
     * CPU
     * This remains set until bits in CPU_INT_STATUS are cleared
     *
     * rx data available
     * These remain set as long as rx data is available. HW clears
     * the rx data available enable bits when receive buffers
     * are exhausted. If we exhaust Host-side received buffers, we
     * mask the rx data available interrupt.
     *
     * tx credits available
     * This remains set until all bits in COUNTER_INT_STATUS are
     * cleared by HW after Host SW reaps all credits on a mailbox.
     * If credits on an endpoint are sufficient, we mask the
     * corresponding COUNTER_INT_STATUS bit. We avoid "dribbling"
     * one credit at a time and instead reap them en masse.
     *
     * The HOST_INT_STATUS register is read-only these bits are cleared
     * by HW when the underlying condition is cleared.
     */

    if (HOST_INT_STATUS_ERROR_GET(pnd_enb_intrs)) {
        htca_service_error_interrupt(target, req);
    }

    if (HOST_INT_STATUS_CPU_GET(pnd_enb_intrs)) {
        htca_service_cpu_interrupt(target, req);
    }

    if (HOST_INT_STATUS_COUNTER_GET(pnd_enb_intrs)) {
        htca_service_credit_counter_interrupt(target, req);
    }

    /* Always needed in order to at least unmask Host interrupts */
    htca_work_task_poke(target);
}

/* Complete an update of interrupt enables. */
void htca_update_intr_enbs_compl(struct htca_target *target, struct htca_reg_request *req)
{
    htcadebug("%s: Enter\r\n", __FUNCTION__);
    if (req->purpose == UPDATE_TARG_AND_ENABLE_HOST_INTRS) {
        /* NB: non-intuitive, but correct */

        /* While waiting for rxdata and txcred
         * interrupts to be disabled at the Target,
         * we temporarily masked interrupts at
         * the Host. It is now safe to allow
         * interrupts (esp. ERROR and CPU) at
         * the Host.
         */
        htcadebug("%s: Unmasking\r\n", __FUNCTION__);
        hif_unmask_interrupt(target->hif_handle);
        target->is_host_intr_enabled = 1;
    }
}

/* Called to complete htca_credit_refresh_start.
 *
 * Ends a credit refresh cycle. Called after decrementing a
 * credit counter register (many times in a row). HW atomically
 * decrements the counter and returns the OLD value but HW will
 * never reduce it below 0.
 *
 * Called in the context of the work_task when the credit counter
 * decrement operation completes synchronously. Called in the
 * context of the compl_task when the credit counter decrement
 * operation completes asynchronously.
 */
void htca_credit_refresh_compl(struct htca_target *target, struct htca_reg_request *reg_request)
{
    struct htca_endpoint *end_point;
    int reaped;
    int i;

    /* A non-zero value indicates 1 credit reaped.
     * Typically, we will find monotonically descending
     * values that reach 0 with the remaining values
     * all zero. But we must scan the entire results
     * to handle the case where the Target just happened
     * to increment credits simultaneously with our
     * series of credit decrement operations.
     */
    htcadebug("%s: epid=%d\r\n", __FUNCTION__, reg_request->epid);
    end_point = &target->end_point[reg_request->epid];
    reaped = 0;
    for (i = 0; i < HTCA_TX_CREDITS_REAP_MAX; i++) {
        htcadebug("|Reap:0x%02x", reg_request->u.credit_dec_results[i]);
        if (reg_request->u.credit_dec_results[i]) {
            reaped++;
        }
    }

    htcadebug("%s: reaped %d credits on epid=%d\r\n", __FUNCTION__, reaped, reg_request->epid);

    INTR_BLOCK(end_point->tx_credit_lock);
    end_point->tx_credits_available += reaped;
    end_point->tx_credit_refresh_in_progress = false;
    INTR_UNBLOCK(end_point->tx_credit_lock);

    htca_work_task_poke(target);
}
