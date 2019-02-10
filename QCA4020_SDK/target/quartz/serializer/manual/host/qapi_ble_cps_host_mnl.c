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
#include "qapi_ble_cps_common.h"
#include "qapi_ble_cps_host_mnl.h"
#include "qapi_ble_cps_host_cb.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_cpstypes_common.h"

qapi_BLE_CPS_Vector_Data_t *Mnl_qapi_BLE_CPS_Decode_CP_Vector(uint8_t TargetID, uint32_t BufferLength, uint8_t *Buffer)
{
   PackedBuffer_t              qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t              qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t          *qsBufferList = NULL;
   SerStatus_t                 qsResult = ssSuccess;
   uint16_t                    qsSize = 0;
   Boolean_t                   qsPointerValid = FALSE;
   qapi_BLE_CPS_Vector_Data_t *VectorData = NULL;

   /* Return value. */
   qapi_BLE_CPS_Vector_Data_t *qsRetVal = NULL;

   /* Calculate size of packed function arguments. */
   qsSize = (4 + (QS_POINTER_HEADER_SIZE * 1));

   qsSize = qsSize + ((BufferLength)*(1));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_CPS_FILE_ID, QAPI_BLE_CPS_DECODE_CP_VECTOR_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&BufferLength);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Buffer);

      if((qsResult == ssSuccess) && (Buffer != NULL))
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void *)Buffer, sizeof(uint8_t), BufferLength);
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
                  qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);

               if((qsResult == ssSuccess) && (qsPointerValid))
               {
                  VectorData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CPS_Vector_Data_t));
                  if(VectorData != NULL)
                  {
                     qsResult = PackedRead_qapi_BLE_CPS_Vector_Data_t(&qsOutputBuffer, &qsBufferList, (qapi_BLE_CPS_Vector_Data_t *)VectorData);

                     if(qsResult == ssSuccess)
                     {
                        /* qapi_BLE_CPS_Decode_CP_Vector() allocates    */
                        /* memory for the caller so we need to simulate */
                        /* this behaviour.                              */
                        if((qsRetVal = QSOSAL_AllocateMemory(sizeof(qapi_BLE_CPS_Vector_Data_t))) != NULL)
                        {
                           /* Format the mandatory fields.              */
                           /* * NOTE * This is only a shallow copy.     */
                           *qsRetVal = *VectorData;

                           /* Check if we need to allocate memory for   */
                           /* the instantaneous magnitude.              */
                           if((VectorData->InstantaneousMagnitude) && (VectorData->MagnitudeDataLength))
                           {
                               /* We know the pointer was valid from the*/
                               /* shallow copy so we will set it to NULL*/
                               /* in case we fail to allocate memory.   */
                               qsRetVal->InstantaneousMagnitude = NULL;

                              /* Allocate memory for the instantaneous  */
                              /* magnitude.                             */
                              if((qsRetVal->InstantaneousMagnitude = QSOSAL_AllocateMemory(VectorData->MagnitudeDataLength * QAPI_BLE_NON_ALIGNED_SWORD_SIZE)) != NULL)
                              {
                                 QSOSAL_MemCopy(qsRetVal->InstantaneousMagnitude, VectorData->InstantaneousMagnitude, (VectorData->MagnitudeDataLength * QAPI_BLE_NON_ALIGNED_SWORD_SIZE));
                              }
                              else
                                 qsResult = ssAllocationError;
                           }
                           else
                              qsRetVal->InstantaneousMagnitude = NULL;
                        }
                        else
                           qsResult = ssAllocationError;
                     }
                  }
                  else
                     qsResult = ssAllocationError;
               }
               else
                  qsRetVal = NULL;

               /* Set the return value to error if necessary. */
               if(qsResult != ssSuccess)
               {
                  qsRetVal = NULL;
               }
            }
            else
            {
               qsRetVal = NULL;
            }

            /* Free the output buffer. */
            FreePackedBuffer(&qsOutputBuffer);
         }
         else
         {
            qsRetVal = NULL;
         }
      }
      else
      {
         qsRetVal = NULL;
      }

      /* Free the input buffer. */
      FreePackedBuffer(&qsInputBuffer);
   }
   else
   {
      qsRetVal = NULL;
   }

   FreeBufferList(&qsBufferList);

   return(qsRetVal);
}

void Mnl_qapi_BLE_CPS_Free_CP_Vector_Data(uint8_t TargetID, qapi_BLE_CPS_Vector_Data_t * VectorData)
{
   if(VectorData)
   {
      /* Free the Instantaneous Force/Torque Magnitude Array if it was
         specified. */
      if(VectorData->InstantaneousMagnitude)
         QSOSAL_FreeMemory(VectorData->InstantaneousMagnitude);

      /* Free the container structure that was allocated. */
      QSOSAL_FreeMemory(VectorData);
   }
}

int Mnl_qapi_BLE_CPS_Decode_Control_Point_Response(uint8_t TargetID, uint32_t BufferLength, uint8_t *Buffer, qapi_BLE_CPS_Control_Point_Response_Data_t *ResponseData)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;
   Boolean_t          qsPointerValid = FALSE;
   uint8_t           *SensorLocations;

   /* Return value. */
   int qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (4 + (QS_POINTER_HEADER_SIZE * 2));

   qsSize = qsSize + ((BufferLength)*(1));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_CPS_FILE_ID, QAPI_BLE_CPS_DECODE_CONTROL_POINT_RESPONSE_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&BufferLength);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Buffer);

      if((qsResult == ssSuccess) && (Buffer != NULL))
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void *)Buffer, sizeof(uint8_t), BufferLength);
      }

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)ResponseData);

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
                  qsResult = PackedRead_qapi_BLE_CPS_Control_Point_Response_Data_t(&qsOutputBuffer, &qsBufferList, (qapi_BLE_CPS_Control_Point_Response_Data_t *)ResponseData);

                  if(qsResult == ssSuccess)
                  {
                     if(ResponseData->RequestOpCode == QAPI_BLE_CPS_CONTROL_POINT_OPCODE_REQUEST_SUPPORTED_SENSOR_LOCATIONS)
                     {
                        if((ResponseData->ResponseParameter.SupportedSensorLocations.NumberOfSensorLocations) && (ResponseData->ResponseParameter.SupportedSensorLocations.SensorLocations))
                        {
                           /* qapi_BLE_CPS_Decode_Control_Point_Response*/
                           /* allocates memory for the caller so we need*/
                           /* to simulate this behaviour.               */
                           if((SensorLocations = QSOSAL_AllocateMemory((ResponseData->ResponseParameter.SupportedSensorLocations.NumberOfSensorLocations))) != NULL)
                           {
                              /* Copy the allocated memory.             */
                              QSOSAL_MemCopy(SensorLocations, ResponseData->ResponseParameter.SupportedSensorLocations.SensorLocations, (ResponseData->ResponseParameter.SupportedSensorLocations.NumberOfSensorLocations));

                              /* Update the pointer.                    */
                              /* * NOTE * The old pointer will be freed */
                              /*          when the buffer list is       */
                              /*          cleaned up.                   */
                              ResponseData->ResponseParameter.SupportedSensorLocations.SensorLocations = SensorLocations;
                           }
                           else
                              qsResult = ssAllocationError;
                        }
                     }
                  }
               }
               else
                  ResponseData = NULL;

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

void Mnl_qapi_BLE_CPS_Free_Supported_Sensor_Locations_Data(uint8_t TargetID, uint8_t *SensorLocations)
{
   if(SensorLocations)
      QSOSAL_FreeMemory(SensorLocations);
}
