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

#include "qapi_zb_cl_groups.h"

qapi_Status_t _qapi_ZB_CL_Groups_Create_Client(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_Cluster_t *Cluster, qapi_ZB_CL_Cluster_Info_t *Cluster_Info, qapi_ZB_CL_Groups_Client_Event_CB_t Event_CB, uint32_t CB_Param);

qapi_Status_t _qapi_ZB_CL_Groups_Create_Server(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_Cluster_t *Cluster, qapi_ZB_CL_Cluster_Info_t *Cluster_Info, qapi_ZB_Cluster_t IdentifyCluster, qapi_ZB_CL_Groups_Server_Event_CB_t Event_CB, uint32_t CB_Param);

qapi_Status_t _qapi_ZB_CL_Groups_Populate_Attributes(uint8_t TargetID, qbool_t Server, uint8_t *AttributeCount, qapi_ZB_CL_Attribute_t *AttributeList);

qapi_Status_t _qapi_ZB_CL_Groups_Send_Add_Group(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint16_t GroupId, const char *GroupName, qbool_t Identifying);

qapi_Status_t _qapi_ZB_CL_Groups_Send_View_Group(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint16_t GroupId);

qapi_Status_t _qapi_ZB_CL_Groups_Send_Get_Group_Membership(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint8_t GroupCount, const uint16_t *GroupList);

qapi_Status_t _qapi_ZB_CL_Groups_Send_Remove_Group(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint16_t GroupId);

qapi_Status_t _qapi_ZB_CL_Groups_Send_Remove_All_Groups(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo);
