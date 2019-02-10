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
#include "qsHost.h"
#include "qsCallback.h"
#include "qapi_ble.h"
#include "qapi_ble_hci_common.h"
#include "qapi_ble_hci_host_cb.h"

void Host_qapi_BLE_HCI_Event_Callback_t_Handler(uint32_t CallbackID, CallbackInfo_t *Info, uint16_t BufferLength, uint8_t *Buffer)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    CallbackInfo_t     qsCallbackInfo;
    Boolean_t          qsPointerValid = FALSE;


    UNUSED(qsPointerValid);

    /* Function parameters. */
    uint32_t BluetoothStackID;
    qapi_BLE_HCI_Event_Data_t *HCI_Event_Data = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, Buffer, BufferLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        HCI_Event_Data = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_HCI_Event_Data_t));

        if(HCI_Event_Data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_BLE_HCI_Event_Data_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_HCI_Event_Data_t *)HCI_Event_Data);
        }
    }
    else
        HCI_Event_Data = NULL;

    /* Find the callback and issue it. */
    if(qsResult == ssSuccess)
    {
        qsResult = Callback_Retrieve(CallbackParameter, &qsCallbackInfo);

        if((qsResult == ssSuccess) && (qsCallbackInfo.AppFunction != NULL))
            (*(qapi_BLE_HCI_Event_Callback_t)qsCallbackInfo.AppFunction)(BluetoothStackID, HCI_Event_Data, (uint32_t)qsCallbackInfo.AppParam);
    }

    FreeBufferList(&qsBufferList);
}
void Host_qapi_BLE_HCI_ACL_Data_Callback_t_Handler(uint32_t CallbackID, CallbackInfo_t *Info, uint16_t BufferLength, uint8_t *Buffer)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    CallbackInfo_t     qsCallbackInfo;
    Boolean_t          qsPointerValid = FALSE;


    UNUSED(qsPointerValid);

    /* Function parameters. */
    uint32_t BluetoothStackID;
    uint16_t Connection_Handle;
    uint16_t Flags;
    uint16_t ACLDataLength;
    uint8_t *ACLData = NULL;
    uint32_t CallbackParameter;

    InitializePackedBuffer(&qsInputBuffer, Buffer, BufferLength);

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
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

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

    /* Find the callback and issue it. */
    if(qsResult == ssSuccess)
    {
        qsResult = Callback_Retrieve(CallbackParameter, &qsCallbackInfo);

        if((qsResult == ssSuccess) && (qsCallbackInfo.AppFunction != NULL))
            (*(qapi_BLE_HCI_ACL_Data_Callback_t)qsCallbackInfo.AppFunction)(BluetoothStackID, Connection_Handle, Flags, ACLDataLength, ACLData, (uint32_t)qsCallbackInfo.AppParam);
    }

    FreeBufferList(&qsBufferList);
}
