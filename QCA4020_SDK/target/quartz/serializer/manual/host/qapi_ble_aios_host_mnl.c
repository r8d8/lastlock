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
#include "qapi_ble_aios_common.h"
#include "qapi_ble_aios_host_mnl.h"
#include "qapi_ble_aios_host_cb.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_aiostypes_common.h"

int Mnl_qapi_BLE_AIOS_Read_Characteristic_Request_Response(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Characteristic_Data_t *CharacteristicData)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   int qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   /* * NOTE * Removed AIOS_Characteristic_Data_t union since we will   */
   /*          handle it below. The QS_Pointer_Header_Size has NOT been */
   /*          modified since it MUST remain.                           */
   qsSize = (17 + CalcPackedSize_qapi_BLE_AIOS_Characteristic_Info_t((qapi_BLE_AIOS_Characteristic_Info_t*)CharacteristicInfo) + (QS_POINTER_HEADER_SIZE * 2));

   /* Make sure the input pointers are valid.                           */
   /* * NOTE * This will be the case if we sending the success response.*/
   /*          Otherwise they are not used and may be NULL (ignored).   */
   if((CharacteristicInfo) && (CharacteristicData))
   {
      /* Determine the size of the AIOS                                 */
      /* qapi_BLE_AIOS_Characteristic_Data_t union to add to the packed */
      /* size.                                                          */
      switch(CharacteristicInfo->Type)
      {
         case QAPI_BLE_ACT_DIGITAL_E:
            qsSize += CalcPackedSize_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&(CharacteristicData->Digital));
            break;
         case QAPI_BLE_ACT_ANALOG_E:
            qsSize += CalcPackedSize_16(&(CharacteristicData->Analog));
            break;
         case QAPI_BLE_ACT_AGGREGATE_E:
            qsSize += CalcPackedSize_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&(CharacteristicData->Aggregate));
            break;
      }
   }

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_AIOS_FILE_ID, QAPI_BLE_AIOS_READ_CHARACTERISTIC_REQUEST_RESPONSE_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&BluetoothStackID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&InstanceID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ConnectionID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&TransactionID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_8(&qsInputBuffer, (uint8_t *)&ErrorCode);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)CharacteristicInfo);

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_qapi_BLE_AIOS_Characteristic_Info_t(&qsInputBuffer, (qapi_BLE_AIOS_Characteristic_Info_t*)CharacteristicInfo);
      }

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)CharacteristicData);
      }

      if(qsResult == ssSuccess)
      {
         /* Make sure the input pointers are valid.                     */
         /* * NOTE * This will be the case if we sending the success    */
         /*          response. Otherwise they are not used and may be   */
         /*          NULL (ignored).                                    */
         if((CharacteristicInfo) && (CharacteristicData))
         {
            /* Pack the qapi_BLE_AIOS_Characteristic_Data_t union.      */
            switch(CharacteristicInfo->Type)
            {
               case QAPI_BLE_ACT_DIGITAL_E:
                  qsResult = PackedWrite_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&qsInputBuffer, &(CharacteristicData->Digital));
                  break;
               case QAPI_BLE_ACT_ANALOG_E:
                  qsResult = PackedWrite_16(&qsInputBuffer, &(CharacteristicData->Analog));
                  break;
               case QAPI_BLE_ACT_AGGREGATE_E:
                  qsResult = PackedWrite_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&qsInputBuffer, &(CharacteristicData->Aggregate));
                  break;
            }
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

int Mnl_qapi_BLE_AIOS_Notify_Characteristic(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Characteristic_Data_t *CharacteristicData)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   int qsRetVal = 0;

   /* Calculate size of packed function arguments. */
    /* * NOTE * Removed AIOS_Characteristic_Data_t union since we will   */
   /*          handle it below. The QS_Pointer_Header_Size has NOT been */
   /*          modified since it MUST remain.                           */
   qsSize = (12 + CalcPackedSize_qapi_BLE_AIOS_Characteristic_Info_t((qapi_BLE_AIOS_Characteristic_Info_t*)CharacteristicInfo) + (QS_POINTER_HEADER_SIZE * 2));

   /* Make sure the input pointers are valid.                           */
   /* * NOTE * This will be the case if we sending the success response.*/
   /*          Otherwise they are not used and may be NULL (ignored).   */
   if((CharacteristicInfo) && (CharacteristicData))
   {
      /* Determine the size of the AIOS                                 */
      /* qapi_BLE_AIOS_Characteristic_Data_t union to add to the packed */
      /* size.                                                          */
      switch(CharacteristicInfo->Type)
      {
         case QAPI_BLE_ACT_DIGITAL_E:
            qsSize += CalcPackedSize_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&(CharacteristicData->Digital));
            break;
         case QAPI_BLE_ACT_ANALOG_E:
            qsSize += CalcPackedSize_16(&(CharacteristicData->Analog));
            break;
         case QAPI_BLE_ACT_AGGREGATE_E:
            qsSize += CalcPackedSize_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&(CharacteristicData->Aggregate));
            break;
      }
   }

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_AIOS_FILE_ID, QAPI_BLE_AIOS_NOTIFY_CHARACTERISTIC_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&BluetoothStackID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&InstanceID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ConnectionID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)CharacteristicInfo);

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_qapi_BLE_AIOS_Characteristic_Info_t(&qsInputBuffer, (qapi_BLE_AIOS_Characteristic_Info_t*)CharacteristicInfo);
      }

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)CharacteristicData);
      }

      if(qsResult == ssSuccess)
      {
         /* Make sure the input pointers are valid.                     */
         /* * NOTE * This will be the case if we sending the success    */
         /*          response. Otherwise they are not used and may be   */
         /*          NULL (ignored).                                    */
         if((CharacteristicInfo) && (CharacteristicData))
         {
            /* Pack the qapi_BLE_AIOS_Characteristic_Data_t union.      */
            switch(CharacteristicInfo->Type)
            {
               case QAPI_BLE_ACT_DIGITAL_E:
                  qsResult = PackedWrite_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&qsInputBuffer, &(CharacteristicData->Digital));
                  break;
               case QAPI_BLE_ACT_ANALOG_E:
                  qsResult = PackedWrite_16(&qsInputBuffer, &(CharacteristicData->Analog));
                  break;
               case QAPI_BLE_ACT_AGGREGATE_E:
                  qsResult = PackedWrite_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&qsInputBuffer, &(CharacteristicData->Aggregate));
                  break;
            }
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

int Mnl_qapi_BLE_AIOS_Indicate_Characteristic(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo, qapi_BLE_AIOS_Characteristic_Data_t *CharacteristicData)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   int qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   /* * NOTE * Removed AIOS_Characteristic_Data_t union since we will   */
   /*          handle it below. The QS_Pointer_Header_Size has NOT been */
   /*          modified since it MUST remain.                           */
   qsSize = (12 + CalcPackedSize_qapi_BLE_AIOS_Characteristic_Info_t((qapi_BLE_AIOS_Characteristic_Info_t*)CharacteristicInfo) + (QS_POINTER_HEADER_SIZE * 2));

   /* Make sure the input pointers are valid.                           */
   /* * NOTE * This will be the case if we sending the success response.*/
   /*          Otherwise they are not used and may be NULL (ignored).   */
   if((CharacteristicInfo) && (CharacteristicData))
   {
      /* Determine the size of the AIOS                                 */
      /* qapi_BLE_AIOS_Characteristic_Data_t union to add to the packed */
      /* size.                                                          */
      switch(CharacteristicInfo->Type)
      {
         case QAPI_BLE_ACT_DIGITAL_E:
            qsSize += CalcPackedSize_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&(CharacteristicData->Digital));
            break;
         case QAPI_BLE_ACT_ANALOG_E:
            qsSize += CalcPackedSize_16(&(CharacteristicData->Analog));
            break;
         case QAPI_BLE_ACT_AGGREGATE_E:
            qsSize += CalcPackedSize_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&(CharacteristicData->Aggregate));
            break;
      }
   }

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_AIOS_FILE_ID, QAPI_BLE_AIOS_INDICATE_CHARACTERISTIC_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&BluetoothStackID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&InstanceID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ConnectionID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)CharacteristicInfo);

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_qapi_BLE_AIOS_Characteristic_Info_t(&qsInputBuffer, (qapi_BLE_AIOS_Characteristic_Info_t*)CharacteristicInfo);
      }

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)CharacteristicData);
      }

      if(qsResult == ssSuccess)
      {
         if(qsResult == ssSuccess)
         {
            /* Make sure the input pointers are valid.                  */
            /* * NOTE * This will be the case if we sending the success */
            /*          response. Otherwise they are not used and may be*/
            /*          NULL (ignored).                                 */
            if((CharacteristicInfo) && (CharacteristicData))
            {
               /* Pack the qapi_BLE_AIOS_Characteristic_Data_t union.   */
               switch(CharacteristicInfo->Type)
               {
                  case QAPI_BLE_ACT_DIGITAL_E:
                     qsResult = PackedWrite_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&qsInputBuffer, &(CharacteristicData->Digital));
                     break;
                  case QAPI_BLE_ACT_ANALOG_E:
                     qsResult = PackedWrite_16(&qsInputBuffer, &(CharacteristicData->Analog));
                     break;
                  case QAPI_BLE_ACT_AGGREGATE_E:
                     qsResult = PackedWrite_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&qsInputBuffer, &(CharacteristicData->Aggregate));
                     break;
               }
            }
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
