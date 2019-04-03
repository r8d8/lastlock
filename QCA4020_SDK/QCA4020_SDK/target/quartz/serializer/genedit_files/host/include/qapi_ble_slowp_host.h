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

#include "qapi_ble_slowp.h"

int _qapi_BLE_SLoWP_Initialize(uint8_t TargetID, uint32_t BluetoothStackID);

int _qapi_BLE_SLoWP_Cleanup(uint8_t TargetID, uint32_t BluetoothStackID);

int _qapi_BLE_SLoWP_Initialize_Node(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters, qapi_BLE_SLoWP_Event_Callback_t EventCallback, uint32_t CallbackParameter, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

int _qapi_BLE_SLoWP_Cleanup_Node(uint8_t TargetID, uint32_t BluetoothStackID);

int _qapi_BLE_SLoWP_Open_Connection_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, boolean_t AcceptConnection);

int _qapi_BLE_SLoWP_Get_Node_Connection_Mode(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_IPSP_Node_Connection_Mode_t *ConnectionMode);

int _qapi_BLE_SLoWP_Set_Node_Connection_Mode(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_IPSP_Node_Connection_Mode_t ConnectionMode);

int _qapi_BLE_SLoWP_Connect_Remote_Node(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters, qapi_BLE_SLoWP_Event_Callback_t EventCallback, uint32_t CallbackParameter);

int _qapi_BLE_SLoWP_Close_Connection(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR);

int _qapi_BLE_SLoWP_Set_Queueing_Parameters(uint8_t TargetID, uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters);
