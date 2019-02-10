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

#ifndef __QAPI_ZB_ZDP_FUNC_H__
#define __QAPI_ZB_ZDP_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_ZB_ZDP_Register_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Unregister_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Nwk_Addr_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_IEEE_Addr_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Node_Desc_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Power_Desc_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Simple_Desc_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Active_EP_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Match_Desc_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Complex_Desc_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_User_Desc_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Device_Annce_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Parent_Annce_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_User_Desc_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_System_Server_Discovery_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Extended_Simple_Desc_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Extended_Active_EP_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_End_Device_Bind_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Bind_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Unbind_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Mgmt_Lqi_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Mgmt_Rtg_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Mgmt_Bind_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Mgmt_Leave_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Mgmt_Permit_Joining_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Mgmt_Nwk_Update_Req(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Set_Local_Complex_Desc(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Set_Local_User_Desc(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_ZDP_Device_Annce_Alias(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_zb_zdp_funclist[] =
{
   Handle_qapi_ZB_ZDP_Register_Callback, /* Function Index = 0 */
   Handle_qapi_ZB_ZDP_Unregister_Callback, /* Function Index = 1 */
   Handle_qapi_ZB_ZDP_Nwk_Addr_Req, /* Function Index = 2 */
   Handle_qapi_ZB_ZDP_IEEE_Addr_Req, /* Function Index = 3 */
   Handle_qapi_ZB_ZDP_Node_Desc_Req, /* Function Index = 4 */
   Handle_qapi_ZB_ZDP_Power_Desc_Req, /* Function Index = 5 */
   Handle_qapi_ZB_ZDP_Simple_Desc_Req, /* Function Index = 6 */
   Handle_qapi_ZB_ZDP_Active_EP_Req, /* Function Index = 7 */
   Handle_qapi_ZB_ZDP_Match_Desc_Req, /* Function Index = 8 */
   Handle_qapi_ZB_ZDP_Complex_Desc_Req, /* Function Index = 9 */
   Handle_qapi_ZB_ZDP_User_Desc_Req, /* Function Index = 10 */
   Handle_qapi_ZB_ZDP_Device_Annce_Req, /* Function Index = 11 */
   Handle_qapi_ZB_ZDP_Parent_Annce_Req, /* Function Index = 12 */
   Handle_qapi_ZB_ZDP_User_Desc_Set, /* Function Index = 13 */
   Handle_qapi_ZB_ZDP_System_Server_Discovery_Req, /* Function Index = 14 */
   Handle_qapi_ZB_ZDP_Extended_Simple_Desc_Req, /* Function Index = 15 */
   Handle_qapi_ZB_ZDP_Extended_Active_EP_Req, /* Function Index = 16 */
   Handle_qapi_ZB_ZDP_End_Device_Bind_Req, /* Function Index = 17 */
   Handle_qapi_ZB_ZDP_Bind_Req, /* Function Index = 18 */
   Handle_qapi_ZB_ZDP_Unbind_Req, /* Function Index = 19 */
   Handle_qapi_ZB_ZDP_Mgmt_Lqi_Req, /* Function Index = 20 */
   Handle_qapi_ZB_ZDP_Mgmt_Rtg_Req, /* Function Index = 21 */
   Handle_qapi_ZB_ZDP_Mgmt_Bind_Req, /* Function Index = 22 */
   Handle_qapi_ZB_ZDP_Mgmt_Leave_Req, /* Function Index = 23 */
   Handle_qapi_ZB_ZDP_Mgmt_Permit_Joining_Req, /* Function Index = 24 */
   Handle_qapi_ZB_ZDP_Mgmt_Nwk_Update_Req, /* Function Index = 25 */
   Handle_qapi_ZB_ZDP_Set_Local_Complex_Desc, /* Function Index = 26 */
   Handle_qapi_ZB_ZDP_Set_Local_User_Desc, /* Function Index = 27 */
   Handle_qapi_ZB_ZDP_Device_Annce_Alias, /* Function Index = 28 */

};

#define QAPI_ZB_ZDP_FUNC_LIST_SIZE   (sizeof(qapi_zb_zdp_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_ZB_ZDP_FUNC_H__
