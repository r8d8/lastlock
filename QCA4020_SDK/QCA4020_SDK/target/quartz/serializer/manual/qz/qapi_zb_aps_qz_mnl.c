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
#include "qapi_zb.h"
#include "qapi_zb_aps_common.h"
#include "qapi_zb_aps_qz_mnl.h"
#include "qapi_zb_aps_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_ZB_APSME_Get_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_ZB_Handle_t ZB_Handle;
   qapi_ZB_AIB_Attribute_ID_t AIBAttribute;
   uint8_t AIBAttributeIndex;
   uint16_t *AIBAttributeLength = NULL;
   void *AIBAttributeValue = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ZB_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&AIBAttribute);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AIBAttributeIndex);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      AIBAttributeLength = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

      if(AIBAttributeLength == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)AIBAttributeLength);
      }
   }
   else
      AIBAttributeLength = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (AIBAttributeLength != NULL))
   {
      AIBAttributeValue = AllocateBufferListEntry(&qsBufferList, (1*(*AIBAttributeLength)));

      if(AIBAttributeValue == NULL)
         qsResult = ssAllocationError;
   }
   else
      AIBAttributeValue= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);

      qsOutputLength = (4 + (AIBAttributeLength == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

      if((AIBAttributeLength != NULL) && (AIBAttributeValue != NULL))
         qsOutputLength = qsOutputLength + ((*AIBAttributeLength)*(1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_APS_FILE_ID, QAPI_ZB_APSME_GET_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)AIBAttributeLength);
         if(qsResult == ssSuccess)
         {
            qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)AIBAttributeLength);
         }

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)AIBAttributeValue);
         if((qsResult == ssSuccess) && (AIBAttributeLength != NULL))
         {
            qsResult = PackedWrite_Array(qsOutputBuffer, (void *)AIBAttributeValue, 1, *AIBAttributeLength);

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

SerStatus_t Mnl_Handle_qapi_ZB_APSME_Set_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_ZB_Handle_t ZB_Handle;
   qapi_ZB_AIB_Attribute_ID_t AIBAttribute;
   uint8_t AIBAttributeIndex;
   uint16_t AIBAttributeLength;
   void *AIBAttributeValue = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ZB_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&AIBAttribute);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AIBAttributeIndex);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&AIBAttributeLength);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      AIBAttributeValue = AllocateBufferListEntry(&qsBufferList, (1*(AIBAttributeLength)));

      if(AIBAttributeValue == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)AIBAttributeValue, 1, AIBAttributeLength);
      }
   }
   else
      AIBAttributeValue = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_APS_FILE_ID, QAPI_ZB_APSME_SET_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_ZB_APS_Create_Test_Endpoint(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   void              *TestEndpoint;

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_ZB_Handle_t ZB_Handle;
   uint16_t ProfileID;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ZB_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&ProfileID);

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_ZB_APS_Create_Test_Endpoint(ZB_Handle, &TestEndpoint, ProfileID);

      qsOutputLength = 8;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_APS_FILE_ID, QAPI_ZB_APS_CREATE_TEST_ENDPOINT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)TestEndpoint);
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_ZB_APS_Test_Endpoint_Data_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_ZB_Handle_t ZB_Handle;
   void *TestEndpoint = NULL;
   qapi_ZB_APSDE_Data_Request_t *RequestData = NULL;
   uint16_t RspClusterID;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ZB_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&RspClusterID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      TestEndpoint = AllocateBufferListEntry(&qsBufferList, 4);

      if(TestEndpoint == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)TestEndpoint);
      }
   }
   else
      TestEndpoint = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      RequestData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_APSDE_Data_Request_t));

      if(RequestData == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_ZB_APSDE_Data_Request_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_APSDE_Data_Request_t*)RequestData);
      }
   }
   else
      RequestData = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, RequestData, RspClusterID);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_APS_FILE_ID, QAPI_ZB_APS_TEST_ENDPOINT_DATA_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}
