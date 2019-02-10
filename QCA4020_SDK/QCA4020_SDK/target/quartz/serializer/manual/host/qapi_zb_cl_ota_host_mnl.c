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
#include "qapi_zb_cl_ota_common.h"
#include "qapi_zb_cl_ota_host_mnl.h"
#include "qapi_zb_cl_ota_host_cb.h"
#include "qapi_zb_cl_common.h"

qapi_Status_t Mnl_qapi_ZB_CL_OTA_Client_Discover(uint8_t TargetID, qapi_ZB_Cluster_t Cluster, qapi_ZB_Addr_Mode_t DstAddrMode, qapi_ZB_Addr_t DstAddress)
{
   PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
   BufferListEntry_t *qsBufferList = NULL;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize = 0;

   /* Return value. */
   qapi_Status_t qsRetVal = 0;

   /* Calculate size of packed function arguments. */
   qsSize = 8;

   switch(DstAddrMode)
   {
      case QAPI_ZB_ADDRESS_MODE_GROUP_ADDRESS_E:
         qsSize += CalcPackedSize_16((uint16_t *)&DstAddress.ShortAddress);
         break;
      case QAPI_ZB_ADDRESS_MODE_SHORT_ADDRESS_E:
         qsSize += CalcPackedSize_16((uint16_t *)&DstAddress.ShortAddress);
         break;
      case QAPI_ZB_ADDRESS_MODE_EXTENDED_ADDRESS_E:
         qsSize += CalcPackedSize_64((uint64_t *)&DstAddress.ExtendedAddress);
         break;
      default:
         /* Prevent compiler warnings.                                  */
         break;
   }

   if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_CLIENT_DISCOVER_FUNCTION_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&Cluster);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_int(&qsInputBuffer, (int *)&DstAddrMode);

      if(qsResult == ssSuccess)
      {
         switch(DstAddrMode)
         {
            case QAPI_ZB_ADDRESS_MODE_GROUP_ADDRESS_E:
               qsSize += PackedWrite_16(&qsInputBuffer, (uint16_t *)&DstAddress.ShortAddress);
               break;
            case QAPI_ZB_ADDRESS_MODE_SHORT_ADDRESS_E:
               qsSize += PackedWrite_16(&qsInputBuffer, (uint16_t *)&DstAddress.ShortAddress);
               break;
            case QAPI_ZB_ADDRESS_MODE_EXTENDED_ADDRESS_E:
               qsSize += PackedWrite_64(&qsInputBuffer, (uint64_t *)&DstAddress.ExtendedAddress);
               break;
            default:
               /* Prevent compiler warnings.                            */
            break;
         }
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
