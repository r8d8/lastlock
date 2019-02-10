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

#include "qapi_zb_zdp.h"

qapi_Status_t _qapi_ZB_ZDP_Register_Callback(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_ZDP_Event_CB_t ZDP_Event_CB, uint32_t CB_Param);

qapi_Status_t _qapi_ZB_ZDP_Unregister_Callback(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_ZDP_Event_CB_t ZDP_Event_CB);

qapi_Status_t _qapi_ZB_ZDP_Nwk_Addr_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint64_t IEEEAddr, qapi_ZB_ZDP_Addr_Request_Type_t RequestType, uint8_t StartIndex);

qapi_Status_t _qapi_ZB_ZDP_IEEE_Addr_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest, qapi_ZB_ZDP_Addr_Request_Type_t RequestType, uint8_t StartIndex);

qapi_Status_t _qapi_ZB_ZDP_Node_Desc_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest);

qapi_Status_t _qapi_ZB_ZDP_Power_Desc_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest);

qapi_Status_t _qapi_ZB_ZDP_Simple_Desc_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest, uint8_t Endpoint);

qapi_Status_t _qapi_ZB_ZDP_Active_EP_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest);

qapi_Status_t _qapi_ZB_ZDP_Match_Desc_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, const qapi_ZB_ZDP_Match_Desc_Req_t *RequestData);

qapi_Status_t _qapi_ZB_ZDP_Complex_Desc_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest);

qapi_Status_t _qapi_ZB_ZDP_User_Desc_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest);

qapi_Status_t _qapi_ZB_ZDP_Device_Annce_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t NwkAddr, uint64_t IEEEAddr, uint8_t Capability);

qapi_Status_t _qapi_ZB_ZDP_Parent_Annce_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle);

qapi_Status_t _qapi_ZB_ZDP_User_Desc_Set(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest, uint8_t Length, const uint8_t *UserDescriptor);

qapi_Status_t _qapi_ZB_ZDP_System_Server_Discovery_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t ServerMask);

qapi_Status_t _qapi_ZB_ZDP_Extended_Simple_Desc_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest, uint8_t Endpoint, uint8_t StartIndex);

qapi_Status_t _qapi_ZB_ZDP_Extended_Active_EP_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint16_t NwkAddrOfInterest, uint8_t StartIndex);

qapi_Status_t _qapi_ZB_ZDP_End_Device_Bind_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZDP_End_Device_Bind_Req_t *RequestData);

qapi_Status_t _qapi_ZB_ZDP_Bind_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZDP_Bind_Req_t *RequestData);

qapi_Status_t _qapi_ZB_ZDP_Unbind_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZDP_Unbind_Req_t *RequestData);

qapi_Status_t _qapi_ZB_ZDP_Mgmt_Lqi_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint8_t StartIndex);

qapi_Status_t _qapi_ZB_ZDP_Mgmt_Rtg_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint8_t StartIndex);

qapi_Status_t _qapi_ZB_ZDP_Mgmt_Bind_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint8_t StartIndex);

qapi_Status_t _qapi_ZB_ZDP_Mgmt_Leave_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint64_t DeviceAddress, qbool_t RemoveChildren, qbool_t Rejoin);

qapi_Status_t _qapi_ZB_ZDP_Mgmt_Permit_Joining_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstNwkAddr, uint8_t PermitDuration, qbool_t TC_Significance);

qapi_Status_t _qapi_ZB_ZDP_Mgmt_Nwk_Update_Req(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZDP_Mgmt_Nwk_Update_Req_t *RequestData);

qapi_Status_t _qapi_ZB_ZDP_Set_Local_Complex_Desc(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const uint8_t *ManufacturerName, const uint8_t *ModelName, const uint8_t *SerialNumber);

qapi_Status_t _qapi_ZB_ZDP_Set_Local_User_Desc(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint8_t DescLength, uint8_t *Desc);

qapi_Status_t _qapi_ZB_ZDP_Device_Annce_Alias(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t AliasAddr, uint64_t IEEEAddr, uint8_t Capability);
