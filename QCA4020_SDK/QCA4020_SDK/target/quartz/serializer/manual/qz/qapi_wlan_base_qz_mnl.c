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
#include "qapi_wlan.h"
#include "qapi_wlan_base_common.h"
#include "qapi_wlan_base_qz_mnl.h"
#include "qapi_wlan_base_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_WLAN_Set_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   uint8_t device_ID;
   void *application_Context = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      application_Context = AllocateBufferListEntry(&qsBufferList, 4);

      if(application_Context == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)application_Context, 1, 4);
      }
   }
   else
      application_Context = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_WLAN_Set_Callback(device_ID, QZ_qapi_WLAN_Callback_t_Handler, application_Context);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_SET_CALLBACK_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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
