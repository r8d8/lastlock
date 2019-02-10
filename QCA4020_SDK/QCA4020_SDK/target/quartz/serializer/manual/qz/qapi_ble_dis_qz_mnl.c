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
#include "qapi_ble_dis_common.h"
#include "qapi_ble_dis_qz_mnl.h"

SerStatus_t Mnl_Handle_qapi_BLE_DIS_Query_Manufacturer_Name(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t InstanceID;
   char *ManufacturerName = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      ManufacturerName = AllocateBufferListEntry(&qsBufferList, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING+1));

      if(ManufacturerName == NULL)
         qsResult = ssAllocationError;
   }
   else
      ManufacturerName= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_DIS_Query_Manufacturer_Name(BluetoothStackID, InstanceID, ManufacturerName);

      qsOutputLength = (4 + (ManufacturerName == NULL ? 0 : (strlen(ManufacturerName) + 1)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_DIS_FILE_ID, QAPI_BLE_DIS_QUERY_MANUFACTURER_NAME_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ManufacturerName);

         if((qsResult == ssSuccess) && (ManufacturerName != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (void *)ManufacturerName, 1, (strlen((const char *)(ManufacturerName))+1));
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

SerStatus_t Mnl_Handle_qapi_BLE_DIS_Query_Model_Number(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t InstanceID;
   char *ModelNumber = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      ModelNumber = AllocateBufferListEntry(&qsBufferList, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING+1));

      if(ModelNumber == NULL)
         qsResult = ssAllocationError;
   }
   else
      ModelNumber= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_DIS_Query_Model_Number(BluetoothStackID, InstanceID, ModelNumber);

      qsOutputLength = (4 + (ModelNumber == NULL ? 0 : (strlen(ModelNumber) + 1)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_DIS_FILE_ID, QAPI_BLE_DIS_QUERY_MODEL_NUMBER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ModelNumber);

         if((qsResult == ssSuccess) && (ModelNumber != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (void *)ModelNumber, 1, (strlen((const char *)(ModelNumber))+1));
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

SerStatus_t Mnl_Handle_qapi_BLE_DIS_Query_Serial_Number(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t InstanceID;
   char *SerialNumber = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      SerialNumber = AllocateBufferListEntry(&qsBufferList, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING+1));

      if(SerialNumber == NULL)
         qsResult = ssAllocationError;
   }
   else
      SerialNumber= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_DIS_Query_Serial_Number(BluetoothStackID, InstanceID, SerialNumber);

      qsOutputLength = (4 + (SerialNumber == NULL ? 0 : (strlen(SerialNumber) + 1)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_DIS_FILE_ID, QAPI_BLE_DIS_QUERY_SERIAL_NUMBER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SerialNumber);

         if((qsResult == ssSuccess) && (SerialNumber != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (void *)SerialNumber, 1, (strlen((const char *)(SerialNumber))+1));
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

SerStatus_t Mnl_Handle_qapi_BLE_DIS_Query_Hardware_Revision(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t InstanceID;
   char *Hardware_Revision = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Hardware_Revision = AllocateBufferListEntry(&qsBufferList, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING+1));

      if(Hardware_Revision == NULL)
         qsResult = ssAllocationError;
   }
   else
      Hardware_Revision= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_DIS_Query_Hardware_Revision(BluetoothStackID, InstanceID, Hardware_Revision);

      qsOutputLength = (4 + (Hardware_Revision == NULL ? 0 : (strlen(Hardware_Revision) + 1)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_DIS_FILE_ID, QAPI_BLE_DIS_QUERY_HARDWARE_REVISION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Hardware_Revision);

         if((qsResult == ssSuccess) && (Hardware_Revision != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (void *)Hardware_Revision, 1, (strlen((const char *)(Hardware_Revision))+1));
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

SerStatus_t Mnl_Handle_qapi_BLE_DIS_Query_Firmware_Revision(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t InstanceID;
   char *FirmwareRevision = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      FirmwareRevision = AllocateBufferListEntry(&qsBufferList, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING+1));

      if(FirmwareRevision == NULL)
         qsResult = ssAllocationError;
   }
   else
      FirmwareRevision= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_DIS_Query_Firmware_Revision(BluetoothStackID, InstanceID, FirmwareRevision);

      qsOutputLength = (4 + (FirmwareRevision == NULL ? 0 : (strlen(FirmwareRevision) + 1)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_DIS_FILE_ID, QAPI_BLE_DIS_QUERY_FIRMWARE_REVISION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)FirmwareRevision);

         if((qsResult == ssSuccess) && (FirmwareRevision != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (void *)FirmwareRevision, 1, (strlen((const char *)(FirmwareRevision))+1));
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

SerStatus_t Mnl_Handle_qapi_BLE_DIS_Query_Software_Revision(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t InstanceID;
   char *SoftwareRevision = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      SoftwareRevision = AllocateBufferListEntry(&qsBufferList, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING+1));

      if(SoftwareRevision == NULL)
         qsResult = ssAllocationError;
   }
   else
      SoftwareRevision= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_DIS_Query_Software_Revision(BluetoothStackID, InstanceID, SoftwareRevision);

      qsOutputLength = (4 + (SoftwareRevision == NULL ? 0 : (strlen(SoftwareRevision) + 1)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_DIS_FILE_ID, QAPI_BLE_DIS_QUERY_SOFTWARE_REVISION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SoftwareRevision);

         if((qsResult == ssSuccess) && (SoftwareRevision != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (void *)SoftwareRevision, 1, (strlen((const char *)(SoftwareRevision))+1));
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

SerStatus_t Mnl_Handle_qapi_BLE_DIS_Query_IEEE_Certification_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint32_t InstanceID;
   uint8_t *IEEE_Certification_Data = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      IEEE_Certification_Data = AllocateBufferListEntry(&qsBufferList, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING+1));

      if(IEEE_Certification_Data == NULL)
         qsResult = ssAllocationError;
   }
   else
      IEEE_Certification_Data= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_DIS_Query_IEEE_Certification_Data(BluetoothStackID, InstanceID, IEEE_Certification_Data);

      qsOutputLength = (4 + (IEEE_Certification_Data == NULL ? 0 : (strlen((const char *)IEEE_Certification_Data) + 1)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_DIS_FILE_ID, QAPI_BLE_DIS_QUERY_IEEE_CERTIFICATION_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)IEEE_Certification_Data);

         if((qsResult == ssSuccess) && (IEEE_Certification_Data != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (uint8_t *)IEEE_Certification_Data, 1, (strlen((const char *)IEEE_Certification_Data)+1));
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
