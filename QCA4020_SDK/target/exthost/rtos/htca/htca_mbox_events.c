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

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "qapi/qurt_mutex.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_thread.h"
#include "qapi/qapi_types.h"

#include "common_defs.h"
#include "hif/hif.h"
#include "htca.h"
#include "htca_mbox_internal.h"

/* Host Target Communications Event Management */

/* Protect all event tables -- global as well as per-endpoint. */
unsigned long event_lock;       /* protects all event tables */

/* Mapping table for global events -- avail/unavail */
static struct htca_event_table_element
 global_event_table[HTCA_EVENT_GLOBAL_COUNT];

struct htca_event_table_element *htca_event_id_to_event(struct htca_target *target,
                                                        uint8_t end_point_id, uint8_t event_id)
{
    struct htca_event_table_element *ev = NULL;

    /* is ep event */
    if ((event_id >= HTCA_EVENT_EP_START) && (event_id <= HTCA_EVENT_EP_END)) {
        struct htca_endpoint *end_point;
        int ep_evid;

        ep_evid = event_id - HTCA_EVENT_EP_START;
        end_point = &target->end_point[end_point_id];
        ev = &end_point->endpoint_event_tbl[ep_evid];
        /* is global event */
    } else if ((event_id >= HTCA_EVENT_GLOBAL_START) && (event_id <= HTCA_EVENT_GLOBAL_END)) {
        int global_evid;

        global_evid = event_id - HTCA_EVENT_GLOBAL_START;
        ev = &global_event_table[global_evid];
    } else {
        ASSERT(0);              /* unknown event */
    }

    return ev;
}

void htca_dispatch_event(struct htca_target *target,
                         uint8_t end_point_id, uint8_t event_id, struct htca_event_info *event_info)
{
    struct htca_event_table_element *ev;

    ev = htca_event_id_to_event(target, end_point_id, event_id);
    ASSERT(ev);

    if (ev->handler) {
        htca_event_handler handler;
        void *param;

        INTR_BLOCK(event_lock);
        handler = ev->handler;
        param = ev->param;
        INTR_UNBLOCK(event_lock);

        handler((void *)target, end_point_id, event_id, event_info, param);
    }
}

int htca_add_to_event_table(struct htca_target *target,
                            uint8_t end_point_id, uint8_t event_id, htca_event_handler handler, void *param)
{
    struct htca_event_table_element *ev;

    ev = htca_event_id_to_event(target, end_point_id, event_id);
    if (!ev) {
        return HTCA_ERROR;
    }

    INTR_BLOCK(event_lock);
    ev->handler = handler;
    ev->param = param;
    INTR_UNBLOCK(event_lock);

    return HTCA_OK;
}

int htca_remove_from_event_table(struct htca_target *target, uint8_t end_point_id, uint8_t event_id)
{
    struct htca_event_table_element *ev;

    ev = htca_event_id_to_event(target, end_point_id, event_id);
    if (!ev) {
        return HTCA_ERROR;
    }

    INTR_BLOCK(event_lock);
    /* Clear event handler info */
    memset(ev, 0, sizeof(*ev));
    INTR_UNBLOCK(event_lock);

    return HTCA_OK;
}

/* Called once during module initialization */
void htca_event_table_init(void)
{
}
