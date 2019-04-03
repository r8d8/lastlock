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

#include "qapi_ble_ots_test_mnl.h"

extern Boolean_t ble_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);
extern Boolean_t ble_SendResponse(PackedBuffer_t *InputBuffer);

#define SendCommand(_a, _b) ble_SendCommand(_a, _b, __func__)
#define SendResponse(_a) ble_SendResponse(_a)

extern Boolean_t  ble_FirstSendCommandCall;
extern Boolean_t  ble_CommandSuccess;
extern uint32_t   ble_FirstLength;
extern uint8_t   *ble_FirstStart;
extern uint32_t   ble_CommandIteration;

Boolean_t Mnl_Test_qapi_BLE_OTS_Read_Object_Metadata_Request_Response(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t BluetoothStackID;
   uint32_t InstanceID;
   uint32_t TransactionID;
   uint8_t ErrorCode;
   qapi_BLE_OTS_Object_Metadata_Type_t Type;
   qapi_BLE_OTS_Object_Metadata_Data_t Metadata;
   uint8_t Offset;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2863048799);
   InstanceID = (uint32_t)(4072087782);
   TransactionID = (uint32_t)(3039783268);
   ErrorCode = (uint8_t)(166);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(135);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3458029674);
   InstanceID = (uint32_t)(562693777);
   TransactionID = (uint32_t)(9757196);
   ErrorCode = (uint8_t)(192);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(87);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(133220430);
   InstanceID = (uint32_t)(25570185);
   TransactionID = (uint32_t)(2158309054);
   ErrorCode = (uint8_t)(215);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(151);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(862464915);
   InstanceID = (uint32_t)(4227966173);
   TransactionID = (uint32_t)(1692342521);
   ErrorCode = (uint8_t)(36);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(111);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(422326650);
   InstanceID = (uint32_t)(2195467346);
   TransactionID = (uint32_t)(3627059072);
   ErrorCode = (uint8_t)(40);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(96);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(722816974);
   InstanceID = (uint32_t)(914379629);
   TransactionID = (uint32_t)(2607029150);
   ErrorCode = (uint8_t)(156);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(50);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(932438432);
   InstanceID = (uint32_t)(4235566909);
   TransactionID = (uint32_t)(2979562265);
   ErrorCode = (uint8_t)(178);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(128);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3620923482);
   InstanceID = (uint32_t)(3908979679);
   TransactionID = (uint32_t)(1614476579);
   ErrorCode = (uint8_t)(27);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(135);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3583022548);
   InstanceID = (uint32_t)(3582614521);
   TransactionID = (uint32_t)(1718742480);
   ErrorCode = (uint8_t)(119);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(28);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2897519132);
   InstanceID = (uint32_t)(1247721959);
   TransactionID = (uint32_t)(2047251266);
   ErrorCode = (uint8_t)(55);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(166);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2573451883);
   InstanceID = (uint32_t)(542968881);
   TransactionID = (uint32_t)(3576142967);
   ErrorCode = (uint8_t)(188);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(148);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1735570153);
   InstanceID = (uint32_t)(4166884894);
   TransactionID = (uint32_t)(1158761150);
   ErrorCode = (uint8_t)(250);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(105);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3925702909);
   InstanceID = (uint32_t)(3837255302);
   TransactionID = (uint32_t)(1267573371);
   ErrorCode = (uint8_t)(106);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(138);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(338648664);
   InstanceID = (uint32_t)(899053494);
   TransactionID = (uint32_t)(2972088806);
   ErrorCode = (uint8_t)(155);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(134);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2025017178);
   InstanceID = (uint32_t)(1150872315);
   TransactionID = (uint32_t)(23083731);
   ErrorCode = (uint8_t)(104);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(97);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(298237338);
   InstanceID = (uint32_t)(1182223489);
   TransactionID = (uint32_t)(2089453401);
   ErrorCode = (uint8_t)(238);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(86);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1036492794);
   InstanceID = (uint32_t)(3585248181);
   TransactionID = (uint32_t)(2582383769);
   ErrorCode = (uint8_t)(159);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(37);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1177398561);
   InstanceID = (uint32_t)(2131381995);
   TransactionID = (uint32_t)(1445873492);
   ErrorCode = (uint8_t)(233);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(161);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3361474584);
   InstanceID = (uint32_t)(121455914);
   TransactionID = (uint32_t)(1267378146);
   ErrorCode = (uint8_t)(144);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(69);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(501422828);
   InstanceID = (uint32_t)(2560767012);
   TransactionID = (uint32_t)(3857054487);
   ErrorCode = (uint8_t)(84);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Offset = (uint8_t)(1);
   qapi_BLE_OTS_Read_Object_Metadata_Request_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, Type, &Metadata, Offset);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Read_Object_Metadata_Request_Response", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_OTS_Format_Object_Metadata(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_BLE_OTS_Object_Metadata_Type_t Type;
   qapi_BLE_OTS_Object_Metadata_Data_t Metadata;
   uint16_t BufferLength;
   uint8_t Buffer;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(17639);
   Buffer = (uint8_t)(160);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(5796);
   Buffer = (uint8_t)(80);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(38318);
   Buffer = (uint8_t)(68);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(26119);
   Buffer = (uint8_t)(30);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(24213);
   Buffer = (uint8_t)(54);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(3115);
   Buffer = (uint8_t)(211);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(49904);
   Buffer = (uint8_t)(254);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(34117);
   Buffer = (uint8_t)(254);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(36391);
   Buffer = (uint8_t)(86);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(58162);
   Buffer = (uint8_t)(189);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(29500);
   Buffer = (uint8_t)(189);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(3352);
   Buffer = (uint8_t)(196);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(20340);
   Buffer = (uint8_t)(18);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(30646);
   Buffer = (uint8_t)(25);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(57859);
   Buffer = (uint8_t)(43);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(42209);
   Buffer = (uint8_t)(187);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(47038);
   Buffer = (uint8_t)(165);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(6038);
   Buffer = (uint8_t)(103);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(57559);
   Buffer = (uint8_t)(27);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
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

   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   BufferLength = (uint16_t)(60306);
   Buffer = (uint8_t)(143);
   qapi_BLE_OTS_Format_Object_Metadata(Type, &Metadata, BufferLength, &Buffer);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Format_Object_Metadata", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_OTS_Decode_Object_Metadata(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t ValueLength;
   uint8_t *Value = NULL;
   qapi_BLE_OTS_Object_Metadata_Type_t Type;
   qapi_BLE_OTS_Object_Metadata_Data_t Metadata;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   ValueLength = (uint32_t)(200);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(159);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(347);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(39);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(70);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(12);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(351);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(224);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(187);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(216);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(201);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(421);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(88);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(267);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(59);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(224);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(410);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(314);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(441);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
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

   ValueLength = (uint32_t)(185);
   memset(&Type, 0, sizeof(Type));
   memset(&(Type), 0xA5, sizeof(qapi_BLE_OTS_Object_Metadata_Type_t));
   memset(&Metadata, 0, sizeof(Metadata));
   GenerateRandom_qapi_BLE_OTS_Object_Metadata_Data_t(&(Metadata), &qsBufferList);
   Value = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * ValueLength));
   if(Value != NULL)
   {
      for(unsigned int Index=0;Index<ValueLength;Index++)
      {
         Value[Index] = (uint8_t)(rand());
      }
   }
   qapi_BLE_OTS_Decode_Object_Metadata(ValueLength, Value, Type, &Metadata);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_OTS_Decode_Object_Metadata", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}
