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
#include <stdint.h>
#include <string.h>
#include "idlist.h"
#include "qsCommon.h"
#include "qsHost.h"
#include "qsCallback.h"
#include "qapi_ble.h"
#include "qapi_ble_cgms_common.h"
#include "qapi_ble_cgms_host_mnl.h"
#include "qapi_ble_cgms_host_cb.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_cgmstypes_common.h"

int Mnl_qapi_BLE_CGMS_Notify_CGMS_Measurements(uint8_t TargetID, uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, uint32_t Flags, uint32_t NumberOfMeasurements, qapi_BLE_CGMS_Measurement_Data_t **MeasurementData)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint32_t           qsIndex = 0;
   uint16_t           qsSize = 0;

   /* Return value. */
   int qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = 24 + (NumberOfMeasurements * sizeof(qapi_BLE_CGMS_Measurement_Data_t) + QS_POINTER_HEADER_SIZE);

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_CGMS_FILE_ID, QAPI_BLE_CGMS_NOTIFY_CGMS_MEASUREMENTS_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&BluetoothStackID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&InstanceID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ConnectionID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&Flags);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&NumberOfMeasurements);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)MeasurementData);

      if((qsResult == ssSuccess) && (MeasurementData))
      {
         for(qsIndex = 0; (qsResult == ssSuccess) && (qsIndex < NumberOfMeasurements); qsIndex++)
         {
            qsResult = PackedWrite_qapi_BLE_CGMS_Measurement_Data_t(&qsInputBuffer, &((*MeasurementData)[qsIndex]));
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
                  qsResult = PackedRead_int(&qsOutputBuffer, &qsBufferList, (int32_t *)&qsRetVal);

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

int Mnl_qapi_BLE_CGMS_Decode_CGMS_Measurement(uint8_t TargetID, uint32_t ValueLength, uint8_t *Value, uint32_t NumberOfMeasurements, qapi_BLE_CGMS_Measurement_Data_t **MeasurementData)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   uint32_t           qsIndex = 0;
  SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   int qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (8 + (QS_POINTER_HEADER_SIZE * 2)) + ((ValueLength)*(1));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_CGMS_FILE_ID, QAPI_BLE_CGMS_DECODE_CGMS_MEASUREMENT_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ValueLength);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&NumberOfMeasurements);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Value);

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void *)Value, sizeof(uint8_t), ValueLength);
      }

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)MeasurementData);
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
                  for(qsIndex = 0; (qsResult == ssSuccess) && (qsIndex < NumberOfMeasurements); qsIndex++)
                  {
                     qsResult = PackedRead_qapi_BLE_CGMS_Measurement_Data_t(&qsOutputBuffer, &qsBufferList, &((*MeasurementData)[qsIndex]));
                  }
               }

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
