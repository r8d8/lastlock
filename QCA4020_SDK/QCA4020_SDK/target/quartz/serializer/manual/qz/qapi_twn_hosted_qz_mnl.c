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
#include "qapi_twn.h"
#include "qapi_twn_hosted.h"
#include "qapi_twn_hosted_common.h"
#include "qapi_twn_hosted_qz_mnl.h"
#include "qapi_twn_hosted_qz_cb.h"
#include "qapi_socket.h"

SerStatus_t Mnl_Handle_qapi_TWN_Hosted_Start_Border_Agent(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   /* This function will NOT be called by the serializer. Instead the
      Mnl_qapi_TWN_Hosted_Start_Border_Agent() function will be called.*/
   return(ssFailure);
}

SerStatus_t Mnl_Handle_qapi_TWN_Hosted_Stop_Border_Agent(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   /* This function will NOT be called by the serializer. Instead the
      Mnl_qapi_TWN_Hosted_Stop_Border_Agent() function will be called.*/
   return(ssFailure);
}

SerStatus_t Mnl_Handle_qapi_TWN_Hosted_Receive_UDP_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   qapi_TWN_Handle_t TWN_Handle;
   qapi_TWN_Hosted_Socket_Info_t SocketInfo;
   uint16_t Length;
   uint8_t *Buffer = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

   if(qsResult == ssSuccess)
   {
      /* If we do not read an ipv6 address, then the buffer needs
         to be initialized.*/
      QSOSAL_MemInitialize(&SocketInfo, 0, sizeof(SocketInfo));
      qsResult = PackedRead_qapi_TWN_Hosted_Socket_Info_t(&qsInputBuffer, &qsBufferList, &SocketInfo);
   }

   if(qsResult == ssSuccess)
      qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Length);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Buffer = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

      if(Buffer == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Buffer, sizeof(uint8_t), Length);
      }
   }
   else
      Buffer = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_TWN_Hosted_Receive_UDP_Data(TWN_Handle, &SocketInfo, Length, Buffer);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_HOSTED_FILE_ID, QAPI_TWN_HOSTED_RECEIVE_UDP_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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
