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
#include "qapi_zb_cl_ota_common.h"
#include "qapi_zb_cl_ota_qz_cb_mnl.h"
#include "qapi_zb_cl_qz_cb_mnl.h"
#include "q_HERH.h"

void Mnl_QZ_qapi_ZB_CL_OTA_Client_CB_t_Handler(qapi_ZB_Handle_t ZB_Handle, qapi_ZB_Cluster_t Cluster, qapi_ZB_CL_OTA_Client_Event_Data_t *Event_Data, uint32_t CB_Param)
{
   PackedBuffer_t     qsInputBuffer;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize;
   HERH_Handle_t      HERH_Handle;
   uint32_t           DataLength;
   uint8_t           *Data;

   /* Calculate size of packed function arguments. */
   qsSize = (16 + CalcPackedSize_qapi_ZB_CL_OTA_Client_Event_Data_t((qapi_ZB_CL_OTA_Client_Event_Data_t*)Event_Data) + (QS_POINTER_HEADER_SIZE * 1));

   if(AllocatePackedBuffer(NULL, QS_ASYNC_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_CLIENT_CB_T_CALLBACK_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&Cluster);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&CB_Param);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Event_Data);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_qapi_ZB_CL_OTA_Client_Event_Data_t(&qsInputBuffer, (qapi_ZB_CL_OTA_Client_Event_Data_t*)Event_Data);
      }

      if(qsResult == ssSuccess)
      {
         /* Check if the event is custom get scene or custom set scene or custom
            read attributes or custom write atributes. */
         if((Event_Data->Event_Type == QAPI_ZB_CL_OTA_CLIENT_EVENT_TYPE_ATTR_CUSTOM_READ_E) || (Event_Data->Event_Type == QAPI_ZB_CL_OTA_CLIENT_EVENT_TYPE_ATTR_CUSTOM_WRITE_E))
         {
            /* Initialize a response event. */
            HERH_Handle = HERH_Init_Response();
            if(HERH_Handle != NULL)
            {
               /* Write the handle into buffer. */
               qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&HERH_Handle);
            }
            else
               qsResult = ssFailure;
         }
      }
      else
         HERH_Handle = NULL;

      /* Send the event. */
      if(qsResult == ssSuccess)
         qsResult = SendEvent(&qsInputBuffer);

      if((qsResult == ssSuccess) && (HERH_Handle != NULL))
      {
         /* Wait for the response event. */
         DataLength = 0;
         Data       = NULL;
         if(HERH_Wait_Response(HERH_Handle, HERH_RESPONSE_TIMEOUT, &DataLength, &Data))
         {
            /* Parsing the data. */
            switch(Event_Data->Event_Type)
            {
               case QAPI_ZB_CL_OTA_CLIENT_EVENT_TYPE_ATTR_CUSTOM_READ_E:
                  zb_cl_Parse_HERH_ReadAttr_Rsp(&(Event_Data->Data.Attr_Custom_Read), DataLength, Data);
                  break;

               case QAPI_ZB_CL_OTA_CLIENT_EVENT_TYPE_ATTR_CUSTOM_WRITE_E:
                  zb_cl_Parse_HERH_WriteAttr_Rsp(&(Event_Data->Data.Attr_Custom_Write), DataLength, Data);
                  break;

               default:
                  qsResult = ssUnkownCommand;
                  break;
            }
         }

         /* Clean the response event. */
         HERH_Cleanup_Response(HERH_Handle);
      }
   }
   else
      qsResult = ssAllocationError;
}

void Mnl_QZ_qapi_ZB_CL_OTA_Server_CB_t_Handler(qapi_ZB_Handle_t ZB_Handle, qapi_ZB_Cluster_t Cluster, qapi_ZB_CL_OTA_Server_Event_Data_t *Event_Data, uint32_t CB_Param)
{
   PackedBuffer_t     qsInputBuffer;
   SerStatus_t        qsResult = ssSuccess;
   uint16_t           qsSize;
   HERH_Handle_t      HERH_Handle;
   uint32_t           DataLength;
   uint8_t           *Data;

   /* Calculate size of packed function arguments. */
   qsSize = (16 + CalcPackedSize_qapi_ZB_CL_OTA_Server_Event_Data_t((qapi_ZB_CL_OTA_Server_Event_Data_t*)Event_Data) + (QS_POINTER_HEADER_SIZE * 1));

   if(AllocatePackedBuffer(NULL, QS_ASYNC_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_SERVER_CB_T_CALLBACK_ID, &qsInputBuffer, qsSize))
   {
      /* Write arguments packed. */
      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&Cluster);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&CB_Param);

      if(qsResult == ssSuccess)
         qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Event_Data);
      if(qsResult == ssSuccess)
      {
         qsResult = PackedWrite_qapi_ZB_CL_OTA_Server_Event_Data_t(&qsInputBuffer, (qapi_ZB_CL_OTA_Server_Event_Data_t*)Event_Data);
      }

      if(qsResult == ssSuccess)
      {
         /* Check if the event is custom get scene or custom set scene or custom
            read attributes or custom write atributes. */
         if((Event_Data->Event_Type == QAPI_ZB_CL_OTA_SERVER_EVENT_TYPE_ATTR_CUSTOM_READ_E) || (Event_Data->Event_Type == QAPI_ZB_CL_OTA_SERVER_EVENT_TYPE_ATTR_CUSTOM_WRITE_E))
         {
            /* Initialize a response event. */
            HERH_Handle = HERH_Init_Response();
            if(HERH_Handle != NULL)
            {
               /* Write the handle into buffer. */
               qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&HERH_Handle);
            }
            else
               qsResult = ssFailure;
         }
      }
      else
         HERH_Handle = NULL;

      /* Send the event. */
      if(qsResult == ssSuccess)
      {
         /* If the event is read image then set the status to not to send
            default response. */
         if(Event_Data->Event_Type == QAPI_ZB_CL_OTA_SERVER_EVENT_TYPE_IMAGE_READ_E)
         {
            *(Event_Data->Data.Image_Read.ReturnStatus) = QAPI_ZB_ERR_ZCL_NO_DEFAULT_RESPONSE;
         }

         /* If the event is unparsed event then set the result to not
            send default response. */
         if(Event_Data->Event_Type == QAPI_ZB_CL_OTA_SERVER_EVENT_TYPE_UNPARSED_DATA_E)
         {
            *(Event_Data->Data.Unparsed_Data.Result) = QAPI_ZB_ERR_ZCL_NO_DEFAULT_RESPONSE;
         }

         qsResult = SendEvent(&qsInputBuffer);

         if((qsResult == ssSuccess) && (HERH_Handle != NULL))
         {
            /* Wait for the response event. */
            DataLength = 0;
            Data       = NULL;
            if(HERH_Wait_Response(HERH_Handle, HERH_RESPONSE_TIMEOUT, &DataLength, &Data))
            {
               /* Parsing the data. */
               switch(Event_Data->Event_Type)
               {
                  case QAPI_ZB_CL_OTA_SERVER_EVENT_TYPE_ATTR_CUSTOM_READ_E:
                     zb_cl_Parse_HERH_ReadAttr_Rsp(&(Event_Data->Data.Attr_Custom_Read), DataLength, Data);
                     break;

                  case QAPI_ZB_CL_OTA_SERVER_EVENT_TYPE_ATTR_CUSTOM_WRITE_E:
                     zb_cl_Parse_HERH_WriteAttr_Rsp(&(Event_Data->Data.Attr_Custom_Write), DataLength, Data);
                     break;

                  default:
                     qsResult = ssUnkownCommand;
                     break;
               }
            }

            /* Clean the response event. */
            HERH_Cleanup_Response(HERH_Handle);
         }
      }
   }
   else
      qsResult = ssAllocationError;
}
