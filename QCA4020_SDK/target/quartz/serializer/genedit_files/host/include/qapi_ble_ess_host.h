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

#include "qapi_ble_ess.h"

int _qapi_BLE_ESS_Initialize_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t ServiceFlags, qapi_BLE_ESS_Initialize_Data_t *InitializeData, qapi_BLE_ESS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

int _qapi_BLE_ESS_Initialize_Service_Handle_Range(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t ServiceFlags, qapi_BLE_ESS_Initialize_Data_t *InitializeData, qapi_BLE_ESS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_ESS_Cleanup_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

unsigned int _qapi_BLE_ESS_Query_Number_Attributes(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

int _qapi_BLE_ESS_Read_Characteristic_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_ESS_Characteristic_Data_t *CharacteristicData);

int _qapi_BLE_ESS_Read_CCCD_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, uint16_t Configuration);

int _qapi_BLE_ESS_Write_CCCD_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo);

int _qapi_BLE_ESS_Query_Extended_Properties(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, uint16_t *ExtendedProperties);

int _qapi_BLE_ESS_Read_ES_Measurement_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_ESS_ES_Measurement_Data_t *MeasurementData);

int _qapi_BLE_ESS_Read_ES_Trigger_Setting_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_ESS_ES_Trigger_Setting_Instance_t Instance, qapi_BLE_ESS_ES_Trigger_Setting_Data_t *TriggerSetting);

int _qapi_BLE_ESS_Write_ES_Trigger_Setting_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_ESS_ES_Trigger_Setting_Instance_t Instance);

int _qapi_BLE_ESS_Read_ES_Configuration_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, uint8_t Configuration);

int _qapi_BLE_ESS_Write_ES_Configuration_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo);

int _qapi_BLE_ESS_Read_User_Description_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, char *UserDescription);

int _qapi_BLE_ESS_Write_User_Description_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo);

int _qapi_BLE_ESS_Read_Valid_Range_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_ESS_Valid_Range_Data_t *ValidRange);

int _qapi_BLE_ESS_Read_Descriptor_Value_Changed_CCCD_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, uint16_t Configuration);

int _qapi_BLE_ESS_Write_Descriptor_Value_Changed_CCCD_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

int _qapi_BLE_ESS_Notify_Characteristic(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_ESS_Characteristic_Data_t *CharacteristicData);

int _qapi_BLE_ESS_Indicate_Descriptor_Value_Changed(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_ESS_Descriptor_Value_Changed_Data_t *DescriptorValueChanged);

int _qapi_BLE_ESS_Decode_Characteristic(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_ESS_Characteristic_Type_t Type, qapi_BLE_ESS_Characteristic_Data_t *CharacteristicData);

int _qapi_BLE_ESS_Decode_ES_Measurement(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_ESS_ES_Measurement_Data_t *MeasurementData);

int _qapi_BLE_ESS_Format_ES_Trigger_Setting_Request(uint8_t TargetID, qapi_BLE_ESS_Characteristic_Type_t Type, qapi_BLE_ESS_ES_Trigger_Setting_Data_t *TriggerSetting, uint32_t BufferLength, uint8_t *Buffer);

int _qapi_BLE_ESS_Decode_ES_Trigger_Setting(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_ESS_Characteristic_Type_t Type, qapi_BLE_ESS_ES_Trigger_Setting_Data_t *TriggerSetting);

int _qapi_BLE_ESS_Decode_Valid_Range(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_ESS_Characteristic_Type_t Type, qapi_BLE_ESS_Valid_Range_Data_t *ValidRange);

int _qapi_BLE_ESS_Decode_Descriptor_Value_Changed(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_ESS_Descriptor_Value_Changed_Data_t *DescriptorValueChanged);
