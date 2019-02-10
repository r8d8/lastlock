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

#include <string.h>
#include "qapi_twn.h"
#include "qsCommon.h"
#include "qapi_twn_common.h"
#include "qapi_twn_common_mnl.h"

uint32_t Mnl_CalcPackedSize_qapi_TWN_IPv6_Prefix_t(qapi_TWN_IPv6_Prefix_t *Structure)
{
   uint32_t qsResult;

   if(Structure == NULL)
   {
      qsResult = 0;
   }
   else
   {
      qsResult = QAPI_TWN_IPV6_PREFIX_T_MIN_PACKED_SIZE + sizeof(qapi_TWN_IPv6_Address_t);
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedWrite_qapi_TWN_IPv6_Prefix_t(PackedBuffer_t *Buffer, qapi_TWN_IPv6_Prefix_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   if(Buffer->Remaining >= CalcPackedSize_qapi_TWN_IPv6_Prefix_t(Structure))
   {
      if(Structure != NULL)
      {
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_Array(Buffer, (void*)(Structure->Address.Byte), sizeof(uint8_t), 16);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Length);

      }
   }
   else
   {
     qsResult = ssInvalidLength;
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedRead_qapi_TWN_IPv6_Prefix_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_IPv6_Prefix_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   if(Buffer->Remaining >= QAPI_TWN_IPV6_PREFIX_T_MIN_PACKED_SIZE)
   {
      if(qsResult == ssSuccess)
         qsResult = PackedRead_Array(Buffer, BufferList, (void*)(Structure->Address.Byte), sizeof(uint8_t), 16);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Length);

   }

   return(qsResult);
}
