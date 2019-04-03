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

#include "qapi_ble_aios_test_mnl.h"

extern Boolean_t ble_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);
extern Boolean_t ble_SendResponse(PackedBuffer_t *InputBuffer);

#define SendCommand(_a, _b) ble_SendCommand(_a, _b, __func__)
#define SendResponse(_a) ble_SendResponse(_a)

extern Boolean_t  ble_FirstSendCommandCall;
extern Boolean_t  ble_CommandSuccess;
extern uint32_t   ble_FirstLength;
extern uint8_t   *ble_FirstStart;
extern uint32_t   ble_CommandIteration;

Boolean_t Mnl_Test_qapi_BLE_AIOS_Read_Characteristic_Request_Response(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t ConnectionID;
   uint32_t TransactionID;
   uint8_t ErrorCode;
   qapi_BLE_AIOS_Characteristic_Info_t CharacteristicInfo;
   qapi_BLE_AIOS_Characteristic_Data_t CharacteristicData;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(1137227216);
   InstanceID = (uint32_t)(3920175388);
   ConnectionID = (uint32_t)(2335732971);
   TransactionID = (uint32_t)(3810587066);
   ErrorCode = (uint8_t)(104);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3942017820);
   InstanceID = (uint32_t)(3434244886);
   ConnectionID = (uint32_t)(1477049500);
   TransactionID = (uint32_t)(3265786303);
   ErrorCode = (uint8_t)(238);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2724703027);
   InstanceID = (uint32_t)(3518187869);
   ConnectionID = (uint32_t)(705651264);
   TransactionID = (uint32_t)(2959426405);
   ErrorCode = (uint8_t)(61);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3264142250);
   InstanceID = (uint32_t)(3526491379);
   ConnectionID = (uint32_t)(3863486856);
   TransactionID = (uint32_t)(1192318814);
   ErrorCode = (uint8_t)(0);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(352855932);
   InstanceID = (uint32_t)(779226792);
   ConnectionID = (uint32_t)(4294021295);
   TransactionID = (uint32_t)(3250167913);
   ErrorCode = (uint8_t)(114);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2505111774);
   InstanceID = (uint32_t)(4033474083);
   ConnectionID = (uint32_t)(3714468589);
   TransactionID = (uint32_t)(4195581454);
   ErrorCode = (uint8_t)(5);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1958839265);
   InstanceID = (uint32_t)(1235430700);
   ConnectionID = (uint32_t)(3472659619);
   TransactionID = (uint32_t)(3212814310);
   ErrorCode = (uint8_t)(14);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3808771533);
   InstanceID = (uint32_t)(2248407641);
   ConnectionID = (uint32_t)(2121210014);
   TransactionID = (uint32_t)(324381977);
   ErrorCode = (uint8_t)(98);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3976449706);
   InstanceID = (uint32_t)(2903536005);
   ConnectionID = (uint32_t)(275282854);
   TransactionID = (uint32_t)(414939686);
   ErrorCode = (uint8_t)(228);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(705583851);
   InstanceID = (uint32_t)(3073833151);
   ConnectionID = (uint32_t)(3931226056);
   TransactionID = (uint32_t)(3903093945);
   ErrorCode = (uint8_t)(70);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1614178947);
   InstanceID = (uint32_t)(697203463);
   ConnectionID = (uint32_t)(426903032);
   TransactionID = (uint32_t)(157125514);
   ErrorCode = (uint8_t)(43);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(363833388);
   InstanceID = (uint32_t)(4081796452);
   ConnectionID = (uint32_t)(1971541377);
   TransactionID = (uint32_t)(566686153);
   ErrorCode = (uint8_t)(143);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(549284891);
   InstanceID = (uint32_t)(72143336);
   ConnectionID = (uint32_t)(1054243350);
   TransactionID = (uint32_t)(2213068464);
   ErrorCode = (uint8_t)(174);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(340314154);
   InstanceID = (uint32_t)(838733366);
   ConnectionID = (uint32_t)(901309722);
   TransactionID = (uint32_t)(322937107);
   ErrorCode = (uint8_t)(223);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(4289940730);
   InstanceID = (uint32_t)(152187365);
   ConnectionID = (uint32_t)(3863357884);
   TransactionID = (uint32_t)(4218774237);
   ErrorCode = (uint8_t)(205);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2895586348);
   InstanceID = (uint32_t)(112559147);
   ConnectionID = (uint32_t)(2499878008);
   TransactionID = (uint32_t)(2395851038);
   ErrorCode = (uint8_t)(51);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3454821778);
   InstanceID = (uint32_t)(750808190);
   ConnectionID = (uint32_t)(3268016868);
   TransactionID = (uint32_t)(4080204372);
   ErrorCode = (uint8_t)(90);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1849295868);
   InstanceID = (uint32_t)(2330367843);
   ConnectionID = (uint32_t)(1618979811);
   TransactionID = (uint32_t)(1444382107);
   ErrorCode = (uint8_t)(142);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3940860181);
   InstanceID = (uint32_t)(3412361295);
   ConnectionID = (uint32_t)(1358435628);
   TransactionID = (uint32_t)(2389934218);
   ErrorCode = (uint8_t)(77);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3244088182);
   InstanceID = (uint32_t)(2967824178);
   ConnectionID = (uint32_t)(3155908103);
   TransactionID = (uint32_t)(2553074976);
   ErrorCode = (uint8_t)(198);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, ConnectionID, TransactionID, ErrorCode, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_AIOS_Notify_Characteristic(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t ConnectionID;
   qapi_BLE_AIOS_Characteristic_Info_t CharacteristicInfo;
   qapi_BLE_AIOS_Characteristic_Data_t CharacteristicData;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2753915169);
   InstanceID = (uint32_t)(3200508761);
   ConnectionID = (uint32_t)(2235012957);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(480479994);
   InstanceID = (uint32_t)(398797959);
   ConnectionID = (uint32_t)(765465467);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3453043877);
   InstanceID = (uint32_t)(3149578346);
   ConnectionID = (uint32_t)(3435378970);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3731788756);
   InstanceID = (uint32_t)(549201472);
   ConnectionID = (uint32_t)(821586211);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(864610100);
   InstanceID = (uint32_t)(2519461004);
   ConnectionID = (uint32_t)(2723116771);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1126726658);
   InstanceID = (uint32_t)(3540454200);
   ConnectionID = (uint32_t)(1914454407);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2518307015);
   InstanceID = (uint32_t)(2221328909);
   ConnectionID = (uint32_t)(2251401386);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3004224277);
   InstanceID = (uint32_t)(1277627781);
   ConnectionID = (uint32_t)(2699917325);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2528403151);
   InstanceID = (uint32_t)(3270377427);
   ConnectionID = (uint32_t)(2111018629);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3752428125);
   InstanceID = (uint32_t)(1096598987);
   ConnectionID = (uint32_t)(2613397742);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3719990287);
   InstanceID = (uint32_t)(366082909);
   ConnectionID = (uint32_t)(2317498173);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(4273294237);
   InstanceID = (uint32_t)(375453662);
   ConnectionID = (uint32_t)(275707648);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2085093621);
   InstanceID = (uint32_t)(2870284801);
   ConnectionID = (uint32_t)(2033559110);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2780072728);
   InstanceID = (uint32_t)(1540748094);
   ConnectionID = (uint32_t)(2609050962);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3827191655);
   InstanceID = (uint32_t)(907146859);
   ConnectionID = (uint32_t)(2879672861);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3714099742);
   InstanceID = (uint32_t)(3238656308);
   ConnectionID = (uint32_t)(1237817526);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1295756422);
   InstanceID = (uint32_t)(2877301079);
   ConnectionID = (uint32_t)(614007462);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2382832285);
   InstanceID = (uint32_t)(2491689440);
   ConnectionID = (uint32_t)(3501950376);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1994640838);
   InstanceID = (uint32_t)(421994835);
   ConnectionID = (uint32_t)(3659450811);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3276136764);
   InstanceID = (uint32_t)(2638379450);
   ConnectionID = (uint32_t)(1688726171);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Notify_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Notify_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_AIOS_Indicate_Characteristic(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t ConnectionID;
   qapi_BLE_AIOS_Characteristic_Info_t CharacteristicInfo;
   qapi_BLE_AIOS_Characteristic_Data_t CharacteristicData;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(4098570869);
   InstanceID = (uint32_t)(2572095337);
   ConnectionID = (uint32_t)(803175932);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2514862834);
   InstanceID = (uint32_t)(2130193608);
   ConnectionID = (uint32_t)(4098643426);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3303137008);
   InstanceID = (uint32_t)(1174143147);
   ConnectionID = (uint32_t)(3801793940);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1973597282);
   InstanceID = (uint32_t)(3273137606);
   ConnectionID = (uint32_t)(711249252);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(395024834);
   InstanceID = (uint32_t)(581747246);
   ConnectionID = (uint32_t)(1304350917);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(4268344009);
   InstanceID = (uint32_t)(2295299237);
   ConnectionID = (uint32_t)(1696317958);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(573236428);
   InstanceID = (uint32_t)(2111190970);
   ConnectionID = (uint32_t)(1121988578);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2757262937);
   InstanceID = (uint32_t)(2856144103);
   ConnectionID = (uint32_t)(4199037856);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1817306860);
   InstanceID = (uint32_t)(2477941465);
   ConnectionID = (uint32_t)(3944556277);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(130452029);
   InstanceID = (uint32_t)(4216772683);
   ConnectionID = (uint32_t)(3282064576);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1215432451);
   InstanceID = (uint32_t)(2952100218);
   ConnectionID = (uint32_t)(1202159931);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2760609752);
   InstanceID = (uint32_t)(3082394554);
   ConnectionID = (uint32_t)(141924205);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(969260329);
   InstanceID = (uint32_t)(4103640640);
   ConnectionID = (uint32_t)(175225650);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2338558395);
   InstanceID = (uint32_t)(2560826806);
   ConnectionID = (uint32_t)(1343360047);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1292882754);
   InstanceID = (uint32_t)(4185374509);
   ConnectionID = (uint32_t)(3197092190);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2983380637);
   InstanceID = (uint32_t)(308797135);
   ConnectionID = (uint32_t)(2442694195);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2808321254);
   InstanceID = (uint32_t)(492820005);
   ConnectionID = (uint32_t)(901494504);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(831256535);
   InstanceID = (uint32_t)(743425271);
   ConnectionID = (uint32_t)(2748047565);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2201966831);
   InstanceID = (uint32_t)(3921852374);
   ConnectionID = (uint32_t)(1568445909);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3773466235);
   InstanceID = (uint32_t)(1185534257);
   ConnectionID = (uint32_t)(380364241);
   memset(&CharacteristicInfo, 0, sizeof(CharacteristicInfo));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Info_t(&(CharacteristicInfo), &qsBufferList);
   memset(&CharacteristicData, 0, sizeof(CharacteristicData));
   GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(&(CharacteristicData), &qsBufferList);
   qapi_BLE_AIOS_Indicate_Characteristic(BluetoothStackID, InstanceID, ConnectionID, &CharacteristicInfo, &CharacteristicData);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_AIOS_Indicate_Characteristic", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}
