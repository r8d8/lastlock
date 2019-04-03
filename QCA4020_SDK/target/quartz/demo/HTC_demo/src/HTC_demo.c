/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
 
 /*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "qapi/qurt_stddef.h" 
#include "qapi/qurt_error.h"
#include "qapi/qurt_thread.h"
#include "qapi/qurt_mutex.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_timer.h"

#include "qapi/qapi_types.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_htc_slave.h"

#include "pal.h"

#if defined(CONFIG_INTERCONNECT_SPI)
qapi_HTC_Instance_id_t interconnect = QAPI_HTC_SPI_SLAVE_INSTANCE_ID;
#endif
#if defined(CONFIG_INTERCONNECT_SDIO)
qapi_HTC_Instance_id_t interconnect = QAPI_HTC_SDIO_SLAVE_INSTANCE_ID;
#endif

/*
 * This source supports LOOPBACK and the BITBUCKET modes.
 * We start and operate in LOOPBACK mode until a "mode switch message"
 * is received. Then we move to BITBUCKET mode. A subsequent mode
 * switch message returns us to LOOPBACK mode.
 */
qbool_t HTC_demo_loopback_enabled = TRUE; /* initially in loopback mode */
uint8_t loopback_msg[] = "LOOPBACK=";

// #define DEBUG
// #define DEBUG_VERBOSE

extern void PAL_CONSOLE_PRINTF(const char *format, ...);

#if defined(DEBUG)
#define demodebug(args...) PAL_CONSOLE_PRINTF(args)
#else
#define demodebug(args...)
#endif

#define demoprint(args...) PAL_CONSOLE_PRINTF(args)

#define ASSERT( __bool ) \
    do { \
        if (0 == (__bool)) { \
            __asm volatile("bkpt 0"); \
        } \
    } while (0)

#define THREAD_STACK_SIZE                           4096
#define THREAD_PRIORITY                             15

/*
 * Number of buffers to use per-endpoint.
 *
 * Must not exceed QAPI_NUM_BUFFERS_PER_ENDPOINT.
 *
 * Heap must accommodate HTC_DEMO_NUM_BUFS_PER_EP * HTC_DEMO_BUFSZ
 * bytes, allocated during startup. If using large SIZE buffers we
 * might not be able to afford memory for the maximum QUANTITY of
 * buffers.
 */
#define HTC_DEMO_NUM_BUFS_PER_EP 16

/* HTC_DEMO_BUFSZ is the size of a Target-side buffer. */
#if 0
/* Test small buffer size */
#define HTC_DEMO_BUFSZ 256
#endif
#if !defined(HTC_DEMO_BUFSZ)
/* By default use a single large buffer for each message */
#define HTC_DEMO_BUFSZ QAPI_HTC_BUFSZ_MAX_SEND
#endif

qurt_thread_t HTC_demo_thread_hdl;
qurt_signal_t HTC_demo_signal;

uint32 HTC_demo_waitmask;
#define HTC_DEMO_WAITMASK_INITDONE      0x00000001
#define HTC_DEMO_WAITMASK_MSGRECVD      0x00000002

qurt_mutex_t HTC_demo_mutex;
/* Tracking structure for messages that have been received */
struct recv_list_tracker_s {
        qapi_HTC_bufinfo_t *msg_bufs;     /* list of buffers that compose a single message */
        struct recv_list_tracker_s *next; /* pointer to next tracker */
};

/* List of messages that have been received by Target */
struct recv_list_tracker_s *recv_list;

/* Free list of tracking structures for received messages */
struct recv_list_tracker_s *free_recv_list = NULL;


#if defined(DEBUG)
extern void (* debug_buffer_print_fn)(qapi_HTC_bufinfo_t *buf, const char *str, int mbox);
void debug_buffer_print(qapi_HTC_bufinfo_t *buf, const char *str, int mbox);
#endif

void HTC_demo_recv_handler(uint32 instance, uint32 epid, uint32 bufarg)
{
    qapi_HTC_bufinfo_t *bufinfo = (qapi_HTC_bufinfo_t *)bufarg;
    struct recv_list_tracker_s *last, *curr, *new_recvd;

#if defined(DEBUG_VERBOSE)
    if (bufinfo == NULL) {
        demodebug("HTC_demo_recv_handler. epid=%ld NULL bufarg\r\n", epid);
    } else {
        demodebug("HTC_demo_recv_handler#1: epid=%ld msgsz=%d offset=%d buf=%p bytes=|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x\r\n",
                epid, bufinfo->actual_length, bufinfo->buffer_offset, bufinfo,
                bufinfo->buffer[0], bufinfo->buffer[1],
                bufinfo->buffer[2], bufinfo->buffer[3],
                bufinfo->buffer[4], bufinfo->buffer[5],
                bufinfo->buffer[6], bufinfo->buffer[7]);
        demodebug("HTC_demo_recv_handler#2: bytes=|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x\r\n",
                bufinfo->buffer[8], bufinfo->buffer[9],
                bufinfo->buffer[10], bufinfo->buffer[11],
                bufinfo->buffer[12], bufinfo->buffer[13],
                bufinfo->buffer[14], bufinfo->buffer[15]);
        demodebug("HTC_demo_recv_handler#3: bytes=|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x\r\n",
                bufinfo->buffer[16], bufinfo->buffer[17],
                bufinfo->buffer[18], bufinfo->buffer[19],
                bufinfo->buffer[20], bufinfo->buffer[21],
                bufinfo->buffer[22], bufinfo->buffer[23]);
        demodebug("HTC_demo_recv_handler#4: bytes=|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x\r\n",
                bufinfo->buffer[24], bufinfo->buffer[25],
                bufinfo->buffer[26], bufinfo->buffer[27],
                bufinfo->buffer[28], bufinfo->buffer[29],
                bufinfo->buffer[30], bufinfo->buffer[31]);
    }
#endif

    /* Enqueue completed buffer chain at tail of recv_list */
    last = NULL;
    qurt_mutex_lock(&HTC_demo_mutex);

    /* Grab a tracking structure for this received message */
    new_recvd = free_recv_list;
    free_recv_list = new_recvd->next;
    new_recvd->msg_bufs = bufinfo;
    new_recvd->next = NULL;

    /* Append the tracking structure for this message to the end of recv'd msg list */
    curr = recv_list;
    while (curr) {
        last = curr;
        curr = curr->next;
    }

    if (last) {
        last->next = new_recvd;
    } else {
        recv_list = new_recvd;
    }
    qurt_mutex_unlock(&HTC_demo_mutex);

    qurt_signal_set(&HTC_demo_signal, HTC_DEMO_WAITMASK_MSGRECVD);
}

void HTC_demo_sent_handler(uint32 instance, uint32 epid, uint32 bufarg)
{
    qapi_Status_t status;
    qapi_HTC_bufinfo_t *bufinfo = (qapi_HTC_bufinfo_t *)bufarg;
    qapi_HTC_bufinfo_t *curr;

    curr = bufinfo;
    while (curr) {
#if defined(DEBUG_VERBOSE)
            demodebug("HTC_demo_sent_handler: epid=%ld msgsz=%d buf=%p bytes=|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x\r\n",
                    epid, curr->actual_length, curr,
                    curr->buffer[0], curr->buffer[1],
                    curr->buffer[2], curr->buffer[3],
                    curr->buffer[4], curr->buffer[5],
                    curr->buffer[6], curr->buffer[7]);
#endif
        curr->actual_length = HTC_DEMO_BUFSZ;
        curr->buffer_offset = 0;
        ASSERT(curr->end_point == epid);

        curr = curr->next;
    }

    /* Enqueue the entire chain */
    status = qapi_HTC_Slave_Receive_Data(interconnect, epid, bufinfo);
    ASSERT(status == QAPI_OK);
}

void HTC_demo_init_done_handler(uint32 instance, uint32 unused1, uint32 unused2)
{
    qurt_signal_set(&HTC_demo_signal, HTC_DEMO_WAITMASK_INITDONE);
}

qapi_HTC_bufinfo_t *HTC_demo_bufchain[QAPI_HTC_SLAVE_MAX_ENDPOINTS];

qapi_HTC_bufinfo_t *HTC_demo_initialize_bufs(int epid)
{
    qapi_HTC_bufinfo_t *bufchain;
    qapi_HTC_bufinfo_t *bufinfo;
    int i;

    ASSERT(epid < QAPI_HTC_SLAVE_MAX_ENDPOINTS);

#if defined(CONFIG_INTERCONNECT_SPI)
    if (epid > 0) {
        return NULL;
    }
#endif

    bufchain = calloc(HTC_DEMO_NUM_BUFS_PER_EP, sizeof(qapi_HTC_bufinfo_t));
    ASSERT(bufchain);

    /* Remember for later so we can free this chain */
    HTC_demo_bufchain[epid] = bufchain;

    for (i=0; i<HTC_DEMO_NUM_BUFS_PER_EP; i++) {
        bufinfo = &bufchain[i];

        bufinfo->buffer = malloc(HTC_DEMO_BUFSZ);
        demodebug("malloc ep#%d buf#%d: %p\r\n", epid, i, bufinfo->buffer);
        if (!bufinfo->buffer) {
            demoprint("ERROR: malloc fail! ep#%d buf#%d\r\n", epid, i);
        }
        ASSERT(bufinfo->buffer);

        bufinfo->buffer_offset = 0;
        bufinfo->actual_length = HTC_DEMO_BUFSZ;
        bufinfo->end_point = epid;
        bufinfo->next = &bufchain[i+1];
    }
    bufinfo->next = NULL;

    return bufchain;
}

void HTC_demo_free_bufs(int epid)
{
    qapi_HTC_bufinfo_t *bufchain;
    qapi_HTC_bufinfo_t *bufinfo;
    int i;

    ASSERT(epid < QAPI_HTC_SLAVE_MAX_ENDPOINTS);

    bufchain = HTC_demo_bufchain[epid];
    ASSERT(bufchain);

    for (i=0; i<HTC_DEMO_NUM_BUFS_PER_EP; i++) {
        bufinfo = &bufchain[i];

        free(bufinfo->buffer);
    }

    free(bufchain);
}

/**
   @brief This function represents the main thread of execution.
*/
static void HTC_demo_thread(void *Param)
{
    qapi_Status_t status;
    uint32 waitmask;
    boolean is_test_running;
    uint8 num_endpoints;
    qurt_time_t alive_delay;
    int epid;
    int rv;
    qbool_t mode_switch_requested = FALSE;
    qbool_t want_loopback_enabled;

#if defined(DEBUG_VERBOSE)
    debug_buffer_print_fn = debug_buffer_print;
#endif

    rv = qurt_signal_create(&HTC_demo_signal);
    ASSERT(rv == QURT_EOK);

    rv = qurt_mutex_create(&HTC_demo_mutex);
    ASSERT(rv == QURT_EOK);

    status = qapi_HTC_Slave_Init(interconnect);
#if 1
    demodebug("qapi_HTC_Slave_Init returns status=%d\r\n", (int)status);
#endif
    ASSERT(status == QAPI_OK);

    status = qapi_HTC_Slave_Get_Num_Endpoints(interconnect, &num_endpoints);
    ASSERT(status == QAPI_OK);

    status = qapi_HTC_Event_Register(interconnect,
                                     QAPI_HTC_SLAVE_BUFFER_RECEIVED,
                                     HTC_demo_recv_handler, NULL);
    ASSERT(status == QAPI_OK);

    status = qapi_HTC_Event_Register(interconnect,
                                     QAPI_HTC_SLAVE_BUFFER_SENT,
                                     HTC_demo_sent_handler, NULL);
    ASSERT(status == QAPI_OK);

    status = qapi_HTC_Event_Register(interconnect,
                                     QAPI_HTC_SLAVE_INIT_COMPLETE,
                                     HTC_demo_init_done_handler, NULL);
    ASSERT(status == QAPI_OK);

    /* Kick off configuration negotiation */
    status = qapi_HTC_Slave_Start(interconnect);
    ASSERT(status == QAPI_OK);

    /* Wait for initialization to complete */
    demodebug("%s: Wait for Host to negotiate configuration...\r\n", __FUNCTION__);
    waitmask = qurt_signal_wait(&HTC_demo_signal,
                                HTC_DEMO_WAITMASK_INITDONE,
                                QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);
    ASSERT((waitmask & HTC_DEMO_WAITMASK_INITDONE) == HTC_DEMO_WAITMASK_INITDONE);
    demodebug("%s: HTC negotiation complete.\r\n", __FUNCTION__);

    for (epid=0; epid<num_endpoints; epid++) {
        status = qapi_HTC_Slave_Bufsz_Set(interconnect,
                                              (qapi_HTCSlaveEndpointID_t)epid,
                                              HTC_DEMO_BUFSZ);
        ASSERT(status == QAPI_OK);

        status = qapi_HTC_Slave_Max_MsgSize_Set(interconnect,
                                               (qapi_HTCSlaveEndpointID_t)epid,
                                               QAPI_HTC_BUFSZ_MAX_SEND);
        ASSERT(status == QAPI_OK);
    }

    /* Supply receive buffers for each endpoint */
    for (epid=0; epid<num_endpoints; epid++) {
        qapi_HTC_bufinfo_t *bufchain;

        bufchain = HTC_demo_initialize_bufs(epid);
        if (bufchain) {
            status = qapi_HTC_Slave_Receive_Data(interconnect,
                                                 epid,
                                                 bufchain);
            ASSERT(status == QAPI_OK);
        }
    }

    /* Initialize free list of tracking structures for received messages */
    {
        int i;
        int num_recv_list_trackers = HTC_DEMO_NUM_BUFS_PER_EP * num_endpoints;

        free_recv_list = calloc(num_recv_list_trackers, sizeof(struct recv_list_tracker_s));
        for (i=0; i<num_recv_list_trackers-1; i++) {
            free_recv_list[i].next = &free_recv_list[i+1];
        }
        free_recv_list[num_recv_list_trackers-1].next = NULL;
    }

    alive_delay = qurt_timer_convert_time_to_ticks(5*1000, QURT_TIME_MSEC); /* 5 seconds */

    is_test_running = true;
    while (is_test_running) {
        qapi_HTC_bufinfo_t *bufinfo;
        int dump_once = 0;
        int rv;

        /* Wait to receive a message from the Host */
        do {
            if (!dump_once) {
                demodebug("%s: waiting to recv...\r\n", __FUNCTION__);
            }
            rv = qurt_signal_wait_timed(&HTC_demo_signal,
                                        HTC_DEMO_WAITMASK_MSGRECVD,
                                        QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK,
                                        &waitmask,
                                        alive_delay);
            if (rv == QURT_EFAILED_TIMEOUT) {
                int i;

                if (!dump_once) {
                    demoprint("HTC_demo is alive but no msgs received recently\r\n");
                    if (recv_list) {
                        demoprint("recv_list != NULL\r\n");
                    } else {
                        demoprint("recv_list == NULL\r\n");
                    }
                    for (i=0; i<4; i++) {
                        qapi_HTC_slave_dump_recv_queued_buffers(interconnect, i);
                    }
#define LOCAL_COUNT_BASE_ADDR   0x50600080
                    demoprint("Outstanding Tx Credits: %d %d %d %d\r\n",
                        ((int *)LOCAL_COUNT_BASE_ADDR)[4],
                        ((int *)LOCAL_COUNT_BASE_ADDR)[5],
                        ((int *)LOCAL_COUNT_BASE_ADDR)[6],
                        ((int *)LOCAL_COUNT_BASE_ADDR)[7]);
                    dump_once++;
                } else {
                    demoprint(".");
                }
            }
        } while (rv != QURT_EOK);

        ASSERT(waitmask & HTC_DEMO_WAITMASK_MSGRECVD);

        for (;;) {
            /* Dequeue next completed buffer chain from head of recv_list */
            qurt_mutex_lock(&HTC_demo_mutex);
            if (recv_list) {
                struct recv_list_tracker_s *recvd = recv_list;

                bufinfo = recvd->msg_bufs;
                recv_list = recvd->next;

                /* Recycle recvd tracker */
                recvd->msg_bufs = NULL; /* sanity */
                recvd->next = free_recv_list;
                free_recv_list = recvd;
            } else {
                bufinfo = NULL;
            }
            qurt_mutex_unlock(&HTC_demo_mutex);

            if (!bufinfo) {
                /* Exit the inner loop. Suspend and wait for more */
                break;
            }

            epid = bufinfo->end_point;
            ASSERT((epid >= 0) && (epid <= 3));

            if (0==memcmp(&bufinfo->buffer[bufinfo->buffer_offset],
                        loopback_msg, sizeof(loopback_msg)-1))
            {
                mode_switch_requested = TRUE;
                want_loopback_enabled =
                        (bufinfo->buffer[bufinfo->buffer_offset+sizeof(loopback_msg)-1]=='0') ? FALSE : TRUE;
                demodebug("want_loopback_enabled=%d\r\n", want_loopback_enabled);
                        
            }

            if (HTC_demo_loopback_enabled && !mode_switch_requested) {
                /* Loopback reply */
                status = qapi_HTC_Slave_Send_Data(interconnect, epid, bufinfo);
            } else {
                /* Recycle recv buffer so we can continue to receive */
                status = qapi_HTC_Slave_Receive_Data(interconnect, epid, bufinfo);
            }
            ASSERT(status == QAPI_OK);

            if (mode_switch_requested) {
                HTC_demo_loopback_enabled = want_loopback_enabled;
                mode_switch_requested = FALSE;
                demodebug("%s: loopback_enabled=%d\r\n", __FUNCTION__, HTC_demo_loopback_enabled);
            }
        }
    }

    /* Cleanup & Shutdown */

    status = qapi_HTC_Event_Deregister(interconnect, QAPI_HTC_SLAVE_BUFFER_RECEIVED);
    ASSERT(status == QAPI_OK);

    status = qapi_HTC_Event_Deregister(interconnect, QAPI_HTC_SLAVE_BUFFER_SENT);
    ASSERT(status == QAPI_OK);

    status = qapi_HTC_Event_Deregister(interconnect, QAPI_HTC_SLAVE_INIT_COMPLETE);
    ASSERT(status == QAPI_OK);

    status = qapi_HTC_Slave_Stop(interconnect);
    ASSERT(status == QAPI_OK);

    status = qapi_HTC_Slave_Shutdown(interconnect);
    ASSERT(status == QAPI_OK);

    for (epid=0; epid<num_endpoints; epid++) {
        HTC_demo_free_bufs(epid);
    }
    qurt_signal_delete(&HTC_demo_signal);
    qurt_mutex_delete(&HTC_demo_mutex);
}

/**
   @brief This function is used to pre initialize resource 
          required before starting the demo this is called
 		  from app_init function in pal.c
 */
void Initialize_Demo(void)
{
    PAL_CONSOLE_WRITE_STRING_LITERAL("Host Target Communications TARGET-side demo\r\n");
    PAL_CONSOLE_WRITE_STRING_LITERAL(PAL_OUTPUT_END_OF_LINE_STRING);
}

/**
   @brief This function is used to start the demo thread.
          It is called from app_init function in pal.c
 */

void App_Start(qbool_t ColdBoot)
{
    qurt_thread_attr_t thread_attr;
    int rv;

    /* Start the HTCdemo thread */
    qurt_thread_attr_init(&thread_attr);
    qurt_thread_attr_set_name(&thread_attr, "HTCdemo");
    qurt_thread_attr_set_priority(&thread_attr, THREAD_PRIORITY);
    qurt_thread_attr_set_stack_size(&thread_attr, THREAD_STACK_SIZE);
    rv = qurt_thread_create(&HTC_demo_thread_hdl, &thread_attr, HTC_demo_thread, NULL);
    if(rv != QURT_EOK)
    {
        PAL_CONSOLE_WRITE_STRING_LITERAL("Failed to start HTC Demo Main thread.");
        PAL_CONSOLE_WRITE_STRING_LITERAL(PAL_OUTPUT_END_OF_LINE_STRING);
    }
}

/* Needed in order to use libc.a */
void *_sbrk(int x)
{
    return(NULL);
}

#if defined(DEBUG)
void debug_buffer_print(qapi_HTC_bufinfo_t *buf, const char *str, int mbox)
{
    if (!buf) {
        demodebug("DEBUG: no buffers on mbox#%d\r\n", mbox);
        return;
    }

    while (buf) {
        demodebug("DEBUG: mbox#%d: 0x%p %d\r\n", mbox, buf->buffer, buf->actual_length);
        buf = buf->next;
    }
}
#endif
