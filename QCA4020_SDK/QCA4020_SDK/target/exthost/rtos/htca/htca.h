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

/* Host-Target Communication API */

#ifndef _HTCA_H_
#define _HTCA_H_

#define DEBUG
#undef DEBUG

/* The HTCA API is independent of the underlying interconnect and
 * independent of the protocols used across that interconnect.
 */

#define HTCA_OK 0               /* Success */
#define HTCA_ERROR 1            /* generic error */
#define HTCA_EINVAL 2           /* Invalid parameter */
#define HTCA_ECANCELED 3        /* Operation canceled */
#define HTCA_EPROTO 4           /* Protocol error */
#define HTCA_ENOMEM 5           /* Memory exhausted */

/* Note: An Endpoint ID is always Interconnect-relative. So we
 * are likely to see the same Endpoint ID with different Targets
 * on a multi-Target system.
 */
#define HTCA_EP_UNUSED (0xff)

#define HTCA_EVENT_UNUSED 0

/* Start global events */
#define HTCA_EVENT_GLOBAL_START 1
#define HTCA_EVENT_TARGET_AVAILABLE 1
#define HTCA_EVENT_TARGET_UNAVAILABLE 2
#define HTCA_EVENT_GLOBAL_END 2
#define HTCA_EVENT_GLOBAL_COUNT \
        (HTCA_EVENT_GLOBAL_END - HTCA_EVENT_GLOBAL_START + 1)
/* End global events */

/* Start endpoint-specific events */
#define HTCA_EVENT_EP_START 3
#define HTCA_EVENT_BUFFER_RECEIVED 3
#define HTCA_EVENT_BUFFER_SENT 4
#define HTCA_EVENT_DATA_AVAILABLE 5
#define HTCA_EVENT_EP_END 5
#define HTCA_EVENT_EP_COUNT (HTCA_EVENT_EP_END - HTCA_EVENT_EP_START + 1)
/* End endpoint-specific events */

/* Maximum size of an HTC header across relevant implementations
 * (e.g. across interconnect types and platforms and OSes of interest).
 *
 * Callers of HTC must leave HTCA_HEADER_LEN_MAX bytes
 * reserved BEFORE the start of a buffer passed to HTCA htca_buffer_send
 * AT the start of a buffer passed to HTCBufferReceive
 * for use by HTC itself.
 *
 * FUTURE: Investigate ways to remove the need for callers to accommodate
 * for HTC headers.* Doesn't seem that hard to do....just tack on the
 * length in a separate buffer and send buffer pairs to HIF. When extracting,
 * first pull header then pull payload into paired buffers.
 */

#define HTCA_HEADER_LEN_MAX 4

struct htca_event_info {
    uint8_t *buffer;
    void *cookie;
    uint32_t buffer_length;
    uint32_t actual_length;
    int status;
};

typedef void (*htca_event_handler) (void *target,
                                    uint8_t ep, uint8_t event_id, struct htca_event_info * event_info, void *context);

int htca_init(void);

void htca_shutdown(void);

int htca_start(void *target);

void htca_stop(void *target);

int htca_event_reg(void *target,
                   uint8_t end_point_id, uint8_t event_id, htca_event_handler event_handler, void *context);

/* Notes:
 * buffer should be multiple of blocksize.
 * buffer should be large enough for header+largest message, rounded up to
 * blocksize.
 * buffer passed in should be start of the buffer -- where header will go.
 * length should be full length, including header.
 * On completion, buffer points to start of payload (AFTER header).
 * On completion, actual_length is the length of payload. Does not include
 * header nor padding. On completion, buffer_length matches the length that
 * was passed in here.
 */
int htca_buffer_receive(void *target, uint8_t end_point_id, uint8_t * buffer, uint32_t length, void *cookie);

/* Notes:
 * buffer should be multiple of blocksize.
 * buffer passed in should be start of payload; header will be tacked on BEFORE
 * this.
 * extra bytes will be sent, padding the message to blocksize.
 * length should be the number of payload bytes to be sent.
 * The actual number of bytes that go over SDIO is length+header, rounded up to
 * blocksize.
 * On completion, buffer points to start of payload (AFTER header).
 * On completion, actual_length is the length of payload. Does not include
 * header nor padding. On completion buffer_length is irrelevant.
 */
int htca_buffer_send(void *target, uint8_t end_point_id, uint8_t * buffer, uint32_t length, void *cookie);

#endif                          /* _HTCA_H_ */
