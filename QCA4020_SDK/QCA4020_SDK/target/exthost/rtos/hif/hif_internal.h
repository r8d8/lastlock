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

#ifndef _HIF_INTERNAL_H_
#define _HIF_INTERNAL_H_

#include "hif.h"

#define HIF_TASK_NAME              "HIF"
#define HIF_TASK_PRIO              18
#define HIF_TASK_STK_SIZE          2048

#define HIF_COMPL_TASK_NAME        "HIFcompl"
#define HIF_COMPL_TASK_PRIO        19
#define HIF_COMPL_TASK_STK_SIZE    2048

/*
 * Make BUS_REQUEST_MAX_NUM large enough to avoid ever failing due to
 * lack of bus requests. A number that accounts for the total number
 * of credits on the Target plus outstanding register requests is good.
 *
 * FUTURE: could dyanamically allocate additional busrequest structs
 * as needed.
 * FUTURE: would be nice for HIF to use HTCA's htca_request. Seems
 * wasteful to use multiple structures -- one for HTCA and another
 * for HIF -- and to copy info from one to the other. Maybe should
 * semi-merge these layers?
 */
#define BUS_REQUEST_MAX_NUM 128

#define SDWLAN_ENABLE_DISABLE_TIMEOUT 20
#define FLAGS_CARD_ENAB 0x02
#define FLAGS_CARD_IRQ_UNMSK 0x04

/* The purpose of these blocks is to amortize SD command setup time
 * across multiple bytes of data. In byte mode, we must issue a command
 * for each byte. In block mode, we issue a command (8B?) for each
 * BLOCK_SIZE bytes.
 *
 * Every mailbox read/write must be padded to this block size. If the
 * value is too large, we spend more time sending padding bytes over
 * SDIO. If the value is too small we see less benefit from amortizing
 * the cost of a command across data bytes.
 */
#define HIF_DEFAULT_IO_BLOCK_SIZE 256

/* The block size is an attribute of the SDIO function which is
 * shared by all four mailboxes. We cannot support per-mailbox
 * block sizes over SD.
 */
#define HIF_MBOX_BLOCK_SIZE HIF_DEFAULT_IO_BLOCK_SIZE
#define HIF_MBOX0_BLOCK_SIZE HIF_MBOX_BLOCK_SIZE
#define HIF_MBOX1_BLOCK_SIZE HIF_MBOX_BLOCK_SIZE
#define HIF_MBOX2_BLOCK_SIZE HIF_MBOX_BLOCK_SIZE
#define HIF_MBOX3_BLOCK_SIZE HIF_MBOX_BLOCK_SIZE

/* Address range of Target HCR register offsets */
#define HIF_HOST_CONTROL_REG_START_ADDR  0x400
#define HIF_HOST_CONTROL_REG_END_ADDR    0x5FF

struct bus_request {
    struct bus_request *next;   /* linked list of available requests */
    qurt_signal_t comp_req;
    uint32_t address;           /* request data */
    uint8_t *buffer;
    uint32_t length;
    uint32_t req_type;
    void *context;
    int status;
};

struct hif_device {
    struct trans_device *tdev;  /* Handle for underlying SDIO/SPI transport */

    /* Main HIF task */
    qurt_thread_t hif_task;     /* main task to handle requests */
    qurt_signal_t hif_wait;
#define HIF_SIGNAL_REQ_PENDING    1     /* read/write request is pending */
#define HIF_SIGNAL_TASK_EXIT      2     /* task should exit */
#define HIF_SIGNAL_TASK_EXIT_DONE 3     /* task has exitted */

    /* HIF Completion task */
    qurt_thread_t completion_task;      /* task to handle completions */
    qurt_signal_t completion_wait;
#define HIF_SIGNAL_COMPL_PENDING        1       /* completion pending */
#define HIF_SIGNAL_COMPL_TASK_EXIT      2       /* completion task should exit */
#define HIF_SIGNAL_COMPL_TASK_EXIT_DONE 3       /* completion task has exitted */

    /* pending request queue */
    struct bus_request *req_qhead;      /* head of request queue */
    struct bus_request *req_qtail;      /* tail of request queue */

    /* completed request queue */
    struct bus_request *compl_qhead;
    struct bus_request *compl_qtail;

    /* request free list */
    struct bus_request *bus_req_free_qhead;     /* free queue */

    /* Space for requests, initially queued to busRequestFreeQueue */
    struct bus_request bus_request[BUS_REQUEST_MAX_NUM];

    struct cbs_from_hif cbs_from_hif;   /* Callbacks made from HIF to caller */
    qbool_t is_enabled;         /* device is currently enabled? */
    qbool_t is_intr_enb;        /* interrupts are currently unmasked at
                                 * Host - dbg only */

    int irq_handling;           /* currently processing interrupts */
    void *context;
    qbool_t ctrl_response_timeout;

    /* for debug; links hif device back to caller (e.g.HTCA target) */
    void *caller_handle;
};

#define CMD53_FIXED_ADDRESS 1
#define CMD53_INCR_ADDRESS 2

#endif                          /* _HIF_INTERNAL_H_ */
