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

#ifndef __QAPI_TWN_FUNC_H__
#define __QAPI_TWN_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_TWN_Initialize(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Shutdown(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Stop(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Get_Device_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Set_Device_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Get_Network_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Set_Network_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Add_Border_Router(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Remove_Border_Router(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Add_External_Route(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Remove_External_Route(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Register_Server_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Set_IP_Stack_Integration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Stop(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Add_Joiner(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Remove_Joiner(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Set_Provisioning_URL(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Generate_PSKc(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Joiner_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Joiner_Stop(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Set_PSKc(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_IPv6_Add_Unicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_IPv6_Remove_Unicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_IPv6_Subscribe_Multicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_IPv6_Unsubscribe_Multicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Set_Ping_Response_Enabled(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Become_Router(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Become_Leader(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Start_Border_Agent(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Stop_Border_Agent(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Clear_Persistent_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Set_Max_Poll_Period(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Send_Mgmt_Get(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Send_Mgmt_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Send_PanId_Query(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Get_Session_Id(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Send_Mgmt_Active_Get(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Commissioner_Send_Mgmt_Active_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Get_Unicast_Addresses(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Set_Key_Sequence(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_TWN_Set_DTLS_Handshake_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_twn_funclist[] =
{
   Handle_qapi_TWN_Initialize, /* Function Index = 0 */
   Handle_qapi_TWN_Shutdown, /* Function Index = 1 */
   Handle_qapi_TWN_Start, /* Function Index = 2 */
   Handle_qapi_TWN_Stop, /* Function Index = 3 */
   Handle_qapi_TWN_Get_Device_Configuration, /* Function Index = 4 */
   Handle_qapi_TWN_Set_Device_Configuration, /* Function Index = 5 */
   Handle_qapi_TWN_Get_Network_Configuration, /* Function Index = 6 */
   Handle_qapi_TWN_Set_Network_Configuration, /* Function Index = 7 */
   Handle_qapi_TWN_Add_Border_Router, /* Function Index = 8 */
   Handle_qapi_TWN_Remove_Border_Router, /* Function Index = 9 */
   Handle_qapi_TWN_Add_External_Route, /* Function Index = 10 */
   Handle_qapi_TWN_Remove_External_Route, /* Function Index = 11 */
   Handle_qapi_TWN_Register_Server_Data, /* Function Index = 12 */
   Handle_qapi_TWN_Set_IP_Stack_Integration, /* Function Index = 13 */
   Handle_qapi_TWN_Commissioner_Start, /* Function Index = 14 */
   Handle_qapi_TWN_Commissioner_Stop, /* Function Index = 15 */
   Handle_qapi_TWN_Commissioner_Add_Joiner, /* Function Index = 16 */
   Handle_qapi_TWN_Commissioner_Remove_Joiner, /* Function Index = 17 */
   Handle_qapi_TWN_Commissioner_Set_Provisioning_URL, /* Function Index = 18 */
   Handle_qapi_TWN_Commissioner_Generate_PSKc, /* Function Index = 19 */
   Handle_qapi_TWN_Joiner_Start, /* Function Index = 20 */
   Handle_qapi_TWN_Joiner_Stop, /* Function Index = 21 */
   Handle_qapi_TWN_Set_PSKc, /* Function Index = 22 */
   Handle_qapi_TWN_IPv6_Add_Unicast_Address, /* Function Index = 23 */
   Handle_qapi_TWN_IPv6_Remove_Unicast_Address, /* Function Index = 24 */
   Handle_qapi_TWN_IPv6_Subscribe_Multicast_Address, /* Function Index = 25 */
   Handle_qapi_TWN_IPv6_Unsubscribe_Multicast_Address, /* Function Index = 26 */
   Handle_qapi_TWN_Set_Ping_Response_Enabled, /* Function Index = 27 */
   Handle_qapi_TWN_Become_Router, /* Function Index = 28 */
   Handle_qapi_TWN_Become_Leader, /* Function Index = 29 */
   Handle_qapi_TWN_Start_Border_Agent, /* Function Index = 30 */
   Handle_qapi_TWN_Stop_Border_Agent, /* Function Index = 31 */
   Handle_qapi_TWN_Clear_Persistent_Data, /* Function Index = 32 */
   Handle_qapi_TWN_Set_Max_Poll_Period, /* Function Index = 33 */
   Handle_qapi_TWN_Commissioner_Send_Mgmt_Get, /* Function Index = 34 */
   Handle_qapi_TWN_Commissioner_Send_Mgmt_Set, /* Function Index = 35 */
   Handle_qapi_TWN_Commissioner_Send_PanId_Query, /* Function Index = 36 */
   Handle_qapi_TWN_Commissioner_Get_Session_Id, /* Function Index = 37 */
   Handle_qapi_TWN_Commissioner_Send_Mgmt_Active_Get, /* Function Index = 38 */
   Handle_qapi_TWN_Commissioner_Send_Mgmt_Active_Set, /* Function Index = 39 */
   Handle_qapi_TWN_Get_Unicast_Addresses, /* Function Index = 40 */
   Handle_qapi_TWN_Set_Key_Sequence, /* Function Index = 41 */
   Handle_qapi_TWN_Set_DTLS_Handshake_Timeout, /* Function Index = 42 */

};

#define QAPI_TWN_FUNC_LIST_SIZE   (sizeof(qapi_twn_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_TWN_FUNC_H__
