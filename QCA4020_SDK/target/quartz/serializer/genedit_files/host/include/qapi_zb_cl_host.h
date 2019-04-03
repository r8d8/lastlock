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

#include "qapi_zb_cl.h"

qapi_Status_t _qapi_ZB_CL_Register_Callback(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_CL_Event_CB_t CL_Event_CB, uint32_t CB_Param);

qapi_Status_t _qapi_ZB_CL_Unregister_Callback(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_CL_Event_CB_t CL_Event_CB);

qapi_Status_t _qapi_ZB_CL_Create_Cluster(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_Cluster_t *Cluster, uint16_t ClusterId, qapi_ZB_CL_Cluster_Info_t *Cluster_Info, qapi_ZB_CL_Frame_Direction_t Direction, qapi_ZB_CL_Custom_Cluster_Event_CB_t Event_CB, uint32_t CB_Param);

qapi_Status_t _qapi_ZB_CL_Destroy_Cluster(uint8_t TargetID, qapi_ZB_Cluster_t Cluster);

qapi_Status_t _qapi_ZB_CL_Get_Cluster_Info(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, uint8_t *Endpoint, uint16_t *ProfileId, uint16_t *ClusterId);

qapi_Status_t _qapi_ZB_CL_Set_Profile_ID(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, uint16_t ProfileID);

qapi_Status_t _qapi_ZB_CL_Set_Min_Security(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, qapi_ZB_CL_Security_Level_t MinSecurity);

qapi_Status_t _qapi_ZB_CL_Set_Tx_Options(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, uint8_t TxOptions);

qapi_Status_t _qapi_ZB_CL_Get_Tx_Options(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, uint8_t *TxOptions);

qapi_Status_t _qapi_ZB_CL_Set_Discover_Route(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, qbool_t DiscoverRoute);

qapi_Status_t _qapi_ZB_CL_Get_Discover_Route(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, qbool_t *DiscoverRoute);

qapi_Status_t _qapi_ZB_CL_Set_Radius(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, uint8_t Radius);

qapi_Status_t _qapi_ZB_CL_Get_Radius(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, uint8_t *Radius);

qapi_Status_t _qapi_ZB_CL_Send_Command(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, qbool_t ResponseExpected, const qapi_ZB_CL_Header_t *ZCL_Header, uint16_t PayloadLength, const uint8_t *Payload);

qapi_Status_t _qapi_ZB_CL_Read_Local_Attribute(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, uint16_t AttrId, uint16_t *Length, uint8_t *Data);

qapi_Status_t _qapi_ZB_CL_Write_Local_Attribute(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, uint16_t AttrId, uint16_t Length, const uint8_t *Data);

qapi_Status_t _qapi_ZB_CL_Read_Attributes(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint8_t AttrCount, const uint16_t *AttrIdList);

qapi_Status_t _qapi_ZB_CL_Write_Attributes(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint8_t AttrCount, const qapi_ZB_CL_Write_Attr_Record_t *AttrRecordList);

qapi_Status_t _qapi_ZB_CL_Configure_Reporting(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint8_t ReportCount, const qapi_ZB_CL_Attr_Reporting_Config_Record_t *ReportRecordList);

qapi_Status_t _qapi_ZB_CL_Read_Reporting_Config(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint8_t ReportCount, const qapi_ZB_CL_Attr_Record_t *ReportConfigList);

qapi_Status_t _qapi_ZB_CL_Discover_Attributes(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, const uint16_t StartAttrId, const uint8_t AttrIdCount);

qapi_Status_t _qapi_ZB_CL_Read_Attributes_Structured(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, const uint8_t AttrCount, const qapi_ZB_CL_Read_Attr_Structured_t *AttrStructuredList);

qapi_Status_t _qapi_ZB_CL_Write_Attributes_Structured(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, const uint8_t AttrCount, const qapi_ZB_CL_Write_Attr_Structured_Record_t *AttrStructuredList);

qapi_Status_t _qapi_ZB_CL_Report_Attributes(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, const uint8_t ReportCount, const qapi_ZB_CL_Attr_Report_t *ReportList);

qapi_Status_t _qapi_ZB_CL_Default_Response(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_APSDE_Data_Indication_t *APSDEData, const qapi_ZB_CL_Header_t *ZCLHeader, qapi_Status_t Status);

qapi_Status_t _qapi_ZB_CL_Generic_Response(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_APSDE_Data_Indication_t *APSDEData, const qapi_ZB_CL_Header_t *ZCLHeader, uint8_t CommandId, uint8_t PayloadLength, uint8_t *PayLoad);
