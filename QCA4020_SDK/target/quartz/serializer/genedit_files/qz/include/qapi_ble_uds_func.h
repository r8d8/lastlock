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

#ifndef __QAPI_BLE_UDS_FUNC_H__
#define __QAPI_BLE_UDS_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_BLE_UDS_Initialize_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Initialize_Service_Handle_Range(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Cleanup_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Query_Number_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Read_Characteristic_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Write_Characteristic_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Prepare_Write_Characteristic_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Read_CCCD_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Write_CCCD_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Database_Change_Increment_Read_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Database_Change_Increment_Write_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Notify_Database_Change_Increment(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_User_Index_Read_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_User_Control_Point_Write_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Indicate_User_Control_Point_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Format_UDS_Characteristic_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Decode_UDS_Characteristic_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Format_User_Control_Point_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_UDS_Decode_User_Control_Point_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_ble_uds_funclist[] =
{
   Handle_qapi_BLE_UDS_Initialize_Service, /* Function Index = 0 */
   Handle_qapi_BLE_UDS_Initialize_Service_Handle_Range, /* Function Index = 1 */
   Handle_qapi_BLE_UDS_Cleanup_Service, /* Function Index = 2 */
   Handle_qapi_BLE_UDS_Query_Number_Attributes, /* Function Index = 3 */
   Handle_qapi_BLE_UDS_Read_Characteristic_Request_Response, /* Function Index = 4 */
   Handle_qapi_BLE_UDS_Write_Characteristic_Request_Response, /* Function Index = 5 */
   Handle_qapi_BLE_UDS_Prepare_Write_Characteristic_Request_Response, /* Function Index = 6 */
   Handle_qapi_BLE_UDS_Read_CCCD_Request_Response, /* Function Index = 7 */
   Handle_qapi_BLE_UDS_Write_CCCD_Request_Response, /* Function Index = 8 */
   Handle_qapi_BLE_UDS_Database_Change_Increment_Read_Request_Response, /* Function Index = 9 */
   Handle_qapi_BLE_UDS_Database_Change_Increment_Write_Request_Response, /* Function Index = 10 */
   Handle_qapi_BLE_UDS_Notify_Database_Change_Increment, /* Function Index = 11 */
   Handle_qapi_BLE_UDS_User_Index_Read_Request_Response, /* Function Index = 12 */
   Handle_qapi_BLE_UDS_User_Control_Point_Write_Request_Response, /* Function Index = 13 */
   Handle_qapi_BLE_UDS_Indicate_User_Control_Point_Response, /* Function Index = 14 */
   Handle_qapi_BLE_UDS_Format_UDS_Characteristic_Request, /* Function Index = 15 */
   Handle_qapi_BLE_UDS_Decode_UDS_Characteristic_Response, /* Function Index = 16 */
   Handle_qapi_BLE_UDS_Format_User_Control_Point_Request, /* Function Index = 17 */
   Handle_qapi_BLE_UDS_Decode_User_Control_Point_Response, /* Function Index = 18 */

};

#define QAPI_BLE_UDS_FUNC_LIST_SIZE   (sizeof(qapi_ble_uds_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_BLE_UDS_FUNC_H__
