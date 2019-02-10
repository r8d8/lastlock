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
#include "qapi_ble_cscs_common.h"
#include "qapi_ble_cscs_qz_cb.h"

SerStatus_t Handle_qapi_BLE_CSCS_Initialize_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_BLE_CSCS_Initialize_Service(BluetoothStackID, QZ_qapi_BLE_CSCS_Event_Callback_t_Handler, CallbackParameter, ServiceID);

        qsOutputLength = (4 + (ServiceID == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_INITIALIZE_SERVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Initialize_Service_Handle_Range(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_BLE_CSCS_Initialize_Service_Handle_Range(BluetoothStackID, QZ_qapi_BLE_CSCS_Event_Callback_t_Handler, CallbackParameter, ServiceID, ServiceHandleRange);

        qsOutputLength = (4 + (ServiceID == NULL ? 0 : 4) + (CalcPackedSize_qapi_BLE_GATT_Attribute_Handle_Group_t((qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_INITIALIZE_SERVICE_HANDLE_RANGE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Cleanup_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_BLE_CSCS_Cleanup_Service(BluetoothStackID, InstanceID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_CLEANUP_SERVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Query_Number_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_BLE_CSCS_Query_Number_Attributes();

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_QUERY_NUMBER_ATTRIBUTES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Read_Client_Configuration_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t ClientConfiguration;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&ClientConfiguration);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Read_Client_Configuration_Response(BluetoothStackID, InstanceID, TransactionID, ClientConfiguration);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_READ_CLIENT_CONFIGURATION_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Notify_CSC_Measurement(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_CSCS_CSC_Measurement_Data_t *MeasurementData = NULL;

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
        MeasurementData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CSCS_CSC_Measurement_Data_t));

        if(MeasurementData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_CSCS_CSC_Measurement_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_CSCS_CSC_Measurement_Data_t *)MeasurementData);
        }
    }
    else
        MeasurementData = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Notify_CSC_Measurement(BluetoothStackID, InstanceID, ConnectionID, MeasurementData);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_NOTIFY_CSC_MEASUREMENT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Set_CSC_Feature(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t SupportedFeatures;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&SupportedFeatures);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Set_CSC_Feature(BluetoothStackID, InstanceID, SupportedFeatures);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_SET_CSC_FEATURE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Query_CSC_Feature(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t *SupportedFeatures = NULL;

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
        SupportedFeatures = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SupportedFeatures == NULL)
            qsResult = ssAllocationError;
    }
    else
        SupportedFeatures= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Query_CSC_Feature(BluetoothStackID, InstanceID, SupportedFeatures);

        qsOutputLength = (4 + (SupportedFeatures == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_QUERY_CSC_FEATURE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SupportedFeatures);

         if((qsResult == ssSuccess) && (SupportedFeatures != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SupportedFeatures);
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

SerStatus_t Handle_qapi_BLE_CSCS_Set_Sensor_Location(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t SensorLocation;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&SensorLocation);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Set_Sensor_Location(BluetoothStackID, InstanceID, SensorLocation);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_SET_SENSOR_LOCATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Query_Sensor_Location(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *SensorLocation = NULL;

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
        SensorLocation = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(SensorLocation == NULL)
            qsResult = ssAllocationError;
    }
    else
        SensorLocation= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Query_Sensor_Location(BluetoothStackID, InstanceID, SensorLocation);

        qsOutputLength = (4 + (SensorLocation == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_QUERY_SENSOR_LOCATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SensorLocation);

         if((qsResult == ssSuccess) && (SensorLocation != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)SensorLocation);
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

SerStatus_t Handle_qapi_BLE_CSCS_SC_Control_Point_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_BLE_CSCS_SC_Control_Point_Response(BluetoothStackID, TransactionID, ErrorCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_SC_CONTROL_POINT_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Indicate_SC_Control_Point_Result(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_CSCS_SCCP_Command_Type_t CommandType;
    uint8_t ResponseCode;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ConnectionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&CommandType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ResponseCode);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Indicate_SC_Control_Point_Result(BluetoothStackID, InstanceID, ConnectionID, CommandType, ResponseCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_INDICATE_SC_CONTROL_POINT_RESULT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Indicate_Supported_Sensor_Locations(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_CSCS_SCCP_Supported_Sensor_Locations_t *SupportedSensorLocations = NULL;

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
        SupportedSensorLocations = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CSCS_SCCP_Supported_Sensor_Locations_t));

        if(SupportedSensorLocations == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_CSCS_SCCP_Supported_Sensor_Locations_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_CSCS_SCCP_Supported_Sensor_Locations_t *)SupportedSensorLocations);
        }
    }
    else
        SupportedSensorLocations = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Indicate_Supported_Sensor_Locations(BluetoothStackID, InstanceID, ConnectionID, SupportedSensorLocations);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_INDICATE_SUPPORTED_SENSOR_LOCATIONS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_CSCS_Decode_CSC_Measurement(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_CSCS_CSC_Measurement_Data_t *MeasurementData = NULL;

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
        MeasurementData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CSCS_CSC_Measurement_Data_t));

        if(MeasurementData == NULL)
            qsResult = ssAllocationError;
    }
    else
        MeasurementData= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Decode_CSC_Measurement(ValueLength, Value, MeasurementData);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_CSCS_CSC_Measurement_Data_t((qapi_BLE_CSCS_CSC_Measurement_Data_t *)MeasurementData)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_DECODE_CSC_MEASUREMENT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)MeasurementData);

         if((qsResult == ssSuccess) && (MeasurementData != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_CSCS_CSC_Measurement_Data_t(qsOutputBuffer, (qapi_BLE_CSCS_CSC_Measurement_Data_t *)MeasurementData);
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

SerStatus_t Handle_qapi_BLE_CSCS_Decode_SC_Control_Point_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_CSCS_SC_Control_Point_Response_Data_t *SCControlPointResponse = NULL;

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
        SCControlPointResponse = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CSCS_SC_Control_Point_Response_Data_t));

        if(SCControlPointResponse == NULL)
            qsResult = ssAllocationError;
    }
    else
        SCControlPointResponse= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Decode_SC_Control_Point_Response(ValueLength, Value, SCControlPointResponse);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_CSCS_SC_Control_Point_Response_Data_t((qapi_BLE_CSCS_SC_Control_Point_Response_Data_t *)SCControlPointResponse)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_DECODE_SC_CONTROL_POINT_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SCControlPointResponse);

         if((qsResult == ssSuccess) && (SCControlPointResponse != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_CSCS_SC_Control_Point_Response_Data_t(qsOutputBuffer, (qapi_BLE_CSCS_SC_Control_Point_Response_Data_t *)SCControlPointResponse);
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

SerStatus_t Handle_qapi_BLE_CSCS_Format_SC_Control_Point_Command(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    /* Create a temporary variable for the length of Buffer. */
    uint32_t qsTmp_BufferLength = 0;
    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    qapi_BLE_CSCS_SC_Control_Point_Format_Data_t *FormatData = NULL;
    uint32_t *BufferLength = NULL;
    uint8_t *Buffer = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        BufferLength = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(BufferLength == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)BufferLength);
        }
    }
    else
        BufferLength = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (BufferLength != NULL))
    {
        Buffer = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(*BufferLength)));

        if(Buffer == NULL)
            qsResult = ssAllocationError;
    }
    else
        Buffer= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        FormatData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_CSCS_SC_Control_Point_Format_Data_t));

        if(FormatData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_CSCS_SC_Control_Point_Format_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_CSCS_SC_Control_Point_Format_Data_t *)FormatData);
        }
    }
    else
        FormatData = NULL;

    if(BufferLength != NULL)
      qsTmp_BufferLength = *BufferLength;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_CSCS_Format_SC_Control_Point_Command(FormatData, BufferLength, Buffer);

        qsOutputLength = (4 + (BufferLength == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 2));

      if((BufferLength != NULL) && (Buffer != NULL))
      {
         if(qsTmp_BufferLength > *BufferLength)
            qsTmp_BufferLength = *BufferLength;
         qsOutputLength = qsOutputLength + ((qsTmp_BufferLength)*(1));
      }

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_CSCS_FILE_ID, QAPI_BLE_CSCS_FORMAT_SC_CONTROL_POINT_COMMAND_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)BufferLength);

         if((qsResult == ssSuccess) && (BufferLength != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)BufferLength);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Buffer);

         if((qsResult == ssSuccess) && (Buffer != NULL) && (BufferLength != NULL))
         {
             qsResult = PackedWrite_Array(qsOutputBuffer, (void *)Buffer, sizeof(uint8_t), qsTmp_BufferLength);
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
