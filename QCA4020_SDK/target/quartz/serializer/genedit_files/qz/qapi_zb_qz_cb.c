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
#include "qapi_zb.h"
#include "qapi_zb_common.h"
#include "qapi_zb_qz_cb.h"

void QZ_qapi_ZB_Event_CB_t_Handler(qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_Event_t *ZB_Event, uint32_t CB_Param)
{
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    SerStatus_t        qsResult = ssSuccess;
    uint32_t           qsIndex = 0;
    uint16_t           qsSize = 0;

    UNUSED(qsIndex);

    /* Calculate size of packed function arguments. */
    qsSize = (8 + CalcPackedSize_qapi_ZB_Event_t((qapi_ZB_Event_t *)ZB_Event) + (QS_POINTER_HEADER_SIZE * 1));

    if(AllocatePackedBuffer(NULL, QS_ASYNC_E, MODULE_ZB, QAPI_ZB_FILE_ID, QAPI_ZB_EVENT_CB_T_CALLBACK_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
      if(qsResult == ssSuccess)
          qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

      if(qsResult == ssSuccess)
          qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&CB_Param);

      if(qsResult == ssSuccess)
          qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)ZB_Event);

      if((qsResult == ssSuccess) && (ZB_Event != NULL))
      {
          qsResult = PackedWrite_qapi_ZB_Event_t(&qsInputBuffer, (qapi_ZB_Event_t *)ZB_Event);
      }

        /* Send the event. */
        if(qsResult == ssSuccess)
            qsResult = SendEvent(&qsInputBuffer);
    }
    else
        qsResult = ssAllocationError;

#ifdef ENABLE_DEBUG_CALLBACKS
    if(qsResult != ssSuccess)
        SendErrorCallback(MODULE_ZB, QAPI_ZB_FILE_ID, QAPI_ZB_EVENT_CB_T_CALLBACK_ID);
#endif // ENABLE_DEBUG_CALLBACKS
}
void QZ_qapi_ZB_Persist_Notify_CB_t_Handler(qapi_ZB_Handle_t ZB_Handle, uint32_t CB_Param)
{
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    SerStatus_t        qsResult = ssSuccess;
    uint32_t           qsIndex = 0;
    uint16_t           qsSize = 0;

    UNUSED(qsIndex);

    /* Calculate size of packed function arguments. */
    qsSize = 8;

    if(AllocatePackedBuffer(NULL, QS_ASYNC_E, MODULE_ZB, QAPI_ZB_FILE_ID, QAPI_ZB_PERSIST_NOTIFY_CB_T_CALLBACK_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
      if(qsResult == ssSuccess)
          qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

      if(qsResult == ssSuccess)
          qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&CB_Param);

        /* Send the event. */
        if(qsResult == ssSuccess)
            qsResult = SendEvent(&qsInputBuffer);
    }
    else
        qsResult = ssAllocationError;

#ifdef ENABLE_DEBUG_CALLBACKS
    if(qsResult != ssSuccess)
        SendErrorCallback(MODULE_ZB, QAPI_ZB_FILE_ID, QAPI_ZB_PERSIST_NOTIFY_CB_T_CALLBACK_ID);
#endif // ENABLE_DEBUG_CALLBACKS
}
