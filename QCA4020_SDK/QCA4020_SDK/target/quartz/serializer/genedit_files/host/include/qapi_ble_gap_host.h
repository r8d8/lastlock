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

#include "qapi_ble_gap.h"

int _qapi_BLE_GAP_Query_Local_BD_ADDR(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t *BD_ADDR);

int _qapi_BLE_GAP_LE_Create_Connection(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t ScanInterval, uint32_t ScanWindow, qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy, qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType, qapi_BLE_BD_ADDR_t *RemoteDevice, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Cancel_Create_Connection(uint8_t TargetID, uint32_t BluetoothStackID);

int _qapi_BLE_GAP_LE_Disconnect(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR);

int _qapi_BLE_GAP_LE_Read_Remote_Features(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR);

int _qapi_BLE_GAP_LE_Perform_Scan(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Scan_Type_t ScanType, uint32_t ScanInterval, uint32_t ScanWindow, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy, boolean_t FilterDuplicates, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Cancel_Scan(uint8_t TargetID, uint32_t BluetoothStackID);

int _qapi_BLE_GAP_LE_Set_Advertising_Data(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t Length, qapi_BLE_Advertising_Data_t *Advertising_Data);

int _qapi_BLE_GAP_LE_Convert_Advertising_Data(uint8_t TargetID, qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data, qapi_BLE_Advertising_Data_t *Advertising_Data);

int _qapi_BLE_GAP_LE_Parse_Advertising_Data(uint8_t TargetID, qapi_BLE_Advertising_Data_t *Advertising_Data, qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data);

int _qapi_BLE_GAP_LE_Set_Scan_Response_Data(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t Length, qapi_BLE_Scan_Response_Data_t *Scan_Response_Data);

int _qapi_BLE_GAP_LE_Convert_Scan_Response_Data(uint8_t TargetID, qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data, qapi_BLE_Scan_Response_Data_t *Scan_Response_Data);

int _qapi_BLE_GAP_LE_Parse_Scan_Response_Data(uint8_t TargetID, qapi_BLE_Scan_Response_Data_t *Scan_Response_Data, qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data);

int _qapi_BLE_GAP_LE_Advertising_Enable(uint8_t TargetID, uint32_t BluetoothStackID, boolean_t EnableScanResponse, qapi_BLE_GAP_LE_Advertising_Parameters_t *GAP_LE_Advertising_Parameters, qapi_BLE_GAP_LE_Connectability_Parameters_t *GAP_LE_Connectability_Parameters, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Advertising_Disable(uint8_t TargetID, uint32_t BluetoothStackID);

int _qapi_BLE_GAP_LE_Wake_On_Scan_Request(uint8_t TargetID, uint32_t BluetoothStackID, boolean_t WakeOnScanRequestEnabled);

int _qapi_BLE_GAP_LE_Generate_Non_Resolvable_Address(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t *NonResolvableAddress_Result);

int _qapi_BLE_GAP_LE_Generate_Static_Address(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t *StaticAddress_Result);

int _qapi_BLE_GAP_LE_Generate_Resolvable_Address(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *IRK, qapi_BLE_BD_ADDR_t *ResolvableAddress_Result);

boolean_t _qapi_BLE_GAP_LE_Resolve_Address(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *IRK, qapi_BLE_BD_ADDR_t ResolvableAddress);

int _qapi_BLE_GAP_LE_Set_Random_Address(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t RandomAddress);

int _qapi_BLE_GAP_LE_Add_Device_To_White_List(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries, uint32_t *AddedDeviceCount);

int _qapi_BLE_GAP_LE_Remove_Device_From_White_List(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries, uint32_t *RemovedDeviceCount);

int _qapi_BLE_GAP_LE_Read_White_List_Size(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t *WhiteListSize);

int _qapi_BLE_GAP_LE_Set_Pairability_Mode(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Pairability_Mode_t PairableMode);

int _qapi_BLE_GAP_LE_Register_Remote_Authentication(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Un_Register_Remote_Authentication(uint8_t TargetID, uint32_t BluetoothStackID);

int _qapi_BLE_GAP_LE_Pair_Remote_Device(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Pairing_Capabilities_t *Capabilities, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Extended_Pair_Remote_Device(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *Extended_Capabilities, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Authentication_Response(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Authentication_Response_Information_t *GAP_LE_Authentication_Information);

int _qapi_BLE_GAP_LE_Reestablish_Security(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Security_Information_t *SecurityInformation, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Request_Security(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Bonding_Type_t Bonding_Type, boolean_t MITM, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Extended_Request_Security(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *ExtendedCapabilities, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Set_Fixed_Passkey(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t *Fixed_Display_Passkey);

int _qapi_BLE_GAP_LE_Update_Local_P256_Public_Key(uint8_t TargetID, uint32_t BluetoothStackID);

int _qapi_BLE_GAP_LE_Query_Encryption_Mode(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_Encryption_Mode_t *GAP_Encryption_Mode);

int _qapi_BLE_GAP_LE_Query_Connection_Handle(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t *Connection_Handle);

int _qapi_BLE_GAP_LE_Query_Connection_Parameters(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Current_Connection_Parameters_t *Current_Connection_Parameters);

int _qapi_BLE_GAP_LE_Generate_Long_Term_Key(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *DHK, qapi_BLE_Encryption_Key_t *ER, qapi_BLE_Long_Term_Key_t *LTK_Result, uint16_t *DIV_Result, uint16_t *EDIV_Result, qapi_BLE_Random_Number_t *Rand_Result);

int _qapi_BLE_GAP_LE_Regenerate_Long_Term_Key(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *DHK, qapi_BLE_Encryption_Key_t *ER, uint16_t EDIV, qapi_BLE_Random_Number_t *Rand, qapi_BLE_Long_Term_Key_t *LTK_Result);

int _qapi_BLE_GAP_LE_Diversify_Function(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *Key, uint16_t DIn, uint16_t RIn, qapi_BLE_Encryption_Key_t *Result);

int _qapi_BLE_GAP_LE_Connection_Parameter_Update_Request(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t Connection_Interval_Min, uint16_t Connection_Interval_Max, uint16_t Slave_Latency, uint16_t Supervision_Timeout);

int _qapi_BLE_GAP_LE_Connection_Parameter_Update_Response(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, boolean_t Accept, qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters);

int _qapi_BLE_GAP_LE_Update_Connection_Parameters(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters);

int _qapi_BLE_GAP_LE_Set_Authenticated_Payload_Timeout(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t AuthenticatedPayloadTimeout);

int _qapi_BLE_GAP_LE_Query_Authenticated_Payload_Timeout(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t *AuthenticatedPayloadTimeout);

int _qapi_BLE_GAP_LE_Set_Resolvable_Private_Address_Timeout(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t RPA_Timeout);

int _qapi_BLE_GAP_LE_Set_Address_Resolution_Enable(uint8_t TargetID, uint32_t BluetoothStackID, boolean_t EnableAddressResolution);

int _qapi_BLE_GAP_LE_Add_Device_To_Resolving_List(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries, uint32_t *AddedDeviceCount);

int _qapi_BLE_GAP_LE_Remove_Device_From_Resolving_List(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries, uint32_t *RemovedDeviceCount);

int _qapi_BLE_GAP_LE_Read_Resolving_List_Size(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t *ResolvingListSize);

int _qapi_BLE_GAP_LE_Set_Resolving_List_Privacy_Mode(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Address_Type_t Peer_Identity_Address_Type, qapi_BLE_BD_ADDR_t Peer_Identity_Address, qapi_BLE_GAP_LE_Privacy_Mode_t PrivacyMode);

int _qapi_BLE_GAP_LE_Set_Data_Length(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t SuggestedTxPacketSize, uint16_t SuggestedTxPacketTime);

int _qapi_BLE_GAP_LE_Set_Default_Data_Length(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t SuggestedTxPacketSize, uint16_t SuggestedTxPacketTime);

int _qapi_BLE_GAP_LE_Query_Default_Data_Length(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t *SuggestedTxPacketSize, uint16_t *SuggestedTxPacketTime);

int _qapi_BLE_GAP_LE_Set_Default_Connection_PHY(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t TxPHYSPreference, uint32_t RxPHYSPreference);

int _qapi_BLE_GAP_LE_Set_Connection_PHY(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint32_t TxPHYSPreference, uint32_t RxPHYSPreference);

int _qapi_BLE_GAP_LE_Query_Connection_PHY(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_PHY_Type_t *TxPHY, qapi_BLE_GAP_LE_PHY_Type_t *RxPHY);

int _qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t *MaximumAdvertisingDataLength);

int _qapi_BLE_GAP_LE_Query_Number_Of_Advertising_Sets(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t *NumberSupportedSets);

int _qapi_BLE_GAP_LE_Set_Extended_Advertising_Parameters(uint8_t TargetID, uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t *AdvertisingParameters, int8_t *SelectedTxPower);

int _qapi_BLE_GAP_LE_Set_Extended_Advertising_Random_Address(uint8_t TargetID, uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_BD_ADDR_t RandomAddress);

int _qapi_BLE_GAP_LE_Set_Extended_Advertising_Data(uint8_t TargetID, uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Advertising_Operation_Type_t Operation, qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference, uint32_t Length, uint8_t *Advertising_Data);

int _qapi_BLE_GAP_LE_Set_Extended_Scan_Response_Data(uint8_t TargetID, uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference, uint32_t Length, uint8_t *Scan_Response_Data);

int _qapi_BLE_GAP_LE_Enable_Extended_Advertising(uint8_t TargetID, uint32_t BluetoothStackID, boolean_t Enable, uint8_t NumberOfSets, uint8_t *AdvertisingHandleList, uint32_t *DurationList, uint8_t *MaxExtendedAdvertisingEventList, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Remove_Advertising_Sets(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t NumberAdvertisingSetHandles, uint8_t *AdvertisingHandles, uint32_t *RemovedSetCount);

int _qapi_BLE_GAP_LE_Set_Extended_Scan_Parameters(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy, uint32_t NumberScanningPHYs, qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t *ScanningParameterList);

int _qapi_BLE_GAP_LE_Enable_Extended_Scan(uint8_t TargetID, uint32_t BluetoothStackID, boolean_t Enable, qapi_BLE_GAP_LE_Extended_Scan_Filter_Duplicates_Type_t FilterDuplicates, uint32_t Duration, uint32_t Period, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Extended_Create_Connection(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy, qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType, qapi_BLE_BD_ADDR_t *RemoteDevice, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, uint32_t NumberOfConnectionParameters, qapi_BLE_GAP_LE_Extended_Connection_Parameters_t *ConnectionParameterList, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_GAP_LE_Query_Local_Secure_Connections_OOB_Data(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_Secure_Connections_Randomizer_t *Randomizer, qapi_BLE_Secure_Connections_Confirmation_t *Confirmation);
