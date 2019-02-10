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

#include <stdint.h>
#include "qsCommon.h"
#include "qapi_hmi.h"

typedef PACKED struct HMI_Key_Descriptor_s
{
   uint64_t Source;
   uint8_t  IdMode;
   uint8_t  Index;
   uint16_t FrameUsage;
   uint8_t  Key[16];
} PACKED_END HMI_Key_Descriptor_t;

#define HMI_KEY_DESCRIPTOR_SIZE                                (sizeof(HMI_Key_Descriptor_t))

typedef PACKED struct HMI_Device_Descriptor_s
{
   uint64_t ExtAddress;
   uint16_t ShortAddress;
   uint16_t PanId;
   uint32_t FrameCounter;
   uint16_t Flags;
   uint8_t  KeyTableIndex;
} PACKED_END HMI_Device_Descriptor_t;

#define HMI_DEVICE_DESCRIPTOR_FLAG_EXEMPT                      (0x0001)

#define HMI_DEVICE_DESCRIPTOR_SIZE                             (sizeof(HMI_Device_Descriptor_t))

typedef PACKED struct HMI_SecurityLevelDescriptor_s
{
   uint16_t FrameUsage;
   uint16_t OverrideMask;
   uint8_t  SecurityMinimum;
} PACKED_END HMI_Security_Level_Descriptor_t;

#define  HMI_SECURITY_LEVEL_DESCRIPTOR_SIZE                    (sizeof(HMI_Security_Level_Descriptor_t))

SerStatus_t Mnl_Handle_qapi_HMI_MLME_Get_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

SerStatus_t Mnl_Handle_qapi_HMI_MLME_Set_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

