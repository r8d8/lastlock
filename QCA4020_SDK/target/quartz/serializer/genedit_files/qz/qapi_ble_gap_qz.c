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
#include "qapi_ble_gap_qz_mnl.h"
#include "qapi_ble_gap_common.h"
#include "qapi_ble_gap_qz_cb.h"

SerStatus_t Handle_qapi_BLE_GAP_Query_Local_BD_ADDR(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t *BD_ADDR = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        BD_ADDR = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(BD_ADDR == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)BD_ADDR);
        }
    }
    else
        BD_ADDR = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_Query_Local_BD_ADDR(BluetoothStackID, BD_ADDR);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_BD_ADDR_t((qapi_BLE_BD_ADDR_t *)BD_ADDR)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_QUERY_LOCAL_BD_ADDR_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)BD_ADDR);

         if((qsResult == ssSuccess) && (BD_ADDR != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_BD_ADDR_t(qsOutputBuffer, (qapi_BLE_BD_ADDR_t *)BD_ADDR);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t ScanInterval;
    uint32_t ScanWindow;
    qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy;
    qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType;
    qapi_BLE_BD_ADDR_t *RemoteDevice = NULL;
    qapi_BLE_GAP_LE_Address_Type_t LocalAddressType;
    qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ScanInterval);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ScanWindow);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&InitatorFilterPolicy);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&RemoteAddressType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&LocalAddressType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RemoteDevice = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(RemoteDevice == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)RemoteDevice);
        }
    }
    else
        RemoteDevice = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ConnectionParameters = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));

        if(ConnectionParameters == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Connection_Parameters_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Connection_Parameters_t *)ConnectionParameters);
        }
    }
    else
        ConnectionParameters = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Create_Connection(BluetoothStackID, ScanInterval, ScanWindow, InitatorFilterPolicy, RemoteAddressType, RemoteDevice, LocalAddressType, ConnectionParameters, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_CREATE_CONNECTION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Cancel_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Cancel_Create_Connection(BluetoothStackID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_CANCEL_CREATE_CONNECTION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Disconnect(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Disconnect(BluetoothStackID, BD_ADDR);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_DISCONNECT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Read_Remote_Features(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Read_Remote_Features(BluetoothStackID, BD_ADDR);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_READ_REMOTE_FEATURES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Perform_Scan(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_GAP_LE_Scan_Type_t ScanType;
    uint32_t ScanInterval;
    uint32_t ScanWindow;
    qapi_BLE_GAP_LE_Address_Type_t LocalAddressType;
    qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy;
    boolean_t FilterDuplicates;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&ScanType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ScanInterval);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ScanWindow);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&LocalAddressType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&FilterPolicy);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&FilterDuplicates);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Perform_Scan(BluetoothStackID, ScanType, ScanInterval, ScanWindow, LocalAddressType, FilterPolicy, FilterDuplicates, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_PERFORM_SCAN_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Cancel_Scan(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Cancel_Scan(BluetoothStackID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_CANCEL_SCAN_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_BLE_GAP_LE_Set_Advertising_Data(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_BLE_GAP_LE_Convert_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_BLE_GAP_LE_Convert_Advertising_Data(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_BLE_GAP_LE_Parse_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_BLE_GAP_LE_Parse_Advertising_Data(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_BLE_GAP_LE_Set_Scan_Response_Data(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_BLE_GAP_LE_Convert_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_BLE_GAP_LE_Convert_Scan_Response_Data(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_BLE_GAP_LE_Parse_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_BLE_GAP_LE_Parse_Scan_Response_Data(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_BLE_GAP_LE_Advertising_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    boolean_t EnableScanResponse;
    qapi_BLE_GAP_LE_Advertising_Parameters_t *GAP_LE_Advertising_Parameters = NULL;
    qapi_BLE_GAP_LE_Connectability_Parameters_t *GAP_LE_Connectability_Parameters = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&EnableScanResponse);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        GAP_LE_Advertising_Parameters = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Advertising_Parameters_t));

        if(GAP_LE_Advertising_Parameters == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Advertising_Parameters_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Advertising_Parameters_t *)GAP_LE_Advertising_Parameters);
        }
    }
    else
        GAP_LE_Advertising_Parameters = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        GAP_LE_Connectability_Parameters = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Connectability_Parameters_t));

        if(GAP_LE_Connectability_Parameters == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Connectability_Parameters_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Connectability_Parameters_t *)GAP_LE_Connectability_Parameters);
        }
    }
    else
        GAP_LE_Connectability_Parameters = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Advertising_Enable(BluetoothStackID, EnableScanResponse, GAP_LE_Advertising_Parameters, GAP_LE_Connectability_Parameters, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_ADVERTISING_ENABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Advertising_Disable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Advertising_Disable(BluetoothStackID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_ADVERTISING_DISABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Wake_On_Scan_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    boolean_t WakeOnScanRequestEnabled;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&WakeOnScanRequestEnabled);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Wake_On_Scan_Request(BluetoothStackID, WakeOnScanRequestEnabled);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_WAKE_ON_SCAN_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Generate_Non_Resolvable_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t *NonResolvableAddress_Result = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        NonResolvableAddress_Result = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(NonResolvableAddress_Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        NonResolvableAddress_Result= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Generate_Non_Resolvable_Address(BluetoothStackID, NonResolvableAddress_Result);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_BD_ADDR_t((qapi_BLE_BD_ADDR_t *)NonResolvableAddress_Result)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_GENERATE_NON_RESOLVABLE_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)NonResolvableAddress_Result);

         if((qsResult == ssSuccess) && (NonResolvableAddress_Result != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_BD_ADDR_t(qsOutputBuffer, (qapi_BLE_BD_ADDR_t *)NonResolvableAddress_Result);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Generate_Static_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t *StaticAddress_Result = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StaticAddress_Result = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(StaticAddress_Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        StaticAddress_Result= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Generate_Static_Address(BluetoothStackID, StaticAddress_Result);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_BD_ADDR_t((qapi_BLE_BD_ADDR_t *)StaticAddress_Result)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_GENERATE_STATIC_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StaticAddress_Result);

         if((qsResult == ssSuccess) && (StaticAddress_Result != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_BD_ADDR_t(qsOutputBuffer, (qapi_BLE_BD_ADDR_t *)StaticAddress_Result);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Generate_Resolvable_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_Encryption_Key_t *IRK = NULL;
    qapi_BLE_BD_ADDR_t *ResolvableAddress_Result = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        IRK = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Encryption_Key_t));

        if(IRK == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)IRK);
        }
    }
    else
        IRK = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ResolvableAddress_Result = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(ResolvableAddress_Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        ResolvableAddress_Result= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Generate_Resolvable_Address(BluetoothStackID, IRK, ResolvableAddress_Result);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_BD_ADDR_t((qapi_BLE_BD_ADDR_t *)ResolvableAddress_Result)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_GENERATE_RESOLVABLE_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ResolvableAddress_Result);

         if((qsResult == ssSuccess) && (ResolvableAddress_Result != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_BD_ADDR_t(qsOutputBuffer, (qapi_BLE_BD_ADDR_t *)ResolvableAddress_Result);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Resolve_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    boolean_t qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    qapi_BLE_Encryption_Key_t *IRK = NULL;
    qapi_BLE_BD_ADDR_t ResolvableAddress;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&ResolvableAddress);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        IRK = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Encryption_Key_t));

        if(IRK == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)IRK);
        }
    }
    else
        IRK = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Resolve_Address(BluetoothStackID, IRK, ResolvableAddress);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_RESOLVE_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Random_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t RandomAddress;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&RandomAddress);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Random_Address(BluetoothStackID, RandomAddress);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_RANDOM_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Add_Device_To_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries = NULL;
    uint32_t *AddedDeviceCount = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&DeviceCount);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        AddedDeviceCount = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(AddedDeviceCount == NULL)
            qsResult = ssAllocationError;
    }
    else
        AddedDeviceCount= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        WhiteListEntries = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GAP_LE_White_List_Entry_t)*(DeviceCount)));

        if(WhiteListEntries == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < DeviceCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_GAP_LE_White_List_Entry_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_GAP_LE_White_List_Entry_t *)WhiteListEntries)[qsIndex]);
            }
        }
    }
    else
        WhiteListEntries = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Add_Device_To_White_List(BluetoothStackID, DeviceCount, WhiteListEntries, AddedDeviceCount);

        qsOutputLength = (4 + (AddedDeviceCount == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_ADD_DEVICE_TO_WHITE_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)AddedDeviceCount);

         if((qsResult == ssSuccess) && (AddedDeviceCount != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)AddedDeviceCount);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Remove_Device_From_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries = NULL;
    uint32_t *RemovedDeviceCount = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&DeviceCount);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RemovedDeviceCount = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(RemovedDeviceCount == NULL)
            qsResult = ssAllocationError;
    }
    else
        RemovedDeviceCount= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        WhiteListEntries = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GAP_LE_White_List_Entry_t)*(DeviceCount)));

        if(WhiteListEntries == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < DeviceCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_GAP_LE_White_List_Entry_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_GAP_LE_White_List_Entry_t *)WhiteListEntries)[qsIndex]);
            }
        }
    }
    else
        WhiteListEntries = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Remove_Device_From_White_List(BluetoothStackID, DeviceCount, WhiteListEntries, RemovedDeviceCount);

        qsOutputLength = (4 + (RemovedDeviceCount == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_REMOVE_DEVICE_FROM_WHITE_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)RemovedDeviceCount);

         if((qsResult == ssSuccess) && (RemovedDeviceCount != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)RemovedDeviceCount);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Read_White_List_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t *WhiteListSize = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        WhiteListSize = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(WhiteListSize == NULL)
            qsResult = ssAllocationError;
    }
    else
        WhiteListSize= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Read_White_List_Size(BluetoothStackID, WhiteListSize);

        qsOutputLength = (4 + (WhiteListSize == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_READ_WHITE_LIST_SIZE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)WhiteListSize);

         if((qsResult == ssSuccess) && (WhiteListSize != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)WhiteListSize);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Pairability_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_GAP_LE_Pairability_Mode_t PairableMode;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&PairableMode);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Pairability_Mode(BluetoothStackID, PairableMode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_PAIRABILITY_MODE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Register_Remote_Authentication(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Register_Remote_Authentication(BluetoothStackID, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_REGISTER_REMOTE_AUTHENTICATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Un_Register_Remote_Authentication(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Un_Register_Remote_Authentication(BluetoothStackID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_UN_REGISTER_REMOTE_AUTHENTICATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Pair_Remote_Device(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Pairing_Capabilities_t *Capabilities = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Capabilities = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Pairing_Capabilities_t));

        if(Capabilities == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Pairing_Capabilities_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Pairing_Capabilities_t *)Capabilities);
        }
    }
    else
        Capabilities = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Pair_Remote_Device(BluetoothStackID, BD_ADDR, Capabilities, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_PAIR_REMOTE_DEVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Extended_Pair_Remote_Device(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *Extended_Capabilities = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Extended_Capabilities = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t));

        if(Extended_Capabilities == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *)Extended_Capabilities);
        }
    }
    else
        Extended_Capabilities = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Extended_Pair_Remote_Device(BluetoothStackID, BD_ADDR, Extended_Capabilities, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_EXTENDED_PAIR_REMOTE_DEVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Authentication_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Authentication_Response_Information_t *GAP_LE_Authentication_Information = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        GAP_LE_Authentication_Information = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Authentication_Response_Information_t));

        if(GAP_LE_Authentication_Information == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Authentication_Response_Information_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Authentication_Response_Information_t *)GAP_LE_Authentication_Information);
        }
    }
    else
        GAP_LE_Authentication_Information = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Authentication_Response(BluetoothStackID, BD_ADDR, GAP_LE_Authentication_Information);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_AUTHENTICATION_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Reestablish_Security(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Security_Information_t *SecurityInformation = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SecurityInformation = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Security_Information_t));

        if(SecurityInformation == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Security_Information_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Security_Information_t *)SecurityInformation);
        }
    }
    else
        SecurityInformation = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Reestablish_Security(BluetoothStackID, BD_ADDR, SecurityInformation, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_REESTABLISH_SECURITY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Request_Security(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Bonding_Type_t Bonding_Type;
    boolean_t MITM;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&Bonding_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&MITM);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Request_Security(BluetoothStackID, BD_ADDR, Bonding_Type, MITM, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_REQUEST_SECURITY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Extended_Request_Security(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *ExtendedCapabilities = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ExtendedCapabilities = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t));

        if(ExtendedCapabilities == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *)ExtendedCapabilities);
        }
    }
    else
        ExtendedCapabilities = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Extended_Request_Security(BluetoothStackID, BD_ADDR, ExtendedCapabilities, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_EXTENDED_REQUEST_SECURITY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Fixed_Passkey(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t *Fixed_Display_Passkey = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Fixed_Display_Passkey = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(Fixed_Display_Passkey == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)Fixed_Display_Passkey);
        }
    }
    else
        Fixed_Display_Passkey = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Fixed_Passkey(BluetoothStackID, Fixed_Display_Passkey);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_FIXED_PASSKEY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Update_Local_P256_Public_Key(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Update_Local_P256_Public_Key(BluetoothStackID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_UPDATE_LOCAL_P256_PUBLIC_KEY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Encryption_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_Encryption_Mode_t *GAP_Encryption_Mode = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        GAP_Encryption_Mode = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_Encryption_Mode_t));

        if(GAP_Encryption_Mode == NULL)
            qsResult = ssAllocationError;
    }
    else
        GAP_Encryption_Mode= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Query_Encryption_Mode(BluetoothStackID, BD_ADDR, GAP_Encryption_Mode);

        qsOutputLength = (4 + (GAP_Encryption_Mode == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_QUERY_ENCRYPTION_MODE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)GAP_Encryption_Mode);

         if((qsResult == ssSuccess) && (GAP_Encryption_Mode != NULL))
         {
             qsResult = PackedWrite_int(qsOutputBuffer, (int *)GAP_Encryption_Mode);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Connection_Handle(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t *Connection_Handle = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_Handle = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_Handle == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_Handle= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Query_Connection_Handle(BluetoothStackID, BD_ADDR, Connection_Handle);

        qsOutputLength = (4 + (Connection_Handle == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_QUERY_CONNECTION_HANDLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_Handle);

         if((qsResult == ssSuccess) && (Connection_Handle != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_Handle);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Connection_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Current_Connection_Parameters_t *Current_Connection_Parameters = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Current_Connection_Parameters = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Current_Connection_Parameters_t));

        if(Current_Connection_Parameters == NULL)
            qsResult = ssAllocationError;
    }
    else
        Current_Connection_Parameters= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Query_Connection_Parameters(BluetoothStackID, BD_ADDR, Current_Connection_Parameters);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_GAP_LE_Current_Connection_Parameters_t((qapi_BLE_GAP_LE_Current_Connection_Parameters_t *)Current_Connection_Parameters)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_QUERY_CONNECTION_PARAMETERS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Current_Connection_Parameters);

         if((qsResult == ssSuccess) && (Current_Connection_Parameters != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_GAP_LE_Current_Connection_Parameters_t(qsOutputBuffer, (qapi_BLE_GAP_LE_Current_Connection_Parameters_t *)Current_Connection_Parameters);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Generate_Long_Term_Key(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_Encryption_Key_t *DHK = NULL;
    qapi_BLE_Encryption_Key_t *ER = NULL;
    qapi_BLE_Long_Term_Key_t *LTK_Result = NULL;
    uint16_t *DIV_Result = NULL;
    uint16_t *EDIV_Result = NULL;
    qapi_BLE_Random_Number_t *Rand_Result = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        DIV_Result = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(DIV_Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        DIV_Result= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        EDIV_Result = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(EDIV_Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        EDIV_Result= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        DHK = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Encryption_Key_t));

        if(DHK == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)DHK);
        }
    }
    else
        DHK = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ER = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Encryption_Key_t));

        if(ER == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)ER);
        }
    }
    else
        ER = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        LTK_Result = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Long_Term_Key_t));

        if(LTK_Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        LTK_Result= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Rand_Result = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Random_Number_t));

        if(Rand_Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        Rand_Result= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Generate_Long_Term_Key(BluetoothStackID, DHK, ER, LTK_Result, DIV_Result, EDIV_Result, Rand_Result);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_Long_Term_Key_t((qapi_BLE_Long_Term_Key_t *)LTK_Result)) + (DIV_Result == NULL ? 0 : 2) + (EDIV_Result == NULL ? 0 : 2) + (CalcPackedSize_qapi_BLE_Random_Number_t((qapi_BLE_Random_Number_t *)Rand_Result)) + (QS_POINTER_HEADER_SIZE * 4));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_GENERATE_LONG_TERM_KEY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)DIV_Result);

         if((qsResult == ssSuccess) && (DIV_Result != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)DIV_Result);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)EDIV_Result);

         if((qsResult == ssSuccess) && (EDIV_Result != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)EDIV_Result);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)LTK_Result);

         if((qsResult == ssSuccess) && (LTK_Result != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_Long_Term_Key_t(qsOutputBuffer, (qapi_BLE_Long_Term_Key_t *)LTK_Result);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Rand_Result);

         if((qsResult == ssSuccess) && (Rand_Result != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_Random_Number_t(qsOutputBuffer, (qapi_BLE_Random_Number_t *)Rand_Result);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Regenerate_Long_Term_Key(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_Encryption_Key_t *DHK = NULL;
    qapi_BLE_Encryption_Key_t *ER = NULL;
    uint16_t EDIV;
    qapi_BLE_Random_Number_t *Rand = NULL;
    qapi_BLE_Long_Term_Key_t *LTK_Result = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&EDIV);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        DHK = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Encryption_Key_t));

        if(DHK == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)DHK);
        }
    }
    else
        DHK = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ER = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Encryption_Key_t));

        if(ER == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)ER);
        }
    }
    else
        ER = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Rand = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Random_Number_t));

        if(Rand == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_Random_Number_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Random_Number_t *)Rand);
        }
    }
    else
        Rand = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        LTK_Result = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Long_Term_Key_t));

        if(LTK_Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        LTK_Result= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Regenerate_Long_Term_Key(BluetoothStackID, DHK, ER, EDIV, Rand, LTK_Result);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_Long_Term_Key_t((qapi_BLE_Long_Term_Key_t *)LTK_Result)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_REGENERATE_LONG_TERM_KEY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)LTK_Result);

         if((qsResult == ssSuccess) && (LTK_Result != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_Long_Term_Key_t(qsOutputBuffer, (qapi_BLE_Long_Term_Key_t *)LTK_Result);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Diversify_Function(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_Encryption_Key_t *Key = NULL;
    uint16_t DIn;
    uint16_t RIn;
    qapi_BLE_Encryption_Key_t *Result = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&DIn);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&RIn);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Key = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Encryption_Key_t));

        if(Key == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)Key);
        }
    }
    else
        Key = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Result = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Encryption_Key_t));

        if(Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        Result= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Diversify_Function(BluetoothStackID, Key, DIn, RIn, Result);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_Encryption_Key_t((qapi_BLE_Encryption_Key_t *)Result)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_DIVERSIFY_FUNCTION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Result);

         if((qsResult == ssSuccess) && (Result != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_Encryption_Key_t(qsOutputBuffer, (qapi_BLE_Encryption_Key_t *)Result);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Connection_Parameter_Update_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t Connection_Interval_Min;
    uint16_t Connection_Interval_Max;
    uint16_t Slave_Latency;
    uint16_t Supervision_Timeout;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Interval_Min);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Interval_Max);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Slave_Latency);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Supervision_Timeout);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Connection_Parameter_Update_Request(BluetoothStackID, BD_ADDR, Connection_Interval_Min, Connection_Interval_Max, Slave_Latency, Supervision_Timeout);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_CONNECTION_PARAMETER_UPDATE_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Connection_Parameter_Update_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    boolean_t Accept;
    qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Accept);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ConnectionParameters = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));

        if(ConnectionParameters == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Connection_Parameters_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Connection_Parameters_t *)ConnectionParameters);
        }
    }
    else
        ConnectionParameters = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Connection_Parameter_Update_Response(BluetoothStackID, BD_ADDR, Accept, ConnectionParameters);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Update_Connection_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ConnectionParameters = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));

        if(ConnectionParameters == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Connection_Parameters_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Connection_Parameters_t *)ConnectionParameters);
        }
    }
    else
        ConnectionParameters = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Update_Connection_Parameters(BluetoothStackID, BD_ADDR, ConnectionParameters);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_UPDATE_CONNECTION_PARAMETERS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Authenticated_Payload_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t AuthenticatedPayloadTimeout;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&AuthenticatedPayloadTimeout);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Authenticated_Payload_Timeout(BluetoothStackID, BD_ADDR, AuthenticatedPayloadTimeout);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_AUTHENTICATED_PAYLOAD_TIMEOUT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Authenticated_Payload_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t *AuthenticatedPayloadTimeout = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        AuthenticatedPayloadTimeout = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(AuthenticatedPayloadTimeout == NULL)
            qsResult = ssAllocationError;
    }
    else
        AuthenticatedPayloadTimeout= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Query_Authenticated_Payload_Timeout(BluetoothStackID, BD_ADDR, AuthenticatedPayloadTimeout);

        qsOutputLength = (4 + (AuthenticatedPayloadTimeout == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_QUERY_AUTHENTICATED_PAYLOAD_TIMEOUT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)AuthenticatedPayloadTimeout);

         if((qsResult == ssSuccess) && (AuthenticatedPayloadTimeout != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)AuthenticatedPayloadTimeout);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Resolvable_Private_Address_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t RPA_Timeout;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&RPA_Timeout);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Resolvable_Private_Address_Timeout(BluetoothStackID, RPA_Timeout);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Address_Resolution_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    boolean_t EnableAddressResolution;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&EnableAddressResolution);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Address_Resolution_Enable(BluetoothStackID, EnableAddressResolution);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_ADDRESS_RESOLUTION_ENABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Add_Device_To_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries = NULL;
    uint32_t *AddedDeviceCount = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&DeviceCount);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        AddedDeviceCount = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(AddedDeviceCount == NULL)
            qsResult = ssAllocationError;
    }
    else
        AddedDeviceCount= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ResolvingListEntries = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t)*(DeviceCount)));

        if(ResolvingListEntries == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < DeviceCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_GAP_LE_Resolving_List_Entry_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_GAP_LE_Resolving_List_Entry_t *)ResolvingListEntries)[qsIndex]);
            }
        }
    }
    else
        ResolvingListEntries = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Add_Device_To_Resolving_List(BluetoothStackID, DeviceCount, ResolvingListEntries, AddedDeviceCount);

        qsOutputLength = (4 + (AddedDeviceCount == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_ADD_DEVICE_TO_RESOLVING_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)AddedDeviceCount);

         if((qsResult == ssSuccess) && (AddedDeviceCount != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)AddedDeviceCount);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Remove_Device_From_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries = NULL;
    uint32_t *RemovedDeviceCount = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&DeviceCount);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RemovedDeviceCount = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(RemovedDeviceCount == NULL)
            qsResult = ssAllocationError;
    }
    else
        RemovedDeviceCount= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ResolvingListEntries = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t)*(DeviceCount)));

        if(ResolvingListEntries == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < DeviceCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_GAP_LE_Resolving_List_Entry_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_GAP_LE_Resolving_List_Entry_t *)ResolvingListEntries)[qsIndex]);
            }
        }
    }
    else
        ResolvingListEntries = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Remove_Device_From_Resolving_List(BluetoothStackID, DeviceCount, ResolvingListEntries, RemovedDeviceCount);

        qsOutputLength = (4 + (RemovedDeviceCount == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)RemovedDeviceCount);

         if((qsResult == ssSuccess) && (RemovedDeviceCount != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)RemovedDeviceCount);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Read_Resolving_List_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t *ResolvingListSize = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ResolvingListSize = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(ResolvingListSize == NULL)
            qsResult = ssAllocationError;
    }
    else
        ResolvingListSize= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Read_Resolving_List_Size(BluetoothStackID, ResolvingListSize);

        qsOutputLength = (4 + (ResolvingListSize == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_READ_RESOLVING_LIST_SIZE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ResolvingListSize);

         if((qsResult == ssSuccess) && (ResolvingListSize != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)ResolvingListSize);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Resolving_List_Privacy_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_GAP_LE_Address_Type_t Peer_Identity_Address_Type;
    qapi_BLE_BD_ADDR_t Peer_Identity_Address;
    qapi_BLE_GAP_LE_Privacy_Mode_t PrivacyMode;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&Peer_Identity_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&Peer_Identity_Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&PrivacyMode);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Resolving_List_Privacy_Mode(BluetoothStackID, Peer_Identity_Address_Type, Peer_Identity_Address, PrivacyMode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_RESOLVING_LIST_PRIVACY_MODE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t SuggestedTxPacketSize;
    uint16_t SuggestedTxPacketTime;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&SuggestedTxPacketSize);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&SuggestedTxPacketTime);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Data_Length(BluetoothStackID, BD_ADDR, SuggestedTxPacketSize, SuggestedTxPacketTime);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_DATA_LENGTH_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Default_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t SuggestedTxPacketSize;
    uint16_t SuggestedTxPacketTime;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&SuggestedTxPacketSize);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&SuggestedTxPacketTime);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Default_Data_Length(BluetoothStackID, SuggestedTxPacketSize, SuggestedTxPacketTime);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_DEFAULT_DATA_LENGTH_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Default_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t *SuggestedTxPacketSize = NULL;
    uint16_t *SuggestedTxPacketTime = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SuggestedTxPacketSize = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SuggestedTxPacketSize == NULL)
            qsResult = ssAllocationError;
    }
    else
        SuggestedTxPacketSize= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SuggestedTxPacketTime = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SuggestedTxPacketTime == NULL)
            qsResult = ssAllocationError;
    }
    else
        SuggestedTxPacketTime= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Query_Default_Data_Length(BluetoothStackID, SuggestedTxPacketSize, SuggestedTxPacketTime);

        qsOutputLength = (4 + (SuggestedTxPacketSize == NULL ? 0 : 2) + (SuggestedTxPacketTime == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_QUERY_DEFAULT_DATA_LENGTH_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SuggestedTxPacketSize);

         if((qsResult == ssSuccess) && (SuggestedTxPacketSize != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SuggestedTxPacketSize);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SuggestedTxPacketTime);

         if((qsResult == ssSuccess) && (SuggestedTxPacketTime != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SuggestedTxPacketTime);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Default_Connection_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t TxPHYSPreference;
    uint32_t RxPHYSPreference;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TxPHYSPreference);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&RxPHYSPreference);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Default_Connection_PHY(BluetoothStackID, TxPHYSPreference, RxPHYSPreference);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_DEFAULT_CONNECTION_PHY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Connection_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint32_t TxPHYSPreference;
    uint32_t RxPHYSPreference;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TxPHYSPreference);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&RxPHYSPreference);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Connection_PHY(BluetoothStackID, BD_ADDR, TxPHYSPreference, RxPHYSPreference);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_CONNECTION_PHY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Connection_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_PHY_Type_t *TxPHY = NULL;
    qapi_BLE_GAP_LE_PHY_Type_t *RxPHY = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&BD_ADDR);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        TxPHY = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_PHY_Type_t));

        if(TxPHY == NULL)
            qsResult = ssAllocationError;
    }
    else
        TxPHY= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RxPHY = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_PHY_Type_t));

        if(RxPHY == NULL)
            qsResult = ssAllocationError;
    }
    else
        RxPHY= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Query_Connection_PHY(BluetoothStackID, BD_ADDR, TxPHY, RxPHY);

        qsOutputLength = (4 + (TxPHY == NULL ? 0 : 4) + (RxPHY == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_QUERY_CONNECTION_PHY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)TxPHY);

         if((qsResult == ssSuccess) && (TxPHY != NULL))
         {
             qsResult = PackedWrite_int(qsOutputBuffer, (int *)TxPHY);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)RxPHY);

         if((qsResult == ssSuccess) && (RxPHY != NULL))
         {
             qsResult = PackedWrite_int(qsOutputBuffer, (int *)RxPHY);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t *MaximumAdvertisingDataLength = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        MaximumAdvertisingDataLength = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(MaximumAdvertisingDataLength == NULL)
            qsResult = ssAllocationError;
    }
    else
        MaximumAdvertisingDataLength= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length(BluetoothStackID, MaximumAdvertisingDataLength);

        qsOutputLength = (4 + (MaximumAdvertisingDataLength == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_QUERY_MAXIMUM_ADVERTISING_DATA_LENGTH_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)MaximumAdvertisingDataLength);

         if((qsResult == ssSuccess) && (MaximumAdvertisingDataLength != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)MaximumAdvertisingDataLength);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Number_Of_Advertising_Sets(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t *NumberSupportedSets = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        NumberSupportedSets = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(NumberSupportedSets == NULL)
            qsResult = ssAllocationError;
    }
    else
        NumberSupportedSets= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Query_Number_Of_Advertising_Sets(BluetoothStackID, NumberSupportedSets);

        qsOutputLength = (4 + (NumberSupportedSets == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_QUERY_NUMBER_OF_ADVERTISING_SETS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)NumberSupportedSets);

         if((qsResult == ssSuccess) && (NumberSupportedSets != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)NumberSupportedSets);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Advertising_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t AdvertisingHandle;
    qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t *AdvertisingParameters = NULL;
    int8_t *SelectedTxPower = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AdvertisingHandle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SelectedTxPower = AllocateBufferListEntry(&qsBufferList, sizeof(int8_t));

        if(SelectedTxPower == NULL)
            qsResult = ssAllocationError;
    }
    else
        SelectedTxPower= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        AdvertisingParameters = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t));

        if(AdvertisingParameters == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t *)AdvertisingParameters);
        }
    }
    else
        AdvertisingParameters = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Extended_Advertising_Parameters(BluetoothStackID, AdvertisingHandle, AdvertisingParameters, SelectedTxPower);

        qsOutputLength = (4 + (SelectedTxPower == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SelectedTxPower);

         if((qsResult == ssSuccess) && (SelectedTxPower != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)SelectedTxPower);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Advertising_Random_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t AdvertisingHandle;
    qapi_BLE_BD_ADDR_t RandomAddress;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AdvertisingHandle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&RandomAddress);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Extended_Advertising_Random_Address(BluetoothStackID, AdvertisingHandle, RandomAddress);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_EXTENDED_ADVERTISING_RANDOM_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t AdvertisingHandle;
    qapi_BLE_GAP_LE_Advertising_Operation_Type_t Operation;
    qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference;
    uint32_t Length;
    uint8_t *Advertising_Data = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AdvertisingHandle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&Operation);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&FragmentationPreference);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Advertising_Data = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

        if(Advertising_Data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Advertising_Data, sizeof(uint8_t), Length);
        }
    }
    else
        Advertising_Data = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Extended_Advertising_Data(BluetoothStackID, AdvertisingHandle, Operation, FragmentationPreference, Length, Advertising_Data);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_EXTENDED_ADVERTISING_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t AdvertisingHandle;
    qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference;
    uint32_t Length;
    uint8_t *Scan_Response_Data = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AdvertisingHandle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&FragmentationPreference);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Scan_Response_Data = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

        if(Scan_Response_Data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Response_Data, sizeof(uint8_t), Length);
        }
    }
    else
        Scan_Response_Data = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Extended_Scan_Response_Data(BluetoothStackID, AdvertisingHandle, FragmentationPreference, Length, Scan_Response_Data);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Enable_Extended_Advertising(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    boolean_t Enable;
    uint8_t NumberOfSets;
    uint8_t *AdvertisingHandleList = NULL;
    uint32_t *DurationList = NULL;
    uint8_t *MaxExtendedAdvertisingEventList = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Enable);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&NumberOfSets);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        AdvertisingHandleList = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(NumberOfSets)));

        if(AdvertisingHandleList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)AdvertisingHandleList, sizeof(uint8_t), NumberOfSets);
        }
    }
    else
        AdvertisingHandleList = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        DurationList = AllocateBufferListEntry(&qsBufferList, (sizeof(uint32_t)*(NumberOfSets)));

        if(DurationList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)DurationList, sizeof(uint32_t), NumberOfSets);
        }
    }
    else
        DurationList = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        MaxExtendedAdvertisingEventList = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(NumberOfSets)));

        if(MaxExtendedAdvertisingEventList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)MaxExtendedAdvertisingEventList, sizeof(uint8_t), NumberOfSets);
        }
    }
    else
        MaxExtendedAdvertisingEventList = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Enable_Extended_Advertising(BluetoothStackID, Enable, NumberOfSets, AdvertisingHandleList, DurationList, MaxExtendedAdvertisingEventList, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_ENABLE_EXTENDED_ADVERTISING_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Remove_Advertising_Sets(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t NumberAdvertisingSetHandles;
    uint8_t *AdvertisingHandles = NULL;
    uint32_t *RemovedSetCount = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumberAdvertisingSetHandles);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        AdvertisingHandles = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(NumberAdvertisingSetHandles)));

        if(AdvertisingHandles == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)AdvertisingHandles, sizeof(uint8_t), NumberAdvertisingSetHandles);
        }
    }
    else
        AdvertisingHandles = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RemovedSetCount = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(RemovedSetCount == NULL)
            qsResult = ssAllocationError;
    }
    else
        RemovedSetCount= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Remove_Advertising_Sets(BluetoothStackID, NumberAdvertisingSetHandles, AdvertisingHandles, RemovedSetCount);

        qsOutputLength = (4 + (RemovedSetCount == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_REMOVE_ADVERTISING_SETS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)RemovedSetCount);

         if((qsResult == ssSuccess) && (RemovedSetCount != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)RemovedSetCount);
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Set_Extended_Scan_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_GAP_LE_Address_Type_t LocalAddressType;
    qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy;
    uint32_t NumberScanningPHYs;
    qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t *ScanningParameterList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&LocalAddressType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&FilterPolicy);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumberScanningPHYs);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ScanningParameterList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t)*(NumberScanningPHYs)));

        if(ScanningParameterList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < NumberScanningPHYs; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t *)ScanningParameterList)[qsIndex]);
            }
        }
    }
    else
        ScanningParameterList = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Set_Extended_Scan_Parameters(BluetoothStackID, LocalAddressType, FilterPolicy, NumberScanningPHYs, ScanningParameterList);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_SET_EXTENDED_SCAN_PARAMETERS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Enable_Extended_Scan(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    boolean_t Enable;
    qapi_BLE_GAP_LE_Extended_Scan_Filter_Duplicates_Type_t FilterDuplicates;
    uint32_t Duration;
    uint32_t Period;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Enable);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&FilterDuplicates);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Duration);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Period);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Enable_Extended_Scan(BluetoothStackID, Enable, FilterDuplicates, Duration, Period, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_ENABLE_EXTENDED_SCAN_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Extended_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy;
    qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType;
    qapi_BLE_BD_ADDR_t *RemoteDevice = NULL;
    qapi_BLE_GAP_LE_Address_Type_t LocalAddressType;
    uint32_t NumberOfConnectionParameters;
    qapi_BLE_GAP_LE_Extended_Connection_Parameters_t *ConnectionParameterList = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&InitatorFilterPolicy);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&RemoteAddressType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&LocalAddressType);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumberOfConnectionParameters);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RemoteDevice = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(RemoteDevice == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)RemoteDevice);
        }
    }
    else
        RemoteDevice = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ConnectionParameterList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GAP_LE_Extended_Connection_Parameters_t)*(NumberOfConnectionParameters)));

        if(ConnectionParameterList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < NumberOfConnectionParameters; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_GAP_LE_Extended_Connection_Parameters_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_GAP_LE_Extended_Connection_Parameters_t *)ConnectionParameterList)[qsIndex]);
            }
        }
    }
    else
        ConnectionParameterList = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Extended_Create_Connection(BluetoothStackID, InitatorFilterPolicy, RemoteAddressType, RemoteDevice, LocalAddressType, NumberOfConnectionParameters, ConnectionParameterList, QZ_qapi_BLE_GAP_LE_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_EXTENDED_CREATE_CONNECTION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_GAP_LE_Query_Local_Secure_Connections_OOB_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_Secure_Connections_Randomizer_t *Randomizer = NULL;
    qapi_BLE_Secure_Connections_Confirmation_t *Confirmation = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Randomizer = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Secure_Connections_Randomizer_t));

        if(Randomizer == NULL)
            qsResult = ssAllocationError;
    }
    else
        Randomizer= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Confirmation = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Secure_Connections_Confirmation_t));

        if(Confirmation == NULL)
            qsResult = ssAllocationError;
    }
    else
        Confirmation= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_GAP_LE_Query_Local_Secure_Connections_OOB_Data(BluetoothStackID, Randomizer, Confirmation);

        qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_Secure_Connections_Randomizer_t((qapi_BLE_Secure_Connections_Randomizer_t *)Randomizer)) + (CalcPackedSize_qapi_BLE_Secure_Connections_Confirmation_t((qapi_BLE_Secure_Connections_Confirmation_t *)Confirmation)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GAP_FILE_ID, QAPI_BLE_GAP_LE_QUERY_LOCAL_SECURE_CONNECTIONS_OOB_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Randomizer);

         if((qsResult == ssSuccess) && (Randomizer != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_Secure_Connections_Randomizer_t(qsOutputBuffer, (qapi_BLE_Secure_Connections_Randomizer_t *)Randomizer);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Confirmation);

         if((qsResult == ssSuccess) && (Confirmation != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_Secure_Connections_Confirmation_t(qsOutputBuffer, (qapi_BLE_Secure_Connections_Confirmation_t *)Confirmation);
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
