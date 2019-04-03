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

#ifndef __TARGET_DIAGMANAGER_INTERNAL_H__
#define __TARGET_DIAGMANAGER_INTERNAL_H__

#include <stdint.h>
#include "qapi_diag_mml_if.h"

#define DIAG_STACK_SIZE 1024
#define DIAG_PRIORITY   10


/* Return values of data manager APIs */
typedef enum {
    DIAG_SUCCESS_E,
    DIAG_FAILURE_E,
    DIAG_INVALID_PARAMETER_E,
    DIAG_MEMORY_ERROR_E
} DiagReturnCodes_e;


typedef struct
{
    qapi_diag_tr_service_context_t *cxt; /* Diag context */
    qurt_thread_t rxThread;  /* Mgmt command handler thread*/
    qurt_signal_t signal; /* Signal for synchronization between MML and mgmt agent */
} diagCxt_t;


/*
 * Initialize data manager context.
 *
 * @param       Cxt       Pointers to the common context.
 */
uint32_t DiagInit(void *Cxt);


/*
 * Deinitialize data manager context.
 *
 * @param       Cxt       Pointers to the common context.
 */
void DiagDeInit(void *Cxt);


#endif /* __TARGET_DIAGMANAGER_INTERNAL_H__ */
#endif /* CONFIG_DAEMON_MODE */

