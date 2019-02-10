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

#include "qapi_ble_hids.h"

int _qapi_BLE_HIDS_Initialize_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint8_t Flags, qapi_BLE_HIDS_HID_Information_Data_t *HIDInformation, uint32_t NumIncludedServices, uint32_t *ServiceIDList, uint32_t NumExternalReportReferences, qapi_BLE_GATT_UUID_t *ReferenceUUID, uint32_t NumReports, qapi_BLE_HIDS_Report_Reference_Data_t *ReportReference, qapi_BLE_HIDS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

int _qapi_BLE_HIDS_Initialize_Service_Handle_Range(uint8_t TargetID, uint32_t BluetoothStackID, uint8_t Flags, qapi_BLE_HIDS_HID_Information_Data_t *HIDInformation, uint32_t NumIncludedServices, uint32_t *ServiceIDList, uint32_t NumExternalReportReferences, qapi_BLE_GATT_UUID_t *ReferenceUUID, uint32_t NumReports, qapi_BLE_HIDS_Report_Reference_Data_t *ReportReference, qapi_BLE_HIDS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_HIDS_Cleanup_Service(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID);

uint32_t _qapi_BLE_HIDS_Query_Number_Attributes(uint8_t TargetID, uint8_t Flags, uint32_t NumIncludedServices, uint32_t NumExternalReportReferences, uint32_t NumReports, qapi_BLE_HIDS_Report_Reference_Data_t *ReportReference);

int _qapi_BLE_HIDS_Read_Client_Configuration_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint16_t Client_Configuration);

int _qapi_BLE_HIDS_Get_Protocol_Mode_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_HIDS_Protocol_Mode_t CurrentProtocolMode);

int _qapi_BLE_HIDS_Get_Report_Map_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, uint32_t ReportMapLength, uint8_t *ReportMap);

int _qapi_BLE_HIDS_Get_Report_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, qapi_BLE_HIDS_Report_Type_t ReportType, qapi_BLE_HIDS_Report_Reference_Data_t *ReportReferenceData, uint8_t ErrorCode, uint32_t ReportLength, uint8_t *Report);

int _qapi_BLE_HIDS_Set_Report_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, qapi_BLE_HIDS_Report_Type_t ReportType, qapi_BLE_HIDS_Report_Reference_Data_t *ReportReferenceData, uint8_t ErrorCode);

int _qapi_BLE_HIDS_Notify_Input_Report(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_HIDS_Report_Type_t ReportType, qapi_BLE_HIDS_Report_Reference_Data_t *ReportReferenceData, uint16_t InputReportLength, uint8_t *InputReportData);

int _qapi_BLE_HIDS_Decode_HID_Information(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_HIDS_HID_Information_Data_t *HIDSHIDInformation);

int _qapi_BLE_HIDS_Decode_Report_Reference(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_HIDS_Report_Reference_Data_t *ReportReferenceData);

int _qapi_BLE_HIDS_Decode_External_Report_Reference(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, qapi_BLE_GATT_UUID_t *ExternalReportReferenceUUID);

int _qapi_BLE_HIDS_Format_Protocol_Mode(uint8_t TargetID, qapi_BLE_HIDS_Protocol_Mode_t ProtocolMode, uint32_t BufferLength, uint8_t *Buffer);

int _qapi_BLE_HIDS_Format_Control_Point_Command(uint8_t TargetID, qapi_BLE_HIDS_Control_Point_Command_t Command, uint32_t BufferLength, uint8_t *Buffer);
