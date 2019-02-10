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

#ifndef __MNL_INITIALIZE_STRUCTURES_H__
#define __MNL_INITIALIZE_STRUCTURES_H__

#include "qsCommon.h"
#include "qapi_ble.h"
#include "qapi_zb.h"
#include "qapi_zb_aps.h"
#include "qapi_zb_bdb.h"
#include "qapi_zb_cl.h"
#include "qapi_zb_cl_alarm.h"
#include "qapi_zb_cl_ballast.h"
#include "qapi_zb_cl_basic.h"
#include "qapi_zb_cl_color_control.h"
#include "qapi_zb_cl_device_temp.h"
#include "qapi_zb_cl_doorlock.h"
#include "qapi_zb_cl_fan_control.h"
#include "qapi_zb_cl_groups.h"
#include "qapi_zb_cl_ias_ace.h"
#include "qapi_zb_cl_ias_wd.h"
#include "qapi_zb_cl_ias_zone.h"
#include "qapi_zb_cl_identify.h"
#include "qapi_zb_cl_illuminance.h"
#include "qapi_zb_cl_level_control.h"
#include "qapi_zb_cl_occupancy.h"
#include "qapi_zb_cl_onoff.h"
#include "qapi_zb_cl_ota.h"
#include "qapi_zb_cl_power_config.h"
#include "qapi_zb_cl_rel_humid.h"
#include "qapi_zb_cl_scenes.h"
#include "qapi_zb_cl_temp_measure.h"
#include "qapi_zb_cl_thermostat.h"
#include "qapi_zb_cl_time.h"
#include "qapi_zb_cl_touchlink.h"
#include "qapi_zb_cl_wincover.h"
#include "qapi_zb_interpan.h"
#include "qapi_zb_nwk.h"
#include "qapi_zb_whitelist.h"
#include "qapi_zb_zdp.h"
#include "qapi_zb_zgp.h"
#include "qapi_hmi.h"
#include "qapi_coex.h"
#include "qapi_twn.h"
#include "qapi_HERH.h"

void Mnl_GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(qapi_BLE_AIOS_Characteristic_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_ANCS_App_Attribute_Data_t(qapi_BLE_ANCS_App_Attribute_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_ANCS_Attribute_Data_t(qapi_BLE_ANCS_Attribute_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_CGMS_RACP_Format_Data_t(qapi_BLE_CGMS_RACP_Format_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_ESS_ES_Trigger_Setting_Data_t(qapi_BLE_ESS_ES_Trigger_Setting_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(qapi_BLE_ESS_Characteristic_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_GAP_LE_Authentication_Response_Information_t(qapi_BLE_GAP_LE_Authentication_Response_Information_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_GAP_LE_Authentication_Event_Data_t(qapi_BLE_GAP_LE_Authentication_Event_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_GATT_Service_Attribute_Entry_t(qapi_BLE_GATT_Service_Attribute_Entry_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t(qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_OTS_OACP_Response_Data_t(qapi_BLE_OTS_OACP_Response_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_OTS_OLCP_Response_Data_t(qapi_BLE_OTS_OLCP_Response_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(qapi_BLE_OTS_Object_Metadata_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_UDS_User_Control_Point_Request_Data_t(qapi_BLE_UDS_User_Control_Point_Request_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_UDS_User_Control_Point_Response_Data_t(qapi_BLE_UDS_User_Control_Point_Response_Data_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_BLE_UDS_Characteristic_t(qapi_BLE_UDS_Characteristic_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_ZB_CL_Cluster_Info_t(qapi_ZB_CL_Cluster_Info_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_ZB_CL_Read_Attr_Status_Record_t(qapi_ZB_CL_Read_Attr_Status_Record_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_ZB_ZGP_Key_Request_t(qapi_ZB_ZGP_Key_Request_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_HMI_PAN_Descriptor_t(qapi_HMI_PAN_Descriptor_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_HMI_MLME_Beacon_Notify_Indication_t(qapi_HMI_MLME_Beacon_Notify_Indication_t *Ptr, BufferListEntry_t **BufferList);
void Mnl_GenerateRandom_qapi_TWN_IPv6_Prefix_t(qapi_TWN_IPv6_Prefix_t *Ptr, BufferListEntry_t **BufferList);

#endif /* __MNL_INITIALIZE_STRUCTURES_H__ */
