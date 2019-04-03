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

#ifndef __QAPI_BLE_GATT_FUNC_H__
#define __QAPI_BLE_GATT_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_BLE_GATT_Initialize(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Cleanup(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Register_Connection_Events(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Un_Register_Connection_Events(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Register_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Un_Register_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Read_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Write_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Execute_Write_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Error_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Handle_Value_Indication(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Handle_Value_Notification(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Verify_Signature(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Service_Changed_Read_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Service_Changed_CCCD_Read_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Service_Changed_Indication(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Exchange_MTU_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Discover_Services(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Discover_Services_By_UUID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Discover_Included_Services(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Discover_Characteristics(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Discover_Characteristic_Descriptors(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Read_Value_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Read_Long_Value_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Read_Value_By_UUID_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Read_Multiple_Values_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Write_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Write_Without_Response_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Signed_Write_Without_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Prepare_Write_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Execute_Write_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Handle_Value_Confirmation(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Start_Service_Discovery(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Start_Service_Discovery_Handle_Range(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Stop_Service_Discovery(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Cancel_Transaction(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Query_Maximum_Supported_MTU(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Change_Maximum_Supported_MTU(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Query_Connection_MTU(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Query_Connection_ID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Query_Transaction_Opcode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Set_Queuing_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Get_Queuing_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GATT_Query_Service_Range_Availability(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_ble_gatt_funclist[] =
{
   Handle_qapi_BLE_GATT_Initialize, /* Function Index = 0 */
   Handle_qapi_BLE_GATT_Cleanup, /* Function Index = 1 */
   Handle_qapi_BLE_GATT_Register_Connection_Events, /* Function Index = 2 */
   Handle_qapi_BLE_GATT_Un_Register_Connection_Events, /* Function Index = 3 */
   Handle_qapi_BLE_GATT_Register_Service, /* Function Index = 4 */
   Handle_qapi_BLE_GATT_Un_Register_Service, /* Function Index = 5 */
   Handle_qapi_BLE_GATT_Read_Response, /* Function Index = 6 */
   Handle_qapi_BLE_GATT_Write_Response, /* Function Index = 7 */
   Handle_qapi_BLE_GATT_Execute_Write_Response, /* Function Index = 8 */
   Handle_qapi_BLE_GATT_Error_Response, /* Function Index = 9 */
   Handle_qapi_BLE_GATT_Handle_Value_Indication, /* Function Index = 10 */
   Handle_qapi_BLE_GATT_Handle_Value_Notification, /* Function Index = 11 */
   Handle_qapi_BLE_GATT_Verify_Signature, /* Function Index = 12 */
   Handle_qapi_BLE_GATT_Service_Changed_Read_Response, /* Function Index = 13 */
   Handle_qapi_BLE_GATT_Service_Changed_CCCD_Read_Response, /* Function Index = 14 */
   Handle_qapi_BLE_GATT_Service_Changed_Indication, /* Function Index = 15 */
   Handle_qapi_BLE_GATT_Exchange_MTU_Request, /* Function Index = 16 */
   Handle_qapi_BLE_GATT_Discover_Services, /* Function Index = 17 */
   Handle_qapi_BLE_GATT_Discover_Services_By_UUID, /* Function Index = 18 */
   Handle_qapi_BLE_GATT_Discover_Included_Services, /* Function Index = 19 */
   Handle_qapi_BLE_GATT_Discover_Characteristics, /* Function Index = 20 */
   Handle_qapi_BLE_GATT_Discover_Characteristic_Descriptors, /* Function Index = 21 */
   Handle_qapi_BLE_GATT_Read_Value_Request, /* Function Index = 22 */
   Handle_qapi_BLE_GATT_Read_Long_Value_Request, /* Function Index = 23 */
   Handle_qapi_BLE_GATT_Read_Value_By_UUID_Request, /* Function Index = 24 */
   Handle_qapi_BLE_GATT_Read_Multiple_Values_Request, /* Function Index = 25 */
   Handle_qapi_BLE_GATT_Write_Request, /* Function Index = 26 */
   Handle_qapi_BLE_GATT_Write_Without_Response_Request, /* Function Index = 27 */
   Handle_qapi_BLE_GATT_Signed_Write_Without_Response, /* Function Index = 28 */
   Handle_qapi_BLE_GATT_Prepare_Write_Request, /* Function Index = 29 */
   Handle_qapi_BLE_GATT_Execute_Write_Request, /* Function Index = 30 */
   Handle_qapi_BLE_GATT_Handle_Value_Confirmation, /* Function Index = 31 */
   Handle_qapi_BLE_GATT_Start_Service_Discovery, /* Function Index = 32 */
   Handle_qapi_BLE_GATT_Start_Service_Discovery_Handle_Range, /* Function Index = 33 */
   Handle_qapi_BLE_GATT_Stop_Service_Discovery, /* Function Index = 34 */
   Handle_qapi_BLE_GATT_Cancel_Transaction, /* Function Index = 35 */
   Handle_qapi_BLE_GATT_Query_Maximum_Supported_MTU, /* Function Index = 36 */
   Handle_qapi_BLE_GATT_Change_Maximum_Supported_MTU, /* Function Index = 37 */
   Handle_qapi_BLE_GATT_Query_Connection_MTU, /* Function Index = 38 */
   Handle_qapi_BLE_GATT_Query_Connection_ID, /* Function Index = 39 */
   Handle_qapi_BLE_GATT_Query_Transaction_Opcode, /* Function Index = 40 */
   Handle_qapi_BLE_GATT_Set_Queuing_Parameters, /* Function Index = 41 */
   Handle_qapi_BLE_GATT_Get_Queuing_Parameters, /* Function Index = 42 */
   Handle_qapi_BLE_GATT_Query_Service_Range_Availability, /* Function Index = 43 */

};

#define QAPI_BLE_GATT_FUNC_LIST_SIZE   (sizeof(qapi_ble_gatt_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_BLE_GATT_FUNC_H__
