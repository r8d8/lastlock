/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
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

#ifdef CONFIG_DAEMON_MODE

#ifndef __TARGET_SPI_INTERNAL_H__
#define __TARGET_SPI_INTERNAL_H__


#include <stdint.h>
#include "common.h"
#include "qapi_status.h"
#include "qapi_htc_slave.h"
#include "qurt_error.h"

#define HTC_HDR_SZ            4

#define SPI_BLOCKSIZE         32

#define SPI_STACK_SIZE        1024
#define SPI_THREAD_PRIORITY   10

#define HTC_DEMO_WAITMASK_INITDONE      0x00000001
#define HTC_DEMO_WAITMASK_MSGRECVD      0x00000002

#define HTC_MAX_BUFSZ                           512
#define HTC_NUM_BUFFERS_PER_ENDPOINT            2
#define HTC_NUM_SND_BUFFERS_PER_ENDPOINT        3
#define HTC_MAX_MSGSZ                           2048
#define HTC_NUM_MSGS_PER_ENDPOINT               2

#define EVENT_SND_BUFOINF                      0x01

#define ASSERT(a)

void (*Dbg_Printf)(char *fmt, ...);

#ifndef      HIF_DEBUG
#define     Dbg_Info_Printf(...)
#else
#define     Dbg_Info_Printf   Dbg_Printf
#endif

/* Round up a value (e.g. length) to a power of 2 (e.g. block size).  */
#define HTC_ROUND_UP(value, pwrof2) (((value) + (pwrof2) - 1) & ~((pwrof2) - 1))

/*Debug info structure*/
typedef struct spiDbg_s{
	uint32_t sentCounter;
	uint32_t rxCounter;
} spiDbg_t;

/* Context for SPI mode */
typedef struct spiCxt_s {
	uint8_t spi_initialized_flag;
    uint8_t num_endpoints;
    qurt_mutex_t bufinfo_mutex;
    qurt_signal_t bufinfo_snd_signal;
    qurt_signal_t bufinfo_rcv_signal;    
    qapi_HTC_bufinfo_t *donelist;
	qurt_signal_t init_sync;
    qurt_signal_t HTC_init_done_signal;
    uint32_t  htc_bufsz_max;
    uint32_t  htc_blksz;
    uint32_t  htc_msgsz_max;

    qapi_HTC_Instance_id_t htc_inst;

    qapi_HTC_bufinfo_t *htc_rcv_bufchain[QAPI_HTC_SLAVE_MAX_ENDPOINTS];   // receive bufinfo
    qapi_HTC_bufinfo_t *htc_snd_bufchain[QAPI_HTC_SLAVE_MAX_ENDPOINTS];   // send bufinfo
    
    qurt_signal_t txEvent;  /* Signal used for Tx related events */
    qurt_signal_t rxEvent;  /* Signal used for Tx related events */
    qurt_thread_t txThread; /* Thread to send data on SPI. */
    qurt_thread_t rxThread; /* Thread to send data on SPI. */
    queue_t txQueue;        /* Queue of packets to be sent */
    queue_t rxQueue;        /* Queue of packets to be sent */
	spiDbg_t dbg;
} spiCxt_t;




uint32_t Create_low_half_Thread();
void htc_init_low_half (void *param);

uint32_t QsSPIInit();
uint32_t QsSPIDeInit();
uint32_t QsSpiTransmit(char *txBuf);

#endif /* __TARGET_SPI_INTERNAL_H__ */
#endif /* CONFIG_DAEMON_MODE */

