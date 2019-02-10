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

#ifndef __QAPI_BLE_L2CAP_COMMON_H__
#define __QAPI_BLE_L2CAP_COMMON_H__
#include "qsCommon.h"
#include "qapi_ble.h"
#include "qapi_ble_l2cap.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"

/* Packed structure minimum size macros. */
#define QAPI_BLE_L2CA_QUEUEING_PARAMETERS_T_MIN_PACKED_SIZE                                             (12)
#define QAPI_BLE_L2CA_LE_CHANNEL_PARAMETERS_T_MIN_PACKED_SIZE                                           (10)
#define QAPI_BLE_L2CA_CONNECTION_PARAMETER_UPDATE_INDICATION_T_MIN_PACKED_SIZE                          (10)
#define QAPI_BLE_L2CA_CONNECTION_PARAMETER_UPDATE_CONFIRMATION_T_MIN_PACKED_SIZE                        (4)
#define QAPI_BLE_L2CA_FIXED_CHANNEL_CONNECT_INDICATION_T_MIN_PACKED_SIZE                                (6)
#define QAPI_BLE_L2CA_FIXED_CHANNEL_DISCONNECT_INDICATION_T_MIN_PACKED_SIZE                             (6)
#define QAPI_BLE_L2CA_FIXED_CHANNEL_DATA_INDICATION_T_MIN_PACKED_SIZE                                   ((4) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_L2CA_FIXED_CHANNEL_BUFFER_EMPTY_INDICATION_T_MIN_PACKED_SIZE                           (2)
#define QAPI_BLE_L2CA_LE_CONNECT_INDICATION_T_MIN_PACKED_SIZE                                           (11)
#define QAPI_BLE_L2CA_LE_CONNECT_CONFIRMATION_T_MIN_PACKED_SIZE                                         (10)
#define QAPI_BLE_L2CA_LE_DISCONNECT_INDICATION_T_MIN_PACKED_SIZE                                        (3)
#define QAPI_BLE_L2CA_LE_DISCONNECT_CONFIRMATION_T_MIN_PACKED_SIZE                                      (4)
#define QAPI_BLE_L2CA_LE_DATA_INDICATION_T_MIN_PACKED_SIZE                                              ((6) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_BLE_L2CA_LE_CHANNEL_BUFFER_EMPTY_INDICATION_T_MIN_PACKED_SIZE                              (2)
#define QAPI_BLE_L2CA_EVENT_DATA_T_MIN_PACKED_SIZE                                                      ((8) + (QS_POINTER_HEADER_SIZE) * (1))

/* Packed structure size definitions. */
uint32_t CalcPackedSize_qapi_BLE_L2CA_Queueing_Parameters_t(qapi_BLE_L2CA_Queueing_Parameters_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_LE_Channel_Parameters_t(qapi_BLE_L2CA_LE_Channel_Parameters_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t(qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t(qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t(qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t(qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t(qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t(qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_LE_Connect_Indication_t(qapi_BLE_L2CA_LE_Connect_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_LE_Connect_Confirmation_t(qapi_BLE_L2CA_LE_Connect_Confirmation_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_LE_Disconnect_Indication_t(qapi_BLE_L2CA_LE_Disconnect_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_LE_Disconnect_Confirmation_t(qapi_BLE_L2CA_LE_Disconnect_Confirmation_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_LE_Data_Indication_t(qapi_BLE_L2CA_LE_Data_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t(qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t *Structure);
uint32_t CalcPackedSize_qapi_BLE_L2CA_Event_Data_t(qapi_BLE_L2CA_Event_Data_t *Structure);

/* Pack structure function definitions. */
SerStatus_t PackedWrite_qapi_BLE_L2CA_Queueing_Parameters_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_Queueing_Parameters_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_LE_Channel_Parameters_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_LE_Channel_Parameters_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_LE_Connect_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_LE_Connect_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_LE_Connect_Confirmation_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_LE_Connect_Confirmation_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_LE_Disconnect_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_LE_Disconnect_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_LE_Disconnect_Confirmation_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_LE_Disconnect_Confirmation_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_LE_Data_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_LE_Data_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t *Structure);
SerStatus_t PackedWrite_qapi_BLE_L2CA_Event_Data_t(PackedBuffer_t *Buffer, qapi_BLE_L2CA_Event_Data_t *Structure);

/* Unpack structure function definitions. */
SerStatus_t PackedRead_qapi_BLE_L2CA_Queueing_Parameters_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_Queueing_Parameters_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_LE_Channel_Parameters_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_LE_Channel_Parameters_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_LE_Connect_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_LE_Connect_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_LE_Connect_Confirmation_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_LE_Connect_Confirmation_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_LE_Disconnect_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_LE_Disconnect_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_LE_Disconnect_Confirmation_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_LE_Disconnect_Confirmation_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_LE_Data_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_LE_Data_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t *Structure);
SerStatus_t PackedRead_qapi_BLE_L2CA_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_L2CA_Event_Data_t *Structure);

#endif // __QAPI_BLE_L2CAP_COMMON_H__
