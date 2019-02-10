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
#include "qapi_ble_hids_common.h"
#include "qapi_ble_hids_qz_cb.h"

SerStatus_t Handle_qapi_BLE_HIDS_Initialize_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Flags;
    qapi_BLE_HIDS_HID_Information_Data_t *HIDInformation = NULL;
    uint32_t NumIncludedServices;
    uint32_t *ServiceIDList = NULL;
    uint32_t NumExternalReportReferences;
    qapi_BLE_GATT_UUID_t *ReferenceUUID = NULL;
    uint32_t NumReports;
    qapi_BLE_HIDS_Report_Reference_Data_t *ReportReference = NULL;
    uint32_t CallbackParameter;
    uint32_t *ServiceID = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Flags);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumIncludedServices);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumExternalReportReferences);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumReports);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ServiceIDList = AllocateBufferListEntry(&qsBufferList, (sizeof(uint32_t)*(NumIncludedServices)));

        if(ServiceIDList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)ServiceIDList, sizeof(uint32_t), NumIncludedServices);
        }
    }
    else
        ServiceIDList = NULL;

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
        HIDInformation = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HIDS_HID_Information_Data_t));

        if(HIDInformation == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_HIDS_HID_Information_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_HIDS_HID_Information_Data_t *)HIDInformation);
        }
    }
    else
        HIDInformation = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ReferenceUUID = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GATT_UUID_t)*(NumExternalReportReferences)));

        if(ReferenceUUID == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < NumExternalReportReferences; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_GATT_UUID_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_GATT_UUID_t *)ReferenceUUID)[qsIndex]);
            }
        }
    }
    else
        ReferenceUUID = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ReportReference = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_HIDS_Report_Reference_Data_t)*(NumReports)));

        if(ReportReference == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < NumReports; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_HIDS_Report_Reference_Data_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_HIDS_Report_Reference_Data_t *)ReportReference)[qsIndex]);
            }
        }
    }
    else
        ReportReference = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Initialize_Service(BluetoothStackID, Flags, HIDInformation, NumIncludedServices, ServiceIDList, NumExternalReportReferences, ReferenceUUID, NumReports, ReportReference, QZ_qapi_BLE_HIDS_Event_Callback_t_Handler, CallbackParameter, ServiceID);

        qsOutputLength = (4 + (ServiceID == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_INITIALIZE_SERVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Initialize_Service_Handle_Range(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Flags;
    qapi_BLE_HIDS_HID_Information_Data_t *HIDInformation = NULL;
    uint32_t NumIncludedServices;
    uint32_t *ServiceIDList = NULL;
    uint32_t NumExternalReportReferences;
    qapi_BLE_GATT_UUID_t *ReferenceUUID = NULL;
    uint32_t NumReports;
    qapi_BLE_HIDS_Report_Reference_Data_t *ReportReference = NULL;
    uint32_t CallbackParameter;
    uint32_t *ServiceID = NULL;
    qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Flags);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumIncludedServices);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumExternalReportReferences);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumReports);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ServiceIDList = AllocateBufferListEntry(&qsBufferList, (sizeof(uint32_t)*(NumIncludedServices)));

        if(ServiceIDList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)ServiceIDList, sizeof(uint32_t), NumIncludedServices);
        }
    }
    else
        ServiceIDList = NULL;

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
        HIDInformation = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HIDS_HID_Information_Data_t));

        if(HIDInformation == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_HIDS_HID_Information_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_HIDS_HID_Information_Data_t *)HIDInformation);
        }
    }
    else
        HIDInformation = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ReferenceUUID = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GATT_UUID_t)*(NumExternalReportReferences)));

        if(ReferenceUUID == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < NumExternalReportReferences; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_GATT_UUID_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_GATT_UUID_t *)ReferenceUUID)[qsIndex]);
            }
        }
    }
    else
        ReferenceUUID = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ReportReference = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_HIDS_Report_Reference_Data_t)*(NumReports)));

        if(ReportReference == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < NumReports; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_HIDS_Report_Reference_Data_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_HIDS_Report_Reference_Data_t *)ReportReference)[qsIndex]);
            }
        }
    }
    else
        ReportReference = NULL;

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
        qsRetVal = qapi_BLE_HIDS_Initialize_Service_Handle_Range(BluetoothStackID, Flags, HIDInformation, NumIncludedServices, ServiceIDList, NumExternalReportReferences, ReferenceUUID, NumReports, ReportReference, QZ_qapi_BLE_HIDS_Event_Callback_t_Handler, CallbackParameter, ServiceID, ServiceHandleRange);

        qsOutputLength = (4 + (ServiceID == NULL ? 0 : 4) + (CalcPackedSize_qapi_BLE_GATT_Attribute_Handle_Group_t((qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleRange)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_INITIALIZE_SERVICE_HANDLE_RANGE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Cleanup_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_BLE_HIDS_Cleanup_Service(BluetoothStackID, InstanceID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_CLEANUP_SERVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Query_Number_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t qsRetVal = 0;

    /* Function parameters. */
    uint8_t Flags;
    uint32_t NumIncludedServices;
    uint32_t NumExternalReportReferences;
    uint32_t NumReports;
    qapi_BLE_HIDS_Report_Reference_Data_t *ReportReference = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Flags);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumIncludedServices);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumExternalReportReferences);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumReports);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ReportReference = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_HIDS_Report_Reference_Data_t)*(NumReports)));

        if(ReportReference == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < NumReports; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_HIDS_Report_Reference_Data_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_HIDS_Report_Reference_Data_t *)ReportReference)[qsIndex]);
            }
        }
    }
    else
        ReportReference = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Query_Number_Attributes(Flags, NumIncludedServices, NumExternalReportReferences, NumReports, ReportReference);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_QUERY_NUMBER_ATTRIBUTES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_HIDS_Read_Client_Configuration_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_BLE_HIDS_Read_Client_Configuration_Response(BluetoothStackID, InstanceID, TransactionID, Client_Configuration);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_READ_CLIENT_CONFIGURATION_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Get_Protocol_Mode_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ErrorCode;
    qapi_BLE_HIDS_Protocol_Mode_t CurrentProtocolMode;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&CurrentProtocolMode);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Get_Protocol_Mode_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, CurrentProtocolMode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_GET_PROTOCOL_MODE_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Get_Report_Map_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ErrorCode;
    uint32_t ReportMapLength;
    uint8_t *ReportMap = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ReportMapLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ReportMap = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(ReportMapLength)));

        if(ReportMap == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)ReportMap, sizeof(uint8_t), ReportMapLength);
        }
    }
    else
        ReportMap = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Get_Report_Map_Response(BluetoothStackID, InstanceID, TransactionID, ErrorCode, ReportMapLength, ReportMap);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_GET_REPORT_MAP_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Get_Report_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_HIDS_Report_Type_t ReportType;
    qapi_BLE_HIDS_Report_Reference_Data_t *ReportReferenceData = NULL;
    uint8_t ErrorCode;
    uint32_t ReportLength;
    uint8_t *Report = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&ReportType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ReportLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Report = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(ReportLength)));

        if(Report == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Report, sizeof(uint8_t), ReportLength);
        }
    }
    else
        Report = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ReportReferenceData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HIDS_Report_Reference_Data_t));

        if(ReportReferenceData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_HIDS_Report_Reference_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_HIDS_Report_Reference_Data_t *)ReportReferenceData);
        }
    }
    else
        ReportReferenceData = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Get_Report_Response(BluetoothStackID, InstanceID, TransactionID, ReportType, ReportReferenceData, ErrorCode, ReportLength, Report);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_GET_REPORT_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Set_Report_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_HIDS_Report_Type_t ReportType;
    qapi_BLE_HIDS_Report_Reference_Data_t *ReportReferenceData = NULL;
    uint8_t ErrorCode;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TransactionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&ReportType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ErrorCode);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ReportReferenceData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HIDS_Report_Reference_Data_t));

        if(ReportReferenceData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_HIDS_Report_Reference_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_HIDS_Report_Reference_Data_t *)ReportReferenceData);
        }
    }
    else
        ReportReferenceData = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Set_Report_Response(BluetoothStackID, InstanceID, TransactionID, ReportType, ReportReferenceData, ErrorCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_SET_REPORT_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Notify_Input_Report(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_HIDS_Report_Type_t ReportType;
    qapi_BLE_HIDS_Report_Reference_Data_t *ReportReferenceData = NULL;
    uint16_t InputReportLength;
    uint8_t *InputReportData = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&InstanceID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ConnectionID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&ReportType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&InputReportLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        InputReportData = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(InputReportLength)));

        if(InputReportData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)InputReportData, sizeof(uint8_t), InputReportLength);
        }
    }
    else
        InputReportData = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ReportReferenceData = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_HIDS_Report_Reference_Data_t)*(InputReportLength)));

        if(ReportReferenceData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < InputReportLength; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_HIDS_Report_Reference_Data_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_HIDS_Report_Reference_Data_t *)ReportReferenceData)[qsIndex]);
            }
        }
    }
    else
        ReportReferenceData = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Notify_Input_Report(BluetoothStackID, InstanceID, ConnectionID, ReportType, ReportReferenceData, InputReportLength, InputReportData);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_NOTIFY_INPUT_REPORT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Decode_HID_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_HIDS_HID_Information_Data_t *HIDSHIDInformation = NULL;

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
        HIDSHIDInformation = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HIDS_HID_Information_Data_t));

        if(HIDSHIDInformation == NULL)
            qsResult = ssAllocationError;
    }
    else
        HIDSHIDInformation= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Decode_HID_Information(ValueLength, Value, HIDSHIDInformation);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_HIDS_HID_Information_Data_t((qapi_BLE_HIDS_HID_Information_Data_t *)HIDSHIDInformation)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_DECODE_HID_INFORMATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)HIDSHIDInformation);

         if((qsResult == ssSuccess) && (HIDSHIDInformation != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_HIDS_HID_Information_Data_t(qsOutputBuffer, (qapi_BLE_HIDS_HID_Information_Data_t *)HIDSHIDInformation);
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

SerStatus_t Handle_qapi_BLE_HIDS_Decode_Report_Reference(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_HIDS_Report_Reference_Data_t *ReportReferenceData = NULL;

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
        ReportReferenceData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HIDS_Report_Reference_Data_t));

        if(ReportReferenceData == NULL)
            qsResult = ssAllocationError;
    }
    else
        ReportReferenceData= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Decode_Report_Reference(ValueLength, Value, ReportReferenceData);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_HIDS_Report_Reference_Data_t((qapi_BLE_HIDS_Report_Reference_Data_t *)ReportReferenceData)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_DECODE_REPORT_REFERENCE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ReportReferenceData);

         if((qsResult == ssSuccess) && (ReportReferenceData != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_HIDS_Report_Reference_Data_t(qsOutputBuffer, (qapi_BLE_HIDS_Report_Reference_Data_t *)ReportReferenceData);
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

SerStatus_t Handle_qapi_BLE_HIDS_Decode_External_Report_Reference(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_GATT_UUID_t *ExternalReportReferenceUUID = NULL;

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
        ExternalReportReferenceUUID = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GATT_UUID_t));

        if(ExternalReportReferenceUUID == NULL)
            qsResult = ssAllocationError;
    }
    else
        ExternalReportReferenceUUID= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Decode_External_Report_Reference(ValueLength, Value, ExternalReportReferenceUUID);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_GATT_UUID_t((qapi_BLE_GATT_UUID_t *)ExternalReportReferenceUUID)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_DECODE_EXTERNAL_REPORT_REFERENCE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ExternalReportReferenceUUID);

         if((qsResult == ssSuccess) && (ExternalReportReferenceUUID != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_GATT_UUID_t(qsOutputBuffer, (qapi_BLE_GATT_UUID_t *)ExternalReportReferenceUUID);
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

SerStatus_t Handle_qapi_BLE_HIDS_Format_Protocol_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_HIDS_Protocol_Mode_t ProtocolMode;
    uint32_t BufferLength;
    uint8_t *Buffer = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&ProtocolMode);

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

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Format_Protocol_Mode(ProtocolMode, BufferLength, Buffer);

        qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      if(Buffer != NULL)
         qsOutputLength = qsOutputLength + ((BufferLength)*(1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_FORMAT_PROTOCOL_MODE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HIDS_Format_Control_Point_Command(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_HIDS_Control_Point_Command_t Command;
    uint32_t BufferLength;
    uint8_t *Buffer = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&Command);

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

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HIDS_Format_Control_Point_Command(Command, BufferLength, Buffer);

        qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      if(Buffer != NULL)
         qsOutputLength = qsOutputLength + ((BufferLength)*(1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HIDS_FILE_ID, QAPI_BLE_HIDS_FORMAT_CONTROL_POINT_COMMAND_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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
