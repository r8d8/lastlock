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

#ifndef __QAPI_ZB_CL_COLOR_CONTROL_FUNC_H__
#define __QAPI_ZB_CL_COLOR_CONTROL_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_ZB_CL_ColorControl_Create_Client(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Create_Server(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Populate_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Move_To_Hue(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Move_Hue(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Step_Hue(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Move_To_Saturation(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Move_Saturation(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Step_Saturation(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Move_To_HueAndSaturation(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Move_To_Color(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Move_Color(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Step_Color(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Move_To_Color_Temp(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Color_Loop_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Stop_Move_Step(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Move_Color_Temp(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_CL_ColorControl_Send_Step_Color_Temp(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_zb_cl_color_control_funclist[] =
{
   Handle_qapi_ZB_CL_ColorControl_Create_Client, /* Function Index = 0 */
   Handle_qapi_ZB_CL_ColorControl_Create_Server, /* Function Index = 1 */
   Handle_qapi_ZB_CL_ColorControl_Populate_Attributes, /* Function Index = 2 */
   Handle_qapi_ZB_CL_ColorControl_Send_Move_To_Hue, /* Function Index = 3 */
   Handle_qapi_ZB_CL_ColorControl_Send_Move_Hue, /* Function Index = 4 */
   Handle_qapi_ZB_CL_ColorControl_Send_Step_Hue, /* Function Index = 5 */
   Handle_qapi_ZB_CL_ColorControl_Send_Move_To_Saturation, /* Function Index = 6 */
   Handle_qapi_ZB_CL_ColorControl_Send_Move_Saturation, /* Function Index = 7 */
   Handle_qapi_ZB_CL_ColorControl_Send_Step_Saturation, /* Function Index = 8 */
   Handle_qapi_ZB_CL_ColorControl_Send_Move_To_HueAndSaturation, /* Function Index = 9 */
   Handle_qapi_ZB_CL_ColorControl_Send_Move_To_Color, /* Function Index = 10 */
   Handle_qapi_ZB_CL_ColorControl_Send_Move_Color, /* Function Index = 11 */
   Handle_qapi_ZB_CL_ColorControl_Send_Step_Color, /* Function Index = 12 */
   Handle_qapi_ZB_CL_ColorControl_Send_Move_To_Color_Temp, /* Function Index = 13 */
   Handle_qapi_ZB_CL_ColorControl_Send_Color_Loop_Set, /* Function Index = 14 */
   Handle_qapi_ZB_CL_ColorControl_Send_Stop_Move_Step, /* Function Index = 15 */
   Handle_qapi_ZB_CL_ColorControl_Send_Move_Color_Temp, /* Function Index = 16 */
   Handle_qapi_ZB_CL_ColorControl_Send_Step_Color_Temp, /* Function Index = 17 */

};

#define QAPI_ZB_CL_COLOR_CONTROL_FUNC_LIST_SIZE   (sizeof(qapi_zb_cl_color_control_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_ZB_CL_COLOR_CONTROL_FUNC_H__
