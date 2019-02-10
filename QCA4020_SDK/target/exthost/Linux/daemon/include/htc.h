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

#ifndef HTC_H
#define HTC_H

#include "htc_internal.h"

#define HTC_TARGET_INSTANCE_0  (0)
#define HTC_SPI_RX_BUF         (2)

int htc_init(void* pCxt);
void signal_htc(void* pCxt);
int htc_deinit(void* pCxt);
int32_t htc_iface_queue_init(HTC_IFACE_CXT_T* pIfaceCxt);
int32_t htc_add_header(uint8_t* buf, uint16_t length);
int htc_get_statistics(HTC_IFACE_CXT_T* pIfaceCxt, long *send_count, long *recv_count);


void event_sent_Handler(HTC_TARGET * target,
        HTC_ENDPOINT_ID ep, HTC_EVENT_ID eventId, HTC_EVENT_INFO * eventInfo, void *context);
void event_received_Handler(HTC_TARGET * target,
        HTC_ENDPOINT_ID ep, HTC_EVENT_ID eventId, HTC_EVENT_INFO * eventInfo, void *context);
extern HTC_TARGET *htcTargetInstance(int i);

void* spi_TXthread(void* arg);
void* spi_RXthread(void* arg);
#endif
