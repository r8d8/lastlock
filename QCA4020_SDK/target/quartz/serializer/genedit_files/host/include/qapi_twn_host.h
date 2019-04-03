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

#include "qapi_twn.h"

qapi_Status_t _qapi_TWN_Initialize(uint8_t TargetID, qapi_TWN_Handle_t *TWN_Handle, qapi_TWN_Event_CB_t TWN_Event_CB, uint32_t CB_Param);

void _qapi_TWN_Shutdown(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Start(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Stop(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Get_Device_Configuration(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_Device_Configuration_t *Configuration);

qapi_Status_t _qapi_TWN_Set_Device_Configuration(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_Device_Configuration_t *Configuration);

qapi_Status_t _qapi_TWN_Get_Network_Configuration(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_Network_Configuration_t *Configuration);

qapi_Status_t _qapi_TWN_Set_Network_Configuration(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_Network_Configuration_t *Configuration);

qapi_Status_t _qapi_TWN_Add_Border_Router(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_Border_Router_t *Border_Router);

qapi_Status_t _qapi_TWN_Remove_Border_Router(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_IPv6_Prefix_t *Prefix);

qapi_Status_t _qapi_TWN_Add_External_Route(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_External_Route_t *External_Route);

qapi_Status_t _qapi_TWN_Remove_External_Route(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_IPv6_Prefix_t *Prefix);

qapi_Status_t _qapi_TWN_Register_Server_Data(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Set_IP_Stack_Integration(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qbool_t Enabled);

qapi_Status_t _qapi_TWN_Commissioner_Start(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Commissioner_Stop(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Commissioner_Add_Joiner(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, uint64_t Extended_Address, const char *PSKd, uint32_t Timeout);

qapi_Status_t _qapi_TWN_Commissioner_Remove_Joiner(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, uint64_t Extended_Address);

qapi_Status_t _qapi_TWN_Commissioner_Set_Provisioning_URL(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const char *Provisioning_URL);

qapi_Status_t _qapi_TWN_Commissioner_Generate_PSKc(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const char *Passphrase, const char *Network_Name, uint64_t Extended_PAN_ID, uint8_t *PSKc);

qapi_Status_t _qapi_TWN_Joiner_Start(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_Joiner_Info_t *Joiner_Info);

qapi_Status_t _qapi_TWN_Joiner_Stop(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Set_PSKc(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const uint8_t *PSKc);

qapi_Status_t _qapi_TWN_IPv6_Add_Unicast_Address(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_IPv6_Prefix_t *Prefix, qbool_t Preferred);

qapi_Status_t _qapi_TWN_IPv6_Remove_Unicast_Address(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_IPv6_Address_t *Address);

qapi_Status_t _qapi_TWN_IPv6_Subscribe_Multicast_Address(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_IPv6_Address_t *Address);

qapi_Status_t _qapi_TWN_IPv6_Unsubscribe_Multicast_Address(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_IPv6_Address_t *Address);

qapi_Status_t _qapi_TWN_Set_Ping_Response_Enabled(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qbool_t Enabled);

qapi_Status_t _qapi_TWN_Become_Router(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Become_Leader(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Start_Border_Agent(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, int AddressFamily, const char *DisplayName, const char *Hostname, const char *Interface);

qapi_Status_t _qapi_TWN_Stop_Border_Agent(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Clear_Persistent_Data(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t _qapi_TWN_Set_Max_Poll_Period(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, uint32_t Period);

qapi_Status_t _qapi_TWN_Commissioner_Send_Mgmt_Get(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const uint8_t *TlvBuffer, uint8_t Length);

qapi_Status_t _qapi_TWN_Commissioner_Send_Mgmt_Set(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_Commissioning_Dataset_t *Dataset, const uint8_t *TlvBuffer, uint8_t Length);

qapi_Status_t _qapi_TWN_Commissioner_Send_PanId_Query(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, uint16_t PanId, uint32_t ChannelMask, const qapi_TWN_IPv6_Address_t *Address);

qapi_Status_t _qapi_TWN_Commissioner_Get_Session_Id(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, uint16_t *SessionId);

qapi_Status_t _qapi_TWN_Commissioner_Send_Mgmt_Active_Get(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_IPv6_Address_t *Address, const uint8_t *TlvBuffer, uint8_t Length);

qapi_Status_t _qapi_TWN_Commissioner_Send_Mgmt_Active_Set(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_Operational_Dataset_t *Dataset, const uint8_t *TlvBuffer, uint8_t Length);

qapi_Status_t _qapi_TWN_Get_Unicast_Addresses(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_IPv6_Prefix_t *AddressList, uint32_t *AddressListSize);

qapi_Status_t _qapi_TWN_Set_Key_Sequence(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, uint32_t Sequence);

qapi_Status_t _qapi_TWN_Set_DTLS_Handshake_Timeout(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, uint8_t Timeout);
