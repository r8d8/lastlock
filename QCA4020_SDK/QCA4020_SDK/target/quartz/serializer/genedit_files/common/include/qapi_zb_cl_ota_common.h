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

#ifndef __QAPI_ZB_CL_OTA_COMMON_H__
#define __QAPI_ZB_CL_OTA_COMMON_H__
#include "qsCommon.h"
#include "qapi_zb.h"
#include "qapi_zb_cl_ota.h"
#include "qapi_zb_cl_common.h"

/* Packed structure minimum size macros. */
#define QAPI_ZB_CL_OTA_HEADER_T_MIN_PACKED_SIZE                                                         (37)
#define QAPI_ZB_CL_OTA_IMAGE_DEFINITION_T_MIN_PACKED_SIZE                                               (8)
#define QAPI_ZB_CL_OTA_IMAGE_DATA_T_MIN_PACKED_SIZE                                                     ((5) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_OTA_IMAGE_BLOCK_DATA_T_MIN_PACKED_SIZE                                               (0)
#define QAPI_ZB_CL_OTA_IMAGE_WAIT_T_MIN_PACKED_SIZE                                                     (10)
#define QAPI_ZB_CL_OTA_IMAGE_BLOCK_RESPONSE_T_MIN_PACKED_SIZE                                           (4)
#define QAPI_ZB_CL_OTA_CLIENT_QUERY_NEXT_IMAGE_T_MIN_PACKED_SIZE                                        (8)
#define QAPI_ZB_CL_OTA_CLIENT_RAW_WRITE_T_MIN_PACKED_SIZE                                               ((1) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_OTA_CLIENT_WRITE_T_MIN_PACKED_SIZE                                                   ((7) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_OTA_CLIENT_VALIDATE_T_MIN_PACKED_SIZE                                                ((QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_OTA_CLIENT_UPGRADE_T_MIN_PACKED_SIZE                                                 (0)
#define QAPI_ZB_CL_OTA_CLIENT_IMAGE_NOTIFY_T_MIN_PACKED_SIZE                                            (2)
#define QAPI_ZB_CL_OTA_CLIENT_EVENT_DATA_T_MIN_PACKED_SIZE                                              (4)
#define QAPI_ZB_CL_OTA_SERVER_IMAGE_EVAL_T_MIN_PACKED_SIZE                                              ((3) + (QS_POINTER_HEADER_SIZE) * (2))
#define QAPI_ZB_CL_OTA_SERVER_IMAGE_READ_T_MIN_PACKED_SIZE                                              ((9) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_OTA_SERVER_IMAGE_UPGRADE_END_TIME_T_MIN_PACKED_SIZE                                  ((QS_POINTER_HEADER_SIZE) * (2))
#define QAPI_ZB_CL_OTA_SERVER_IMAGE_UPGRADE_END_ERROR_T_MIN_PACKED_SIZE                                 (4)
#define QAPI_ZB_CL_OTA_SERVER_EVENT_DATA_T_MIN_PACKED_SIZE                                              (4)
#define QAPI_ZB_CL_OTA_CLIENT_CONFIG_T_MIN_PACKED_SIZE                                                  (22)
#define QAPI_ZB_CL_OTA_SERVER_CONFIG_T_MIN_PACKED_SIZE                                                  (4)

/* Packed structure size definitions. */
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Header_t(qapi_ZB_CL_OTA_Header_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Image_Definition_t(qapi_ZB_CL_OTA_Image_Definition_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Image_Data_t(qapi_ZB_CL_OTA_Image_Data_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Image_Block_Data_t(qapi_ZB_CL_OTA_Image_Block_Data_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Image_Wait_t(qapi_ZB_CL_OTA_Image_Wait_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Image_Block_Response_t(qapi_ZB_CL_OTA_Image_Block_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Client_Query_Next_Image_t(qapi_ZB_CL_OTA_Client_Query_Next_Image_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Client_Raw_Write_t(qapi_ZB_CL_OTA_Client_Raw_Write_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Client_Write_t(qapi_ZB_CL_OTA_Client_Write_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Client_Validate_t(qapi_ZB_CL_OTA_Client_Validate_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Client_Upgrade_t(qapi_ZB_CL_OTA_Client_Upgrade_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Client_Image_Notify_t(qapi_ZB_CL_OTA_Client_Image_Notify_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Client_Event_Data_t(qapi_ZB_CL_OTA_Client_Event_Data_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Server_Image_Eval_t(qapi_ZB_CL_OTA_Server_Image_Eval_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Server_Image_Read_t(qapi_ZB_CL_OTA_Server_Image_Read_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Time_t(qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Time_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Error_t(qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Error_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Server_Event_Data_t(qapi_ZB_CL_OTA_Server_Event_Data_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Client_Config_t(qapi_ZB_CL_OTA_Client_Config_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_OTA_Server_Config_t(qapi_ZB_CL_OTA_Server_Config_t *Structure);

/* Pack structure function definitions. */
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Header_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Header_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Image_Definition_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Image_Definition_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Image_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Image_Data_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Image_Block_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Image_Block_Data_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Image_Wait_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Image_Wait_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Image_Block_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Image_Block_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Client_Query_Next_Image_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Client_Query_Next_Image_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Client_Raw_Write_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Client_Raw_Write_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Client_Write_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Client_Write_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Client_Validate_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Client_Validate_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Client_Upgrade_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Client_Upgrade_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Client_Image_Notify_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Client_Image_Notify_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Client_Event_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Client_Event_Data_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Server_Image_Eval_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Server_Image_Eval_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Server_Image_Read_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Server_Image_Read_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Time_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Time_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Error_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Error_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Server_Event_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Server_Event_Data_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Client_Config_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Client_Config_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_OTA_Server_Config_t(PackedBuffer_t *Buffer, qapi_ZB_CL_OTA_Server_Config_t *Structure);

/* Unpack structure function definitions. */
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Header_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Header_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Image_Definition_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Image_Definition_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Image_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Image_Data_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Image_Block_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Image_Block_Data_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Image_Wait_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Image_Wait_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Image_Block_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Image_Block_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Client_Query_Next_Image_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Client_Query_Next_Image_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Client_Raw_Write_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Client_Raw_Write_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Client_Write_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Client_Write_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Client_Validate_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Client_Validate_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Client_Upgrade_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Client_Upgrade_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Client_Image_Notify_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Client_Image_Notify_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Client_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Client_Event_Data_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Server_Image_Eval_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Server_Image_Eval_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Server_Image_Read_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Server_Image_Read_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Time_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Time_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Error_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Server_Image_Upgrade_End_Error_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Server_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Server_Event_Data_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Client_Config_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Client_Config_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_OTA_Server_Config_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_OTA_Server_Config_t *Structure);

#endif // __QAPI_ZB_CL_OTA_COMMON_H__
