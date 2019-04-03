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

#include "qapi_ble_gaps.h"

int _qapi_BLE_GAPS_Initialize_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t *ServiceID);

int _qapi_BLE_GAPS_Initialize_Service_Handle_Range(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_GAPS_Cleanup_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

uint32_t _qapi_BLE_GAPS_Query_Number_Attributes(uint8_t TargetID);

int _qapi_BLE_GAPS_Set_Device_Name(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *DeviceName);

int _qapi_BLE_GAPS_Query_Device_Name(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *NameBuffer);

int _qapi_BLE_GAPS_Set_Device_Appearance(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint16_t DeviceAppearance);

int _qapi_BLE_GAPS_Query_Device_Appearance(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint16_t *DeviceAppearance);

int _qapi_BLE_GAPS_Set_Preferred_Connection_Parameters(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters);

int _qapi_BLE_GAPS_Query_Preferred_Connection_Parameters(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters);

int _qapi_BLE_GAPS_Set_Central_Address_Resolution(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Central_Address_Resolution_t CentralAddressResolution);

int _qapi_BLE_GAPS_Query_Central_Address_Resolution(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Central_Address_Resolution_t *CentralAddressResolution);

int _qapi_BLE_GAPS_Decode_Preferred_Connection_Parameters(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters);

int _qapi_BLE_GAPS_Decode_Central_Address_Resolution(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_GAP_Central_Address_Resolution_t *CentralAddressResolution);
