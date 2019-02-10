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
#include "qapi_ble_cgms_common.h"
#include "qapi_ble_cgms_common_mnl.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_cgmstypes_common.h"

uint32_t Mnl_CalcPackedSize_qapi_BLE_CGMS_RACP_Format_Data_t(qapi_BLE_CGMS_RACP_Format_Data_t *Structure)
{
   uint32_t qsResult;

   if(Structure == NULL)
   {
      qsResult = 0;
   }
   else
   {
      /* * NOTE * The FilterType field is an operand (Not a mandatory   */
      /*          field).                                               */
      qsResult = QAPI_BLE_CGMS_RACP_FORMAT_DATA_T_MIN_PACKED_SIZE - 1;

      /* Determine operands based on the mandatory op code.             */
      switch(Structure->CommandType)
      {
         case QAPI_BLE_CGMS_COMMAND_REPORT_STORED_RECORDS_REQUEST_E:
         case QAPI_BLE_CGMS_COMMAND_DELETE_STORED_RECORDS_REQUEST_E:
         case QAPI_BLE_CGMS_COMMAND_NUMBER_OF_STORED_RECORDS_REQUEST_E:
            /* Intentional fall through.                                */

            /* Determine operands based on the mandatory operator type. */
            switch(Structure->OperatorType)
            {
               case QAPI_BLE_CGMS_LESS_THAN_OR_EQUAL_TO_E:
                  qsResult += CalcPackedSize_8(&Structure->FilterType);
                  qsResult += CalcPackedSize_16(&Structure->FilterParameters.TimeOffset);
                  break;
               case QAPI_BLE_CGMS_GREATER_THAN_OR_EQUAL_TO_E:
                  qsResult += CalcPackedSize_8(&Structure->FilterType);
                  qsResult += CalcPackedSize_16(&Structure->FilterParameters.TimeOffset);
                  break;
               case QAPI_BLE_CGMS_WITHIN_RANGE_OF_E:
                  qsResult += CalcPackedSize_8(&Structure->FilterType);
                  qsResult += CalcPackedSize_qapi_BLE_CGMS_Time_Offset_Range_Data_t(&Structure->FilterParameters.TimeOffsetRange);
                  break;
               default:
                  /* No operand.                                        */
                  break;
            }
            break;
         case QAPI_BLE_CGMS_COMMAND_ABORT_OPERATION_REQUEST_E:
         default:
            /* Intentional fall through.                                */

            /* No operand.                                              */
            break;
      }
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedWrite_qapi_BLE_CGMS_RACP_Format_Data_t(PackedBuffer_t *Buffer, qapi_BLE_CGMS_RACP_Format_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_CGMS_RACP_Format_Data_t(Structure))
   {
      if(Structure != NULL)
      {
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->CommandType);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->OperatorType);

         if(qsResult == ssSuccess)
         {
            switch(Structure->OperatorType)
            {
               case QAPI_BLE_CGMS_RACP_OPERATOR_LESS_THAN_OR_EQUAL_TO:
                  qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->FilterType);

                  if(qsResult == ssSuccess)
                  {
                     qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->FilterParameters.TimeOffset);
                  }
                  break;
               case QAPI_BLE_CGMS_RACP_OPERATOR_GREATER_THAN_OR_EQUAL_TO:
                  qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->FilterType);

                  if(qsResult == ssSuccess)
                  {
                     qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->FilterParameters.TimeOffset);
                  }
                  break;
               case QAPI_BLE_CGMS_RACP_OPERATOR_WITHIN_RANGE_OF:
                  qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->FilterType);

                  if(qsResult == ssSuccess)
                  {
                     qsResult = PackedWrite_qapi_BLE_CGMS_Time_Offset_Range_Data_t(Buffer, (qapi_BLE_CGMS_Time_Offset_Range_Data_t *)&Structure->FilterParameters.TimeOffsetRange);
                  }
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

SerStatus_t Mnl_PackedRead_qapi_BLE_CGMS_RACP_Format_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_CGMS_RACP_Format_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   /* * NOTE * The FilterType field is an operand (Not a mandatory   */
   /*          field).                                               */
   if(Buffer->Remaining >= (QAPI_BLE_CGMS_RACP_FORMAT_DATA_T_MIN_PACKED_SIZE - 1))
   {
      if(qsResult == ssSuccess)
         qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->CommandType);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->OperatorType);

      if(qsResult == ssSuccess)
      {
         switch(Structure->OperatorType)
         {
            case QAPI_BLE_CGMS_RACP_OPERATOR_LESS_THAN_OR_EQUAL_TO:
               qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->FilterType);

               if(qsResult == ssSuccess)
               {
                  qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->FilterParameters.TimeOffset);
               }
               break;
            case QAPI_BLE_CGMS_RACP_OPERATOR_GREATER_THAN_OR_EQUAL_TO:
               qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->FilterType);

               if(qsResult == ssSuccess)
               {
                  qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->FilterParameters.TimeOffset);
               }
               break;
            case QAPI_BLE_CGMS_RACP_OPERATOR_WITHIN_RANGE_OF:
               qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->FilterType);

               if(qsResult == ssSuccess)
               {
                  qsResult = PackedRead_qapi_BLE_CGMS_Time_Offset_Range_Data_t(Buffer, BufferList, (qapi_BLE_CGMS_Time_Offset_Range_Data_t *)&Structure->FilterParameters.TimeOffsetRange);
               }
               break;
         }
      }
   }
   else
   {
     qsResult = ssInvalidLength;
   }

   return(qsResult);
}
