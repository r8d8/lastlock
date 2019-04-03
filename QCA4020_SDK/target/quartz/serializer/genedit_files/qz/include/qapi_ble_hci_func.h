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

#ifndef __QAPI_BLE_HCI_FUNC_H__
#define __QAPI_BLE_HCI_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_BLE_HCI_Version_Supported(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Command_Supported(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Register_Event_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Register_ACL_Data_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Un_Register_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Send_ACL_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Send_Raw_Command(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Reconfigure_Driver(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Set_Host_Flow_Control(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Query_Host_Flow_Control(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Disconnect(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Read_Remote_Version_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Set_Event_Mask(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Reset(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Read_Transmit_Power_Level(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Set_Event_Mask_Page_2(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_Channel_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Set_External_Frame_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_Signaling(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_Transport_Layer(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_PATTERN_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Read_Authenticated_Payload_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Write_Authenticated_Payload_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Read_Local_Version_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Read_Local_Supported_Features(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Read_BD_ADDR(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Read_Local_Supported_Commands(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Read_RSSI(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_Free_MWS_Transport_Layer_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Event_Mask(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Buffer_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Local_Supported_Features(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Random_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Advertising_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Advertise_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Scan_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Scan_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Create_Connection_Cancel(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_White_List_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Clear_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Add_Device_To_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Remove_Device_From_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Connection_Update(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Host_Channel_Classification(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Channel_Map(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Remote_Used_Features(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Encrypt(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Rand(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Start_Encryption(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Supported_States(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Receiver_Test(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Transmitter_Test(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Test_End(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Local_P256_Public_Key(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Generate_DHKey(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Add_Device_To_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Clear_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Resolving_List_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Local_Resolvable_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Address_Resolution_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Maximum_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Default_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Enhanced_Receiver_Test(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Enhanced_Transmitter_Test(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Maximum_Advertising_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Number_Of_Supported_Advertising_Sets(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Remove_Advertising_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Clear_Advertising_Sets(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Extended_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Transmit_Power(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Read_RF_Path_Compensation(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Write_RF_Path_Compensation(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Privacy_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_ble_hci_funclist[] =
{
   Handle_qapi_BLE_HCI_Version_Supported, /* Function Index = 0 */
   Handle_qapi_BLE_HCI_Command_Supported, /* Function Index = 1 */
   Handle_qapi_BLE_HCI_Register_Event_Callback, /* Function Index = 2 */
   Handle_qapi_BLE_HCI_Register_ACL_Data_Callback, /* Function Index = 3 */
   Handle_qapi_BLE_HCI_Un_Register_Callback, /* Function Index = 4 */
   Handle_qapi_BLE_HCI_Send_ACL_Data, /* Function Index = 5 */
   Handle_qapi_BLE_HCI_Send_Raw_Command, /* Function Index = 6 */
   Handle_qapi_BLE_HCI_Reconfigure_Driver, /* Function Index = 7 */
   Handle_qapi_BLE_HCI_Set_Host_Flow_Control, /* Function Index = 8 */
   Handle_qapi_BLE_HCI_Query_Host_Flow_Control, /* Function Index = 9 */
   Handle_qapi_BLE_HCI_Disconnect, /* Function Index = 10 */
   Handle_qapi_BLE_HCI_Read_Remote_Version_Information, /* Function Index = 11 */
   Handle_qapi_BLE_HCI_Set_Event_Mask, /* Function Index = 12 */
   Handle_qapi_BLE_HCI_Reset, /* Function Index = 13 */
   Handle_qapi_BLE_HCI_Read_Transmit_Power_Level, /* Function Index = 14 */
   Handle_qapi_BLE_HCI_Set_Event_Mask_Page_2, /* Function Index = 15 */
   Handle_qapi_BLE_HCI_Set_MWS_Channel_Parameters, /* Function Index = 16 */
   Handle_qapi_BLE_HCI_Set_External_Frame_Configuration, /* Function Index = 17 */
   Handle_qapi_BLE_HCI_Set_MWS_Signaling, /* Function Index = 18 */
   Handle_qapi_BLE_HCI_Set_MWS_Transport_Layer, /* Function Index = 19 */
   Handle_qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table, /* Function Index = 20 */
   Handle_qapi_BLE_HCI_Set_MWS_PATTERN_Configuration, /* Function Index = 21 */
   Handle_qapi_BLE_HCI_Read_Authenticated_Payload_Timeout, /* Function Index = 22 */
   Handle_qapi_BLE_HCI_Write_Authenticated_Payload_Timeout, /* Function Index = 23 */
   Handle_qapi_BLE_HCI_Read_Local_Version_Information, /* Function Index = 24 */
   Handle_qapi_BLE_HCI_Read_Local_Supported_Features, /* Function Index = 25 */
   Handle_qapi_BLE_HCI_Read_BD_ADDR, /* Function Index = 26 */
   Handle_qapi_BLE_HCI_Read_Local_Supported_Commands, /* Function Index = 27 */
   Handle_qapi_BLE_HCI_Read_RSSI, /* Function Index = 28 */
   Handle_qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration, /* Function Index = 29 */
   Handle_qapi_BLE_HCI_Free_MWS_Transport_Layer_Configuration, /* Function Index = 30 */
   Handle_qapi_BLE_HCI_LE_Set_Event_Mask, /* Function Index = 31 */
   Handle_qapi_BLE_HCI_LE_Read_Buffer_Size, /* Function Index = 32 */
   Handle_qapi_BLE_HCI_LE_Read_Local_Supported_Features, /* Function Index = 33 */
   Handle_qapi_BLE_HCI_LE_Set_Random_Address, /* Function Index = 34 */
   Handle_qapi_BLE_HCI_LE_Set_Advertising_Parameters, /* Function Index = 35 */
   Handle_qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power, /* Function Index = 36 */
   Handle_qapi_BLE_HCI_LE_Set_Advertising_Data, /* Function Index = 37 */
   Handle_qapi_BLE_HCI_LE_Set_Scan_Response_Data, /* Function Index = 38 */
   Handle_qapi_BLE_HCI_LE_Set_Advertise_Enable, /* Function Index = 39 */
   Handle_qapi_BLE_HCI_LE_Set_Scan_Parameters, /* Function Index = 40 */
   Handle_qapi_BLE_HCI_LE_Set_Scan_Enable, /* Function Index = 41 */
   Handle_qapi_BLE_HCI_LE_Create_Connection, /* Function Index = 42 */
   Handle_qapi_BLE_HCI_LE_Create_Connection_Cancel, /* Function Index = 43 */
   Handle_qapi_BLE_HCI_LE_Read_White_List_Size, /* Function Index = 44 */
   Handle_qapi_BLE_HCI_LE_Clear_White_List, /* Function Index = 45 */
   Handle_qapi_BLE_HCI_LE_Add_Device_To_White_List, /* Function Index = 46 */
   Handle_qapi_BLE_HCI_LE_Remove_Device_From_White_List, /* Function Index = 47 */
   Handle_qapi_BLE_HCI_LE_Connection_Update, /* Function Index = 48 */
   Handle_qapi_BLE_HCI_LE_Set_Host_Channel_Classification, /* Function Index = 49 */
   Handle_qapi_BLE_HCI_LE_Read_Channel_Map, /* Function Index = 50 */
   Handle_qapi_BLE_HCI_LE_Read_Remote_Used_Features, /* Function Index = 51 */
   Handle_qapi_BLE_HCI_LE_Encrypt, /* Function Index = 52 */
   Handle_qapi_BLE_HCI_LE_Rand, /* Function Index = 53 */
   Handle_qapi_BLE_HCI_LE_Start_Encryption, /* Function Index = 54 */
   Handle_qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply, /* Function Index = 55 */
   Handle_qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply, /* Function Index = 56 */
   Handle_qapi_BLE_HCI_LE_Read_Supported_States, /* Function Index = 57 */
   Handle_qapi_BLE_HCI_LE_Receiver_Test, /* Function Index = 58 */
   Handle_qapi_BLE_HCI_LE_Transmitter_Test, /* Function Index = 59 */
   Handle_qapi_BLE_HCI_LE_Test_End, /* Function Index = 60 */
   Handle_qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply, /* Function Index = 61 */
   Handle_qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply, /* Function Index = 62 */
   Handle_qapi_BLE_HCI_LE_Set_Data_Length, /* Function Index = 63 */
   Handle_qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length, /* Function Index = 64 */
   Handle_qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length, /* Function Index = 65 */
   Handle_qapi_BLE_HCI_LE_Read_Local_P256_Public_Key, /* Function Index = 66 */
   Handle_qapi_BLE_HCI_LE_Generate_DHKey, /* Function Index = 67 */
   Handle_qapi_BLE_HCI_LE_Add_Device_To_Resolving_List, /* Function Index = 68 */
   Handle_qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List, /* Function Index = 69 */
   Handle_qapi_BLE_HCI_LE_Clear_Resolving_List, /* Function Index = 70 */
   Handle_qapi_BLE_HCI_LE_Read_Resolving_List_Size, /* Function Index = 71 */
   Handle_qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address, /* Function Index = 72 */
   Handle_qapi_BLE_HCI_LE_Read_Local_Resolvable_Address, /* Function Index = 73 */
   Handle_qapi_BLE_HCI_LE_Set_Address_Resolution_Enable, /* Function Index = 74 */
   Handle_qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout, /* Function Index = 75 */
   Handle_qapi_BLE_HCI_LE_Read_Maximum_Data_Length, /* Function Index = 76 */
   Handle_qapi_BLE_HCI_LE_Read_PHY, /* Function Index = 77 */
   Handle_qapi_BLE_HCI_LE_Set_Default_PHY, /* Function Index = 78 */
   Handle_qapi_BLE_HCI_LE_Set_PHY, /* Function Index = 79 */
   Handle_qapi_BLE_HCI_LE_Enhanced_Receiver_Test, /* Function Index = 80 */
   Handle_qapi_BLE_HCI_LE_Enhanced_Transmitter_Test, /* Function Index = 81 */
   Handle_qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address, /* Function Index = 82 */
   Handle_qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters, /* Function Index = 83 */
   Handle_qapi_BLE_HCI_LE_Set_Extended_Advertising_Data, /* Function Index = 84 */
   Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data, /* Function Index = 85 */
   Handle_qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable, /* Function Index = 86 */
   Handle_qapi_BLE_HCI_LE_Read_Maximum_Advertising_Data_Length, /* Function Index = 87 */
   Handle_qapi_BLE_HCI_LE_Read_Number_Of_Supported_Advertising_Sets, /* Function Index = 88 */
   Handle_qapi_BLE_HCI_LE_Remove_Advertising_Set, /* Function Index = 89 */
   Handle_qapi_BLE_HCI_LE_Clear_Advertising_Sets, /* Function Index = 90 */
   Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters, /* Function Index = 91 */
   Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Enable, /* Function Index = 92 */
   Handle_qapi_BLE_HCI_LE_Extended_Create_Connection, /* Function Index = 93 */
   Handle_qapi_BLE_HCI_LE_Read_Transmit_Power, /* Function Index = 94 */
   Handle_qapi_BLE_HCI_LE_Read_RF_Path_Compensation, /* Function Index = 95 */
   Handle_qapi_BLE_HCI_LE_Write_RF_Path_Compensation, /* Function Index = 96 */
   Handle_qapi_BLE_HCI_LE_Set_Privacy_Mode, /* Function Index = 97 */

};

#define QAPI_BLE_HCI_FUNC_LIST_SIZE   (sizeof(qapi_ble_hci_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_BLE_HCI_FUNC_H__
