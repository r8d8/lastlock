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

#ifndef __QAPI_ZB_CL_SCENES_COMMON_H__
#define __QAPI_ZB_CL_SCENES_COMMON_H__
#include "qsCommon.h"
#include "qapi_zb.h"
#include "qapi_zb_cl_scenes.h"
#include "qapi_zb_cl_common.h"

/* Packed structure minimum size macros. */
#define QAPI_ZB_CL_SCENES_EXTENSION_FIELD_SET_T_MIN_PACKED_SIZE                                         ((3) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_SCENES_ADD_SCENE_T_MIN_PACKED_SIZE                                                   ((10) + (QS_POINTER_HEADER_SIZE) * (2))
#define QAPI_ZB_CL_SCENES_ADD_SCENE_RESPONSE_T_MIN_PACKED_SIZE                                          (11)
#define QAPI_ZB_CL_SCENES_VIEW_SCENE_RESPONSE_T_MIN_PACKED_SIZE                                         ((14) + (QS_POINTER_HEADER_SIZE) * (2))
#define QAPI_ZB_CL_SCENES_REMOVE_SCENE_RESPONSE_T_MIN_PACKED_SIZE                                       (7)
#define QAPI_ZB_CL_SCENES_REMOVE_ALL_SCENES_RESPONSE_T_MIN_PACKED_SIZE                                  (6)
#define QAPI_ZB_CL_SCENES_STORE_SCENE_RESPONSE_T_MIN_PACKED_SIZE                                        (7)
#define QAPI_ZB_CL_SCENES_GET_SCENE_MEMBERSHIP_RESPONSE_T_MIN_PACKED_SIZE                               ((8) + (QS_POINTER_HEADER_SIZE) * (1))
#define QAPI_ZB_CL_SCENES_COPY_SCENE_T_MIN_PACKED_SIZE                                                  (10)
#define QAPI_ZB_CL_SCENES_COPY_SCENE_RESPONSE_T_MIN_PACKED_SIZE                                         (7)
#define QAPI_ZB_CL_SCENES_CLIENT_EVENT_DATA_T_MIN_PACKED_SIZE                                           (4)
#define QAPI_ZB_CL_SCENES_SERVER_EVENT_DATA_T_MIN_PACKED_SIZE                                           (4)

/* Packed structure size definitions. */
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Extension_Field_Set_t(qapi_ZB_CL_Scenes_Extension_Field_Set_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Add_Scene_t(qapi_ZB_CL_Scenes_Add_Scene_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Add_Scene_Response_t(qapi_ZB_CL_Scenes_Add_Scene_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_View_Scene_Response_t(qapi_ZB_CL_Scenes_View_Scene_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Remove_Scene_Response_t(qapi_ZB_CL_Scenes_Remove_Scene_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Remove_All_Scenes_Response_t(qapi_ZB_CL_Scenes_Remove_All_Scenes_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Store_Scene_Response_t(qapi_ZB_CL_Scenes_Store_Scene_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Get_Scene_Membership_Response_t(qapi_ZB_CL_Scenes_Get_Scene_Membership_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Copy_Scene_t(qapi_ZB_CL_Scenes_Copy_Scene_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Copy_Scene_Response_t(qapi_ZB_CL_Scenes_Copy_Scene_Response_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Client_Event_Data_t(qapi_ZB_CL_Scenes_Client_Event_Data_t *Structure);
uint32_t CalcPackedSize_qapi_ZB_CL_Scenes_Server_Event_Data_t(qapi_ZB_CL_Scenes_Server_Event_Data_t *Structure);

/* Pack structure function definitions. */
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Extension_Field_Set_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Extension_Field_Set_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Add_Scene_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Add_Scene_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Add_Scene_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Add_Scene_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_View_Scene_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_View_Scene_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Remove_Scene_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Remove_Scene_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Remove_All_Scenes_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Remove_All_Scenes_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Store_Scene_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Store_Scene_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Get_Scene_Membership_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Get_Scene_Membership_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Copy_Scene_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Copy_Scene_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Copy_Scene_Response_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Copy_Scene_Response_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Client_Event_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Client_Event_Data_t *Structure);
SerStatus_t PackedWrite_qapi_ZB_CL_Scenes_Server_Event_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Scenes_Server_Event_Data_t *Structure);

/* Unpack structure function definitions. */
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Extension_Field_Set_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Extension_Field_Set_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Add_Scene_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Add_Scene_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Add_Scene_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Add_Scene_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_View_Scene_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_View_Scene_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Remove_Scene_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Remove_Scene_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Remove_All_Scenes_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Remove_All_Scenes_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Store_Scene_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Store_Scene_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Get_Scene_Membership_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Get_Scene_Membership_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Copy_Scene_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Copy_Scene_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Copy_Scene_Response_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Copy_Scene_Response_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Client_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Client_Event_Data_t *Structure);
SerStatus_t PackedRead_qapi_ZB_CL_Scenes_Server_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Scenes_Server_Event_Data_t *Structure);

#endif // __QAPI_ZB_CL_SCENES_COMMON_H__
