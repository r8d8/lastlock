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

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <glob.h>           /* Including glob.h for glob() function used in find_pid() */
#include <signal.h>
#include <err.h>
#include <errno.h>
#include <sys/queue.h>
#include <pthread.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>

#include <pthread.h>
#include <unistd.h>

#include  "htc_event_signal.h"

htc_event_signal_t *htc_signal_init()
{
	htc_event_signal_t *evt_signal;

	evt_signal = malloc(sizeof(htc_event_signal_t));
	if (evt_signal == NULL)
		return NULL;
	
	evt_signal->cond_var = 0;
	pthread_mutex_init(&evt_signal->mutex, NULL);
	pthread_cond_init(&evt_signal->cond, NULL);
	
	return  evt_signal;
}

uint32_t htc_signal_wait(htc_event_signal_t *evt_signal, 
								uint32_t wait_for_cond, uint32_t type)
{
	uint32_t var32;
	
	pthread_mutex_lock(&evt_signal->mutex); //mutex lock
	
	if ((type & HTC_EVENT_WAIT_MASK) == HTC_EVENT_WAIT_ALL)
	{
		while((evt_signal->cond_var & wait_for_cond) != wait_for_cond)
		{
			pthread_cond_wait(&evt_signal->cond, &evt_signal->mutex); //wait for the condition
		}		
	} 
	else
	{
		while((evt_signal->cond_var & wait_for_cond) == 0)
		{
			pthread_cond_wait(&evt_signal->cond, &evt_signal->mutex); //wait for the condition
		}				
	}
	var32 = evt_signal->cond_var;
	if ((type & HTC_EVENT_CLEAR_MASK) == HTC_EVENT_CLEAR_ALL)
		evt_signal->cond_var = 0; 
	
	pthread_mutex_unlock(&evt_signal->mutex);
	
	return var32;
}

uint32_t htc_signal_set(htc_event_signal_t *evt_signal, uint32_t set_cond)
{
	pthread_mutex_lock(&evt_signal->mutex); //mutex lock
	
	evt_signal->cond_var |= set_cond;	
	pthread_cond_signal(&evt_signal->cond); //wait for the condition

	pthread_mutex_unlock(&evt_signal->mutex);
	
	return evt_signal->cond_var;
}