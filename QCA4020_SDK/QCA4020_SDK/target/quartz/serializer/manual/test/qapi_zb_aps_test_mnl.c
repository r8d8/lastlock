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

#include "qapi_zb_aps_test_mnl.h"

extern Boolean_t zb_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);
extern Boolean_t zb_SendResponse(PackedBuffer_t *InputBuffer);

#define SendCommand(_a, _b) zb_SendCommand(_a, _b, __func__)
#define SendResponse(_a) zb_SendResponse(_a)

extern Boolean_t  zb_FirstSendCommandCall;
extern Boolean_t  zb_CommandSuccess;
extern uint32_t   zb_FirstLength;
extern uint8_t   *zb_FirstStart;
extern uint32_t   zb_CommandIteration;

Boolean_t Mnl_Test_qapi_ZB_APSME_Get_Request(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_ZB_Handle_t ZB_Handle;
   qapi_ZB_AIB_Attribute_ID_t AIBAttribute;
   uint8_t AIBAttributeIndex;
   uint16_t AIBAttributeLength;
   void *AIBAttributeValue = NULL;

   zb_CommandIteration = 1;

   /* Iteration = 1.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(241);
   AIBAttributeLength = (uint16_t)(64489);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(97);
   AIBAttributeLength = (uint16_t)(21596);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(163);
   AIBAttributeLength = (uint16_t)(48719);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(58);
   AIBAttributeLength = (uint16_t)(4996);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(210);
   AIBAttributeLength = (uint16_t)(53101);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(137);
   AIBAttributeLength = (uint16_t)(36079);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(88);
   AIBAttributeLength = (uint16_t)(17975);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(220);
   AIBAttributeLength = (uint16_t)(40208);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(209);
   AIBAttributeLength = (uint16_t)(38487);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(48);
   AIBAttributeLength = (uint16_t)(11463);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(182);
   AIBAttributeLength = (uint16_t)(47927);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(80);
   AIBAttributeLength = (uint16_t)(41496);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(243);
   AIBAttributeLength = (uint16_t)(14208);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(102);
   AIBAttributeLength = (uint16_t)(46049);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(182);
   AIBAttributeLength = (uint16_t)(56875);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(185);
   AIBAttributeLength = (uint16_t)(47191);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(147);
   AIBAttributeLength = (uint16_t)(33475);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(93);
   AIBAttributeLength = (uint16_t)(28551);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(10);
   AIBAttributeLength = (uint16_t)(10403);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(209);
   AIBAttributeLength = (uint16_t)(24325);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Get_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, &AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Get_Request", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_ZB_APSME_Set_Request(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_ZB_Handle_t ZB_Handle;
   qapi_ZB_AIB_Attribute_ID_t AIBAttribute;
   uint8_t AIBAttributeIndex;
   uint16_t AIBAttributeLength;
   void *AIBAttributeValue = NULL;

   zb_CommandIteration = 1;

   /* Iteration = 1.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(9);
   AIBAttributeLength = (uint16_t)(274);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(59);
   AIBAttributeLength = (uint16_t)(504);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(29);
   AIBAttributeLength = (uint16_t)(321);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(29);
   AIBAttributeLength = (uint16_t)(203);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(88);
   AIBAttributeLength = (uint16_t)(270);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(203);
   AIBAttributeLength = (uint16_t)(465);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(201);
   AIBAttributeLength = (uint16_t)(99);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(224);
   AIBAttributeLength = (uint16_t)(219);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(12);
   AIBAttributeLength = (uint16_t)(458);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(78);
   AIBAttributeLength = (uint16_t)(302);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(78);
   AIBAttributeLength = (uint16_t)(163);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(36);
   AIBAttributeLength = (uint16_t)(485);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(154);
   AIBAttributeLength = (uint16_t)(151);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(122);
   AIBAttributeLength = (uint16_t)(195);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(51);
   AIBAttributeLength = (uint16_t)(348);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(211);
   AIBAttributeLength = (uint16_t)(377);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(177);
   AIBAttributeLength = (uint16_t)(244);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(187);
   AIBAttributeLength = (uint16_t)(91);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(57);
   AIBAttributeLength = (uint16_t)(23);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&AIBAttribute, 0, sizeof(AIBAttribute));
   memset(&(AIBAttribute), 0xA5, sizeof(qapi_ZB_AIB_Attribute_ID_t));
   AIBAttributeIndex = (uint8_t)(235);
   AIBAttributeLength = (uint16_t)(267);
   AIBAttributeValue = (void *)AllocateBufferListEntry(&qsBufferList, (1 * AIBAttributeLength));
   if(AIBAttributeValue != NULL)
   {
      for(unsigned int Index=0;Index<AIBAttributeLength;Index++)
      {
         memset(&(((uint8_t *)AIBAttributeValue)[Index]), 0xA5, 1);
      }
   }
   qapi_ZB_APSME_Set_Request(ZB_Handle, AIBAttribute, AIBAttributeIndex, AIBAttributeLength, AIBAttributeValue);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APSME_Set_Request", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   return(Success);
}

Boolean_t Mnl_Test_qapi_ZB_APS_Test_Endpoint_Data_Request(void)
{
   Boolean_t Success;
   BufferListEntry_t *qsBufferList  = NULL;
   unsigned int Index;

   /* Function arguments.   */
   qapi_ZB_Handle_t ZB_Handle;
   void *TestEndpoint = NULL;
   qapi_ZB_APSDE_Data_Request_t RequestData;
   uint16_t RspClusterID;

   zb_CommandIteration = 1;

   /* Iteration = 1.               */
   zb_FirstSendCommandCall = TRUE;
   zb_CommandSuccess       = FALSE;
   zb_FirstLength          = 0;
   zb_FirstStart           = NULL;

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(531);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(9337);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(50193);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(11969);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(7136);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(30165);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(13717);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(18295);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(50799);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(50417);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(29749);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(4727);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(8927);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(2782);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(14290);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(54342);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(6973);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(39723);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(3012);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
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

   memset(&ZB_Handle, 0, sizeof(ZB_Handle));
   memset(&(ZB_Handle), 0xA5, sizeof(qapi_ZB_Handle_t));
   memset(&RequestData, 0, sizeof(RequestData));
   GenerateRandom_qapi_ZB_APSDE_Data_Request_t(&(RequestData), &qsBufferList);
   RspClusterID = (uint16_t)(37909);
   TestEndpoint = (void *)AllocateBufferListEntry(&qsBufferList, (1 * 1));
   if(TestEndpoint != NULL)
   {
      memset(&(((uint8_t *)TestEndpoint)[0]), 0xA5, 1);
   }
   qapi_ZB_APS_Test_Endpoint_Data_Request(ZB_Handle, TestEndpoint, &RequestData, RspClusterID);
   if(zb_CommandSuccess)
   {
      Success = TRUE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;
   }
   else
   {
      QSOSAL_OutputMessage("%s failed at iteration %u\n", "qapi_ZB_APS_Test_Endpoint_Data_Request", zb_CommandIteration);
      Success = FALSE;

      FreeBufferList(&qsBufferList);
      qsBufferList = NULL;

      return(Success);
   }

   zb_CommandIteration++;

   return(Success);
}
