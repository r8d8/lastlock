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

#ifndef _HTCA_INTERNAL_H_
#define _HTCA_INTERNAL_H_

#include "mbox_host_reg.h"

// #define DEBUG

#if defined(DEBUG)
/* For debug define htcadebug as a printf-like function. */
extern void PAL_CONSOLE_PRINTF(const char *format, ...);
#define htcadebug(args...) PAL_CONSOLE_PRINTF(args)
#else
#define htcadebug(args...)
#endif

/* HTCA internal specific declarations and prototypes */

/*
 * Target-side mbox controller supplies 4 mailboxes.
 * With SDIO, all 4 mailboxes are usable.
 * With SPI, only one mailbox is currently usable.
 */
#define HTCA_NUM_MBOX 4

/* Software supports at most this many Target devices */
#define HTCA_NUM_DEVICES_MAX 2

/* Maximum supported mailbox message size.
 *
 * Quartz' SDIO/SPI mailbox alias spaces are 2KB each; so changes
 * would be required to exceed that. WLAN restricts packets to
 * under 1500B.
 */
#define HTCA_MESSAGE_SIZE_MAX 2048

#define HTCA_TARGET_RESPONSE_TIMEOUT 2000       /* in ms */

/*
 * The maximum number of credits that we will reap
 * from one endpoint of the Target at one time.
 */
#define HTCA_TX_CREDITS_REAP_MAX 32

/* Mailbox address in SDIO address space */
#define MBOX_BASE_ADDR 0x800    /* Start of MBOX alias spaces */
#define MBOX_WIDTH 0x800        /* Width of each mailbox alias space */

#define MBOX_START_ADDR(mbox) (MBOX_BASE_ADDR + ((mbox) * (MBOX_WIDTH)))

/* The byte just before this causes an EndOfMessage interrupt to be generated */
#define MBOX_END_ADDR(mbox) (MBOX_START_ADDR(mbox) + MBOX_WIDTH)

/* extended MBOX address for larger MBOX writes to MBOX 0 (not used) */
#define MBOX0_EXTENDED_BASE_ADDR 0x2800
#define MBOX0_EXTENDED_WIDTH (6 * 1024)

/*
 * There *might* be a marginal improvement in memory utilization and performance
 * on a uniprocessor Host by UNdefining this. And a marginal improvement in throughput, 
 * especially on a multiprocessor Host, by defining this.
 *
 * If undefined, the HTCA Completion Task is eliminated and we handle HTCA
 * completion directly in the context of the HIF Complete Task.
 */
#define CONFIG_HTCA_COMPLETION_TASK 1

/* HTCA message header */
struct HTCA_header {
    uint16_t total_msg_length;
    uint8_t reserved[2];
};

#define HTCA_HEADER_LEN sizeof(struct HTCA_header)

/* Populate an htca_event_info structure to be passed to
 * a user's event handler.
 */
static inline void htca_frame_event(struct htca_event_info *event_info,
                                    uint8_t * buffer, size_t buffer_length,
                                    size_t actual_length, uint32_t status, void *cookie)
{
    if (event_info) {
        event_info->buffer = buffer;
        event_info->buffer_length = buffer_length;
        event_info->actual_length = actual_length;
        event_info->status = status;
        event_info->cookie = cookie;
    }
}

/* Global and endpoint-specific event tables use these to
 * map an event ID --> handler + param.
 */
struct htca_event_table_element {
    htca_event_handler handler;
    void *param;
};

/* This layout MUST MATCH Target hardware layout! */
struct htca_intr_status {
    uint8_t host_int_status;
    uint8_t cpu_int_status;
    uint8_t err_int_status;
    uint8_t counter_int_status;
};

/* This layout MUST MATCH Target hardware layout! */
struct htca_intr_enables {
    uint8_t int_status_enb;
    uint8_t cpu_int_status_enb;
    uint8_t err_status_enb;
    uint8_t counter_int_status_enb;
};

/* The Register table contains Target SDIO/SPI interrupt/rxstatus
 * registers used by HTCA. Rather than read particular registers,
 * we use a bulk "register refresh" to read all at once.
 *
 * This layout MUST MATCH Target hardware layout!
 */
struct htca_register_table {
    struct htca_intr_status status;

    uint8_t mbox_frame;
    uint8_t rx_lookahead_valid;
    uint8_t hole[2];

    /* Four lookahead bytes for each mailbox */
    uint32_t rx_lookahead[HTCA_NUM_MBOX];

#if 0
    struct htca_intr_enables enables;   /* Useful for debugging interrupts */
#endif

};

/* Two types of requests/responses are supported:
 * "mbox requests" are messages or data which
 * are sent to a Target mailbox
 * "register requests" are to read/write Target registers
 *
 * Mbox requests are managed with a per-endpoint
 * pending list and free list.
 *
 * Register requests are managed with a per-Target
 * pending list and free list.
 *
 * A generic HTCA request -- one which is either an
 * htca_mbox_request or an htca_reg_request is represented
 * by an htca_request.
 */

/* Number of mbox_requests and reg_requests allocated initially.  */
#define HTCA_MBOX_REQUEST_COUNT 16      /* per mailbox */
#define HTCA_REG_REQUEST_COUNT (4 * HTCA_NUM_MBOX)      /* per target */

/* An htca_request is at the start of a mbox_request structure
 * and at the start of a reg_request structure.
 *
 * Specific request types may be cast to a generic htca_request
 * (e.g. in order to invoke the completion callback function)
 */
struct htca_request {
                                                /*struct htca_request */ void *next;
                                                /* linkage */
    struct htca_target *target;
    void (*completion_cb) (struct htca_request * req, int status);
    int status;                 /* completion status from HIF */
};

struct htca_endpoint;           /* forward reference */

/* Mailbox request -- a message or bulk data */
struct htca_mbox_request {
    struct htca_request req;    /* Must be first -- (cast to htca_request) */

    /* Caller-supplied cookie associated with this request */
    void *cookie;

    /* Pointer to the start of the buffer. In the transmit
     * direction this points to the start of the payload. In the
     * receive direction, however, the buffer when queued up
     * points to the start of the HTCA header but when returned
     * to the caller points to the start of the payload
     *
     * Note: buffer is set to NULL whenever this request is free.
     */
    uint8_t *buffer;

    /* length, in bytes, of the buffer */
    uint32_t buffer_length;

    /* length, in bytes, of the payload within the buffer */
    uint32_t actual_length;

    struct htca_endpoint *end_point;
};

/* Round up a value (e.g. length) to a power of 2 (e.g. block size).  */
static inline uint32_t htca_round_up(uint32_t value, uint32_t pwrof2)
{
    return (((value) + (pwrof2) - 1) & ~((pwrof2) - 1));
}

/* Indicates reasons that we might access Target register space */
enum htca_req_purpose {
    UNUSED_PURPOSE,
    INTR_REFRESH,               /* Interrupt/status register refresh due to interrupt */
    POLLING_REFRESH,            /* Interrupt/status register refresh due to polling */
    CREDIT_REFRESH,             /* Reap credits */
    UPDATE_TARG_INTRS,
    UPDATE_TARG_AND_ENABLE_HOST_INTRS,
};

/* Register read request -- used to read registers from SDIO/SPI space.
 * Register writes are fire and forget; no completion is needed.
 *
 */
struct htca_reg_request {
    struct htca_request req;    /* Must be first -- (cast to htca_request) */
    uint8_t *buffer;            /* register value(s) */
    uint32_t length;

    /* Indicates the purpose this request was made */
    enum htca_req_purpose purpose;

    /* Which endpoint this read is for.
     * Used when processing a completed credit refresh request.
     */
    uint8_t epid;               /* which endpoint ID [0..3] */

    /* A read to Target register space returns
     * one specific Target register value OR
     * all values in the register_table OR
     * a special repeated read-and-dec from a credit register
     *
     * FUTURE: We could separate these into separate request
     * types in order to perhaps save a bit of space....
     * eliminate the union.
     */
    union {
        struct htca_intr_enables enb;
        struct htca_register_table reg_table;
        uint8_t credit_dec_results[HTCA_TX_CREDITS_REAP_MAX];
    } u;
};

struct htca_request_queue {
    struct htca_request *head;
    struct htca_request *tail;
};

#define HTCA_IS_QUEUE_EMPTY(q) (!((q)->head))

/* List of Target registers in SDIO/SPI space which can be accessed by Host */
enum target_registers {
    UNUSED_REG = 0,
    INTR_ENB_REG = INT_STATUS_ENABLE_ADDRESS,
    ALL_STATUS_REG = HOST_INT_STATUS_ADDRESS,
    ERROR_INT_STATUS_REG = ERROR_INT_STATUS_ADDRESS,
    CPU_INT_STATUS_REG = CPU_INT_STATUS_ADDRESS,
    TX_CREDIT_COUNTER_DECREMENT_REG = COUNT_DEC_ADDRESS,
    INT_TARGET_REG = INT_TARGET_ADDRESS,
};

static inline uint32_t get_reg_addr(enum target_registers which, uint8_t epid)
{
    return (((which) == TX_CREDIT_COUNTER_DECREMENT_REG)
            ? (COUNT_DEC_ADDRESS + (HTCA_NUM_MBOX + (epid)) * 4)
            : (which));
}

/* FUTURE: See if we can use lock-free operations
 * to manage credits and linked lists.
 */

/* One of these per endpoint */
struct htca_endpoint {
    /* Enabled or Disabled */
    qbool_t enabled;

    /* If data is available, rxLengthPending
     * indicates the length of the incoming message.
     */
    uint32_t rx_frame_length;   /* incoming frame length on this endpoint */
    /* includes HTCA header */
    /* Modified only by compl_task */

    qbool_t rx_data_alerted;    /* Caller was sent a BUFFER_AVAILABLE event */
    /* and has not supplied a new recv buffer */
    /* since that warning was sent.  */
    /* Modified only by work_task */

    qbool_t tx_credits_to_reap; /* At least one credit available at the */
    /* Target waiting to be reaped. */
    /* Modified only by compl_task */

    /* Guards tx_credits_available and tx_credit_refresh_in_progress */
    unsigned long tx_credit_lock;

    /* The number of credits that we have already reaped
     * from the Target. (i.e. we have decremented the Target's
     * count register so that we have ability to send future
     * messages). We have the ability to send tx_credits_available
     * messages without blocking.
     *
     * The size of a message is endpoint-dependent and always
     * a multiple of the device's block_size.
     */
    uint32_t tx_credits_available;

    /* Maximum message size */
    uint32_t max_msg_sz;

    /* Indicates that we are in the midst of a credit refresh cycle */
    qbool_t tx_credit_refresh_in_progress;

    /* Free/Pending Send/Recv queues are used for mbox requests.
     * An mbox Send request cannot be given to HIF until we have
     * a tx credit. An mbox Recv request cannot be given to HIF
     * until we have a pending rx msg.
     *
     * The HIF layer maintains its own queue of requests, which
     * it uses to serialize access to SDIO. Its queue contains
     * a mixture of sends/recvs and mbox/reg requests. HIF is
     * "beyond" flow control so once a requets is given to HIF
     * it is guaranteed to complete (after all previous requests
     * complete).
     */

    /* Guards Free/Pending send/recv queues */
    unsigned long mbox_queue_lock;
    struct htca_request_queue send_free_queue;
    struct htca_request_queue send_pending_queue;
    struct htca_request_queue recv_free_queue;
    struct htca_request_queue recv_pending_queue;

    /* Inverse reference to the target */
    struct htca_target *target;

    /* Block size configured for the endpoint -- common across all endpoints
     */
    uint32_t block_size;

    /* Mapping table for per-endpoint events */
    struct htca_event_table_element endpoint_event_tbl[HTCA_EVENT_EP_COUNT];

    /* Location of the endpoint's mailbox space */
    uint32_t mbox_start_addr;
    uint32_t mbox_end_addr;
};

#define ENDPOINT_UNUSED 0

/* One of these per connected QCA402X device. */
struct htca_target {
    /* Target device is initialized and ready to go?
     * This has little o do with Host state;
     * it reflects readiness of the Target.
     */
    qbool_t ready;

    /* Handle passed to HIF layer for SDIO/SPI Host controller access */
    void *hif_handle;           /* hif_device */

    /* Per-endpoint info */
    struct htca_endpoint end_point[HTCA_NUM_MBOX];

    /* Used during startup while the Host waits for the
     * Target to initialize.
     */
    qurt_signal_t target_init_wait;
#define HTCA_TARGET_CONFIGURE_FLAG 1
#define HTCA_TARGET_READY_FLAG     2

    /* Free queue for htca_reg_requests.
     *
     * We don't need a regPendingQueue because reads/writes to
     * Target register space are not flow controlled by the Target.
     * There is no need to wait for credits in order to hand off a
     * register read/write to HIF.
     *
     * The register read/write may end up queued in a HIF queue
     * behind both register and mbox reads/writes that were
     * handed to HIF earlier. But they will never be queued
     * by HTCA.
     */
    unsigned long reg_queue_lock;
    struct htca_request_queue reg_free_queue;

    /*
     * Counts of number of oustanding operations. Stores to these
     * counters are protected by outstanding_lock.
     */
    unsigned long outstanding_lock;
    unsigned int outstanding_update_intr;
    unsigned int outstanding_credit_refresh;
    unsigned int outstanding_register_refresh;
    unsigned int outstanding_data;      /* count of rx/tx currently queued to HIF */

    /* comp task synchronization */
    qurt_mutex_t task_mutex;

    qurt_thread_t work_task;
    qurt_thread_t compl_task;

    /* work_task synchronization */
    qurt_signal_t work_task_wait;       /* wait for work to do */
#define HTCA_WORK_TASK_HAS_WORK_FLAG    1
#define HTCA_WORK_TASK_HIF_IS_IDLE_FLAG 2
#define HTCA_WORK_TASK_SHUTDOWN_FLAG    4
#define HTCA_WORK_TASK_EXIT_FLAG        8

    /* compl_task synchronization */
    qurt_signal_t compl_task_wait;      /* wait for work to do */
#define HTCA_COMPL_TASK_HAS_WORK_FLAG 1
#define HTCA_COMPL_TASK_SHUTDOWN_FLAG 2
#define HTCA_COMPL_TASK_EXIT_FLAG     4

    /* Queue of completed mailbox and register requests */
    unsigned long compl_queue_lock;
    struct htca_request_queue compl_queue;

    /* Software's shadow copy of interrupt enables.
     * Only the work_task changes intr_enable bits,
     * so no locking necessary.
     *
     * Committed to Target HW when
     * we convert from polling to interrupts or
     * we are using interrupts and enables have changed
     */
    struct htca_intr_enables enb;
    struct htca_intr_enables last_committed_enb;
    int is_host_intr_enabled;   /* Interrupts from Target to Host are enabled at Host? */

    /* Set after we read data from a mailbox (to
     * update lookahead and mailbox status bits).
     * used only by work_task even though refreshes
     * may be started in other contexts.
     */
    int need_register_refresh;

    unsigned long pending_op_lock;      /* Guards pending_recv_mask */

    /* Non-zero if a recv operation has been started
     * but not yet completed. 1 bit for each ep.
     */
    int pending_recv_mask;
};

/* Convert an endpoint POINTER into an endpoint ID [0..3] */
static inline uint32_t get_endpoint_id(struct htca_endpoint *ep)
{
    return (uint32_t) (ep - ep->target->end_point);
}

void htca_receive_frame(struct htca_endpoint *end_point);

uint32_t htca_get_frame_length(struct htca_endpoint *end_point);

void htca_send_frame(struct htca_endpoint *end_point);

void htca_send_blk_size(struct htca_endpoint *end_point);

int htca_rw_completion_handler(void *req, int status);

void htca_send_compl(struct htca_request *req, int status);

void htca_recv_compl(struct htca_request *req, int status);

void htca_reg_compl(struct htca_request *req, int status);

int htca_target_inserted_handler(void *context, void *hif_handle);

int htca_target_removed_handler(void *context, void *hif_handle);

int htca_dsr_handler(void *target_ctxt);

void htca_service_cpu_interrupt(struct htca_target *target, struct htca_reg_request *req);

void htca_service_error_interrupt(struct htca_target *target, struct htca_reg_request *req);

void htca_service_credit_counter_interrupt(struct htca_target *target, struct htca_reg_request *req);

void htca_enable_credit_counter_interrupt(struct htca_target *target, uint8_t end_point_id);

void htca_disable_credit_counter_interrupt(struct htca_target *target, uint8_t end_point_id);

int htca_add_to_mbox_queue(struct htca_mbox_request *queue,
                           uint8_t * buffer, uint32_t buffer_length, uint32_t actual_length, void *cookie);

struct htca_mbox_request *htca_remove_from_mbox_queue(struct htca_mbox_request *queue);

void htca_mbox_queue_flush(struct htca_endpoint *end_point,
                           struct htca_request_queue *pending_queue,
                           struct htca_request_queue *free_queue, uint8_t event_id);

int htca_add_to_event_table(struct htca_target *target,
                            uint8_t end_point_id, uint8_t event_id, htca_event_handler handler, void *param);

int htca_remove_from_event_table(struct htca_target *target, uint8_t end_point_id, uint8_t event_id);

void htca_dispatch_event(struct htca_target *target,
                         uint8_t end_point_id, uint8_t event_id, struct htca_event_info *event_info);

struct htca_target *htca_target_instance(int i);

void htca_target_instance_add(struct htca_target *target);

void htca_target_instance_remove(struct htca_target *target);

uint8_t htca_get_bit_num_set(uint32_t data);

void htca_register_refresh(struct htca_target *target);

void free_request(struct htca_request *req, struct htca_request_queue *queue);

extern struct htca_target *htca_target_list[HTCA_NUM_DEVICES_MAX];

int htca_work_task_start(struct htca_target *target);
int htca_compl_task_start(struct htca_target *target);
void htca_work_task_stop(struct htca_target *target);
void htca_compl_task_stop(struct htca_target *target);
void htca_work_task_poke(struct htca_target *target);
void htca_compl_task_poke(struct htca_target *target);
void htca_idle_poke(struct htca_target *target);

void htca_event_table_init(void);
struct htca_event_table_element *htca_event_id_to_event(struct htca_target *target,
                                                        uint8_t end_point_id, uint8_t event_id);

int htca_request_queue_empty(struct htca_request_queue *queue);
void htca_request_enq_tail(struct htca_request_queue *queue, struct htca_request *req);
struct htca_request *htca_request_deq_head(struct htca_request_queue *queue);

void htca_register_refresh_start(struct htca_target *target, enum htca_req_purpose purpose);
void htca_register_refresh_compl(struct htca_target *target, struct htca_reg_request *req);

int htca_credit_refresh_start(struct htca_endpoint *end_point);
void htca_credit_refresh_compl(struct htca_target *target, struct htca_reg_request *req);

void htca_update_intr_enbs(struct htca_target *target, int enable_host_intrs);
void htca_update_intr_enbs_compl(struct htca_target *target, struct htca_reg_request *req);

qbool_t htca_negotiate_config(struct htca_target *target);

int htca_recv_request_to_hif(struct htca_endpoint *end_point, struct htca_mbox_request *mbox_request);
int htca_send_request_to_hif(struct htca_endpoint *endpoint, struct htca_mbox_request *mbox_request);

int htca_manage_pending_sends(struct htca_target *target, int epid);
int htca_manage_pending_recvs(struct htca_target *target, int epid);

void _htca_stop(struct htca_target *target);

#endif                          /* _HTCA_INTERNAL_H_ */
