/*
 * Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
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

#include "qapi/qapi_crypto.h"
#include "qapi/qurt_mutex.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_thread.h"
#include "qapi/qurt_timer.h"

#include "malloc.h"
#include "common_defs.h"
#include "htca/htca.h"

/*
 * Demonstration of Host access via SDIO/SPI to QCA402X.
 * This demo is for TEST, DEMONSTRATION and EXPERIMENTATION only.
 */

// #define DEBUG
// #define DEBUG_VERBOSE
extern void spi_hal_config_freq(unsigned int);
extern void sdio_hal_config_freq(unsigned int);

#define DEMO_NUM_RECV_BUFS 2    /* per endpoint */
#define DEMO_NUM_SEND_BUFS 8    /* per target */

#define DEMO_MAIN_THREAD_NAME "demoMain"
#define DEMO_MAIN_THREAD_PRIO 19
#define DEMO_MAIN_THREAD_STK_SIZE (2*1024)

#define DEMO_CHECKER_THREAD_NAME "demoChkr"
#define DEMO_CHECKER_THREAD_PRIO 19
#define DEMO_CHECKER_THREAD_STK_SIZE (2*1024)

int demosent;

/* Minimal # bytes in payload (+msgnum+cksum) */
int demomsgmin = 0;

/* Maximum # bytes in payload (+msgnum+cksum) */
int demomsgmax = 1995;

/* Print a CHECKSUM message approximately every Nth loopback */
int demoquiet = 100;

/* Validate checksums on loopback messages */
int demovalidate = 1;

#if defined(SPI_TRANSPORT)
#define SDHOST_TRANSPORT_NAME "SPI"
unsigned int sdhost_freq_table[] = {
    3000000, 4000000, 6000000, 8000000, 12000000, 16000000, 24000000, 48000000
};
#define sdhost_config_freq(freq) spi_hal_config_freq(freq)
#define NUM_EPS_MAX 1           /* Currently limited to 1 EP for SPI */
#endif

#if defined(SDIO_TRANSPORT)
#define SDHOST_TRANSPORT_NAME "SDIO"
unsigned int sdhost_freq_table[] = {
    400000, 1000000, 2000000, 4000000, 8000000, 16000000, 24000000, 32000000, 48000000
};
#define sdhost_config_freq(freq) sdio_hal_config_freq(freq)
#define NUM_EPS_MAX 4
#endif
#define SDHOST_FREQ_TBL_SZ (sizeof(sdhost_freq_table) / sizeof(sdhost_freq_table[0]))

/* Control the number of endpoints to use. */
// unsigned int demoeps = NUM_EPS_MAX; /* Use all available endpoints */
unsigned int demoeps = 1; /* restrict to a single endpoint */

/* Controls whether or not to generate random data for each new send */
unsigned int demorndm = 1;

#if defined(DEBUG_VERBOSE)
/* Dynamically control verbose debug */
unsigned int demodebug_verbose = 1;
#endif

extern void PAL_CONSOLE_PRINTF(const char *format, ...);
#define printf(args...) PAL_CONSOLE_PRINTF(args)

#if defined(DEBUG)
#define debug(args...) PAL_CONSOLE_PRINTF(args)
#else
#define debug(args...)
#endif

/*
 * Count of messages that were identified with failed checksum
 * validataion after having been sent from Host to Target and
 * then looped back. When things are working correctly, this
 * count should be zero. If there is some fundamental communication
 * problem there may be a non-zero count. This may indicate, for
 * instance, that the wires used to connect Host and Target are
 * unreliable or too long.
 */
int bad_mesg_count;

#define DEMO_BUFSZ_MAX 2048

struct demobuf {
    struct demobuf *next;
    int epid;
    unsigned int msgsz;
    uint8_t buffer[DEMO_BUFSZ_MAX];
};

struct demobuf demobuf_send_space[DEMO_NUM_SEND_BUFS];
struct demobuf demobuf_recv_space[NUM_EPS_MAX][DEMO_NUM_RECV_BUFS];

/* Debug statistics */
struct demo_stats_s {
    unsigned int send[4];
} demo_stats;

/*
 * Three queues: free, rcvd and send.
 *
 * Each queue uses a counting semaphore to track how many
 * items are in the queue and to suspend a process until
 * an item becomes available.
 *
 * Each queue uses interrupt blocking for safe changes to the queue.
 */

struct demo_q {
    unsigned long lock;

    qurt_signal_t sig;
#define DEMO_QUEUE_NONEMPTY_FLAG 1

    struct demobuf *head;
    struct demobuf *tail;
};

struct demo_q demo_freeQ;
struct demo_q demo_recvQ;
struct demo_q demo_sendQ;

struct htca_target *demo_target;
qurt_thread_t demo_thread_main;
qurt_thread_t demo_thread_checker;
qurt_mutex_t demo_thread_mutex;

extern int demo_thread_start(void);
extern struct demobuf *demo_dequeue(struct demo_q *queue);

/*
 * Message that causes Target-side HTC_demo application to
 * enable/disable LOOPBACK.
 * "LOOPBACK=1" (enable loopback)
 * "LOOPBACK=0" (disable loopback; use bitbucket mode)
 *
 * Loopback mode permits us to test a combination of reads and writes.
 * Reads are more expensive than writes. We measure maximum throughput
 * using a write-only test which requires HTC_demo to operate in
 * BUTBUCKET mode.
 */
uint8_t loopback_msg[] = "LOOPBACK=";

/*
 * Send a message to Target that causes it to toggle between
 * LOOPBACK (disposition=1) and BITBUCKET (disposition=0) modes.
 */
void demo_loopback_mode_select(int disposition)
{
    struct demobuf *db;
    uint8_t *payload;
    unsigned int msgsz;
    int status;

    db = demo_dequeue(&demo_freeQ);
    ASSERT(db);

    payload = &db->buffer[HTCA_HEADER_LEN_MAX];
    msgsz = sizeof(loopback_msg);
    memcpy(payload, loopback_msg, msgsz);
    payload[msgsz - 1] = '0' + disposition;     /* replace string terminator with '0' or '1' */
    msgsz++;                    /* append a new string terminator */
    payload[msgsz - 1] = 0;
    debug("Set loopback disposition: %s (%d)\r\n", payload, msgsz);
    status = htca_buffer_send(demo_target, 0, payload, msgsz, db);
    ASSERT(status == HTCA_OK);
}

void demo_enqueue(struct demo_q *queue, struct demobuf *db)
{
    unsigned long intr_state;

    db->next = NULL;
    INTR_BLOCK(intr_state);
    if (queue->head) {
        queue->tail->next = db;
        queue->tail = db;
    } else {
        queue->head = queue->tail = db;
    }
    qurt_signal_set(&queue->sig, DEMO_QUEUE_NONEMPTY_FLAG);
    INTR_UNBLOCK(intr_state);
}

struct demobuf *demo_dequeue(struct demo_q *queue)
{
    unsigned long flags;
    struct demobuf *db;

    do {
        INTR_BLOCK(flags);
        db = queue->head;
        if (db) {
            queue->head = db->next;
            if (queue->head == NULL) {
                qurt_signal_clear(&queue->sig, DEMO_QUEUE_NONEMPTY_FLAG);
            }
        } else {
            INTR_UNBLOCK(flags);
            qurt_signal_wait(&queue->sig, DEMO_QUEUE_NONEMPTY_FLAG, 0);
            continue;
        }
        INTR_UNBLOCK(flags);
    } while (db == NULL);

    db->next = NULL;

    return db;
}

void demo_avail_handler(void *target, uint8_t epid, uint8_t eventid, struct htca_event_info *event_info, void *context)
{
    int rv;

    debug("sdhost: demo_avail_handler\r\n");
    ASSERT(demo_target == NULL);

    demo_target = (struct htca_target *)target;
    rv = demo_thread_start();
    ASSERT(!rv);
}

void demo_unavail_handler(void *target_unused, uint8_t epid,
                          uint8_t eventid, struct htca_event_info *event_info, void *context)
{
    debug("sdhost: demo_unavail_handler\r\n");
}

void demo_recvd_handler(void *target_unused, uint8_t epid,
                        uint8_t eventid, struct htca_event_info *event_info, void *context)
{
    struct demobuf *db;

    debug("sdhost: Enter demo_recvd_handler\r\n");
    db = (struct demobuf *)event_info->cookie;
    db->msgsz = event_info->actual_length;
    ASSERT(db->msgsz <= 2048);
    ASSERT(event_info->buffer == &db->buffer[HTCA_HEADER_LEN_MAX]);
    demo_enqueue(&demo_recvQ, db);
}

void demo_sent_handler(void *target_unused, uint8_t epid,
                       uint8_t eventid, struct htca_event_info *event_info, void *context)
{
    struct demobuf *db;

    debug("sdhost: Enter demo_sent_handler\r\n");
    demosent++;
    if (!demovalidate && demoquiet && ((demosent % demoquiet) == 0)) {
        printf("%016llu sdhost: sent %d.\r\n", timetick_get64(), demosent);
    }
    db = (struct demobuf *)event_info->cookie;
    demo_enqueue(&demo_freeQ, db);
}

unsigned int gen_rand(unsigned int low, unsigned int high)
{
    unsigned int rnum;

    ASSERT(low <= high);
    if (low == high) {
        return low;
    }

    RANDOM_BUFFER_FILL(&rnum, sizeof(rnum));
    rnum = rnum % (high - low);
    rnum += low;

    return rnum;
}

/* Fletcher16 16-bit checksum over an array of bytes */
uint16_t demo_cksum(void *_data, unsigned int count)
{
    uint16_t sum1 = 0;
    uint16_t sum2 = 0;
    uint8_t *data = _data;
    unsigned int index;

    for (index = 0; index < count; ++index) {
        sum1 = (sum1 + data[index]) % 255;
        sum2 = (sum2 + sum1) % 255;
    }

    return (sum2 << 8) | sum1;
}

void demo_send_messages(unsigned int num)
{
    struct demobuf *db;
    int status;
    uint8_t *payload;
    unsigned int msgcnt;
    unsigned int msgsz;
    int epid;
    uint16_t mycksum;

    demosent = 0;
    for (msgcnt = 1; msgcnt <= num; msgcnt++) {
        db = demo_dequeue(&demo_freeQ);
        ASSERT(db);

        /* Send a buffer */
        debug("sdhost: send buffer (%d)\r\n", msgcnt);

        /* Choose a random message size */
        msgsz = gen_rand(4 + 2 + demomsgmin, 4 + 2 + demomsgmax);
        db->msgsz = msgsz;

        /* Choose an endpoint */
        epid = gen_rand(0, demoeps - 1);
        ASSERT(epid < NUM_EPS_MAX);
        db->epid = epid;

        /*
         * Buffer format:
         *   HTCA header reserved space followed by payload:
         *       2 byte checksum over remainder of message
         *       4 byte message number (msgcnt)
         *       remainder is random message data
         */
        payload = &db->buffer[HTCA_HEADER_LEN_MAX];

        if (demorndm) {
            /* Fill in new random data for each send */
            RANDOM_BUFFER_FILL(&payload[2 + 4], msgsz - 2 - 4);
        }

        /* Fill in message number */
        memcpy(&payload[2], &msgcnt, 4);

        if (demovalidate) {
            mycksum = demo_cksum(&payload[2], msgsz - 2);
            memcpy(payload, &mycksum, 2);
        }

        debug("sdhost: Send#1: %d byte payload on ep=%d:|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x\r\n",
              msgsz, epid, payload[0], payload[1],
              payload[2], payload[3], payload[4], payload[5], payload[6], payload[7]);
        debug("sdhost: Send#2 :|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x\r\n",
              payload[8], payload[9], payload[10], payload[11], payload[12], payload[13], payload[14], payload[15]);

        demo_stats.send[epid]++;
        status = htca_buffer_send(demo_target, epid, payload, msgsz, db);
        ASSERT(status == HTCA_OK);
    }
}

void demo_thruput_at_freq(int freq)
{
    uint64_t start_time;
    uint64_t end_time;
    unsigned int delta_time;

    sdhost_config_freq(freq);

#if 1 /* DO loopback testing */
    printf("\r\nLoopback 500 2044B msgs@bus freq=%d\r\n", freq);
    demo_loopback_mode_select(1);
    demorndm = 1;
    demoquiet = 100;
    demovalidate = 1;
    demomsgmin = 0;
    demomsgmax = 2038;          /* plus cksum + msgID (+ HTC hdr) */
    demo_send_messages(500);

    Sleep(3000);                /* Allow send queue to drain before we measure thruput */
#endif

#if 1 /* DO throughput (butbucket) testing */
    printf("\r\nBitbucket 500 2044B msgs@bus freq=%d\r\n", freq);
    demo_loopback_mode_select(0);       /* no loopback */
    demorndm = 0;               /* no randomness */
    demoquiet = 0;              /* no chatter */
    demovalidate = 0;           /* no checksum validation */
    demomsgmin = demomsgmax = 2038;     /* fixed-size messages */
    start_time = timetick_get64();
    demo_send_messages(500);
    end_time = timetick_get64();

    /* 500 messages; 2044B each; 8 bits per byte; 32000 ticks per second */
    delta_time = end_time - start_time;
    printf("Took %d ticks for throughput = %d bps\r\n",
           delta_time, (unsigned int)((500ULL * 2044 * 8 * 32000) / delta_time));

    /*
     * Note: When re-enabling loopback with validation, be aware that if
     * there were pending messages waiting to be sent without proper cksums
     * they will be send and looped back and will cause cksum mismatches
     * when received. To avoid this, make sure send queue has been drained
     * before enabling loopback and validation.
     */
    Sleep(3000);                /* Allow send queue to drain */
#endif
}

void _demo_thread_main(void *unused)
{
    int status;

    struct demobuf *db;
    int epid;
    int i;

    debug("sdhost: main thread started\r\n");

    /*
     * This thread is started as the result of HTCA_EVENT_TARGET_AVAILABLE.
     * Start this Target and start processing some commands.
     */
    status = htca_start(demo_target);
    ASSERT(status == HTCA_OK);

    for (epid = 0; epid < NUM_EPS_MAX; epid++) {
        htca_event_reg(demo_target, epid, HTCA_EVENT_BUFFER_RECEIVED, demo_recvd_handler, (void *)0x88888888);
        htca_event_reg(demo_target, epid, HTCA_EVENT_BUFFER_SENT, demo_sent_handler, (void *)0x77777777);

        for (i = 0; i < DEMO_NUM_RECV_BUFS; i++) {
            db = &demobuf_recv_space[epid][i];
            memset(db, 0, sizeof(*db));

            db->epid = epid;

            status = htca_buffer_receive(demo_target, epid, db->buffer, DEMO_BUFSZ_MAX, db);
            ASSERT(status == HTCA_OK);
        }
    }

    for (i = 0; i < DEMO_NUM_SEND_BUFS; i++) {
        db = &demobuf_send_space[i];
        memset(db, 0, sizeof(*db));
        demo_enqueue(&demo_freeQ, db);
    }

#if 0
    {
        /*
         * Alternate test: Send/Recv at a single bus clock frequency.
         */
        printf("\r\nsdhost: Begin long robustness test\r\n");
        sdhost_config_freq(sdhost_freq_table[0]); /* ...at slow speed */
        demovalidate = 1;
        demorndm = 1;
        demomsgmin = 0;
        demomsgmax = 2038;
        demo_send_messages(0xffffffff);
        printf("\r\nsdhost: END long robustness test\r\n");
    }
#endif

#if 0
    {
        /*
         * Alternative test: Use a few small messages with
         * known fixed-size and fixed content.
         */
        struct demobuf *db;
        int status;
        uint8_t *payload;
        unsigned int msgsz;
        int epid;
        uint16_t mycksum;
        int i;

        demoquiet = 1;
        demovalidate = 1;

        /* First message */
        db = demo_dequeue(&demo_freeQ);
        ASSERT(db);

        msgsz = 5;
        db->msgsz = msgsz;
        epid = 0;
        db->epid = epid;
        payload = &db->buffer[HTCA_HEADER_LEN_MAX];
        for (i = 2; i < msgsz; i++) {
            payload[i] = 'A';
        }
        mycksum = demo_cksum(&payload[2], msgsz - 2);
        memcpy(payload, &mycksum, 2);
        status = htca_buffer_send(demo_target, epid, payload, msgsz, db);
        ASSERT(status == HTCA_OK);

        demo_loopback_mode_select(1);   /* bitbucket second test message  */

        /* Second message */
        db = demo_dequeue(&demo_freeQ);
        ASSERT(db);

        msgsz = 15;
        db->msgsz = msgsz;
        epid = 0;
        db->epid = epid;
        payload = &db->buffer[HTCA_HEADER_LEN_MAX];
        for (i = 2; i < msgsz; i++) {
            payload[i] = 'B';
        }
        mycksum = demo_cksum(&payload[2], msgsz - 2);
        memcpy(payload, &mycksum, 2);
        status = htca_buffer_send(demo_target, epid, payload, msgsz, db);
        ASSERT(status == HTCA_OK);

        demo_loopback_mode_select(1);

        /* Third message */
        db = demo_dequeue(&demo_freeQ);
        ASSERT(db);

        msgsz = 25;
        db->msgsz = msgsz;
        epid = 0;
        db->epid = epid;
        payload = &db->buffer[HTCA_HEADER_LEN_MAX];
        for (i = 2; i < msgsz; i++) {
            payload[i] = 'C';
        }
        mycksum = demo_cksum(&payload[2], msgsz - 2);
        memcpy(payload, &mycksum, 2);
        status = htca_buffer_send(demo_target, epid, payload, msgsz, db);
        ASSERT(status == HTCA_OK);
    }
#endif

#if 1
    {
        unsigned int freq_idx;

        /*
         * Main sdhost throughput test:
         * Over increasing bus clock rates, first validate
         * correct operation in loopback mode; then measure
         * maximum throughput using a send-only test.
         */
        printf("\r\nsdhost: BEGIN THROUGHPUT TEST\r\n");
        for (freq_idx=0; freq_idx < SDHOST_FREQ_TBL_SZ; freq_idx++) {
            printf("\r\nsdhost: %s bus frequency is %d\r\n",
                SDHOST_TRANSPORT_NAME, sdhost_freq_table[freq_idx]);
            demo_thruput_at_freq(sdhost_freq_table[freq_idx]);
        }
        printf("\r\nEND THROUGHPUT TEST\r\n");
    }
#endif

    Sleep(1000 * 60 * 60);      /* sleep "forever" */
}

void _demo_thread_checker(void *unused)
{
    struct demobuf *db;
    uint8_t *payload;
    unsigned int msgsz;
    int msgnum;
    int status;
    int epid;

    for (;;) {
        db = demo_dequeue(&demo_recvQ);
        ASSERT(db);

        epid = db->epid;
        ASSERT((epid >= 0) && (epid < NUM_EPS_MAX));

        payload = &db->buffer[HTCA_HEADER_LEN_MAX];
        msgsz = db->msgsz;
        memcpy(&msgnum, &payload[2], 4);
#if defined(DEBUG_VERBOSE)
        if (demodebug_verbose) {
            int i;

            debug("sdhost: Checking %d byte payload:", msgsz);
            for (i = 0; (i < msgsz) && (i < 16); i++) {
                if ((i % 16) == 0) {
                    debug("\r\n");
                }

                debug("|0x%02x", payload[i]);
            }
            debug("\r\n");
        }
#endif                          /* DEBUG_VERBOSE */

        /* Validate checksum */
        if (demovalidate) {
            uint16_t mycksum, calc_cksum;

            calc_cksum = demo_cksum(&payload[2], msgsz - 2);
            memcpy(&mycksum, payload, 2);
            if (calc_cksum != mycksum) {
                bad_mesg_count++;
                printf
                    ("%016llu sdhost: CHECKSUM MISMATCH (calc=0x%x msg=0x%x). Message 0x%08x sz=%d on ep#%d. bad_msgs=%d\r\n",
                     timetick_get64(), calc_cksum, mycksum, msgnum, msgsz, epid, bad_mesg_count);
                /* ASSERT(0); */
            } else {
                if (demoquiet && ((msgnum % demoquiet) == 0)) {
                    printf("%016llu sdhost: Loopback on ep#%d 0x%08x (%d) CHECKSUM VALID. (bad=%d)\r\n",
                           timetick_get64(), epid, msgnum, msgnum, bad_mesg_count);
                }
            }
        } else {
            if (demoquiet && ((msgnum % demoquiet) == 0)) {
                printf("sdhost: Loopback count: %d\r\n", msgnum);
            }
        }

        /* Recycle for next receive */
        db->msgsz = 0;          /* sanity */
        status = htca_buffer_receive(demo_target, epid, db->buffer, DEMO_BUFSZ_MAX, db);
        ASSERT(status == HTCA_OK);
    }
}

int demo_thread_start(void)
{
    int rv = -1;

    debug("sdhost: Enter demo_thread_start\r\n");
    qurt_mutex_lock(&demo_thread_mutex);

    if (demo_thread_main) {
        debug("sdhost: demo_thread_main already started\r\n");
        goto done;              /* already started */
    } else {
        qurt_thread_attr_t thread_attr;
        int rv;

        debug("sdhost: create demo_thread_main\r\n");
        qurt_thread_attr_set_name(&thread_attr, DEMO_MAIN_THREAD_NAME);
        qurt_thread_attr_set_priority(&thread_attr, DEMO_MAIN_THREAD_PRIO);
        qurt_thread_attr_set_stack_size(&thread_attr, DEMO_MAIN_THREAD_STK_SIZE);

        rv = qurt_thread_create(&demo_thread_main, &thread_attr, _demo_thread_main, NULL);
        if (rv) {
            goto done;          /* Failed to create main thread */
        }
        debug("sdhost: done creating demo_thread_main\r\n");
    }

    {
        qurt_thread_attr_t thread_attr;
        int rv;

        debug("sdhost: create demo_thread_checker\r\n");
        qurt_thread_attr_set_name(&thread_attr, DEMO_CHECKER_THREAD_NAME);
        qurt_thread_attr_set_priority(&thread_attr, DEMO_CHECKER_THREAD_PRIO);
        qurt_thread_attr_set_stack_size(&thread_attr, DEMO_CHECKER_THREAD_STK_SIZE);

        rv = qurt_thread_create(&demo_thread_checker, &thread_attr, _demo_thread_checker, NULL);
        if (rv) {
            goto done;          /* Failed to create checker thread */
        }
        debug("sdhost: done creating demo_thread_checker\r\n");
    }

    rv = 0;

 done:
    qurt_mutex_unlock(&demo_thread_mutex);
    return rv;
}

int demo_init(void)
{
    int status;

    debug("sdhost: Enter demo_init\r\n");
    printf("sdhost: Snoozing for 5 seconds.....\r\n");
    Sleep(5000);

    qurt_mutex_create(&demo_thread_mutex);

    qurt_signal_create(&demo_freeQ.sig);
    qurt_signal_create(&demo_recvQ.sig);
    qurt_signal_create(&demo_sendQ.sig);

    status = htca_init();
    if (status != HTCA_OK) {
        debug("sdhost: htca_init failed (%d)\r\n", status);
        return -1;
    }

    debug("sdhost: register avail/unavail events\r\n");
    htca_event_reg(NULL, 0 /* unused */ , HTCA_EVENT_TARGET_AVAILABLE,
                   demo_avail_handler, NULL);
    htca_event_reg(NULL, 0 /* unused */ , HTCA_EVENT_TARGET_UNAVAILABLE,
                   demo_unavail_handler, NULL);

    return 0;
}

/**
   @brief This function is used to pre initialize resource 
          required before starting the demo this is called
          from app_init function in pal.c
 */
void Initialize_Demo(void)
{
    PAL_CONSOLE_PRINTF("%s Demonstration\r\n", SDHOST_TRANSPORT_NAME);
}

/**
   @brief This function is used to start the demo thread this
          is called from app_init function in pal.c
 */
void App_Start(qbool_t ColdBoot)
{
    if (demo_init() < 0) {
        debug("sdhost: demo_init failed\r\n");
    }
}
