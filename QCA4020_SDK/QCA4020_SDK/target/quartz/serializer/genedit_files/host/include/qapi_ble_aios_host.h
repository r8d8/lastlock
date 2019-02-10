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

#include "qapi_ble_aios.h"

int _qapi_BLE_AIOS_Initialize_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t Service_Flags, qapi_BLE_AIOS_Initialize_Data_t *InitializeData, qapi_BLE_AIOS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

int _qapi_BLE_AIOS_Initialize_Service_Handle_Range(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t Service_Flags, qapi_BLE_AIOS_Initialize_Data_t *InitializeData, qapi_BLE_AIOS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_AIOS_Cleanup_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

unsigned int _qapi_BLE_AIOS_Query_Number_Attributes(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

int _qapi_BLE_AIOS_Read_CCCD_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, uint16_t ClientConfiguration);

int _qapi_BLE_AIOS_Write_CCCD_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo);

int _qapi_BLE_AIOS_Read_Presentation_Format_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Presentation_Format_Data_t *PresentationFormatData);

int _qapi_BLE_AIOS_Read_User_Description_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, char *UserDescription);

int _qapi_BLE_AIOS_Write_User_Description_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo);

int _qapi_BLE_AIOS_Read_Value_Trigger_Setting_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Value_Trigger_Data_t *ValueTriggerData);

int _qapi_BLE_AIOS_Write_Value_Trigger_Setting_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo);

int _qapi_BLE_AIOS_Read_Time_Trigger_Setting_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Time_Trigger_Data_t *TimeTriggerData);

int _qapi_BLE_AIOS_Write_Time_Trigger_Setting_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo);

int _qapi_BLE_AIOS_Read_Number_Of_Digitals_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, uint8_t NumberOfDigitals);

int _qapi_BLE_AIOS_Read_Valid_Range_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Valid_Range_Data_t *ValidRangeData);

int _qapi_BLE_AIOS_Read_Characteristic_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Characteristic_Data_t *CharacteristicData);

int _qapi_BLE_AIOS_Write_Characteristic_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo);

int _qapi_BLE_AIOS_Notify_Characteristic(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Characteristic_Data_t *CharacteristicData);

int _qapi_BLE_AIOS_Indicate_Characteristic(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Characteristic_Data_t *CharacteristicData);

int _qapi_BLE_AIOS_Decode_Presentation_Format(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_AIOS_Presentation_Format_Data_t *PresentationFormatData);

int _qapi_BLE_AIOS_Format_Value_Trigger_Setting(uint8_t TargetID, qapi_BLE_AIOS_Value_Trigger_Data_t *ValueTriggerData, uint32_t BufferLength, uint8_t *Buffer);

int _qapi_BLE_AIOS_Decode_Value_Trigger_Setting(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_AIOS_Value_Trigger_Data_t *ValueTriggerData);

int _qapi_BLE_AIOS_Format_Time_Trigger_Setting(uint8_t TargetID, qapi_BLE_AIOS_Time_Trigger_Data_t * TimeTriggerData, uint32_t BufferLength, uint8_t *Buffer);

int _qapi_BLE_AIOS_Decode_Time_Trigger_Setting(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_AIOS_Time_Trigger_Data_t *TimeTriggerData);

int _qapi_BLE_AIOS_Decode_Valid_Range(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_AIOS_Valid_Range_Data_t *ValidRangeData);
