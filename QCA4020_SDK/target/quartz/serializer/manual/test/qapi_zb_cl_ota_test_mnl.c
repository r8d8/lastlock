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
#include "qapi_zb.h"
#include "random_struct_init.h"

#include "qsCommon.h"

#include "qapi_zb_cl_ota_test_mnl.h"

extern Boolean_t zb_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);
extern Boolean_t zb_SendResponse(PackedBuffer_t *InputBuffer);

#define SendCommand(_a, _b) zb_SendCommand(_a, _b, __func__)
#define SendResponse(_a) zb_SendResponse(_a)

extern Boolean_t  zb_FirstSendCommandCall;
extern Boolean_t  zb_CommandSuccess;
extern uint32_t   zb_FirstLength;
extern uint8_t   *zb_FirstStart;
extern uint32_t   zb_CommandIteration;

Boolean_t Mnl_Test_qapi_ZB_CL_OTA_Client_Discover(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_ZB_Cluster_t Cluster;
   qapi_ZB_Addr_Mode_t DstAddrMode;
   qapi_ZB_Addr_t DstAddress;

   zb_CommandIteration = 1;

   /* Iteration = 1.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 2.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 3.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 4.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 5.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 6.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 7.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 8.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 9.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 10.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 11.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 12.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 13.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 14.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 15.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 16.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 17.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 18.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 19.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   /* Iteration = 20.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&Cluster, 0, sizeof(Cluster));
   memset(&(Cluster), 0xA5, sizeof(qapi_ZB_Cluster_t));
   memset(&DstAddrMode, 0, sizeof(DstAddrMode));
   memset(&(DstAddrMode), 0xA5, sizeof(qapi_ZB_Addr_Mode_t));
   memset(&DstAddress, 0, sizeof(DstAddress));
   qapi_ZB_CL_OTA_Client_Discover(Cluster, DstAddrMode, DstAddress);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_CL_OTA_Client_Discover", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   return(Success);
}
