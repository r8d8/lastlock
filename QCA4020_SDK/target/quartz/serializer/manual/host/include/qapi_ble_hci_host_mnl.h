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

#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_hcitypes_common.h"

int Mnl_qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters(uint8_t TargetID, uint32_t BluetoothStackID, uint8_t Own_Address_Type, uint8_t Scanning_Filter_Policy, uint8_t Scanning_PHYS, uint8_t *Scan_Type, uint16_t *Scan_Interval, uint16_t *Scan_Window, uint8_t *StatusResult);

int Mnl_qapi_BLE_HCI_LE_Extended_Create_Connection(uint8_t TargetID, uint32_t BluetoothStackID, uint8_t Initiating_Filter_Policy, uint8_t Own_Address_Type, uint8_t Peer_Address_Type, qapi_BLE_BD_ADDR_t *Peer_Address, uint8_t Initiating_PHYS, uint16_t *Scan_Interval, uint16_t *Scan_Window, uint16_t *Conn_Interval_Min, uint16_t *Conn_Interval_Max, uint16_t *Conn_Latency, uint16_t *Supervision_Timeout, uint16_t *Minimum_CE_Length, uint16_t *Maximum_CE_Length, uint8_t *StatusResult);
