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

#include <stdlib.h>
#include <string.h>
#include "idlist.h"
#include "qsCommon.h"
#include "qsQuartz.h"
#include "qsPack.h"
#include "qapi_ble.h"
#include "qapi_ble_ancs_common.h"
#include "qapi_ble_ancs_qz_mnl.h"

SerStatus_t Mnl_Handle_qapi_BLE_ANCS_Encode_Notification_Attribute_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   uint32_t           qsIndex;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint32_t NotificationUID;
   uint32_t NumberAttributes;
   qapi_BLE_ANCS_Notification_Attribute_Request_Data_t *NotificationAttributes = NULL;
   uint32_t *TotalLength = NULL;
   uint8_t  *Buffer      = NULL;
   uint8_t  **Buffer2    = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NotificationUID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumberAttributes);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Buffer2 = &Buffer;
   }

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      TotalLength = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

      if(TotalLength == NULL)
         qsResult = ssAllocationError;
   }
   else
      TotalLength= NULL;


   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      NotificationAttributes = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_ANCS_Notification_Attribute_Request_Data_t)*(NumberAttributes)));

      if(NotificationAttributes == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         for (qsIndex = 0; qsIndex < NumberAttributes; qsIndex++)
         {
            if(qsResult == ssSuccess)
               qsResult = PackedRead_qapi_BLE_ANCS_Notification_Attribute_Request_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_ANCS_Notification_Attribute_Request_Data_t*)&NotificationAttributes[qsIndex]);
         }
      }
   }
   else
      NotificationAttributes = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_ANCS_Encode_Notification_Attribute_Request(NotificationUID, NumberAttributes, NotificationAttributes, Buffer2, TotalLength);

      qsOutputLength = (4 + (TotalLength == NULL ? 0 : *TotalLength) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_ANCS_FILE_ID, QAPI_BLE_ANCS_ENCODE_NOTIFICATION_ATTRIBUTE_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)TotalLength);

         if(qsResult == ssSuccess)
         {
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)TotalLength);
         }

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)(*Buffer2));

         if(qsResult == ssSuccess)
         {
            if(*Buffer2)
            {
               qsResult = PackedWrite_Array(qsOutputBuffer, *Buffer2, 1, *TotalLength);
            }
         }

         if(*Buffer2)
         {
            free(*Buffer2);
         }
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_BLE_ANCS_Encode_App_Attribute_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   uint32_t           qsIndex;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   char *AppIdentifier = NULL;
   uint32_t NumberAttributes;
   qapi_BLE_ANCS_App_Attribute_Request_Data_t *AppAttributes = NULL;
   uint32_t *TotalLength = NULL;
   uint8_t  *Buffer      = NULL;
   uint8_t  **Buffer2    = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumberAttributes);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      AppIdentifier = AllocateBufferListEntry(&qsBufferList, sizeof(char));

      if(AppIdentifier == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)AppIdentifier);
      }
   }
   else
      AppIdentifier = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      TotalLength = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

      if(TotalLength == NULL)
         qsResult = ssAllocationError;
   }
   else
      TotalLength= NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Buffer2 = &Buffer;
   }

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      AppAttributes = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_ANCS_App_Attribute_Request_Data_t)*(NumberAttributes)));

      if(AppAttributes == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         for (qsIndex = 0; qsIndex < NumberAttributes; qsIndex++)
         {
            if(qsResult == ssSuccess)
               qsResult = PackedRead_qapi_BLE_ANCS_App_Attribute_Request_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_ANCS_App_Attribute_Request_Data_t*)&AppAttributes[qsIndex]);
         }
      }
   }
   else
      AppAttributes = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_ANCS_Encode_App_Attribute_Request(AppIdentifier, NumberAttributes, AppAttributes, Buffer2, TotalLength);

      qsOutputLength = (4 + (TotalLength == NULL ? 0 : *TotalLength) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_ANCS_FILE_ID, QAPI_BLE_ANCS_ENCODE_APP_ATTRIBUTE_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)TotalLength);

         if(qsResult == ssSuccess)
         {
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)TotalLength);
         }

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)(*Buffer2));

         if(qsResult == ssSuccess)
         {
            if(*Buffer2)
            {
               qsResult = PackedWrite_Array(qsOutputBuffer, *Buffer2, 1, *TotalLength);
            }
         }

         if(*Buffer2)
         {
            free(*Buffer2);
         }
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}
