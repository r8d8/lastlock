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

#include "qapi_ble_lns.h"

int _qapi_BLE_LNS_Initialize_Service(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_LNS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

int _qapi_BLE_LNS_Initialize_Service_Handle_Range(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_LNS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_LNS_Cleanup_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

unsigned int _qapi_BLE_LNS_Query_Number_Attributes(uint8_t TargetID);

int _qapi_BLE_LNS_Read_Client_Configuration_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint16_t ClientConfiguration);

int _qapi_BLE_LNS_Set_LN_Feature(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t SupportedFeatures);

int _qapi_BLE_LNS_Query_LN_Feature(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t *SupportedFeatures);

int _qapi_BLE_LNS_Notify_Location_And_Speed(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_LNS_Location_Speed_Data_t *LocationAndSpeedData);

int _qapi_BLE_LNS_Set_Position_Quality(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_LNS_Position_Quality_Data_t *Position_Quality);

int _qapi_BLE_LNS_Query_Position_Quality(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_LNS_Position_Quality_Data_t *Position_Quality);

int _qapi_BLE_LNS_Notify_Navigation(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_LNS_Navigation_Data_t *Navigation);

int _qapi_BLE_LNS_LN_Control_Point_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t TransactionID, uint8_t ErrorCode);

int _qapi_BLE_LNS_Indicate_LN_Control_Point_Result(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_LNS_LNCP_Command_Type_t RequestOpCode, uint8_t ResponseCode);

int _qapi_BLE_LNS_Indicate_Number_Of_Routes(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_LNS_LNCP_Command_Type_t RequestOpCode, uint8_t ResponseCode, uint16_t NumberOfRoutes);

int _qapi_BLE_LNS_Indicate_Name_Of_Route(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_LNS_LNCP_Command_Type_t RequestOpCode, uint8_t ResponseCode, char *NameOfRoute);

int _qapi_BLE_LNS_Format_LN_Control_Point_Command(uint8_t TargetID, qapi_BLE_LNS_LN_Control_Point_Format_Data_t *FormatData, uint32_t *BufferLength, uint8_t *Buffer);

int _qapi_BLE_LNS_Decode_LN_Control_Point_Response(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_LNS_LN_Control_Point_Response_Data_t *LNCPResponseData);

void _qapi_BLE_LNS_Free_LN_Control_Point_Response(uint8_t TargetID, qapi_BLE_LNS_LN_Control_Point_Response_Data_t *LNCPResponseData);

int _qapi_BLE_LNS_Decode_Location_And_Speed(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_LNS_Location_Speed_Data_t *LocationAndSpeedData);

int _qapi_BLE_LNS_Decode_Navigation(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_LNS_Navigation_Data_t *NavigationData);

int _qapi_BLE_LNS_Decode_Position_Quality(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_LNS_Position_Quality_Data_t *PositionQualityData);
