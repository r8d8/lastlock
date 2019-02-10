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

#include "qapi_ble_hrs.h"

int _qapi_BLE_HRS_Initialize_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t Supported_Commands, qapi_BLE_HRS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

int _qapi_BLE_HRS_Initialize_Service_Handle_Range(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t Supported_Commands, qapi_BLE_HRS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_HRS_Cleanup_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

unsigned int _qapi_BLE_HRS_Query_Number_Attributes(uint8_t TargetID);

int _qapi_BLE_HRS_Set_Body_Sensor_Location(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t Body_Sensor_Location);

int _qapi_BLE_HRS_Query_Body_Sensor_Location(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t *Body_Sensor_Location);

int _qapi_BLE_HRS_Read_Client_Configuration_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint16_t Client_Configuration);

int _qapi_BLE_HRS_Notify_Heart_Rate_Measurement(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_HRS_Heart_Rate_Measurement_Data_t *Heart_Rate_Measurement);

int _qapi_BLE_HRS_Decode_Heart_Rate_Measurement(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_HRS_Heart_Rate_Measurement_Data_t *HeartRateMeasurement);

int _qapi_BLE_HRS_Decode_Body_Sensor_Location(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, uint8_t *BodySensorLocation);

int _qapi_BLE_HRS_Format_Heart_Rate_Control_Command(uint8_t TargetID, qapi_BLE_HRS_Heart_Rate_Control_Command_t Command, uint32_t BufferLength, uint8_t *Buffer);
