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

#ifndef _HTC_EVENT_SIGNAL_H_
#define _HTC_EVENT_SIGNAL_H_

#include <pthread.h>

typedef struct _htc_event_signal_s {
	pthread_cond_t  cond;
	pthread_mutex_t mutex;
	uint32_t   cond_var;
} htc_event_signal_t;

#define	HTC_EVENT_WAIT_ALL 		0x01
#define	HTC_EVENT_WAIT_ANY      0x00
#define HTC_EVENT_WAIT_MASK		0x01

#define	HTC_EVENT_CLEAR_ALL 	0x02
#define	HTC_EVENT_CLEAR_NONE    0x00
#define	HTC_EVENT_CLEAR_MASK    0x02

#define HTC_EVENT_WAIT_ANY_CLEAR_ALL	(HTC_EVENT_WAIT_ANY | HTC_EVENT_CLEAR_ALL)


#define	TARGET_INIT_DONE		0x01

#define EVENT_TASK_WAKEUP		0x01

htc_event_signal_t *htc_signal_init();
uint32_t htc_signal_wait(htc_event_signal_t *spitool_signal, 
								uint32_t wait_for_cond, uint32_t type);
uint32_t htc_signal_set(htc_event_signal_t *spitool_signal, uint32_t set_cond);
#endif
