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

/* Implementation of Host Target Communication
 * API v1 and HTCA Protocol v1
 * over Qualcomm QCA mailbox-based SDIO/SPI interconnects.
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "qapi/qurt_mutex.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_thread.h"
#include "qapi/qapi_types.h"
#include "bsp/malloc.h"

#include "common_defs.h"
#include "hif/hif.h"
#include "htca.h"
#include "htca_mbox_internal.h"

struct htca_target *htca_target_list[HTCA_NUM_DEVICES_MAX];

/* Single thread module initialization, module shutdown,
 * target start and target stop.
 */
static qurt_mutex_t htca_startup_mutex;
static qbool_t htca_initialized;

/* Initialize the HTCA software module.
 * Typically invoked exactly once.
 */
int htca_init(void)
{
    struct cbs_from_os callbacks;

    qurt_mutex_create(&htca_startup_mutex);
    qurt_mutex_lock(&htca_startup_mutex);

    ASSERT(!htca_initialized);
    htca_initialized = true;

    htca_event_table_init();

    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.dev_inserted_hdl = htca_target_inserted_handler;
    callbacks.dev_removed_hdl = htca_target_removed_handler;
    hif_init(&callbacks);

    qurt_mutex_unlock(&htca_startup_mutex);

    return HTCA_OK;
}

/* Shutdown the entire module and free all module data.
 * Inverse of htca_init.
 *
 * May be invoked only after all Targets are stopped.
 */
void htca_shutdown(void)
{
    int i;

    qurt_mutex_lock(&htca_startup_mutex);

    if (!htca_initialized) {
        qurt_mutex_unlock(&htca_startup_mutex);
        return;                 /* Not initialized, so nothing to shut down */
    }

    for (i = 0; i < HTCA_NUM_DEVICES_MAX; i++) {
        if (htca_target_instance(i)) {
            /* One or more Targets are still active --
             * cannot shutdown software.
             */
            qurt_mutex_unlock(&htca_startup_mutex);
            ASSERT(0);
            return;
        }
    }

    hif_shutdown_device(NULL);  /* Tell HIF that we're all done */
    htca_initialized = false;

    qurt_mutex_unlock(&htca_startup_mutex);
    qurt_mutex_delete(&htca_startup_mutex);
}

/* Start a Target. This typically happens once per Target after
 * the module has been initialized and a Target is powered on.
 *
 * When a Target starts, it posts a single credit to each mailbox
 * and it enters "HTCA configuration". During configuration
 * negotiation, block sizes for each HTCA endpoint are established
 * that both Host and Target agree. Once this is complete, the
 * Target starts normal operation so it can send/receive.
 */
int htca_start(void *targ)
{
    int status;
    uint32_t address;
    struct htca_target *target = (struct htca_target *)targ;

    qurt_mutex_lock(&htca_startup_mutex);

    if (!htca_initialized) {
        qurt_mutex_unlock(&htca_startup_mutex);
        return HTCA_ERROR;
    }

    /* Unmask Host controller interrupts associated with this Target */
    hif_unmask_interrupt(target->hif_handle);
    target->is_host_intr_enabled = 1;

    /* Enable all interrupts of interest on the Target. */

    target->enb.int_status_enb = INT_STATUS_ENABLE_ERROR_SET(0x01) |
#if 0                           /* Not currently used -- ignore */
        INT_STATUS_ENABLE_CPU_SET(0x01) |
#endif
        INT_STATUS_ENABLE_COUNTER_SET(0x01) | INT_STATUS_ENABLE_MBOX_DATA_SET(0x0F);

    target->enb.cpu_int_status_enb = CPU_INT_STATUS_ENABLE_BIT_SET(0x00);

    target->enb.err_status_enb = ERROR_STATUS_ENABLE_RX_UNDERFLOW_SET(0x01) | ERROR_STATUS_ENABLE_TX_OVERFLOW_SET(0x01);

    target->enb.counter_int_status_enb = COUNTER_INT_STATUS_ENABLE_BIT_SET(0xFF);

    /* Commit interrupt register values to Target HW. */
    address = get_reg_addr(INTR_ENB_REG, ENDPOINT_UNUSED);
    status = hif_read_write(target->hif_handle, address, &target->enb, sizeof(target->enb), HIF_WR_SYNC_BYTE_INC, NULL);
    if (status != HIF_OK) {
        _htca_stop(target);
        qurt_mutex_unlock(&htca_startup_mutex);
        return HTCA_ERROR;
    }

    /* At this point, we're waiting for the Target to post
     * 1 credit to each mailbox. This allows us to begin
     * configuration negotiation. We should see an interrupt
     * as soon as the first credit is posted. The remaining
     * credits should be posted almost immediately after.
     */

    /* Wait indefinitely until configuration negotiation with
     * the Target completes and the Target tells us it is ready to go.
     */
    qurt_signal_wait(&target->target_init_wait, HTCA_TARGET_READY_FLAG, QURT_SIGNAL_ATTR_CLEAR_MASK);
    status = HTCA_OK;

    qurt_mutex_unlock(&htca_startup_mutex);
    return status;
}

void _htca_stop(struct htca_target *target)
{
    uint8_t ep;
    struct htca_endpoint *end_point;
    uint32_t address;

    htcadebug("%s: Enter\r\n", __FUNCTION__);

    /* Note: htca_startup_mutex must be held on entry */
    if (!htca_initialized) {
        return;
    }

    htca_work_task_stop(target);

    /* Disable interrupts at source, on Target */
    target->enb.int_status_enb = 0;
    target->enb.cpu_int_status_enb = 0;
    target->enb.err_status_enb = 0;
    target->enb.counter_int_status_enb = 0;

    address = get_reg_addr(INTR_ENB_REG, ENDPOINT_UNUSED);

    /* Try to disable all interrupts on the Target. */
    (void)hif_read_write(target->hif_handle, address, &target->enb, sizeof(target->enb), HIF_WR_SYNC_BYTE_INC, NULL);

    /* Disable Host controller interrupts */
    hif_mask_interrupt(target->hif_handle);
    target->is_host_intr_enabled = 0;

    /* Flush all the queues and return the buffers to their owner */
    for (ep = 0; ep < HTCA_NUM_MBOX; ep++) {
        end_point = &target->end_point[ep];

        INTR_BLOCK(end_point->tx_credit_lock);
        end_point->tx_credits_available = 0;
        INTR_UNBLOCK(end_point->tx_credit_lock);

        end_point->enabled = false;

        /* Flush the Pending Receive Queue */
        htca_mbox_queue_flush(end_point, &end_point->recv_pending_queue,
                              &end_point->recv_free_queue, HTCA_EVENT_BUFFER_RECEIVED);

        /* Flush the Pending Send Queue */
        htca_mbox_queue_flush(end_point, &end_point->send_pending_queue,
                              &end_point->send_free_queue, HTCA_EVENT_BUFFER_SENT);
    }

    target->ready = false;

    hif_detach(target->hif_handle);

    /* Remove this Target from the global list */
    htca_target_instance_remove(target);

    /* Free target memory */
    free(target);
}

void htca_stop(void *tar)
{
    struct htca_target *target = (struct htca_target *)tar;

    htca_work_task_stop(target);
    htca_compl_task_stop(target);

    qurt_mutex_lock(&htca_startup_mutex);
    _htca_stop(target);
    qurt_mutex_unlock(&htca_startup_mutex);
}

/* Provides an interface for the caller to register for
 * various events supported by the HTCA module.
 */
int htca_event_reg(void *tar, uint8_t end_point_id, uint8_t event_id, htca_event_handler event_handler, void *param)
{
    int status;
    struct htca_endpoint *end_point;
    struct htca_event_info event_info;
    struct htca_target *target = (struct htca_target *)tar;

    /* Register a new handler BEFORE dispatching events.
     * UNregister a handler AFTER dispatching events.
     */
    if (event_handler) {
        /* Register a new event handler */

        status = htca_add_to_event_table(target, end_point_id, event_id, event_handler, param);
        if (status != HTCA_OK) {
            return status;      /* Fail to register handler */
        }
    }

    /* Handle events associated with this handler */
    switch (event_id) {
    case HTCA_EVENT_TARGET_AVAILABLE:
        if (event_handler) {
            struct htca_target *targ;
            int i;

            /* Dispatch a Target Available event for all Targets
             * that are already present.
             */
            for (i = 0; i < HTCA_NUM_DEVICES_MAX; i++) {
                targ = htca_target_list[i];
                if (targ) {
                    size_t size = hif_get_device_size();

                    htca_frame_event(&event_info, (uint8_t *) targ->hif_handle, size, size, HTCA_OK, NULL);

                    htca_dispatch_event(targ, ENDPOINT_UNUSED, HTCA_EVENT_TARGET_AVAILABLE, &event_info);
                }
            }
        }
        break;

    case HTCA_EVENT_TARGET_UNAVAILABLE:
        break;

    case HTCA_EVENT_BUFFER_RECEIVED:
        if (!event_handler) {
            /* Flush the Pending Recv queue before unregistering
             * the event handler.
             */
            end_point = &target->end_point[end_point_id];
            htca_mbox_queue_flush(end_point,
                                  &end_point->recv_pending_queue,
                                  &end_point->recv_free_queue, HTCA_EVENT_BUFFER_RECEIVED);
        }
        break;

    case HTCA_EVENT_BUFFER_SENT:
        if (!event_handler) {
            /* Flush the Pending Send queue before unregistering
             * the event handler.
             */
            end_point = &target->end_point[end_point_id];
            htca_mbox_queue_flush(end_point,
                                  &end_point->send_pending_queue, &end_point->send_free_queue, HTCA_EVENT_BUFFER_SENT);
        }
        break;

    case HTCA_EVENT_DATA_AVAILABLE:
        /* We could dispatch a data available event. Instead,
         * we require users to register this event handler
         * before posting receive buffers.
         */
        break;

    default:
        return HTCA_EINVAL;     /* unknown event? */
    }

    if (!event_handler) {
        /* Unregister an event handler */
        status = htca_remove_from_event_table(target, end_point_id, event_id);
        if (status != HTCA_OK) {
            return status;
        }
    }

    return HTCA_OK;
}

/* Enqueue to the endpoint's recv_pending_queue an empty buffer
 * which will receive data from the Target.
 */
int htca_buffer_receive(void *tar, uint8_t end_point_id, uint8_t * buffer, uint32_t length, void *cookie)
{
    struct htca_endpoint *end_point;
    struct htca_mbox_request *mbox_request;
    struct htca_event_table_element *ev;
    struct htca_target *target = (struct htca_target *)tar;
    int was_empty;

    end_point = &target->end_point[end_point_id];

    if (!end_point->enabled) {
        return HTCA_ERROR;
    }

    /* Length must be a multiple of block_size.
     * (Ideally, length should match the largest message that can be sent
     * over this endpoint, including HTCA header, rounded up to blocksize.)
     */
    if (length % end_point->block_size) {
        return HTCA_EINVAL;
    }

    if (length > HTCA_MESSAGE_SIZE_MAX) {
        return HTCA_EINVAL;
    }

    if (length < HTCA_HEADER_LEN_MAX) {
        return HTCA_EINVAL;
    }

    ev = htca_event_id_to_event(target, end_point_id, HTCA_EVENT_BUFFER_RECEIVED);
    if (!ev->handler) {
        /* In order to use this API, caller must
         * register an event handler for HTCA_EVENT_BUFFER_RECEIVED.
         */
        return HTCA_ERROR;
    }

    INTR_BLOCK(end_point->mbox_queue_lock);
    mbox_request = (struct htca_mbox_request *)htca_request_deq_head(&end_point->recv_free_queue);
    INTR_UNBLOCK(end_point->mbox_queue_lock);
    if (!mbox_request) {
        return HTCA_ENOMEM;
    }

    ASSERT(mbox_request->req.target == target);

    mbox_request->buffer = buffer;
    /* includes space for HTCA header */
    mbox_request->buffer_length = length;
    /* filled in after message is received */
    mbox_request->actual_length = 0;
    mbox_request->end_point = end_point;
    mbox_request->cookie = cookie;

    INTR_BLOCK(end_point->mbox_queue_lock);
    was_empty = htca_request_queue_empty(&end_point->recv_pending_queue);
    htca_request_enq_tail(&end_point->recv_pending_queue, (struct htca_request *)mbox_request);

    if (was_empty) {
        /* Alert the work_task that there may be work to do */
        htca_work_task_poke(target);
    }
    INTR_UNBLOCK(end_point->mbox_queue_lock);

    return HTCA_OK;
}

/* Enqueue a buffer to be sent to the Target.
 *
 * Supplied buffer must be preceded by HTCA_HEADER_LEN_MAX bytes for the
 * HTCA header (of which HTCA_HEADER_LEN bytes are actually used, and the
 * remaining are padding).
 *
 * Must be followed with sufficient space for block-size padding.
 *
 * Example:
 * To send a 10B message over an endpoint that uses 64B blocks, caller
 * specifies length=10. HTCA adds HTCA_HEADER_LEN_MAX bytes just before
 * buffer, consisting of HTCA_HEADER_LEN header bytes followed by
 * HTCA_HEADER_LEN_MAX-HTCA_HEADER_LEN pad bytes. HTC sends blockSize
 * bytes starting at buffer-HTCA_HEADER_LEN_MAX.
 */
int htca_buffer_send(void *tar, uint8_t end_point_id, uint8_t * buffer, uint32_t length, void *cookie)
{
    struct htca_endpoint *end_point;
    struct htca_mbox_request *mbox_request;
    struct htca_event_table_element *ev;
    struct htca_target *target = (struct htca_target *)tar;
    int was_empty;

    end_point = &target->end_point[end_point_id];

    if (!end_point->enabled) {
        return HTCA_ERROR;
    }

    if (length + HTCA_HEADER_LEN_MAX > HTCA_MESSAGE_SIZE_MAX) {
        return HTCA_EINVAL;
    }

    ev = htca_event_id_to_event(target, end_point_id, HTCA_EVENT_BUFFER_SENT);
    if (!ev->handler) {
        /* In order to use this API, caller must
         * register an event handler for HTCA_EVENT_BUFFER_SENT.
         */
        return HTCA_ERROR;
    }

    INTR_BLOCK(end_point->mbox_queue_lock);
    mbox_request = (struct htca_mbox_request *)htca_request_deq_head(&end_point->send_free_queue);
    INTR_UNBLOCK(end_point->mbox_queue_lock);
    if (!mbox_request) {
        return HTCA_ENOMEM;
    }

    /* Buffer will be adjusted by HTCA_HEADER_LEN later, in
     * htca_send_request_to_hif.
     */
    mbox_request->buffer = buffer;
    mbox_request->buffer_length = length;
    mbox_request->actual_length = length;
    mbox_request->end_point = end_point;
    mbox_request->cookie = cookie;

    INTR_BLOCK(end_point->mbox_queue_lock);
    was_empty = htca_request_queue_empty(&end_point->send_pending_queue);
    htca_request_enq_tail(&end_point->send_pending_queue, (struct htca_request *)mbox_request);

    if (was_empty) {
        /* Alert the work_task that there may be work to do */
        htca_work_task_poke(target);
    }
    INTR_UNBLOCK(end_point->mbox_queue_lock);

    return HTCA_OK;
}
