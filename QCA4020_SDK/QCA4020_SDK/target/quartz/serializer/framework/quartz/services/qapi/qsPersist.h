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

#ifndef __QS_PERSIST_H__
#define __QS_PERSIST_H__

#include "qsCommon.h"

/**
   Information for persist data registered with this module.
*/
typedef struct PersistInfo_s
{
   uint16_t    ModuleID;      /** ID of the module, identical for all persists in a module. */
   uint16_t    FileID;        /** ID of the file, identical for all persists in a file. */
   uint16_t    FunctionID;    /** ID of the function, identical for all persists for a function. */
   uint32_t    PersistKey;    /** Persist key, generally returned by a registration function. */
   uint32_t    AppDataLength; /** Application persist data length. */
   void       *AppData;       /** Application persist data. */
} PersistInfo_t;

/**
   Initiializes the persist module.

   @return the status result of the parser initialization.
*/
SerStatus_t Persist_Initialize(void);

/**
   Shuts down the persist module.
*/
void Persist_Shutdown(void);

/**
   Registers a persist function with the provided information.

   @param PersistHandle Pointer to where the persist handle will be stored upon
                         successful return.
   @param PersistInfo   Information for the persist to be registered.  The
                         ModuleID, FileID, FunctionID, and
                         AppData must all be valid.

   @return ssSuccess if the persist was registered successfully or a negative
           value if there was an error.
*/
SerStatus_t Persist_Register(uint32_t *PersistHandle, const PersistInfo_t *PersistInfo);

/**
   Updates the persist key for a registered persist function.

   @param PersistHandle Persist handle returned from successful registration.
   @param PersistKey    The new value for the persist key.

   @return ssSuccess if the persist was found successfully or a negative value
           if there was an error.
*/
SerStatus_t Persist_UpdateKey(uint32_t PersistHandle, uint32_t PersistKey);

/**
   Retrieves the persist info for the specified handle.

   @param PersistHandle Persist handle returned from successful registration.
   @param PersistInfo   Information for the persist.

   @return ssSuccess if the persist was found successfully or a negative value
           if there was an error.
*/
SerStatus_t Persist_Retrieve(uint32_t PersistHandle, PersistInfo_t *PersistInfo);

/**
   Retrieves the persist info based on the persist key and
   identifiers.

   @param ModuleID    ID of the persist's module to retrieve.
   @param FileID      ID of the persist's file to retrieve.
   @param FunctionID  ID of the persist's type to retrieve.
   @param PersistKey  Key specific to the persist to
                       retrieve.
*/
SerStatus_t Persist_RetrieveByKey(uint16_t ModuleID, uint16_t FileID, uint16_t FunctionID, uint32_t PersistKey, PersistInfo_t *PersistInfo);

/**
   Unregisters a persist function based on the persist key and identifiers.

   @param ModuleID    ID of the persist's module to unregister.
   @param FileID      ID of the persist's file to unregister.
   @param FunctionID  ID of the persist's type to unregister.
   @param PersistKey  Key specific to the persist to
                       unregister.
*/
void Persist_UnregisterByKey(uint16_t ModuleID, uint16_t FileID, uint16_t FunctionID, uint32_t PersistKey);

/**
   Unregisters a persist function based on the function ID and identifiers.

   @param ModuleID    ID of the persist's module to unregister.
   @param FileID      ID of the persist's file to unregister.
   @param FunctionID  ID of the persist's type to unregister.
*/
void Persist_UnregisterByFunctionID(uint16_t ModuleID, uint16_t FileID, uint16_t FunctionID);

/**
   Unregisters a persist function based on the PersistHandle returned from
   Persist_Register().

   @param PersistHandle Handle of the persist to unregister.
*/
void Persist_UnregisterByHandle(uint32_t PersistHandle);

/**
   Unregisters persist functions based on the module. All persists
   registered for the module and instance will be unregistered.

   @param ModuleID ID of the module of the persists to unregister.
*/
void Persist_UnregisterByModule(uint16_t ModuleID);

#endif // __QS_PERSIST_H__

