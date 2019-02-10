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
#include "qapi_ble_gap_common.h"
#include "qapi_ble_gap_qz_mnl.h"
#include "qapi_ble_gap_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_BLE_GAP_LE_Set_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t Length;
   uint8_t *Advertising_Data = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Length);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Advertising_Data = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

      if(Advertising_Data == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Advertising_Data, sizeof(uint8_t), Length);
      }
   }
   else
      Advertising_Data = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_GAP_LE_Set_Advertising_Data(BluetoothStackID, Length, (qapi_BLE_Advertising_Data_t *)Advertising_Data);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_ADVERTISING_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Mnl_Handle_qapi_BLE_GAP_LE_Convert_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data = NULL;
   uint8_t *Advertising_Data = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Advertising_Data = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Advertising_Data_t));

      if(Advertising_Data == NULL)
         qsResult = ssAllocationError;
   }
   else
      Advertising_Data= NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      GAP_LE_Advertising_Data = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Advertising_Data_t));

      if(GAP_LE_Advertising_Data == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_GAP_LE_Advertising_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Advertising_Data_t *)GAP_LE_Advertising_Data);
      }
   }
   else
      GAP_LE_Advertising_Data = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_GAP_LE_Convert_Advertising_Data(GAP_LE_Advertising_Data, (qapi_BLE_Advertising_Data_t *)Advertising_Data);

      qsOutputLength = (4 + (Advertising_Data == NULL ? 0 : sizeof(qapi_BLE_Advertising_Data_t)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_CONVERT_ADVERTISING_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Advertising_Data);

         if((qsResult == ssSuccess) && (Advertising_Data != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (uint8_t *)Advertising_Data, 1, sizeof(qapi_BLE_Advertising_Data_t));
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
SerStatus_t Mnl_Handle_qapi_BLE_GAP_LE_Parse_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;
   uint32_t           qsIndex = 0;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint8_t *Advertising_Data = NULL;
   qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Advertising_Data = AllocateBufferListEntry(&qsBufferList, QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE);

      if(Advertising_Data == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (uint8_t *)Advertising_Data, 1 , QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE);
      }
   }
   else
      Advertising_Data = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      GAP_LE_Advertising_Data = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Advertising_Data_t));

      if(GAP_LE_Advertising_Data == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
          if(qsInputBuffer.Remaining >= QAPI_BLE_GAP_LE_ADVERTISING_DATA_T_MIN_PACKED_SIZE)
          {
              if(qsResult == ssSuccess)
                  qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&GAP_LE_Advertising_Data->Number_Data_Entries);

              if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

              if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
              {
                  GAP_LE_Advertising_Data->Data_Entries = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GAP_LE_Advertising_Data_Entry_t)*(GAP_LE_Advertising_Data->Number_Data_Entries)));

                  if(GAP_LE_Advertising_Data->Data_Entries == NULL)
                  {
                      qsResult = ssAllocationError;
                  }

                  /* Memory will be allocated for the AD buffer field by*/
                  /* the qapi_BLE_GAP_LE_Parse_Advertising_Data()       */
                  /* function.                                          */
              }
              else
                  GAP_LE_Advertising_Data->Data_Entries = NULL;

          }
          else
          {
              qsResult = ssInvalidLength;
          }
      }
   }
   else
      GAP_LE_Advertising_Data = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_GAP_LE_Parse_Advertising_Data((qapi_BLE_Advertising_Data_t *)Advertising_Data, GAP_LE_Advertising_Data);

      qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_GAP_LE_Advertising_Data_t((qapi_BLE_GAP_LE_Advertising_Data_t *)GAP_LE_Advertising_Data)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_PARSE_ADVERTISING_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)GAP_LE_Advertising_Data);

         if((qsResult == ssSuccess) && (GAP_LE_Advertising_Data != NULL))
         {
            qsResult = PackedWrite_qapi_BLE_GAP_LE_Advertising_Data_t(qsOutputBuffer, (qapi_BLE_GAP_LE_Advertising_Data_t *)GAP_LE_Advertising_Data);

            /* Free the memory allocated for each AD buffer field.      */
            for (qsIndex = 0; qsIndex < GAP_LE_Advertising_Data->Number_Data_Entries; qsIndex++)
            {
               if(GAP_LE_Advertising_Data->Data_Entries[qsIndex].AD_Data_Buffer)
                  QSOSAL_FreeMemory(GAP_LE_Advertising_Data->Data_Entries[qsIndex].AD_Data_Buffer);
            }
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

SerStatus_t Mnl_Handle_qapi_BLE_GAP_LE_Set_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t Length;
   uint8_t *Scan_Response_Data = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Length);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Scan_Response_Data = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

      if(Scan_Response_Data == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Response_Data, sizeof(uint8_t), Length);
      }
   }
   else
      Scan_Response_Data = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_GAP_LE_Set_Scan_Response_Data(BluetoothStackID, Length, (qapi_BLE_Scan_Response_Data_t *)Scan_Response_Data);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_SCAN_RESPONSE_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Mnl_Handle_qapi_BLE_GAP_LE_Convert_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{

   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data = NULL;
   uint8_t *Scan_Response_Data = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Scan_Response_Data = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Scan_Response_Data_t));

      if(Scan_Response_Data == NULL)
         qsResult = ssAllocationError;
   }
   else
      Scan_Response_Data= NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      GAP_LE_Advertising_Data = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Advertising_Data_t));

      if(GAP_LE_Advertising_Data == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_GAP_LE_Advertising_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Advertising_Data_t *)GAP_LE_Advertising_Data);
      }
   }
   else
      GAP_LE_Advertising_Data = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_GAP_LE_Convert_Scan_Response_Data(GAP_LE_Advertising_Data, (qapi_BLE_Scan_Response_Data_t *)Scan_Response_Data);

      qsOutputLength = (4 + (Scan_Response_Data == NULL ? 0 : sizeof(qapi_BLE_Scan_Response_Data_t)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_CONVERT_SCAN_RESPONSE_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Scan_Response_Data);

         if((qsResult == ssSuccess) && (Scan_Response_Data != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (uint8_t *)Scan_Response_Data, 1, sizeof(qapi_BLE_Scan_Response_Data_t));
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

SerStatus_t Mnl_Handle_qapi_BLE_GAP_LE_Parse_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;
   uint32_t           qsIndex = 0;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint8_t *Scan_Response_Data = NULL;
   qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Scan_Response_Data = AllocateBufferListEntry(&qsBufferList, QAPI_BLE_SCAN_RESPONSE_DATA_MAXIMUM_SIZE);

      if(Scan_Response_Data == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (uint8_t *)Scan_Response_Data, 1 , QAPI_BLE_SCAN_RESPONSE_DATA_MAXIMUM_SIZE);
      }
   }
   else
      Scan_Response_Data = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      GAP_LE_Advertising_Data = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Advertising_Data_t));

      if(GAP_LE_Advertising_Data == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         if(qsInputBuffer.Remaining >= QAPI_BLE_GAP_LE_ADVERTISING_DATA_T_MIN_PACKED_SIZE)
          {
              if(qsResult == ssSuccess)
                  qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&GAP_LE_Advertising_Data->Number_Data_Entries);

              if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

              if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
              {
                  GAP_LE_Advertising_Data->Data_Entries = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GAP_LE_Advertising_Data_Entry_t)*(GAP_LE_Advertising_Data->Number_Data_Entries)));

                  if(GAP_LE_Advertising_Data->Data_Entries == NULL)
                  {
                      qsResult = ssAllocationError;
                  }

                  /* Memory will be allocated for the AD buffer field by*/
                  /* the qapi_BLE_GAP_LE_Parse_Scan_Response_Data()     */
                  /* function.                                          */
              }
              else
                  GAP_LE_Advertising_Data->Data_Entries = NULL;

          }
          else
          {
              qsResult = ssInvalidLength;
          }
      }
   }
   else
      GAP_LE_Advertising_Data= NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_GAP_LE_Parse_Scan_Response_Data((qapi_BLE_Scan_Response_Data_t *)Scan_Response_Data, GAP_LE_Advertising_Data);

      qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_GAP_LE_Advertising_Data_t((qapi_BLE_GAP_LE_Advertising_Data_t *)GAP_LE_Advertising_Data)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_PARSE_SCAN_RESPONSE_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)GAP_LE_Advertising_Data);

         if((qsResult == ssSuccess) && (GAP_LE_Advertising_Data != NULL))
         {
            qsResult = PackedWrite_qapi_BLE_GAP_LE_Advertising_Data_t(qsOutputBuffer, (qapi_BLE_GAP_LE_Advertising_Data_t *)GAP_LE_Advertising_Data);

            /* Free the memory allocated for each AD buffer field.      */
            for (qsIndex = 0; qsIndex < GAP_LE_Advertising_Data->Number_Data_Entries; qsIndex++)
            {
               if(GAP_LE_Advertising_Data->Data_Entries[qsIndex].AD_Data_Buffer)
                  QSOSAL_FreeMemory(GAP_LE_Advertising_Data->Data_Entries[qsIndex].AD_Data_Buffer);
            }
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
