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

#ifndef __QAPI_BLE_OTS_COMMON_H__
#define __QAPI_BLE_OTS_COMMON_H__
#include "qsCommon.h"
#include "qapi_ble.h"
#include "qapi_ble_ots.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_l2cap_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_otstypes_common.h"

/* Packed structure minimum size macros. */
#define QAPI_BLE_OTS_CLIENT_INFORMATION_T_MIN_PACKED_SIZE                                               (28)
#define QAPI_BLE_OTS_SERVER_INFORMATION_T_MIN_PACKED_SIZE                                               (6)
#define QAPI_BLE_OTS_FEATURE_DATA_T_MIN_PACKED_SIZE                                                     (8)
#define QAPI_BLE_OTS_NAME_DATA_T_MIN_PACKED_SIZE                                                        ((1) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_OTS_OBJECT_SIZE_DATA_T_MIN_PACKED_SIZE                                                 (8)
#define QAPI_BLE_OTS_DATE_TIME_DATA_T_MIN_PACKED_SIZE                                                   (7)
#define QAPI_BLE_OTS_UINT48_DATA_T_MIN_PACKED_SIZE                                                      (6)
#define QAPI_BLE_OTS_OBJECT_DATA_T_MIN_PACKED_SIZE                                                      (9)
#define QAPI_BLE_OTS_OACP_CREATE_REQUEST_DATA_T_MIN_PACKED_SIZE                                         (4)
#define QAPI_BLE_OTS_OACP_CALCULATE_CHECKSUM_REQUEST_DATA_T_MIN_PACKED_SIZE                             (8)
#define QAPI_BLE_OTS_OACP_EXECUTE_REQUEST_DATA_T_MIN_PACKED_SIZE                                        ((2) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_OTS_OACP_READ_REQUEST_DATA_T_MIN_PACKED_SIZE                                           (8)
#define QAPI_BLE_OTS_OACP_WRITE_REQUEST_DATA_T_MIN_PACKED_SIZE                                          (12)
#define QAPI_BLE_OTS_OACP_REQUEST_DATA_T_MIN_PACKED_SIZE                                                (4)
#define QAPI_BLE_OTS_OACP_EXECUTE_RESPONSE_DATA_T_MIN_PACKED_SIZE                                       ((2) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_OTS_OACP_RESPONSE_DATA_T_MIN_PACKED_SIZE                                               (8)
#define QAPI_BLE_OTS_OLCP_REQUEST_DATA_T_MIN_PACKED_SIZE                                                (4)
#define QAPI_BLE_OTS_OLCP_RESPONSE_DATA_T_MIN_PACKED_SIZE                                               (8)
#define QAPI_BLE_OTS_DATE_TIME_RANGE_DATA_T_MIN_PACKED_SIZE                                             (0)
#define QAPI_BLE_OTS_SIZE_RANGE_DATA_T_MIN_PACKED_SIZE                                                  (8)
#define QAPI_BLE_OTS_OBJECT_LIST_FILTER_DATA_T_MIN_PACKED_SIZE                                          (4)
#define QAPI_BLE_OTS_OBJECT_CHANGED_DATA_T_MIN_PACKED_SIZE                                              (1)
#define QAPI_BLE_OTS_READ_OTS_FEATURE_REQUEST_DATA_T_MIN_PACKED_SIZE                                    (16)
#define QAPI_BLE_OTS_READ_OBJECT_METADATA_REQUEST_DATA_T_MIN_PACKED_SIZE                                (21)
#define QAPI_BLE_OTS_WRITE_OBJECT_METADATA_REQUEST_DATA_T_MIN_PACKED_SIZE                               (20)
#define QAPI_BLE_OTS_WRITE_OACP_REQUEST_DATA_T_MIN_PACKED_SIZE                                          (16)
#define QAPI_BLE_OTS_WRITE_OLCP_REQUEST_DATA_T_MIN_PACKED_SIZE                                          (16)
#define QAPI_BLE_OTS_READ_OBJECT_LIST_FILTER_REQUEST_DATA_T_MIN_PACKED_SIZE                             (21)
#define QAPI_BLE_OTS_WRITE_OBJECT_LIST_FILTER_REQUEST_DATA_T_MIN_PACKED_SIZE                            (20)
#define QAPI_BLE_OTS_READ_CCCD_REQUEST_DATA_T_MIN_PACKED_SIZE                                           (20)
#define QAPI_BLE_OTS_WRITE_CCCD_REQUEST_DATA_T_MIN_PACKED_SIZE                                          (22)
#define QAPI_BLE_OTS_PREPARE_WRITE_REQUEST_DATA_T_MIN_PACKED_SIZE                                       (16)
#define QAPI_BLE_OTS_CONFIRMATION_DATA_T_MIN_PACKED_SIZE                                                (19)
#define QAPI_BLE_OTS_EVENT_DATA_T_MIN_PACKED_SIZE                                                       ((6) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_OTS_CHANNEL_OPEN_INDICATION_DATA_T_MIN_PACKED_SIZE                                     (14)
#define QAPI_BLE_OTS_CHANNEL_OPEN_REQUEST_INDICATION_DATA_T_MIN_PACKED_SIZE                             (14)
#define QAPI_BLE_OTS_CHANNEL_OPEN_CONFIRMATION_DATA_T_MIN_PACKED_SIZE                                   (16)
#define QAPI_BLE_OTS_CHANNEL_CLOSE_INDICATION_DATA_T_MIN_PACKED_SIZE                                    (11)
#define QAPI_BLE_OTS_CHANNEL_DATA_INDICATION_DATA_T_MIN_PACKED_SIZE                                     ((14) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_OTS_CHANNEL_DATA_ERROR_INDICATION_T_MIN_PACKED_SIZE                                    (12)
#define QAPI_BLE_OTS_CHANNEL_BUFFER_EMPTY_INDICATION_DATA_T_MIN_PACKED_SIZE                             (10)
#define QAPI_BLE_OTS_CHANNEL_EVENT_DATA_T_MIN_PACKED_SIZE                                               ((5) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_OTS_INITIALIZE_DATA_T_MIN_PACKED_SIZE                                                  (26)
#define QAPI_BLE_OTS_OBJECT_METADATA_DATA_T_MIN_PACKED_SIZE                                             (0)

/* Packed structure size definitions. */
uint32_t CalcPackedSize_qapi_BLE_OTS_Client_Information_t(qapi_BLE_OTS_Client_Information_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Server_Information_t(qapi_BLE_OTS_Server_Information_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Feature_Data_t(qapi_BLE_OTS_Feature_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Name_Data_t(qapi_BLE_OTS_Name_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Object_Size_Data_t(qapi_BLE_OTS_Object_Size_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Date_Time_Data_t(qapi_BLE_OTS_Date_Time_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_UINT48_Data_t(qapi_BLE_OTS_UINT48_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Object_Data_t(qapi_BLE_OTS_Object_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OACP_Create_Request_Data_t(qapi_BLE_OTS_OACP_Create_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OACP_Calculate_Checksum_Request_Data_t(qapi_BLE_OTS_OACP_Calculate_Checksum_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OACP_Execute_Request_Data_t(qapi_BLE_OTS_OACP_Execute_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OACP_Read_Request_Data_t(qapi_BLE_OTS_OACP_Read_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OACP_Write_Request_Data_t(qapi_BLE_OTS_OACP_Write_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OACP_Request_Data_t(qapi_BLE_OTS_OACP_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OACP_Execute_Response_Data_t(qapi_BLE_OTS_OACP_Execute_Response_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OACP_Response_Data_t(qapi_BLE_OTS_OACP_Response_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OLCP_Request_Data_t(qapi_BLE_OTS_OLCP_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_OLCP_Response_Data_t(qapi_BLE_OTS_OLCP_Response_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Date_Time_Range_Data_t(qapi_BLE_OTS_Date_Time_Range_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Size_Range_Data_t(qapi_BLE_OTS_Size_Range_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Object_List_Filter_Data_t(qapi_BLE_OTS_Object_List_Filter_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Object_Changed_Data_t(qapi_BLE_OTS_Object_Changed_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t(qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t(qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t(qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Write_OACP_Request_Data_t(qapi_BLE_OTS_Write_OACP_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Write_OLCP_Request_Data_t(qapi_BLE_OTS_Write_OLCP_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t(qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t(qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Read_CCCD_Request_Data_t(qapi_BLE_OTS_Read_CCCD_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Write_CCCD_Request_Data_t(qapi_BLE_OTS_Write_CCCD_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Prepare_Write_Request_Data_t(qapi_BLE_OTS_Prepare_Write_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Confirmation_Data_t(qapi_BLE_OTS_Confirmation_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Event_Data_t(qapi_BLE_OTS_Event_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Channel_Open_Indication_Data_t(qapi_BLE_OTS_Channel_Open_Indication_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t(qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Channel_Open_Confirmation_Data_t(qapi_BLE_OTS_Channel_Open_Confirmation_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Channel_Close_Indication_Data_t(qapi_BLE_OTS_Channel_Close_Indication_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Channel_Data_Indication_Data_t(qapi_BLE_OTS_Channel_Data_Indication_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Channel_Data_Error_Indication_t(qapi_BLE_OTS_Channel_Data_Error_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t(qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Channel_Event_Data_t(qapi_BLE_OTS_Channel_Event_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Initialize_Data_t(qapi_BLE_OTS_Initialize_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_OTS_Object_Metadata_Data_t(qapi_BLE_OTS_Object_Metadata_Data_t *Structure);

/* Pack structure function definitions. */
SerStatus_t PackedWrite_qapi_BLE_OTS_Client_Information_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Client_Information_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Server_Information_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Server_Information_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Feature_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Feature_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Name_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Name_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Object_Size_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Object_Size_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Date_Time_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Date_Time_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_UINT48_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_UINT48_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Object_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Object_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OACP_Create_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OACP_Create_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OACP_Calculate_Checksum_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OACP_Calculate_Checksum_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OACP_Execute_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OACP_Execute_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OACP_Read_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OACP_Read_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OACP_Write_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OACP_Write_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OACP_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OACP_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OACP_Execute_Response_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OACP_Execute_Response_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OACP_Response_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OACP_Response_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OLCP_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OLCP_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_OLCP_Response_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_OLCP_Response_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Date_Time_Range_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Date_Time_Range_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Size_Range_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Size_Range_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Object_List_Filter_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Object_List_Filter_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Object_Changed_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Object_Changed_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Write_OACP_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Write_OACP_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Write_OLCP_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Write_OLCP_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Read_CCCD_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Read_CCCD_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Write_CCCD_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Write_CCCD_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Prepare_Write_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Prepare_Write_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Confirmation_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Confirmation_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Event_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Event_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Channel_Open_Indication_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Channel_Open_Indication_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Channel_Open_Confirmation_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Channel_Open_Confirmation_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Channel_Close_Indication_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Channel_Close_Indication_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Channel_Data_Indication_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Channel_Data_Indication_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Channel_Data_Error_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Channel_Data_Error_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Channel_Event_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Channel_Event_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Initialize_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Initialize_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_OTS_Object_Metadata_Data_t(PackedBuffer_t *Buffer, qapi_BLE_OTS_Object_Metadata_Data_t *Structure);

/* Unpack structure function definitions. */
SerStatus_t PackedRead_qapi_BLE_OTS_Client_Information_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Client_Information_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Server_Information_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Server_Information_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Feature_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Feature_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Name_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Name_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Object_Size_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Object_Size_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Date_Time_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Date_Time_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_UINT48_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_UINT48_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Object_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Object_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OACP_Create_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OACP_Create_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OACP_Calculate_Checksum_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OACP_Calculate_Checksum_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OACP_Execute_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OACP_Execute_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OACP_Read_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OACP_Read_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OACP_Write_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OACP_Write_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OACP_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OACP_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OACP_Execute_Response_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OACP_Execute_Response_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OACP_Response_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OACP_Response_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OLCP_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OLCP_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_OLCP_Response_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_OLCP_Response_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Date_Time_Range_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Date_Time_Range_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Size_Range_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Size_Range_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Object_List_Filter_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Object_List_Filter_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Object_Changed_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Object_Changed_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Write_OACP_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Write_OACP_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Write_OLCP_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Write_OLCP_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Read_CCCD_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Read_CCCD_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Write_CCCD_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Write_CCCD_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Prepare_Write_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Prepare_Write_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Confirmation_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Confirmation_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Event_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Channel_Open_Indication_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Channel_Open_Indication_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Channel_Open_Confirmation_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Channel_Open_Confirmation_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Channel_Close_Indication_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Channel_Close_Indication_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Channel_Data_Indication_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Channel_Data_Indication_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Channel_Data_Error_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Channel_Data_Error_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Channel_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Channel_Event_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Initialize_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Initialize_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_OTS_Object_Metadata_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_OTS_Object_Metadata_Data_t *Structure);

#endif // __QAPI_BLE_OTS_COMMON_H__
