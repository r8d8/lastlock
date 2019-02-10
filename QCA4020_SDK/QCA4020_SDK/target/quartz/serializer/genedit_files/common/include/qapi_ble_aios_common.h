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

#ifndef __QAPI_BLE_AIOS_COMMON_H__
#define __QAPI_BLE_AIOS_COMMON_H__
#include "qsCommon.h"
#include "qapi_ble.h"
#include "qapi_ble_aios.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_aiostypes_common.h"

/* Packed structure minimum size macros. */
#define QAPI_BLE_AIOS_CHARACTERISTIC_INSTANCE_ENTRY_T_MIN_PACKED_SIZE                                   (11)
#define QAPI_BLE_AIOS_CHARACTERISTIC_ENTRY_T_MIN_PACKED_SIZE                                            ((6) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_AIOS_INITIALIZE_DATA_T_MIN_PACKED_SIZE                                                 ((6) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_AIOS_DIGITAL_CHARACTERISTIC_DATA_T_MIN_PACKED_SIZE                                     ((2) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_AIOS_AGGREGATE_CHARACTERISTIC_DATA_T_MIN_PACKED_SIZE                                   ((2) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_AIOS_PRESENTATION_FORMAT_DATA_T_MIN_PACKED_SIZE                                        (7)
#define QAPI_BLE_AIOS_VALID_RANGE_DATA_T_MIN_PACKED_SIZE                                                (4)
#define QAPI_BLE_AIOS_VALUE_TRIGGER_DATA_T_MIN_PACKED_SIZE                                              (4)
#define QAPI_BLE_AIOS_TIME_INTERVAL_T_MIN_PACKED_SIZE                                                   (3)
#define QAPI_BLE_AIOS_TIME_TRIGGER_DATA_T_MIN_PACKED_SIZE                                               (4)
#define QAPI_BLE_AIOS_CHARACTERISTIC_INFO_T_MIN_PACKED_SIZE                                             (12)
#define QAPI_BLE_AIOS_READ_CHARACTERISTIC_REQUEST_DATA_T_MIN_PACKED_SIZE                                (16)
#define QAPI_BLE_AIOS_WRITE_CHARACTERISTIC_REQUEST_DATA_T_MIN_PACKED_SIZE                               (16)
#define QAPI_BLE_AIOS_READ_CCCD_REQUEST_DATA_T_MIN_PACKED_SIZE                                          (16)
#define QAPI_BLE_AIOS_WRITE_CCCD_REQUEST_DATA_T_MIN_PACKED_SIZE                                         (18)
#define QAPI_BLE_AIOS_READ_PRESENTATION_FORMAT_REQUEST_DATA_T_MIN_PACKED_SIZE                           (16)
#define QAPI_BLE_AIOS_READ_USER_DESCRIPTION_REQUEST_DATA_T_MIN_PACKED_SIZE                              (18)
#define QAPI_BLE_AIOS_WRITE_USER_DESCRIPTION_REQUEST_DATA_T_MIN_PACKED_SIZE                             ((18) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_AIOS_READ_VALUE_TRIGGER_SETTING_REQUEST_DATA_T_MIN_PACKED_SIZE                         (16)
#define QAPI_BLE_AIOS_WRITE_VALUE_TRIGGER_SETTING_REQUEST_DATA_T_MIN_PACKED_SIZE                        (16)
#define QAPI_BLE_AIOS_READ_TIME_TRIGGER_SETTING_REQUEST_DATA_T_MIN_PACKED_SIZE                          (16)
#define QAPI_BLE_AIOS_WRITE_TIME_TRIGGER_SETTING_REQUEST_DATA_T_MIN_PACKED_SIZE                         (16)
#define QAPI_BLE_AIOS_READ_NUMBER_OF_DIGITALS_REQUEST_DATA_T_MIN_PACKED_SIZE                            (16)
#define QAPI_BLE_AIOS_READ_VALID_RANGE_REQUEST_DATA_T_MIN_PACKED_SIZE                                   (16)
#define QAPI_BLE_AIOS_CONFIRMATION_DATA_T_MIN_PACKED_SIZE                                               (19)
#define QAPI_BLE_AIOS_EVENT_DATA_T_MIN_PACKED_SIZE                                                      ((6) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_AIOS_CHARACTERISTIC_DATA_T_MIN_PACKED_SIZE                                             (0)

/* Packed structure size definitions. */
uint32_t CalcPackedSize_qapi_BLE_AIOS_Characteristic_Instance_Entry_t(qapi_BLE_AIOS_Characteristic_Instance_Entry_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Characteristic_Entry_t(qapi_BLE_AIOS_Characteristic_Entry_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Initialize_Data_t(qapi_BLE_AIOS_Initialize_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Digital_Characteristic_Data_t(qapi_BLE_AIOS_Digital_Characteristic_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(qapi_BLE_AIOS_Aggregate_Characteristic_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Presentation_Format_Data_t(qapi_BLE_AIOS_Presentation_Format_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Valid_Range_Data_t(qapi_BLE_AIOS_Valid_Range_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Value_Trigger_Data_t(qapi_BLE_AIOS_Value_Trigger_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Time_Interval_t(qapi_BLE_AIOS_Time_Interval_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Time_Trigger_Data_t(qapi_BLE_AIOS_Time_Trigger_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Characteristic_Info_t(qapi_BLE_AIOS_Characteristic_Info_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Read_Characteristic_Request_Data_t(qapi_BLE_AIOS_Read_Characteristic_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Write_Characteristic_Request_Data_t(qapi_BLE_AIOS_Write_Characteristic_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Read_CCCD_Request_Data_t(qapi_BLE_AIOS_Read_CCCD_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Write_CCCD_Request_Data_t(qapi_BLE_AIOS_Write_CCCD_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Read_Presentation_Format_Request_Data_t(qapi_BLE_AIOS_Read_Presentation_Format_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Read_User_Description_Request_Data_t(qapi_BLE_AIOS_Read_User_Description_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Write_User_Description_Request_Data_t(qapi_BLE_AIOS_Write_User_Description_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Read_Value_Trigger_Setting_Request_Data_t(qapi_BLE_AIOS_Read_Value_Trigger_Setting_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Write_Value_Trigger_Setting_Request_Data_t(qapi_BLE_AIOS_Write_Value_Trigger_Setting_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Read_Time_Trigger_Setting_Request_Data_t(qapi_BLE_AIOS_Read_Time_Trigger_Setting_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Write_Time_Trigger_Setting_Request_Data_t(qapi_BLE_AIOS_Write_Time_Trigger_Setting_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Read_Number_Of_Digitals_Request_Data_t(qapi_BLE_AIOS_Read_Number_Of_Digitals_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Read_Valid_Range_Request_Data_t(qapi_BLE_AIOS_Read_Valid_Range_Request_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Confirmation_Data_t(qapi_BLE_AIOS_Confirmation_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Event_Data_t(qapi_BLE_AIOS_Event_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_AIOS_Characteristic_Data_t(qapi_BLE_AIOS_Characteristic_Data_t *Structure);

/* Pack structure function definitions. */
SerStatus_t PackedWrite_qapi_BLE_AIOS_Characteristic_Instance_Entry_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Characteristic_Instance_Entry_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Characteristic_Entry_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Characteristic_Entry_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Initialize_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Initialize_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Digital_Characteristic_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Digital_Characteristic_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Aggregate_Characteristic_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Presentation_Format_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Presentation_Format_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Valid_Range_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Valid_Range_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Value_Trigger_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Value_Trigger_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Time_Interval_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Time_Interval_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Time_Trigger_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Time_Trigger_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Characteristic_Info_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Characteristic_Info_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Read_Characteristic_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Read_Characteristic_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Write_Characteristic_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Write_Characteristic_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Read_CCCD_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Read_CCCD_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Write_CCCD_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Write_CCCD_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Read_Presentation_Format_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Read_Presentation_Format_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Read_User_Description_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Read_User_Description_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Write_User_Description_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Write_User_Description_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Read_Value_Trigger_Setting_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Read_Value_Trigger_Setting_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Write_Value_Trigger_Setting_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Write_Value_Trigger_Setting_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Read_Time_Trigger_Setting_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Read_Time_Trigger_Setting_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Write_Time_Trigger_Setting_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Write_Time_Trigger_Setting_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Read_Number_Of_Digitals_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Read_Number_Of_Digitals_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Read_Valid_Range_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Read_Valid_Range_Request_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Confirmation_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Confirmation_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Event_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Event_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_AIOS_Characteristic_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Characteristic_Data_t *Structure);

/* Unpack structure function definitions. */
SerStatus_t PackedRead_qapi_BLE_AIOS_Characteristic_Instance_Entry_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Characteristic_Instance_Entry_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Characteristic_Entry_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Characteristic_Entry_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Initialize_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Initialize_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Digital_Characteristic_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Digital_Characteristic_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Aggregate_Characteristic_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Presentation_Format_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Presentation_Format_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Valid_Range_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Valid_Range_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Value_Trigger_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Value_Trigger_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Time_Interval_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Time_Interval_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Time_Trigger_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Time_Trigger_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Characteristic_Info_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Characteristic_Info_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Read_Characteristic_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Read_Characteristic_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Write_Characteristic_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Write_Characteristic_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Read_CCCD_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Read_CCCD_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Write_CCCD_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Write_CCCD_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Read_Presentation_Format_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Read_Presentation_Format_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Read_User_Description_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Read_User_Description_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Write_User_Description_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Write_User_Description_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Read_Value_Trigger_Setting_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Read_Value_Trigger_Setting_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Write_Value_Trigger_Setting_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Write_Value_Trigger_Setting_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Read_Time_Trigger_Setting_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Read_Time_Trigger_Setting_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Write_Time_Trigger_Setting_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Write_Time_Trigger_Setting_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Read_Number_Of_Digitals_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Read_Number_Of_Digitals_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Read_Valid_Range_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Read_Valid_Range_Request_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Confirmation_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Confirmation_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Event_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_AIOS_Characteristic_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Characteristic_Data_t *Structure);

#endif // __QAPI_BLE_AIOS_COMMON_H__
