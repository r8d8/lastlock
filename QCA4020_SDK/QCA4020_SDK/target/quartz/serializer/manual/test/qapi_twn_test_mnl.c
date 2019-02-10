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
#include "qapi_twn.h"
#include "random_struct_init.h"

#include "qsCommon.h"

#include "qapi_twn_test_mnl.h"

extern Boolean_t twn_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);
extern Boolean_t twn_SendResponse(PackedBuffer_t *InputBuffer);

#define SendCommand(_a, _b) twn_SendCommand(_a, _b, __func__)
#define SendResponse(_a) twn_SendResponse(_a)

extern Boolean_t  twn_FirstSendCommandCall;
extern Boolean_t  twn_CommandSuccess;
extern uint32_t   twn_FirstLength;
extern uint8_t   *twn_FirstStart;
extern uint32_t   twn_CommandIteration;

Boolean_t Mnl_Test_qapi_TWN_IPv6_Remove_Unicast_Address(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_TWN_Handle_t TWN_Handle;
   qapi_TWN_IPv6_Address_t Address;

   twn_CommandIteration = 1;

   /* Iteration = 1.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 2.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 3.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 4.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 5.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 6.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 7.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 8.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 9.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 10.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 11.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 12.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 13.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 14.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 15.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 16.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 17.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 18.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 19.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 20.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Remove_Unicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Remove_Unicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_TWN_IPv6_Subscribe_Multicast_Address(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_TWN_Handle_t TWN_Handle;
   qapi_TWN_IPv6_Address_t Address;

   twn_CommandIteration = 1;

   /* Iteration = 1.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 2.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 3.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 4.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 5.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 6.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 7.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 8.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 9.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 10.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 11.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 12.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 13.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 14.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 15.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 16.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 17.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 18.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 19.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 20.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Subscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Subscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_TWN_IPv6_Unsubscribe_Multicast_Address(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_TWN_Handle_t TWN_Handle;
   qapi_TWN_IPv6_Address_t Address;

   twn_CommandIteration = 1;

   /* Iteration = 1.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 2.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 3.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 4.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 5.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 6.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 7.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 8.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 9.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 10.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 11.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 12.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 13.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 14.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 15.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 16.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 17.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 18.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 19.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 20.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_IPv6_Unsubscribe_Multicast_Address(TWN_Handle, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_IPv6_Unsubscribe_Multicast_Address", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_TWN_Commissioner_Send_PanId_Query(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_TWN_Handle_t TWN_Handle;
   uint16_t PanId;
   uint32_t ChannelMask;
   qapi_TWN_IPv6_Address_t Address;

   twn_CommandIteration = 1;

   /* Iteration = 1.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(57971);
   ChannelMask = (uint32_t)(4056541088);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 2.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(4652);
   ChannelMask = (uint32_t)(3995604840);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 3.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(4634);
   ChannelMask = (uint32_t)(4256121663);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 4.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(12293);
   ChannelMask = (uint32_t)(1443735681);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 5.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(62261);
   ChannelMask = (uint32_t)(3241330216);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 6.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(8404);
   ChannelMask = (uint32_t)(2278851054);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 7.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(51210);
   ChannelMask = (uint32_t)(1881031383);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 8.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(17528);
   ChannelMask = (uint32_t)(394813512);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 9.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(52959);
   ChannelMask = (uint32_t)(2831144395);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 10.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(3000);
   ChannelMask = (uint32_t)(2578926680);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 11.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(18607);
   ChannelMask = (uint32_t)(1367078795);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 12.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(30027);
   ChannelMask = (uint32_t)(2699863181);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 13.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(12045);
   ChannelMask = (uint32_t)(1395666160);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 14.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(48039);
   ChannelMask = (uint32_t)(1048658706);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 15.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(52765);
   ChannelMask = (uint32_t)(688736223);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 16.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(33464);
   ChannelMask = (uint32_t)(3631283192);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 17.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(16776);
   ChannelMask = (uint32_t)(622362073);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 18.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(9888);
   ChannelMask = (uint32_t)(3468057924);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 19.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(22302);
   ChannelMask = (uint32_t)(3445297830);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 20.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   PanId = (uint16_t)(59837);
   ChannelMask = (uint32_t)(2501257631);
   memset(&Address, 0, sizeof(Address));
   qapi_TWN_Commissioner_Send_PanId_Query(TWN_Handle, PanId, ChannelMask, &Address);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_PanId_Query", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_TWN_Commissioner_Send_Mgmt_Active_Get(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_TWN_Handle_t TWN_Handle;
   qapi_TWN_IPv6_Address_t Address;
   uint8_t *TlvBuffer = NULL;
   uint8_t Length;

   twn_CommandIteration = 1;

   /* Iteration = 1.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(202);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 2.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(351);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 3.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(502);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 4.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(242);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 5.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(502);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 6.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(277);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 7.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(260);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 8.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(371);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 9.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(23);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 10.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(381);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 11.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(38);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 12.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(287);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 13.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(290);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 14.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(222);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 15.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(282);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 16.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(119);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 17.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(362);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 18.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(39);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 19.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(378);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   /* Iteration = 20.               */
   twn_FirstSendCommandCall = TRUE;
   twn_CommandSuccess       = FALSE;
   twn_FirstLength          = 0;
   twn_FirstStart           = NULL;

   memset(&TWN_Handle, 0, sizeof(TWN_Handle));
   memset(&(TWN_Handle), 0xA5, sizeof(qapi_TWN_Handle_t));
   memset(&Address, 0, sizeof(Address));
   Length = (uint8_t)(272);
   TlvBuffer = (uint8_t *)AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t) * Length));
   if(TlvBuffer != NULL)
   {
      for(unsigned int Index=0;Index<Length;Index++)
      {
         TlvBuffer[Index] = (uint8_t)(rand());
      }
   }
   qapi_TWN_Commissioner_Send_Mgmt_Active_Get(TWN_Handle, &Address, TlvBuffer, Length);
   if(twn_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_TWN_Commissioner_Send_Mgmt_Active_Get", twn_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   twn_CommandIteration++;

   return(Success);
}
