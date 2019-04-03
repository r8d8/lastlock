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
#include "qapi_twn.h"
#include "qapi_twn_hosted_host_mnl.h"
#include "qapi_twn_hosted_common.h"
#include "qapi_twn_hosted_host_cb.h"
#include "qapi_twn_common.h"

qapi_Status_t _qapi_TWN_Hosted_Start_Border_Agent(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, int AddressFamily, const char *DisplayName, const char *HostName, const char *Interface)
{
    return(Mnl_qapi_TWN_Hosted_Start_Border_Agent(TargetID, TWN_Handle, AddressFamily, DisplayName, HostName, Interface));
}

qapi_Status_t qapi_TWN_Hosted_Start_Border_Agent(qapi_TWN_Handle_t TWN_Handle, int AddressFamily, const char *DisplayName, const char *HostName, const char *Interface)
{
   return _qapi_TWN_Hosted_Start_Border_Agent(qsTargetId, TWN_Handle, AddressFamily, DisplayName, HostName, Interface);
}

qapi_Status_t _qapi_TWN_Hosted_Stop_Border_Agent(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle)
{
    return(Mnl_qapi_TWN_Hosted_Stop_Border_Agent(TargetID, TWN_Handle));
}

qapi_Status_t qapi_TWN_Hosted_Stop_Border_Agent(qapi_TWN_Handle_t TWN_Handle)
{
   return _qapi_TWN_Hosted_Stop_Border_Agent(qsTargetId, TWN_Handle);
}

qapi_Status_t _qapi_TWN_Hosted_Receive_UDP_Data(uint8_t TargetID, qapi_TWN_Handle_t TWN_Handle, qapi_TWN_Hosted_Socket_Info_t *SocketInfo, uint16_t Length, uint8_t *Buffer)
{
    return(Mnl_qapi_TWN_Hosted_Receive_UDP_Data(TargetID, TWN_Handle, SocketInfo, Length, Buffer));
}

qapi_Status_t qapi_TWN_Hosted_Receive_UDP_Data(qapi_TWN_Handle_t TWN_Handle, qapi_TWN_Hosted_Socket_Info_t *SocketInfo, uint16_t Length, uint8_t *Buffer)
{
   return _qapi_TWN_Hosted_Receive_UDP_Data(qsTargetId, TWN_Handle, SocketInfo, Length, Buffer);
}

qapi_Status_t _qapi_TWN_Hosted_Enable_Logging(uint8_t TargetID)
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
    qsSize = 0;

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_TWN, QAPI_TWN_HOSTED_FILE_ID, QAPI_TWN_HOSTED_ENABLE_LOGGING_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
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

qapi_Status_t qapi_TWN_Hosted_Enable_Logging()
{
   return _qapi_TWN_Hosted_Enable_Logging(qsTargetId);
}

qapi_Status_t _qapi_TWN_Hosted_Disable_Logging(uint8_t TargetID)
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
    qsSize = 0;

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_TWN, QAPI_TWN_HOSTED_FILE_ID, QAPI_TWN_HOSTED_DISABLE_LOGGING_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
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

qapi_Status_t qapi_TWN_Hosted_Disable_Logging()
{
   return _qapi_TWN_Hosted_Disable_Logging(qsTargetId);
}
