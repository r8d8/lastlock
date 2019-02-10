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

#ifdef CONFIG_DAEMON_MODE

#ifndef __QS_CALLBACK_H__
#define __QS_CALLBACK_H__

#include "qsCommon.h"

/**
   Information for a callback function registered with this module.
*/
typedef struct CallbackInfo_s
{
   uint16_t   TargetID;       /** ID of target device */
   uint16_t   ModuleID;       /** ID of the module, identical for all callbacks in a module. */
   uint16_t   FileID;         /** ID of the file, identical for all callbacks in a file. */
   uint16_t   CallbackID;     /** ID of the callback, identical for all callbacks of one type. */
   uintptr_t  CallbackKey;    /** Callback key, generally returned by a registration function. */
   void      *AppFunction;    /** Application callback function. */
   uint32_t   AppParam;       /** Application callback parameter. */
} CallbackInfo_t;

/**
   Definition of a function which handles parsing the callback.

   @param CallbackHandle Handle of the callback info.
   @param CallbackInfo   Information for the callback function.
   @param BufferLength   Length of the packed data.
   @param Buffer         Buffer of the packed data for the callback.
*/

typedef void (*CallbackParser_t)(uint32_t CallbackHandle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer);

/**
   Initiializes the callback module.

   @return the status result of the parser initialization.
*/
SerStatus_t Callback_Initialize(void);

/**
   Shuts down the callback module.
*/
void Callback_Shutdown(void);

/**
   Registers a callback function with the provided information.

   @param CallbackHandle Pointer to where the callback handle will be stored upon
                         successful return.
   @param CallbackParser Function that will handle parsing the callback.
   @param CallbackInfo   Information for the callback to be registered.  The
                         ModuleID, FileID, CallbackID, and AppFunction must all be valid.

   @return ssSuccess if the callback was registered successfully or a negative
           value if there was an error.
*/
SerStatus_t Callback_Register(uint32_t *CallbackHandle, CallbackParser_t CallbackParser, const CallbackInfo_t *CallbackInfo);

/**
   Updates the callback key for a registered callback function.

   @param CallbackHandle Callback handle returned from successful registration.
   @param CallbackKey    The new value for the callback key.

   @return ssSuccess if the callback was found successfully or a negative value
           if there was an error.
*/
SerStatus_t Callback_UpdateKey(uint32_t CallbackHandle, uintptr_t CallbackKey);

/**
   Retrieves the callback info for the specified handle.

   @param CallbackHandle Callback handle returned from successful registration.
   @param CallbackInfo   Information for the callback.

   @return ssSuccess if the callback was found successfully or a negative value
           if there was an error.
*/
SerStatus_t Callback_Retrieve(uint32_t CallbackHandle, CallbackInfo_t *CallbackInfo);

/**
   Unregisters a callback function based on the callback key and identifiers.

   @param ModuleID    ID of the callback's module to unregister.
   @param FileID      ID of the callback's file to unregister.
   @param CallbackID  ID of the callback's type to unregister.
   @param CallbackKey Key specific to the callback to unregister.
*/
void Callback_UnregisterByKey(uint16_t ModuleID, uint16_t FileID, uint16_t CallbackID, uintptr_t CallbackKey);

/**
   Unregisters a callback function based on the CallbackHandle returned from
   Callback_Register().

   @param CallbackHandle Handle of the callback to unregister.
*/
void Callback_UnregisterByHandle(uint32_t CallbackHandle);

/**
   Unregisters callback functions based on the module. All callbacks
   registered for the module and instance will be unregistered.

   @param ModuleID ID of the module of the callbacks to unregister.
*/
void Callback_UnregisterByModule(uint16_t ModuleID);

/**
   Processes callback data received from a remote device. It will invoke the
   correct parser for the callback function.

   @param ModuleID     ID of the callback's module.
   @param FileID       ID of the callback's file.
   @param EventID      ID of the callback's event.
   @param BufferLength Length of the buffer that was received.
   @param Buffer       Data that was received.  Note that it is expected that
                       the callback ID is packed into the begining of this
                       buffer.
*/
void Callback_Process(uint8_t ModuleID, uint8_t FileID, uint16_t EventID, uint32_t BufferLength, uint8_t *Buffer);

/**
   Locks the callback processing preventing any future callbacks from being
   issued to the module until the unlocked.

   Note, this function may prevent callbacks to all modules, not just the
   specified module.

   @param ModuleID ID of the callback's module to lock.

   @return True if the lock was aquired successfully or false if there was an
           error.
*/
Boolean_t Callback_Lock(uint8_t ModuleID);

/**
   Unlocks callback processing for a module.

   @param ModuleID ID of the callback's module to unlock.
*/
void Callback_Unlock(uint8_t ModuleID);

#endif // __QS_CALLBACK_H__

#endif /* CONFIG_DAEMON_MODE */

