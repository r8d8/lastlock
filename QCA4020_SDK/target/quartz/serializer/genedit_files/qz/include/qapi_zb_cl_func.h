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

#ifndef __QAPI_ZB_CL_FUNC_H__
#define __QAPI_ZB_CL_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_ZB_CL_Register_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Unregister_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Create_Cluster(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Destroy_Cluster(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Get_Cluster_Info(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Set_Profile_ID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Set_Min_Security(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Set_Tx_Options(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Get_Tx_Options(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Set_Discover_Route(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Get_Discover_Route(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Set_Radius(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Get_Radius(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Send_Command(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Read_Local_Attribute(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Write_Local_Attribute(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Read_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Write_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Configure_Reporting(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Read_Reporting_Config(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Discover_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Read_Attributes_Structured(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Write_Attributes_Structured(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Report_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Default_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_Generic_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_zb_cl_funclist[] =
{
   Handle_qapi_ZB_CL_Register_Callback, /* Function Index = 0 */
   Handle_qapi_ZB_CL_Unregister_Callback, /* Function Index = 1 */
   Handle_qapi_ZB_CL_Create_Cluster, /* Function Index = 2 */
   Handle_qapi_ZB_CL_Destroy_Cluster, /* Function Index = 3 */
   Handle_qapi_ZB_CL_Get_Cluster_Info, /* Function Index = 4 */
   Handle_qapi_ZB_CL_Set_Profile_ID, /* Function Index = 5 */
   Handle_qapi_ZB_CL_Set_Min_Security, /* Function Index = 6 */
   Handle_qapi_ZB_CL_Set_Tx_Options, /* Function Index = 7 */
   Handle_qapi_ZB_CL_Get_Tx_Options, /* Function Index = 8 */
   Handle_qapi_ZB_CL_Set_Discover_Route, /* Function Index = 9 */
   Handle_qapi_ZB_CL_Get_Discover_Route, /* Function Index = 10 */
   Handle_qapi_ZB_CL_Set_Radius, /* Function Index = 11 */
   Handle_qapi_ZB_CL_Get_Radius, /* Function Index = 12 */
   Handle_qapi_ZB_CL_Send_Command, /* Function Index = 13 */
   Handle_qapi_ZB_CL_Read_Local_Attribute, /* Function Index = 14 */
   Handle_qapi_ZB_CL_Write_Local_Attribute, /* Function Index = 15 */
   Handle_qapi_ZB_CL_Read_Attributes, /* Function Index = 16 */
   Handle_qapi_ZB_CL_Write_Attributes, /* Function Index = 17 */
   Handle_qapi_ZB_CL_Configure_Reporting, /* Function Index = 18 */
   Handle_qapi_ZB_CL_Read_Reporting_Config, /* Function Index = 19 */
   Handle_qapi_ZB_CL_Discover_Attributes, /* Function Index = 20 */
   Handle_qapi_ZB_CL_Read_Attributes_Structured, /* Function Index = 21 */
   Handle_qapi_ZB_CL_Write_Attributes_Structured, /* Function Index = 22 */
   Handle_qapi_ZB_CL_Report_Attributes, /* Function Index = 23 */
   Handle_qapi_ZB_CL_Default_Response, /* Function Index = 24 */
   Handle_qapi_ZB_CL_Generic_Response, /* Function Index = 25 */

};

#define QAPI_ZB_CL_FUNC_LIST_SIZE   (sizeof(qapi_zb_cl_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_ZB_CL_FUNC_H__
