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
#include "qapi_ble_hci_qz_mnl.h"
#include "qapi_ble_hci_common.h"
#include "qapi_ble_hci_qz_cb.h"

SerStatus_t Handle_qapi_BLE_HCI_Version_Supported(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_HCI_Version_t *HCI_Version = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        HCI_Version = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HCI_Version_t));

        if(HCI_Version == NULL)
            qsResult = ssAllocationError;
    }
    else
        HCI_Version= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Version_Supported(BluetoothStackID, HCI_Version);

        qsOutputLength = (4 + (HCI_Version == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_VERSION_SUPPORTED_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)HCI_Version);

         if((qsResult == ssSuccess) && (HCI_Version != NULL))
         {
             qsResult = PackedWrite_int(qsOutputBuffer, (int *)HCI_Version);
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

SerStatus_t Handle_qapi_BLE_HCI_Command_Supported(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t SupportedCommandBitNumber;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&SupportedCommandBitNumber);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Command_Supported(BluetoothStackID, SupportedCommandBitNumber);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_COMMAND_SUPPORTED_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HCI_Register_Event_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_BLE_HCI_Register_Event_Callback(BluetoothStackID, QZ_qapi_BLE_HCI_Event_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_REGISTER_EVENT_CALLBACK_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HCI_Register_ACL_Data_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_BLE_HCI_Register_ACL_Data_Callback(BluetoothStackID, QZ_qapi_BLE_HCI_ACL_Data_Callback_t_Handler, CallbackParameter);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_REGISTER_ACL_DATA_CALLBACK_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HCI_Un_Register_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t CallbackID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Un_Register_Callback(BluetoothStackID, CallbackID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_UN_REGISTER_CALLBACK_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HCI_Send_ACL_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint16_t Connection_Handle;
    uint16_t Flags;
    uint16_t ACLDataLength;
    uint8_t *ACLData = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Flags);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&ACLDataLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ACLData = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(ACLDataLength)));

        if(ACLData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)ACLData, sizeof(uint8_t), ACLDataLength);
        }
    }
    else
        ACLData = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        /* Host does not require a response for this API. */
        (void)qapi_BLE_HCI_Send_ACL_Data(BluetoothStackID, Connection_Handle, Flags, ACLDataLength, ACLData);
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_HCI_Send_Raw_Command(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    /* Create a temporary variable for the length of BufferResult. */
    uint32_t qsTmp_LengthResult = 0;
    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    int qsRetVal = 0;

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint8_t Command_OGF;
    uint16_t Command_OCF;
    uint8_t Command_Length;
    uint8_t *Command_Data = NULL;
    uint8_t *StatusResult = NULL;
    uint8_t *LengthResult = NULL;
    uint8_t *BufferResult = NULL;
    boolean_t WaitForResponse;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Command_OGF);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Command_OCF);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Command_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&WaitForResponse);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Command_Data = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Command_Length)));

        if(Command_Data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Command_Data, sizeof(uint8_t), Command_Length);
        }
    }
    else
        Command_Data = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        LengthResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(LengthResult == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)LengthResult);
        }
    }
    else
        LengthResult = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (LengthResult != NULL))
    {
        BufferResult = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(*LengthResult)));

        if(BufferResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        BufferResult= NULL;

    if(LengthResult != NULL)
      qsTmp_LengthResult = *LengthResult;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Send_Raw_Command(BluetoothStackID, Command_OGF, Command_OCF, Command_Length, Command_Data, StatusResult, LengthResult, BufferResult, WaitForResponse);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (LengthResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 3));

      if((LengthResult != NULL) && (BufferResult != NULL))
      {
         if(qsTmp_LengthResult > *LengthResult)
            qsTmp_LengthResult = *LengthResult;
         qsOutputLength = qsOutputLength + ((qsTmp_LengthResult)*(1));
      }

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SEND_RAW_COMMAND_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)LengthResult);

         if((qsResult == ssSuccess) && (LengthResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)LengthResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)BufferResult);

         if((qsResult == ssSuccess) && (BufferResult != NULL) && (LengthResult != NULL))
         {
             qsResult = PackedWrite_Array(qsOutputBuffer, (void *)BufferResult, sizeof(uint8_t), qsTmp_LengthResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Reconfigure_Driver(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    boolean_t ResetStateMachines;
    qapi_BLE_HCI_Driver_Reconfigure_Data_t *DriverReconfigureData = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ResetStateMachines);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        DriverReconfigureData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HCI_Driver_Reconfigure_Data_t));

        if(DriverReconfigureData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_HCI_Driver_Reconfigure_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_HCI_Driver_Reconfigure_Data_t *)DriverReconfigureData);
        }
    }
    else
        DriverReconfigureData = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Reconfigure_Driver(BluetoothStackID, ResetStateMachines, DriverReconfigureData);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_RECONFIGURE_DRIVER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HCI_Set_Host_Flow_Control(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t NumberOfACLPackets;
    uint16_t NumberOfSCOPackets;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&NumberOfACLPackets);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&NumberOfSCOPackets);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Set_Host_Flow_Control(BluetoothStackID, NumberOfACLPackets, NumberOfSCOPackets);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SET_HOST_FLOW_CONTROL_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_BLE_HCI_Query_Host_Flow_Control(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t *NumberOfACLPackets = NULL;
    uint16_t *NumberOfSCOPackets = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        NumberOfACLPackets = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(NumberOfACLPackets == NULL)
            qsResult = ssAllocationError;
    }
    else
        NumberOfACLPackets= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        NumberOfSCOPackets = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(NumberOfSCOPackets == NULL)
            qsResult = ssAllocationError;
    }
    else
        NumberOfSCOPackets= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Query_Host_Flow_Control(BluetoothStackID, NumberOfACLPackets, NumberOfSCOPackets);

        qsOutputLength = (4 + (NumberOfACLPackets == NULL ? 0 : 2) + (NumberOfSCOPackets == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_QUERY_HOST_FLOW_CONTROL_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)NumberOfACLPackets);

         if((qsResult == ssSuccess) && (NumberOfACLPackets != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)NumberOfACLPackets);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)NumberOfSCOPackets);

         if((qsResult == ssSuccess) && (NumberOfSCOPackets != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)NumberOfSCOPackets);
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

SerStatus_t Handle_qapi_BLE_HCI_Disconnect(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t Reason;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Reason);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Disconnect(BluetoothStackID, Connection_Handle, Reason, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_DISCONNECT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Read_Remote_Version_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Read_Remote_Version_Information(BluetoothStackID, Connection_Handle, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_READ_REMOTE_VERSION_INFORMATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Set_Event_Mask(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_Event_Mask_t Event_Mask;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Event_Mask_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Event_Mask_t *)&Event_Mask);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Set_Event_Mask(BluetoothStackID, Event_Mask, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SET_EVENT_MASK_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Reset(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Reset(BluetoothStackID, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_RESET_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Read_Transmit_Power_Level(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t Type;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;
    int8_t *Transmit_Power_LevelResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Transmit_Power_LevelResult = AllocateBufferListEntry(&qsBufferList, sizeof(int8_t));

        if(Transmit_Power_LevelResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Transmit_Power_LevelResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Read_Transmit_Power_Level(BluetoothStackID, Connection_Handle, Type, StatusResult, Connection_HandleResult, Transmit_Power_LevelResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (Transmit_Power_LevelResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 3));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_READ_TRANSMIT_POWER_LEVEL_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Transmit_Power_LevelResult);

         if((qsResult == ssSuccess) && (Transmit_Power_LevelResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Transmit_Power_LevelResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Set_Event_Mask_Page_2(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_Event_Mask_t Event_Mask;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Event_Mask_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Event_Mask_t *)&Event_Mask);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Set_Event_Mask_Page_2(BluetoothStackID, Event_Mask, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SET_EVENT_MASK_PAGE_2_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_Channel_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t MWS_Channel_Enable;
    uint16_t MWS_RX_Center_Frequency;
    uint16_t MWS_TX_Center_Frequency;
    uint16_t MWS_RX_Channel_Bandwidth;
    uint16_t MWS_TX_Channel_Bandwidth;
    uint8_t MWS_Channel_Type;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&MWS_Channel_Enable);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&MWS_RX_Center_Frequency);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&MWS_TX_Center_Frequency);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&MWS_RX_Channel_Bandwidth);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&MWS_TX_Channel_Bandwidth);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&MWS_Channel_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Set_MWS_Channel_Parameters(BluetoothStackID, MWS_Channel_Enable, MWS_RX_Center_Frequency, MWS_TX_Center_Frequency, MWS_RX_Channel_Bandwidth, MWS_TX_Channel_Bandwidth, MWS_Channel_Type, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SET_MWS_CHANNEL_PARAMETERS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Set_External_Frame_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Ext_Frame_Duration;
    uint16_t Ext_Frame_Sync_Assert_Offset;
    uint16_t Ext_Frame_Sync_Assert_Jitter;
    uint8_t Ext_Num_Periods;
    uint16_t *Period_Duration = NULL;
    uint8_t *Period_Type = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Ext_Frame_Duration);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Ext_Frame_Sync_Assert_Offset);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Ext_Frame_Sync_Assert_Jitter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Ext_Num_Periods);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Period_Duration = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Ext_Num_Periods)));

        if(Period_Duration == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Period_Duration, sizeof(uint16_t), Ext_Num_Periods);
        }
    }
    else
        Period_Duration = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Period_Type = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Ext_Num_Periods)));

        if(Period_Type == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Period_Type, sizeof(uint8_t), Ext_Num_Periods);
        }
    }
    else
        Period_Type = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Set_External_Frame_Configuration(BluetoothStackID, Ext_Frame_Duration, Ext_Frame_Sync_Assert_Offset, Ext_Frame_Sync_Assert_Jitter, Ext_Num_Periods, Period_Duration, Period_Type, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SET_EXTERNAL_FRAME_CONFIGURATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_Signaling(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_HCI_Set_MWS_Signaling_Parameters_t *Set_MWS_Signaling_Parameters = NULL;
    uint8_t *StatusResult = NULL;
    qapi_BLE_HCI_Set_MWS_Signaling_Result_t *Set_MWS_Signaling_Result = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Set_MWS_Signaling_Parameters = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HCI_Set_MWS_Signaling_Parameters_t));

        if(Set_MWS_Signaling_Parameters == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_HCI_Set_MWS_Signaling_Parameters_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_HCI_Set_MWS_Signaling_Parameters_t *)Set_MWS_Signaling_Parameters);
        }
    }
    else
        Set_MWS_Signaling_Parameters = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Set_MWS_Signaling_Result = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HCI_Set_MWS_Signaling_Result_t));

        if(Set_MWS_Signaling_Result == NULL)
            qsResult = ssAllocationError;
    }
    else
        Set_MWS_Signaling_Result= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Set_MWS_Signaling(BluetoothStackID, Set_MWS_Signaling_Parameters, StatusResult, Set_MWS_Signaling_Result);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_HCI_Set_MWS_Signaling_Result_t((qapi_BLE_HCI_Set_MWS_Signaling_Result_t *)Set_MWS_Signaling_Result)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SET_MWS_SIGNALING_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Set_MWS_Signaling_Result);

         if((qsResult == ssSuccess) && (Set_MWS_Signaling_Result != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_HCI_Set_MWS_Signaling_Result_t(qsOutputBuffer, (qapi_BLE_HCI_Set_MWS_Signaling_Result_t *)Set_MWS_Signaling_Result);
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

SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_Transport_Layer(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Transport_Layer;
    uint32_t To_MWS_Baud_Rate;
    uint32_t From_MWS_Baud_Rate;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Transport_Layer);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&To_MWS_Baud_Rate);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&From_MWS_Baud_Rate);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Set_MWS_Transport_Layer(BluetoothStackID, Transport_Layer, To_MWS_Baud_Rate, From_MWS_Baud_Rate, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SET_MWS_TRANSPORT_LAYER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Num_Scan_Frequencies;
    uint16_t *Scan_Frequency_Low = NULL;
    uint16_t *Scan_Frequency_High = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Num_Scan_Frequencies);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Scan_Frequency_Low = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Num_Scan_Frequencies)));

        if(Scan_Frequency_Low == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Frequency_Low, sizeof(uint16_t), Num_Scan_Frequencies);
        }
    }
    else
        Scan_Frequency_Low = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Scan_Frequency_High = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Num_Scan_Frequencies)));

        if(Scan_Frequency_High == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Frequency_High, sizeof(uint16_t), Num_Scan_Frequencies);
        }
    }
    else
        Scan_Frequency_High = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table(BluetoothStackID, Num_Scan_Frequencies, Scan_Frequency_Low, Scan_Frequency_High, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SET_MWS_SCAN_FREQUENCY_TABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Set_MWS_PATTERN_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t MWS_PATTERN_Index;
    uint8_t MWS_PATTERN_NumIntervals;
    uint16_t *MWS_PATTERN_IntervalDuration = NULL;
    uint8_t *MWS_PATTERN_IntervalType = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&MWS_PATTERN_Index);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&MWS_PATTERN_NumIntervals);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        MWS_PATTERN_IntervalDuration = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(MWS_PATTERN_NumIntervals)));

        if(MWS_PATTERN_IntervalDuration == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)MWS_PATTERN_IntervalDuration, sizeof(uint16_t), MWS_PATTERN_NumIntervals);
        }
    }
    else
        MWS_PATTERN_IntervalDuration = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        MWS_PATTERN_IntervalType = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(MWS_PATTERN_NumIntervals)));

        if(MWS_PATTERN_IntervalType == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)MWS_PATTERN_IntervalType, sizeof(uint8_t), MWS_PATTERN_NumIntervals);
        }
    }
    else
        MWS_PATTERN_IntervalType = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Set_MWS_PATTERN_Configuration(BluetoothStackID, MWS_PATTERN_Index, MWS_PATTERN_NumIntervals, MWS_PATTERN_IntervalDuration, MWS_PATTERN_IntervalType, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_SET_MWS_PATTERN_CONFIGURATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Read_Authenticated_Payload_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;
    uint16_t *Authenticated_Payload_TimeoutResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Authenticated_Payload_TimeoutResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Authenticated_Payload_TimeoutResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Authenticated_Payload_TimeoutResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Read_Authenticated_Payload_Timeout(BluetoothStackID, Connection_Handle, StatusResult, Connection_HandleResult, Authenticated_Payload_TimeoutResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (Authenticated_Payload_TimeoutResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 3));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_READ_AUTHENTICATED_PAYLOAD_TIMEOUT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Authenticated_Payload_TimeoutResult);

         if((qsResult == ssSuccess) && (Authenticated_Payload_TimeoutResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Authenticated_Payload_TimeoutResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Write_Authenticated_Payload_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint16_t Authenticated_Payload_Timeout;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Authenticated_Payload_Timeout);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Write_Authenticated_Payload_Timeout(BluetoothStackID, Connection_Handle, Authenticated_Payload_Timeout, StatusResult, Connection_HandleResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Read_Local_Version_Information(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint8_t *HCI_VersionResult = NULL;
    uint16_t *HCI_RevisionResult = NULL;
    uint8_t *LMP_VersionResult = NULL;
    uint16_t *Manufacturer_NameResult = NULL;
    uint16_t *LMP_SubversionResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        HCI_VersionResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(HCI_VersionResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        HCI_VersionResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        HCI_RevisionResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(HCI_RevisionResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        HCI_RevisionResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        LMP_VersionResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(LMP_VersionResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        LMP_VersionResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Manufacturer_NameResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Manufacturer_NameResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Manufacturer_NameResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        LMP_SubversionResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(LMP_SubversionResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        LMP_SubversionResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Read_Local_Version_Information(BluetoothStackID, StatusResult, HCI_VersionResult, HCI_RevisionResult, LMP_VersionResult, Manufacturer_NameResult, LMP_SubversionResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (HCI_VersionResult == NULL ? 0 : 1) + (HCI_RevisionResult == NULL ? 0 : 2) + (LMP_VersionResult == NULL ? 0 : 1) + (Manufacturer_NameResult == NULL ? 0 : 2) + (LMP_SubversionResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 6));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_READ_LOCAL_VERSION_INFORMATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)HCI_VersionResult);

         if((qsResult == ssSuccess) && (HCI_VersionResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)HCI_VersionResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)HCI_RevisionResult);

         if((qsResult == ssSuccess) && (HCI_RevisionResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)HCI_RevisionResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)LMP_VersionResult);

         if((qsResult == ssSuccess) && (LMP_VersionResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)LMP_VersionResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Manufacturer_NameResult);

         if((qsResult == ssSuccess) && (Manufacturer_NameResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Manufacturer_NameResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)LMP_SubversionResult);

         if((qsResult == ssSuccess) && (LMP_SubversionResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)LMP_SubversionResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Read_Local_Supported_Features(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    qapi_BLE_LMP_Features_t *LMP_FeaturesResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        LMP_FeaturesResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_LMP_Features_t));

        if(LMP_FeaturesResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        LMP_FeaturesResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Read_Local_Supported_Features(BluetoothStackID, StatusResult, LMP_FeaturesResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_LMP_Features_t((qapi_BLE_LMP_Features_t *)LMP_FeaturesResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_FEATURES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)LMP_FeaturesResult);

         if((qsResult == ssSuccess) && (LMP_FeaturesResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_LMP_Features_t(qsOutputBuffer, (qapi_BLE_LMP_Features_t *)LMP_FeaturesResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Read_BD_ADDR(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    qapi_BLE_BD_ADDR_t *BD_ADDRResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        BD_ADDRResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(BD_ADDRResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        BD_ADDRResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Read_BD_ADDR(BluetoothStackID, StatusResult, BD_ADDRResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_BD_ADDR_t((qapi_BLE_BD_ADDR_t *)BD_ADDRResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_READ_BD_ADDR_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)BD_ADDRResult);

         if((qsResult == ssSuccess) && (BD_ADDRResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_BD_ADDR_t(qsOutputBuffer, (qapi_BLE_BD_ADDR_t *)BD_ADDRResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Read_Local_Supported_Commands(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    qapi_BLE_Supported_Commands_t *Supported_CommandsResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Supported_CommandsResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Supported_Commands_t));

        if(Supported_CommandsResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Supported_CommandsResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Read_Local_Supported_Commands(BluetoothStackID, StatusResult, Supported_CommandsResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_Supported_Commands_t((qapi_BLE_Supported_Commands_t *)Supported_CommandsResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_COMMANDS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Supported_CommandsResult);

         if((qsResult == ssSuccess) && (Supported_CommandsResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_Supported_Commands_t(qsOutputBuffer, (qapi_BLE_Supported_Commands_t *)Supported_CommandsResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Read_RSSI(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;
    int8_t *RSSIResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RSSIResult = AllocateBufferListEntry(&qsBufferList, sizeof(int8_t));

        if(RSSIResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        RSSIResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Read_RSSI(BluetoothStackID, Connection_Handle, StatusResult, Connection_HandleResult, RSSIResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (RSSIResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 3));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_READ_RSSI_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)RSSIResult);

         if((qsResult == ssSuccess) && (RSSIResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)RSSIResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t *Transport_Layer_ConfigurationResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Transport_Layer_ConfigurationResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t));

        if(Transport_Layer_ConfigurationResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Transport_Layer_ConfigurationResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration(BluetoothStackID, StatusResult, Transport_Layer_ConfigurationResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t((qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t *)Transport_Layer_ConfigurationResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_GET_MWS_TRANSPORT_LAYER_CONFIGURATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Transport_Layer_ConfigurationResult);

         if((qsResult == ssSuccess) && (Transport_Layer_ConfigurationResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t(qsOutputBuffer, (qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t *)Transport_Layer_ConfigurationResult);
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

SerStatus_t Handle_qapi_BLE_HCI_Free_MWS_Transport_Layer_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Function parameters. */
    qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t *Transport_Layer_Configuration = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Transport_Layer_Configuration = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t));

        if(Transport_Layer_Configuration == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t *)Transport_Layer_Configuration);
        }
    }
    else
        Transport_Layer_Configuration = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qapi_BLE_HCI_Free_MWS_Transport_Layer_Configuration(Transport_Layer_Configuration);

    qsOutputLength = 0;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_FREE_MWS_TRANSPORT_LAYER_CONFIGURATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
        }
        else
        {
            qsResult = ssAllocationError;
        }
    }

    FreeBufferList(&qsBufferList);

    return(qsResult);
}

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Event_Mask(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_Event_Mask_t LE_Event_Mask;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Event_Mask_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Event_Mask_t *)&LE_Event_Mask);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Event_Mask(BluetoothStackID, LE_Event_Mask, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_EVENT_MASK_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Buffer_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint16_t *HC_LE_ACL_Data_Packet_Length = NULL;
    uint8_t *HC_Total_Num_LE_ACL_Data_Packets = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        HC_LE_ACL_Data_Packet_Length = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(HC_LE_ACL_Data_Packet_Length == NULL)
            qsResult = ssAllocationError;
    }
    else
        HC_LE_ACL_Data_Packet_Length= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        HC_Total_Num_LE_ACL_Data_Packets = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(HC_Total_Num_LE_ACL_Data_Packets == NULL)
            qsResult = ssAllocationError;
    }
    else
        HC_Total_Num_LE_ACL_Data_Packets= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Buffer_Size(BluetoothStackID, StatusResult, HC_LE_ACL_Data_Packet_Length, HC_Total_Num_LE_ACL_Data_Packets);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (HC_LE_ACL_Data_Packet_Length == NULL ? 0 : 2) + (HC_Total_Num_LE_ACL_Data_Packets == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 3));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_BUFFER_SIZE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)HC_LE_ACL_Data_Packet_Length);

         if((qsResult == ssSuccess) && (HC_LE_ACL_Data_Packet_Length != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)HC_LE_ACL_Data_Packet_Length);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)HC_Total_Num_LE_ACL_Data_Packets);

         if((qsResult == ssSuccess) && (HC_Total_Num_LE_ACL_Data_Packets != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)HC_Total_Num_LE_ACL_Data_Packets);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Local_Supported_Features(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    qapi_BLE_LE_Features_t *LE_FeaturesResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        LE_FeaturesResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_LE_Features_t));

        if(LE_FeaturesResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        LE_FeaturesResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Local_Supported_Features(BluetoothStackID, StatusResult, LE_FeaturesResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_LE_Features_t((qapi_BLE_LE_Features_t *)LE_FeaturesResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_LOCAL_SUPPORTED_FEATURES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)LE_FeaturesResult);

         if((qsResult == ssSuccess) && (LE_FeaturesResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_LE_Features_t(qsOutputBuffer, (qapi_BLE_LE_Features_t *)LE_FeaturesResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Random_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;

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
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Random_Address(BluetoothStackID, BD_ADDR, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_RANDOM_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Advertising_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Advertising_Interval_Min;
    uint16_t Advertising_Interval_Max;
    uint8_t Advertising_Type;
    uint8_t Own_Address_Type;
    uint8_t Direct_Address_Type;
    qapi_BLE_BD_ADDR_t Direct_Address;
    uint8_t Advertising_Channel_Map;
    uint8_t Advertising_Filter_Policy;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Advertising_Interval_Min);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Advertising_Interval_Max);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Own_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Direct_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&Direct_Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Channel_Map);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Filter_Policy);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Advertising_Parameters(BluetoothStackID, Advertising_Interval_Min, Advertising_Interval_Max, Advertising_Type, Own_Address_Type, Direct_Address_Type, Direct_Address, Advertising_Channel_Map, Advertising_Filter_Policy, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_ADVERTISING_PARAMETERS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint8_t *Transmit_Power_LevelResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Transmit_Power_LevelResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(Transmit_Power_LevelResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Transmit_Power_LevelResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power(BluetoothStackID, StatusResult, Transmit_Power_LevelResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Transmit_Power_LevelResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_ADVERTISING_CHANNEL_TX_POWER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Transmit_Power_LevelResult);

         if((qsResult == ssSuccess) && (Transmit_Power_LevelResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Transmit_Power_LevelResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Advertising_Data_Length;
    qapi_BLE_Advertising_Data_t *Advertising_Data = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Data_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Advertising_Data = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_Advertising_Data_t)*(Advertising_Data_Length)));

        if(Advertising_Data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < Advertising_Data_Length; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_Advertising_Data_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_Advertising_Data_t *)Advertising_Data)[qsIndex]);
            }
        }
    }
    else
        Advertising_Data = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Advertising_Data(BluetoothStackID, Advertising_Data_Length, Advertising_Data, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_ADVERTISING_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Scan_Response_Data_Length;
    qapi_BLE_Scan_Response_Data_t *Scan_Response_Data = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Scan_Response_Data_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Scan_Response_Data = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_Scan_Response_Data_t)*(Scan_Response_Data_Length)));

        if(Scan_Response_Data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < Scan_Response_Data_Length; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_BLE_Scan_Response_Data_t(&qsInputBuffer, &qsBufferList, &((qapi_BLE_Scan_Response_Data_t *)Scan_Response_Data)[qsIndex]);
            }
        }
    }
    else
        Scan_Response_Data = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Scan_Response_Data(BluetoothStackID, Scan_Response_Data_Length, Scan_Response_Data, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_SCAN_RESPONSE_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Advertise_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Advertising_Enable;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Enable);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Advertise_Enable(BluetoothStackID, Advertising_Enable, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_ADVERTISE_ENABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Scan_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t LE_Scan_Type;
    uint16_t LE_Scan_Interval;
    uint16_t LE_Scan_Window;
    uint8_t Own_Address_Type;
    uint8_t Scanning_Filter_Policy;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&LE_Scan_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&LE_Scan_Interval);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&LE_Scan_Window);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Own_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Scanning_Filter_Policy);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Scan_Parameters(BluetoothStackID, LE_Scan_Type, LE_Scan_Interval, LE_Scan_Window, Own_Address_Type, Scanning_Filter_Policy, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_SCAN_PARAMETERS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Scan_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t LE_Scan_Enable;
    uint8_t Filter_Duplicates;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&LE_Scan_Enable);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Filter_Duplicates);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Scan_Enable(BluetoothStackID, LE_Scan_Enable, Filter_Duplicates, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_SCAN_ENABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t LE_Scan_Interval;
    uint16_t LE_Scan_Window;
    uint8_t Initiator_Filter_Policy;
    uint8_t Peer_Address_Type;
    qapi_BLE_BD_ADDR_t Peer_Address;
    uint8_t Own_Address_Type;
    uint16_t Conn_Interval_Min;
    uint16_t Conn_Interval_Max;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint16_t Minimum_CE_Length;
    uint16_t Maximum_CE_Length;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&LE_Scan_Interval);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&LE_Scan_Window);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Initiator_Filter_Policy);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Peer_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&Peer_Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Own_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Conn_Interval_Min);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Conn_Interval_Max);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Conn_Latency);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Supervision_Timeout);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Minimum_CE_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Maximum_CE_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Create_Connection(BluetoothStackID, LE_Scan_Interval, LE_Scan_Window, Initiator_Filter_Policy, Peer_Address_Type, Peer_Address, Own_Address_Type, Conn_Interval_Min, Conn_Interval_Max, Conn_Latency, Supervision_Timeout, Minimum_CE_Length, Maximum_CE_Length, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_CREATE_CONNECTION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Create_Connection_Cancel(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Create_Connection_Cancel(BluetoothStackID, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_CREATE_CONNECTION_CANCEL_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_White_List_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint8_t *White_List_SizeResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        White_List_SizeResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(White_List_SizeResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        White_List_SizeResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_White_List_Size(BluetoothStackID, StatusResult, White_List_SizeResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (White_List_SizeResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_WHITE_LIST_SIZE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)White_List_SizeResult);

         if((qsResult == ssSuccess) && (White_List_SizeResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)White_List_SizeResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Clear_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Clear_White_List(BluetoothStackID, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_CLEAR_WHITE_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Add_Device_To_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Address_Type;
    qapi_BLE_BD_ADDR_t Address;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Add_Device_To_White_List(BluetoothStackID, Address_Type, Address, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_ADD_DEVICE_TO_WHITE_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Remove_Device_From_White_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Address_Type;
    qapi_BLE_BD_ADDR_t Address;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Remove_Device_From_White_List(BluetoothStackID, Address_Type, Address, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_REMOVE_DEVICE_FROM_WHITE_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Connection_Update(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint16_t Conn_Interval_Min;
    uint16_t Conn_Interval_Max;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint16_t Minimum_CE_Length;
    uint16_t Maximum_CE_Length;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Conn_Interval_Min);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Conn_Interval_Max);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Conn_Latency);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Supervision_Timeout);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Minimum_CE_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Maximum_CE_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Connection_Update(BluetoothStackID, Connection_Handle, Conn_Interval_Min, Conn_Interval_Max, Conn_Latency, Supervision_Timeout, Minimum_CE_Length, Maximum_CE_Length, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_CONNECTION_UPDATE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Host_Channel_Classification(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_LE_Channel_Map_t Channel_Map;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_LE_Channel_Map_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_LE_Channel_Map_t *)&Channel_Map);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Host_Channel_Classification(BluetoothStackID, Channel_Map, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_HOST_CHANNEL_CLASSIFICATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Channel_Map(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;
    qapi_BLE_LE_Channel_Map_t *Channel_MapResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Channel_MapResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_LE_Channel_Map_t));

        if(Channel_MapResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Channel_MapResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Channel_Map(BluetoothStackID, Connection_Handle, StatusResult, Connection_HandleResult, Channel_MapResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (CalcPackedSize_qapi_BLE_LE_Channel_Map_t((qapi_BLE_LE_Channel_Map_t *)Channel_MapResult)) + (QS_POINTER_HEADER_SIZE * 3));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_CHANNEL_MAP_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Channel_MapResult);

         if((qsResult == ssSuccess) && (Channel_MapResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_LE_Channel_Map_t(qsOutputBuffer, (qapi_BLE_LE_Channel_Map_t *)Channel_MapResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Remote_Used_Features(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Remote_Used_Features(BluetoothStackID, Connection_Handle, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_REMOTE_USED_FEATURES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Encrypt(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_Encryption_Key_t Key;
    qapi_BLE_Plain_Text_Data_t Plain_Text_Data;
    uint8_t *StatusResult = NULL;
    qapi_BLE_Encrypted_Data_t *Encrypted_DataResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)&Key);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Plain_Text_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Plain_Text_Data_t *)&Plain_Text_Data);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Encrypted_DataResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Encrypted_Data_t));

        if(Encrypted_DataResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Encrypted_DataResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Encrypt(BluetoothStackID, Key, Plain_Text_Data, StatusResult, Encrypted_DataResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_Encrypted_Data_t((qapi_BLE_Encrypted_Data_t *)Encrypted_DataResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_ENCRYPT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Encrypted_DataResult);

         if((qsResult == ssSuccess) && (Encrypted_DataResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_Encrypted_Data_t(qsOutputBuffer, (qapi_BLE_Encrypted_Data_t *)Encrypted_DataResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Rand(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    qapi_BLE_Random_Number_t *Random_NumberResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Random_NumberResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_Random_Number_t));

        if(Random_NumberResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Random_NumberResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Rand(BluetoothStackID, StatusResult, Random_NumberResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_Random_Number_t((qapi_BLE_Random_Number_t *)Random_NumberResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_RAND_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Random_NumberResult);

         if((qsResult == ssSuccess) && (Random_NumberResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_Random_Number_t(qsOutputBuffer, (qapi_BLE_Random_Number_t *)Random_NumberResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Start_Encryption(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    qapi_BLE_Random_Number_t Random_Number;
    uint16_t Encrypted_Diversifier;
    qapi_BLE_Long_Term_Key_t Long_Term_Key;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Random_Number_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Random_Number_t *)&Random_Number);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Encrypted_Diversifier);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Long_Term_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Long_Term_Key_t *)&Long_Term_Key);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Start_Encryption(BluetoothStackID, Connection_Handle, Random_Number, Encrypted_Diversifier, Long_Term_Key, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_START_ENCRYPTION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    qapi_BLE_Long_Term_Key_t Long_Term_Key;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Long_Term_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Long_Term_Key_t *)&Long_Term_Key);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply(BluetoothStackID, Connection_Handle, Long_Term_Key, StatusResult, Connection_HandleResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_LONG_TERM_KEY_REQUEST_REPLY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply(BluetoothStackID, Connection_Handle, StatusResult, Connection_HandleResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Supported_States(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    qapi_BLE_LE_States_t *LE_StatesResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        LE_StatesResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_LE_States_t));

        if(LE_StatesResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        LE_StatesResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Supported_States(BluetoothStackID, StatusResult, LE_StatesResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_LE_States_t((qapi_BLE_LE_States_t *)LE_StatesResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_SUPPORTED_STATES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)LE_StatesResult);

         if((qsResult == ssSuccess) && (LE_StatesResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_LE_States_t(qsOutputBuffer, (qapi_BLE_LE_States_t *)LE_StatesResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Receiver_Test(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t RX_Frequency;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&RX_Frequency);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Receiver_Test(BluetoothStackID, RX_Frequency, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_RECEIVER_TEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Transmitter_Test(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t TX_Frequency;
    uint8_t Length_Of_Test_Data;
    uint8_t Packet_Payload;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&TX_Frequency);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Length_Of_Test_Data);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Packet_Payload);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Transmitter_Test(BluetoothStackID, TX_Frequency, Length_Of_Test_Data, Packet_Payload, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_TRANSMITTER_TEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Test_End(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint16_t *Number_Of_PacketsResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Number_Of_PacketsResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Number_Of_PacketsResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Number_Of_PacketsResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Test_End(BluetoothStackID, StatusResult, Number_Of_PacketsResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Number_Of_PacketsResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_TEST_END_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Number_Of_PacketsResult);

         if((qsResult == ssSuccess) && (Number_Of_PacketsResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Number_Of_PacketsResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint16_t Conn_Interval_Min;
    uint16_t Conn_Interval_Max;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint16_t Minimum_CE_Length;
    uint16_t Maximum_CE_Length;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Conn_Interval_Min);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Conn_Interval_Max);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Conn_Latency);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Supervision_Timeout);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Minimum_CE_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Maximum_CE_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply(BluetoothStackID, Connection_Handle, Conn_Interval_Min, Conn_Interval_Max, Conn_Latency, Supervision_Timeout, Minimum_CE_Length, Maximum_CE_Length, StatusResult, Connection_HandleResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t Reason;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Reason);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply(BluetoothStackID, Connection_Handle, Reason, StatusResult, Connection_HandleResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint16_t TxOctets;
    uint16_t Txtime;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&TxOctets);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Txtime);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Data_Length(BluetoothStackID, Connection_Handle, TxOctets, Txtime, StatusResult, Connection_HandleResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_DATA_LENGTH_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint16_t *SuggestedMaxTxOctetsResult = NULL;
    uint16_t *SuggestedMaxTxTimeResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SuggestedMaxTxOctetsResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SuggestedMaxTxOctetsResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        SuggestedMaxTxOctetsResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SuggestedMaxTxTimeResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SuggestedMaxTxTimeResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        SuggestedMaxTxTimeResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length(BluetoothStackID, StatusResult, SuggestedMaxTxOctetsResult, SuggestedMaxTxTimeResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (SuggestedMaxTxOctetsResult == NULL ? 0 : 2) + (SuggestedMaxTxTimeResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 3));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SuggestedMaxTxOctetsResult);

         if((qsResult == ssSuccess) && (SuggestedMaxTxOctetsResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SuggestedMaxTxOctetsResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SuggestedMaxTxTimeResult);

         if((qsResult == ssSuccess) && (SuggestedMaxTxTimeResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SuggestedMaxTxTimeResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t SuggestedMaxTxOctets;
    uint16_t SuggestedMaxTxTime;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&SuggestedMaxTxOctets);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&SuggestedMaxTxTime);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length(BluetoothStackID, SuggestedMaxTxOctets, SuggestedMaxTxTime, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Local_P256_Public_Key(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Local_P256_Public_Key(BluetoothStackID, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_LOCAL_P256_PUBLIC_KEY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Generate_DHKey(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_BLE_P256_Public_Key_t *Remote_P256_Public_Key = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Remote_P256_Public_Key = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_P256_Public_Key_t));

        if(Remote_P256_Public_Key == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_P256_Public_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_P256_Public_Key_t *)Remote_P256_Public_Key);
        }
    }
    else
        Remote_P256_Public_Key = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Generate_DHKey(BluetoothStackID, Remote_P256_Public_Key, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_GENERATE_DHKEY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Add_Device_To_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Peer_Identity_Address_Type;
    qapi_BLE_BD_ADDR_t Peer_Identity_Address;
    qapi_BLE_Encryption_Key_t Peer_IRK;
    qapi_BLE_Encryption_Key_t Local_IRK;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Peer_Identity_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&Peer_Identity_Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)&Peer_IRK);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_Encryption_Key_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_Encryption_Key_t *)&Local_IRK);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Add_Device_To_Resolving_List(BluetoothStackID, Peer_Identity_Address_Type, Peer_Identity_Address, Peer_IRK, Local_IRK, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_ADD_DEVICE_TO_RESOLVING_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Peer_Identity_Address_Type;
    qapi_BLE_BD_ADDR_t Peer_Identity_Address;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Peer_Identity_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&Peer_Identity_Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List(BluetoothStackID, Peer_Identity_Address_Type, Peer_Identity_Address, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Clear_Resolving_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Clear_Resolving_List(BluetoothStackID, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_CLEAR_RESOLVING_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Resolving_List_Size(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint8_t *Resolving_List_SizeResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Resolving_List_SizeResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(Resolving_List_SizeResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Resolving_List_SizeResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Resolving_List_Size(BluetoothStackID, StatusResult, Resolving_List_SizeResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Resolving_List_SizeResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_RESOLVING_LIST_SIZE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Resolving_List_SizeResult);

         if((qsResult == ssSuccess) && (Resolving_List_SizeResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Resolving_List_SizeResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Peer_Identity_Address_Type;
    qapi_BLE_BD_ADDR_t Peer_Identity_Address;
    uint8_t *StatusResult = NULL;
    qapi_BLE_BD_ADDR_t *Peer_Resolvable_AddressResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Peer_Identity_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&Peer_Identity_Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Peer_Resolvable_AddressResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(Peer_Resolvable_AddressResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Peer_Resolvable_AddressResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address(BluetoothStackID, Peer_Identity_Address_Type, Peer_Identity_Address, StatusResult, Peer_Resolvable_AddressResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_BD_ADDR_t((qapi_BLE_BD_ADDR_t *)Peer_Resolvable_AddressResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_PEER_RESOLVABLE_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Peer_Resolvable_AddressResult);

         if((qsResult == ssSuccess) && (Peer_Resolvable_AddressResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_BD_ADDR_t(qsOutputBuffer, (qapi_BLE_BD_ADDR_t *)Peer_Resolvable_AddressResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Local_Resolvable_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Peer_Identity_Address_Type;
    qapi_BLE_BD_ADDR_t Peer_Identity_Address;
    uint8_t *StatusResult = NULL;
    qapi_BLE_BD_ADDR_t *Local_Resolvable_AddressResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Peer_Identity_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)&Peer_Identity_Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Local_Resolvable_AddressResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(Local_Resolvable_AddressResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Local_Resolvable_AddressResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Local_Resolvable_Address(BluetoothStackID, Peer_Identity_Address_Type, Peer_Identity_Address, StatusResult, Local_Resolvable_AddressResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (CalcPackedSize_qapi_BLE_BD_ADDR_t((qapi_BLE_BD_ADDR_t *)Local_Resolvable_AddressResult)) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_LOCAL_RESOLVABLE_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Local_Resolvable_AddressResult);

         if((qsResult == ssSuccess) && (Local_Resolvable_AddressResult != NULL))
         {
             qsResult = PackedWrite_qapi_BLE_BD_ADDR_t(qsOutputBuffer, (qapi_BLE_BD_ADDR_t *)Local_Resolvable_AddressResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Address_Resolution_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Address_Resolution_Enable;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Address_Resolution_Enable);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Address_Resolution_Enable(BluetoothStackID, Address_Resolution_Enable, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_ADDRESS_RESOLUTION_ENABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t RPA_Timeout;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&RPA_Timeout);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout(BluetoothStackID, RPA_Timeout, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Maximum_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint16_t *SupportedMaxTxOctetsResult = NULL;
    uint16_t *SupportedMaxTxTimeResult = NULL;
    uint16_t *SupportedMaxRxOctetsResult = NULL;
    uint16_t *SupportedMaxRxTimeResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SupportedMaxTxOctetsResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SupportedMaxTxOctetsResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        SupportedMaxTxOctetsResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SupportedMaxTxTimeResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SupportedMaxTxTimeResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        SupportedMaxTxTimeResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SupportedMaxRxOctetsResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SupportedMaxRxOctetsResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        SupportedMaxRxOctetsResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SupportedMaxRxTimeResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SupportedMaxRxTimeResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        SupportedMaxRxTimeResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Maximum_Data_Length(BluetoothStackID, StatusResult, SupportedMaxTxOctetsResult, SupportedMaxTxTimeResult, SupportedMaxRxOctetsResult, SupportedMaxRxTimeResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (SupportedMaxTxOctetsResult == NULL ? 0 : 2) + (SupportedMaxTxTimeResult == NULL ? 0 : 2) + (SupportedMaxRxOctetsResult == NULL ? 0 : 2) + (SupportedMaxRxTimeResult == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 5));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_MAXIMUM_DATA_LENGTH_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SupportedMaxTxOctetsResult);

         if((qsResult == ssSuccess) && (SupportedMaxTxOctetsResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SupportedMaxTxOctetsResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SupportedMaxTxTimeResult);

         if((qsResult == ssSuccess) && (SupportedMaxTxTimeResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SupportedMaxTxTimeResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SupportedMaxRxOctetsResult);

         if((qsResult == ssSuccess) && (SupportedMaxRxOctetsResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SupportedMaxRxOctetsResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SupportedMaxRxTimeResult);

         if((qsResult == ssSuccess) && (SupportedMaxRxTimeResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SupportedMaxRxTimeResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t *StatusResult = NULL;
    uint16_t *Connection_HandleResult = NULL;
    uint8_t *TX_PHYResult = NULL;
    uint8_t *RX_PHYResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Connection_HandleResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Connection_HandleResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Connection_HandleResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        TX_PHYResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(TX_PHYResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        TX_PHYResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RX_PHYResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(RX_PHYResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        RX_PHYResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_PHY(BluetoothStackID, Connection_Handle, StatusResult, Connection_HandleResult, TX_PHYResult, RX_PHYResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Connection_HandleResult == NULL ? 0 : 2) + (TX_PHYResult == NULL ? 0 : 1) + (RX_PHYResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 4));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_PHY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Connection_HandleResult);

         if((qsResult == ssSuccess) && (Connection_HandleResult != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Connection_HandleResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)TX_PHYResult);

         if((qsResult == ssSuccess) && (TX_PHYResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)TX_PHYResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)RX_PHYResult);

         if((qsResult == ssSuccess) && (RX_PHYResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)RX_PHYResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Default_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ALL_PHYS;
    uint8_t TX_PHYS;
    uint8_t RX_PHYS;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ALL_PHYS);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&TX_PHYS);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&RX_PHYS);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Default_PHY(BluetoothStackID, ALL_PHYS, TX_PHYS, RX_PHYS, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_DEFAULT_PHY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_PHY(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t Connection_Handle;
    uint8_t ALL_PHYS;
    uint8_t TX_PHYS;
    uint8_t RX_PHYS;
    uint16_t PHY_Options;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Connection_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ALL_PHYS);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&TX_PHYS);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&RX_PHYS);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&PHY_Options);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_PHY(BluetoothStackID, Connection_Handle, ALL_PHYS, TX_PHYS, RX_PHYS, PHY_Options, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_PHY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Enhanced_Receiver_Test(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t RX_Channel;
    uint8_t PHY;
    uint8_t Modulation_Index;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&RX_Channel);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&PHY);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Modulation_Index);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Enhanced_Receiver_Test(BluetoothStackID, RX_Channel, PHY, Modulation_Index, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_ENHANCED_RECEIVER_TEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Enhanced_Transmitter_Test(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t TX_Channel;
    uint8_t Length_Of_Test_Data;
    uint8_t Packet_Payload;
    uint8_t PHY;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&TX_Channel);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Length_Of_Test_Data);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Packet_Payload);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&PHY);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Enhanced_Transmitter_Test(BluetoothStackID, TX_Channel, Length_Of_Test_Data, Packet_Payload, PHY, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Advertising_Handle;
    qapi_BLE_BD_ADDR_t *Advertising_Random_Address = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Advertising_Random_Address = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(Advertising_Random_Address == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)Advertising_Random_Address);
        }
    }
    else
        Advertising_Random_Address = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address(BluetoothStackID, Advertising_Handle, Advertising_Random_Address, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_ADVERTISING_SET_RANDOM_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Advertising_Handle;
    uint16_t Advertising_Event_Properties;
    uint32_t Primary_Advertising_Interval_Min;
    uint32_t Primary_Advertising_Interval_Max;
    uint8_t Primary_Advertising_Channel_Map;
    uint8_t Own_Address_Type;
    uint8_t Peer_Address_Type;
    qapi_BLE_BD_ADDR_t *Peer_Address = NULL;
    uint8_t Advertising_Filter_Policy;
    int8_t Advertising_TX_Power;
    uint8_t Primary_Advertising_PHY;
    uint8_t Secondary_Advertising_Max_Skip;
    uint8_t Secondary_Advertising_PHY;
    uint8_t Advertising_SID;
    uint8_t Scan_Request_Notification_Enable;
    uint8_t *StatusResult = NULL;
    int8_t *Selected_TX_PowerResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Advertising_Event_Properties);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Primary_Advertising_Interval_Min);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Primary_Advertising_Interval_Max);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Primary_Advertising_Channel_Map);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Own_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Peer_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Filter_Policy);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_TX_Power);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Primary_Advertising_PHY);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Secondary_Advertising_Max_Skip);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Secondary_Advertising_PHY);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_SID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Scan_Request_Notification_Enable);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Selected_TX_PowerResult = AllocateBufferListEntry(&qsBufferList, sizeof(int8_t));

        if(Selected_TX_PowerResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        Selected_TX_PowerResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Peer_Address = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(Peer_Address == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)Peer_Address);
        }
    }
    else
        Peer_Address = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters(BluetoothStackID, Advertising_Handle, Advertising_Event_Properties, Primary_Advertising_Interval_Min, Primary_Advertising_Interval_Max, Primary_Advertising_Channel_Map, Own_Address_Type, Peer_Address_Type, Peer_Address, Advertising_Filter_Policy, Advertising_TX_Power, Primary_Advertising_PHY, Secondary_Advertising_Max_Skip, Secondary_Advertising_PHY, Advertising_SID, Scan_Request_Notification_Enable, StatusResult, Selected_TX_PowerResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Selected_TX_PowerResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Selected_TX_PowerResult);

         if((qsResult == ssSuccess) && (Selected_TX_PowerResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Selected_TX_PowerResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Advertising_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Advertising_Handle;
    uint8_t Operation;
    uint8_t Fragment_Preference;
    uint8_t Advertising_Data_Length;
    uint8_t *Advertising_Data = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Operation);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Fragment_Preference);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Data_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Advertising_Data = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Advertising_Data_Length)));

        if(Advertising_Data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Advertising_Data, sizeof(uint8_t), Advertising_Data_Length);
        }
    }
    else
        Advertising_Data = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Extended_Advertising_Data(BluetoothStackID, Advertising_Handle, Operation, Fragment_Preference, Advertising_Data_Length, Advertising_Data, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_EXTENDED_ADVERTISING_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Advertising_Handle;
    uint8_t Operation;
    uint8_t Fragment_Preference;
    uint8_t Scan_Response_Data_Length;
    uint8_t *Scan_Response_Data = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Operation);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Fragment_Preference);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Scan_Response_Data_Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Scan_Response_Data = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Scan_Response_Data_Length)));

        if(Scan_Response_Data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Response_Data, sizeof(uint8_t), Scan_Response_Data_Length);
        }
    }
    else
        Scan_Response_Data = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data(BluetoothStackID, Advertising_Handle, Operation, Fragment_Preference, Scan_Response_Data_Length, Scan_Response_Data, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Enable;
    uint8_t Number_of_Sets;
    uint8_t *Advertising_Handle = NULL;
    uint16_t *Duration = NULL;
    uint8_t *Max_Extended_Advertising_Events = NULL;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Enable);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Number_of_Sets);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Advertising_Handle = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Number_of_Sets)));

        if(Advertising_Handle == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Advertising_Handle, sizeof(uint8_t), Number_of_Sets);
        }
    }
    else
        Advertising_Handle = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Duration = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Number_of_Sets)));

        if(Duration == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Duration, sizeof(uint16_t), Number_of_Sets);
        }
    }
    else
        Duration = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Max_Extended_Advertising_Events = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Number_of_Sets)));

        if(Max_Extended_Advertising_Events == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Max_Extended_Advertising_Events, sizeof(uint8_t), Number_of_Sets);
        }
    }
    else
        Max_Extended_Advertising_Events = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable(BluetoothStackID, Enable, Number_of_Sets, Advertising_Handle, Duration, Max_Extended_Advertising_Events, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_EXTENDED_ADVERTISING_ENABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Maximum_Advertising_Data_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint16_t *Maximum_Advertising_Data_Length = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Maximum_Advertising_Data_Length = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Maximum_Advertising_Data_Length == NULL)
            qsResult = ssAllocationError;
    }
    else
        Maximum_Advertising_Data_Length= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Maximum_Advertising_Data_Length(BluetoothStackID, StatusResult, Maximum_Advertising_Data_Length);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Maximum_Advertising_Data_Length == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_MAXIMUM_ADVERTISING_DATA_LENGTH_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Maximum_Advertising_Data_Length);

         if((qsResult == ssSuccess) && (Maximum_Advertising_Data_Length != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Maximum_Advertising_Data_Length);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Number_Of_Supported_Advertising_Sets(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    uint8_t *Num_Supported_Advertising_Sets = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Num_Supported_Advertising_Sets = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(Num_Supported_Advertising_Sets == NULL)
            qsResult = ssAllocationError;
    }
    else
        Num_Supported_Advertising_Sets= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Number_Of_Supported_Advertising_Sets(BluetoothStackID, StatusResult, Num_Supported_Advertising_Sets);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Num_Supported_Advertising_Sets == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_NUMBER_OF_SUPPORTED_ADVERTISING_SETS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Num_Supported_Advertising_Sets);

         if((qsResult == ssSuccess) && (Num_Supported_Advertising_Sets != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Num_Supported_Advertising_Sets);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Remove_Advertising_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Advertising_Handle;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Advertising_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Remove_Advertising_Set(BluetoothStackID, Advertising_Handle, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_REMOVE_ADVERTISING_SET_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Clear_Advertising_Sets(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Clear_Advertising_Sets(BluetoothStackID, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_CLEAR_ADVERTISING_SETS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Enable;
    uint8_t Filter_Duplicates;
    uint16_t Duration;
    uint16_t Period;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Enable);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Filter_Duplicates);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Duration);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Period);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Extended_Scan_Enable(BluetoothStackID, Enable, Filter_Duplicates, Duration, Period, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_EXTENDED_SCAN_ENABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Extended_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_BLE_HCI_LE_Extended_Create_Connection(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_Transmit_Power(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    int8_t *Min_TX_Power = NULL;
    int8_t *Max_TX_Power = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Min_TX_Power = AllocateBufferListEntry(&qsBufferList, sizeof(int8_t));

        if(Min_TX_Power == NULL)
            qsResult = ssAllocationError;
    }
    else
        Min_TX_Power= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Max_TX_Power = AllocateBufferListEntry(&qsBufferList, sizeof(int8_t));

        if(Max_TX_Power == NULL)
            qsResult = ssAllocationError;
    }
    else
        Max_TX_Power= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_Transmit_Power(BluetoothStackID, StatusResult, Min_TX_Power, Max_TX_Power);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (Min_TX_Power == NULL ? 0 : 1) + (Max_TX_Power == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 3));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_TRANSMIT_POWER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Min_TX_Power);

         if((qsResult == ssSuccess) && (Min_TX_Power != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Min_TX_Power);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Max_TX_Power);

         if((qsResult == ssSuccess) && (Max_TX_Power != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Max_TX_Power);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Read_RF_Path_Compensation(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *StatusResult = NULL;
    int16_t *RF_TX_Path_Compensation_Value = NULL;
    int16_t *RF_RX_Path_Compensation_Value = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RF_TX_Path_Compensation_Value = AllocateBufferListEntry(&qsBufferList, sizeof(int16_t));

        if(RF_TX_Path_Compensation_Value == NULL)
            qsResult = ssAllocationError;
    }
    else
        RF_TX_Path_Compensation_Value= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        RF_RX_Path_Compensation_Value = AllocateBufferListEntry(&qsBufferList, sizeof(int16_t));

        if(RF_RX_Path_Compensation_Value == NULL)
            qsResult = ssAllocationError;
    }
    else
        RF_RX_Path_Compensation_Value= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Read_RF_Path_Compensation(BluetoothStackID, StatusResult, RF_TX_Path_Compensation_Value, RF_RX_Path_Compensation_Value);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (RF_TX_Path_Compensation_Value == NULL ? 0 : 2) + (RF_RX_Path_Compensation_Value == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 3));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_READ_RF_PATH_COMPENSATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)RF_TX_Path_Compensation_Value);

         if((qsResult == ssSuccess) && (RF_TX_Path_Compensation_Value != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)RF_TX_Path_Compensation_Value);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)RF_RX_Path_Compensation_Value);

         if((qsResult == ssSuccess) && (RF_RX_Path_Compensation_Value != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)RF_RX_Path_Compensation_Value);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Write_RF_Path_Compensation(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    int16_t RF_TX_Path_Compensation_Value;
    int16_t RF_RX_Path_Compensation_Value;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&RF_TX_Path_Compensation_Value);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&RF_RX_Path_Compensation_Value);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Write_RF_Path_Compensation(BluetoothStackID, RF_TX_Path_Compensation_Value, RF_RX_Path_Compensation_Value, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_WRITE_RF_PATH_COMPENSATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Handle_qapi_BLE_HCI_LE_Set_Privacy_Mode(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Peer_Identity_Address_Type;
    qapi_BLE_BD_ADDR_t *Peer_Identity_Address = NULL;
    uint8_t Privacy_Mode;
    uint8_t *StatusResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Peer_Identity_Address_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Privacy_Mode);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(StatusResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        StatusResult= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Peer_Identity_Address = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

        if(Peer_Identity_Address == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)Peer_Identity_Address);
        }
    }
    else
        Peer_Identity_Address = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_BLE_HCI_LE_Set_Privacy_Mode(BluetoothStackID, Peer_Identity_Address_Type, Peer_Identity_Address, Privacy_Mode, StatusResult);

        qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_PRIVACY_MODE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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
