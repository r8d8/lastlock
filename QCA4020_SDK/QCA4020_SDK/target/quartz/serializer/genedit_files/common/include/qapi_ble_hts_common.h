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

#ifndef __QAPI_BLE_HTS_COMMON_H__
#define __QAPI_BLE_HTS_COMMON_H__
#include "qsCommon.h"
#include "qapi_ble.h"
#include "qapi_ble_hts.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_htstypes_common.h"

/* Packed structure minimum size macros. */
#define QAPI_BLE_HTS_TIME_STAMP_DATA_T_MIN_PACKED_SIZE                                                  (7)
#define QAPI_BLE_HTS_VALID_RANGE_DATA_T_MIN_PACKED_SIZE                                                 (4)
#define QAPI_BLE_HTS_TEMPERATURE_MEASUREMENT_DATA_T_MIN_PACKED_SIZE                                     (2)
#define QAPI_BLE_HTS_CLIENT_INFORMATION_T_MIN_PACKED_SIZE                                               (16)
#define QAPI_BLE_HTS_SERVER_INFORMATION_T_MIN_PACKED_SIZE                                               (6)
#define QAPI_BLE_HTS_READ_CLIENT_CONFIGURATION_DATA_T_MIN_PACKED_SIZE                                   (20)
#define QAPI_BLE_HTS_CLIENT_CONFIGURATION_UPDATE_DATA_T_MIN_PACKED_SIZE                                 (18)
#define QAPI_BLE_HTS_MEASUREMENT_INTERVAL_UPDATE_DATA_T_MIN_PACKED_SIZE                                 (14)
#define QAPI_BLE_HTS_CONFIRMATION_DATA_T_MIN_PACKED_SIZE                                                (17)
#define QAPI_BLE_HTS_EVENT_DATA_T_MIN_PACKED_SIZE                                                       ((6) + (QS_POINTER_HEADER_SIZE) * (1))

/* Packed structure size definitions. */
uint32_t CalcPackedSize_qapi_BLE_HTS_Time_Stamp_Data_t(qapi_BLE_HTS_Time_Stamp_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_HTS_Valid_Range_Data_t(qapi_BLE_HTS_Valid_Range_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_HTS_Temperature_Measurement_Data_t(qapi_BLE_HTS_Temperature_Measurement_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_HTS_Client_Information_t(qapi_BLE_HTS_Client_Information_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_HTS_Server_Information_t(qapi_BLE_HTS_Server_Information_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_HTS_Read_Client_Configuration_Data_t(qapi_BLE_HTS_Read_Client_Configuration_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_HTS_Client_Configuration_Update_Data_t(qapi_BLE_HTS_Client_Configuration_Update_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_HTS_Measurement_Interval_Update_Data_t(qapi_BLE_HTS_Measurement_Interval_Update_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_HTS_Confirmation_Data_t(qapi_BLE_HTS_Confirmation_Data_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_HTS_Event_Data_t(qapi_BLE_HTS_Event_Data_t *Structure);

/* Pack structure function definitions. */
SerStatus_t PackedWrite_qapi_BLE_HTS_Time_Stamp_Data_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Time_Stamp_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_HTS_Valid_Range_Data_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Valid_Range_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_HTS_Temperature_Measurement_Data_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Temperature_Measurement_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_HTS_Client_Information_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Client_Information_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_HTS_Server_Information_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Server_Information_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_HTS_Read_Client_Configuration_Data_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Read_Client_Configuration_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_HTS_Client_Configuration_Update_Data_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Client_Configuration_Update_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_HTS_Measurement_Interval_Update_Data_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Measurement_Interval_Update_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_HTS_Confirmation_Data_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Confirmation_Data_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_HTS_Event_Data_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Event_Data_t *Structure);

/* Unpack structure function definitions. */
SerStatus_t PackedRead_qapi_BLE_HTS_Time_Stamp_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Time_Stamp_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_HTS_Valid_Range_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Valid_Range_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_HTS_Temperature_Measurement_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Temperature_Measurement_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_HTS_Client_Information_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Client_Information_t *Structure);
SerStatus_t PackedRead_qapi_BLE_HTS_Server_Information_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Server_Information_t *Structure);
SerStatus_t PackedRead_qapi_BLE_HTS_Read_Client_Configuration_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Read_Client_Configuration_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_HTS_Client_Configuration_Update_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Client_Configuration_Update_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_HTS_Measurement_Interval_Update_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Measurement_Interval_Update_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_HTS_Confirmation_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Confirmation_Data_t *Structure);
SerStatus_t PackedRead_qapi_BLE_HTS_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Event_Data_t *Structure);

#endif // __QAPI_BLE_HTS_COMMON_H__
