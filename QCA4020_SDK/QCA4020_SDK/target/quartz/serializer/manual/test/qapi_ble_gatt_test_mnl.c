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

#include "qapi_ble_gatt_test_mnl.h"

extern Boolean_t ble_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);
extern Boolean_t ble_SendResponse(PackedBuffer_t *InputBuffer);

#define SendCommand(_a, _b) ble_SendCommand(_a, _b, __func__)
#define SendResponse(_a) ble_SendResponse(_a)

extern Boolean_t  ble_FirstSendCommandCall;
extern Boolean_t  ble_CommandSuccess;
extern uint32_t   ble_FirstLength;
extern uint8_t   *ble_FirstStart;
extern uint32_t   ble_CommandIteration;

Boolean_t Mnl_Test_qapi_BLE_GATT_Cleanup(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t BluetoothStackID;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(2853285758);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(338566771);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2819889615);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2401873852);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3412632021);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3852506514);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(621280247);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2681193422);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2026148844);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2596264507);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3526655427);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(249521216);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1198888667);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2117018614);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(546445929);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3988530920);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(533225408);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3347925501);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3209108078);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1159004361);
   qapi_BLE_GATT_Cleanup(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Cleanup", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_GATT_Un_Register_Service(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   uint32_t BluetoothStackID;
   uint32_t ServiceID;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3409205536);
   ServiceID = (uint32_t)(1237286899);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3670036218);
   ServiceID = (uint32_t)(1467457679);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1568081573);
   ServiceID = (uint32_t)(4195053873);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1238065038);
   ServiceID = (uint32_t)(1165541679);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1364930714);
   ServiceID = (uint32_t)(85284657);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3393831155);
   ServiceID = (uint32_t)(1443895586);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1052648450);
   ServiceID = (uint32_t)(2524563028);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(486718774);
   ServiceID = (uint32_t)(384919325);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2134330071);
   ServiceID = (uint32_t)(2286185340);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(4188061324);
   ServiceID = (uint32_t)(1061757989);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(898479448);
   ServiceID = (uint32_t)(1870602909);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1317796441);
   ServiceID = (uint32_t)(1833380972);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2397431669);
   ServiceID = (uint32_t)(2290238840);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2980254681);
   ServiceID = (uint32_t)(2167643879);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(379603584);
   ServiceID = (uint32_t)(3662805585);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3519107165);
   ServiceID = (uint32_t)(2392581199);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(519129498);
   ServiceID = (uint32_t)(3881710509);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1197860180);
   ServiceID = (uint32_t)(3620414127);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3744754216);
   ServiceID = (uint32_t)(953893774);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1555907046);
   ServiceID = (uint32_t)(3844338924);
   qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_GATT_Un_Register_Service", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}
