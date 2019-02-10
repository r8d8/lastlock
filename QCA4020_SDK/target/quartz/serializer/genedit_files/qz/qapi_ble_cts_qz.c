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
#include "idlist.h"
#include "qsCommon.h"
#include "qsQuartz.h"
#include "qsPack.h"
#include "qapi_ble.h"
#include "qapi_ble_cts_common.h"
#include "qapi_ble_cts_qz_cb.h"

SerStatus_t Handle_qapi_BLE_CTS_Initialize_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t CallbackParameter;
    uint32_t *ServiceID = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ServiceID = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(ServiceID == NULL)
            qsResult = ssAllocationError;
    }
    else
        ServiceID= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Initialize_Service(BluetoothStackID, QZ_qapi_BLE_CTS_Event_Callback_t_Handler, CallbackParameter, ServiceID);

        qsOutputLength = (4 + (ServiceID == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_INITIALIZE_SERVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ServiceID);

         if((qsResult == ssSuccess) && (ServiceID != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)ServiceID);
         }

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Initialize_Service_Handle_Range(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t CallbackParameter;
    uint32_t *ServiceID = NULL;
    qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ServiceID = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(ServiceID == NULL)
            qsResult = ssAllocationError;
    }
    else
        ServiceID= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ServiceHandleRange = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

        if(ServiceHandleRange == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GATT_Attribute_Handle_Group_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange);
        }
    }
    else
        ServiceHandleRange = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Initialize_Service_Handle_Range(BluetoothStackID, QZ_qapi_BLE_CTS_Event_Callback_t_Handler, CallbackParameter, ServiceID, ServiceHandleRange);

        qsOutputLength = (4 + (ServiceID == NULL ? 0 : 4) + (CalcPackedSize_qapi_BLE_GATT_Attribute_Handle_Group_t((qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_INITIALIZE_SERVICE_HANDLE_RANGE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ServiceID);

         if((qsResult == ssSuccess) && (ServiceID != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)ServiceID);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ServiceHandleRange);

         if((qsResult == ssSuccess) && (ServiceHandleRange != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_GATT_Attribute_Handle_Group_t(qsOutputBuffer, (qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange);
         }

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Initialize_Service_Flags(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t Flags;
    uint32_t CallbackParameter;
    uint32_t *ServiceID = NULL;
    qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Flags);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ServiceID = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(ServiceID == NULL)
            qsResult = ssAllocationError;
    }
    else
        ServiceID= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ServiceHandleRange = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

        if(ServiceHandleRange == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GATT_Attribute_Handle_Group_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange);
        }
    }
    else
        ServiceHandleRange = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Initialize_Service_Flags(BluetoothStackID, Flags, QZ_qapi_BLE_CTS_Event_Callback_t_Handler, CallbackParameter, ServiceID, ServiceHandleRange);

        qsOutputLength = (4 + (ServiceID == NULL ? 0 : 4) + (CalcPackedSize_qapi_BLE_GATT_Attribute_Handle_Group_t((qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_INITIALIZE_SERVICE_FLAGS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ServiceID);

         if((qsResult == ssSuccess) && (ServiceID != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)ServiceID);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ServiceHandleRange);

         if((qsResult == ssSuccess) && (ServiceHandleRange != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_GATT_Attribute_Handle_Group_t(qsOutputBuffer, (qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange);
         }

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Cleanup_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t InstanceID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Cleanup_Service(BluetoothStackID, InstanceID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_CLEANUP_SERVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Query_Number_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    unsigned int qsRetVal = 0;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Query_Number_Attributes();

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_QUERY_NUMBER_ATTRIBUTES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Current_Time_Read_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    qapi_BLE_CTS_Current_Time_Data_t *Current_Time = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Current_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Current_Time_Data_t));

        if(Current_Time == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_CTS_Current_Time_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_CTS_Current_Time_Data_t *)Current_Time);
        }
    }
    else
        Current_Time = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Current_Time_Read_Request_Response(BluetoothStackID, TransactionID, Current_Time);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_CURRENT_TIME_READ_REQUEST_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Current_Time_Read_Request_Error_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint8_t ErrorCode;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Current_Time_Read_Request_Error_Response(BluetoothStackID, TransactionID, ErrorCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_CURRENT_TIME_READ_REQUEST_ERROR_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Current_Time_Write_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint8_t ErrorCode;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Current_Time_Write_Request_Response(BluetoothStackID, TransactionID, ErrorCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_CURRENT_TIME_WRITE_REQUEST_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Set_Local_Time_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_CTS_Local_Time_Information_Data_t *Local_Time = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Local_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Local_Time_Information_Data_t));

        if(Local_Time == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_CTS_Local_Time_Information_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_CTS_Local_Time_Information_Data_t *)Local_Time);
        }
    }
    else
        Local_Time = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Set_Local_Time_Information(BluetoothStackID, InstanceID, Local_Time);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_SET_LOCAL_TIME_INFORMATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Query_Local_Time_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_CTS_Local_Time_Information_Data_t *Local_Time = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Local_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Local_Time_Information_Data_t));

        if(Local_Time == NULL)
            qsResult = ssAllocationError;
    }
    else
        Local_Time= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Query_Local_Time_Information(BluetoothStackID, InstanceID, Local_Time);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_CTS_Local_Time_Information_Data_t((qapi_BLE_CTS_Local_Time_Information_Data_t *)Local_Time)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_QUERY_LOCAL_TIME_INFORMATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Local_Time);

         if((qsResult == ssSuccess) && (Local_Time != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_CTS_Local_Time_Information_Data_t(qsOutputBuffer, (qapi_BLE_CTS_Local_Time_Information_Data_t *)Local_Time);
         }

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Local_Time_Information_Write_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint8_t ErrorCode;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Local_Time_Information_Write_Request_Response(BluetoothStackID, TransactionID, ErrorCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_LOCAL_TIME_INFORMATION_WRITE_REQUEST_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Reference_Time_Information_Read_Request_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    qapi_BLE_CTS_Reference_Time_Information_Data_t *Reference_Time = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Reference_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Reference_Time_Information_Data_t));

        if(Reference_Time == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_CTS_Reference_Time_Information_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_CTS_Reference_Time_Information_Data_t *)Reference_Time);
        }
    }
    else
        Reference_Time = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Reference_Time_Information_Read_Request_Response(BluetoothStackID, TransactionID, Reference_Time);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_REFERENCE_TIME_INFORMATION_READ_REQUEST_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Reference_Time_Information_Read_Request_Error_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint8_t ErrorCode;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Reference_Time_Information_Read_Request_Error_Response(BluetoothStackID, TransactionID, ErrorCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_REFERENCE_TIME_INFORMATION_READ_REQUEST_ERROR_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Read_Client_Configuration_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t TransactionID;
    uint16_t Client_Configuration;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Client_Configuration);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Read_Client_Configuration_Response(BluetoothStackID, InstanceID, TransactionID, Client_Configuration);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_READ_CLIENT_CONFIGURATION_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Notify_Current_Time(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t ConnectionID;
    qapi_BLE_CTS_Current_Time_Data_t *Current_Time = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ConnectionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Current_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Current_Time_Data_t));

        if(Current_Time == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_CTS_Current_Time_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_CTS_Current_Time_Data_t *)Current_Time);
        }
    }
    else
        Current_Time = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Notify_Current_Time(BluetoothStackID, InstanceID, ConnectionID, Current_Time);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_NOTIFY_CURRENT_TIME_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Format_Current_Time(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    qapi_BLE_CTS_Current_Time_Data_t *Current_Time = NULL;
    uint32_t BufferLength;
    uint8_t *Buffer = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BufferLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Buffer = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(BufferLength)));

        if(Buffer == NULL)
            qsResult = ssAllocationError;
    }
    else
        Buffer= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Current_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Current_Time_Data_t));

        if(Current_Time == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_CTS_Current_Time_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_CTS_Current_Time_Data_t *)Current_Time);
        }
    }
    else
        Current_Time = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Format_Current_Time(Current_Time, BufferLength, Buffer);

        qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      if(Buffer != NULL)
         qsOutputLength = qsOutputLength + ((BufferLength)*(1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_FORMAT_CURRENT_TIME_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Buffer);

         if((qsResult == ssSuccess) && (Buffer != NULL))
         {
             qsResult = PackedWrite_Array(qsOutputBuffer, (void *)Buffer, sizeof(uint8_t), BufferLength);
         }

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Decode_Current_Time(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t ValueLength;
    uint8_t *Value = NULL;
    qapi_BLE_CTS_Current_Time_Data_t *Current_Time = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ValueLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Value = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(ValueLength)));

        if(Value == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Value, sizeof(uint8_t), ValueLength);
        }
    }
    else
        Value = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Current_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Current_Time_Data_t));

        if(Current_Time == NULL)
            qsResult = ssAllocationError;
    }
    else
        Current_Time= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Decode_Current_Time(ValueLength, Value, Current_Time);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_CTS_Current_Time_Data_t((qapi_BLE_CTS_Current_Time_Data_t *)Current_Time)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_DECODE_CURRENT_TIME_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Current_Time);

         if((qsResult == ssSuccess) && (Current_Time != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_CTS_Current_Time_Data_t(qsOutputBuffer, (qapi_BLE_CTS_Current_Time_Data_t *)Current_Time);
         }

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Format_Local_Time_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    qapi_BLE_CTS_Local_Time_Information_Data_t *Local_Time = NULL;
    uint32_t BufferLength;
    uint8_t *Buffer = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BufferLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Buffer = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(BufferLength)));

        if(Buffer == NULL)
            qsResult = ssAllocationError;
    }
    else
        Buffer= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Local_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Local_Time_Information_Data_t));

        if(Local_Time == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_CTS_Local_Time_Information_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_CTS_Local_Time_Information_Data_t *)Local_Time);
        }
    }
    else
        Local_Time = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Format_Local_Time_Information(Local_Time, BufferLength, Buffer);

        qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      if(Buffer != NULL)
         qsOutputLength = qsOutputLength + ((BufferLength)*(1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_FORMAT_LOCAL_TIME_INFORMATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Buffer);

         if((qsResult == ssSuccess) && (Buffer != NULL))
         {
             qsResult = PackedWrite_Array(qsOutputBuffer, (void *)Buffer, sizeof(uint8_t), BufferLength);
         }

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Decode_Local_Time_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t ValueLength;
    uint8_t *Value = NULL;
    qapi_BLE_CTS_Local_Time_Information_Data_t *Local_Time = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ValueLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Value = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(ValueLength)));

        if(Value == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Value, sizeof(uint8_t), ValueLength);
        }
    }
    else
        Value = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Local_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Local_Time_Information_Data_t));

        if(Local_Time == NULL)
            qsResult = ssAllocationError;
    }
    else
        Local_Time= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Decode_Local_Time_Information(ValueLength, Value, Local_Time);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_CTS_Local_Time_Information_Data_t((qapi_BLE_CTS_Local_Time_Information_Data_t *)Local_Time)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_DECODE_LOCAL_TIME_INFORMATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Local_Time);

         if((qsResult == ssSuccess) && (Local_Time != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_CTS_Local_Time_Information_Data_t(qsOutputBuffer, (qapi_BLE_CTS_Local_Time_Information_Data_t *)Local_Time);
         }

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_CTS_Decode_Reference_Time_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t ValueLength;
    uint8_t *Value = NULL;
    qapi_BLE_CTS_Reference_Time_Information_Data_t *Reference_Time = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ValueLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Value = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(ValueLength)));

        if(Value == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Value, sizeof(uint8_t), ValueLength);
        }
    }
    else
        Value = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Reference_Time = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CTS_Reference_Time_Information_Data_t));

        if(Reference_Time == NULL)
            qsResult = ssAllocationError;
    }
    else
        Reference_Time= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CTS_Decode_Reference_Time_Information(ValueLength, Value, Reference_Time);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_CTS_Reference_Time_Information_Data_t((qapi_BLE_CTS_Reference_Time_Information_Data_t *)Reference_Time)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CTS_FILE_ID, QAPI_BLE_CTS_DECODE_REFERENCE_TIME_INFORMATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Reference_Time);

         if((qsResult == ssSuccess) && (Reference_Time != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_CTS_Reference_Time_Information_Data_t(qsOutputBuffer, (qapi_BLE_CTS_Reference_Time_Information_Data_t *)Reference_Time);
         }

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}
