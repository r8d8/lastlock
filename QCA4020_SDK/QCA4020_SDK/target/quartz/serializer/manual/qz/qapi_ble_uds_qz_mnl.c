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
#include "qapi_ble_uds_common.h"
#include "qapi_ble_uds_qz_mnl.h"
#include "qapi_ble_uds_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_BLE_UDS_Read_Characteristic_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t TransactionID;
   uint8_t ErrorCode;
   uint16_t Offset;
   qapi_BLE_UDS_Characteristic_Type_t Type;
   qapi_BLE_UDS_Characteristic_t *UDS_Characteristic = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Offset);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&Type);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      UDS_Characteristic = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_UDS_Characteristic_t));

      if(UDS_Characteristic == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         switch(Type)
         {
            case QAPI_BLE_UDS_CT_FIRST_NAME_E:
            case QAPI_BLE_UDS_CT_LAST_NAME_E:
            case QAPI_BLE_UDS_CT_EMAIL_ADDRESS_E:
            case QAPI_BLE_UDS_CT_LANGUAGE_E:
               if(qsResult == ssSuccess)
                  qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->First_Name.Buffer_Length));

               if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

               if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
               {
                  if(qsResult == ssSuccess)
                  {
                     if((UDS_Characteristic->First_Name.Buffer = malloc(UDS_Characteristic->First_Name.Buffer_Length)) != NULL)
                     {
                        qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, UDS_Characteristic->First_Name.Buffer, 1, UDS_Characteristic->First_Name.Buffer_Length);
                     }
                     else
                        qsResult = ssAllocationError;
                  }
               }
               break;
            case QAPI_BLE_UDS_CT_AGE_E:
            case QAPI_BLE_UDS_CT_GENDER_E:
            case QAPI_BLE_UDS_CT_VO2_MAX_E:
            case QAPI_BLE_UDS_CT_HEART_RATE_MAX_E:
            case QAPI_BLE_UDS_CT_RESTING_HEART_RATE_E:
            case QAPI_BLE_UDS_CT_MAXIMUM_RECOMMENDED_HEART_RATE_E:
            case QAPI_BLE_UDS_CT_AEROBIC_THRESHOLD_E:
            case QAPI_BLE_UDS_CT_ANAEROBIC_THRESHOLD_E:
            case QAPI_BLE_UDS_CT_SPORT_TYPE_E:
            case QAPI_BLE_UDS_CT_FAT_BURN_HEART_RATE_LOWER_LIMIT_E:
            case QAPI_BLE_UDS_CT_FAT_BURN_HEART_RATE_UPPER_LIMIT_E:
            case QAPI_BLE_UDS_CT_AEROBIC_HEART_RATE_LOWER_LIMIT_E:
            case QAPI_BLE_UDS_CT_AEROBIC_HEART_RATE_UPPER_LIMIT_E:
            case QAPI_BLE_UDS_CT_ANAEROBIC_HEART_RATE_LOWER_LIMIT_E:
            case QAPI_BLE_UDS_CT_ANAEROBIC_HEART_RATE_UPPER_LIMIT_E:
            case QAPI_BLE_UDS_CT_TWO_ZONE_HEART_RATE_LIMIT_E:
               /* Intentional fall through for UINT8.                   */
               qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Age));
               break;
            case QAPI_BLE_UDS_CT_WEIGHT_E:
            case QAPI_BLE_UDS_CT_HEIGHT_E:
            case QAPI_BLE_UDS_CT_WAIST_CIRCUMFERENCE_E:
            case QAPI_BLE_UDS_CT_HIP_CIRCUMFERENCE_E:
               /* Intentional fall through for UINT16.                  */
               qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Weight));
               break;
            case QAPI_BLE_UDS_CT_DATE_OF_BIRTH_E:
            case QAPI_BLE_UDS_CT_DATE_OF_THRESHOLD_E:
               /* Intentional fall through for UDS Data/Time data.      */
               qsResult = PackedRead_qapi_BLE_UDS_Date_Data_t(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Date_Of_Birth));
               break;
            case QAPI_BLE_UDS_CT_FIVE_ZONE_HEART_RATE_LIMITS_E:
               qsResult = PackedRead_qapi_BLE_UDS_Five_Zone_Heart_Rate_Limits_Data_t(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Five_Zone_Heart_Rate_Limits));
               break;
            case QAPI_BLE_UDS_CT_THREE_ZONE_HEART_RATE_LIMITS_E:
               qsResult = PackedRead_qapi_BLE_UDS_Three_Zone_Heart_Rate_Limits_Data_t(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Three_Zone_Heart_Rate_Limits));
               break;
         }
      }
   }
   else
      UDS_Characteristic = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, UDS_Characteristic);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_UDS_FILE_ID, QAPI_BLE_UDS_READ_CHARACTERISTIC_REQUEST_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

   if(UDS_Characteristic)
   {
      switch(Type)
      {
         case QAPI_BLE_UDS_CT_FIRST_NAME_E:
         case QAPI_BLE_UDS_CT_LAST_NAME_E:
         case QAPI_BLE_UDS_CT_EMAIL_ADDRESS_E:
         case QAPI_BLE_UDS_CT_LANGUAGE_E:
            if(UDS_Characteristic->First_Name.Buffer)
               free(UDS_Characteristic->First_Name.Buffer);
            break;
         default:
            /* Prevent compiler warnings.*/
            break;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_BLE_UDS_Format_UDS_Characteristic_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   uint32_t           qsIndex;
   Boolean_t          qsPointerValid = FALSE;

   UNUSED(qsPointerValid);
   UNUSED(qsIndex);

   /* Return value. */
   int qsRetVal;

   /* Function parameters. */
   qapi_BLE_UDS_Characteristic_Type_t Type;
   qapi_BLE_UDS_Characteristic_t *UDS_Characteristic = NULL;
   uint16_t BufferLength;
   uint8_t *Buffer = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&Type);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&BufferLength);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Buffer = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(BufferLength)));

      if(Buffer == NULL)
         qsResult = ssAllocationError;
   }
   else
      Buffer= NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      UDS_Characteristic = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_UDS_Characteristic_t));

      if(UDS_Characteristic == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         switch(Type)
         {
            case QAPI_BLE_UDS_CT_FIRST_NAME_E:
            case QAPI_BLE_UDS_CT_LAST_NAME_E:
            case QAPI_BLE_UDS_CT_EMAIL_ADDRESS_E:
            case QAPI_BLE_UDS_CT_LANGUAGE_E:
               if(qsResult == ssSuccess)
                  qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->First_Name.Buffer_Length));

               if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

               if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
               {
                  if(qsResult == ssSuccess)
                  {
                     if((UDS_Characteristic->First_Name.Buffer = malloc(UDS_Characteristic->First_Name.Buffer_Length)) != NULL)
                     {
                        qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, UDS_Characteristic->First_Name.Buffer, 1, UDS_Characteristic->First_Name.Buffer_Length);
                     }
                     else
                        qsResult = ssAllocationError;
                  }
               }
               break;
            case QAPI_BLE_UDS_CT_AGE_E:
            case QAPI_BLE_UDS_CT_GENDER_E:
            case QAPI_BLE_UDS_CT_VO2_MAX_E:
            case QAPI_BLE_UDS_CT_HEART_RATE_MAX_E:
            case QAPI_BLE_UDS_CT_RESTING_HEART_RATE_E:
            case QAPI_BLE_UDS_CT_MAXIMUM_RECOMMENDED_HEART_RATE_E:
            case QAPI_BLE_UDS_CT_AEROBIC_THRESHOLD_E:
            case QAPI_BLE_UDS_CT_ANAEROBIC_THRESHOLD_E:
            case QAPI_BLE_UDS_CT_SPORT_TYPE_E:
            case QAPI_BLE_UDS_CT_FAT_BURN_HEART_RATE_LOWER_LIMIT_E:
            case QAPI_BLE_UDS_CT_FAT_BURN_HEART_RATE_UPPER_LIMIT_E:
            case QAPI_BLE_UDS_CT_AEROBIC_HEART_RATE_LOWER_LIMIT_E:
            case QAPI_BLE_UDS_CT_AEROBIC_HEART_RATE_UPPER_LIMIT_E:
            case QAPI_BLE_UDS_CT_ANAEROBIC_HEART_RATE_LOWER_LIMIT_E:
            case QAPI_BLE_UDS_CT_ANAEROBIC_HEART_RATE_UPPER_LIMIT_E:
            case QAPI_BLE_UDS_CT_TWO_ZONE_HEART_RATE_LIMIT_E:
               /* Intentional fall through for UINT8.                   */
               qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Age));
               break;
            case QAPI_BLE_UDS_CT_WEIGHT_E:
            case QAPI_BLE_UDS_CT_HEIGHT_E:
            case QAPI_BLE_UDS_CT_WAIST_CIRCUMFERENCE_E:
            case QAPI_BLE_UDS_CT_HIP_CIRCUMFERENCE_E:
               /* Intentional fall through for UINT16.                  */
               qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Weight));
               break;
            case QAPI_BLE_UDS_CT_DATE_OF_BIRTH_E:
            case QAPI_BLE_UDS_CT_DATE_OF_THRESHOLD_E:
               /* Intentional fall through for UDS Data/Time data.      */
               qsResult = PackedRead_qapi_BLE_UDS_Date_Data_t(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Date_Of_Birth));
               break;
            case QAPI_BLE_UDS_CT_FIVE_ZONE_HEART_RATE_LIMITS_E:
               qsResult = PackedRead_qapi_BLE_UDS_Five_Zone_Heart_Rate_Limits_Data_t(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Five_Zone_Heart_Rate_Limits));
               break;
            case QAPI_BLE_UDS_CT_THREE_ZONE_HEART_RATE_LIMITS_E:
               qsResult = PackedRead_qapi_BLE_UDS_Three_Zone_Heart_Rate_Limits_Data_t(&qsInputBuffer, &qsBufferList, &(UDS_Characteristic->Three_Zone_Heart_Rate_Limits));
               break;
         }
      }
   }
   else
      UDS_Characteristic = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_UDS_Format_UDS_Characteristic_Request(Type, UDS_Characteristic, BufferLength, Buffer);

      qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      if(Buffer != NULL)
         qsOutputLength = qsOutputLength + ((BufferLength)*(1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_UDS_FILE_ID, QAPI_BLE_UDS_FORMAT_UDS_CHARACTERISTIC_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Buffer);

         if((qsResult == ssSuccess) && (Buffer != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (void *)Buffer, sizeof(uint8_t), BufferLength);
         }
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   if(UDS_Characteristic)
   {
      switch(Type)
      {
         case QAPI_BLE_UDS_CT_FIRST_NAME_E:
         case QAPI_BLE_UDS_CT_LAST_NAME_E:
         case QAPI_BLE_UDS_CT_EMAIL_ADDRESS_E:
         case QAPI_BLE_UDS_CT_LANGUAGE_E:
            if(UDS_Characteristic->First_Name.Buffer)
               free(UDS_Characteristic->First_Name.Buffer);
            break;
         default:
            /* Prevent compiler warnings.*/
            break;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_BLE_UDS_Decode_UDS_Characteristic_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint32_t ValueLength;
   uint8_t *Value = NULL;
   qapi_BLE_UDS_Characteristic_Type_t Type;
   qapi_BLE_UDS_Characteristic_t *UDS_Characteristic = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ValueLength);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&Type);

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
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      UDS_Characteristic = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_UDS_Characteristic_t));

      if(UDS_Characteristic == NULL)
      {
         qsResult = ssAllocationError;
      }
   }
   else
      UDS_Characteristic= NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, UDS_Characteristic);

      qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      if(UDS_Characteristic)
      {
         switch(Type)
         {
            case QAPI_BLE_UDS_CT_FIRST_NAME_E:
            case QAPI_BLE_UDS_CT_LAST_NAME_E:
            case QAPI_BLE_UDS_CT_EMAIL_ADDRESS_E:
            case QAPI_BLE_UDS_CT_LANGUAGE_E:
               /* Intentional fall through for UDS string data.            */
               qsOutputLength += CalcPackedSize_16(&(UDS_Characteristic->First_Name.Buffer_Length));
               qsOutputLength += QS_POINTER_HEADER_SIZE;
               qsOutputLength += UDS_Characteristic->First_Name.Buffer_Length;
               break;
            case QAPI_BLE_UDS_CT_AGE_E:
            case QAPI_BLE_UDS_CT_GENDER_E:
            case QAPI_BLE_UDS_CT_VO2_MAX_E:
            case QAPI_BLE_UDS_CT_HEART_RATE_MAX_E:
            case QAPI_BLE_UDS_CT_RESTING_HEART_RATE_E:
            case QAPI_BLE_UDS_CT_MAXIMUM_RECOMMENDED_HEART_RATE_E:
            case QAPI_BLE_UDS_CT_AEROBIC_THRESHOLD_E:
            case QAPI_BLE_UDS_CT_ANAEROBIC_THRESHOLD_E:
            case QAPI_BLE_UDS_CT_SPORT_TYPE_E:
            case QAPI_BLE_UDS_CT_FAT_BURN_HEART_RATE_LOWER_LIMIT_E:
            case QAPI_BLE_UDS_CT_FAT_BURN_HEART_RATE_UPPER_LIMIT_E:
            case QAPI_BLE_UDS_CT_AEROBIC_HEART_RATE_LOWER_LIMIT_E:
            case QAPI_BLE_UDS_CT_AEROBIC_HEART_RATE_UPPER_LIMIT_E:
            case QAPI_BLE_UDS_CT_ANAEROBIC_HEART_RATE_LOWER_LIMIT_E:
            case QAPI_BLE_UDS_CT_ANAEROBIC_HEART_RATE_UPPER_LIMIT_E:
            case QAPI_BLE_UDS_CT_TWO_ZONE_HEART_RATE_LIMIT_E:
               /* Intentional fall through for UINT8.                      */
               qsOutputLength += CalcPackedSize_8(&(UDS_Characteristic->Age));
               break;
            case QAPI_BLE_UDS_CT_WEIGHT_E:
            case QAPI_BLE_UDS_CT_HEIGHT_E:
            case QAPI_BLE_UDS_CT_WAIST_CIRCUMFERENCE_E:
            case QAPI_BLE_UDS_CT_HIP_CIRCUMFERENCE_E:
               /* Intentional fall through for UINT16.                     */
               qsOutputLength += CalcPackedSize_16(&(UDS_Characteristic->Weight));
               break;
            case QAPI_BLE_UDS_CT_DATE_OF_BIRTH_E:
            case QAPI_BLE_UDS_CT_DATE_OF_THRESHOLD_E:
               /* Intentional fall through for UDS Data/Time data.         */
               qsOutputLength += CalcPackedSize_qapi_BLE_UDS_Date_Data_t(&(UDS_Characteristic->Date_Of_Birth));
               break;
            case QAPI_BLE_UDS_CT_FIVE_ZONE_HEART_RATE_LIMITS_E:
               qsOutputLength += CalcPackedSize_qapi_BLE_UDS_Five_Zone_Heart_Rate_Limits_Data_t(&(UDS_Characteristic->Five_Zone_Heart_Rate_Limits));
               break;
            case QAPI_BLE_UDS_CT_THREE_ZONE_HEART_RATE_LIMITS_E:
               qsOutputLength += CalcPackedSize_qapi_BLE_UDS_Three_Zone_Heart_Rate_Limits_Data_t(&(UDS_Characteristic->Three_Zone_Heart_Rate_Limits));
               break;
         }
      }

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_UDS_FILE_ID, QAPI_BLE_UDS_DECODE_UDS_CHARACTERISTIC_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)UDS_Characteristic);

         if((qsResult == ssSuccess) && (UDS_Characteristic))
         {
            switch(Type)
            {
               case QAPI_BLE_UDS_CT_FIRST_NAME_E:
               case QAPI_BLE_UDS_CT_LAST_NAME_E:
               case QAPI_BLE_UDS_CT_EMAIL_ADDRESS_E:
               case QAPI_BLE_UDS_CT_LANGUAGE_E:
                  if(qsResult == ssSuccess)
                     qsResult = PackedWrite_16(qsOutputBuffer, &(UDS_Characteristic->First_Name.Buffer_Length));

                  if(qsResult == ssSuccess)
                     qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)UDS_Characteristic->First_Name.Buffer);

                  if(qsResult == ssSuccess)
                  {
                     qsResult = PackedWrite_Array(qsOutputBuffer, UDS_Characteristic->First_Name.Buffer, 1, UDS_Characteristic->First_Name.Buffer_Length);
                  }
                  break;
               case QAPI_BLE_UDS_CT_AGE_E:
               case QAPI_BLE_UDS_CT_GENDER_E:
               case QAPI_BLE_UDS_CT_VO2_MAX_E:
               case QAPI_BLE_UDS_CT_HEART_RATE_MAX_E:
               case QAPI_BLE_UDS_CT_RESTING_HEART_RATE_E:
               case QAPI_BLE_UDS_CT_MAXIMUM_RECOMMENDED_HEART_RATE_E:
               case QAPI_BLE_UDS_CT_AEROBIC_THRESHOLD_E:
               case QAPI_BLE_UDS_CT_ANAEROBIC_THRESHOLD_E:
               case QAPI_BLE_UDS_CT_SPORT_TYPE_E:
               case QAPI_BLE_UDS_CT_FAT_BURN_HEART_RATE_LOWER_LIMIT_E:
               case QAPI_BLE_UDS_CT_FAT_BURN_HEART_RATE_UPPER_LIMIT_E:
               case QAPI_BLE_UDS_CT_AEROBIC_HEART_RATE_LOWER_LIMIT_E:
               case QAPI_BLE_UDS_CT_AEROBIC_HEART_RATE_UPPER_LIMIT_E:
               case QAPI_BLE_UDS_CT_ANAEROBIC_HEART_RATE_LOWER_LIMIT_E:
               case QAPI_BLE_UDS_CT_ANAEROBIC_HEART_RATE_UPPER_LIMIT_E:
               case QAPI_BLE_UDS_CT_TWO_ZONE_HEART_RATE_LIMIT_E:
                  /* Intentional fall through for UINT8.                */
                  qsResult = PackedWrite_8(qsOutputBuffer, &(UDS_Characteristic->Age));
                  break;
               case QAPI_BLE_UDS_CT_WEIGHT_E:
               case QAPI_BLE_UDS_CT_HEIGHT_E:
               case QAPI_BLE_UDS_CT_WAIST_CIRCUMFERENCE_E:
               case QAPI_BLE_UDS_CT_HIP_CIRCUMFERENCE_E:
                  /* Intentional fall through for UINT16.               */
                  qsResult = PackedWrite_16(qsOutputBuffer, &(UDS_Characteristic->Weight));
                  break;
               case QAPI_BLE_UDS_CT_DATE_OF_BIRTH_E:
               case QAPI_BLE_UDS_CT_DATE_OF_THRESHOLD_E:
                  /* Intentional fall through for UDS Data/Time data.   */
                  qsResult = PackedWrite_qapi_BLE_UDS_Date_Data_t(qsOutputBuffer, &(UDS_Characteristic->Date_Of_Birth));
                  break;
               case QAPI_BLE_UDS_CT_FIVE_ZONE_HEART_RATE_LIMITS_E:
                  qsResult = PackedWrite_qapi_BLE_UDS_Five_Zone_Heart_Rate_Limits_Data_t(qsOutputBuffer, &(UDS_Characteristic->Five_Zone_Heart_Rate_Limits));
                  break;
               case QAPI_BLE_UDS_CT_THREE_ZONE_HEART_RATE_LIMITS_E:
                  qsResult = PackedWrite_qapi_BLE_UDS_Three_Zone_Heart_Rate_Limits_Data_t(qsOutputBuffer, &(UDS_Characteristic->Three_Zone_Heart_Rate_Limits));
                  break;
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
