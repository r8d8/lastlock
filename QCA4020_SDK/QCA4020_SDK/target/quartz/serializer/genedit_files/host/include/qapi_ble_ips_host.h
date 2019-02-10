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

#include "qapi_ble_ips.h"

int _qapi_BLE_IPS_Initialize_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t Service_Flags, qapi_BLE_IPS_Initialize_Data_t *InitializeData, qapi_BLE_IPS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

int _qapi_BLE_IPS_Initialize_Service_Handle_Range(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t Service_Flags, qapi_BLE_IPS_Initialize_Data_t *InitializeData, qapi_BLE_IPS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_IPS_Cleanup_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

unsigned int _qapi_BLE_IPS_Query_Number_Attributes(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

int _qapi_BLE_IPS_Set_Indoor_Positioning_Configuration(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t Configuration);

int _qapi_BLE_IPS_Query_Indoor_Positioning_Configuration(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t *Configuration);

int _qapi_BLE_IPS_Set_Latitude(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, int32_t Latitude);

int _qapi_BLE_IPS_Query_Latitude(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, int32_t *Latitude);

int _qapi_BLE_IPS_Set_Longitude(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, int32_t Longitude);

int _qapi_BLE_IPS_Query_Longitude(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, int32_t *Longitude);

int _qapi_BLE_IPS_Set_Local_North_Coordinate(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, int16_t LocalCoordinate);

int _qapi_BLE_IPS_Query_Local_North_Coordinate(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, int16_t *LocalCoordinate);

int _qapi_BLE_IPS_Set_Local_East_Coordinate(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, int16_t LocalCoordinate);

int _qapi_BLE_IPS_Query_Local_East_Coordinate(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, int16_t *LocalCoordinate);

int _qapi_BLE_IPS_Set_Floor_Number(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t FloorNumber);

int _qapi_BLE_IPS_Query_Floor_Number(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t *FloorNumber);

int _qapi_BLE_IPS_Set_Altitude(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint16_t Altitude);

int _qapi_BLE_IPS_Query_Altitude(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint16_t *Altitude);

int _qapi_BLE_IPS_Set_Uncertainty(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t Uncertainty);

int _qapi_BLE_IPS_Query_Uncertainty(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t *Uncertainty);

int _qapi_BLE_IPS_Set_Location_Name(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *LocationName);

int _qapi_BLE_IPS_Query_Location_Name(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t LocationNameLength, char *LocationName);

int _qapi_BLE_IPS_Authorization_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, boolean_t NotAuthorized);

int _qapi_BLE_IPS_Format_Broadcasting_Data(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t *BufferLength, uint8_t *Buffer);

int _qapi_BLE_IPS_Decode_Broadcasting_Data(uint8_t TargetID, uint8_t BufferLength, uint8_t *Buffer, qapi_BLE_IPS_Broadcast_Data_t *BroadcastData);
