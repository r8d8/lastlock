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
#include "qapi_ble_gls_common.h"
#include "qapi_ble_gls_common_mnl.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_glstypes_common.h"

uint32_t Mnl_CalcPackedSize_qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t(qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t *Structure)
{
   uint32_t qsResult;

   if(Structure == NULL)
   {
      qsResult = 0;
   }
   else
   {
      /* * NOTE * The FilterType field is an operand, NOT a mandatory   */
      /*          field.                                                */
      qsResult = QAPI_BLE_GLS_RECORD_ACCESS_CONTROL_POINT_FORMAT_DATA_T_MIN_PACKED_SIZE - 4;

      /* Determine operands based on the mandatory op code.             */
      switch(Structure->CommandType)
      {
         case QAPI_BLE_GLS_COMMAND_REPORT_STORED_RECORDS_REQUEST_E:
         case QAPI_BLE_GLS_COMMAND_DELETE_STORED_RECORDS_REQUEST_E:
         case QAPI_BLE_GLS_COMMAND_NUMBER_OF_STORED_RECORDS_REQUEST_E:
            /* Intentional fall through.                                */

            /* Determine operands based on the mandatory operator type. */
            switch(Structure->OperatorType)
            {
               case QAPI_BLE_GLS_LESS_THAN_OR_EQUAL_TO_E:
               case QAPI_BLE_GLS_GREATER_THAN_OR_EQUAL_TO_E:
                  /* Intentional fall through.                          */

                  qsResult += CalcPackedSize_int((int *)&Structure->FilterType);

                  /* Determine the operand based on the filter type.    */
                  switch(Structure->FilterType)
                  {
                     case QAPI_BLE_GLS_FILTER_SEQUENCE_NUMBER_E:
                        qsResult += CalcPackedSize_16(&Structure->FilterParameters.SequenceNumber);
                        break;
                     case QAPI_BLE_GLS_FILTER_USER_FACING_TIME_E:
                        qsResult += CalcPackedSize_qapi_BLE_GLS_Date_Time_Data_t(&Structure->FilterParameters.UserFacingTime);
                        break;
                     default:
                        break;
                  }
                  break;
               case QAPI_BLE_GLS_WITHIN_RANGE_OF_E:
                  qsResult += CalcPackedSize_int((int *)&Structure->FilterType);

                  /* Determine the operand based on the filter type.    */
                  switch(Structure->FilterType)
                  {
                     case QAPI_BLE_GLS_FILTER_SEQUENCE_NUMBER_E:
                        qsResult += CalcPackedSize_qapi_BLE_GLS_Sequence_Number_Range_Data_t(&Structure->FilterParameters.SequenceNumberRange);
                        break;
                     case QAPI_BLE_GLS_FILTER_USER_FACING_TIME_E:
                        qsResult += CalcPackedSize_qapi_BLE_GLS_Date_Time_Range_Data_t(&Structure->FilterParameters.UserFacingTimeRange);
                        break;
                     default:
                        break;
                  }
                  break;
               default:
                  /* No operand.                                        */
                  break;
            }
            break;
         case QAPI_BLE_GLS_COMMAND_ABORT_OPERATION_REQUEST_E:
         default:
            /* Intentional fall through.                                */

            /* No operand.                                              */
            break;
      }
   }

   return(qsResult);
}

SerStatus_t Mnl_PackedWrite_qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t(PackedBuffer_t *Buffer, qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t(Structure))
   {
      if(Structure != NULL)
      {
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(Buffer, (int *)&Structure->CommandType);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(Buffer, (int *)&Structure->OperatorType);

         if(qsResult == ssSuccess)
         {
            /* Determine operands based on the mandatory op code.       */
            switch(Structure->CommandType)
            {
               case QAPI_BLE_GLS_COMMAND_REPORT_STORED_RECORDS_REQUEST_E:
               case QAPI_BLE_GLS_COMMAND_DELETE_STORED_RECORDS_REQUEST_E:
               case QAPI_BLE_GLS_COMMAND_NUMBER_OF_STORED_RECORDS_REQUEST_E:
                  /* Intentional fall through.                          */

                  /* Determine operands based on the mandatory operator */
                  /* type.                                              */
                  switch(Structure->OperatorType)
                  {
                     case QAPI_BLE_GLS_LESS_THAN_OR_EQUAL_TO_E:
                     case QAPI_BLE_GLS_GREATER_THAN_OR_EQUAL_TO_E:
                        /* Intentional fall through.                    */

                        qsResult = PackedWrite_int(Buffer, (int *)&Structure->FilterType);

                        if(qsResult == ssSuccess)
                        {
                           /* Determine the operand based on the filter */
                           /* type.                                     */
                           switch(Structure->FilterType)
                           {
                              case QAPI_BLE_GLS_FILTER_SEQUENCE_NUMBER_E:
                                 qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->FilterParameters.SequenceNumber);
                                 break;
                              case QAPI_BLE_GLS_FILTER_USER_FACING_TIME_E:
                                 qsResult = PackedWrite_qapi_BLE_GLS_Date_Time_Data_t(Buffer, (qapi_BLE_GLS_Date_Time_Data_t*)&Structure->FilterParameters.UserFacingTime);
                                 break;
                              default:
                                 break;
                           }
                        }
                        break;
                     case QAPI_BLE_GLS_WITHIN_RANGE_OF_E:
                        qsResult = PackedWrite_int(Buffer, (int *)&Structure->FilterType);

                        if(qsResult == ssSuccess)
                        {
                           /* Determine the operand based on the filter */
                           /* type.                                     */
                           switch(Structure->FilterType)
                           {
                              case QAPI_BLE_GLS_FILTER_SEQUENCE_NUMBER_E:
                                 qsResult = PackedWrite_qapi_BLE_GLS_Sequence_Number_Range_Data_t(Buffer, (qapi_BLE_GLS_Sequence_Number_Range_Data_t*)&Structure->FilterParameters.SequenceNumberRange);
                                 break;
                              case QAPI_BLE_GLS_FILTER_USER_FACING_TIME_E:
                                 qsResult = PackedWrite_qapi_BLE_GLS_Date_Time_Range_Data_t(Buffer, (qapi_BLE_GLS_Date_Time_Range_Data_t*)&Structure->FilterParameters.UserFacingTimeRange);
                                 break;
                              default:
                                 break;
                           }
                        }
                        break;
                     default:
                        /* No operand.                                        */
                        break;
                  }
                  break;
               case QAPI_BLE_GLS_COMMAND_ABORT_OPERATION_REQUEST_E:
               default:
                  /* Intentional fall through.                                */

                  /* No operand.                                              */
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

SerStatus_t Mnl_PackedRead_qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   /* * NOTE * The FilterType field is an operand, NOT a mandatory   */
   /*          field.                                                */
   if(Buffer->Remaining >= (QAPI_BLE_GLS_RECORD_ACCESS_CONTROL_POINT_FORMAT_DATA_T_MIN_PACKED_SIZE - 4))
   {
      if(qsResult == ssSuccess)
         qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->CommandType);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->OperatorType);

      if(qsResult == ssSuccess)
      {
         /* Determine operands based on the mandatory op code.          */
         switch(Structure->CommandType)
         {
            case QAPI_BLE_GLS_COMMAND_REPORT_STORED_RECORDS_REQUEST_E:
            case QAPI_BLE_GLS_COMMAND_DELETE_STORED_RECORDS_REQUEST_E:
            case QAPI_BLE_GLS_COMMAND_NUMBER_OF_STORED_RECORDS_REQUEST_E:
               /* Intentional fall through.                             */

               /* Determine operands based on the mandatory operator    */
               /* type.                                                 */
               switch(Structure->OperatorType)
               {
                  case QAPI_BLE_GLS_LESS_THAN_OR_EQUAL_TO_E:
                  case QAPI_BLE_GLS_GREATER_THAN_OR_EQUAL_TO_E:
                     /* Intentional fall through.                       */

                     qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->FilterType);

                     if(qsResult == ssSuccess)
                     {
                        /* Determine the operand based on the filter    */
                        /* type.                                        */
                        switch(Structure->FilterType)
                        {
                           case QAPI_BLE_GLS_FILTER_SEQUENCE_NUMBER_E:
                              qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->FilterParameters.SequenceNumber);
                              break;
                           case QAPI_BLE_GLS_FILTER_USER_FACING_TIME_E:
                              qsResult = PackedRead_qapi_BLE_GLS_Date_Time_Data_t(Buffer, BufferList, (qapi_BLE_GLS_Date_Time_Data_t*)&Structure->FilterParameters.UserFacingTime);
                              break;
                           default:
                              break;
                        }
                     }
                     break;
                  case QAPI_BLE_GLS_WITHIN_RANGE_OF_E:
                     qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->FilterType);

                     if(qsResult == ssSuccess)
                     {
                        /* Determine the operand based on the filter    */
                        /* type.                                        */
                        switch(Structure->FilterType)
                        {
                           case QAPI_BLE_GLS_FILTER_SEQUENCE_NUMBER_E:
                              qsResult = PackedRead_qapi_BLE_GLS_Sequence_Number_Range_Data_t(Buffer, BufferList, (qapi_BLE_GLS_Sequence_Number_Range_Data_t*)&Structure->FilterParameters.SequenceNumberRange);
                              break;
                           case QAPI_BLE_GLS_FILTER_USER_FACING_TIME_E:
                              qsResult = PackedRead_qapi_BLE_GLS_Date_Time_Range_Data_t(Buffer, BufferList, (qapi_BLE_GLS_Date_Time_Range_Data_t*)&Structure->FilterParameters.UserFacingTimeRange);
                              break;
                           default:
                              break;
                        }
                     }
                     break;
                  default:
                     /* No operand.                                     */
                     break;
               }
               break;
            case QAPI_BLE_GLS_COMMAND_ABORT_OPERATION_REQUEST_E:
            default:
               /* Intentional fall through.                             */

               /* No operand.                                           */
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
