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

#ifndef IOTD_MANAGER_H_
#define IOTD_MANAGER_H_

#include "iotd_context.h"

#define MGMT_CMD_TYPE_OFFSET        (QS_IOTD_HEADER_LEN)
#define GET_MGMT_CMD_TYPE(_x)       (*((char*)_x + QS_IOTD_HEADER_LEN))
#define GET_MGMT_RESP_STATUS(_x)    (*((char*)_x + QS_IOTD_HEADER_LEN + 1))
#define GET_MGMT_RESP_DATA(_x)    (((char*)_x + QS_IOTD_HEADER_LEN + 2))

#define IOTD_TEST_ECHO_MODE_SENDONLY            0
#define IOTD_TEST_ECHO_MODE_LOOPBACK            1


typedef enum _IotdMgmt_Msg_Type{
    MGMT_MSG_HELLO,         /* mgmt sync */ 
    MGMT_MSG_RESET,         /* target reset */
    MGMT_MSG_GET_STATUS,    /* target status */
    MGMT_MSG_GET_VERSION,   /* target version */
    MGMT_MSG_HEART_BEAT,    /* target heart beat message */
    MGMT_MSG_ECHO,          /* target echo */
    MGMT_MSG_DBG,
} IOTDMGMT_MSG_TYPE_T;

typedef enum _IotdMgmt_Response_Type{
    MGMT_RESP_OK,
    MGMT_RESP_ERR,
    MGMT_RESP_UNKOWN,
} IOTDMGMT_RESP_TYPE_T;

/************************************************************************/
int32_t iotdManagement_Cmd_Reset(void* pCxt);
int32_t iotdManagement_Cmd_GetStatus(void* pCxt);
int32_t iotdManagement_Cmd_Echo(void* pCxt, uint8_t* echo_buf, uint16_t echo_buf_size);
int32_t iotdManagement_Cmd_Hello(void* pCxt);
int iotdManagement_init(void* pCxt);
int iotdManagement_deinit(void* pCxt);
int run_throughput_test(void *pCxt);
#endif  /* IOTD_MANAGER_H_ */
