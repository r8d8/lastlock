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

#ifndef IPC_MGR_H
#define IPC_MGR_H


#include "iotd_context.h"


#define IPCM_CLIENT_QNAME_OFFSET  (IOTD_HEADER_LEN + 1)  /*Offset to q string in Hello Packet*/
#define IPCM_MODULE_ID_OFFSET  (IOTD_HEADER_LEN + 2)

#define IPCM_GET_PACKET_TYPE(_x)  (((char*)_x)[IPCM_MODULE_ID_OFFSET+1])
#define IPCM_SEND_TIMEOUT          (3)  /*Time in seconds to wait for an IPC TX*/

int ipcManager_init(void* pCxt);
int ipcManager_deinit(void* pCxt);
void process_msg(IPC_CXT_T* pCxt, uint8_t* buf, uint16_t size, uint8_t sqId);
int send_client(void* pCxt, uint8_t index, uint8_t* buf, uint16_t size);
int send_server_exit(void* pCxt, uint8_t msg);
int32_t ipcManager_queue_init(IPC_CXT_T* pCxt);

int32_t diagManager_init(void* pCxt);
int32_t diagManager_deinit(void* pCxt);
#endif
