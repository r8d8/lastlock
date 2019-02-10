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

#include "qapi_ble_uds_test_mnl.h"

extern Boolean_t ble_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);
extern Boolean_t ble_SendResponse(PackedBuffer_t *InputBuffer);

#define SendCommand(_a, _b) ble_SendCommand(_a, _b, __func__)
#define SendResponse(_a) ble_SendResponse(_a)

extern Boolean_t  ble_FirstSendCommandCall;
extern Boolean_t  ble_CommandSuccess;
extern uint32_t   ble_FirstLength;
extern uint8_t   *ble_FirstStart;
extern uint32_t   ble_CommandIteration;

Boolean_t Mnl_Test_qapi_BLE_UDS_Read_Characteristic_Request_Response(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t TransactionID;
   uint8_t ErrorCode;
   uint16_t Offset;
   qapi_BLE_UDS_Characteristic_Type_t Type;
   qapi_BLE_UDS_Characteristic_t UDS_Characteristic;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2979217585);
   InstanceID = (uint32_t)(1502527497);
   TransactionID = (uint32_t)(3202187905);
   ErrorCode = (uint8_t)(119);
   Offset = (uint16_t)(42001);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(6482813);
   InstanceID = (uint32_t)(716063466);
   TransactionID = (uint32_t)(1994789214);
   ErrorCode = (uint8_t)(85);
   Offset = (uint16_t)(27390);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2299927922);
   InstanceID = (uint32_t)(154694049);
   TransactionID = (uint32_t)(2910553668);
   ErrorCode = (uint8_t)(95);
   Offset = (uint16_t)(5034);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(14073119);
   InstanceID = (uint32_t)(1632114600);
   TransactionID = (uint32_t)(257718593);
   ErrorCode = (uint8_t)(217);
   Offset = (uint16_t)(51849);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(359687860);
   InstanceID = (uint32_t)(655805943);
   TransactionID = (uint32_t)(3346773129);
   ErrorCode = (uint8_t)(249);
   Offset = (uint16_t)(38954);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(983826869);
   InstanceID = (uint32_t)(4281360570);
   TransactionID = (uint32_t)(737913044);
   ErrorCode = (uint8_t)(152);
   Offset = (uint16_t)(52739);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(880931937);
   InstanceID = (uint32_t)(126830199);
   TransactionID = (uint32_t)(2113997171);
   ErrorCode = (uint8_t)(23);
   Offset = (uint16_t)(23802);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1114021813);
   InstanceID = (uint32_t)(3482431196);
   TransactionID = (uint32_t)(582442875);
   ErrorCode = (uint8_t)(35);
   Offset = (uint16_t)(38742);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1339381533);
   InstanceID = (uint32_t)(4161529732);
   TransactionID = (uint32_t)(4202562257);
   ErrorCode = (uint8_t)(133);
   Offset = (uint16_t)(39391);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1179642417);
   InstanceID = (uint32_t)(323325560);
   TransactionID = (uint32_t)(218113767);
   ErrorCode = (uint8_t)(98);
   Offset = (uint16_t)(39733);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2187383076);
   InstanceID = (uint32_t)(2731033896);
   TransactionID = (uint32_t)(2320013967);
   ErrorCode = (uint8_t)(62);
   Offset = (uint16_t)(64815);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1106592220);
   InstanceID = (uint32_t)(1039927827);
   TransactionID = (uint32_t)(3513495720);
   ErrorCode = (uint8_t)(131);
   Offset = (uint16_t)(50082);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(197878980);
   InstanceID = (uint32_t)(4130901853);
   TransactionID = (uint32_t)(3398086335);
   ErrorCode = (uint8_t)(63);
   Offset = (uint16_t)(8432);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(976499815);
   InstanceID = (uint32_t)(2432522801);
   TransactionID = (uint32_t)(2963760047);
   ErrorCode = (uint8_t)(210);
   Offset = (uint16_t)(47067);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1270796930);
   InstanceID = (uint32_t)(1266790061);
   TransactionID = (uint32_t)(3479186779);
   ErrorCode = (uint8_t)(201);
   Offset = (uint16_t)(4847);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1181910235);
   InstanceID = (uint32_t)(1487660329);
   TransactionID = (uint32_t)(1998843232);
   ErrorCode = (uint8_t)(11);
   Offset = (uint16_t)(40140);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2650084838);
   InstanceID = (uint32_t)(4078285641);
   TransactionID = (uint32_t)(1880224499);
   ErrorCode = (uint8_t)(151);
   Offset = (uint16_t)(32952);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(4215467176);
   InstanceID = (uint32_t)(918729278);
   TransactionID = (uint32_t)(961323366);
   ErrorCode = (uint8_t)(111);
   Offset = (uint16_t)(60251);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1997200418);
   InstanceID = (uint32_t)(1784776250);
   TransactionID = (uint32_t)(3196255703);
   ErrorCode = (uint8_t)(239);
   Offset = (uint16_t)(47730);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2530164415);
   InstanceID = (uint32_t)(1507793972);
   TransactionID = (uint32_t)(3645320829);
   ErrorCode = (uint8_t)(216);
   Offset = (uint16_t)(46037);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   qapi_BLE_UDS_Read_Characteristic_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Offset, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Read_Characteristic_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_UDS_Decode_UDS_Characteristic_Response(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t ValueLength;
   uint8_t *Value = NULL;
   qapi_BLE_UDS_Characteristic_Type_t Type;
   qapi_BLE_UDS_Characteristic_t UDS_Characteristic;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(443);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(110);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(86);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(475);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(131);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(317);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(141);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(1);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(361);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(101);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(348);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(357);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(7);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(508);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(388);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(16);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(365);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(41);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(17);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
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

   ValueLength = (uint32_t)(228);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_UDS_Characteristic_Type_t));
   memset(&UDS_Characteristic, 0, sizeof(UDS_Characteristic));
   GenerateRandom_qapi_BLE_UDS_Characteristic_t(&(UDS_Characteristic), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_UDS_Decode_UDS_Characteristic_Response(ValueLength, Value, Type, &UDS_Characteristic);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_UDS_Decode_UDS_Characteristic_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}
