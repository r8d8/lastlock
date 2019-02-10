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
#include "qapi_zb.h"
#include "qapi_zb_cl_basic_common.h"
#include "qapi_zb_cl_basic_qz_cb.h"

SerStatus_t Handle_qapi_ZB_CL_Basic_Create_Client(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_Status_t qsRetVal = 0;

    /* Function parameters. */
    qapi_ZB_Handle_t ZB_Handle;
    qapi_ZB_Cluster_t *Cluster = NULL;
    qapi_ZB_CL_Cluster_Info_t *Cluster_Info = NULL;
    uint32_t CB_Param;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ZB_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CB_Param);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Cluster = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_Cluster_t));

        if(Cluster == NULL)
            qsResult = ssAllocationError;
    }
    else
        Cluster= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Cluster_Info = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_Cluster_Info_t));

        if(Cluster_Info == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_Cluster_Info_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_Cluster_Info_t *)Cluster_Info);
        }
    }
    else
        Cluster_Info = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Basic_Create_Client(ZB_Handle, Cluster, Cluster_Info, QZ_qapi_ZB_CL_Basic_Client_CB_t_Handler, CB_Param);

        qsOutputLength = (4 + (Cluster == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_BASIC_FILE_ID, QAPI_ZB_CL_BASIC_CREATE_CLIENT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Cluster);

         if((qsResult == ssSuccess) && (Cluster != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)Cluster);
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

SerStatus_t Handle_qapi_ZB_CL_Basic_Send_Reset_To_Factory(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_Status_t qsRetVal = 0;

    /* Function parameters. */
    qapi_ZB_Cluster_t Cluster;
    qapi_ZB_CL_General_Send_Info_t *SendInfo = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SendInfo = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_General_Send_Info_t));

        if(SendInfo == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_General_Send_Info_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_General_Send_Info_t *)SendInfo);
        }
    }
    else
        SendInfo = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Basic_Send_Reset_To_Factory(Cluster, SendInfo);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_BASIC_FILE_ID, QAPI_ZB_CL_BASIC_SEND_RESET_TO_FACTORY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Basic_Server_Read_Attribute(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    /* Create a temporary variable for the length of Data. */
    uint32_t qsTmp_Length = 0;
    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Function parameters. */
    qapi_ZB_Handle_t ZB_Handle;
    uint16_t AttrId;
    uint16_t *Length = NULL;
    uint8_t *Data = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ZB_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&AttrId);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Length = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(Length == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)Length);
        }
    }
    else
        Length = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (Length != NULL))
    {
        Data = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(*Length)));

        if(Data == NULL)
            qsResult = ssAllocationError;
    }
    else
        Data= NULL;

    if(Length != NULL)
      qsTmp_Length = *Length;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Basic_Server_Read_Attribute(ZB_Handle, AttrId, Length, Data);

        qsOutputLength = (4 + (Length == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

      if((Length != NULL) && (Data != NULL))
      {
         if(qsTmp_Length > *Length)
            qsTmp_Length = *Length;
         qsOutputLength = qsOutputLength + ((qsTmp_Length)*(1));
      }

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_BASIC_FILE_ID, QAPI_ZB_CL_BASIC_SERVER_READ_ATTRIBUTE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Length);

         if((qsResult == ssSuccess) && (Length != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)Length);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Data);

         if((qsResult == ssSuccess) && (Data != NULL) && (Length != NULL))
         {
             qsResult = PackedWrite_Array(qsOutputBuffer, (void *)Data, sizeof(uint8_t), qsTmp_Length);
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

SerStatus_t Handle_qapi_ZB_CL_Basic_Server_Write_Attribute(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_Status_t qsRetVal = 0;

    /* Function parameters. */
    qapi_ZB_Handle_t ZB_Handle;
    uint16_t AttrId;
    uint16_t Length;
    uint8_t *Data = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ZB_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&AttrId);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Data = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

        if(Data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Data, sizeof(uint8_t), Length);
        }
    }
    else
        Data = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Basic_Server_Write_Attribute(ZB_Handle, AttrId, Length, Data);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_BASIC_FILE_ID, QAPI_ZB_CL_BASIC_SERVER_WRITE_ATTRIBUTE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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
