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

#include "qsOSAL.h"
#include "qsPersist.h"

#define PERSIST_LIST_INITIAL_SIZE                                      (64)

typedef struct PersistListEntry_s
{
    Boolean_t       EntryUsed;
    PersistInfo_t   Info;
} PersistListEntry_t;

typedef struct PersistContext_s
{
    Mutex_t              Mutex;
    PersistListEntry_t *PersistList;
    uint32_t             PersistListSize;
} PersistContext_t;

#define PERSIST_INFO_ALLOC_SIZE(__size__)                              (sizeof(PersistInfo_t) * (__size__))

static PersistContext_t *PersistContext;

static SerStatus_t Persist_ResizePersistList(void);

/**
  Resizes the parser persist list.

  @return the status result for resizing the list.
  */
static SerStatus_t Persist_ResizePersistList(void)
{
    uint32_t        NewSize;
    SerStatus_t     RetVal;
    PersistInfo_t *NewList;

    /* Double the size of the persist list. */
    NewSize = PersistContext->PersistListSize * 2;

#if 0
    NewList = QSOSAL_Realloc(PersistContext->PersistList, PERSIST_INFO_ALLOC_SIZE(NewSize));
#else
    NewList = QSOSAL_AllocateMemory(PERSIST_INFO_ALLOC_SIZE(NewSize));

    if(NewList != NULL)
    {
        QSOSAL_MemCopy_S(NewList, PERSIST_INFO_ALLOC_SIZE(NewSize), PersistContext->PersistList, PERSIST_INFO_ALLOC_SIZE(PersistContext->PersistListSize));

        QSOSAL_FreeMemory(PersistContext->PersistList);
    }
#endif

    if(NewList != NULL)
    {
        /* Initialize the new portion of the list. */
        QSOSAL_MemInitialize(NewList + PersistContext->PersistListSize, 0, PERSIST_INFO_ALLOC_SIZE(NewSize - PersistContext->PersistListSize));

        /* TODO.   Non-matching types.*/
        PersistContext->PersistList     = (PersistListEntry_t *)NewList;
        PersistContext->PersistListSize = NewSize;

        RetVal = ssSuccess;
    }
    else
    {
        RetVal = ssAllocationError;
    }

    return(RetVal);
}

/**
  Initializes the parser module.

  @return the status result of the parser initialization.
  */
SerStatus_t Persist_Initialize(void)
{
    SerStatus_t RetVal;

    if(PersistContext == NULL)
    {
        /* Allocate the persist context. */
        PersistContext = QSOSAL_AllocateMemory(sizeof(PersistContext_t));
        if(PersistContext != NULL)
        {
            /* Create the mutex for the persist module. */
            PersistContext->Mutex = QSOSAL_CreateMutex(FALSE);
            if(PersistContext->Mutex != NULL)
            {
                /* Allocate the initial persist list. */
                PersistContext->PersistListSize = PERSIST_LIST_INITIAL_SIZE;

                /* TODO Fix pointer types. PersistListEntry_t*/
                /*PersistContext->PersistList     = (PersistInfo_t *)QSOSAL_AllocateMemory(PERSIST_INFO_ALLOC_SIZE(PersistContext->PersistListSize));*/
                PersistContext->PersistList = (PersistListEntry_t *)QSOSAL_AllocateMemory(PERSIST_INFO_ALLOC_SIZE(PersistContext->PersistListSize));
                if(PersistContext->PersistList != NULL)
                {
                    /* Initialize the persist list. */
                    QSOSAL_MemInitialize(PersistContext->PersistList, 0, PERSIST_INFO_ALLOC_SIZE(PersistContext->PersistListSize));

                    RetVal = ssSuccess;
                }
                else
                {
                    RetVal = ssAllocationError;
                }
            }
            else
            {
                RetVal = ssAllocationError;
            }
        }
        else
        {
            RetVal = ssAllocationError;
        }

        if(RetVal != ssSuccess)
        {
            /* Cleanup the allocated resources. */
            if(PersistContext->Mutex != NULL)
            {
                QSOSAL_CloseMutex(PersistContext->Mutex);
            }

            QSOSAL_FreeMemory(PersistContext);
            PersistContext = NULL;
        }
    }
    else
    {
        RetVal = ssFailure;
    }

    return(RetVal);
}

/**
  Shuts down the parser module.
  */
void Persist_Shutdown(void)
{
    if(PersistContext != NULL)
    {
        QSOSAL_WaitMutex(PersistContext->Mutex, QSOSAL_INFINITE_WAIT);

        /* Free the persist list. */
        QSOSAL_FreeMemory(PersistContext->PersistList);

        /* Delete the mutex. */
        QSOSAL_ReleaseMutex(PersistContext->Mutex);
        QSOSAL_CloseMutex(PersistContext->Mutex);

        /* Free the context. */
        QSOSAL_FreeMemory(PersistContext);
        PersistContext = NULL;
    }
}

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
SerStatus_t Persist_Register(uint32_t *PersistHandle, const PersistInfo_t *PersistInfo)
{
    uint32_t    Index;
    SerStatus_t RetVal;

    /* Initialize if not yet. */
    if (PersistContext == NULL)
    {
        Persist_Initialize();
    }

    /* Verify the module is initialized and the parameters are valid. */
    if((PersistContext != NULL) && (PersistHandle != NULL) && (PersistInfo != NULL) && (PersistInfo->ModuleID >= QS_MODULE_BLE) && (PersistInfo->ModuleID <= QS_MODULE_THREAD))
    {
        if(QSOSAL_WaitMutex(PersistContext->Mutex, QSOSAL_INFINITE_WAIT))
        {
            /* Search for an available entry in the persist list. */
            for(Index = 0; Index < PersistContext->PersistListSize; Index ++)
            {
                if(PersistContext->PersistList[Index].EntryUsed == FALSE)
                {
                    /* Found an available entry. */
                    break;
                }
            }

            if(Index == PersistContext->PersistListSize)
            {
                /* Current persist list is full so attempt to increase its size. The
                   current value of Index will reference the first entry in the newly
                   allocated list which is guaranteed to be free. */
                RetVal = Persist_ResizePersistList();
            }
            else
            {
                RetVal = ssSuccess;
            }

            if(RetVal == ssSuccess)
            {
                /* Allocate the persist list entry. */
                PersistContext->PersistList[Index].EntryUsed = TRUE;
                QSOSAL_MemCopy_S(&(PersistContext->PersistList[Index].Info), sizeof(PersistInfo_t), PersistInfo, sizeof(PersistInfo_t));

                /* Return the persist handle to the caller. */
                *PersistHandle = Index;
            }

            QSOSAL_ReleaseMutex(PersistContext->Mutex);
        }
        else
        {
            RetVal = ssFailure;
        }
    }
    else
    {
        RetVal = ssInvalidParameter;
    }

    return(RetVal);
}

/**
  Updates the persist key for a registered persist function.

  @param PersistHandle Persist handle returned from successful registration.
  @param PersistKey    The new value for the persist key.

  @return ssSuccess if the persist was found successfully or a negative value
  if there was an error.
  */
SerStatus_t Persist_UpdateKey(uint32_t PersistHandle, uint32_t PersistKey)
{
    SerStatus_t RetVal;

    /* Verify the module is initialized and the parameters are valid. */
    if((PersistContext != NULL) && (PersistHandle < PersistContext->PersistListSize))
    {
        if(QSOSAL_WaitMutex(PersistContext->Mutex, QSOSAL_INFINITE_WAIT))
        {
            /* Make sure the persist ID is in use. */
            if(PersistContext->PersistList[PersistHandle].EntryUsed == TRUE)
            {
                PersistContext->PersistList[PersistHandle].Info.PersistKey = PersistKey;

                RetVal = ssSuccess;
            }
            else
            {
                RetVal = ssInvalidParameter;
            }

            QSOSAL_ReleaseMutex(PersistContext->Mutex);
        }
        else
        {
            RetVal = ssFailure;
        }
    }
    else
    {
        RetVal = ssInvalidParameter;
    }

    return(RetVal);
}

/**
  Retrieves the persist info for the specified handle.

  @param PersistHandle Persist handle returned from successful registration.
  @param PersistInfo   Information for the persist.

  @return ssSuccess if the persist was found successfully or a negative value
  if there was an error.
  */
SerStatus_t Persist_Retrieve(uint32_t PersistHandle, PersistInfo_t *PersistInfo)
{
    SerStatus_t RetVal;

    /* Initialize if not yet. */
    if (PersistContext == NULL)
    {
        Persist_Initialize();
    }

    /* Verify the module is initialized and the parameters are valid. */
    if((PersistContext != NULL) && (PersistHandle < PersistContext->PersistListSize) && (PersistInfo))
    {
        if(QSOSAL_WaitMutex(PersistContext->Mutex, QSOSAL_INFINITE_WAIT))
        {
            /* Make sure the persist ID is in use. */
            if(PersistContext->PersistList[PersistHandle].EntryUsed == TRUE)
            {
                /* Found the correct entry. */
                QSOSAL_MemCopy_S(PersistInfo, sizeof(PersistInfo_t), &(PersistContext->PersistList[PersistHandle].Info), sizeof(PersistInfo_t));

                RetVal = ssSuccess;
            }
            else
            {
                RetVal = ssInvalidParameter;
            }

            QSOSAL_ReleaseMutex(PersistContext->Mutex);
        }
        else
        {
            RetVal = ssFailure;
        }
    }
    else
    {
        RetVal = ssInvalidParameter;
    }

    return(RetVal);
}

/**
  Retrieves the persist info based on the persist key and
  identifiers.

  @param ModuleID    ID of the persist's module to retrieve.
  @param FileID      ID of the persist's file to retrieve.
  @param FunctionID  ID of the persist's type to retrieve.
  @param PersistKey  Key specific to the persist to
  retrieve.
  */
SerStatus_t Persist_RetrieveByKey(uint16_t ModuleID, uint16_t FileID, uint16_t FunctionID, uint32_t PersistKey, PersistInfo_t *PersistInfo)
{
    uint32_t    Index;
    SerStatus_t RetVal;

    /* Initialize if not yet. */
    if (PersistContext == NULL)
    {
        Persist_Initialize();
    }

    /* Verify the module is initialized and the parameters are valid. */
    if((PersistContext != NULL) && (PersistInfo))
    {
        if(QSOSAL_WaitMutex(PersistContext->Mutex, QSOSAL_INFINITE_WAIT))
        {
            /* Search for the entry in the persist list. */
            for(Index = 0; Index < PersistContext->PersistListSize; Index ++)
            {
                /* Match to the given parameters. */
                if((PersistContext->PersistList[Index].Info.ModuleID == ModuleID) && \
                        (PersistContext->PersistList[Index].Info.FileID == FileID) && \
                        (PersistContext->PersistList[Index].Info.FunctionID == FunctionID) && \
                        (PersistContext->PersistList[Index].Info.PersistKey == PersistKey) && \
                        (PersistContext->PersistList[Index].EntryUsed == TRUE))
                {
                    /* Found the correct entry. */
                    QSOSAL_MemCopy_S(PersistInfo, sizeof(PersistInfo_t), &(PersistContext->PersistList[Index].Info), sizeof(PersistInfo_t));

                    RetVal = ssSuccess;
                    break;
                }
            }

            /* Set the AppData to NULL if the entry could not be found. */
            if(Index == PersistContext->PersistListSize)
            {
                PersistInfo->AppData = NULL;

                RetVal = ssSuccess;
            }

            QSOSAL_ReleaseMutex(PersistContext->Mutex);
        }
        else
        {
            RetVal = ssFailure;
        }
    }
    else
    {
        RetVal = ssInvalidParameter;
    }

    return(RetVal);
}

/**
  Unregisters a persist function based on the persist key and identifiers.

  @param ModuleID    ID of the persist's module to unregister.
  @param FileID      ID of the persist's file to unregister.
  @param FunctionID  ID of the persist's type to unregister.
  @param PersistKey Key specific to the persist to unregister.
  */
void Persist_UnregisterByKey(uint16_t ModuleID, uint16_t FileID, uint16_t FunctionID, uint32_t PersistKey)
{
    uint32_t Index;

    /* Verify the module is initialized and the parameters are valid. */
    if(PersistContext != NULL)
    {
        if(QSOSAL_WaitMutex(PersistContext->Mutex, QSOSAL_INFINITE_WAIT))
        {
            /* Search for the entry in the persist list. */
            for(Index = 0; Index < PersistContext->PersistListSize; Index ++)
            {
                /* Match to the given parameters. */
                if((PersistContext->PersistList[Index].Info.ModuleID == ModuleID) && \
                        (PersistContext->PersistList[Index].Info.FileID == FileID) && \
                        (PersistContext->PersistList[Index].Info.FunctionID == FunctionID) && \
                        (PersistContext->PersistList[Index].Info.PersistKey == PersistKey) && \
                        (PersistContext->PersistList[Index].EntryUsed == TRUE))
                {
                    /* Found an available entry. */
                    break;
                }
            }

            if(Index < PersistContext->PersistListSize)
            {
                /* Memset the entry to unregister it. */
                QSOSAL_MemInitialize(&(PersistContext->PersistList[Index]), 0, sizeof(PersistListEntry_t));
            }

            QSOSAL_ReleaseMutex(PersistContext->Mutex);
        }
    }
}

/**
  Unregisters a persist function based on the function ID and identifiers.

  @param ModuleID    ID of the persist's module to unregister.
  @param FileID      ID of the persist's file to unregister.
  @param FunctionID  ID of the persist's type to unregister.
  */
void Persist_UnregisterByFunctionID(uint16_t ModuleID, uint16_t FileID, uint16_t FunctionID)
{
    uint32_t Index;

    /* Verify the module is initialized and the parameters are valid. */
    if(PersistContext != NULL)
    {
        if(QSOSAL_WaitMutex(PersistContext->Mutex, QSOSAL_INFINITE_WAIT))
        {
            /* Search for the entry in the persist list. */
            for(Index = 0; Index < PersistContext->PersistListSize; Index ++)
            {
                /* Match to the given parameters. */
                if((PersistContext->PersistList[Index].Info.ModuleID == ModuleID) && \
                        (PersistContext->PersistList[Index].Info.FileID == FileID) && \
                        (PersistContext->PersistList[Index].Info.FunctionID == FunctionID) && \
                        (PersistContext->PersistList[Index].EntryUsed == TRUE))
                {
                    /* Found an available entry. */
                    break;
                }
            }

            if(Index < PersistContext->PersistListSize)
            {
                /* Memset the entry to unregister it. */
                QSOSAL_MemInitialize(&(PersistContext->PersistList[Index]), 0, sizeof(PersistListEntry_t));
            }

            QSOSAL_ReleaseMutex(PersistContext->Mutex);
        }
    }
}

/**
  Unregisters a persist function based on the PersistHandle returned from
  Persist_Register().

  @param PersistHandle Handle of the persist to unregister.
  */
void Persist_UnregisterByHandle(uint32_t PersistHandle)
{
    /* Verify the module is initialized and the parameters are valid. */
    if((PersistContext != NULL) && (PersistHandle < PersistContext->PersistListSize))
    {
        if(QSOSAL_WaitMutex(PersistContext->Mutex, QSOSAL_INFINITE_WAIT))
        {
            /* Entry found, memset it to unregister it. */
            QSOSAL_MemInitialize(&(PersistContext->PersistList[PersistHandle]), 0, sizeof(PersistListEntry_t));

            QSOSAL_ReleaseMutex(PersistContext->Mutex);
        }
    }
}

/**
  Unregisters persist functions based on the module. All persists
  registered for the module and instance will be unregistered.

  @param ModuleID ID of the module of the persists to unregister.
  */
void Persist_UnregisterByModule(uint16_t ModuleID)
{
    uint32_t Index;

    /* Verify the module is initialized and the parameters are valid. */
    if(PersistContext != NULL)
    {
        if(QSOSAL_WaitMutex(PersistContext->Mutex, QSOSAL_INFINITE_WAIT))
        {
            /* Search the list for an allocated entry that matches the provided
               information. */
            for(Index = 0; Index < PersistContext->PersistListSize; Index ++)
            {
                if((PersistContext->PersistList[Index].EntryUsed == TRUE) && \
                        (PersistContext->PersistList[Index].Info.ModuleID == ModuleID))
                {
                    /* Entry found, memset it to unregister it. */
                    QSOSAL_MemInitialize(&(PersistContext->PersistList[Index]), 0, sizeof(PersistListEntry_t));
                }
            }

            QSOSAL_ReleaseMutex(PersistContext->Mutex);
        }
    }
}

