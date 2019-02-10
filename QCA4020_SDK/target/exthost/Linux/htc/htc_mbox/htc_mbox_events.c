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

#ifndef USER_SPACE

#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/spinlock_types.h>
#include <linux/wait.h>
#include <linux/completion.h>

#else
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#endif

#include "htc_internal.h"
#include "hif/spi/hif.h"

#include "mbox_host_reg.h"
#include "htc_mbox_internal.h"
#include "dbg.h"

/* Host Target Communications Event Management */

/* Protect all event tables -- global as well as per-endpoint. */
#ifndef USER_SPACE
static spinlock_t eventLock;    /* protects all event tables */
#endif

/* Mapping table for global events -- avail/unavail */
static struct htc_event_table_element globalEventTable[HTC_EVENT_GLOBAL_COUNT];

struct htc_event_table_element *htcEventIDtoEvent(HTC_TARGET * target, HTC_ENDPOINT_ID endPointId, HTC_EVENT_ID eventId)
{
    struct htc_event_table_element *ev;

    if (HTC_IS_EP_EVENT(eventId)) {
        struct htc_endpoint *endPoint;
        int ep_evid;

        ep_evid = eventId - HTC_EVENT_EP_START;
        endPoint = &target->endPoint[endPointId];

        ev = &endPoint->endpointEventTable[ep_evid];
    } else if (HTC_IS_GLOBAL_EVENT(eventId)) {
        int global_evid;

        global_evid = eventId - HTC_EVENT_GLOBAL_START;
        ev = &globalEventTable[global_evid];
    } else {
        BUG_ON(1);              /* unknown event */
    }

    return ev;
}

void htcDispatchEvent(HTC_TARGET * target, HTC_ENDPOINT_ID endPointId, HTC_EVENT_ID eventId, HTC_EVENT_INFO * eventInfo)
{
    struct htc_event_table_element *ev;

    ev = htcEventIDtoEvent(target, endPointId, eventId);
	
	HTCPrintf(HTC_PRINT_GRP2, "htcDispatchEvent ev=%p endPointId:%d eventid=%d\n", ev, endPointId, eventId);

    if (ev->handler) {
        HTC_EVENT_HANDLER handler;
        void *param;
#ifndef USER_SPACE
        unsigned long flags;
#endif

#ifndef USER_SPACE
        spin_lock_irqsave(&eventLock, flags);
#else
    	sem_wait(&target->eventLock);
#endif
		handler = ev->handler;
        param = ev->param;
		
#ifndef USER_SPACE
        spin_unlock_irqrestore(&eventLock, flags);
#else
    	sem_post(&target->eventLock);
#endif
        handler(target, endPointId, eventId, eventInfo, param);
    }
}

HTC_STATUS
htcAddToEventTable(HTC_TARGET * target,
                   HTC_ENDPOINT_ID endPointId, HTC_EVENT_ID eventId, HTC_EVENT_HANDLER handler, void *param)
{
    struct htc_event_table_element *ev;
#ifndef USER_SPACE
    unsigned long flags;
#endif

    ev = htcEventIDtoEvent(target, endPointId, eventId);

#ifndef USER_SPACE
    spin_lock_irqsave(&eventLock, flags);
#else
	sem_wait(&target->eventLock);
#endif

    ev->handler = handler;
    ev->param = param;

	HTCPrintf(HTC_PRINT_GRP2, "htcAddToEventTable param:%p\n", param);
	
#ifndef USER_SPACE
    spin_unlock_irqrestore(&eventLock, flags);
#else
	sem_post(&target->eventLock);
#endif

    return HTC_OK;
}

HTC_STATUS htcRemoveFromEventTable(HTC_TARGET * target, HTC_ENDPOINT_ID endPointId, HTC_EVENT_ID eventId)
{
    struct htc_event_table_element *ev;
#ifndef USER_SPACE
    unsigned long flags;
#endif

    ev = htcEventIDtoEvent(target, endPointId, eventId);

#ifndef USER_SPACE
    spin_lock_irqsave(&eventLock, flags);
#else
	sem_wait(&target->eventLock);
#endif
    /* Clear event handler info */
    memset(ev, 0, sizeof(*ev));
#ifndef USER_SPACE
    spin_unlock_irqrestore(&eventLock, flags);
#else
	sem_post(&target->eventLock);
#endif

    return HTC_OK;
}
