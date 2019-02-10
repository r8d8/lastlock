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
#include "qapi_ble.h"
#include "qapi_ble_ess_common.h"
#include "qapi_ble_ess_qz_mnl.h"
#include "qapi_ble_ess_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_BLE_ESS_Read_Characteristic_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t TransactionID;
   uint8_t ErrorCode;
   qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo = NULL;
   qapi_BLE_ESS_Characteristic_Data_t *CharacteristicData = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicInfo = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_ESS_Characteristic_Info_t));

      if(CharacteristicInfo == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_ESS_Characteristic_Info_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_ESS_Characteristic_Info_t*)CharacteristicInfo);
      }
   }
   else
      CharacteristicInfo = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_ESS_Characteristic_Data_t));

      if(CharacteristicData == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         /* Determine the size of the ESS                               */
         /* qapi_BLE_ESS_Characteristic_Data_t union to add to the      */
         /* packed size.                                                */
         switch(CharacteristicInfo->Type)
         {
            case QAPI_BLE_ESS_ECT_GUST_FACTOR_E:
            case QAPI_BLE_ESS_ECT_UV_INDEX_E:
               /* Intentional fall through for UINT8.                   */

               qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Gust_Factor));
               break;
            case QAPI_BLE_ESS_ECT_DEW_POINT_E:
            case QAPI_BLE_ESS_ECT_HEAT_INDEX_E:
            case QAPI_BLE_ESS_ECT_WIND_CHILL_E:
               /* Intentional fall through for INT8.                    */
               qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&(CharacteristicData->Dew_Point));
               break;
            case QAPI_BLE_ESS_ECT_APPARENT_WIND_DIRECTION_E:
            case QAPI_BLE_ESS_ECT_APPARENT_WIND_SPEED_E:
            case QAPI_BLE_ESS_ECT_HUMIDITY_E:
            case QAPI_BLE_ESS_ECT_IRRADIANCE_E:
            case QAPI_BLE_ESS_ECT_RAIN_FALL_E:
            case QAPI_BLE_ESS_ECT_TEMPERATURE_E:
            case QAPI_BLE_ESS_ECT_TRUE_WIND_DIRECTION_E:
            case QAPI_BLE_ESS_ECT_TRUE_WIND_SPEED_E:
            case QAPI_BLE_ESS_ECT_MAGNETIC_DECLINATION_E:
               /* Intentional fall through for UINT16.                  */
               qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Apparent_Wind_Direction));
               break;
            case QAPI_BLE_ESS_ECT_ELEVATION_E:
            case QAPI_BLE_ESS_ECT_POLLEN_CONCENTRATION_E:
               /* Intentional fall through for UINT24.                  */
               qsResult = PackedRead_qapi_BLE_ESS_Int_24_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Elevation));
               break;
            case QAPI_BLE_ESS_ECT_PRESSURE_E:
               /* Intentional fall through for UINT32.                  */
               qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Pressure));
               break;
            case QAPI_BLE_ESS_ECT_BAROMETRIC_PRESSURE_TREND_E:
               qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&(CharacteristicData->Barometric_Pressure_Trend));
               break;
            case QAPI_BLE_ESS_ECT_MAGNETIC_FLUX_DENSITY_2D_E:
               qsResult = PackedRead_qapi_BLE_ESS_Magnetic_Flux_Density_2D_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Magnetic_Flux_Density_2D));
               break;
            case QAPI_BLE_ESS_ECT_MAGNETIC_FLUX_DENSITY_3D_E:
               qsResult = PackedRead_qapi_BLE_ESS_Magnetic_Flux_Density_3D_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Magnetic_Flux_Density_3D));
               break;
         }
      }
   }
   else
      CharacteristicData = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, CharacteristicInfo, CharacteristicData);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_ESS_FILE_ID, QAPI_BLE_ESS_READ_CHARACTERISTIC_REQUEST_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_BLE_ESS_Notify_Characteristic(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t ConnectionID;
   qapi_BLE_ESS_Characteristic_Info_t *CharacteristicInfo = NULL;
   qapi_BLE_ESS_Characteristic_Data_t *CharacteristicData = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ConnectionID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicInfo = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_ESS_Characteristic_Info_t));

      if(CharacteristicInfo == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_ESS_Characteristic_Info_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_ESS_Characteristic_Info_t*)CharacteristicInfo);
      }
   }
   else
      CharacteristicInfo = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_ESS_Characteristic_Data_t));

      if(CharacteristicData == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         /* Determine the size of the ESS                               */
         /* qapi_BLE_ESS_Characteristic_Data_t union to add to the      */
         /* packed size.                                                */
         switch(CharacteristicInfo->Type)
         {
            case QAPI_BLE_ESS_ECT_GUST_FACTOR_E:
            case QAPI_BLE_ESS_ECT_UV_INDEX_E:
               /* Intentional fall through for UINT8.                   */

               qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Gust_Factor));
               break;
            case QAPI_BLE_ESS_ECT_DEW_POINT_E:
            case QAPI_BLE_ESS_ECT_HEAT_INDEX_E:
            case QAPI_BLE_ESS_ECT_WIND_CHILL_E:
               /* Intentional fall through for INT8.                    */
               qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&(CharacteristicData->Dew_Point));
               break;
            case QAPI_BLE_ESS_ECT_APPARENT_WIND_DIRECTION_E:
            case QAPI_BLE_ESS_ECT_APPARENT_WIND_SPEED_E:
            case QAPI_BLE_ESS_ECT_HUMIDITY_E:
            case QAPI_BLE_ESS_ECT_IRRADIANCE_E:
            case QAPI_BLE_ESS_ECT_RAIN_FALL_E:
            case QAPI_BLE_ESS_ECT_TEMPERATURE_E:
            case QAPI_BLE_ESS_ECT_TRUE_WIND_DIRECTION_E:
            case QAPI_BLE_ESS_ECT_TRUE_WIND_SPEED_E:
            case QAPI_BLE_ESS_ECT_MAGNETIC_DECLINATION_E:
               /* Intentional fall through for UINT16.                  */
               qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Apparent_Wind_Direction));
               break;
            case QAPI_BLE_ESS_ECT_ELEVATION_E:
            case QAPI_BLE_ESS_ECT_POLLEN_CONCENTRATION_E:
               /* Intentional fall through for UINT24.                  */
               qsResult = PackedRead_qapi_BLE_ESS_Int_24_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Elevation));
               break;
            case QAPI_BLE_ESS_ECT_PRESSURE_E:
               /* Intentional fall through for UINT32.                  */
               qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Pressure));
               break;
            case QAPI_BLE_ESS_ECT_BAROMETRIC_PRESSURE_TREND_E:
               qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&(CharacteristicData->Barometric_Pressure_Trend));
               break;
            case QAPI_BLE_ESS_ECT_MAGNETIC_FLUX_DENSITY_2D_E:
               qsResult = PackedRead_qapi_BLE_ESS_Magnetic_Flux_Density_2D_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Magnetic_Flux_Density_2D));
               break;
            case QAPI_BLE_ESS_ECT_MAGNETIC_FLUX_DENSITY_3D_E:
               qsResult = PackedRead_qapi_BLE_ESS_Magnetic_Flux_Density_3D_Data_t(&qsInputBuffer, &qsBufferList, &(CharacteristicData->Magnetic_Flux_Density_3D));
               break;
         }
      }
   }
   else
      CharacteristicData = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, CharacteristicInfo, CharacteristicData);

      qsOutputLength = 4;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_ESS_FILE_ID, QAPI_BLE_ESS_NOTIFY_CHARACTERISTIC_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_BLE_ESS_Decode_Characteristic(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   Boolean_t          qsPointerValid = FALSE;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint32_t ValueLength;
   uint8_t *Value = NULL;
   qapi_BLE_ESS_Characteristic_Type_t Type;
   qapi_BLE_ESS_Characteristic_Data_t *CharacteristicData = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ValueLength);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&Type);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Value = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(ValueLength)));

      if(Value == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Value, sizeof(uint8_t), ValueLength);
      }
   }
   else
      Value = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      CharacteristicData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_ESS_Characteristic_Data_t));

      if(CharacteristicData == NULL)
         qsResult = ssAllocationError;
   }
   else
      CharacteristicData= NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, CharacteristicData);

      qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      /* Determine the size of the ESS                                  */
      /* qapi_BLE_ESS_Characteristic_Data_t union to add to the packed  */
      /* size.                                                          */
      switch(Type)
      {
         case QAPI_BLE_ESS_ECT_GUST_FACTOR_E:
         case QAPI_BLE_ESS_ECT_UV_INDEX_E:
            /* Intentional fall through for UINT8.                      */
            qsOutputLength += CalcPackedSize_8(&(CharacteristicData->Gust_Factor));
            break;
         case QAPI_BLE_ESS_ECT_DEW_POINT_E:
         case QAPI_BLE_ESS_ECT_HEAT_INDEX_E:
         case QAPI_BLE_ESS_ECT_WIND_CHILL_E:
            /* Intentional fall through for INT8.                       */
            qsOutputLength += CalcPackedSize_8((uint8_t *)&(CharacteristicData->Dew_Point));
            break;
         case QAPI_BLE_ESS_ECT_APPARENT_WIND_DIRECTION_E:
         case QAPI_BLE_ESS_ECT_APPARENT_WIND_SPEED_E:
         case QAPI_BLE_ESS_ECT_HUMIDITY_E:
         case QAPI_BLE_ESS_ECT_IRRADIANCE_E:
         case QAPI_BLE_ESS_ECT_RAIN_FALL_E:
         case QAPI_BLE_ESS_ECT_TEMPERATURE_E:
         case QAPI_BLE_ESS_ECT_TRUE_WIND_DIRECTION_E:
         case QAPI_BLE_ESS_ECT_TRUE_WIND_SPEED_E:
         case QAPI_BLE_ESS_ECT_MAGNETIC_DECLINATION_E:
            /* Intentional fall through for UINT16.                     */
            qsOutputLength += CalcPackedSize_16(&(CharacteristicData->Apparent_Wind_Direction));
            break;
         case QAPI_BLE_ESS_ECT_ELEVATION_E:
         case QAPI_BLE_ESS_ECT_POLLEN_CONCENTRATION_E:
            /* Intentional fall through for UINT24.                     */
            qsOutputLength += CalcPackedSize_qapi_BLE_ESS_Int_24_Data_t(&(CharacteristicData->Elevation));
            break;
         case QAPI_BLE_ESS_ECT_PRESSURE_E:
            /* Intentional fall through for UINT32.                     */
            qsOutputLength += CalcPackedSize_32(&(CharacteristicData->Pressure));
            break;
         case QAPI_BLE_ESS_ECT_BAROMETRIC_PRESSURE_TREND_E:
            qsOutputLength += CalcPackedSize_int((int *)&(CharacteristicData->Barometric_Pressure_Trend));
            break;
         case QAPI_BLE_ESS_ECT_MAGNETIC_FLUX_DENSITY_2D_E:
            qsOutputLength += CalcPackedSize_qapi_BLE_ESS_Magnetic_Flux_Density_2D_Data_t(&(CharacteristicData->Magnetic_Flux_Density_2D));
            break;
         case QAPI_BLE_ESS_ECT_MAGNETIC_FLUX_DENSITY_3D_E:
            qsOutputLength += CalcPackedSize_qapi_BLE_ESS_Magnetic_Flux_Density_3D_Data_t(&(CharacteristicData->Magnetic_Flux_Density_3D));
            break;
      }

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_ESS_FILE_ID, QAPI_BLE_ESS_DECODE_CHARACTERISTIC_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)CharacteristicData);

         if(qsResult == ssSuccess)
         {
            /* Determine the size of the ESS                            */
            /* qapi_BLE_ESS_Characteristic_Data_t union to add to the   */
            /* packed size.                                             */
            switch(Type)
            {
               case QAPI_BLE_ESS_ECT_GUST_FACTOR_E:
               case QAPI_BLE_ESS_ECT_UV_INDEX_E:
                  /* Intentional fall through for UINT8.                */
                  qsResult = PackedWrite_8(qsOutputBuffer, &(CharacteristicData->Gust_Factor));
                  break;
               case QAPI_BLE_ESS_ECT_DEW_POINT_E:
               case QAPI_BLE_ESS_ECT_HEAT_INDEX_E:
               case QAPI_BLE_ESS_ECT_WIND_CHILL_E:
                  /* Intentional fall through for INT8.                  */
                  qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)&(CharacteristicData->Dew_Point));
                  break;
               case QAPI_BLE_ESS_ECT_APPARENT_WIND_DIRECTION_E:
               case QAPI_BLE_ESS_ECT_APPARENT_WIND_SPEED_E:
               case QAPI_BLE_ESS_ECT_HUMIDITY_E:
               case QAPI_BLE_ESS_ECT_IRRADIANCE_E:
               case QAPI_BLE_ESS_ECT_RAIN_FALL_E:
               case QAPI_BLE_ESS_ECT_TEMPERATURE_E:
               case QAPI_BLE_ESS_ECT_TRUE_WIND_DIRECTION_E:
               case QAPI_BLE_ESS_ECT_TRUE_WIND_SPEED_E:
               case QAPI_BLE_ESS_ECT_MAGNETIC_DECLINATION_E:
                  /* Intentional fall through for UINT16.               */
                  qsResult = PackedWrite_16(qsOutputBuffer, &(CharacteristicData->Apparent_Wind_Direction));
                  break;
               case QAPI_BLE_ESS_ECT_ELEVATION_E:
               case QAPI_BLE_ESS_ECT_POLLEN_CONCENTRATION_E:
                  /* Intentional fall through for UINT24.               */
                  qsResult = PackedWrite_qapi_BLE_ESS_Int_24_Data_t(qsOutputBuffer, &(CharacteristicData->Elevation));
                  break;
               case QAPI_BLE_ESS_ECT_PRESSURE_E:
                  /* Intentional fall through for UINT32.               */
                  qsResult = PackedWrite_32(qsOutputBuffer, &(CharacteristicData->Pressure));
                  break;
               case QAPI_BLE_ESS_ECT_BAROMETRIC_PRESSURE_TREND_E:
                  qsResult = PackedWrite_int(qsOutputBuffer, (int *)&(CharacteristicData->Barometric_Pressure_Trend));
                  break;
               case QAPI_BLE_ESS_ECT_MAGNETIC_FLUX_DENSITY_2D_E:
                  qsResult = PackedWrite_qapi_BLE_ESS_Magnetic_Flux_Density_2D_Data_t(qsOutputBuffer, &(CharacteristicData->Magnetic_Flux_Density_2D));
                  break;
               case QAPI_BLE_ESS_ECT_MAGNETIC_FLUX_DENSITY_3D_E:
                  qsResult = PackedWrite_qapi_BLE_ESS_Magnetic_Flux_Density_3D_Data_t(qsOutputBuffer, &(CharacteristicData->Magnetic_Flux_Density_3D));
                  break;
            }
         }
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}
