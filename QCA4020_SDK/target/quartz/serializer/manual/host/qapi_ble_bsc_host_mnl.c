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

#include <stdint.h>
#include <string.h>
#include "qsCommon.h"
#include "qsHost.h"
#include "qsCallback.h"
#include "qapi_ble.h"
#include "qapi_ble_bsc_common.h"
#include "qapi_ble_bsc_host_mnl.h"
#include "qapi_ble_bsc_host_cb.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_hcitypes_common.h"

   /* Bluetooth Protocol Stack Major and Minor Version Numbers.         */
#define BTPS_VERSION_MAJOR_VERSION_NUMBER                   4
#define BTPS_VERSION_MINOR_VERSION_NUMBER                   2

   /* Bluetooth Protocol Stack Release Number.                          */
#ifndef BTPS_VERSION_RELEASE_NUMBER
   #define BTPS_VERSION_RELEASE_NUMBER                      1
#endif

   /* Bluetooth Protocol Stack Revision Number.                         */
#ifndef BTPS_VERSION_REVISION_NUMBER
   #define BTPS_VERSION_REVISION_NUMBER                     1
#endif

   /* Constants used to convert numeric constants to string constants   */
   /* (used in MACRO's below).                                          */
#define BTPS_VERSION_NUMBER_TO_STRING(_x)                   #_x
#define BTPS_VERSION_CONSTANT_TO_STRING(_y)                 BTPS_VERSION_NUMBER_TO_STRING(_y)

   /* Bluetooth Protocol Stack Constant Version String of the form      */
   /*    "a.b.c.d"                                                      */
   /* where:                                                            */
   /*    a - BTPS_VERSION_MAJOR_VERSION_NUMBER                          */
   /*    b - BTPS_VERSION_MINOR_VERSION_NUMBER                          */
   /*    c - BTPS_VERSION_RELEASE_NUMBER                                */
   /*    d - BTPS_VERSION_REVISION_NUMBER                               */
#define BTPS_VERSION_VERSION_STRING                         BTPS_VERSION_CONSTANT_TO_STRING(BTPS_VERSION_MAJOR_VERSION_NUMBER) "." BTPS_VERSION_CONSTANT_TO_STRING(BTPS_VERSION_MINOR_VERSION_NUMBER) "." BTPS_VERSION_CONSTANT_TO_STRING(BTPS_VERSION_RELEASE_NUMBER) "." BTPS_VERSION_CONSTANT_TO_STRING(BTPS_VERSION_REVISION_NUMBER)

char *Mnl_qapi_BLE_BSC_Query_Host_Version(uint8_t TargetID)
{
    return(BTPS_VERSION_VERSION_STRING);
}

int Mnl_qapi_BLE_BSC_LockBluetoothStack(uint8_t TargetID, uint32_t BluetoothStackID)
{
    int ret_val;

    if(Callback_Lock(QS_MODULE_BLE))
        ret_val = 0;
    else
        ret_val = QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES;

    return(ret_val);
}

void Mnl_qapi_BLE_BSC_UnLockBluetoothStack(uint8_t TargetID, uint32_t BluetoothStackID)
{
    Callback_Unlock(QS_MODULE_BLE);
}
