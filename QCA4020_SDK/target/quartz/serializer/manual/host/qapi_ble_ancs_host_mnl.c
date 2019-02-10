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
#include <string.h>
#include "idlist.h"
#include "qsCommon.h"
#include "qsHost.h"
#include "qsCallback.h"
#include "qapi_ble.h"
#include "qapi_ble_ancs_common.h"
#include "qapi_ble_ancs_host_mnl.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_ancstypes_common.h"

int Mnl_qapi_BLE_ANCS_Encode_Notification_Attribute_Request(uint8_t TargetID, uint32_t NotificationUID, uint32_t NumberAttributes, qapi_BLE_ANCS_Notification_Attribute_Request_Data_t *NotificationAttributes, uint8_t **Buffer, uint32_t *TotalLength)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint32_t           qsIndex = 0;
   uint16_t           qsSize = 0;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   int qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   /* * NOTE * Added 1 more pointer header for the Buffer double        */
   /*          pointer.                                                 */
   qsSize = (8 + (QS_POINTER_HEADER_SIZE * 3));

   for (qsIndex = 0; qsIndex < NumberAttributes; qsIndex++)
   {
      qsSize = qsSize + CalcPackedSize_qapi_BLE_ANCS_Notification_Attribute_Request_Data_t((qapi_BLE_ANCS_Notification_Attribute_Request_Data_t*)&NotificationAttributes[qsIndex]);
   }

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_ANCS_FILE_ID, QAPI_BLE_ANCS_ENCODE_NOTIFICATION_ATTRIBUTE_REQUEST_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&NotificationUID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&NumberAttributes);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)TotalLength);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Buffer);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)NotificationAttributes);

      if(qsResult == ssSuccess)
      {
         for (qsIndex = 0; qsIndex < NumberAttributes; qsIndex++)
         {
            if(qsResult == ssSuccess)
               qsResult = PackedWrite_qapi_BLE_ANCS_Notification_Attribute_Request_Data_t(&qsInputBuffer, (qapi_BLE_ANCS_Notification_Attribute_Request_Data_t*)&NotificationAttributes[qsIndex]);
         }
      }

      if(qsResult == ssSuccess)
      {
         /* Send the command. */
         if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
         {
            if(qsOutputBuffer.Start != NULL)
            {
               /* Unpack returned values. */
               if(qsResult == ssSuccess)
                  qsResult = PackedRead_int(&qsOutputBuffer, &qsBufferList, (int *)&qsRetVal);

               if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);

               if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
               {
                  qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)TotalLength);
               }
               else
                  TotalLength = NULL;

               if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);

               if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
               {
                  qsResult = PackedRead_Array(&qsOutputBuffer, &qsBufferList, *Buffer, 1, *TotalLength);
               }
               else
                  *Buffer = NULL;

               /* Set the return value to error if necessary. */
               if(qsResult != ssSuccess)
               {
                  qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
               }
            }
            else
            {
               qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
            }

            /* Free the output buffer. */
            FreePackedBuffer(&qsOutputBuffer);
         }
         else
         {
            qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
         }
      }
      else
      {
         qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
      }

      /* Free the input buffer. */
      FreePackedBuffer(&qsInputBuffer);
   }
   else
   {
      qsRetVal = QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR;
   }

   FreeBufferList(&qsBufferList);

   return(qsRetVal);
}

int Mnl_qapi_BLE_ANCS_Encode_App_Attribute_Request(uint8_t TargetID, char *AppIdentifier, uint32_t NumberAttributes, qapi_BLE_ANCS_App_Attribute_Request_Data_t *AppAttributes, uint8_t **Buffer, uint32_t *TotalLength)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint32_t           qsIndex = 0;
   uint16_t           qsSize = 0;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   int qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   /* * NOTE * Added 1 more pointer header for the Buffer double        */
   /*          pointer.                                                 */
   qsSize = (4 + CalcPackedSize_8((uint8_t *)AppIdentifier) + (QS_POINTER_HEADER_SIZE * 4));

   for (qsIndex = 0; qsIndex < NumberAttributes; qsIndex++)
   {
      qsSize = qsSize + CalcPackedSize_qapi_BLE_ANCS_App_Attribute_Request_Data_t((qapi_BLE_ANCS_App_Attribute_Request_Data_t*)&AppAttributes[qsIndex]);
   }

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_ANCS_FILE_ID, QAPI_BLE_ANCS_ENCODE_APP_ATTRIBUTE_REQUEST_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&NumberAttributes);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)AppIdentifier);

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_8(&qsInputBuffer, (uint8_t *)AppIdentifier);
      }

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)TotalLength);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Buffer);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)AppAttributes);

      if(qsResult == ssSuccess)
      {
         for (qsIndex = 0; qsIndex < NumberAttributes; qsIndex++)
         {
            if(qsResult == ssSuccess)
               qsResult = PackedWrite_qapi_BLE_ANCS_App_Attribute_Request_Data_t(&qsInputBuffer, (qapi_BLE_ANCS_App_Attribute_Request_Data_t*)&AppAttributes[qsIndex]);
         }
      }

      if(qsResult == ssSuccess)
      {
         /* Send the command. */
         if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
         {
            if(qsOutputBuffer.Start != NULL)
            {
               /* Unpack returned values. */
               if(qsResult == ssSuccess)
                  qsResult = PackedRead_int(&qsOutputBuffer, &qsBufferList, (int *)&qsRetVal);

               if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);

               if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
               {
                  qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)TotalLength);
               }
               else
                  TotalLength = NULL;

               if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);

               if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
               {
                  qsResult = PackedRead_Array(&qsOutputBuffer, &qsBufferList, *Buffer, 1, *TotalLength);
               }
               else
                  *Buffer = NULL;

               /* Set the return value to error if necessary. */
               if(qsResult != ssSuccess)
               {
                  qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
               }
            }
            else
            {
               qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
            }

            /* Free the output buffer. */
            FreePackedBuffer(&qsOutputBuffer);
         }
         else
         {
            qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
         }
      }
      else
      {
         qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
      }

      /* Free the input buffer. */
      FreePackedBuffer(&qsInputBuffer);
   }
   else
   {
      qsRetVal = QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR;
   }

   FreeBufferList(&qsBufferList);

   return(qsRetVal);
}
