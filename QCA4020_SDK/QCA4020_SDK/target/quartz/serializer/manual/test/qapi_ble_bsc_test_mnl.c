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
#include "qsPack.h"
#include "qapi_ble.h"
#include "random_struct_init.h"

#include "qsCommon.h"

#include "qapi_ble_bsc_test_mnl.h"

extern Boolean_t ble_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);
extern Boolean_t ble_SendResponse(PackedBuffer_t *InputBuffer);

#define SendCommand(_a, _b) ble_SendCommand(_a, _b, __func__)
#define SendResponse(_a) ble_SendResponse(_a)

extern Boolean_t  ble_FirstSendCommandCall;
extern Boolean_t  ble_CommandSuccess;
extern uint32_t   ble_FirstLength;
extern uint8_t   *ble_FirstStart;
extern uint32_t   ble_CommandIteration;

Boolean_t Mnl_Test_qapi_BLE_BSC_Query_Host_Version(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;
   char *Result = NULL;

   /* Function arguments.                                               */
   ble_CommandIteration = 1;

   /* Iteration = 1.                                                    */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   Result = qapi_BLE_BSC_Query_Host_Version();

   /* Make sure the returned character string is valid.                 */
   if((ble_CommandSuccess) && (Result) && strlen(Result))
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_Query_Host_Version", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_BSC_LockBluetoothStack(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;


#error Must complete this code manually.

   /* Function arguments.   */
   uint32_t BluetoothStackID;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3052503368);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(617443443);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1483327495);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(608917142);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2512531662);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2814660875);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3953856234);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(558537142);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3327092157);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(684134722);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(393050016);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1942962875);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3872665638);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2018628039);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2823077460);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3789187983);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3179126659);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2546884530);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3077871657);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3835319387);
   qapi_BLE_BSC_LockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_LockBluetoothStack", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_BLE_BSC_UnLockBluetoothStack(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;


#error Must complete this code manually.

   /* Function arguments.   */
   uint32_t BluetoothStackID;

   ble_CommandIteration = 1;

   /* Iteration = 1.               */
   ble_FirstSendCommandCall = TRUE;
   ble_CommandSuccess       = FALSE;
   ble_FirstLength          = 0;
   ble_FirstStart           = NULL;

   BluetoothStackID = (uint32_t)(3958731814);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(20865271);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1842618281);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3330452353);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1747228749);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1054422723);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(4258118241);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1039972990);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2754532059);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(629344933);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(482424064);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3226971268);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(3990863819);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(2478416976);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(774559682);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(121989670);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1174592071);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(529351585);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(935945431);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
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

   BluetoothStackID = (uint32_t)(1950495306);
   qapi_BLE_BSC_UnLockBluetoothStack(BluetoothStackID);
   if(ble_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      OSAL_OutputMessage("%s failed at iteration %u\n", "qapi_BLE_BSC_UnLockBluetoothStack", ble_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   ble_CommandIteration++;

   return(Success);
}
