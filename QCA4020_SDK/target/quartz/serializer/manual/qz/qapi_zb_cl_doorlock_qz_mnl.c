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
#include "qapi_zb_cl_doorlock_common.h"
#include "qapi_zb_cl_doorlock_qz_mnl.h"
#include "qapi_zb_cl_doorlock_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_ZB_CL_DoorLock_Server_Get_PIN_Code(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_ZB_Cluster_t Cluster;
   qapi_ZB_CL_DoorLock_PIN_t *PIN = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      PIN = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_DoorLock_PIN_t));

      if(PIN == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_ZB_CL_DoorLock_PIN_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_DoorLock_PIN_t *)PIN);
      }
   }
   else
      PIN = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_ZB_CL_DoorLock_Server_Get_PIN_Code(Cluster, PIN);

      qsOutputLength = (4 + (CalcPackedSize_qapi_ZB_CL_DoorLock_PIN_t((qapi_ZB_CL_DoorLock_PIN_t *)PIN)) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_DOORLOCK_FILE_ID, QAPI_ZB_CL_DOORLOCK_SERVER_GET_PIN_CODE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)PIN);

         if((qsResult == ssSuccess) && (PIN != NULL))
         {
            qsResult = PackedWrite_qapi_ZB_CL_DoorLock_PIN_t(qsOutputBuffer, (qapi_ZB_CL_DoorLock_PIN_t *)PIN);
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
