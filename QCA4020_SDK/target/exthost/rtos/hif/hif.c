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

#include "qapi/qurt_mutex.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_thread.h"
#include "qapi/qapi_types.h"
#include "malloc.h"
#include "common_defs.h"
#include "hif/hif.h"
#include "transport/transport.h"

#include "hif_internal.h"

// #define DEBUG
// #define DEBUG_VERBOSE
// #define CONFIG_HIF_LOG

#if defined(DEBUG)
extern void PAL_CONSOLE_PRINTF(const char *format, ...);
#define hifdebug PAL_CONSOLE_PRINTF
#else
#define hifdebug(args...)
#endif

#include "qapi/qurt_timer.h"

#define MAX_HIF_DEVICES 2

int hif_device_inserted(void *tdev, qbool_t hotplug);
int hif_device_removed(void *tdev, qbool_t hotplug);
void hif_stop_hif_task(struct hif_device *device);
struct bus_request *hif_allocate_bus_request(void *device);
void hif_free_bus_request(struct hif_device *device, struct bus_request *busrequest);
void hif_add_to_req_list(struct hif_device *device, struct bus_request *busrequest);
struct hif_device *get_hif_device(struct trans_device *tdev);
void *add_hif_device(struct trans_device *tdev);
int hif_enable_func(struct hif_device *device, struct trans_device *tdev);
void del_hif_device(struct hif_device *device);

/* Callbacks to HIF caller (upper layers) */
struct cbs_from_os hif_callbacks;

struct hif_device *hif_devices[MAX_HIF_DEVICES];

int hif_init(struct cbs_from_os *callbacks)
{
    hif_callbacks_t cbs;

    hifdebug("%s: Enter\r\n", __FUNCTION__);
    if (!callbacks) {
        return HIF_ERROR;
    }

    hif_callbacks = *callbacks; /* structure copy */
    hifdebug("%s: dev_inserted_hdl is at 0x%p\r\n", __FUNCTION__, hif_callbacks.dev_inserted_hdl);

    cbs.hif_trans_device_inserted = hif_device_inserted;
    cbs.hif_trans_device_removed = hif_device_removed;

    hifdebug("%s: calling trans_init\r\n", __FUNCTION__);
    if (trans_init(&cbs)) {
        return HIF_ERROR;
    }
    hifdebug("%s: returned from trans_init...OK\r\n", __FUNCTION__);

    return HIF_OK;
}

#if defined(CONFIG_HIF_LOG)
extern uint64 timetick_get64(void);
#define HIF_LOG_ENTRY_COUNT 256

struct hif_log_s {
    uint64 start_time;
    uint64 stop_time;
    uint32_t address;
    uint32_t length;
    uint32_t request;
} hif_log_entry[HIF_LOG_ENTRY_COUNT];
unsigned int hif_log_index;

void hif_log(uint64 start_time, uint64 stop_time, uint32_t address, uint32_t length, uint32_t request)
{
    struct hif_log_s *log;
    unsigned long intrstate;

    INTR_BLOCK(intrstate);
    log = &hif_log_entry[hif_log_index];
    log->start_time = start_time;
    log->stop_time = stop_time;
    log->address = address;
    log->length = length;
    log->request = request;
    hif_log_index = (hif_log_index + 1) % HIF_LOG_ENTRY_COUNT;
    INTR_UNBLOCK(intrstate);
}
#endif

int __hif_read_write(struct hif_device *device, uint32_t address,
                     uint8_t * buffer, uint32_t length, uint32_t request, void *context)
{
    int status = HIF_OK;
    int ret = 0;
    io_mode_t iomode;
#if defined(CONFIG_HIF_LOG)
    uint64 start_time, stop_time;
#endif

    if (!device || !device->tdev) {
        return HIF_ERROR;
    }

    if (!buffer) {
        return HIF_EINVAL;
    }

    if (length == 0) {
        return HIF_EINVAL;
    }
#if defined(CONFIG_HIF_LOG)
    start_time = timetick_get64();
#endif

    do {
        if (!(request & HIF_EXTENDED_IO)) {
            status = HIF_EINVAL;
            break;
        }

        if (request & HIF_BLOCK_BASIS) {
            ASSERT((length & (HIF_MBOX_BLOCK_SIZE - 1)) == 0);
        } else if (request & HIF_BYTE_BASIS) {
        } else {
            status = HIF_EINVAL;
            break;
        }

        if ((address >= HIF_HOST_CONTROL_REG_START_ADDR) && (address <= HIF_HOST_CONTROL_REG_END_ADDR)) {
            iomode = TRANSPORT_IO_FLAG_HCR_REGISTER;    /* Register range */
        } else {
            iomode = TRANSPORT_IO_FLAG_MBOXFIFO;        /* MBOX FIFO range */
        }

        if (request & HIF_FIXED_ADDRESS) {
            iomode |= TRANSPORT_IO_FLAG_NONINCR;
        }

        if (request & HIF_WRITE) {
            ret = trans_write_data(device->tdev, iomode, address, buffer, length);
        } else if (request & HIF_READ) {
            ret = trans_read_data(device->tdev, iomode, address, buffer, length);
        } else {
            status = HIF_EINVAL;        /* Neither read nor write */
            break;
        }

        if (ret) {
            hifdebug("%s: transport read/write returns error (%d)\r\n", __FUNCTION__, ret);
            status = HIF_ETRANSPORT;
        }
    }
    while (false);

#if defined(CONFIG_HIF_LOG)
    stop_time = timetick_get64();
    hif_log(start_time, stop_time, address, length, request);
#endif

    return status;
}

/* Add busrequest to tail of sdio_request request list */
void hif_add_to_req_list(struct hif_device *device, struct bus_request *busrequest)
{
    unsigned long intrstate;
    busrequest->next = NULL;

    INTR_BLOCK(intrstate);
    if (device->req_qhead) {
        device->req_qtail->next = (void *)busrequest;
    } else {
        device->req_qhead = busrequest;
    }
    device->req_qtail = busrequest;
    INTR_UNBLOCK(intrstate);
}

/* Queue a read/write request and optionally wait for it to complete. */
int hif_read_write(void *hif_device, uint32_t address, void *buffer, uint32_t length, uint32_t req_type, void *context)
{
    struct bus_request *busrequest;
    int status;
    struct hif_device *device = (struct hif_device *)hif_device;

    if (!device || !device->tdev) {
        return HIF_ERROR;
    }

    if (!(req_type & HIF_ASYNCHRONOUS) && !(req_type & HIF_SYNCHRONOUS)) {
        return HIF_EINVAL;
    }

    /* Serialize all requests through the reqlist and HIFtask */
    busrequest = hif_allocate_bus_request(device);
    if (!busrequest) {
        return HIF_ERROR;
    }

    /* TBD: caller may pass buffers ON THE STACK, especially 4 Byte buffers.
     * If this is a problem on some platforms/drivers, this is one
     * reasonable
     * place to handle it. If poentially using DMA
     * reject large buffers on stack
     * copy 4B buffers allow register writes (no DMA)
     */

    busrequest->address = address;
    busrequest->buffer = buffer;
    busrequest->length = length;
    busrequest->req_type = req_type;
    busrequest->context = context;

    hif_add_to_req_list(device, busrequest);

    /* Notify HIF task */
    qurt_signal_set(&device->hif_wait, HIF_SIGNAL_REQ_PENDING);

    if (req_type & HIF_ASYNCHRONOUS) {
        return HIF_PENDING;
    }

    /* Synchronous request -- wait for completion. */
    qurt_signal_wait(&busrequest->comp_req, 1, QURT_SIGNAL_ATTR_CLEAR_MASK);
    status = busrequest->status;
    hif_free_bus_request(device, busrequest);
    return status;
}

/* add_to_completion_list() - Queue a completed request
 * @device:    context to the hif device.
 * @comple: SDIO bus access request.
 *
 * This function adds an sdio bus access request to the
 * completion list.
 *
 * Return: No return.
 */
void add_to_completion_list(struct hif_device *device, struct bus_request *comple)
{
    unsigned long intrstate;
    comple->next = NULL;

    INTR_BLOCK(intrstate);
    if (device->compl_qhead) {
        device->compl_qtail->next = (void *)comple;
    } else {
        device->compl_qhead = comple;
    }

    device->compl_qtail = comple;
    INTR_UNBLOCK(intrstate);
}

/* process_completion_list() - Remove completed requests from
 * the completion list, and invoke the corresponding callbacks.
 *
 * @device:  HIF device handle.
 *
 * Function to clean the completion list.
 *
 * Return: No
 */
void process_completion_list(struct hif_device *device)
{
    struct bus_request *next_comple;
    struct bus_request *request;
    unsigned long intrstate;

    /* Pull the entire chain of completions from the list */
    INTR_BLOCK(intrstate);
    request = device->compl_qhead;
    device->compl_qhead = NULL;
    device->compl_qtail = NULL;
    INTR_UNBLOCK(intrstate);

    while (request) {
        int status;
        void *context;

        hifdebug("%s: HIF top of loop\r\n", __FUNCTION__);
        next_comple = (struct bus_request *)request->next;

        status = request->status;
        context = request->context;
        hif_free_bus_request(device, request);
        device->cbs_from_hif.rw_completion_hdl(context, status);

        request = next_comple;
    }
}

/* completion_task() - Thread to process request completions
 *
 * @param:   context to the hif device.
 *
 * Completed asynchronous requests are added to a completion
 * queue where they are processed by this task. This serves
 * multiple purposes:
 * -minimizes processing by the HIFTask, which allows
 *  that task to keep SDIO busy
 * -allows request processing to be parallelized on
 *  multiprocessor systems
 * -provides a suspendable context for use by the
 *  caller's callback function, though this should
 *  not be abused since it will cause requests to
 *  sit on the completion queue (which makes us
 *  more likely to exhaust free requests).
 *
 * Return: 0 thread exits
 */
void completion_task(void *param)
{
    struct hif_device *device;

    device = (struct hif_device *)param;

    for (;;) {
        uint32 sigs;

        hifdebug("%s: HIF top of loop\r\n", __FUNCTION__);
        sigs = qurt_signal_wait(&device->completion_wait,
                                HIF_SIGNAL_COMPL_PENDING | HIF_SIGNAL_COMPL_TASK_EXIT,
                                QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);
        hifdebug("%s: after qurt_signal_wait, sigs=0x%x\r\n", __FUNCTION__, sigs);

        if (sigs & HIF_SIGNAL_COMPL_TASK_EXIT) {
            break;
        }

        ASSERT(sigs & HIF_SIGNAL_COMPL_PENDING);
        process_completion_list(device);
    }

    /* Process any remaining completions.
     * This task should not be shut down
     * until after all requests are stopped.
     */
    process_completion_list(device);
    qurt_signal_set(&device->completion_wait, HIF_SIGNAL_COMPL_TASK_EXIT_DONE);
}

/* hif_request_complete() - Completion processing after a request
 * is processed.
 *
 * @device:    device handle.
 * @request:   SIDO bus access request.
 *
 * All completed requests are queued onto a completion list
 * which is processed by complete_task.
 *
 * Return: None.
 */
void hif_request_complete(struct hif_device *device, struct bus_request *request)
{
    add_to_completion_list(device, request);
    qurt_signal_set(&device->completion_wait, HIF_SIGNAL_COMPL_PENDING);
}

/* hif_stop_completion_thread() - Destroy the completion task
 * @device: device handle.
 *
 * This function will destroy the completion thread.
 *
 * Return: None.
 */
void hif_stop_completion_thread(struct hif_device *device)
{
    if (device->completion_task) {
        qurt_signal_set(&device->completion_wait, HIF_SIGNAL_COMPL_TASK_EXIT);
        qurt_signal_wait(&device->completion_wait, HIF_SIGNAL_COMPL_TASK_EXIT_DONE,
                         QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);
        device->completion_task = 0;
    }
}

/* This task tries to keep the SDIO bus as busy as it
 * can. It pulls both synchronous and asynchronous requests
 * from the request queue and it uses the underlying sdtransport
 * module to make them happen.
 *
 * Requests may be one of
 *   synchronous (a thread is suspended until it completes)
 *   asynchronous (a completion callback will be invoked)
 * and one of
 *   reads (from Target SD space into Host RAM)
 *   writes (from Host RAM into Target SD space)
 * and it is to one of
 *   Target's mailbox space
 *   Target's register space
 * and lots of other choices.
 */
void hif_task(void *param)
{
    struct hif_device *device;
    struct bus_request *request;
    int status;
    unsigned long intrstate;

    device = (struct hif_device *)param;

    for (;;) {
        uint32 sigs;

        hifdebug("%s: top of loop\r\n", __FUNCTION__);
        /* wait for work */
        sigs = qurt_signal_wait(&device->hif_wait,
                                HIF_SIGNAL_REQ_PENDING | HIF_SIGNAL_TASK_EXIT,
                                QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);

        if (sigs & HIF_SIGNAL_TASK_EXIT) {
            break;
        }
        ASSERT(sigs & HIF_SIGNAL_REQ_PENDING);

        for (;;) {
            hifdebug("%s: pull next request\r\n", __FUNCTION__);
            /* Pull the next request to work on */
            INTR_BLOCK(intrstate);
            request = device->req_qhead;
            if (!request) {
                INTR_UNBLOCK(intrstate);
                break;
            }

            /* Remove request from queue */
            device->req_qhead = (struct bus_request *)request->next;
            /* Note: No need to clean up req_qtail */

            INTR_UNBLOCK(intrstate);

            /* call __hif_read_write to do the work */
            hifdebug("%s: before HIFRW: address=0x%08x buffer=0x%p\r\n",
                     __FUNCTION__, request->address, request->buffer);
            hifdebug("%s: before HIFRW: length=%d req_type=0x%08x\r\n",
                     __FUNCTION__, request->length, request->req_type);

#if defined(DEBUG_VERBOSE)
            {
                int dbgcount;
                int i;

                if (request->length <= 16) {
                    dbgcount = request->length;
                } else {
                    dbgcount = 16;
                }

                if (request->req_type & HIF_WRITE) {
                    for (i = 0; i < dbgcount; i++) {
                        hifdebug("|hifwr:0x%02x", request->buffer[i]);
                    }
                    hifdebug("\r\n");
                } else {
                    memset(request->buffer, 0xaa, dbgcount);
                }
            }
#endif                          /* DEBUG_VERBOSE */
            status = __hif_read_write(device, request->address, request->buffer,
                                      request->length, request->req_type & ~HIF_SYNCHRONOUS, NULL);
            hifdebug("%s: after HIFRW: status=%d address=0x%08x buffer=0x%p\r\n",
                     __FUNCTION__, status, request->address, request->buffer);
            hifdebug("%s: after HIFRW: length=%d req_type=0x%08x\r\n",
                     __FUNCTION__, request->length, request->req_type);

#if defined(DEBUG_VERBOSE)
            if (request->req_type & HIF_READ) {
                int i;
                int dbgcount;

                if (request->length <= 16) {
                    dbgcount = request->length;
                } else {
                    dbgcount = 16;
                }

                for (i = 0; i < dbgcount; i++) {
                    hifdebug("|hifrd:0x%02x", request->buffer[i]);
                }
                hifdebug("\r\n");
            }
#endif                          /* DEBUG_VERBOSE */

            /* When we return, the read/write is done */
            request->status = status;

            if (request->req_type & HIF_ASYNCHRONOUS) {
                hif_request_complete(device, request);
            } else {
                /* notify thread that's waiting on this request */
                qurt_signal_set(&request->comp_req, 1);
            }
        }
    }

    qurt_signal_set(&device->hif_wait, HIF_SIGNAL_TASK_EXIT_DONE);
}

int hif_configure_device(void *hif_device, enum hif_device_config_opcode opcode, void *config, uint32_t config_len)
{
    int status = HIF_OK;
    struct hif_device *device = (struct hif_device *)hif_device;

    switch (opcode) {
    case HIF_DEVICE_GET_MBOX_BLOCK_SIZE:
        ((uint32_t *) config)[0] = HIF_MBOX0_BLOCK_SIZE;
        ((uint32_t *) config)[1] = HIF_MBOX1_BLOCK_SIZE;
        ((uint32_t *) config)[2] = HIF_MBOX2_BLOCK_SIZE;
        ((uint32_t *) config)[3] = HIF_MBOX3_BLOCK_SIZE;
        break;

    case HIF_DEVICE_SET_CONTEXT:
        device->context = config;
        break;

    case HIF_DEVICE_GET_CONTEXT:
        if (!config) {
            return HIF_ERROR;
        }
        *(void **)config = device->context;
        break;

    default:
        status = HIF_ERROR;
    }

    return status;
}

#if TBD
void hif_shutdown_device(void *device)
{
    if (!device) {
        int i;
        /* since we are unloading the driver, reset all cards
         * in case the SDIO card is externally powered and we
         * are unloading the SDIO stack.  This avoids the problem
         * when the SDIO stack is reloaded and attempts are made
         * to re-enumerate a card that is already enumerated.
         */

        /* Unregister with bus driver core */
        if (registered) {
            registered = 0;
            hif_sdio_unregister_driver();
            ASSERT(0);
            return;
        }

        for (i = 0; i < MAX_HIF_DEVICES; ++i) {
            if (hif_devices[i] && !hif_devices[i]->func) {
                del_hif_device(hif_devices[i]);
                hif_devices[i] = NULL;
            }
        }
    }
}
#endif                          /* TBD */

void hif_irq_handler(void *tdev)
{
    struct hif_device *device;

    device = get_hif_device(tdev);
    device->irq_handling = 1;
    (void)device->cbs_from_hif.dsr_hdl(device->cbs_from_hif.context);
    device->irq_handling = 0;
}

int hif_device_inserted(void *tdev, qbool_t hotplug)
{
    int i;
    int ret = -1;
    struct hif_device *device;
    int count;

    hifdebug("%s: hif_device_inserted: Enter\r\n", __FUNCTION__);

    device = add_hif_device(tdev);
    if (!device) {
        hifdebug("%s: add_hif_device failed\r\n", __FUNCTION__);
        return ret;
    }

    for (i = 0; i < MAX_HIF_DEVICES; ++i) {
        if (!hif_devices[i]) {
            hif_devices[i] = device;
            break;
        }
    }
    ASSERT(i < MAX_HIF_DEVICES);

    device->is_enabled = false;

    /* Initialize the bus requests to be used later */
    memset(device->bus_request, 0, sizeof(device->bus_request));
    for (count = 0; count < BUS_REQUEST_MAX_NUM; count++) {
        qurt_signal_create(&device->bus_request[count].comp_req);
        hif_free_bus_request(device, &device->bus_request[count]);
    }
    qurt_signal_create(&device->hif_wait);
    qurt_signal_create(&device->completion_wait);

    ret = hif_enable_func(device, tdev);
    if ((ret == HIF_OK) || (ret == HIF_PENDING)) {
        hifdebug("%s: HIF Device is ENABLED (%d)\r\n", __FUNCTION__, ret);

        hifdebug("%s: Calling deviceInsertedHandler....\r\n", __FUNCTION__);
        hifdebug("%s: ....at 0x%p\r\n", __FUNCTION__, hif_callbacks.dev_inserted_hdl);
        hif_callbacks.dev_inserted_hdl(hif_callbacks.context, device);
        hifdebug("%s: Returned from dev_inserted_hdl\r\n", __FUNCTION__);

        hifdebug("%s: HIF Device registering intr handler\r\n", __FUNCTION__);
        ret = trans_register_interrupt(tdev, hif_irq_handler);
        ASSERT(ret == 0);

        return 0;
    }
    hifdebug("%s: hif_enable_func failed (%d)\r\n", __FUNCTION__, ret);

    /* Failed to enable device */
    for (i = 0; i < MAX_HIF_DEVICES; i++) {
        if (hif_devices[i] == device) {
            hif_devices[i] = NULL;
            break;
        }
    }
    del_hif_device(device);
    return ret;
}

void hif_unmask_interrupt(void *hif_device)
{
    struct hif_device *device = (struct hif_device *)hif_device;

    hifdebug("%s: Enter\r\n", __FUNCTION__);

    /* Unmask our function IRQ */
    trans_unmask_interrupt(device->tdev);
    device->is_intr_enb = true;
}

void hif_mask_interrupt(void *hif_device)
{
    struct hif_device *device = (struct hif_device *)hif_device;

    hifdebug("%s: Enter\r\n", __FUNCTION__);

    /* Mask our function IRQ */
    trans_mask_interrupt(device->tdev);
    device->is_intr_enb = false;
}

struct bus_request *hif_allocate_bus_request(void *hif_device)
{
    struct bus_request *busrequest;
    struct hif_device *device = (struct hif_device *)hif_device;
    unsigned long intrstate;

    INTR_BLOCK(intrstate);
    /* Remove first in list */
    busrequest = device->bus_req_free_qhead;
    if (busrequest) {
        device->bus_req_free_qhead = (struct bus_request *)busrequest->next;
    }
    INTR_UNBLOCK(intrstate);

    return busrequest;
}

void hif_free_bus_request(struct hif_device *device, struct bus_request *busrequest)
{
    unsigned long intrstate;

    if (!busrequest) {
        return;
    }

    busrequest->next = NULL;

    /* Insert first in list */
    INTR_BLOCK(intrstate);
    busrequest->next = (struct bus_request *)device->bus_req_free_qhead;
    device->bus_req_free_qhead = busrequest;
    INTR_UNBLOCK(intrstate);
}

int hif_disable_func(struct hif_device *device, struct trans_device *tdev)
{
    device = get_hif_device(tdev);

    hif_stop_completion_thread(device);
    hif_stop_hif_task(device);
    trans_disable_trans(tdev);

    device->is_enabled = false;
    return 0;
}

int hif_enable_func(struct hif_device *device, struct trans_device *tdev)
{
    device = get_hif_device(tdev);
    int rv;

    if (!device) {
        return HIF_EINVAL;
    }

    if (!device->is_enabled) {
        trans_enable_trans(tdev);
        device->is_enabled = true;

        if (!device->completion_task) {
            qurt_thread_attr_t thread_attr;

            device->compl_qhead = NULL;
            device->compl_qtail = NULL;

            qurt_thread_attr_set_name(&thread_attr, HIF_COMPL_TASK_NAME);
            qurt_thread_attr_set_priority(&thread_attr, HIF_COMPL_TASK_PRIO);
            qurt_thread_attr_set_stack_size(&thread_attr, HIF_COMPL_TASK_STK_SIZE);

            rv = qurt_thread_create(&device->completion_task, &thread_attr, completion_task, (void *)device);
            if (rv) {
                return HIF_ERROR;
            }
        }

        /* create HIF I/O thread */
        if (!device->hif_task) {
            qurt_thread_attr_t thread_attr;

            qurt_thread_attr_set_name(&thread_attr, HIF_TASK_NAME);
            qurt_thread_attr_set_priority(&thread_attr, HIF_TASK_PRIO);
            qurt_thread_attr_set_stack_size(&thread_attr, HIF_TASK_STK_SIZE);

            rv = qurt_thread_create(&device->hif_task, &thread_attr, hif_task, (void *)device);
            if (rv) {
                return HIF_ERROR;
            }
        }
    }

    return HIF_OK;
}

int hif_device_removed(void *tdev, qbool_t hotplug)
{
    int i;
    int status = HIF_OK;
    struct hif_device *device;

    device = get_hif_device(tdev);
    if (!device) {
        return HIF_ERROR;
    }

    hif_callbacks.dev_removed_hdl(hif_callbacks.context, device);

    for (i = 0; i < MAX_HIF_DEVICES; ++i) {
        if (hif_devices[i] == device) {
            hif_devices[i] = NULL;
        }
    }

    trans_deregister_interrupt(tdev);

    if (device->is_enabled) {
        status = hif_disable_func(device, tdev);
    }

    del_hif_device(device);

    return status;
}

void *add_hif_device(struct trans_device *tdev)
{
    struct hif_device *hifdevice = NULL;

    if (!tdev) {
        return NULL;
    }

    hifdevice = malloc(sizeof(*hifdevice));
    if (!hifdevice) {
        return NULL;
    }
    memset(hifdevice, 0, sizeof(*hifdevice));

    hifdevice->tdev = tdev;
    trans_set_hifcontext(tdev, hifdevice);

    return (void *)hifdevice;
}

struct hif_device *get_hif_device(struct trans_device *tdev)
{
    return (struct hif_device *)trans_get_hifcontext(tdev);
}

void del_hif_device(struct hif_device *device)
{
    if (!device) {
        return;
    }
    free(device);
}

int hif_attach(void *hif_device, struct cbs_from_hif *callbacks)
{
    struct hif_device *device = (struct hif_device *)hif_device;

    if (device->cbs_from_hif.context) {
        /* already in use! */
        return HIF_ERROR;
    }
    device->cbs_from_hif = *callbacks;
    return HIF_OK;
}

void hif_stop_hif_task(struct hif_device *device)
{
    if (device->hif_task) {
        qurt_signal_set(&device->hif_wait, HIF_SIGNAL_TASK_EXIT);
        qurt_signal_wait(&device->hif_wait, HIF_SIGNAL_TASK_EXIT_DONE,
                         QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);
        device->hif_task = 0;
    }
}

/* hif_reset_target() - Reset target device
 * @struct hif_device: pointer to struct hif_device structure
 *
 * Reset the target by invoking power off and power on
 * sequence to bring back target into active state.
 * This API shall be called only when driver load/unload
 * is in progress.
 *
 * Return: 0 on success, error for failure case.
 */
int hif_reset_target(struct hif_device *hif_device)
{
    int ret;
    struct trans_device *tdev;

    if (!hif_device) {
        return HIF_ERROR;
    }

    tdev = hif_device->tdev;
    if (!tdev) {
        return HIF_ERROR;
    }

    ret = trans_reset_target(hif_device->tdev);
    if (!ret) {
        return HIF_ERROR;
    }

    return HIF_OK;
}

void hif_detach(void *hif_device)
{
    struct hif_device *device = (struct hif_device *)hif_device;

    hif_stop_hif_task(device);
    if (device->ctrl_response_timeout) {
        int rv;

        /* Reset the target by invoking power off and power on sequence
         * to the card to bring back into active state.
         */
        rv = hif_reset_target(device);
        ASSERT(rv == HIF_OK);
        device->ctrl_response_timeout = false;
    }

    memset(&device->cbs_from_hif, 0, sizeof(device->cbs_from_hif));
}

void hif_set_handle(void *hif_handle, void *handle)
{
    struct hif_device *device = (struct hif_device *)hif_handle;

    device->caller_handle = handle;
}

size_t hif_get_device_size(void)
{
    return sizeof(struct hif_device);
}
