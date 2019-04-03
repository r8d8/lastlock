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

#include "qapi_zb_nwk.h"

qapi_Status_t _qapi_ZB_NWK_Register_Callback(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NWK_Event_CB_t NWK_Event_CB, uint32_t CB_Param);

qapi_Status_t _qapi_ZB_NWK_Unregister_Callback(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NWK_Event_CB_t NWK_Event_CB);

qapi_Status_t _qapi_ZB_NLDE_Data_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NLDE_Data_Request_t *RequestData);

qapi_Status_t _qapi_ZB_NLME_Network_Discovery(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint32_t ScanChannels, uint8_t ScanDuration);

qapi_Status_t _qapi_ZB_NLME_Network_Formation(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NLME_Network_Formation_Request_t *RequestData);

qapi_Status_t _qapi_ZB_NLME_Permit_Joining(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint8_t PermitDuration);

qapi_Status_t _qapi_ZB_NLME_Start_Router(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NLME_Start_Router_Request_t *RequestData);

qapi_Status_t _qapi_ZB_NLME_ED_Scan(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const uint32_t ScanChannels, const uint8_t ScanDuration);

qapi_Status_t _qapi_ZB_NLME_Join(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NLME_Join_Request_t *RequestData);

qapi_Status_t _qapi_ZB_NLME_Direct_Join(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NLME_Direct_Join_Request_t *RequestData, qapi_ZB_NLME_Direct_Join_Confirm_t *ConfirmData);

qapi_Status_t _qapi_ZB_NLME_Leave(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NLME_Leave_Request_t *RequestData);

qapi_Status_t _qapi_ZB_NLME_Reset(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qbool_t WarmStart);

qapi_Status_t _qapi_ZB_NLME_Sync(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qbool_t Track);

qapi_Status_t _qapi_ZB_NLME_Get_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_NIB_Attribute_ID_t AttributeId, uint8_t AttributeIndex, uint16_t *AttributeLength, uint8_t *AttributeValue);

qapi_Status_t _qapi_ZB_NLME_Set_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_NIB_Attribute_ID_t AttributeId, uint8_t AttributeIndex, uint16_t AttributeLength, const uint8_t *AttributeValue);

qapi_Status_t _qapi_ZB_NLME_Get_Key(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint8_t KeySeqNumber, qapi_ZB_NWK_Security_Material_Set_t *ConfirmData);

qapi_Status_t _qapi_ZB_NLME_Add_Key(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NWK_Security_Material_Set_t *Request);

qapi_Status_t _qapi_ZB_NLME_Route_Discovery(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_NLME_Route_Discovery_Request_t *RequestData);

qapi_Status_t _qapi_ZB_NLME_Send_Link_Status(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle);

qapi_Status_t _qapi_ZB_NLME_Send_NWK_Status(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t NWKAddr, qapi_ZB_NLME_NWK_Status_t StatusCode, uint16_t DstAddr, qapi_ZB_Addr_Mode_t DstAddrMode);

qapi_Status_t _qapi_ZB_NLME_Send_Unknown_Command(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t DstAddr, uint8_t NWKProtocolVer);

qapi_Status_t _qapi_ZB_NLME_Set_Next_Child_Address(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint16_t NextChildAddress);

qapi_Status_t _qapi_ZB_NLME_Set_Security_Frame_Count(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, uint8_t SeqNumber, uint64_t DevAddr, uint32_t FrameCount);
