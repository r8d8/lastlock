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

#ifndef __QAPI_FIRMWARE_UPGRADE_EXT_COMMON_H__
#define __QAPI_FIRMWARE_UPGRADE_EXT_COMMON_H__
#include "qsCommon.h"
#include "qapi_firmware_upgrade_ext.h"
#include "qapi_firmware_upgrade_ext.h"

/* Packed structure minimum size macros. */
#define QAPI_FW_VER_T_MIN_PACKED_SIZE                                                                   (8)

/* Packed structure size definitions. */
uint32_t CalcPackedSize_qapi_FW_Ver_t(qapi_FW_Ver_t *Structure);

/* Pack structure function definitions. */
SerStatus_t PackedWrite_qapi_FW_Ver_t(PackedBuffer_t *Buffer, qapi_FW_Ver_t *Structure);

/* Unpack structure function definitions. */
SerStatus_t PackedRead_qapi_FW_Ver_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_FW_Ver_t *Structure);

#endif // __QAPI_FIRMWARE_UPGRADE_EXT_COMMON_H__
