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

#include "qapi_wlan_base.h"

qapi_Status_t _qapi_WLAN_Coex_Control(uint8_t TargetID, const qapi_WLAN_Coex_Config_Data_t *data);

qapi_Status_t _qapi_Get_WLAN_Coex_Stats(uint8_t TargetID, qapi_WLAN_Coex_Stats_t *WLAN_CoexStats);

qapi_Status_t _qapi_WLAN_Enable(uint8_t TargetID, qapi_WLAN_Enable_e enable);

qapi_Status_t _qapi_WLAN_Add_Device(uint8_t TargetID, uint8_t device_ID);

qapi_Status_t _qapi_WLAN_Remove_Device(uint8_t TargetID, uint8_t device_ID);

qapi_Status_t _qapi_WLAN_Start_Scan(uint8_t TargetID, uint8_t device_ID, const qapi_WLAN_Start_Scan_Params_t *scan_Params, qapi_WLAN_Store_Scan_Results_e store_Scan_Results);

qapi_Status_t _qapi_WLAN_Get_Scan_Results(uint8_t TargetID, uint8_t device_ID, qapi_WLAN_BSS_Scan_Info_t *scan_Info, int16_t *num_Results);

qapi_Status_t _qapi_WLAN_Commit(uint8_t TargetID, uint8_t device_ID);

qapi_Status_t _qapi_WLAN_Set_Callback(uint8_t TargetID, uint8_t device_ID, qapi_WLAN_Callback_t callback, const void *application_Context);

qapi_Status_t _qapi_WLAN_Disconnect(uint8_t TargetID, uint8_t device_ID);

qapi_Status_t _qapi_WLAN_Set_Param(uint8_t TargetID, uint8_t device_ID, uint16_t group_ID, uint16_t param_ID, const void *data, uint32_t length, qapi_WLAN_Wait_For_Status_e wait_For_Status);

qapi_Status_t _qapi_WLAN_Get_Param(uint8_t TargetID, uint8_t device_ID, uint16_t group_ID, uint16_t param_ID, void *data, uint32_t *length);

qapi_Status_t _qapi_WLAN_Suspend_Start(uint8_t TargetID, uint32_t suspend_Time_In_Ms);

qapi_Status_t _qapi_WLAN_Raw_Send(uint8_t TargetID, uint8_t device_ID, const qapi_WLAN_Raw_Send_Params_t *raw_Params);

qapi_Status_t _qapi_WLAN_WPS_Start(uint8_t TargetID, uint8_t device_ID, qapi_WLAN_WPS_Connect_Action_e connect_Action, qapi_WLAN_WPS_Mode_e mode, const char *pin);

qapi_Status_t _qapi_WLAN_WPS_Await_Completion(uint8_t TargetID, uint32_t device_ID, qapi_WLAN_Netparams_t *net_Params);

qapi_Status_t _qapi_WLAN_WPS_Connect(uint8_t TargetID, uint8_t device_ID);
