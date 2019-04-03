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

#include "qapi_ble_l2cap.h"

int _qapi_BLE_L2CA_Register_LE_PSM(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t LE_PSM, qapi_BLE_L2CA_Event_Callback_t L2CA_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_L2CA_Un_Register_LE_PSM(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t L2CAP_PSMID);

int _qapi_BLE_L2CA_Register_Fixed_Channel(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t FixedChannel, void *ChannelParameters, qapi_BLE_L2CA_Event_Callback_t L2CA_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_L2CA_Un_Register_Fixed_Channel(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t FCID);

int _qapi_BLE_L2CA_LE_Connect_Request(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t LE_PSM, qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters, qapi_BLE_L2CA_Event_Callback_t L2CA_Event_Callback, uint32_t CallbackParameter);

int _qapi_BLE_L2CA_LE_Connect_Response(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t Identifier, uint16_t LCID, uint16_t Result, qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters);

int _qapi_BLE_L2CA_LE_Disconnect_Request(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t LCID);

int _qapi_BLE_L2CA_LE_Disconnect_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t LCID);

int _qapi_BLE_L2CA_Fixed_Channel_Data_Write(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t FCID, uint16_t Data_Length, uint8_t *Data);

int _qapi_BLE_L2CA_Enhanced_Fixed_Channel_Data_Write(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t FCID, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters, uint16_t Data_Length, uint8_t *Data);

int _qapi_BLE_L2CA_Enhanced_Dynamic_Channel_Data_Write(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t LCID, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters, uint16_t Data_Length, uint8_t *Data);

int _qapi_BLE_L2CA_LE_Flush_Channel_Data(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t CID);

int _qapi_BLE_L2CA_LE_Grant_Credits(uint8_t TargetID, uint32_t BluetoothStackID, uint16_t CID, uint16_t CreditsToGrant);

int _qapi_BLE_L2CA_Connection_Parameter_Update_Request(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t IntervalMin, uint16_t IntervalMax, uint16_t SlaveLatency, uint16_t TimeoutMultiplier);

int _qapi_BLE_L2CA_Connection_Parameter_Update_Response(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t Result);
