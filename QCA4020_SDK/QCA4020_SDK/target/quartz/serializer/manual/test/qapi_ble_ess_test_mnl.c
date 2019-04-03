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
#include <stdlib.h>
#include "qsCommon.h"
#include "qapi_ble.h"
#include "random_struct_init.h"

#include "qsCommon.h"

#include "qapi_ble_ess_test_mnl.h"

extern Boolean_t ble_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);
extern Boolean_t ble_SendResponse(PackedBuffer_t *InputBuffer);

#define SendCommand(_a, _b) ble_SendCommand(_a, _b, __func__)
#define SendResponse(_a) ble_SendResponse(_a)

extern Boolean_t  ble_FirstSendCommandCall;
extern Boolean_t  ble_CommandSuccess;
extern uint32_t   ble_FirstLength;
extern uint8_t   *ble_FirstStart;
extern uint32_t   ble_CommandIteration;

Boolean_t Mnl_Test_qapi_BLE_ESS_Read_Characteristic_Request_Response(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t TransactionID;
   uint8_t ErrorCode;
   qapi_BLE_ESS_Characteristic_Info_t CharacteristicInfo;
   qapi_BLE_ESS_Characteristic_Data_t CharacteristicData;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(812129590);
   InstanceID = (uint32_t)(2934831642);
   TransactionID = (uint32_t)(3856030457);
   ErrorCode = (uint8_t)(104);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 2.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(948432216);
   InstanceID = (uint32_t)(880482633);
   TransactionID = (uint32_t)(2279323767);
   ErrorCode = (uint8_t)(194);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 3.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(1154848160);
   InstanceID = (uint32_t)(4240940176);
   TransactionID = (uint32_t)(2217631882);
   ErrorCode = (uint8_t)(206);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 4.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(1383639815);
   InstanceID = (uint32_t)(3149613031);
   TransactionID = (uint32_t)(2384832034);
   ErrorCode = (uint8_t)(236);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 5.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(1219898834);
   InstanceID = (uint32_t)(1286150487);
   TransactionID = (uint32_t)(2556412190);
   ErrorCode = (uint8_t)(175);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 6.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(192408612);
   InstanceID = (uint32_t)(1991630021);
   TransactionID = (uint32_t)(1361383533);
   ErrorCode = (uint8_t)(74);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 7.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3764829568);
   InstanceID = (uint32_t)(4078567663);
   TransactionID = (uint32_t)(992041656);
   ErrorCode = (uint8_t)(73);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 8.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(1423211486);
   InstanceID = (uint32_t)(696754793);
   TransactionID = (uint32_t)(1549862454);
   ErrorCode = (uint8_t)(238);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 9.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3563243562);
   InstanceID = (uint32_t)(749964172);
   TransactionID = (uint32_t)(2203105101);
   ErrorCode = (uint8_t)(203);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 10.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2052459764);
   InstanceID = (uint32_t)(1578232077);
   TransactionID = (uint32_t)(1323799637);
   ErrorCode = (uint8_t)(142);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 11.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3575348305);
   InstanceID = (uint32_t)(294512820);
   TransactionID = (uint32_t)(3475517015);
   ErrorCode = (uint8_t)(4);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 12.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2016615254);
   InstanceID = (uint32_t)(1735696095);
   TransactionID = (uint32_t)(3330094945);
   ErrorCode = (uint8_t)(145);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 13.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(330274933);
   InstanceID = (uint32_t)(1191683035);
   TransactionID = (uint32_t)(1660821383);
   ErrorCode = (uint8_t)(4);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 14.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2138532740);
   InstanceID = (uint32_t)(1047575828);
   TransactionID = (uint32_t)(3323487361);
   ErrorCode = (uint8_t)(190);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 15.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(4166707448);
   InstanceID = (uint32_t)(2628649757);
   TransactionID = (uint32_t)(764718625);
   ErrorCode = (uint8_t)(92);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 16.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3845957087);
   InstanceID = (uint32_t)(1893648771);
   TransactionID = (uint32_t)(3994236571);
   ErrorCode = (uint8_t)(92);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 17.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3130992145);
   InstanceID = (uint32_t)(3476282973);
   TransactionID = (uint32_t)(676927320);
   ErrorCode = (uint8_t)(109);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 18.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3116507231);
   InstanceID = (uint32_t)(2371130849);
   TransactionID = (uint32_t)(870334905);
   ErrorCode = (uint8_t)(189);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 19.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(437886673);
   InstanceID = (uint32_t)(911645070);
   TransactionID = (uint32_t)(2531538599);
   ErrorCode = (uint8_t)(88);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 20.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(4071077700);
   InstanceID = (uint32_t)(1042246622);
   TransactionID = (uint32_t)(2580596170);
   ErrorCode = (uint8_t)(126);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_ESS_Notify_Characteristic(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t ConnectionID;
   qapi_BLE_ESS_Characteristic_Info_t CharacteristicInfo;
   qapi_BLE_ESS_Characteristic_Data_t CharacteristicData;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3907714429);
   InstanceID = (uint32_t)(3458012320);
   ConnectionID = (uint32_t)(1744267685);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 2.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2380165075);
   InstanceID = (uint32_t)(1246685066);
   ConnectionID = (uint32_t)(3949749237);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 3.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2167426114);
   InstanceID = (uint32_t)(1082719068);
   ConnectionID = (uint32_t)(900876872);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 4.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(19546426);
   InstanceID = (uint32_t)(276463182);
   ConnectionID = (uint32_t)(1013360144);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 5.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(577776011);
   InstanceID = (uint32_t)(1337042482);
   ConnectionID = (uint32_t)(3466628961);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 6.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(1183532769);
   InstanceID = (uint32_t)(687523523);
   ConnectionID = (uint32_t)(1014680829);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 7.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(1497334369);
   InstanceID = (uint32_t)(3758601777);
   ConnectionID = (uint32_t)(4281042426);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 8.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3805212811);
   InstanceID = (uint32_t)(3182048749);
   ConnectionID = (uint32_t)(4149618686);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 9.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(1354927035);
   InstanceID = (uint32_t)(2328107622);
   ConnectionID = (uint32_t)(3529085857);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 10.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(4242666401);
   InstanceID = (uint32_t)(834943573);
   ConnectionID = (uint32_t)(3348922165);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 11.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3411513297);
   InstanceID = (uint32_t)(3860400071);
   ConnectionID = (uint32_t)(3673824420);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 12.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(1185953819);
   InstanceID = (uint32_t)(3637085300);
   ConnectionID = (uint32_t)(2560743132);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 13.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(222064739);
   InstanceID = (uint32_t)(2553401637);
   ConnectionID = (uint32_t)(1161132784);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 14.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(4210908875);
   InstanceID = (uint32_t)(2183641105);
   ConnectionID = (uint32_t)(4262362597);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 15.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3768628477);
   InstanceID = (uint32_t)(2591765901);
   ConnectionID = (uint32_t)(1897114559);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 16.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3457812601);
   InstanceID = (uint32_t)(3921390224);
   ConnectionID = (uint32_t)(1908801657);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 17.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2927911918);
   InstanceID = (uint32_t)(2742850346);
   ConnectionID = (uint32_t)(2423094873);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 18.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3205650093);
   InstanceID = (uint32_t)(3164150526);
   ConnectionID = (uint32_t)(2145560837);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 19.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2202260633);
   InstanceID = (uint32_t)(3343930138);
   ConnectionID = (uint32_t)(1931964984);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 20.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2308840209);
   InstanceID = (uint32_t)(1045005945);
   ConnectionID = (uint32_t)(875210167);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_ESS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_ESS_Decode_Characteristic(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t ValueLength;
   uint8_t *Value = NULL;
   qapi_BLE_ESS_Characteristic_Type_t Type;
   qapi_BLE_ESS_Characteristic_Data_t CharacteristicData;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(442);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 2.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(369);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 3.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(466);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 4.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(277);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 5.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(52);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 6.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(141);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 7.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(10);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 8.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(28);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 9.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(181);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 10.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(184);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 11.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(285);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 12.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(422);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 13.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(197);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 14.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(336);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 15.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(160);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 16.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(316);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 17.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(143);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 18.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(434);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 19.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(220);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   /* Iteration = 20.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(288);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_ESS_Characteristic_Type_t));
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_ESS_Decode_Characteristic(ValueLength, Value, Type, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_ESS_Decode_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}
