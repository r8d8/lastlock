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
#include "qapi_twn.h"
#include "qapi_twn_common.h"
#include "qapi_twn_host_mnl.h"
#include "qapi_twn_host_cb.h"
#include "qapi_twn_hosted.h"

qapi_Status_t _qapi_TWN_Hosted_Start_Border_Agent(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, int AddressFamily, const char *DisplayName, const char *HostName, const char *Interface);
qapi_Status_t _qapi_TWN_Hosted_Stop_Border_Agent(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle);

qapi_Status_t Mnl_qapi_TWN_IPv6_Remove_Unicast_Address(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_IPv6_Address_t *Address)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (4 + sizeof(qapi_TWN_IPv6_Address_t) + (QS_POINTER_HEADER_SIZE * 1));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_IPV6_REMOVE_UNICAST_ADDRESS_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&TWN_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Address);

      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void*)Address->Byte, sizeof(uint8_t), 16);
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

qapi_Status_t Mnl_qapi_TWN_IPv6_Subscribe_Multicast_Address(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_IPv6_Address_t *Address)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (4 + sizeof(qapi_TWN_IPv6_Address_t) + (QS_POINTER_HEADER_SIZE * 1));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_IPV6_SUBSCRIBE_MULTICAST_ADDRESS_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&TWN_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Address);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void*)Address->Byte, sizeof(uint8_t), 16);
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

qapi_Status_t Mnl_qapi_TWN_IPv6_Unsubscribe_Multicast_Address(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_IPv6_Address_t *Address)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (4 + sizeof(qapi_TWN_IPv6_Address_t) + (QS_POINTER_HEADER_SIZE * 1));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_IPV6_UNSUBSCRIBE_MULTICAST_ADDRESS_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&TWN_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Address);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void*)Address->Byte, sizeof(uint8_t), 16);
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

qapi_Status_t Mnl_qapi_TWN_Start_Border_Agent(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, int AddressFamily, const char *DisplayName, const char *Hostname, const char *Interface)
{
   /* Simply call the hosted function. */
   return(_qapi_TWN_Hosted_Start_Border_Agent(TargetID, TWN_Handle, AddressFamily, DisplayName, Hostname, Interface));
}

qapi_Status_t Mnl_qapi_TWN_Stop_Border_Agent(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle)
{
   /* Simply call the hosted function. */
   return(_qapi_TWN_Hosted_Stop_Border_Agent(TargetID, TWN_Handle));
}

qapi_Status_t Mnl_qapi_TWN_Commissioner_Send_PanId_Query(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, uint16_t PanId, uint32_t ChannelMask, const qapi_TWN_IPv6_Address_t *Address)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (10 + sizeof(qapi_TWN_IPv6_Address_t) + (QS_POINTER_HEADER_SIZE * 1));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_SEND_PANID_QUERY_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&TWN_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_16(&qsInputBuffer, (uint16_t *)&PanId);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ChannelMask);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Address);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void*)Address->Byte, sizeof(uint8_t), 16);
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

qapi_Status_t Mnl_qapi_TWN_Commissioner_Send_Mgmt_Active_Get(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, const qapi_TWN_IPv6_Address_t *Address, const uint8_t *TlvBuffer, uint8_t Length)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = (5 + sizeof(qapi_TWN_IPv6_Address_t) + (QS_POINTER_HEADER_SIZE * 2));

   qsSize = qsSize + ((Length)*(1));

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_SEND_MGMT_ACTIVE_GET_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&TWN_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_8(&qsInputBuffer, (uint8_t *)&Length);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Address);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void*)Address->Byte, sizeof(uint8_t), 16);
      }

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)TlvBuffer);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_Array(&qsInputBuffer, (void *)TlvBuffer, sizeof(uint8_t), Length);

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

