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
#include "qapi_ble_cgms_common.h"
#include "qapi_ble_cgms_qz_mnl.h"
#include "qapi_ble_cgms_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_BLE_CGMS_Notify_CGMS_Measurements(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t ConnectionID;
   uint32_t Flags;
   uint32_t NumberOfMeasurements;
   qapi_BLE_CGMS_Measurement_Data_t *MeasurementList = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ConnectionID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Flags);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumberOfMeasurements);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      if((MeasurementList = malloc(sizeof(qapi_BLE_CGMS_Measurement_Data_t) * NumberOfMeasurements)) != NULL)
      {
         for(qsIndex = 0; (qsResult == ssSuccess) && (qsIndex < NumberOfMeasurements); qsIndex++)
         {
            qsResult = PackedRead_qapi_BLE_CGMS_Measurement_Data_t(&qsInputBuffer, &qsBufferList, &(MeasurementList[qsIndex]));
         }
      }
      else
         qsResult = ssAllocationError;
   }

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_CGMS_Notify_CGMS_Measurements(BluetoothStackID, InstanceID, ConnectionID, Flags, NumberOfMeasurements, &MeasurementList);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CGMS_FILE_ID, QAPI_BLE_CGMS_NOTIFY_CGMS_MEASUREMENTS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

   /* Free allocated memory.*/
   if(MeasurementList)
   {
      free(MeasurementList);
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_BLE_CGMS_Decode_CGMS_Measurement(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t ValueLength;
   uint8_t *Value = NULL;
   uint32_t NumberOfMeasurements;
   qapi_BLE_CGMS_Measurement_Data_t *MeasurementList = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ValueLength);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumberOfMeasurements);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Value = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(ValueLength)));

      if(Value == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Value, sizeof(uint8_t), ValueLength);
      }
   }
   else
      Value = NULL;

   if(qsResult == ssSuccess)
   {
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   }

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      if((MeasurementList = malloc(sizeof(qapi_BLE_CGMS_Measurement_Data_t) * NumberOfMeasurements)) == NULL)
         qsResult = ssAllocationError;
   }

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_CGMS_Decode_CGMS_Measurement(ValueLength, Value, NumberOfMeasurements, &MeasurementList);

      qsOutputLength = 4 + QS_POINTER_HEADER_SIZE;

      if((NumberOfMeasurements) && (MeasurementList))
      {
         qsOutputLength += (sizeof(qapi_BLE_CGMS_Measurement_Data_t) * NumberOfMeasurements);
      }

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CGMS_FILE_ID, QAPI_BLE_CGMS_DECODE_CGMS_MEASUREMENT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)(MeasurementList));

         if(qsResult == ssSuccess)
         {
            if((NumberOfMeasurements) && (MeasurementList))
            {
               for(qsIndex = 0; (qsResult == ssSuccess) && (qsIndex < NumberOfMeasurements); qsIndex++)
               {
                  qsResult = PackedWrite_qapi_BLE_CGMS_Measurement_Data_t(qsOutputBuffer, &(MeasurementList[qsIndex]));
               }
            }
         }
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   /* Free allocated memory.*/
   if(MeasurementList)
   {
      free(MeasurementList);
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}
