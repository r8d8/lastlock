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
#include "qsCommon.h"
#include "qsQuartz.h"
#include "qapi_ble.h"
#include "qapi_ble_gls_common.h"
#include "qapi_ble_gls_qz_cb.h"

void QZ_qapi_BLE_GLS_Event_Callback_t_Handler(uint32_t BluetoothStackID, qapi_BLE_GLS_Event_Data_t *GLS_Event_Data, uint32_t CallbackParameter)
{
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    SerStatus_t        qsResult = ssSuccess;
    uint32_t           qsIndex = 0;
    uint16_t           qsSize = 0;

    UNUSED(qsIndex);

    /* Calculate size of packed function arguments. */
    qsSize = (8 + CalcPackedSize_qapi_BLE_GLS_Event_Data_t((qapi_BLE_GLS_Event_Data_t *)GLS_Event_Data) + (QS_POINTER_HEADER_SIZE * 1));

    if(AllocatePackedBuffer(NULL, QS_ASYNC_E, MODULE_BLE, QAPI_BLE_GLS_FILE_ID, QAPI_BLE_GLS_EVENT_CALLBACK_T_CALLBACK_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
      if(qsResult == ssSuccess)
          qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&BluetoothStackID);

      if(qsResult == ssSuccess)
          qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&CallbackParameter);

      if(qsResult == ssSuccess)
          qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)GLS_Event_Data);

      if((qsResult == ssSuccess) && (GLS_Event_Data != NULL))
      {
          qsResult = PackedWrite_qapi_BLE_GLS_Event_Data_t(&qsInputBuffer, (qapi_BLE_GLS_Event_Data_t *)GLS_Event_Data);
      }

        /* Send the event. */
        if(qsResult == ssSuccess)
            qsResult = SendEvent(&qsInputBuffer);
    }
    else
        qsResult = ssAllocationError;

#ifdef ENABLE_DEBUG_CALLBACKS
    if(qsResult != ssSuccess)
        SendErrorCallback(MODULE_BLE, QAPI_BLE_GLS_FILE_ID, QAPI_BLE_GLS_EVENT_CALLBACK_T_CALLBACK_ID);
#endif // ENABLE_DEBUG_CALLBACKS
}
