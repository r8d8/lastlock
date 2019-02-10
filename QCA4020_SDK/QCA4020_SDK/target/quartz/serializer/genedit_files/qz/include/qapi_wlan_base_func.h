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

#ifndef __QAPI_WLAN_BASE_FUNC_H__
#define __QAPI_WLAN_BASE_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_WLAN_Coex_Control(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_Get_WLAN_Coex_Stats(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Add_Device(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Remove_Device(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Start_Scan(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Get_Scan_Results(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Commit(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Set_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Disconnect(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Set_Param(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Get_Param(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Suspend_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_Raw_Send(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_WPS_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_WPS_Await_Completion(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_WLAN_WPS_Connect(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_wlan_base_funclist[] =
{
   Handle_qapi_WLAN_Coex_Control, /* Function Index = 0 */
   Handle_qapi_Get_WLAN_Coex_Stats, /* Function Index = 1 */
   Handle_qapi_WLAN_Enable, /* Function Index = 2 */
   Handle_qapi_WLAN_Add_Device, /* Function Index = 3 */
   Handle_qapi_WLAN_Remove_Device, /* Function Index = 4 */
   Handle_qapi_WLAN_Start_Scan, /* Function Index = 5 */
   Handle_qapi_WLAN_Get_Scan_Results, /* Function Index = 6 */
   Handle_qapi_WLAN_Commit, /* Function Index = 7 */
   Handle_qapi_WLAN_Set_Callback, /* Function Index = 8 */
   NULL, /* Function Index = 9 */
   Handle_qapi_WLAN_Disconnect, /* Function Index = 10 */
   Handle_qapi_WLAN_Set_Param, /* Function Index = 11 */
   Handle_qapi_WLAN_Get_Param, /* Function Index = 12 */
   Handle_qapi_WLAN_Suspend_Start, /* Function Index = 13 */
   Handle_qapi_WLAN_Raw_Send, /* Function Index = 14 */
   Handle_qapi_WLAN_WPS_Start, /* Function Index = 15 */
   Handle_qapi_WLAN_WPS_Await_Completion, /* Function Index = 16 */
   Handle_qapi_WLAN_WPS_Connect, /* Function Index = 17 */
   NULL, /* Function Index = 18 */

};

#define QAPI_WLAN_BASE_FUNC_LIST_SIZE   (sizeof(qapi_wlan_base_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_WLAN_BASE_FUNC_H__
