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

#ifndef __TARGET_MGMT_INTERNAL_H__
#define __TARGET_MGMT_INTERNAL_H__

#include "qsCommon.h"
#include "qurt_signal.h"
#include "qurt_timer.h"
#include "qurt_thread.h"

#define MGMT_STACK_SIZE     1024
#define MGMT_PRIORITY       10
#define MGMT_TIMER_EVENT    0x80

#define MGMT_TEST_ECHO_MODE_SENDONLY            0
#define MGMT_TEST_ECHO_MODE_LOOPBACK            1

#define MGMT_CMD_TYPE_OFFSET    (QS_IOTD_HEADER_LEN)
#define GET_MGMT_CMD_TYPE(_x)   (*((char*)_x + QS_IOTD_HEADER_LEN))

/****************************************************************************************/
typedef enum _IotdMgmt_Msg_Type{
    MGMT_MSG_HELLO,    
    MGMT_MSG_RESET,
    MGMT_MSG_GET_STATUS,
    MGMT_MSG_GET_VERSION,
    MGMT_MSG_HEART_BEAT,
    MGMT_MSG_ECHO,
} IOTDMGMT_MSG_TYPE_T;

typedef enum _IotdMgmt_Response_Type{
    MGMT_RESP_OK,
    MGMT_RESP_ERR,
    MGMT_RESP_UNKNOWN,
} IOTDMGMT_RESP_TYPE_T;

typedef struct
{
    uint8_t status;
    qurt_thread_t thread;  /* Mgmt command handler thread */
    qurt_signal_t signal;    /* Signal for synchronization between MML and mgmt agent */
    qurt_timer_t timer;      /* timer for heart beat */
    uint8_t timer_start;      /* flag for timer flag */
} mgmtCxt_t;

/****************************************************************************************/
uint32_t MgmtSendResp(uint8 resp, uint8 status, uint8_t* result, uint16_t result_size);
uint32_t MgmtInit(void *cxt);
void MgmtDeInit(void *cxt);

#endif /* __TARGET_MGMT_INTERNAL_H__ */
#endif /* CONFIG_DAEMON_MODE */

