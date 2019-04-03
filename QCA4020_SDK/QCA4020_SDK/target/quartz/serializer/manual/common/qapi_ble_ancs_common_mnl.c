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
#include "qapi_ble.h"
#include "qsCommon.h"
#include "qapi_ble_ancs_common.h"
#include "qapi_ble_ancs_common_mnl.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_ancstypes_common.h"

uint32_t Mnl_CalcPackedSize_qapi_BLE_ANCS_App_Attribute_Data_t(qapi_BLE_ANCS_App_Attribute_Data_t *Structure)
{
   uint32_t qsResult;

   if(Structure == NULL)
   {
      qsResult = 0;
   }
   else
   {
      qsResult = QAPI_BLE_ANCS_APP_ATTRIBUTE_DATA_T_MIN_PACKED_SIZE;
   }

   return(qsResult);
}

uint32_t Mnl_CalcPackedSize_qapi_BLE_ANCS_Attribute_Data_t(qapi_BLE_ANCS_Attribute_Data_t *Structure)
{
   uint32_t qsResult;

   if(Structure == NULL)
   {
      qsResult = 0;
   }
   else
   {
      qsResult = QAPI_BLE_ANCS_ATTRIBUTE_DATA_T_MIN_PACKED_SIZE;

      switch(Structure->Type)
      {
         case QAPI_BLE_DT_NOTIFICATION_E:
            qsResult += CalcPackedSize_int((int *)&Structure->AttributeID.NotificationAttributeID);
            break;
         case QAPI_BLE_DT_APPLICATION_E:
            qsResult += CalcPackedSize_int((int *)&Structure->AttributeID.AppAttributeID);
            break;
      }
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedWrite_qapi_BLE_ANCS_App_Attribute_Data_t(PackedBuffer_t *Buffer, qapi_BLE_ANCS_App_Attribute_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_ANCS_App_Attribute_Data_t(Structure))
   {
      if(Structure != NULL)
      {
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(Buffer, (int *)&Structure->AttributeID);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(Buffer, (void *)Structure->AttributeData);
         if(qsResult == ssSuccess)
         {
            qsResult = PackedWrite_int(Buffer, (int *)Structure->AttributeData);
         }

      }
   }
   else
   {
     qsResult = ssInvalidLength;
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedWrite_qapi_BLE_ANCS_Attribute_Data_t(PackedBuffer_t *Buffer, qapi_BLE_ANCS_Attribute_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_ANCS_Attribute_Data_t(Structure))
   {
      if(Structure != NULL)
      {
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(Buffer, (int *)&Structure->Type);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(Buffer, (void *)Structure->AttributeData);
         if(qsResult == ssSuccess)
         {
            qsResult = PackedWrite_8(Buffer, (uint8_t *)Structure->AttributeData);
         }

         if(qsResult == ssSuccess)
         {
            switch(Structure->Type)
            {
               case QAPI_BLE_DT_NOTIFICATION_E:
                  qsResult = PackedWrite_int(Buffer, (int *)&Structure->AttributeID.NotificationAttributeID);
                  break;
               case QAPI_BLE_DT_APPLICATION_E:
                  qsResult = PackedWrite_int(Buffer, (int *)&Structure->AttributeID.AppAttributeID);
                  break;
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

SerStatus_t Mnl_PackedRead_qapi_BLE_ANCS_App_Attribute_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_ANCS_App_Attribute_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;
   Boolean_t   qsPointerValid = FALSE;

   if(Buffer->Remaining >= QAPI_BLE_ANCS_APP_ATTRIBUTE_DATA_T_MIN_PACKED_SIZE)
   {
      if(qsResult == ssSuccess)
         qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->AttributeID);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_PointerHeader(Buffer, BufferList, &qsPointerValid);
      if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
      {
         Structure->AttributeData = AllocateBufferListEntry(BufferList, sizeof(uint8_t));

         if(Structure->AttributeData == NULL)
         {
            qsResult = ssAllocationError;
         }
         else
         {
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)Structure->AttributeData);
         }
      }
      else
         Structure->AttributeData = NULL;
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedRead_qapi_BLE_ANCS_Attribute_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_ANCS_Attribute_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;
   Boolean_t   qsPointerValid = FALSE;

   if(Buffer->Remaining >= QAPI_BLE_ANCS_ATTRIBUTE_DATA_T_MIN_PACKED_SIZE)
   {
      if(qsResult == ssSuccess)
         qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->Type);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_PointerHeader(Buffer, BufferList, &qsPointerValid);
      if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
      {
         Structure->AttributeData = AllocateBufferListEntry(BufferList, sizeof(uint8_t));

         if(Structure->AttributeData == NULL)
         {
            qsResult = ssAllocationError;
         }
         else
         {
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)Structure->AttributeData);
         }
      }
      else
         Structure->AttributeData = NULL;

      if(qsResult == ssSuccess)
      {
         switch(Structure->Type)
         {
            case QAPI_BLE_DT_NOTIFICATION_E:
               qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->AttributeID.NotificationAttributeID);
               break;
            case QAPI_BLE_DT_APPLICATION_E:
               qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->AttributeID.AppAttributeID);
               break;
         }
      }
   }

   return(qsResult);
}
