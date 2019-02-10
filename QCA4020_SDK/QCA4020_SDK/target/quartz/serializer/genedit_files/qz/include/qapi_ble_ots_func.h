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

#ifndef __QAPI_BLE_OTS_FUNC_H__
#define __QAPI_BLE_OTS_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_BLE_OTS_Initialize_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Initialize_Service_Handle_Range(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Cleanup_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Query_Number_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Read_CCCD_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Write_CCCD_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Read_OTS_Feature_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Read_Object_Metadata_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Write_Object_Metadata_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Write_OACP_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Indicate_OACP_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Write_OLCP_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Indicate_OLCP_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Read_Object_List_Filter_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Write_Object_List_Filter_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Prepare_Write_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Indicate_Object_Changed(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Calculate_CRC_32(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Decode_OTS_Feature(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Format_Object_Metadata(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Decode_Object_Metadata(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Format_OACP_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Decode_OACP_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Format_OLCP_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Decode_OLCP_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Format_Object_List_Filter_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Decode_Object_List_Filter_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Decode_Object_Changed_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Channel_Open_Connection_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Channel_Get_Connection_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Channel_Set_Connection_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Format_Directory_Listing_Object_Contents(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Channel_Connect_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Decode_Directory_Listing_Object_Contents(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Channel_Close_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Channel_Send_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_OTS_Channel_Grant_Credits(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_ble_ots_funclist[] =
{
   Handle_qapi_BLE_OTS_Initialize_Service, /* Function Index = 0 */
   Handle_qapi_BLE_OTS_Initialize_Service_Handle_Range, /* Function Index = 1 */
   Handle_qapi_BLE_OTS_Cleanup_Service, /* Function Index = 2 */
   Handle_qapi_BLE_OTS_Query_Number_Attributes, /* Function Index = 3 */
   Handle_qapi_BLE_OTS_Read_CCCD_Request_Response, /* Function Index = 4 */
   Handle_qapi_BLE_OTS_Write_CCCD_Request_Response, /* Function Index = 5 */
   Handle_qapi_BLE_OTS_Read_OTS_Feature_Request_Response, /* Function Index = 6 */
   Handle_qapi_BLE_OTS_Read_Object_Metadata_Request_Response, /* Function Index = 7 */
   Handle_qapi_BLE_OTS_Write_Object_Metadata_Request_Response, /* Function Index = 8 */
   Handle_qapi_BLE_OTS_Write_OACP_Request_Response, /* Function Index = 9 */
   Handle_qapi_BLE_OTS_Indicate_OACP_Response, /* Function Index = 10 */
   Handle_qapi_BLE_OTS_Write_OLCP_Request_Response, /* Function Index = 11 */
   Handle_qapi_BLE_OTS_Indicate_OLCP_Response, /* Function Index = 12 */
   Handle_qapi_BLE_OTS_Read_Object_List_Filter_Request_Response, /* Function Index = 13 */
   Handle_qapi_BLE_OTS_Write_Object_List_Filter_Request_Response, /* Function Index = 14 */
   Handle_qapi_BLE_OTS_Prepare_Write_Request_Response, /* Function Index = 15 */
   Handle_qapi_BLE_OTS_Indicate_Object_Changed, /* Function Index = 16 */
   Handle_qapi_BLE_OTS_Calculate_CRC_32, /* Function Index = 17 */
   Handle_qapi_BLE_OTS_Decode_OTS_Feature, /* Function Index = 18 */
   Handle_qapi_BLE_OTS_Format_Object_Metadata, /* Function Index = 19 */
   Handle_qapi_BLE_OTS_Decode_Object_Metadata, /* Function Index = 20 */
   Handle_qapi_BLE_OTS_Format_OACP_Request, /* Function Index = 21 */
   Handle_qapi_BLE_OTS_Decode_OACP_Response, /* Function Index = 22 */
   Handle_qapi_BLE_OTS_Format_OLCP_Request, /* Function Index = 23 */
   Handle_qapi_BLE_OTS_Decode_OLCP_Response, /* Function Index = 24 */
   Handle_qapi_BLE_OTS_Format_Object_List_Filter_Data, /* Function Index = 25 */
   Handle_qapi_BLE_OTS_Decode_Object_List_Filter_Data, /* Function Index = 26 */
   Handle_qapi_BLE_OTS_Decode_Object_Changed_Data, /* Function Index = 27 */
   Handle_qapi_BLE_OTS_Channel_Open_Connection_Request_Response, /* Function Index = 28 */
   Handle_qapi_BLE_OTS_Channel_Get_Connection_Mode, /* Function Index = 29 */
   Handle_qapi_BLE_OTS_Channel_Set_Connection_Mode, /* Function Index = 30 */
   Handle_qapi_BLE_OTS_Format_Directory_Listing_Object_Contents, /* Function Index = 31 */
   Handle_qapi_BLE_OTS_Channel_Connect_Request, /* Function Index = 32 */
   Handle_qapi_BLE_OTS_Decode_Directory_Listing_Object_Contents, /* Function Index = 33 */
   Handle_qapi_BLE_OTS_Channel_Close_Connection, /* Function Index = 34 */
   Handle_qapi_BLE_OTS_Channel_Send_Data, /* Function Index = 35 */
   Handle_qapi_BLE_OTS_Channel_Grant_Credits, /* Function Index = 36 */

};

#define QAPI_BLE_OTS_FUNC_LIST_SIZE   (sizeof(qapi_ble_ots_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_BLE_OTS_FUNC_H__
