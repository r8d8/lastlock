/*
 * Copyright (c) 2016-2017 Qualcomm Technologies, Inc.
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

#include "malloc.h"
#include "string.h"
#include "qcli_api.h"
#include "qcli_util.h"
#include "debug_demo.h"
#include "qsOSAL.h"
#include "qsCommon.h"
#include "qsPack.h"
#include "qsCallback.h"

/* Context information for the debug demo. */
typedef struct Debug_Demo_Context_s
{
   QCLI_Group_Handle_t     QCLI_Handle;                     /* QCLI handle for the debug demo. */
} Debug_Demo_Context_t;

static Debug_Demo_Context_t Debug_Demo_Context;

/* Command list for the ZigBee Cluster demo. */
const QCLI_Command_t Debug_CMD_List[] =
{
   /* cmd_function                 thread  cmd_string             usage_string                                                                      description */
};

const QCLI_Command_Group_t Debug_CMD_Group  = {"Debug",  sizeof(Debug_CMD_List) / sizeof(QCLI_Command_t), Debug_CMD_List};

static void Debug_Callback(uint32_t CallbackHandle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer);

/* Handles dropped callback events from Quartz due to packing or size errors. */
static void Debug_Callback(uint32_t CallbackHandle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
   qsDebugEvent_t *DebugEvent;
   uint8_t         ModuleID;
   uint8_t         FileID;
   uint16_t        EventID;

   /* Check the input variables. */
   if((Buffer) && (BufferLength >= QSDEBUGEVENT_T_SIZE))
   {
      /* Read the debug event message. */
      DebugEvent = (qsDebugEvent_t *)Buffer;

      ModuleID = READ_UNALIGNED_LITTLE_ENDIAN_UINT8( &DebugEvent->ModuleID);
      FileID   = READ_UNALIGNED_LITTLE_ENDIAN_UINT8( &DebugEvent->FileID);
      EventID  = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&DebugEvent->EventID);

      QCLI_Printf(Debug_Demo_Context.QCLI_Handle, "Dropped callback for ModuleID %d, FileID %d, EventID %d.\n", ModuleID, FileID, EventID);
   }
}

/**
   @brief Registers the Debug interface command with QCLI.

   @param Debug_QCLI_Handle is the QCLI handle for the main
                        Debug demo.

   @return true if the Debug demo initialized successfully,
           false otherwise.
*/
qbool_t Initialize_Debug_Demo(void)
{
   qbool_t        Ret_Val;
   SerStatus_t    Result;
   CallbackInfo_t CallbackInfo;
   uint32_t       CallbackHandle;

   memset(&Debug_Demo_Context, 0, sizeof(Debug_Demo_Context_t));

   /* Register Debug command group. */
   Debug_Demo_Context.QCLI_Handle = QCLI_Register_Command_Group(NULL, &Debug_CMD_Group);

   if(Debug_Demo_Context.QCLI_Handle)
   {
      /* Register a callback using HERH. */
      CallbackInfo.ModuleID = QS_MODULE_HERH;
      CallbackInfo.FileID = QSDEBUGEVENT_FILEID;
      CallbackInfo.CallbackID = QSDEBUGEVENT_EVENTID;
      CallbackInfo.CallbackKey = 0;
      CallbackInfo.AppFunction = Debug_Callback;
      CallbackInfo.AppParam = 0;

      /* Register a callback. */
      Result = Callback_Register(&CallbackHandle, Debug_Callback, &CallbackInfo);

      if(Result == ssSuccess)
      {
         Ret_Val = true;
      }
      else
      {
         QCLI_Printf(Debug_Demo_Context.QCLI_Handle, "Failed to register Debug callback.\n");
         Ret_Val = false;
      }
   }

   return(Ret_Val);
}

/**
   @brief Un-Registers the Debug commands with QCLI.
*/
void Cleanup_Debug_Demo(void)
{
   if(Debug_Demo_Context.QCLI_Handle)
   {
      QCLI_Unregister_Command_Group(Debug_Demo_Context.QCLI_Handle);
      Debug_Demo_Context.QCLI_Handle = NULL;
   }

   Callback_UnregisterByModule(QS_MODULE_HERH);
}

