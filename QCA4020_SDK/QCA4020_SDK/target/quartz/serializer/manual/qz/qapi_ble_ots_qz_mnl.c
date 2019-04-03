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
#include "qapi_ble_ots_common.h"
#include "qapi_ble_ots_qz_mnl.h"
#include "qapi_ble_ots_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_BLE_OTS_Initialize_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t BluetoothStackID;
   uint8_t ServiceFlags;
   qapi_BLE_OTS_Initialize_Data_t *InitializeData = NULL;
   uint32_t CallbackParameter;
   uint32_t *ServiceID = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ServiceFlags);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      ServiceID = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

      if(ServiceID == NULL)
         qsResult = ssAllocationError;
   }
   else
      ServiceID= NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      InitializeData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_OTS_Initialize_Data_t));

      if(InitializeData == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_OTS_Initialize_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_OTS_Initialize_Data_t *)InitializeData);

         /* Set the OTS Channel Event Callback handler.*/
         if(qsResult == ssSuccess)
         {
            InitializeData->EventCallback = QZ_qapi_BLE_OTS_Channel_Event_Callback_t_Handler;
         }
      }
   }
   else
      InitializeData = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_OTS_Initialize_Service(BluetoothStackID, ServiceFlags, InitializeData, QZ_qapi_BLE_OTS_Event_Callback_t_Handler, CallbackParameter, ServiceID);

      qsOutputLength = (4 + (ServiceID == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_OTS_FILE_ID, QAPI_BLE_OTS_INITIALIZE_SERVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ServiceID);

         if((qsResult == ssSuccess) && (ServiceID != NULL))
         {
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)ServiceID);
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

SerStatus_t Mnl_Handle_qapi_BLE_OTS_Initialize_Service_Handle_Range(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t BluetoothStackID;
   uint8_t ServiceFlags;
   qapi_BLE_OTS_Initialize_Data_t *InitializeData = NULL;
   uint32_t CallbackParameter;
   uint32_t *ServiceID = NULL;
   qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ServiceFlags);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      ServiceID = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

      if(ServiceID == NULL)
         qsResult = ssAllocationError;
   }
   else
      ServiceID= NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      InitializeData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_OTS_Initialize_Data_t));

      if(InitializeData == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_OTS_Initialize_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_OTS_Initialize_Data_t *)InitializeData);

         /* Set the OTS Channel Event Callback handler.*/
         if(qsResult == ssSuccess)
         {
            InitializeData->EventCallback = QZ_qapi_BLE_OTS_Channel_Event_Callback_t_Handler;
         }
      }
   }
   else
      InitializeData = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      ServiceHandleRange = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

      if(ServiceHandleRange == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_GATT_Attribute_Handle_Group_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange);
      }
   }
   else
      ServiceHandleRange = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_OTS_Initialize_Service_Handle_Range(BluetoothStackID, ServiceFlags, InitializeData, QZ_qapi_BLE_OTS_Event_Callback_t_Handler, CallbackParameter, ServiceID, ServiceHandleRange);

      qsOutputLength = (4 + (ServiceID == NULL ? 0 : 4) + (CalcPackedSize_qapi_BLE_GATT_Attribute_Handle_Group_t((qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange)) + (QS_POINTER_HEADER_SIZE * 2));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_OTS_FILE_ID, QAPI_BLE_OTS_INITIALIZE_SERVICE_HANDLE_RANGE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ServiceID);

         if((qsResult == ssSuccess) && (ServiceID != NULL))
         {
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)ServiceID);
         }

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ServiceHandleRange);

         if((qsResult == ssSuccess) && (ServiceHandleRange != NULL))
         {
            qsResult = PackedWrite_qapi_BLE_GATT_Attribute_Handle_Group_t(qsOutputBuffer, (qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange);
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

SerStatus_t Mnl_Handle_qapi_BLE_OTS_Read_Object_Metadata_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   qapi_BLE_OTS_Object_Metadata_Type_t Type;
   qapi_BLE_OTS_Object_Metadata_Data_t *Metadata = NULL;
   uint8_t Offset;

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
      qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&Type);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Offset);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Metadata = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_OTS_Object_Metadata_Data_t));

      if(Metadata == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         switch(Type)
         {
            case QAPI_BLE_OTS_OMT_OBJECT_NAME_E:
               if(qsResult == ssSuccess)
               {
                  qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, &(Metadata->Name.Buffer_Length));
               }

               if(qsResult == ssSuccess)
               {
                  qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
               }

               if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
               {
                  if((Metadata->Name.Buffer = AllocateBufferListEntry(&qsBufferList, Metadata->Name.Buffer_Length)) != NULL)
                  {
                     qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, Metadata->Name.Buffer, 1, Metadata->Name.Buffer_Length);
                  }
                  else
                     qsResult = ssAllocationError;
               }
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_TYPE_E:
               qsResult = PackedRead_qapi_BLE_GATT_UUID_t(&qsInputBuffer, &qsBufferList, &(Metadata->Type));
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_SIZE_E:
               qsResult = PackedRead_qapi_BLE_OTS_Object_Size_Data_t(&qsInputBuffer, &qsBufferList, &(Metadata->Size));
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_FIRST_CREATED_E:
            case QAPI_BLE_OTS_OMT_OBJECT_LAST_MODIFIED_E:
               /* Intentional fall through for OTS Date Time Data.      */
               qsResult = PackedRead_qapi_BLE_OTS_Date_Time_Data_t(&qsInputBuffer, &qsBufferList, &(Metadata->First_Created));
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_ID_E:
               qsResult = PackedRead_qapi_BLE_OTS_UINT48_Data_t(&qsInputBuffer, &qsBufferList, &(Metadata->ID));
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_PROPERTIES_E:
               qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, &(Metadata->Properties));
               break;
         }
      }
   }
   else
      Metadata = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, Metadata, Offset);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_OTS_FILE_ID, QAPI_BLE_OTS_READ_OBJECT_METADATA_REQUEST_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Mnl_Handle_qapi_BLE_OTS_Format_Object_Metadata(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   qapi_BLE_OTS_Object_Metadata_Type_t Type;
   qapi_BLE_OTS_Object_Metadata_Data_t *Metadata = NULL;
   uint16_t BufferLength;
   uint8_t *Buffer = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
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
      Metadata = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_OTS_Object_Metadata_Data_t));

      if(Metadata == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         switch(Type)
         {
            case QAPI_BLE_OTS_OMT_OBJECT_NAME_E:
               if(qsResult == ssSuccess)
               {
                  qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, &(Metadata->Name.Buffer_Length));
               }

               if(qsResult == ssSuccess)
               {
                  qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
               }

               if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
               {
                  if((Metadata->Name.Buffer = AllocateBufferListEntry(&qsBufferList, Metadata->Name.Buffer_Length)) != NULL)
                  {
                     qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, Metadata->Name.Buffer, 1, Metadata->Name.Buffer_Length);
                  }
                  else
                     qsResult = ssAllocationError;
               }
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_TYPE_E:
               qsResult = PackedRead_qapi_BLE_GATT_UUID_t(&qsInputBuffer, &qsBufferList, &(Metadata->Type));
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_SIZE_E:
               qsResult = PackedRead_qapi_BLE_OTS_Object_Size_Data_t(&qsInputBuffer, &qsBufferList, &(Metadata->Size));
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_FIRST_CREATED_E:
            case QAPI_BLE_OTS_OMT_OBJECT_LAST_MODIFIED_E:
               /* Intentional fall through for OTS Date Time Data.      */
               qsResult = PackedRead_qapi_BLE_OTS_Date_Time_Data_t(&qsInputBuffer, &qsBufferList, &(Metadata->First_Created));
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_ID_E:
               qsResult = PackedRead_qapi_BLE_OTS_UINT48_Data_t(&qsInputBuffer, &qsBufferList, &(Metadata->ID));
               break;
            case QAPI_BLE_OTS_OMT_OBJECT_PROPERTIES_E:
               qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, &(Metadata->Properties));
               break;
         }
      }
   }
   else
      Metadata = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_OTS_Format_Object_Metadata(Type, Metadata, BufferLength, Buffer);

      qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      if(Buffer != NULL)
         qsOutputLength = qsOutputLength + ((BufferLength)*(1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_OTS_FILE_ID, QAPI_BLE_OTS_FORMAT_OBJECT_METADATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Buffer);

         if(qsResult == ssSuccess)
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (void *)Buffer, sizeof(uint8_t), BufferLength);
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

SerStatus_t Mnl_Handle_qapi_BLE_OTS_Decode_Object_Metadata(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   qapi_BLE_OTS_Object_Metadata_Type_t Type;
   qapi_BLE_OTS_Object_Metadata_Data_t *Metadata = NULL;

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
      Metadata = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_OTS_Object_Metadata_Data_t));

      if(Metadata == NULL)
      {
         qsResult = ssAllocationError;
      }
   }
   else
      Metadata= NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, Metadata);

      qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      switch(Type)
      {
         case QAPI_BLE_OTS_OMT_OBJECT_NAME_E:
            qsOutputLength += CalcPackedSize_8(&(Metadata->Name.Buffer_Length));
            qsOutputLength += QS_POINTER_HEADER_SIZE;
            qsOutputLength += Metadata->Name.Buffer_Length;
            break;
         case QAPI_BLE_OTS_OMT_OBJECT_TYPE_E:
            qsOutputLength += CalcPackedSize_qapi_BLE_GATT_UUID_t(&(Metadata->Type));
            break;
         case QAPI_BLE_OTS_OMT_OBJECT_SIZE_E:
            qsOutputLength += CalcPackedSize_qapi_BLE_OTS_Object_Size_Data_t(&(Metadata->Size));
            break;
         case QAPI_BLE_OTS_OMT_OBJECT_FIRST_CREATED_E:
         case QAPI_BLE_OTS_OMT_OBJECT_LAST_MODIFIED_E:
            /* Intentional fall through for OTS Date Time Data.         */
            qsOutputLength += CalcPackedSize_qapi_BLE_OTS_Date_Time_Data_t(&(Metadata->First_Created));
            break;
         case QAPI_BLE_OTS_OMT_OBJECT_ID_E:
            qsOutputLength += CalcPackedSize_qapi_BLE_OTS_UINT48_Data_t(&(Metadata->ID));
            break;
         case QAPI_BLE_OTS_OMT_OBJECT_PROPERTIES_E:
            qsOutputLength += CalcPackedSize_32(&(Metadata->Properties));
            break;
      }

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_OTS_FILE_ID, QAPI_BLE_OTS_DECODE_OBJECT_METADATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Metadata);

         if(qsResult == ssSuccess)
         {
            switch(Type)
            {
               case QAPI_BLE_OTS_OMT_OBJECT_NAME_E:
                  if(qsResult == ssSuccess)
                  {
                     qsResult = PackedWrite_8(qsOutputBuffer, &(Metadata->Name.Buffer_Length));
                  }

                  if(qsResult == ssSuccess)
                  {
                     qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Metadata->Name.Buffer);
                  }

                  if(qsResult == ssSuccess)
                  {
                     qsResult = PackedWrite_Array(qsOutputBuffer, Metadata->Name.Buffer, 1, Metadata->Name.Buffer_Length);
                  }
                  break;
               case QAPI_BLE_OTS_OMT_OBJECT_TYPE_E:
                  qsResult = PackedWrite_qapi_BLE_GATT_UUID_t(qsOutputBuffer, &(Metadata->Type));
                  break;
               case QAPI_BLE_OTS_OMT_OBJECT_SIZE_E:
                  qsResult = PackedWrite_qapi_BLE_OTS_Object_Size_Data_t(qsOutputBuffer, &(Metadata->Size));
                  break;
               case QAPI_BLE_OTS_OMT_OBJECT_FIRST_CREATED_E:
               case QAPI_BLE_OTS_OMT_OBJECT_LAST_MODIFIED_E:
                  /* Intentional fall through for OTS Date Time Data.   */
                  qsResult = PackedWrite_qapi_BLE_OTS_Date_Time_Data_t(qsOutputBuffer, &(Metadata->First_Created));
                  break;
               case QAPI_BLE_OTS_OMT_OBJECT_ID_E:
                  qsResult = PackedWrite_qapi_BLE_OTS_UINT48_Data_t(qsOutputBuffer, &(Metadata->ID));
                  break;
               case QAPI_BLE_OTS_OMT_OBJECT_PROPERTIES_E:
                  qsResult = PackedWrite_32(qsOutputBuffer, &(Metadata->Properties));
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
