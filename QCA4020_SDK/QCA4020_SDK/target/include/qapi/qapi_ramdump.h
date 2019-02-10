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

#ifndef _QAPI_RAMDUMP_H_
#define _QAPI_RAMDUMP_H_

/**
@file qapi_ramdump.h
This section provides APIs, macros definitions, enumerations and data structures
for applications to perform ramdump.
*/

#include <stdint.h>
#include "qapi/qapi_status.h"

/** @addtogroup qapi_ramdump
@{ */

/**
@ingroup qapi_ramdump
Describe ramdump state.
*/
typedef enum 
{
    QAPI_RAMDUMP_STATE_NONE_E = 1,          /**< No ramdump is flashed. */
    QAPI_RAMDUMP_STATE_FLASHED_E = 2,       /**< Ramdump is flashed. */
} qapi_Ramdump_State_e;

/**
@ingroup qapi_ramdump
Describe ftp configuration.
*/
typedef struct
{
    char            *ip_Version;
    char            *ftps_Ip_Addr;
    char            *login_Name;
    char            *login_Password;
    char            *path;
    uint16_t        data_Port;
    uint16_t        cmd_Port;
} qapi_Ftpc_Config_t;

#define QAPI_RAMDUMP_SERVER_TYPE_FTP    "ftp"

#define QAPI_FTPC_IP_V4                 "v4"
#define QAPI_FTPC_IP_V6                 "v6"

#define QAPI_RAMDUMP_SERVER_CFG_LEN	    16

/**
@ingroup qapi_ramdump
Data structure used by the application to pass ramdump parameters.
*/
typedef struct
{
    char            *server_Type;
    union {
        uint32_t            cfg[QAPI_RAMDUMP_SERVER_CFG_LEN];
        qapi_Ftpc_Config_t  ftpc_Cfg;
    } svc_U;
    int             encryption;
    uint32_t        *encrypt_Cfg;
} qapi_Ramdump_Config_t;

/**
@ingroup qapi_ramdump
Get ramdump state.

@param[out] pState  qapi_Ramdump_State_e.

@return
QAPI_OK -- Get the right ramdump state. \n
Nonzero value -- Not get the ramdump state.
*/
qapi_Status_t qapi_Ramdump_Get_State (qapi_Ramdump_State_e *pQ_State);

/**
@ingroup qapi_ramdump
Do ramdump.

@param[in] pRamdump_Params  qapi_Ramdump_Params_t.

@return
QAPI_OK -- Ramdump ok. \n
Nonzero value -- Ramdump fail.
*/
qapi_Status_t qapi_Ramdump_Handle (const qapi_Ramdump_Config_t *pQ_Ramdump_Config);

#endif
