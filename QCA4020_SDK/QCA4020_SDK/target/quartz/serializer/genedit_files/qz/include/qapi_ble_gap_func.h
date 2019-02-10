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

#ifndef __QAPI_BLE_GAP_FUNC_H__
#define __QAPI_BLE_GAP_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_BLE_GAP_Query_Local_BD_ADDR(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Cancel_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Disconnect(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Read_Remote_Features(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Perform_Scan(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Cancel_Scan(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Convert_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Parse_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Convert_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Parse_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Advertising_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Advertising_Disable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Wake_On_Scan_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Generate_Non_Resolvable_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Generate_Static_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Generate_Resolvable_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Resolve_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Random_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Add_Device_To_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Remove_Device_From_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Read_White_List_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Pairability_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Register_Remote_Authentication(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Un_Register_Remote_Authentication(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Pair_Remote_Device(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Extended_Pair_Remote_Device(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Authentication_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Reestablish_Security(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Request_Security(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Extended_Request_Security(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Fixed_Passkey(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Update_Local_P256_Public_Key(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Encryption_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Connection_Handle(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Connection_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Generate_Long_Term_Key(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Regenerate_Long_Term_Key(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Diversify_Function(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Connection_Parameter_Update_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Connection_Parameter_Update_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Update_Connection_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Authenticated_Payload_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Authenticated_Payload_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Resolvable_Private_Address_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Address_Resolution_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Add_Device_To_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Remove_Device_From_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Read_Resolving_List_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Resolving_List_Privacy_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Default_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Default_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Default_Connection_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Connection_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Connection_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Number_Of_Advertising_Sets(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Advertising_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Advertising_Random_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Enable_Extended_Advertising(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Remove_Advertising_Sets(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Scan_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Enable_Extended_Scan(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Extended_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Local_Secure_Connections_OOB_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_ble_gap_funclist[] =
{
   Handle_qapi_BLE_GAP_Query_Local_BD_ADDR, /* Function Index = 0 */
   Handle_qapi_BLE_GAP_LE_Create_Connection, /* Function Index = 1 */
   Handle_qapi_BLE_GAP_LE_Cancel_Create_Connection, /* Function Index = 2 */
   Handle_qapi_BLE_GAP_LE_Disconnect, /* Function Index = 3 */
   Handle_qapi_BLE_GAP_LE_Read_Remote_Features, /* Function Index = 4 */
   Handle_qapi_BLE_GAP_LE_Perform_Scan, /* Function Index = 5 */
   Handle_qapi_BLE_GAP_LE_Cancel_Scan, /* Function Index = 6 */
   Handle_qapi_BLE_GAP_LE_Set_Advertising_Data, /* Function Index = 7 */
   Handle_qapi_BLE_GAP_LE_Convert_Advertising_Data, /* Function Index = 8 */
   Handle_qapi_BLE_GAP_LE_Parse_Advertising_Data, /* Function Index = 9 */
   Handle_qapi_BLE_GAP_LE_Set_Scan_Response_Data, /* Function Index = 10 */
   Handle_qapi_BLE_GAP_LE_Convert_Scan_Response_Data, /* Function Index = 11 */
   Handle_qapi_BLE_GAP_LE_Parse_Scan_Response_Data, /* Function Index = 12 */
   Handle_qapi_BLE_GAP_LE_Advertising_Enable, /* Function Index = 13 */
   Handle_qapi_BLE_GAP_LE_Advertising_Disable, /* Function Index = 14 */
   Handle_qapi_BLE_GAP_LE_Wake_On_Scan_Request, /* Function Index = 15 */
   Handle_qapi_BLE_GAP_LE_Generate_Non_Resolvable_Address, /* Function Index = 16 */
   Handle_qapi_BLE_GAP_LE_Generate_Static_Address, /* Function Index = 17 */
   Handle_qapi_BLE_GAP_LE_Generate_Resolvable_Address, /* Function Index = 18 */
   Handle_qapi_BLE_GAP_LE_Resolve_Address, /* Function Index = 19 */
   Handle_qapi_BLE_GAP_LE_Set_Random_Address, /* Function Index = 20 */
   Handle_qapi_BLE_GAP_LE_Add_Device_To_White_List, /* Function Index = 21 */
   Handle_qapi_BLE_GAP_LE_Remove_Device_From_White_List, /* Function Index = 22 */
   Handle_qapi_BLE_GAP_LE_Read_White_List_Size, /* Function Index = 23 */
   Handle_qapi_BLE_GAP_LE_Set_Pairability_Mode, /* Function Index = 24 */
   Handle_qapi_BLE_GAP_LE_Register_Remote_Authentication, /* Function Index = 25 */
   Handle_qapi_BLE_GAP_LE_Un_Register_Remote_Authentication, /* Function Index = 26 */
   Handle_qapi_BLE_GAP_LE_Pair_Remote_Device, /* Function Index = 27 */
   Handle_qapi_BLE_GAP_LE_Extended_Pair_Remote_Device, /* Function Index = 28 */
   Handle_qapi_BLE_GAP_LE_Authentication_Response, /* Function Index = 29 */
   Handle_qapi_BLE_GAP_LE_Reestablish_Security, /* Function Index = 30 */
   Handle_qapi_BLE_GAP_LE_Request_Security, /* Function Index = 31 */
   Handle_qapi_BLE_GAP_LE_Extended_Request_Security, /* Function Index = 32 */
   Handle_qapi_BLE_GAP_LE_Set_Fixed_Passkey, /* Function Index = 33 */
   Handle_qapi_BLE_GAP_LE_Update_Local_P256_Public_Key, /* Function Index = 34 */
   Handle_qapi_BLE_GAP_LE_Query_Encryption_Mode, /* Function Index = 35 */
   Handle_qapi_BLE_GAP_LE_Query_Connection_Handle, /* Function Index = 36 */
   Handle_qapi_BLE_GAP_LE_Query_Connection_Parameters, /* Function Index = 37 */
   Handle_qapi_BLE_GAP_LE_Generate_Long_Term_Key, /* Function Index = 38 */
   Handle_qapi_BLE_GAP_LE_Regenerate_Long_Term_Key, /* Function Index = 39 */
   Handle_qapi_BLE_GAP_LE_Diversify_Function, /* Function Index = 40 */
   Handle_qapi_BLE_GAP_LE_Connection_Parameter_Update_Request, /* Function Index = 41 */
   Handle_qapi_BLE_GAP_LE_Connection_Parameter_Update_Response, /* Function Index = 42 */
   Handle_qapi_BLE_GAP_LE_Update_Connection_Parameters, /* Function Index = 43 */
   Handle_qapi_BLE_GAP_LE_Set_Authenticated_Payload_Timeout, /* Function Index = 44 */
   Handle_qapi_BLE_GAP_LE_Query_Authenticated_Payload_Timeout, /* Function Index = 45 */
   Handle_qapi_BLE_GAP_LE_Set_Resolvable_Private_Address_Timeout, /* Function Index = 46 */
   Handle_qapi_BLE_GAP_LE_Set_Address_Resolution_Enable, /* Function Index = 47 */
   Handle_qapi_BLE_GAP_LE_Add_Device_To_Resolving_List, /* Function Index = 48 */
   Handle_qapi_BLE_GAP_LE_Remove_Device_From_Resolving_List, /* Function Index = 49 */
   Handle_qapi_BLE_GAP_LE_Read_Resolving_List_Size, /* Function Index = 50 */
   Handle_qapi_BLE_GAP_LE_Set_Resolving_List_Privacy_Mode, /* Function Index = 51 */
   Handle_qapi_BLE_GAP_LE_Set_Data_Length, /* Function Index = 52 */
   Handle_qapi_BLE_GAP_LE_Set_Default_Data_Length, /* Function Index = 53 */
   Handle_qapi_BLE_GAP_LE_Query_Default_Data_Length, /* Function Index = 54 */
   Handle_qapi_BLE_GAP_LE_Set_Default_Connection_PHY, /* Function Index = 55 */
   Handle_qapi_BLE_GAP_LE_Set_Connection_PHY, /* Function Index = 56 */
   Handle_qapi_BLE_GAP_LE_Query_Connection_PHY, /* Function Index = 57 */
   Handle_qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length, /* Function Index = 58 */
   Handle_qapi_BLE_GAP_LE_Query_Number_Of_Advertising_Sets, /* Function Index = 59 */
   Handle_qapi_BLE_GAP_LE_Set_Extended_Advertising_Parameters, /* Function Index = 60 */
   Handle_qapi_BLE_GAP_LE_Set_Extended_Advertising_Random_Address, /* Function Index = 61 */
   Handle_qapi_BLE_GAP_LE_Set_Extended_Advertising_Data, /* Function Index = 62 */
   Handle_qapi_BLE_GAP_LE_Set_Extended_Scan_Response_Data, /* Function Index = 63 */
   Handle_qapi_BLE_GAP_LE_Enable_Extended_Advertising, /* Function Index = 64 */
   Handle_qapi_BLE_GAP_LE_Remove_Advertising_Sets, /* Function Index = 65 */
   Handle_qapi_BLE_GAP_LE_Set_Extended_Scan_Parameters, /* Function Index = 66 */
   Handle_qapi_BLE_GAP_LE_Enable_Extended_Scan, /* Function Index = 67 */
   Handle_qapi_BLE_GAP_LE_Extended_Create_Connection, /* Function Index = 68 */
   Handle_qapi_BLE_GAP_LE_Query_Local_Secure_Connections_OOB_Data, /* Function Index = 69 */

};

#define QAPI_BLE_GAP_FUNC_LIST_SIZE   (sizeof(qapi_ble_gap_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_BLE_GAP_FUNC_H__
