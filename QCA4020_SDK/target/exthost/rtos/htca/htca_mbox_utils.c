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

/* HTCA utility routines  */

/* Invoked when shutting down */
void htca_mbox_queue_flush(struct htca_endpoint *end_point,
                           struct htca_request_queue *pending_queue,
                           struct htca_request_queue *free_queue, uint8_t event_id)
{
    struct htca_event_info event_info;
    uint8_t end_point_id;
    struct htca_target *target;
    struct htca_mbox_request *mbox_request;

    target = end_point->target;
    end_point_id = get_endpoint_id(end_point);

    INTR_BLOCK(end_point->mbox_queue_lock);
    for (;;) {
        mbox_request = (struct htca_mbox_request *)htca_request_deq_head(pending_queue);
        INTR_UNBLOCK(end_point->mbox_queue_lock);

        if (!mbox_request) {
            break;
        }

        htca_frame_event(&event_info, mbox_request->buffer,
                         mbox_request->buffer_length, 0, HTCA_ECANCELED, mbox_request->cookie);

        htca_dispatch_event(target, end_point_id, event_id, &event_info);

        /* Recycle the request */
        INTR_BLOCK(end_point->mbox_queue_lock);
        htca_request_enq_tail(free_queue, (struct htca_request *)mbox_request);
    }
    INTR_UNBLOCK(end_point->mbox_queue_lock);
}

struct htca_target *htca_target_instance(int i)
{
    return htca_target_list[i];
}

void htca_target_instance_add(struct htca_target *target)
{
    int i;

    for (i = 0; i < HTCA_NUM_DEVICES_MAX; i++) {
        if (!htca_target_list[i]) {
            htca_target_list[i] = target;
            break;
        }
    }
    ASSERT(i < HTCA_NUM_DEVICES_MAX);
}

void htca_target_instance_remove(struct htca_target *target)
{
    int i;

    for (i = 0; i < HTCA_NUM_DEVICES_MAX; i++) {
        if (htca_target_list[i] == target) {
            htca_target_list[i] = NULL;
            break;
        }
    }
    ASSERT(i < HTCA_NUM_DEVICES_MAX);
}

/*
 * See whether a queue is empty:
 *   0-->something is on the queue
 *   1-->queue is empty
 * Caller must handle any locking required.
 */
int htca_request_queue_empty(struct htca_request_queue *queue)
{
    if (queue->tail) {
        return 0;
    } else {
        return 1;
    }
}

/* Add a request to the tail of a queue.
 * Caller must handle any locking required.
 */
void htca_request_enq_tail(struct htca_request_queue *queue, struct htca_request *req)
{
    req->next = NULL;

    if (queue->tail) {
        queue->tail->next = (void *)req;
    } else {
        queue->head = req;
    }

    queue->tail = req;
}

/* Remove a request from the start of a queue.
 * Caller must handle any locking required.
 * TBD: If cannot allocate from FREE queue, caller may add more elements.
 */
struct htca_request *htca_request_deq_head(struct htca_request_queue *queue)
{
    struct htca_request *req;

    req = queue->head;
    if (!req) {
        return NULL;
    }

    queue->head = req->next;
    if (!queue->head) {
        queue->tail = NULL;
    }
    req->next = NULL;

    return req;
}

/* Start a Register Refresh cycle.
 *
 * Submits a request to fetch ALL relevant registers from Target.
 * When this completes, we'll take actions based on the new
 * register values.
 */
void htca_register_refresh_start(struct htca_target *target, enum htca_req_purpose purpose)
{
    int status;
    struct htca_reg_request *reg_request;
    uint32_t address;

    htcadebug("%s: Enter\r\n", __FUNCTION__);
    INTR_BLOCK(target->reg_queue_lock);
    reg_request = (struct htca_reg_request *)htca_request_deq_head(&target->reg_free_queue);
    INTR_UNBLOCK(target->reg_queue_lock);

    INTR_BLOCK(target->outstanding_lock);
    target->outstanding_register_refresh++;
    INTR_UNBLOCK(target->outstanding_lock);

    ASSERT(reg_request);
    ASSERT(reg_request->purpose == UNUSED_PURPOSE);

    reg_request->buffer = (uint8_t *) & reg_request->u.reg_table;
    reg_request->length = sizeof(reg_request->u.reg_table);
    reg_request->purpose = purpose;
    reg_request->epid = 0;      /* not used */

    address = get_reg_addr(ALL_STATUS_REG, ENDPOINT_UNUSED);
    status = hif_read_write(target->hif_handle, address,
                            &reg_request->u.reg_table,
                            sizeof(reg_request->u.reg_table), HIF_RD_ASYNC_BYTE_INC, reg_request);
    if (status == HIF_OK && reg_request->req.completion_cb) {
        reg_request->req.completion_cb((struct htca_request *)reg_request, HIF_OK);
        /* htca_register_refresh_compl */
    } else if (status == HIF_PENDING) {
        /* Will complete later */
    } else {                    /* HIF error */
        ASSERT(0);
    }
}
