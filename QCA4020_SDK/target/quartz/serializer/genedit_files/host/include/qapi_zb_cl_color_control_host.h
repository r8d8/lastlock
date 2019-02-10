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

#include "qapi_zb_cl_color_control.h"

qapi_Status_t _qapi_ZB_CL_ColorControl_Create_Client(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_Cluster_t *Cluster, qapi_ZB_CL_Cluster_Info_t *Cluster_Info, qapi_ZB_CL_ColorControl_Client_CB_t Event_CB, uint32_t CB_Param);

qapi_Status_t _qapi_ZB_CL_ColorControl_Create_Server(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_Cluster_t *Cluster, uint16_t CapabilityFlag, uint8_t NumberOfPrimaries, qapi_ZB_CL_Cluster_Info_t *Cluster_Info, qapi_ZB_CL_ColorControl_Server_CB_t Event_CB, uint32_t CB_Param);

qapi_Status_t _qapi_ZB_CL_ColorControl_Populate_Attributes(uint8_t TargetID, qbool_t Server, uint16_t Capability, uint8_t NumberOfPrimaries, uint8_t *AttributeCount, qapi_ZB_CL_Attribute_t *AttributeList);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Move_To_Hue(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint16_t Hue, qapi_ZB_CL_ColorControl_Move_Mode_t Direction, uint16_t TransitionTime, qbool_t IsEnhanced);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Move_Hue(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, qapi_ZB_CL_ColorControl_Move_Mode_t MoveMode, uint16_t Rate, qbool_t IsEnhanced);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Step_Hue(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, qapi_ZB_CL_ColorControl_Move_Mode_t StepMode, uint16_t StepSize, uint16_t TransitionTime, qbool_t IsEnhanced);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Move_To_Saturation(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint8_t Saturation, uint16_t TransitionTime);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Move_Saturation(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, qapi_ZB_CL_ColorControl_Move_Mode_t MoveMode, uint8_t Rate);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Step_Saturation(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, qapi_ZB_CL_ColorControl_Move_Mode_t StepMode, uint8_t StepSize, uint8_t TransitionTime);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Move_To_HueAndSaturation(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint16_t Hue, uint8_t Saturation, uint16_t TransitionTime, qbool_t IsEnhanced);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Move_To_Color(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint16_t ColorX, uint16_t ColorY, uint16_t TransitionTime);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Move_Color(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, int16_t RateX, int16_t RateY);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Step_Color(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, int16_t StepX, int16_t StepY, uint16_t TransitionTime);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Move_To_Color_Temp(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, uint16_t ColorTempMireds, uint16_t TransitionTime);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Color_Loop_Set(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, const qapi_ZB_CL_ColorControl_Color_Loop_Set_t *ColorLoopSet);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Stop_Move_Step(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Move_Color_Temp(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, qapi_ZB_CL_ColorControl_Move_Mode_t MoveMode, uint16_t Rate, uint16_t Limit);

qapi_Status_t _qapi_ZB_CL_ColorControl_Send_Step_Color_Temp(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, const qapi_ZB_CL_General_Send_Info_t *SendInfo, const qapi_ZB_CL_ColorControl_Step_Color_Temp_t *StepColorTemp);
