/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
 * Copyright (c) 2004-2006 Atheros Communications Inc.
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

/* Host-Target Communication API */

#ifndef _HTC_H_
#define _HTC_H_

#include <assert.h>

#ifdef USER_SPACE

#define		SPI_THREAD_STACKSIZE		16536

#ifndef     true
#define		true	1
#endif

#ifndef     false
#define		false   0
#endif

typedef	uint32_t	bool;

#define		BUG_ON(a)	assert(!(a))
#define		printk(a,...)

#endif

/*
 * TBD:
 * Need thorough doxygen documentation for each API.
 * Describe expectations for buffers (space for headers, 
 * space for block padding), asynchronous nature, ordering
 * of calls, startup, etc.
 *
 * Also describe compatibility (or not) with existing HTC
 * protocol versions.
 *
 * Are API names OK or should we be more "QAPI-esque"?
 */

#if defined(CONFIG_QCA402X_DEBUG)
#define DEBUG
#endif

/*
 * Maximum size of an HTC header.
 *
 * Callers of HTC must leave this many bytes before
 * the start of a buffer passed to any HTC API for
 * use by HTC itself.
 *
 * FUTURE: Investigate ways to remove this requirement.
 * Doesn't seem that hard to do....just tack on the
 * length in a separate buffer and send buffer pairs
 * to HIF. When extracting, first pull header then
 * pull payload into paired buffers.
 */
#define HTC_HEADER_LEN_MAX 8

/*
 * The HTC API is independent of the underlying interconnect and
 * independent of the protocols used across that interconnect.
 */

typedef int HTC_STATUS;
#define HTC_OK                0 /* Success */
#define HTC_ERROR             1 /* generic error */
#define HTC_EINVAL            2 /* Invalid parameter */
#define HTC_ECANCELED         3 /* Operation canceled */
#define HTC_EPROTO            4 /* Protocol error */
#define HTC_ENOMEM            5 /* Memory exhausted */

/*
 * Note: An Endpoint ID is always Interconnect-relative. So we
 * are likely to see the same Endpoint ID with different Targets
 * on a multi-Target system.
 */
typedef uint8_t HTC_ENDPOINT_ID;
#define HTC_EP_UNUSED (0xff)

typedef uint8_t HTC_EVENT_ID;
#define HTC_EVENT_UNUSED                   0

/* Start global events */
#define HTC_EVENT_GLOBAL_START             1
#define HTC_EVENT_TARGET_AVAILABLE         1
#define HTC_EVENT_TARGET_UNAVAILABLE       2
#define HTC_EVENT_GLOBAL_END               2
#define HTC_EVENT_GLOBAL_COUNT             (HTC_EVENT_GLOBAL_END - HTC_EVENT_GLOBAL_START + 1)
/* End global events */

/* Start endpoint-specific events */
#define HTC_EVENT_EP_START                 3
#define HTC_EVENT_BUFFER_RECEIVED          3
#define HTC_EVENT_BUFFER_SENT              4
#define HTC_EVENT_DATA_AVAILABLE           5
#define HTC_EVENT_EP_END                   5
#define HTC_EVENT_EP_COUNT                 (HTC_EVENT_EP_END - HTC_EVENT_EP_START + 1)
/* End endpoint-specific events */

#define HTC_IS_GLOBAL_EVENT(n) (((n) >= HTC_EVENT_GLOBAL_START) && ((n) <= HTC_EVENT_GLOBAL_END))
#define HTC_IS_EP_EVENT(n) (((n) >= HTC_EVENT_EP_START) && ((n) <= HTC_EVENT_EP_END))

struct htc_target;              /* opaque */
typedef struct htc_target HTC_TARGET;

typedef struct htc_event_info {
    uint8_t *buffer;
    void *cookie;
    uint32_t bufferLength;
    uint32_t actualLength;
    HTC_STATUS status;
} HTC_EVENT_INFO;

typedef void (*HTC_EVENT_HANDLER) (HTC_TARGET * target,
                                   HTC_ENDPOINT_ID ep, HTC_EVENT_ID eventId, HTC_EVENT_INFO * eventInfo, void *context);

HTC_STATUS HTCInit(void *pInfo);

void HTCShutDown(void);

HTC_STATUS HTCStart(HTC_TARGET * target);

void HTCStop(HTC_TARGET * target);

HTC_STATUS HTCEventReg(HTC_TARGET * target,
                       HTC_ENDPOINT_ID endPointId, HTC_EVENT_ID eventId, HTC_EVENT_HANDLER eventHandler, void *context);

HTC_STATUS HTCBufferReceive(HTC_TARGET * target,
                            HTC_ENDPOINT_ID endPointId, uint8_t * buffer, uint32_t length, void *cookie);

HTC_STATUS HTCBufferSend(HTC_TARGET * target,
                         HTC_ENDPOINT_ID endPointId, uint8_t * buffer, uint32_t length, void *cookie);

void signal_htc(void* pCxt);

#endif                          /* _HTC_H_ */
