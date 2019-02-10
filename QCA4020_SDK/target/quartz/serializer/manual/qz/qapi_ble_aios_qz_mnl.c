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
#include "idlist.h"
#include "qsCommon.h"
#include "qsQuartz.h"
#include "qsPack.h"
#include "qapi_ble.h"
#include "qapi_ble_aios_common.h"
#include "qapi_ble_aios_qz_mnl.h"
#include "qapi_ble_aios_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_BLE_AIOS_Read_Characteristic_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t ConnectionID;
   uint32_t TransactionID;
   uint8_t ErrorCode;
   qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo = NULL;
   qapi_BLE_AIOS_Characteristic_Data_t *CharacteristicData = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ConnectionID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicInfo = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_AIOS_Characteristic_Info_t));

      if(CharacteristicInfo == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_AIOS_Characteristic_Info_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_AIOS_Characteristic_Info_t*)CharacteristicInfo);
      }
   }
   else
      CharacteristicInfo = NULL;

   if(qsResult == ssSuccess)
   {
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   }

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_AIOS_Characteristic_Data_t));

      if(CharacteristicData == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         /* Un-Pack the qapi_BLE_AIOS_Characteristic_Data_t union.      */
         switch(CharacteristicInfo->Type)
         {
            case QAPI_BLE_ACT_DIGITAL_E:
               qsResult = PackedRead_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Digital));
               break;
            case QAPI_BLE_ACT_ANALOG_E:
               qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Analog));
               break;
            case QAPI_BLE_ACT_AGGREGATE_E:
               qsResult = PackedRead_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Aggregate));
               break;
         }
      }
   }
   else
      CharacteristicData = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, CharacteristicInfo, CharacteristicData);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_AIOS_FILE_ID, QAPI_BLE_AIOS_READ_CHARACTERISTIC_REQUEST_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_BLE_AIOS_Notify_Characteristic(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t ConnectionID;
   qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo = NULL;
   qapi_BLE_AIOS_Characteristic_Data_t *CharacteristicData = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ConnectionID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicInfo = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_AIOS_Characteristic_Info_t));

      if(CharacteristicInfo == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_AIOS_Characteristic_Info_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_AIOS_Characteristic_Info_t*)CharacteristicInfo);
      }
   }
   else
      CharacteristicInfo = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_AIOS_Characteristic_Data_t));

      if(CharacteristicData == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         /* Un-Pack the qapi_BLE_AIOS_Characteristic_Data_t union.      */
         switch(CharacteristicInfo->Type)
         {
            case QAPI_BLE_ACT_DIGITAL_E:
               qsResult = PackedRead_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Digital));
               break;
            case QAPI_BLE_ACT_ANALOG_E:
               qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Analog));
               break;
            case QAPI_BLE_ACT_AGGREGATE_E:
               qsResult = PackedRead_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Aggregate));
               break;
         }
      }
   }
   else
      CharacteristicData = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, CharacteristicInfo, CharacteristicData);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_AIOS_FILE_ID, QAPI_BLE_AIOS_NOTIFY_CHARACTERISTIC_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_BLE_AIOS_Indicate_Characteristic(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t ConnectionID;
   qapi_BLE_AIOS_Characteristic_Info_t *CharacteristicInfo = NULL;
   qapi_BLE_AIOS_Characteristic_Data_t *CharacteristicData = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ConnectionID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicInfo = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_AIOS_Characteristic_Info_t));

      if(CharacteristicInfo == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_AIOS_Characteristic_Info_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_AIOS_Characteristic_Info_t*)CharacteristicInfo);
      }
   }
   else
      CharacteristicInfo = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_AIOS_Characteristic_Data_t));

      if(CharacteristicData == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         /* Un-Pack the qapi_BLE_AIOS_Characteristic_Data_t union.      */
         switch(CharacteristicInfo->Type)
         {
            case QAPI_BLE_ACT_DIGITAL_E:
               qsResult = PackedRead_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Digital));
               break;
            case QAPI_BLE_ACT_ANALOG_E:
               qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Analog));
               break;
            case QAPI_BLE_ACT_AGGREGATE_E:
               qsResult = PackedRead_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Aggregate));
               break;
         }
      }
   }
   else
      CharacteristicData = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, CharacteristicInfo, CharacteristicData);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_AIOS_FILE_ID, QAPI_BLE_AIOS_INDICATE_CHARACTERISTIC_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}
