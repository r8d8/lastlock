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

#include "qapi_zb.h"

qapi_Status_t _qapi_ZB_Initialize(uint8_t TargetID, qapi_ZB_Handle_t *ZB_Handle, qapi_ZB_Event_CB_t ZB_Event_CB, uint32_t CB_Param);

void _qapi_ZB_Shutdown(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle);

qapi_Status_t _qapi_ZB_Preconfigure(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_Preconfigure_t *Config);

qapi_Status_t _qapi_ZB_Form(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NetworkConfig_t *Config);

qapi_Status_t _qapi_ZB_Join(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_Join_t *Config);

qapi_Status_t _qapi_ZB_Reconnect(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qbool_t UseTCRejoin);

qapi_Status_t _qapi_ZB_Permit_Join(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint8_t Duration);

qapi_Status_t _qapi_ZB_Leave(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle);

qapi_Status_t _qapi_ZB_Set_Extended_Address(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint64_t Extended_Address);

qapi_Status_t _qapi_ZB_Get_Extended_Address(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint64_t *Extended_Address);

qapi_Status_t _qapi_ZB_Get_Current_Channel(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint8_t *Page, uint32_t *Channel);

qapi_Status_t _qapi_ZB_Get_Persistent_Data(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint8_t *Buffer, uint32_t *Length);

qapi_Status_t _qapi_ZB_Restore_Persistent_Data(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const uint8_t *Buffer, uint32_t Length);

qapi_Status_t _qapi_ZB_Register_Persist_Notify_CB(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_Persist_Notify_CB_t ZB_Persist_Notify_CB, uint32_t CB_Param);

qapi_Status_t _qapi_ZB_Set_Transmit_Power(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, int8_t TxPower);

qapi_Status_t _qapi_ZB_Get_Transmit_Power(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, int8_t *TxPower);
