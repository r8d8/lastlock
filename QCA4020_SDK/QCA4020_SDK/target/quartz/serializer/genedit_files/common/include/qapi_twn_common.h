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

#ifndef __QAPI_TWN_COMMON_H__
#define __QAPI_TWN_COMMON_H__
#include "qsCommon.h"
#include "qapi_twn.h"
#include "qapi_twn.h"

/* Packed structure minimum size macros. */
#define QAPI_TWN_IPV6_PREFIX_T_MIN_PACKED_SIZE                                                          (1)
#define QAPI_TWN_DEVICE_CONFIGURATION_T_MIN_PACKED_SIZE                                                 (28)
#define QAPI_TWN_NETWORK_CONFIGURATION_T_MIN_PACKED_SIZE                                                (11)
#define QAPI_TWN_BORDER_ROUTER_T_MIN_PACKED_SIZE                                                        (12)
#define QAPI_TWN_EXTERNAL_ROUTE_T_MIN_PACKED_SIZE                                                       (8)
#define QAPI_TWN_JOINER_INFO_T_MIN_PACKED_SIZE                                                          ((QS_POINTER_HEADER_SIZE) * (6))
#define QAPI_TWN_LOG_INFO_T_MIN_PACKED_SIZE                                                             ((QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_TWN_MDNS_INFO_T_MIN_PACKED_SIZE                                                            ((QS_POINTER_HEADER_SIZE) * (2))
#define QAPI_TWN_EVENT_T_MIN_PACKED_SIZE                                                                (4)
#define QAPI_TWN_STEERING_DATA_T_MIN_PACKED_SIZE                                                        (1)
#define QAPI_TWN_COMMISSIONING_DATASET_T_MIN_PACKED_SIZE                                                (22)
#define QAPI_TWN_SEC_POLICY_T_MIN_PACKED_SIZE                                                           (3)
#define QAPI_TWN_OPERATIONAL_DATASET_T_MIN_PACKED_SIZE                                                  (84)

/* Packed structure size definitions. */
uint32_t CalcPackedSize_qapi_TWN_IPv6_Prefix_t(qapi_TWN_IPv6_Prefix_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Device_Configuration_t(qapi_TWN_Device_Configuration_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Network_Configuration_t(qapi_TWN_Network_Configuration_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Border_Router_t(qapi_TWN_Border_Router_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_External_Route_t(qapi_TWN_External_Route_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Joiner_Info_t(qapi_TWN_Joiner_Info_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Log_Info_t(qapi_TWN_Log_Info_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_MDNS_Info_t(qapi_TWN_MDNS_Info_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Event_t(qapi_TWN_Event_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Steering_Data_t(qapi_TWN_Steering_Data_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Commissioning_Dataset_t(qapi_TWN_Commissioning_Dataset_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Sec_Policy_t(qapi_TWN_Sec_Policy_t *Structure);
uint32_t CalcPackedSize_qapi_TWN_Operational_Dataset_t(qapi_TWN_Operational_Dataset_t *Structure);

/* Pack structure function definitions. */
SerStatus_t PackedWrite_qapi_TWN_IPv6_Prefix_t(PackedBuffer_t *Buffer, qapi_TWN_IPv6_Prefix_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Device_Configuration_t(PackedBuffer_t *Buffer, qapi_TWN_Device_Configuration_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Network_Configuration_t(PackedBuffer_t *Buffer, qapi_TWN_Network_Configuration_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Border_Router_t(PackedBuffer_t *Buffer, qapi_TWN_Border_Router_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_External_Route_t(PackedBuffer_t *Buffer, qapi_TWN_External_Route_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Joiner_Info_t(PackedBuffer_t *Buffer, qapi_TWN_Joiner_Info_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Log_Info_t(PackedBuffer_t *Buffer, qapi_TWN_Log_Info_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_MDNS_Info_t(PackedBuffer_t *Buffer, qapi_TWN_MDNS_Info_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Event_t(PackedBuffer_t *Buffer, qapi_TWN_Event_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Steering_Data_t(PackedBuffer_t *Buffer, qapi_TWN_Steering_Data_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Commissioning_Dataset_t(PackedBuffer_t *Buffer, qapi_TWN_Commissioning_Dataset_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Sec_Policy_t(PackedBuffer_t *Buffer, qapi_TWN_Sec_Policy_t *Structure);
SerStatus_t PackedWrite_qapi_TWN_Operational_Dataset_t(PackedBuffer_t *Buffer, qapi_TWN_Operational_Dataset_t *Structure);

/* Unpack structure function definitions. */
SerStatus_t PackedRead_qapi_TWN_IPv6_Prefix_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_IPv6_Prefix_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Device_Configuration_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Device_Configuration_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Network_Configuration_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Network_Configuration_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Border_Router_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Border_Router_t *Structure);
SerStatus_t PackedRead_qapi_TWN_External_Route_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_External_Route_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Joiner_Info_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Joiner_Info_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Log_Info_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Log_Info_t *Structure);
SerStatus_t PackedRead_qapi_TWN_MDNS_Info_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_MDNS_Info_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Event_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Event_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Steering_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Steering_Data_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Commissioning_Dataset_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Commissioning_Dataset_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Sec_Policy_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Sec_Policy_t *Structure);
SerStatus_t PackedRead_qapi_TWN_Operational_Dataset_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Operational_Dataset_t *Structure);

#endif // __QAPI_TWN_COMMON_H__
