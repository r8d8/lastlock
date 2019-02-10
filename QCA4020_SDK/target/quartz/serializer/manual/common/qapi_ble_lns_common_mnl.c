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
#include "qapi_ble.h"
#include "qsCommon.h"
#include "qsPack.h"
#include "qapi_ble_lns_common.h"
#include "qapi_ble_lns_common_mnl.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_lnstypes_common.h"

uint32_t Mnl_CalcPackedSize_qapi_BLE_LNS_LN_Control_Point_Response_Data_t(qapi_BLE_LNS_LN_Control_Point_Response_Data_t *Structure)
{
   uint32_t qsResult;

   if(Structure == NULL)
   {
      qsResult = 0;
   }
   else
   {
      qsResult = QAPI_BLE_LNS_LN_CONTROL_POINT_RESPONSE_DATA_T_MIN_PACKED_SIZE;

      switch(Structure->RequestOpCode)
      {
         case QAPI_BLE_LNC_REQUEST_NUMBER_OF_ROUTES_E:
            qsResult += CalcPackedSize_16((uint16_t *)&Structure->ResponseParameter.NumberOfRoutes);
            break;
         case QAPI_BLE_LNC_REQUEST_NAME_OF_ROUTE_E:
            if(Structure->ResponseParameter.NameOfRoute != NULL)
               qsResult += (strlen(Structure->ResponseParameter.NameOfRoute) + 1);
            break;
         default:
            break;
      }
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedWrite_qapi_BLE_LNS_LN_Control_Point_Response_Data_t(PackedBuffer_t *Buffer, qapi_BLE_LNS_LN_Control_Point_Response_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_LNS_LN_Control_Point_Response_Data_t(Structure))
   {
      if(Structure != NULL)
      {
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->ResponseCodeOpCode);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(Buffer, (int *)&Structure->RequestOpCode);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(Buffer, (int *)&Structure->ResponseCode);

         if(qsResult == ssSuccess)
         {
            switch(Structure->RequestOpCode)
            {
               case QAPI_BLE_LNC_REQUEST_NUMBER_OF_ROUTES_E:
                  qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->ResponseParameter.NumberOfRoutes);
                  break;
               case QAPI_BLE_LNC_REQUEST_NAME_OF_ROUTE_E:
                  qsResult = PackedWrite_Array(Buffer, Structure->ResponseParameter.NameOfRoute, 1, (strlen(Structure->ResponseParameter.NameOfRoute) + 1));
                  break;
               default:
                  break;
            }
         }
      }
   }
   else
   {
     qsResult = ssInvalidLength;
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedRead_qapi_BLE_LNS_LN_Control_Point_Response_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_LNS_LN_Control_Point_Response_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;
   Boolean_t   qsPointerValid = FALSE;
   uint32_t    Length;

   UNUSED(qsPointerValid);

   if(Buffer->Remaining >= QAPI_BLE_LNS_LN_CONTROL_POINT_RESPONSE_DATA_T_MIN_PACKED_SIZE)
   {
      if(qsResult == ssSuccess)
         qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->ResponseCodeOpCode);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->RequestOpCode);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->ResponseCode);

      if(qsResult == ssSuccess)
      {
         switch(Structure->RequestOpCode)
         {
            case QAPI_BLE_LNC_REQUEST_NUMBER_OF_ROUTES_E:
               qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->ResponseParameter.NumberOfRoutes);
               break;
            case QAPI_BLE_LNC_REQUEST_NAME_OF_ROUTE_E:
               /* Veirfy the buffer. */
               if(Buffer->CurrentPos != NULL)
               {
                  /* Store the length of the string. */
                  Length = (strlen((char *)Buffer->CurrentPos) + 1);

                  if(Buffer->Remaining >= Length)
                  {
                     /* Allocate memory for the string.*/
                     Structure->ResponseParameter.NameOfRoute = QSOSAL_AllocateMemory(Length);

                     if(Structure->ResponseParameter.NameOfRoute == NULL)
                     {
                        qsResult = ssAllocationError;
                     }
                     else
                     {
                        QSOSAL_StringCopy_S(Structure->ResponseParameter.NameOfRoute, Length, (char *)Buffer->CurrentPos);

                        Buffer->CurrentPos += Length;
                        Buffer->Remaining  -= Length;
                     }
                  }
                  else
                     qsResult = ssFailure;
               }
               else
                  qsResult = ssFailure;
               break;
            default:
               break;
         }
      }
   }

   return(qsResult);
}
