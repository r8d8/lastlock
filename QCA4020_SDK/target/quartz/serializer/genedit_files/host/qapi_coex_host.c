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
#include "qapi_coex.h"
#include "qapi_coex_common.h"

qapi_Status_t _qapi_COEX_Configure(uint8_t TargetID, const qapi_COEX_Config_Data_t *config_Data)
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
    qsSize = (CalcPackedSize_qapi_COEX_Config_Data_t((qapi_COEX_Config_Data_t *)config_Data) + (QS_POINTER_HEADER_SIZE * 1));

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_COEX, QAPI_COEX_FILE_ID, QAPI_COEX_CONFIGURE_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)config_Data);

        if((qsResult == ssSuccess) && (config_Data != NULL))
        {
            qsResult = PackedWrite_qapi_COEX_Config_Data_t(&qsInputBuffer, (qapi_COEX_Config_Data_t *)config_Data);
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

qapi_Status_t qapi_COEX_Configure(const qapi_COEX_Config_Data_t *config_Data)
{
   return _qapi_COEX_Configure(qsTargetId, config_Data);
}

qapi_Status_t _qapi_COEX_Configure_Advanced(uint8_t TargetID, const qapi_COEX_Advanced_Config_Data_t *advanced_Config_Data)
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
    qsSize = (CalcPackedSize_qapi_COEX_Advanced_Config_Data_t((qapi_COEX_Advanced_Config_Data_t *)advanced_Config_Data) + (QS_POINTER_HEADER_SIZE * 1));

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_COEX, QAPI_COEX_FILE_ID, QAPI_COEX_CONFIGURE_ADVANCED_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)advanced_Config_Data);

        if((qsResult == ssSuccess) && (advanced_Config_Data != NULL))
        {
            qsResult = PackedWrite_qapi_COEX_Advanced_Config_Data_t(&qsInputBuffer, (qapi_COEX_Advanced_Config_Data_t *)advanced_Config_Data);
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

qapi_Status_t qapi_COEX_Configure_Advanced(const qapi_COEX_Advanced_Config_Data_t *advanced_Config_Data)
{
   return _qapi_COEX_Configure_Advanced(qsTargetId, advanced_Config_Data);
}

qapi_Status_t _qapi_COEX_Statistics_Enable(uint8_t TargetID, boolean enable, uint32 statistics_Mask, uint32 flags)
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
    qsSize = 12;

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_COEX, QAPI_COEX_FILE_ID, QAPI_COEX_STATISTICS_ENABLE_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&enable);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&statistics_Mask);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&flags);

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

qapi_Status_t qapi_COEX_Statistics_Enable(boolean enable, uint32 statistics_Mask, uint32 flags)
{
   return _qapi_COEX_Statistics_Enable(qsTargetId, enable, statistics_Mask, flags);
}

qapi_Status_t _qapi_COEX_Statistics_Get(uint8_t TargetID, qapi_COEX_Statistics_Data_t *statistics_Data, uint8 *statistics_Data_Length, uint32 statistics_Mask, boolean reset)
{
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    BufferListEntry_t *qsBufferList = NULL;
    SerStatus_t        qsResult = ssSuccess;
    uint32_t           qsIndex = 0;
    uint16_t           qsSize = 0;
    Boolean_t          qsPointerValid = FALSE;

    /* Create a temporary variable for the length of statistics_Data. */
    uint32_t qsTmp_statistics_Data_Length = 0;
    if (statistics_Data_Length != NULL)
        qsTmp_statistics_Data_Length = *statistics_Data_Length;

    UNUSED(qsIndex);
    UNUSED(qsPointerValid);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Calculate size of packed function arguments. */
    qsSize = (8 + CalcPackedSize_8((uint8_t *)statistics_Data_Length) + (QS_POINTER_HEADER_SIZE * 2));

    for (qsIndex = 0; qsIndex < *statistics_Data_Length; qsIndex++)
    {
        qsSize = qsSize + CalcPackedSize_qapi_COEX_Statistics_Data_t((qapi_COEX_Statistics_Data_t *)&statistics_Data[qsIndex]);
    }

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_COEX, QAPI_COEX_FILE_ID, QAPI_COEX_STATISTICS_GET_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&statistics_Mask);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&reset);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)statistics_Data_Length);

        if((qsResult == ssSuccess) && (statistics_Data_Length != NULL))
        {
            qsResult = PackedWrite_8(&qsInputBuffer, (uint8_t *)statistics_Data_Length);
        }

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)statistics_Data);

        if((qsResult == ssSuccess) && (statistics_Data != NULL) && (statistics_Data_Length != NULL))
        {
            for (qsIndex = 0; qsIndex < qsTmp_statistics_Data_Length; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedWrite_qapi_COEX_Statistics_Data_t(&qsInputBuffer, &((qapi_COEX_Statistics_Data_t *)statistics_Data)[qsIndex]);
            }
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

                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);

                    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
                    {
                        qsResult = PackedRead_8(&qsOutputBuffer, &qsBufferList, (uint8_t *)statistics_Data_Length);
                    }

                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);

                    if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (statistics_Data_Length != NULL))
                    {
                        if(qsTmp_statistics_Data_Length > *statistics_Data_Length)
                            qsTmp_statistics_Data_Length = *statistics_Data_Length;
                        for (qsIndex = 0; qsIndex < qsTmp_statistics_Data_Length; qsIndex++)
                        {
                            if(qsResult == ssSuccess)
                                qsResult = PackedRead_qapi_COEX_Statistics_Data_t(&qsOutputBuffer, &qsBufferList, &((qapi_COEX_Statistics_Data_t *)statistics_Data)[qsIndex]);
                        }
                    }

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

qapi_Status_t qapi_COEX_Statistics_Get(qapi_COEX_Statistics_Data_t *statistics_Data, uint8 *statistics_Data_Length, uint32 statistics_Mask, boolean reset)
{
   return _qapi_COEX_Statistics_Get(qsTargetId, statistics_Data, statistics_Data_Length, statistics_Mask, reset);
}
