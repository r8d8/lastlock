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
#include "qapi_zb.h"
#include "qsCommon.h"
#include "qapi_zb_cl_common.h"
#include "qapi_zb_cl_common_mnl.h"
#include "qapi_zb_common.h"
#include "qapi_zb_aps_common.h"

uint32_t Mnl_CalcPackedSize_qapi_ZB_CL_Cluster_Info_t(qapi_ZB_CL_Cluster_Info_t *Structure)
{
   uint32_t qsIndex;
   uint32_t qsResult;

   if(Structure == NULL)
   {
      qsResult = 0;
   }
   else
   {
      qsResult = QAPI_ZB_CL_CLUSTER_INFO_T_MIN_PACKED_SIZE;

      if(Structure->AttributeList != NULL)
      {
         for (qsIndex = 0; qsIndex < Structure->AttributeCount; qsIndex++)
            qsResult += CalcPackedSize_qapi_ZB_CL_Attribute_t((qapi_ZB_CL_Attribute_t*)&Structure->AttributeList[qsIndex]);
      }
   }

   return(qsResult);
}

uint32_t Mnl_CalcPackedSize_qapi_ZB_CL_Read_Attr_Status_Record_t(qapi_ZB_CL_Read_Attr_Status_Record_t *Structure)
{
   uint32_t qsResult;

   if(Structure == NULL)
   {
      qsResult = 0;
   }
   else
   {
      qsResult = QAPI_ZB_CL_READ_ATTR_STATUS_RECORD_T_MIN_PACKED_SIZE;

      if(Structure->AttrValue != NULL)
      {
         qsResult += (Structure->AttrLength);
      }
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedWrite_qapi_ZB_CL_Cluster_Info_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Cluster_Info_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;
   uint32_t    qsIndex;

   if(Buffer->Remaining >= CalcPackedSize_qapi_ZB_CL_Cluster_Info_t(Structure))
   {
      if(Structure != NULL)
      {
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Endpoint);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->AttributeCount);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(Buffer, (void *)Structure->AttributeList);
         if(qsResult == ssSuccess)
         {
            for (qsIndex = 0; qsIndex < Structure->AttributeCount; qsIndex++)
            {
               if(qsResult == ssSuccess)
                  qsResult = PackedWrite_qapi_ZB_CL_Attribute_t(Buffer, (qapi_ZB_CL_Attribute_t*)&Structure->AttributeList[qsIndex]);
            }
         }

      }
   }
   else
   {
     qsResult = ssInvalidLength;
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedWrite_qapi_ZB_CL_Read_Attr_Status_Record_t(PackedBuffer_t *Buffer, qapi_ZB_CL_Read_Attr_Status_Record_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   if(Buffer->Remaining >= CalcPackedSize_qapi_ZB_CL_Read_Attr_Status_Record_t(Structure))
   {
      if(Structure != NULL)
      {
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->Status);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->AttrId);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->DataType);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->AttrLength);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(Buffer, (void *)Structure->AttrValue);
         if(qsResult == ssSuccess)
         {
            qsResult = PackedWrite_Array(Buffer, (void *)Structure->AttrValue, sizeof(uint8_t), Structure->AttrLength);

         }

      }
   }
   else
   {
     qsResult = ssInvalidLength;
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedRead_qapi_ZB_CL_Cluster_Info_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Cluster_Info_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;
   Boolean_t   qsPointerValid = FALSE;
   uint32_t    qsIndex;

   if(Buffer->Remaining >= QAPI_ZB_CL_CLUSTER_INFO_T_MIN_PACKED_SIZE)
   {
      if(qsResult == ssSuccess)
         qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Endpoint);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->AttributeCount);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_PointerHeader(Buffer, BufferList, &qsPointerValid);
      if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
      {
         Structure->AttributeList = AllocateBufferListEntry(BufferList, (sizeof(qapi_ZB_CL_Attribute_t)*(Structure->AttributeCount)));

         if(Structure->AttributeList == NULL)
         {
            qsResult = ssAllocationError;
         }
         else
         {
            for (qsIndex = 0; qsIndex < Structure->AttributeCount; qsIndex++)
            {
               if(qsResult == ssSuccess)
                  qsResult = PackedRead_qapi_ZB_CL_Attribute_t(Buffer, BufferList, (qapi_ZB_CL_Attribute_t*)&Structure->AttributeList[qsIndex]);
            }
         }
      }
      else
         Structure->AttributeList = NULL;

   }

   return(qsResult);
}

SerStatus_t Mnl_PackedRead_qapi_ZB_CL_Read_Attr_Status_Record_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_Read_Attr_Status_Record_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;
   Boolean_t   qsPointerValid = FALSE;

   if(Buffer->Remaining >= QAPI_ZB_CL_READ_ATTR_STATUS_RECORD_T_MIN_PACKED_SIZE)
   {
      if(qsResult == ssSuccess)
         qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->Status);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->AttrId);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->DataType);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->AttrLength);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_PointerHeader(Buffer, BufferList, &qsPointerValid);
      if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
      {
         Structure->AttrValue = AllocateBufferListEntry(BufferList, (sizeof(uint8_t)*(Structure->AttrLength)));

         if(Structure->AttrValue == NULL)
         {
            qsResult = ssAllocationError;
         }
         else
         {
            qsResult = PackedRead_Array(Buffer, BufferList, (void *)Structure->AttrValue, sizeof(uint8_t), Structure->AttrLength);
         }
      }
      else
         Structure->AttrValue = NULL;

   }

   return(qsResult);
}
