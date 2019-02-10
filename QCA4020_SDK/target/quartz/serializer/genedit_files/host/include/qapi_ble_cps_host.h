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

#include "qapi_ble_cps.h"

int _qapi_BLE_CPS_Initialize_Service(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_CPS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

int _qapi_BLE_CPS_Initialize_Service_Handle_Range(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_CPS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_CPS_Cleanup_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

unsigned int _qapi_BLE_CPS_Query_Number_Attributes(uint8_t TargetID);

int _qapi_BLE_CPS_Read_Client_Configuration_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint16_t ClientConfiguration);

int _qapi_BLE_CPS_Vector_Client_Configuration_Update_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t TransactionID, uint8_t ErrorCode);

int _qapi_BLE_CPS_Read_CP_Measurement_Server_Configuration_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint16_t ServerConfiguration);

int _qapi_BLE_CPS_Set_Feature(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t SupportedFeatures);

int _qapi_BLE_CPS_Query_Feature(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t *SupportedFeatures);

int _qapi_BLE_CPS_Notify_CP_Measurement(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_CPS_Measurement_Data_t *MeasurementData);

int _qapi_BLE_CPS_Set_Sensor_Location(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t SensorLocation);

int _qapi_BLE_CPS_Query_Sensor_Location(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t *SensorLocation);

int _qapi_BLE_CPS_Notify_CP_Vector(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_CPS_Vector_Data_t *VectorData);

int _qapi_BLE_CPS_Control_Point_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t TransactionID, uint8_t ErrorCode);

int _qapi_BLE_CPS_Indicate_Control_Point_Result(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_CPS_Control_Point_Command_Type_t CommandType, uint8_t ResponseCode);

int _qapi_BLE_CPS_Indicate_Control_Point_Result_With_Data(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_CPS_Control_Point_Indication_Data_t *IndicationData);

int _qapi_BLE_CPS_Format_CP_Measurement(uint8_t TargetID, qapi_BLE_CPS_Measurement_Data_t *MeasurementData, uint16_t *BufferLength, uint8_t *Buffer);

int _qapi_BLE_CPS_Decode_CP_Measurement(uint8_t TargetID, uint32_t BufferLength, uint8_t *Buffer, qapi_BLE_CPS_Measurement_Data_t *MeasurementData);

qapi_BLE_CPS_Vector_Data_t *_qapi_BLE_CPS_Decode_CP_Vector(uint8_t TargetID, uint32_t BufferLength, uint8_t *Buffer);

void _qapi_BLE_CPS_Free_CP_Vector_Data(uint8_t TargetID, qapi_BLE_CPS_Vector_Data_t * VectorData);

int _qapi_BLE_CPS_Decode_Control_Point_Response(uint8_t TargetID, uint32_t BufferLength, uint8_t *Buffer, qapi_BLE_CPS_Control_Point_Response_Data_t *ResponseData);

void _qapi_BLE_CPS_Free_Supported_Sensor_Locations_Data(uint8_t TargetID, uint8_t *SensorLocations);

int _qapi_BLE_CPS_Format_Control_Point_Command(uint8_t TargetID, qapi_BLE_CPS_Control_Point_Format_Data_t *FormatData, uint32_t *BufferLength, uint8_t *Buffer);
