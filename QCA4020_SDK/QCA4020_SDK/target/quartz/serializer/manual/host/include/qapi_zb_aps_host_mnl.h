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

#include "qapi_zb_common.h"
#include "qapi_zb_aps.h"

qapi_Status_t Mnl_qapi_ZB_APSME_Get_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_AIB_Attribute_ID_t AIBAttribute, uint8_t AIBAttributeIndex, uint16_t *AIBAttributeLength, void *AIBAttributeValue);
qapi_Status_t Mnl_qapi_ZB_APSME_Set_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_AIB_Attribute_ID_t AIBAttribute, uint8_t AIBAttributeIndex, uint16_t AIBAttributeLength, const void *AIBAttributeValue);
qapi_Status_t Mnl_qapi_ZB_APS_Create_Test_Endpoint(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, void **TestEndpoint, uint16_t ProfileID);
qapi_Status_t Mnl_qapi_ZB_APS_Test_Endpoint_Data_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, void *TestEndpoint, const qapi_ZB_APSDE_Data_Request_t *RequestData, const uint16_t RspClusterID);
