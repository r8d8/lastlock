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

/* Decide when an endpoint is low on tx credits and we should
 * initiate a credit refresh. If this is set very low, we may
 * exhaust credits entirely and pause while we wait for credits
 * to be reaped from the Target. If set very high we may end
 * up spending excessive time trying to reap when nothing is
 * available.
 *
 * TBD: We could make this something like a percentage of the
 * most credits we've ever seen on this endpoint. Or make it
 * a value that automatically adjusts -- increase by one whenever
 * we exhaust credits; decrease by one whenever a CREDIT_REFRESH
 * fails to reap any credits.
 * For now, wait until credits are completely exhausted; then
 * initiate a credit refresh cycle.
 */
#define HTCA_EP_CREDITS_ARE_LOW(_endp) ((_endp)->tx_credits_available <= 0)

/* Pull as many Mailbox Send Requests off of the PendingSend queue
 * as we can (must have a credit for each send) and hand off the
 * request to HIF.
 *
 * This function returns when we exhaust Send Requests OR when we
 * exhaust credits.
 *
 * If we are low on credits, it starts a credit refresh cycle.
 *
 * Returns 0 if nothing was send to HIF
 * returns 1 if at least one request was sent to HIF
 */
int htca_manage_pending_sends(struct htca_target *target, int epid)
{
    struct htca_endpoint *end_point;
    struct htca_request_queue *send_queue;
    struct htca_mbox_request *mbox_request;
    uint8_t tx_credits_available;
    int work_done = 0;

    end_point = &target->end_point[epid];
    send_queue = &end_point->send_pending_queue;

    /* Transmit messages as long as we have both something to send
     * tx credits that permit us to send
     */
    while (!HTCA_IS_QUEUE_EMPTY(send_queue)) {
        INTR_BLOCK(end_point->tx_credit_lock);
#if 0                           /* EXPERIMENTAL -- DISABLE FLOW CONTROL */
        /*
         * This test feature may be used with Target firmware
         * such as "bitbucket" in order to test raw send speed
         * with no flow control.
         */
        end_point->tx_credits_available = 99;
#endif
        tx_credits_available = end_point->tx_credits_available;
        if (tx_credits_available) {
            end_point->tx_credits_available--;
        }
        INTR_UNBLOCK(end_point->tx_credit_lock);
        htcadebug("%s: (epid=%d) tx_credits_available=%d\r\n", __FUNCTION__, epid, tx_credits_available);
        if (!tx_credits_available) {
            /* We exhausted tx credits */
            break;
        }

        /* Get the request buffer from the Pending Send Queue */
        INTR_BLOCK(end_point->mbox_queue_lock);
        mbox_request = (struct htca_mbox_request *)htca_request_deq_head(send_queue);
        INTR_UNBLOCK(end_point->mbox_queue_lock);

        if (!mbox_request) {
            break;
        }

        INTR_BLOCK(target->outstanding_lock);
        target->outstanding_data++;
        INTR_UNBLOCK(target->outstanding_lock);

        /* Hand off this Mbox Send request to HIF */
        if (htca_send_request_to_hif(end_point, mbox_request) == HTCA_ERROR) {
            ASSERT(0);          /* should never fail */
#if 0                           /* Failure is unexpected; code below is untested */
            struct htca_event_info event_info;

            /* TBD: Could requeue this at the HEAD of the
             * pending send queue. Try again later?
             */

            /* Restore tx credit, since it was not used */
            INTR_BLOCK(end_point->tx_credit_lock);
            end_point->tx_credits_available++;
            INTR_UNBLOCK(&end_point->tx_credit_lock);

            /* Frame an event to send to caller */
            htca_frame_event(&event_info, mbox_request->buffer,
                             mbox_request->buffer_length,
                             mbox_request->actual_length, HTCA_ECANCELED, mbox_request->cookie);

            /* Free the Mailbox request */
            INTR_BLOCK(end_point->mbox_queue_lock);
            htca_request_enq_tail(&end_point->send_free_queue, (struct htca_request *)mbox_request);
            INTR_UNBLOCK(end_point->mbox_queue_lock);

            htca_dispatch_event(target, epid, HTCA_EVENT_BUFFER_SENT, &event_info);

            INTR_BLOCK(target->outstanding_lock);
            target->outstanding_data--;
            INTR_UNBLOCK(target->outstanding_lock);
            htca_idle_poke(target);

#endif
            goto done;
        }
        work_done = 1;
    }

    htcadebug("%s: epid=%d credsAvail=%d toReap=%d\r\n",
              __FUNCTION__, epid, end_point->tx_credits_available, end_point->tx_credits_to_reap);
    if (HTCA_EP_CREDITS_ARE_LOW(end_point)) {
        if (end_point->tx_credits_to_reap) {
            htca_credit_refresh_start(end_point);
        } else {
            target->enb.counter_int_status_enb |= (0x10 << epid);
        }
    } else {
        target->enb.counter_int_status_enb &= ~(0x10 << epid);
    }

 done:
    return work_done;
}

/* Send one send request to HIF.
 *
 * Called from the HTCA task while processing requests from
 * an endpoint's pendingSendQueue.
 *
 * Note: May consider calling this in the context of a process
 * submitting a new Send Request (i.e. when nothing else is
 * pending and credits are available). This would save the
 * cost of context switching to the HTCA Work Task; but it would
 * require additional synchronization and would add some
 * complexity. For the high throughput case this optimization
 * would not help since we are likely to have requests
 * pending which must be submitted to HIF in the order received.
 */
int htca_send_request_to_hif(struct htca_endpoint *end_point, struct htca_mbox_request *mbox_request)
{
    int status;
    struct htca_target *target;
    uint32_t padded_length;
    uint32_t mbox_address;
    uint32_t req_type;

    target = end_point->target;

    /* Adjust length for power-of-2 block size */
    padded_length = htca_round_up(mbox_request->actual_length + HTCA_HEADER_LEN_MAX, end_point->block_size);

    /* Prepend the message's actual length to the  outgoing message.
     * Caller is REQUIRED to leave HTCA_HEADER_LEN_MAX bytes before
     * the message for this purpose (of which the first HTCA_HEADER_LEN
     * bytes are actually used).
     *
     * TBD: We may enhance HIF so that a single write request
     * may have TWO consecutive components: one for the HTCA header
     * and another for the payload. This would remove the burden
     * on callers to reserve space in their buffer for HTCA.
     *
     * TBD: Since the messaging layer sitting on top of HTCA may
     * have this same issue it may make sense to allow a Send
     * to pass in a "header buffer" along with a "payload buffer".
     * So two buffers (or more generally, a list of buffers)
     * rather than one on each call.  These buffers would be
     * guaranteed to be sent to HIF as a group and they would
     * be sent over SDIO back to back.
     */
    mbox_request->buffer -= HTCA_HEADER_LEN_MAX;

    if (HTCA_HEADER_LEN_MAX > HTCA_HEADER_LEN) {
        /* Sanity: clear padding bytes, if used */
        memset(&mbox_request->buffer[HTCA_HEADER_LEN], 0, HTCA_HEADER_LEN_MAX - HTCA_HEADER_LEN);
    }
    /* Target receives length in LittleEndian byte order
     * regardeless of Host endianness.
     */
    mbox_request->buffer[0] = mbox_request->actual_length & 0xff;
    mbox_request->buffer[1] = (mbox_request->actual_length >> 8) & 0xff;

    req_type = (end_point->block_size > 1) ? HIF_WR_ASYNC_BLOCK_INC : HIF_WR_ASYNC_BYTE_INC;

    /* Arrange for last byte of the message to generate an
     * EndOfMessage interrupt to the Target.
     */
    mbox_address = end_point->mbox_end_addr - padded_length;

    /* Send the request to HIF */
    status = hif_read_write(target->hif_handle, mbox_address,
                            mbox_request->buffer, padded_length, req_type, mbox_request);

    if (status == HIF_OK && mbox_request->req.completion_cb) {
        mbox_request->req.completion_cb((struct htca_request *)mbox_request, HTCA_OK);
        /* htcaSendCompletionCB */
    } else if (status == HIF_PENDING) {
        /* Will complete later */
    } else {                    /* HIF error */
        /* Restore mbox_request buffer */
        mbox_request->buffer += HTCA_HEADER_LEN_MAX;
        return HTCA_ERROR;
    }

    return HTCA_OK;
}

/* Start a credit refresh cycle. Credits will appear in
 * end_point->tx_credits_available when this refresh completes.
 *
 * Called in the context of the work_task when we are unable
 * to send any more requests because credits are exhausted.
 * Also called from HIF completion's context when a credit
 * interrupt occurs.
 *
 * TBD: Consider HTCA v2 features: Quartz FW can send
 * in-band TX Credit hint
 * RX Length hint
 * interrupt status registers
 * as opportunistic trailer(s) on an RX message.
 * This increases code complexity but may reduce overhead
 * since we may reduce the number of explicit SDIO register
 * read operations which are relatively expensive "byte basis"
 * operations.
 */
int htca_credit_refresh_start(struct htca_endpoint *end_point)
{
    uint8_t end_point_id;
    int status;
    struct htca_target *target;
    struct htca_reg_request *reg_request;
    qbool_t already_in_progress;
    uint32_t address;

    htcadebug("%s: Enter\r\n", __FUNCTION__);

    INTR_BLOCK(end_point->tx_credit_lock);
    already_in_progress = end_point->tx_credit_refresh_in_progress;
    end_point->tx_credit_refresh_in_progress = true;
    end_point->tx_credits_to_reap = false;
    INTR_UNBLOCK(end_point->tx_credit_lock);

    if (already_in_progress) {
        return 0;
    }

    target = end_point->target;
    end_point_id = get_endpoint_id(end_point);
    htcadebug("%s: on endpoint %d\r\n", __FUNCTION__, end_point_id);

    INTR_BLOCK(target->reg_queue_lock);
    reg_request = (struct htca_reg_request *)htca_request_deq_head(&target->reg_free_queue);
    INTR_UNBLOCK(target->reg_queue_lock);

    INTR_BLOCK(target->outstanding_lock);
    target->outstanding_credit_refresh++;
    INTR_UNBLOCK(target->outstanding_lock);

    ASSERT(reg_request);
    ASSERT(reg_request->purpose == UNUSED_PURPOSE);

    reg_request->buffer = NULL;
    reg_request->length = 0;
    reg_request->purpose = CREDIT_REFRESH;
    reg_request->epid = end_point_id;

    address = get_reg_addr(TX_CREDIT_COUNTER_DECREMENT_REG, end_point_id);

    /* Note: reading many times FROM a FIXed register address, the
     * "atomic decrement address". The function htca_credit_refresh_compl
     * examines the results upon completion.
     */
    status = hif_read_write(target->hif_handle, address, reg_request->u.credit_dec_results,
                            HTCA_TX_CREDITS_REAP_MAX, HIF_RD_ASYNC_BYTE_FIX, reg_request);
    if (status == HIF_OK && reg_request->req.completion_cb) {
        reg_request->req.completion_cb((struct htca_request *)reg_request, HIF_OK);
        /* htca_credit_refresh_compl */
    } else if (status == HIF_PENDING) {
        /* Will complete later */
    } else {                    /* HIF error */
        ASSERT(0);
    }
    return 1;
}

/* Used during Configuration Negotiation at startup
 * to configure max message sizes for each endpoint.
 *
 * Returns true if all endpoints have been configured,
 * by this pass and/or all earlier calls. (Typically
 * there should be only a single call which enables
 * all endpoints at once.)
 *
 * Returns false if at least one endpoint has not
 * yet been configured.
 */
qbool_t htca_negotiate_config(struct htca_target * target)
{
    int status;
    struct htca_endpoint *end_point;
    uint32_t address;
    int enb_count = 0;
    int ep;

    htcadebug("%s: Enter\r\n", __FUNCTION__);

    /* The Target should have posted 1 credit to
     * each endpoint by the time we reach here.
     */
    for (ep = 0; ep < HTCA_NUM_MBOX; ep++) {
        end_point = &target->end_point[ep];
        if (end_point->enabled) {
            /* This endpoint was already enabled */
            enb_count++;
            continue;
        }
        htcadebug("%s: try epid=%d\r\n", __FUNCTION__, ep);

        address = get_reg_addr(TX_CREDIT_COUNTER_DECREMENT_REG, ep);
 again:
        end_point->tx_credits_available = 0;
        status =
            hif_read_write(target->hif_handle, address,
                           (uint8_t *) & end_point->tx_credits_available, 1, HIF_RD_SYNC_BYTE_FIX, NULL);
        if (status != HIF_OK) {
            htcadebug("%s: DBG: address=0x%08x status=%d\r\n", __FUNCTION__, address, status);
        }
        ASSERT(status == HIF_OK);

        if (!end_point->tx_credits_available) {
            /* not yet ready -- no credit posted.  Odd case. */
            htcadebug("%s: DBG: no negotiation credit yet for epid %d\r\n", __FUNCTION__, ep);
            goto again;
        } else {
            htcadebug("%s: DBG: %d credits available on epid %d\r\n",
                      __FUNCTION__, end_point->tx_credits_available, ep);
            if (end_point->tx_credits_available != 1) {
                goto again;
            }
        }

        ASSERT(end_point->tx_credits_available == 1);

        end_point->tx_credits_available--;

        /* TBD: Tacitly assumes LittleEndian Host.
         * This -- rather than an explicit Host interrupt -- is
         * what should trigger Target to fetch blocksize.
         */
        htcadebug("%s: good to go epid=%d\r\n", __FUNCTION__, ep);

        /* "Negotiate" the message size for this endpoint by writing
         * the maximum message size (and trigger EOM).
         */
        address = end_point->mbox_end_addr - sizeof(end_point->max_msg_sz);
        status = hif_read_write(target->hif_handle, address,
                                (uint8_t *) & end_point->max_msg_sz,
                                sizeof(end_point->max_msg_sz), HIF_WR_SYNC_BYTE_INC, NULL);
        ASSERT(status == HIF_OK);

        end_point->enabled = true;
        enb_count++;
    }

    htcadebug("%s: enb_count=%d\r\n", __FUNCTION__, enb_count);
    return (enb_count == HTCA_NUM_MBOX);
}
