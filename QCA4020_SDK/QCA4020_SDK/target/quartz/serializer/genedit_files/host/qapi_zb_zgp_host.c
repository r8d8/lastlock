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
#include "idlist.h"
#include "qapi_zb.h"
#include "qapi_zb_zgp_common.h"
#include "qapi_zb_zgp_host_cb.h"
#include "qapi_zb_common.h"

qapi_Status_t _qapi_ZB_ZGP_Register_Callback(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZGP_Event_CB_t ZGP_Event_CB, uint32_t CB_Param)
{
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    BufferListEntry_t *qsBufferList = NULL;
    SerStatus_t        qsResult = ssSuccess;
    uint32_t           qsIndex = 0;
    uint16_t           qsSize = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsIndex);
    UNUSED(qsPointerValid);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Handle event callback registration. */
    uint32_t qsCbParam = 0;
    CallbackInfo_t CallbackInfo;
    CallbackInfo.TargetID = TargetID;
    CallbackInfo.ModuleID = QS_MODULE_ZIGBEE;
    CallbackInfo.FileID = QAPI_ZB_ZGP_FILE_ID;
    CallbackInfo.CallbackID = QAPI_ZB_ZGP_EVENT_CB_T_CALLBACK_ID;
    CallbackInfo.CallbackKey = 0;
    CallbackInfo.AppFunction = ZGP_Event_CB;
    CallbackInfo.AppParam = (uint32_t)CB_Param;
    qsResult = Callback_Register(&qsCbParam, Host_qapi_ZB_ZGP_Event_CB_t_Handler, &CallbackInfo);

    /* Override the callback parameter with the new one. */
    CB_Param = qsCbParam;

    /* Calculate size of packed function arguments. */
    qsSize = 8;

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_ZB, QAPI_ZB_ZGP_FILE_ID, QAPI_ZB_ZGP_REGISTER_CALLBACK_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&CB_Param);

        if(qsResult == ssSuccess)
        {
            /* Send the command. */
            if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
            {
                if(qsOutputBuffer.Start != NULL)
                {
                    /* Unpack returned values. */
                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)&qsRetVal);

                    /* Update the event callback ID. */
                    if(qsRetVal == QAPI_OK)
                        qsResult = Callback_UpdateKey(qsCbParam, (uintptr_t)ZGP_Event_CB);
                    else
                        Callback_UnregisterByHandle(qsCbParam);

                    /* Set the return value to error if necessary. */
                    if(qsResult != ssSuccess)
                    {
                        qsRetVal = QAPI_ERROR;
                    }
                }
                else
                {
                    qsRetVal = QAPI_ERROR;
                }

                /* Free the output buffer. */
                FreePackedBuffer(&qsOutputBuffer);
            }
            else
            {
                qsRetVal = QAPI_ERROR;
            }
        }
        else
        {
            qsRetVal = QAPI_ERROR;
        }

        /* Free the input buffer. */
        FreePackedBuffer(&qsInputBuffer);
    }
    else
    {
        qsRetVal = QAPI_ERR_NO_MEMORY;
    }

    FreeBufferList(&qsBufferList);

    return(qsRetVal);
}

qapi_Status_t qapi_ZB_ZGP_Register_Callback(qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZGP_Event_CB_t ZGP_Event_CB, uint32_t CB_Param)
{
   return _qapi_ZB_ZGP_Register_Callback(qsTargetId, ZB_Handle, ZGP_Event_CB, CB_Param);
}

qapi_Status_t _qapi_ZB_ZGP_Unregister_Callback(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZGP_Event_CB_t ZGP_Event_CB)
{
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    BufferListEntry_t *qsBufferList = NULL;
    SerStatus_t        qsResult = ssSuccess;
    uint32_t           qsIndex = 0;
    uint16_t           qsSize = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsIndex);
    UNUSED(qsPointerValid);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Calculate size of packed function arguments. */
    qsSize = 4;

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_ZB, QAPI_ZB_ZGP_FILE_ID, QAPI_ZB_ZGP_UNREGISTER_CALLBACK_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

        if(qsResult == ssSuccess)
        {
            /* Send the command. */
            if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
            {
                if(qsOutputBuffer.Start != NULL)
                {
                    /* Unpack returned values. */
                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)&qsRetVal);

                    /* Un-register the callback. */
                    if(qsRetVal == QAPI_OK)
                        Callback_UnregisterByKey(MODULE_ZB, QAPI_ZB_ZGP_FILE_ID, QAPI_ZB_ZGP_EVENT_CB_T_CALLBACK_ID, (uintptr_t)ZGP_Event_CB);

                    /* Set the return value to error if necessary. */
                    if(qsResult != ssSuccess)
                    {
                        qsRetVal = QAPI_ERROR;
                    }
                }
                else
                {
                    qsRetVal = QAPI_ERROR;
                }

                /* Free the output buffer. */
                FreePackedBuffer(&qsOutputBuffer);
            }
            else
            {
                qsRetVal = QAPI_ERROR;
            }
        }
        else
        {
            qsRetVal = QAPI_ERROR;
        }

        /* Free the input buffer. */
        FreePackedBuffer(&qsInputBuffer);
    }
    else
    {
        qsRetVal = QAPI_ERR_NO_MEMORY;
    }

    FreeBufferList(&qsBufferList);

    return(qsRetVal);
}

qapi_Status_t qapi_ZB_ZGP_Unregister_Callback(qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZGP_Event_CB_t ZGP_Event_CB)
{
   return _qapi_ZB_ZGP_Unregister_Callback(qsTargetId, ZB_Handle, ZGP_Event_CB);
}

qapi_Status_t _qapi_ZB_ZGP_Data_Request(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZGP_GP_Data_Request_t *Data_Request)
{
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    BufferListEntry_t *qsBufferList = NULL;
    SerStatus_t        qsResult = ssSuccess;
    uint32_t           qsIndex = 0;
    uint16_t           qsSize = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsIndex);
    UNUSED(qsPointerValid);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Calculate size of packed function arguments. */
    qsSize = (4 + CalcPackedSize_qapi_ZB_ZGP_GP_Data_Request_t((qapi_ZB_ZGP_GP_Data_Request_t *)Data_Request) + (QS_POINTER_HEADER_SIZE * 1));

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_ZB, QAPI_ZB_ZGP_FILE_ID, QAPI_ZB_ZGP_DATA_REQUEST_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Data_Request);

        if((qsResult == ssSuccess) && (Data_Request != NULL))
        {
            qsResult = PackedWrite_qapi_ZB_ZGP_GP_Data_Request_t(&qsInputBuffer, (qapi_ZB_ZGP_GP_Data_Request_t *)Data_Request);
        }

        if(qsResult == ssSuccess)
        {
            /* Send the command. */
            if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
            {
                if(qsOutputBuffer.Start != NULL)
                {
                    /* Unpack returned values. */
                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)&qsRetVal);

                    /* Set the return value to error if necessary. */
                    if(qsResult != ssSuccess)
                    {
                        qsRetVal = QAPI_ERROR;
                    }
                }
                else
                {
                    qsRetVal = QAPI_ERROR;
                }

                /* Free the output buffer. */
                FreePackedBuffer(&qsOutputBuffer);
            }
            else
            {
                qsRetVal = QAPI_ERROR;
            }
        }
        else
        {
            qsRetVal = QAPI_ERROR;
        }

        /* Free the input buffer. */
        FreePackedBuffer(&qsInputBuffer);
    }
    else
    {
        qsRetVal = QAPI_ERR_NO_MEMORY;
    }

    FreeBufferList(&qsBufferList);

    return(qsRetVal);
}

qapi_Status_t qapi_ZB_ZGP_Data_Request(qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZGP_GP_Data_Request_t *Data_Request)
{
   return _qapi_ZB_ZGP_Data_Request(qsTargetId, ZB_Handle, Data_Request);
}

qapi_Status_t _qapi_ZB_ZGP_Add_Key(uint8_t TargetID, qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZGP_Key_Request_t *Key_Request)
{
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    BufferListEntry_t *qsBufferList = NULL;
    SerStatus_t        qsResult = ssSuccess;
    uint32_t           qsIndex = 0;
    uint16_t           qsSize = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsIndex);
    UNUSED(qsPointerValid);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Calculate size of packed function arguments. */
    qsSize = (4 + CalcPackedSize_qapi_ZB_ZGP_Key_Request_t((qapi_ZB_ZGP_Key_Request_t *)Key_Request) + (QS_POINTER_HEADER_SIZE * 1));

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_ZB, QAPI_ZB_ZGP_FILE_ID, QAPI_ZB_ZGP_ADD_KEY_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&ZB_Handle);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Key_Request);

        if((qsResult == ssSuccess) && (Key_Request != NULL))
        {
            qsResult = PackedWrite_qapi_ZB_ZGP_Key_Request_t(&qsInputBuffer, (qapi_ZB_ZGP_Key_Request_t *)Key_Request);
        }

        if(qsResult == ssSuccess)
        {
            /* Send the command. */
            if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
            {
                if(qsOutputBuffer.Start != NULL)
                {
                    /* Unpack returned values. */
                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_32(&qsOutputBuffer, &qsBufferList, (uint32_t *)&qsRetVal);

                    /* Set the return value to error if necessary. */
                    if(qsResult != ssSuccess)
                    {
                        qsRetVal = QAPI_ERROR;
                    }
                }
                else
                {
                    qsRetVal = QAPI_ERROR;
                }

                /* Free the output buffer. */
                FreePackedBuffer(&qsOutputBuffer);
            }
            else
            {
                qsRetVal = QAPI_ERROR;
            }
        }
        else
        {
            qsRetVal = QAPI_ERROR;
        }

        /* Free the input buffer. */
        FreePackedBuffer(&qsInputBuffer);
    }
    else
    {
        qsRetVal = QAPI_ERR_NO_MEMORY;
    }

    FreeBufferList(&qsBufferList);

    return(qsRetVal);
}

qapi_Status_t qapi_ZB_ZGP_Add_Key(qapi_ZB_Handle_t ZB_Handle, const qapi_ZB_ZGP_Key_Request_t *Key_Request)
{
   return _qapi_ZB_ZGP_Add_Key(qsTargetId, ZB_Handle, Key_Request);
}
