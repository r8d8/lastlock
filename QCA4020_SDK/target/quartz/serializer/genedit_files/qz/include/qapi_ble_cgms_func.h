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

#ifndef __QAPI_BLE_CGMS_FUNC_H__
#define __QAPI_BLE_CGMS_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_BLE_CGMS_Initialize_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Initialize_Service_Handle_Range(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Cleanup_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Query_Number_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Read_Client_Configuration_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Notify_CGMS_Measurements(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Feature_Read_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Status_Read_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Session_Start_Time_Read_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Session_Start_Time_Write_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Session_Run_Time_Read_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Record_Access_Control_Point_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Indicate_Number_Of_Stored_Records(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Indicate_Record_Access_Control_Point_Result(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Specific_Ops_Control_Point_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Indicate_CGMS_Specific_Ops_Control_Point_Result(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Indicate_Communication_Interval(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Indicate_Calibration_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Indicate_Alert_Level(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Decode_CGMS_Measurement(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Decode_CGMS_Feature(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Decode_CGMS_Status(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Decode_Session_Start_Time(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Format_Session_Start_Time(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Decode_Session_Run_Time(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Decode_Record_Access_Control_Point_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Format_Record_Access_Control_Point_Command(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Decode_CGMS_Specific_Ops_Control_Point_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_CGMS_Format_CGMS_Specific_Ops_Control_Point_Command(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_ble_cgms_funclist[] =
{
   Handle_qapi_BLE_CGMS_Initialize_Service, /* Function Index = 0 */
   Handle_qapi_BLE_CGMS_Initialize_Service_Handle_Range, /* Function Index = 1 */
   Handle_qapi_BLE_CGMS_Cleanup_Service, /* Function Index = 2 */
   Handle_qapi_BLE_CGMS_Query_Number_Attributes, /* Function Index = 3 */
   Handle_qapi_BLE_CGMS_Read_Client_Configuration_Response, /* Function Index = 4 */
   Handle_qapi_BLE_CGMS_Notify_CGMS_Measurements, /* Function Index = 5 */
   Handle_qapi_BLE_CGMS_Feature_Read_Request_Response, /* Function Index = 6 */
   Handle_qapi_BLE_CGMS_Status_Read_Request_Response, /* Function Index = 7 */
   Handle_qapi_BLE_CGMS_Session_Start_Time_Read_Request_Response, /* Function Index = 8 */
   Handle_qapi_BLE_CGMS_Session_Start_Time_Write_Request_Response, /* Function Index = 9 */
   Handle_qapi_BLE_CGMS_Session_Run_Time_Read_Request_Response, /* Function Index = 10 */
   Handle_qapi_BLE_CGMS_Record_Access_Control_Point_Response, /* Function Index = 11 */
   Handle_qapi_BLE_CGMS_Indicate_Number_Of_Stored_Records, /* Function Index = 12 */
   Handle_qapi_BLE_CGMS_Indicate_Record_Access_Control_Point_Result, /* Function Index = 13 */
   Handle_qapi_BLE_CGMS_Specific_Ops_Control_Point_Response, /* Function Index = 14 */
   Handle_qapi_BLE_CGMS_Indicate_CGMS_Specific_Ops_Control_Point_Result, /* Function Index = 15 */
   Handle_qapi_BLE_CGMS_Indicate_Communication_Interval, /* Function Index = 16 */
   Handle_qapi_BLE_CGMS_Indicate_Calibration_Data, /* Function Index = 17 */
   Handle_qapi_BLE_CGMS_Indicate_Alert_Level, /* Function Index = 18 */
   Handle_qapi_BLE_CGMS_Decode_CGMS_Measurement, /* Function Index = 19 */
   Handle_qapi_BLE_CGMS_Decode_CGMS_Feature, /* Function Index = 20 */
   Handle_qapi_BLE_CGMS_Decode_CGMS_Status, /* Function Index = 21 */
   Handle_qapi_BLE_CGMS_Decode_Session_Start_Time, /* Function Index = 22 */
   Handle_qapi_BLE_CGMS_Format_Session_Start_Time, /* Function Index = 23 */
   Handle_qapi_BLE_CGMS_Decode_Session_Run_Time, /* Function Index = 24 */
   Handle_qapi_BLE_CGMS_Decode_Record_Access_Control_Point_Response, /* Function Index = 25 */
   Handle_qapi_BLE_CGMS_Format_Record_Access_Control_Point_Command, /* Function Index = 26 */
   Handle_qapi_BLE_CGMS_Decode_CGMS_Specific_Ops_Control_Point_Response, /* Function Index = 27 */
   Handle_qapi_BLE_CGMS_Format_CGMS_Specific_Ops_Control_Point_Command, /* Function Index = 28 */

};

#define QAPI_BLE_CGMS_FUNC_LIST_SIZE   (sizeof(qapi_ble_cgms_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_BLE_CGMS_FUNC_H__
