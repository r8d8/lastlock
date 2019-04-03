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

#include "qapi_wlan_p2p.h"

qapi_Status_t _qapi_WLAN_P2P_Enable(uint8_t TargetID, uint8_t device_ID, qapi_WLAN_Enable_e enable);

qapi_Status_t _qapi_WLAN_P2P_Cancel(uint8_t TargetID, uint8_t device_ID);

qapi_Status_t _qapi_WLAN_P2P_Find(uint8_t TargetID, uint8_t device_ID, qapi_WLAN_P2P_Disc_Type_e disc_Type, uint32_t timeout_In_Secs);

qapi_Status_t _qapi_WLAN_P2P_Stop_Find(uint8_t TargetID, uint8_t device_ID);

qapi_Status_t _qapi_WLAN_P2P_Prov(uint8_t TargetID, uint8_t device_ID, uint16_t wps_Method, const uint8_t *mac);

qapi_Status_t _qapi_WLAN_P2P_Auth(uint8_t TargetID, uint8_t device_ID, int32_t dev_Auth, qapi_WLAN_P2P_WPS_Method_e wps_Method, const uint8_t *peer_Mac, qapi_WLAN_P2P_Persistent_e persistent);

qapi_Status_t _qapi_WLAN_P2P_Connect(uint8_t TargetID, uint8_t device_ID, qapi_WLAN_P2P_WPS_Method_e wps_Method, const uint8_t *peer_Mac, qapi_WLAN_P2P_Persistent_e persistent);

qapi_Status_t _qapi_WLAN_P2P_Start_Go(uint8_t TargetID, uint8_t device_ID, qapi_WLAN_P2P_Go_Params_t *params, int32_t channel, qapi_WLAN_P2P_Persistent_e persistent);

qapi_Status_t _qapi_WLAN_P2P_Invite(uint8_t TargetID, uint8_t device_ID, const char *ssid, qapi_WLAN_P2P_WPS_Method_e wps_Method, const uint8_t *mac, qapi_WLAN_P2P_Persistent_e persistent, qapi_WLAN_P2P_Inv_Role_e role);

qapi_Status_t _qapi_WLAN_P2P_Join(uint8_t TargetID, uint8_t device_ID, qapi_WLAN_P2P_WPS_Method_e wps_Method, const uint8_t *mac, const char *pin, uint16_t channel);

qapi_Status_t _qapi_WLAN_P2P_Listen(uint8_t TargetID, uint8_t device_ID, uint32_t timeout_In_Secs);

qapi_Status_t _qapi_WLAN_P2P_Invite_Auth(uint8_t TargetID, uint8_t device_ID, const qapi_WLAN_P2P_Invite_Info_t *invite_Info);
