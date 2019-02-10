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

#ifndef __QAPI_ZB_CL_IAS_ACE_COMMON_H__
#define __QAPI_ZB_CL_IAS_ACE_COMMON_H__
#include "qsCommon.h"
#include "qapi_zb.h"
#include "qapi_zb_cl_ias_ace.h"
#include "qapi_zb_cl_common.h"
#include "qapi_zb_cl_ias_zone_common.h"

/* Packed structure minimum size macros. */
#define QAPI_ZB_CL_IASACE_ZONE_TABLE_ENTRY_T_MIN_PACKED_SIZE                                            (13)
#define QAPI_ZB_CL_IASACE_ARM_RESPONSE_T_MIN_PACKED_SIZE                                                (4)
#define QAPI_ZB_CL_IASACE_GET_ZONE_ID_MAP_RESPONSE_T_MIN_PACKED_SIZE                                    ((QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_IASACE_GET_ZONE_INFO_RESPONSE_T_MIN_PACKED_SIZE                                      ((13) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_IASACE_ZONE_STATUS_CHANGED_T_MIN_PACKED_SIZE                                         ((4) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_IASACE_PANEL_STATUS_INFO_T_MIN_PACKED_SIZE                                           (10)
#define QAPI_ZB_CL_IASACE_SET_BYPASSED_ZONE_LIST_T_MIN_PACKED_SIZE                                      ((1) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_IASACE_ZONE_STATUS_T_MIN_PACKED_SIZE                                                 (3)
#define QAPI_ZB_CL_IASACE_BYPASS_RESPONSE_T_MIN_PACKED_SIZE                                             ((1) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_IASACE_GET_ZONE_STATUS_RESPONSE_T_MIN_PACKED_SIZE                                    ((5) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_IASACE_ARM_T_MIN_PACKED_SIZE                                                         ((5) + (QS_POINTER_HEADER_SIZE) * (3))
#define QAPI_ZB_CL_IASACE_BYPASS_T_MIN_PACKED_SIZE                                                      ((1) + (QS_POINTER_HEADER_SIZE) * (4))
#define QAPI_ZB_CL_IASACE_DELAY_TIMEOUT_T_MIN_PACKED_SIZE                                               (4)
#define QAPI_ZB_CL_IASACE_GET_ZONE_INFO_T_MIN_PACKED_SIZE                                               (1)
#define QAPI_ZB_CL_IASACE_GET_ZONE_STATUS_T_MIN_PACKED_SIZE                                             (8)
#define QAPI_ZB_CL_IASACE_CLIENT_EVENT_DATA_T_MIN_PACKED_SIZE                                           (4)
#define QAPI_ZB_CL_IASACE_SERVER_EVENT_DATA_T_MIN_PACKED_SIZE                                           (4)

/* Packed structure size definitions. */
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Zone_Table_Entry_t(qapi_ZB_CL_IASACE_Zone_Table_Entry_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Arm_Response_t(qapi_ZB_CL_IASACE_Arm_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Get_Zone_ID_Map_Response_t(qapi_ZB_CL_IASACE_Get_Zone_ID_Map_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Get_Zone_Info_Response_t(qapi_ZB_CL_IASACE_Get_Zone_Info_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Zone_Status_Changed_t(qapi_ZB_CL_IASACE_Zone_Status_Changed_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Panel_Status_Info_t(qapi_ZB_CL_IASACE_Panel_Status_Info_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Set_Bypassed_Zone_List_t(qapi_ZB_CL_IASACE_Set_Bypassed_Zone_List_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Zone_Status_t(qapi_ZB_CL_IASACE_Zone_Status_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Bypass_Response_t(qapi_ZB_CL_IASACE_Bypass_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Get_Zone_Status_Response_t(qapi_ZB_CL_IASACE_Get_Zone_Status_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Arm_t(qapi_ZB_CL_IASACE_Arm_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Bypass_t(qapi_ZB_CL_IASACE_Bypass_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Delay_Timeout_t(qapi_ZB_CL_IASACE_Delay_Timeout_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Get_Zone_Info_t(qapi_ZB_CL_IASACE_Get_Zone_Info_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Get_Zone_Status_t(qapi_ZB_CL_IASACE_Get_Zone_Status_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Client_Event_Data_t(qapi_ZB_CL_IASACE_Client_Event_Data_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_IASACE_Server_Event_Data_t(qapi_ZB_CL_IASACE_Server_Event_Data_t *Structure);

/* Pack structure function definitions. */
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Zone_Table_Entry_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Zone_Table_Entry_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Arm_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Arm_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Get_Zone_ID_Map_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Get_Zone_ID_Map_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Get_Zone_Info_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Get_Zone_Info_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Zone_Status_Changed_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Zone_Status_Changed_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Panel_Status_Info_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Panel_Status_Info_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Set_Bypassed_Zone_List_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Set_Bypassed_Zone_List_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Zone_Status_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Zone_Status_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Bypass_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Bypass_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Get_Zone_Status_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Get_Zone_Status_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Arm_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Arm_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Bypass_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Bypass_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Delay_Timeout_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Delay_Timeout_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Get_Zone_Info_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Get_Zone_Info_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Get_Zone_Status_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Get_Zone_Status_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Client_Event_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Client_Event_Data_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_IASACE_Server_Event_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_IASACE_Server_Event_Data_t *Structure);

/* Unpack structure function definitions. */
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Zone_Table_Entry_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Zone_Table_Entry_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Arm_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Arm_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Get_Zone_ID_Map_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Get_Zone_ID_Map_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Get_Zone_Info_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Get_Zone_Info_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Zone_Status_Changed_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Zone_Status_Changed_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Panel_Status_Info_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Panel_Status_Info_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Set_Bypassed_Zone_List_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Set_Bypassed_Zone_List_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Zone_Status_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Zone_Status_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Bypass_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Bypass_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Get_Zone_Status_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Get_Zone_Status_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Arm_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Arm_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Bypass_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Bypass_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Delay_Timeout_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Delay_Timeout_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Get_Zone_Info_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Get_Zone_Info_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Get_Zone_Status_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Get_Zone_Status_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Client_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Client_Event_Data_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_IASACE_Server_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_IASACE_Server_Event_Data_t *Structure);

#endif // __QAPI_ZB_CL_IAS_ACE_COMMON_H__
