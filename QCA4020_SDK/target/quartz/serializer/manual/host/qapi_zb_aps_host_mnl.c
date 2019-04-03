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
#include "qapi_zb.h"
#include "qapi_zb_aps_common.h"
#include "qapi_zb_aps_host_mnl.h"
#include "qapi_zb_aps_host_cb.h"
#include "qapi_zb_common.h"

qapi_Status_t Mnl_qapi_ZB_APSME_Get_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_AIB_Attribute_ID_t AIBAttribute, uint8_t AIBAttributeIndex, uint16_t *AIBAttributeLength, void *AIBAttributeValue)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (9 + CalcPackedSize_16((uint16_t *)AIBAttributeLength) + (QS_POINTER_HEADER_SIZE * 2));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_ZB, QAPI_ZB_APS_FILE_ID, QAPI_ZB_APSME_GET_REQUEST_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_int(&qsInputBuffer, (int *)&AIBAttribute);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_8(&qsInputBuffer, (uint8_t *)&AIBAttributeIndex);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)AIBAttributeLength);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_16(&qsInputBuffer, (uint16_t *)AIBAttributeLength);
      }

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)AIBAttributeValue);

      if(qsResult == ssSuccess)
      {
         /* Send the command. */
         if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
         {
            if(qsOutputBuffer.Start != NULL)
            {
               /* Unpack returned values. */
               if(qsResult == ssSuccess)
                  qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)&qsRetVal);

               if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);
               if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
               {
                  qsResult = PackedRead_16(&qsOutputBuffer, &qsBufferList, (uint16_t *)AIBAttributeLength);
               }
               else
                  AIBAttributeLength = NULL;

               if(qsResult == ssSuccess)
                  qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);
               if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (AIBAttributeLength != NULL))
               {
                  qsResult = PackedRead_Array(&qsOutputBuffer, &qsBufferList, (void *)AIBAttributeValue, 1, *AIBAttributeLength);
               }
               else
                  AIBAttributeValue = NULL;

               /* Set the return value to error if necessary. */
               if(qsResult != ssSuccess)
               {
                  qsRetVal = QAPI_ERROR;
               }
            }
            else
            {
               qsRetVal = QAPI_ERROR;
            }

            /* Free the output buffer. */
            FreePackedBuffer(&qsOutputBuffer);
         }
         else
         {
            qsRetVal = QAPI_ERROR;
         }
      }
      else
      {
         qsRetVal = QAPI_ERROR;
      }

      /* Free the input buffer. */
      FreePackedBuffer(&qsInputBuffer);
   }
   else
   {
      qsRetVal = QAPI_ERR_NO_MEMORY;
   }

   FreeBufferList(&qsBufferList);

   return(qsRetVal);
}

qapi_Status_t Mnl_qapi_ZB_APSME_Set_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, qapi_ZB_AIB_Attribute_ID_t AIBAttribute, uint8_t AIBAttributeIndex, uint16_t AIBAttributeLength, const void *AIBAttributeValue)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (11 + (QS_POINTER_HEADER_SIZE * 1));

   qsSize = qsSize + ((AIBAttributeLength)*(1));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_ZB, QAPI_ZB_APS_FILE_ID, QAPI_ZB_APSME_SET_REQUEST_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_int(&qsInputBuffer, (int *)&AIBAttribute);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_8(&qsInputBuffer, (uint8_t *)&AIBAttributeIndex);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_16(&qsInputBuffer, (uint16_t *)&AIBAttributeLength);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)AIBAttributeValue);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void *)AIBAttributeValue, 1, AIBAttributeLength);

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
                  qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)&qsRetVal);

               /* Set the return value to error if necessary. */
               if(qsResult != ssSuccess)
               {
                  qsRetVal = QAPI_ERROR;
               }
            }
            else
            {
               qsRetVal = QAPI_ERROR;
            }

            /* Free the output buffer. */
            FreePackedBuffer(&qsOutputBuffer);
         }
         else
         {
            qsRetVal = QAPI_ERROR;
         }
      }
      else
      {
         qsRetVal = QAPI_ERROR;
      }

      /* Free the input buffer. */
      FreePackedBuffer(&qsInputBuffer);
   }
   else
   {
      qsRetVal = QAPI_ERR_NO_MEMORY;
   }

   FreeBufferList(&qsBufferList);

   return(qsRetVal);
}

qapi_Status_t Mnl_qapi_ZB_APS_Create_Test_Endpoint(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, void **TestEndpoint, uint16_t ProfileID)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = 6;

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_ZB, QAPI_ZB_APS_FILE_ID, QAPI_ZB_APS_CREATE_TEST_ENDPOINT_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_16(&qsInputBuffer, (uint16_t *)&ProfileID);

      if(qsResult == ssSuccess)
      {
         /* Send the command. */
         if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
         {
            if(qsOutputBuffer.Start != NULL)
            {
               /* Unpack returned values. */
               if(qsResult == ssSuccess)
                  qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)&qsRetVal);

               if(qsResult == ssSuccess)
                  qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)(*TestEndpoint));

               /* Set the return value to error if necessary. */
               if(qsResult != ssSuccess)
               {
                  qsRetVal = QAPI_ERROR;
               }
            }
            else
            {
               qsRetVal = QAPI_ERROR;
            }

            /* Free the output buffer. */
            FreePackedBuffer(&qsOutputBuffer);
         }
         else
         {
            qsRetVal = QAPI_ERROR;
         }
      }
      else
      {
         qsRetVal = QAPI_ERROR;
      }

      /* Free the input buffer. */
      FreePackedBuffer(&qsInputBuffer);
   }
   else
   {
      qsRetVal = QAPI_ERR_NO_MEMORY;
   }

   FreeBufferList(&qsBufferList);

   return(qsRetVal);
}

qapi_Status_t Mnl_qapi_ZB_APS_Test_Endpoint_Data_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, void *TestEndpoint, const qapi_ZB_APSDE_Data_Request_t *RequestData, const uint16_t RspClusterID)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (6 + CalcPackedSize_32((uint32_t *)TestEndpoint) + CalcPackedSize_qapi_ZB_APSDE_Data_Request_t((qapi_ZB_APSDE_Data_Request_t*)RequestData) + (QS_POINTER_HEADER_SIZE * 2));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_ZB, QAPI_ZB_APS_FILE_ID, QAPI_ZB_APS_TEST_ENDPOINT_DATA_REQUEST_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_16(&qsInputBuffer, (uint16_t *)&RspClusterID);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)TestEndpoint);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)TestEndpoint);
      }

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)RequestData);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_qapi_ZB_APSDE_Data_Request_t(&qsInputBuffer, (qapi_ZB_APSDE_Data_Request_t*)RequestData);
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
                  qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)&qsRetVal);

               /* Set the return value to error if necessary. */
               if(qsResult != ssSuccess)
               {
                  qsRetVal = QAPI_ERROR;
               }
            }
            else
            {
               qsRetVal = QAPI_ERROR;
            }

            /* Free the output buffer. */
            FreePackedBuffer(&qsOutputBuffer);
         }
         else
         {
            qsRetVal = QAPI_ERROR;
         }
      }
      else
      {
         qsRetVal = QAPI_ERROR;
      }

      /* Free the input buffer. */
      FreePackedBuffer(&qsInputBuffer);
   }
   else
   {
      qsRetVal = QAPI_ERR_NO_MEMORY;
   }

   FreeBufferList(&qsBufferList);

   return(qsRetVal);
}
