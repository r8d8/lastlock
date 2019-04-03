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

#include "qapi_ble_dis.h"

int _qapi_BLE_DIS_Initialize_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t *ServiceID);

int _qapi_BLE_DIS_Initialize_Service_Handle_Range(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_DIS_Cleanup_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

uint32_t _qapi_BLE_DIS_Query_Number_Attributes(uint8_t TargetID);

int _qapi_BLE_DIS_Set_Manufacturer_Name(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *ManufacturerName);

int _qapi_BLE_DIS_Query_Manufacturer_Name(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *ManufacturerName);

int _qapi_BLE_DIS_Set_Model_Number(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *ModelNumber);

int _qapi_BLE_DIS_Query_Model_Number(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *ModelNumber);

int _qapi_BLE_DIS_Set_Serial_Number(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *SerialNumber);

int _qapi_BLE_DIS_Query_Serial_Number(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *SerialNumber);

int _qapi_BLE_DIS_Set_Hardware_Revision(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *Hardware_Revision);

int _qapi_BLE_DIS_Query_Hardware_Revision(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *Hardware_Revision);

int _qapi_BLE_DIS_Set_Firmware_Revision(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *FirmwareRevision);

int _qapi_BLE_DIS_Query_Firmware_Revision(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *FirmwareRevision);

int _qapi_BLE_DIS_Set_Software_Revision(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *SoftwareRevision);

int _qapi_BLE_DIS_Query_Software_Revision(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, char *SoftwareRevision);

int _qapi_BLE_DIS_Set_System_ID(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_System_ID_Value_t *SystemID);

int _qapi_BLE_DIS_Query_System_ID(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_System_ID_Value_t *SystemID);

int _qapi_BLE_DIS_Set_IEEE_Certification_Data(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t Length, uint8_t *IEEE_Certification_Data);

int _qapi_BLE_DIS_Query_IEEE_Certification_Data(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t *IEEE_Certification_Data);

int _qapi_BLE_DIS_Set_PNP_ID(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data);

int _qapi_BLE_DIS_Query_PNP_ID(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data);

int _qapi_BLE_DIS_Decode_PNP_ID(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data);
