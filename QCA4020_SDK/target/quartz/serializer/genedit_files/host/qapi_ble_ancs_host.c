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
#include "qapi_ble.h"
#include "qapi_ble_ancs_host_mnl.h"
#include "qapi_ble_ancs_common.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_ancstypes_common.h"

int _qapi_BLE_ANCS_Decode_Notification_Received_Data(uint8_t TargetID, uint32_t BufferLength, uint8_t *Buffer, qapi_BLE_ANCS_Notification_Received_Data_t *NotificationReceivedData)
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
    int qsRetVal = 0;

    /* Calculate size of packed function arguments. */
    qsSize = (4 + (QS_POINTER_HEADER_SIZE * 2));

    qsSize = qsSize + ((BufferLength)*(1));

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_ANCS_FILE_ID, QAPI_BLE_ANCS_DECODE_NOTIFICATION_RECEIVED_DATA_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&BufferLength);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Buffer);

        if((qsResult == ssSuccess) && (Buffer != NULL))
        {
            qsResult = PackedWrite_Array(&qsInputBuffer, (void *)Buffer, sizeof(uint8_t), BufferLength);
        }

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)NotificationReceivedData);

        if(qsResult == ssSuccess)
        {
            /* Send the command. */
            if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
            {
                if(qsOutputBuffer.Start != NULL)
                {
                    /* Unpack returned values. */
                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_int(&qsOutputBuffer, &qsBufferList, (int *)&qsRetVal);

                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);

                    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
                    {
                        qsResult = PackedRead_qapi_BLE_ANCS_Notification_Received_Data_t(&qsOutputBuffer, &qsBufferList, (qapi_BLE_ANCS_Notification_Received_Data_t *)NotificationReceivedData);
                    }

                    /* Set the return value to error if necessary. */
                    if(qsResult != ssSuccess)
                    {
                        qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
                    }
                }
                else
                {
                    qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
                }

                /* Free the output buffer. */
                FreePackedBuffer(&qsOutputBuffer);
            }
            else
            {
                qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
            }
        }
        else
        {
            qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
        }

        /* Free the input buffer. */
        FreePackedBuffer(&qsInputBuffer);
    }
    else
    {
        qsRetVal = QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR;
    }

    FreeBufferList(&qsBufferList);

    return(qsRetVal);
}

int qapi_BLE_ANCS_Decode_Notification_Received_Data(uint32_t BufferLength, uint8_t *Buffer, qapi_BLE_ANCS_Notification_Received_Data_t *NotificationReceivedData)
{
   return _qapi_BLE_ANCS_Decode_Notification_Received_Data(qsTargetId, BufferLength, Buffer, NotificationReceivedData);
}

int _qapi_BLE_ANCS_Encode_Notification_Attribute_Request(uint8_t TargetID, uint32_t NotificationUID, uint32_t NumberAttributes, qapi_BLE_ANCS_Notification_Attribute_Request_Data_t *NotificationAttributes, uint8_t **Buffer, uint32_t *TotalLength)
{
    return(Mnl_qapi_BLE_ANCS_Encode_Notification_Attribute_Request(TargetID, NotificationUID, NumberAttributes, NotificationAttributes, Buffer, TotalLength));
}

int qapi_BLE_ANCS_Encode_Notification_Attribute_Request(uint32_t NotificationUID, uint32_t NumberAttributes, qapi_BLE_ANCS_Notification_Attribute_Request_Data_t *NotificationAttributes, uint8_t **Buffer, uint32_t *TotalLength)
{
   return _qapi_BLE_ANCS_Encode_Notification_Attribute_Request(qsTargetId, NotificationUID, NumberAttributes, NotificationAttributes, Buffer, TotalLength);
}

int _qapi_BLE_ANCS_Encode_App_Attribute_Request(uint8_t TargetID, char *AppIdentifier, uint32_t NumberAttributes, qapi_BLE_ANCS_App_Attribute_Request_Data_t *AppAttributes, uint8_t **Buffer, uint32_t *TotalLength)
{
    return(Mnl_qapi_BLE_ANCS_Encode_App_Attribute_Request(TargetID, AppIdentifier, NumberAttributes, AppAttributes, Buffer, TotalLength));
}

int qapi_BLE_ANCS_Encode_App_Attribute_Request(char *AppIdentifier, uint32_t NumberAttributes, qapi_BLE_ANCS_App_Attribute_Request_Data_t *AppAttributes, uint8_t **Buffer, uint32_t *TotalLength)
{
   return _qapi_BLE_ANCS_Encode_App_Attribute_Request(qsTargetId, AppIdentifier, NumberAttributes, AppAttributes, Buffer, TotalLength);
}

boolean_t _qapi_BLE_ANCS_Is_Buffer_Complete(uint8_t TargetID, uint32_t BufferLength, uint8_t *Buffer, uint32_t NumberAttributesRequested)
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
    boolean_t qsRetVal = 0;

    /* Calculate size of packed function arguments. */
    qsSize = (8 + (QS_POINTER_HEADER_SIZE * 1));

    qsSize = qsSize + ((BufferLength)*(1));

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_ANCS_FILE_ID, QAPI_BLE_ANCS_IS_BUFFER_COMPLETE_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&BufferLength);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&NumberAttributesRequested);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)Buffer);

        if((qsResult == ssSuccess) && (Buffer != NULL))
        {
            qsResult = PackedWrite_Array(&qsInputBuffer, (void *)Buffer, sizeof(uint8_t), BufferLength);
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
                        qsRetVal = FALSE;
                    }
                }
                else
                {
                    qsRetVal = FALSE;
                }

                /* Free the output buffer. */
                FreePackedBuffer(&qsOutputBuffer);
            }
            else
            {
                qsRetVal = FALSE;
            }
        }
        else
        {
            qsRetVal = FALSE;
        }

        /* Free the input buffer. */
        FreePackedBuffer(&qsInputBuffer);
    }
    else
    {
        qsRetVal = FALSE;
    }

    FreeBufferList(&qsBufferList);

    return(qsRetVal);
}

boolean_t qapi_BLE_ANCS_Is_Buffer_Complete(uint32_t BufferLength, uint8_t *Buffer, uint32_t NumberAttributesRequested)
{
   return _qapi_BLE_ANCS_Is_Buffer_Complete(qsTargetId, BufferLength, Buffer, NumberAttributesRequested);
}

int _qapi_BLE_ANCS_Decode_Attribute_Data(uint8_t TargetID, uint32_t NumberAttributes, uint32_t RawDataLength, uint8_t *RawAttributeData, qapi_BLE_ANCS_Parsed_Attribute_Data_t *ParsedAttributeData)
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
    int qsRetVal = 0;

    /* Calculate size of packed function arguments. */
    qsSize = (8 + (QS_POINTER_HEADER_SIZE * 2));

    qsSize = qsSize + ((RawDataLength)*(1));

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_ANCS_FILE_ID, QAPI_BLE_ANCS_DECODE_ATTRIBUTE_DATA_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&NumberAttributes);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(&qsInputBuffer, (uint32_t *)&RawDataLength);

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)RawAttributeData);

        if((qsResult == ssSuccess) && (RawAttributeData != NULL))
        {
            qsResult = PackedWrite_Array(&qsInputBuffer, (void *)RawAttributeData, sizeof(uint8_t), RawDataLength);
        }

        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *)ParsedAttributeData);

        if(qsResult == ssSuccess)
        {
            /* Send the command. */
            if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
            {
                if(qsOutputBuffer.Start != NULL)
                {
                    /* Unpack returned values. */
                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_int(&qsOutputBuffer, &qsBufferList, (int *)&qsRetVal);

                    if(qsResult == ssSuccess)
                        qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);

                    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
                    {
                        qsResult = PackedRead_qapi_BLE_ANCS_Parsed_Attribute_Data_t(&qsOutputBuffer, &qsBufferList, (qapi_BLE_ANCS_Parsed_Attribute_Data_t *)ParsedAttributeData);
                    }

                    /* Set the return value to error if necessary. */
                    if(qsResult != ssSuccess)
                    {
                        qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
                    }
                }
                else
                {
                    qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
                }

                /* Free the output buffer. */
                FreePackedBuffer(&qsOutputBuffer);
            }
            else
            {
                qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
            }
        }
        else
        {
            qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;
        }

        /* Free the input buffer. */
        FreePackedBuffer(&qsInputBuffer);
    }
    else
    {
        qsRetVal = QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR;
    }

    FreeBufferList(&qsBufferList);

    return(qsRetVal);
}

int qapi_BLE_ANCS_Decode_Attribute_Data(uint32_t NumberAttributes, uint32_t RawDataLength, uint8_t *RawAttributeData, qapi_BLE_ANCS_Parsed_Attribute_Data_t *ParsedAttributeData)
{
   return _qapi_BLE_ANCS_Decode_Attribute_Data(qsTargetId, NumberAttributes, RawDataLength, RawAttributeData, ParsedAttributeData);
}

void _qapi_BLE_ANCS_Free_Parsed_Attribute_Data(uint8_t TargetID, qapi_BLE_ANCS_Parsed_Attribute_Data_t * ParsedAttributeData)
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

    /* Calculate size of packed function arguments. */
    qsSize = (CalcPackedSize_qapi_BLE_ANCS_Parsed_Attribute_Data_t((qapi_BLE_ANCS_Parsed_Attribute_Data_t *) ParsedAttributeData) + (QS_POINTER_HEADER_SIZE * 1));

    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_BLE, QAPI_BLE_ANCS_FILE_ID, QAPI_BLE_ANCS_FREE_PARSED_ATTRIBUTE_DATA_FUNCTION_ID, &qsInputBuffer, qsSize))
    {
        /* Write arguments packed. */
        if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(&qsInputBuffer, (void *) ParsedAttributeData);

        if((qsResult == ssSuccess) && ( ParsedAttributeData != NULL))
        {
            qsResult = PackedWrite_qapi_BLE_ANCS_Parsed_Attribute_Data_t(&qsInputBuffer, (qapi_BLE_ANCS_Parsed_Attribute_Data_t *) ParsedAttributeData);
        }

        if(qsResult == ssSuccess)
        {
            /* Send the command. */
            if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)
            {
                if(qsOutputBuffer.Start != NULL)
                {
                }
                else
                {
                    // Return type is void, no need to set any variables.
                }

                /* Free the output buffer. */
                FreePackedBuffer(&qsOutputBuffer);
            }
            else
            {
                // Return type is void, no need to set any variables.
            }
        }
        else
        {
            // Return type is void, no need to set any variables.
        }

        /* Free the input buffer. */
        FreePackedBuffer(&qsInputBuffer);
    }
    else
    {
        // Return type is void, no need to set any variables.
    }

    FreeBufferList(&qsBufferList);

}

void qapi_BLE_ANCS_Free_Parsed_Attribute_Data(qapi_BLE_ANCS_Parsed_Attribute_Data_t * ParsedAttributeData)
{
   _qapi_BLE_ANCS_Free_Parsed_Attribute_Data(qsTargetId,  ParsedAttributeData);
}
