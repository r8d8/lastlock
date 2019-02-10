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

#ifndef __QAPI_ZB_APS_FUNC_H__
#define __QAPI_ZB_APS_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_ZB_APS_Register_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Unregister_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSDE_Data_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Bind_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Unbind_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Get_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Set_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Add_Group_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Remove_Group_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Remove_All_Groups_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Transport_Key_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Update_Device_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Remove_Device_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Request_Key_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Switch_Key_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Verify_Key_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APSME_Confirm_Key_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Add_Endpoint(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Remove_Endpoint(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Create_Test_Endpoint(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Destroy_Test_Endpoint(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Test_Endpoint_Data_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Add_Device_Key_Pair_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Get_Device_Key_Pair_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Remove_Device_Key_Pair_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_ADD_Fragmented_Data_Drop(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Clear_Fragmented_Data_Drop(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Hash_Install_Code(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Add_Link_Key(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_ZB_APS_Set_Update_Device_Key_Id(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_zb_aps_funclist[] =
{
   Handle_qapi_ZB_APS_Register_Callback, /* Function Index = 0 */
   Handle_qapi_ZB_APS_Unregister_Callback, /* Function Index = 1 */
   Handle_qapi_ZB_APSDE_Data_Request, /* Function Index = 2 */
   Handle_qapi_ZB_APSME_Bind_Request, /* Function Index = 3 */
   Handle_qapi_ZB_APSME_Unbind_Request, /* Function Index = 4 */
   Handle_qapi_ZB_APSME_Get_Request, /* Function Index = 5 */
   Handle_qapi_ZB_APSME_Set_Request, /* Function Index = 6 */
   Handle_qapi_ZB_APSME_Add_Group_Request, /* Function Index = 7 */
   Handle_qapi_ZB_APSME_Remove_Group_Request, /* Function Index = 8 */
   Handle_qapi_ZB_APSME_Remove_All_Groups_Request, /* Function Index = 9 */
   Handle_qapi_ZB_APSME_Transport_Key_Request, /* Function Index = 10 */
   Handle_qapi_ZB_APSME_Update_Device_Request, /* Function Index = 11 */
   Handle_qapi_ZB_APSME_Remove_Device_Request, /* Function Index = 12 */
   Handle_qapi_ZB_APSME_Request_Key_Request, /* Function Index = 13 */
   Handle_qapi_ZB_APSME_Switch_Key_Request, /* Function Index = 14 */
   Handle_qapi_ZB_APSME_Verify_Key_Request, /* Function Index = 15 */
   Handle_qapi_ZB_APSME_Confirm_Key_Request, /* Function Index = 16 */
   Handle_qapi_ZB_APS_Add_Endpoint, /* Function Index = 17 */
   Handle_qapi_ZB_APS_Remove_Endpoint, /* Function Index = 18 */
   Handle_qapi_ZB_APS_Create_Test_Endpoint, /* Function Index = 19 */
   Handle_qapi_ZB_APS_Destroy_Test_Endpoint, /* Function Index = 20 */
   Handle_qapi_ZB_APS_Test_Endpoint_Data_Request, /* Function Index = 21 */
   Handle_qapi_ZB_APS_Add_Device_Key_Pair_Set, /* Function Index = 22 */
   Handle_qapi_ZB_APS_Get_Device_Key_Pair_Set, /* Function Index = 23 */
   Handle_qapi_ZB_APS_Remove_Device_Key_Pair_Set, /* Function Index = 24 */
   Handle_qapi_ZB_APS_ADD_Fragmented_Data_Drop, /* Function Index = 25 */
   Handle_qapi_ZB_APS_Clear_Fragmented_Data_Drop, /* Function Index = 26 */
   Handle_qapi_ZB_APS_Hash_Install_Code, /* Function Index = 27 */
   Handle_qapi_ZB_APS_Add_Link_Key, /* Function Index = 28 */
   Handle_qapi_ZB_APS_Set_Update_Device_Key_Id, /* Function Index = 29 */

};

#define QAPI_ZB_APS_FUNC_LIST_SIZE   (sizeof(qapi_zb_aps_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_ZB_APS_FUNC_H__
