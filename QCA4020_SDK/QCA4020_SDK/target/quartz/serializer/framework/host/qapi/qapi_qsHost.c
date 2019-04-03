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
#include <stdlib.h>
#include "qsHost.h"
#include "qapi_qsHost.h"

#ifdef CONFIG_DAEMON_MODE

uint32_t qapi_Qs_Set_Target_Id(uint8_t targetId)
{
    return QsSetTargetId(targetId);
}

uint32_t qapi_Qs_Init(char *serverName, uint16_t maxMsgSize, uint16_t maxMsgCnt)
{
    return QsInit(serverName, maxMsgSize, maxMsgCnt);
}

uint32_t qapi_Qs_DeInit()
{
    QsDeInit();
    return 0;
}

uint32_t qapi_Qs_Register_Cb(eventCb_t cb, void *parameter)
{
    return QsRegisterCb(cb, parameter);
}

#else

uint32_t qapi_Qs_Init(uint8_t module, uint32_t transport, char *device_Name)
{
    return QsInit(module, transport, device_Name);
}

uint32_t qapi_Qs_DeInit(uint8_t module)
{
    return QsDeInit(module);
}
#endif /* CONFIG_DAEMON_MODE*/
