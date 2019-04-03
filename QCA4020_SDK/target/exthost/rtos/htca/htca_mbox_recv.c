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

/* If there is data available to read on the specified mailbox,
 * pull a Mailbox Recv Request off of the PendingRecv queue
 * and request HIF to pull data from the mailbox into the
 * request's recv buffer.
 *
 * If we are not aware of data waiting on the endpoint, simply
 * return. Note that our awareness is based on slightly stale
 * data from Quartz registers. Upper layers insure that we are
 * called shortly after data becomes available on an endpoint.
 *
 * If we exhaust receive buffers, disable the mailbox's interrupt
 * until additional buffers are available.
 *
 * Returns 0 if no request was sent to HIF
 * returns 1 if at least one request was sent to HIF
 */
int htca_manage_pending_recvs(struct htca_target *target, int epid)
{
    struct htca_endpoint *end_point;
    struct htca_request_queue *recv_queue;
    struct htca_mbox_request *mbox_request;
    uint32_t rx_frame_length;
    int work_done = 0;

    if (target->pending_recv_mask & (1 << epid)) {
        /* Receive operation is already in progress on this endpoint */
        return 0;
    }

    end_point = &target->end_point[epid];

    /* Hand off requests as long as we have both
     * something to recv into
     * data waiting to be read on the mailbox
     */

    /* rx_frame_length of 0 --> nothing waiting; otherwise, it's
     * the length of data waiting to be read, NOT including
     * HTCA header nor block padding.
     */
    rx_frame_length = end_point->rx_frame_length;

    recv_queue = &end_point->recv_pending_queue;
    if (HTCA_IS_QUEUE_EMPTY(recv_queue)) {
        htcadebug("%s: no recv buff for ep#%d\r\n", __FUNCTION__, epid);
        /* Not interested in rxdata interrupts
         * since we have no recv buffers.
         */
        target->enb.int_status_enb &= ~(1 << epid);

        if (rx_frame_length) {
            struct htca_event_info event_info;

            htcadebug("%s: frame waiting (%d): %d\r\n", __FUNCTION__, epid, rx_frame_length);
            /* No buffer ready to receive but data
             * is ready. Alert the caller with a
             * DATA_AVAILABLE event.
             */
            if (!end_point->rx_data_alerted) {
                end_point->rx_data_alerted = true;

                htca_frame_event(&event_info, NULL, rx_frame_length, 0, HTCA_OK, NULL);

                htca_dispatch_event(target, epid, HTCA_EVENT_DATA_AVAILABLE, &event_info);
            }
        }
        return 0;
    }

    /* We have recv buffers available, so we are
     * interested in rxdata interrupts.
     */
    target->enb.int_status_enb |= (1 << epid);
    end_point->rx_data_alerted = false;

    if (rx_frame_length == 0) {
        htcadebug("%s: buffer available (%d), but no data to recv\r\n", __FUNCTION__, epid);
        /* We have a buffer but there's nothing
         * available on the Target to read.
         */
        return 0;
    }

    /* There is rxdata waiting and a buffer to read it into */

    /* Pull the request buffer off the Pending Recv Queue */
    INTR_BLOCK(end_point->mbox_queue_lock);
    mbox_request = (struct htca_mbox_request *)htca_request_deq_head(recv_queue);
    INTR_UNBLOCK(end_point->mbox_queue_lock);

    if (!mbox_request) {
        goto done;
    }

    htcadebug("%s: ep#%d receiving frame: %d bytes\r\n", __FUNCTION__, epid, rx_frame_length);

    INTR_BLOCK(target->pending_op_lock);
    target->pending_recv_mask |= (1 << epid);
    INTR_UNBLOCK(target->pending_op_lock);

    INTR_BLOCK(target->outstanding_lock);
    target->outstanding_data++;
    INTR_UNBLOCK(target->outstanding_lock);

    /* Hand off this Mbox Recv request to HIF */
    mbox_request->actual_length = rx_frame_length;
    if (htca_recv_request_to_hif(end_point, mbox_request) == HTCA_ERROR) {

        ASSERT(0);              /* should never fail */
#if 0

        struct htca_event_info event_info;

        /* TBD: Could requeue this at the HEAD of the
         * pending recv queue. Try again later?
         */

        /* Frame an event to send to caller */
        htca_frame_event(&event_info, mbox_request->buffer,
                         mbox_request->buffer_length,
                         mbox_request->actual_length, HTCA_ECANCELED, mbox_request->cookie);

        /* Free the Mailbox request */
        INTR_BLOCK(end_point->mbox_queue_lock);
        htca_request_enq_tail(&end_point->recv_free_queue, (struct htca_request *)mbox_request);
        INTR_UNBLOCK(end_point->mbox_queue_lock);

        INTR_BLOCK(target->pending_op_lock);
        target->pending_recv_mask &= ~(1 << epid);
        htca_idle_poke(target);
        INTR_UNBLOCK(target->pending_op_lock);

        INTR_BLOCK(target->outstanding_lock);
        target->outstanding_data--;
        INTR_UNBLOCK(target->outstanding_lock);

        htca_dispatch_event(target, epid, HTCA_EVENT_BUFFER_RECEIVED, &event_info);
        htca_idle_poke(target);
        goto done;
#endif
    } else {
        work_done = 1;
    }

 done:
    return work_done;
}

int htca_recv_request_to_hif(struct htca_endpoint *end_point, struct htca_mbox_request *mbox_request)
{
    int status;
    struct htca_target *target;
    uint32_t padded_length;
    uint32_t mbox_address;
    uint32_t req_type;

    target = end_point->target;

    /* Adjust length for power-of-2 block size */
    padded_length = htca_round_up(mbox_request->actual_length + HTCA_HEADER_LEN_MAX, end_point->block_size);

    req_type = (end_point->block_size > 1) ? HIF_RD_ASYNC_BLOCK_INC : HIF_RD_ASYNC_BYTE_INC;

    mbox_address = end_point->mbox_start_addr;

    status = hif_read_write(target->hif_handle, mbox_address,
                            &mbox_request->buffer
                            [HTCA_HEADER_LEN_MAX - HTCA_HEADER_LEN], padded_length, req_type, mbox_request);

    if (status == HIF_OK && mbox_request->req.completion_cb) {
        mbox_request->req.completion_cb((struct htca_request *)mbox_request, HTCA_OK);
        /* htca_recv_compl */
    } else if (status == HIF_PENDING) {
        /* Will complete later */
    } else {                    /* HIF error */
        return HTCA_ERROR;
    }

    return HTCA_OK;
}
