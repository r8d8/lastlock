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
#include "qapi_ble_aios_common.h"
#include "qapi_ble_aios_common_mnl.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_aiostypes_common.h"

uint32_t Mnl_CalcPackedSize_qapi_BLE_AIOS_Write_Characteristic_Request_Data_t(qapi_BLE_AIOS_Write_Characteristic_Request_Data_t *Structure)
{
   uint32_t qsResult;

   if(Structure == NULL)
   {
      qsResult = 0;
   }
   else
   {
      qsResult = QAPI_BLE_AIOS_WRITE_CHARACTERISTIC_REQUEST_DATA_T_MIN_PACKED_SIZE;

      qsResult += CalcPackedSize_qapi_BLE_BD_ADDR_t((qapi_BLE_BD_ADDR_t *)&Structure->RemoteDevice);

      qsResult += CalcPackedSize_qapi_BLE_AIOS_Characteristic_Info_t((qapi_BLE_AIOS_Characteristic_Info_t *)&Structure->CharacteristicInfo);

      /* Determine the size of the AIOS                                 */
      /* qapi_BLE_AIOS_Characteristic_Data_t union to add to the packed */
      /* size.                                                          */
      switch(Structure->CharacteristicInfo.Type)
      {
         case QAPI_BLE_ACT_DIGITAL_E:
            qsResult += CalcPackedSize_qapi_BLE_AIOS_Digital_Characteristic_Data_t(&(Structure->Data.Digital));
            break;
         case QAPI_BLE_ACT_ANALOG_E:
            qsResult += CalcPackedSize_16(&(Structure->Data.Analog));
            break;
         case QAPI_BLE_ACT_AGGREGATE_E:
            qsResult += CalcPackedSize_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(&(Structure->Data.Aggregate));
            break;
      }
   }

   return(qsResult);
}

uint32_t Mnl_CalcPackedSize_qapi_BLE_AIOS_Characteristic_Data_t(qapi_BLE_AIOS_Characteristic_Data_t *Structure)
{
   /* This function MUST not be used since we cannot determine the union*/
   /* element. Every function that would have called this function knows*/
   /* how to handle the union element so we MUST handle it there.       */
   return(0);
}

SerStatus_t Mnl_PackedWrite_qapi_BLE_AIOS_Write_Characteristic_Request_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Write_Characteristic_Request_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;

   if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_AIOS_Write_Characteristic_Request_Data_t(Structure))
   {
      if(Structure != NULL)
      {
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->InstanceID);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->ConnectionID);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->TransactionID);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(Buffer, (int *)&Structure->ConnectionType);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_qapi_BLE_BD_ADDR_t(Buffer, (qapi_BLE_BD_ADDR_t *)&Structure->RemoteDevice);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_qapi_BLE_AIOS_Characteristic_Info_t(Buffer, (qapi_BLE_AIOS_Characteristic_Info_t *)&Structure->CharacteristicInfo);

         if(qsResult == ssSuccess)
         {
            /* Pack the qapi_BLE_AIOS_Characteristic_Data_t union.      */
            switch(Structure->CharacteristicInfo.Type)
            {
               case QAPI_BLE_ACT_DIGITAL_E:
                  qsResult = PackedWrite_qapi_BLE_AIOS_Digital_Characteristic_Data_t(Buffer, &(Structure->Data.Digital));
                  break;
               case QAPI_BLE_ACT_ANALOG_E:
                  qsResult = PackedWrite_16(Buffer, &(Structure->Data.Analog));
                  break;
               case QAPI_BLE_ACT_AGGREGATE_E:
                  qsResult = PackedWrite_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(Buffer, &(Structure->Data.Aggregate));
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

SerStatus_t Mnl_PackedWrite_qapi_BLE_AIOS_Characteristic_Data_t(PackedBuffer_t *Buffer, qapi_BLE_AIOS_Characteristic_Data_t *Structure)
{
   /* This function MUST not be used since we cannot determine the union*/
   /* element. Every function that would have called this function knows*/
   /* how to handle the union element so we MUST handle it there.       */
   return(ssFailure);
}

SerStatus_t Mnl_PackedRead_qapi_BLE_AIOS_Write_Characteristic_Request_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Write_Characteristic_Request_Data_t *Structure)
{
   SerStatus_t qsResult = ssSuccess;
   Boolean_t   qsPointerValid = FALSE;

   UNUSED(qsPointerValid);

   if(Buffer->Remaining >= QAPI_BLE_AIOS_WRITE_CHARACTERISTIC_REQUEST_DATA_T_MIN_PACKED_SIZE)
   {
      if(qsResult == ssSuccess)
         qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->InstanceID);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->ConnectionID);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->TransactionID);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->ConnectionType);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_qapi_BLE_BD_ADDR_t(Buffer, BufferList, (qapi_BLE_BD_ADDR_t *)&Structure->RemoteDevice);

      if(qsResult == ssSuccess)
         qsResult = PackedRead_qapi_BLE_AIOS_Characteristic_Info_t(Buffer, BufferList, (qapi_BLE_AIOS_Characteristic_Info_t *)&Structure->CharacteristicInfo);

      if(qsResult == ssSuccess)
      {
         /* Un-Pack the qapi_BLE_AIOS_Characteristic_Data_t union.      */
         switch(Structure->CharacteristicInfo.Type)
         {
            case QAPI_BLE_ACT_DIGITAL_E:
               qsResult = PackedRead_qapi_BLE_AIOS_Digital_Characteristic_Data_t(Buffer, BufferList, &(Structure->Data.Digital));
               break;
            case QAPI_BLE_ACT_ANALOG_E:
               qsResult = PackedRead_16(Buffer, BufferList, &(Structure->Data.Analog));
               break;
            case QAPI_BLE_ACT_AGGREGATE_E:
               qsResult = PackedRead_qapi_BLE_AIOS_Aggregate_Characteristic_Data_t(Buffer, BufferList, &(Structure->Data.Aggregate));
               break;
         }
      }

   }

   return(qsResult);
}

SerStatus_t Mnl_PackedRead_qapi_BLE_AIOS_Characteristic_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_AIOS_Characteristic_Data_t *Structure)
{
   /* This function MUST not be used since we cannot determine the union*/
   /* element. Every function that would have called this function knows*/
   /* how to handle the union element so we MUST handle it there.       */
   return(ssFailure);
}
