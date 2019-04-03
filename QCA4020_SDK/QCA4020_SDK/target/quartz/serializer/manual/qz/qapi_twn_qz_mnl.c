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
#include "qapi_twn_common.h"
#include "qapi_twn_qz_mnl.h"
#include "qapi_twn_qz_cb.h"
#include "qapi_twn_hosted_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_TWN_IPv6_Remove_Unicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_TWN_Handle_t TWN_Handle;
   qapi_TWN_IPv6_Address_t *Address = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Address = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_IPv6_Address_t));

      if(Address == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Address->Byte, sizeof(uint8_t), 16);
      }
   }
   else
      Address = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, Address);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_IPV6_REMOVE_UNICAST_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Mnl_Handle_qapi_TWN_IPv6_Subscribe_Multicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_TWN_Handle_t TWN_Handle;
   qapi_TWN_IPv6_Address_t *Address = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Address = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_IPv6_Address_t));

      if(Address == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Address->Byte, sizeof(uint8_t), 16);
      }
   }
   else
      Address = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, Address);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_IPV6_SUBSCRIBE_MULTICAST_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Mnl_Handle_qapi_TWN_IPv6_Unsubscribe_Multicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_TWN_Handle_t TWN_Handle;
   qapi_TWN_IPv6_Address_t *Address = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Address = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_IPv6_Address_t));

      if(Address == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Address->Byte, sizeof(uint8_t), 16);
      }
   }
   else
      Address = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, Address);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_IPV6_UNSUBSCRIBE_MULTICAST_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Mnl_Handle_qapi_TWN_Start_Border_Agent(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
   int AddressFamily;
   char *DisplayName = NULL;
   char *Hostname = NULL;
   char *Interface = NULL;
   uint32_t CallbackParameter;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&AddressFamily);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      DisplayName = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

      if(DisplayName == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)DisplayName, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
      }
   }
   else
      DisplayName = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Hostname = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

      if(Hostname == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Hostname, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
      }
   }
   else
      Hostname = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Interface = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

      if(Interface == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Interface, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
      }
   }
   else
      Interface = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_TWN_Start_Border_Agent(TWN_Handle, AddressFamily, DisplayName, Hostname, Interface);

      if(qsRetVal == QAPI_OK)
      {
         /* Register the event callback so the encrypted UDP data can
            be transmitted via the serializer to the host.*/
         qapi_TWN_Hosted_Register_Event_Callback(TWN_Handle, QZ_qapi_TWN_Hosted_Event_Callback_t_Handler, CallbackParameter);
      }

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_START_BORDER_AGENT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Mnl_Handle_qapi_TWN_Stop_Border_Agent(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_TWN_Stop_Border_Agent(TWN_Handle);

      if(qsRetVal == QAPI_OK)
      {
         /* Un-Register the event callback.*/
         qapi_TWN_Hosted_UnRegister_Event_Callback(TWN_Handle);
      }

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_STOP_BORDER_AGENT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Mnl_Handle_qapi_TWN_Commissioner_Send_PanId_Query(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_TWN_Handle_t TWN_Handle;
   uint16_t PanId;
   uint32_t ChannelMask;
   qapi_TWN_IPv6_Address_t *Address = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&PanId);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ChannelMask);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Address = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_IPv6_Address_t));

      if(Address == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Address->Byte, sizeof(uint8_t), 16);
      }
   }
   else
      Address = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, Address);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_SEND_PANID_QUERY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Mnl_Handle_qapi_TWN_Commissioner_Send_Mgmt_Active_Get(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   qapi_TWN_Handle_t TWN_Handle;
   qapi_TWN_IPv6_Address_t *Address = NULL;
   uint8_t *TlvBuffer = NULL;
   uint8_t Length;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Length);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Address = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_IPv6_Address_t));

      if(Address == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Address->Byte, sizeof(uint8_t), 16);
      }
   }
   else
      Address = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);
   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      TlvBuffer = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

      if(TlvBuffer == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)TlvBuffer, sizeof(uint8_t), Length);
      }
   }
   else
      TlvBuffer = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, Address, TlvBuffer, Length);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_SEND_MGMT_ACTIVE_GET_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

