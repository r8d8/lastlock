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

#ifndef __QS_QUARTZ_H__
#define __QS_QUARTZ_H__

#include "common.h"

/**********************************************************************************************************************/
/*************************************************   CONSTANTS   ******************************************************/
/**********************************************************************************************************************/
#define QS_STACK            2048
#define QS_PRIORITY         10

/**********************************************************************************************************************/
/**************************************************   STRUCTURES   ****************************************************/
/**********************************************************************************************************************/

/* This structure holds state for each module */
typedef struct moduleCxt_s {
    uint32_t       mask;      /* Mask used for module related signals */
    qurt_mutex_t   mutex;     /* Mutex */
    qurt_signal_t  event;     /* Semaphore for synchronization */
    queue_t        queue;     /* Queue of packets received from host for a given module */
} moduleCxt_t;


/* Common context for all the modules */
typedef struct moduleCommonCxt_s {
    qurt_mutex_t   mutex;                 /* Mutex */
    moduleCxt_t    *cxts[QS_MODULE_MAX];  /* Individual module contexts */
} moduleCommonCxt_t;


/* Defintion of a function which handles API calls.
 * @param Buffer Buffer of the packed data for the function.
 * @param Length Length of the packed data.
 * @return Status result for parsing the function's information. This does not
 * include the return value of the API.
 */
typedef SerStatus_t (*FunctionHandler_t)(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);


/* Information for an entry in a file info list. */
typedef struct FileEntry_s
{
    FunctionHandler_t *FunctionList;   /* List of function handlers for the file. */
    uint16_t           FunctionCount;  /* Number of functions in the list. */
    uint16_t           Flags;          /* Flags for the function (future support). */
} FileEntry_t;



/**********************************************************************************************************************/
/**************************************************   FUNCTIONS   *****************************************************/
/**********************************************************************************************************************/

/*
 * Intialize QAPI serialization.
 *
 * @param       Cxt            Common context.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QapiInit(void *Cxt);

/*
 * Deintialize QAPI serialization.
 *
 * @param       Cxt            Common context.

 * @return      0 for success, non-zero for failure.
 */
void QapiDeInit(void *Cxt);

/*
 * Enqueue QAPI request received from the host.
 *
 * @param       Buffer            Object to be enqueued.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsEnqQapi(void *Buffer);


/*
 * Dequeue QAPI request received  from the host.
 *
 * @param       ModuleID          Module ID of to find respective queue.
 * @param       ReqBufPtr         Pointer to retrieve the dequeued buffer.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsDeqQapi(uint8_t ModuleID, void **ReqBufPtr);


/*
 * Allocates a packed buffer.
 *
 * @param       ModuleID          ID of the module sending this packet.
 * @param       FileID            ID of the file sending this packet.
 * @param       FunctionID        ID of the function sending this packet.
 * @param       PackedBuffer      Pointer to the packed buffer to be allocated.
 * @param       Size              Required size of the buffer.
 *
 * @return      TRUE: Success, FALSE: Failure
 */
Boolean_t AllocatePackedBuffer(uint8_t *UID, qsPacketType_t PacketType, uint8_t ModuleID, uint16_t FileID, uint16_t FunctionID, PackedBuffer_t *PackedBuffer, uint16_t Size);


/*
 * Sends an asynchronous event packet.
 *
 * @param       InputBuffer       Pointer to the packed buffer to send.
 */
SerStatus_t SendEvent(PackedBuffer_t *InputBuffer);




/* Creates an error callback packet to send to the host.
 *
 * @param       ModuleID          ID of the module sending this packet.
 * @param       FileID            ID of the file sending this packet.
 * @param       CallbackID        ID of the callback sending this packet.
 */
void SendErrorCallback(uint8_t ModuleID, uint8_t FileID, uint16_t CallbackID);


#endif /* __QS_QUARTZ_H__ */
#endif /* CONFIG_DAEMON_MODE */

