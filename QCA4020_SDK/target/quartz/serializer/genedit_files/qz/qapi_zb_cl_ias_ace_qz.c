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
#include "qapi_zb_cl_ias_ace_common.h"
#include "qapi_zb_cl_ias_ace_qz_cb.h"

SerStatus_t Handle_qapi_ZB_CL_IASACE_Create_Client(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_IASACE_Create_Client(ZB_Handle, Cluster, Cluster_Info, QZ_qapi_ZB_CL_IASACE_Client_CB_t_Handler, CB_Param);

        qsOutputLength = (4 + (Cluster == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CREATE_CLIENT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Create_Server(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_IASACE_Create_Server(ZB_Handle, Cluster, Cluster_Info, QZ_qapi_ZB_CL_IASACE_Server_CB_t_Handler, CB_Param);

        qsOutputLength = (4 + (Cluster == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CREATE_SERVER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Populate_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    /* Create a temporary variable for the length of AttributeList. */
    uint32_t qsTmp_AttributeCount = 0;
    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Function parameters. */
    qbool_t Server;
    uint8_t *AttributeCount = NULL;
    qapi_ZB_CL_Attribute_t *AttributeList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Server);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        AttributeCount = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(AttributeCount == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)AttributeCount);
        }
    }
    else
        AttributeCount = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (AttributeCount != NULL))
    {
        AttributeList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_ZB_CL_Attribute_t)*(*AttributeCount)));

        if(AttributeList == NULL)
            qsResult = ssAllocationError;
    }
    else
        AttributeList= NULL;

    if(AttributeCount != NULL)
      qsTmp_AttributeCount = *AttributeCount;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Populate_Attributes(Server, AttributeCount, AttributeList);

        qsOutputLength = (4 + (AttributeCount == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 2));

      if((AttributeCount != NULL) && (AttributeList != NULL))
      {
         if(qsTmp_AttributeCount > *AttributeCount)
            qsTmp_AttributeCount = *AttributeCount;
         for (qsIndex = 0; qsIndex < qsTmp_AttributeCount; qsIndex++)
         {
            qsOutputLength = qsOutputLength + CalcPackedSize_qapi_ZB_CL_Attribute_t((qapi_ZB_CL_Attribute_t *)&AttributeList[qsIndex]);
         }
      }

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_POPULATE_ATTRIBUTES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)AttributeCount);

         if((qsResult == ssSuccess) && (AttributeCount != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)AttributeCount);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)AttributeList);

         if((qsResult == ssSuccess) && (AttributeList != NULL) && (AttributeCount != NULL))
         {
             for (qsIndex = 0; qsIndex < qsTmp_AttributeCount; qsIndex++)
             {
                 if(qsResult == ssSuccess)
                     qsResult = PackedWrite_qapi_ZB_CL_Attribute_t(qsOutputBuffer, &((qapi_ZB_CL_Attribute_t *)AttributeList)[qsIndex]);
             }
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Arm(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ZoneID;
    qapi_ZB_CL_IASACE_Arm_Mode_t ArmMode;
    uint8_t *ArmCode = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ZoneID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&ArmMode);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ArmCode = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

        if(ArmCode == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)ArmCode, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
        }
    }
    else
        ArmCode = NULL;

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
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Arm(Cluster, SendInfo, ZoneID, ArmMode, ArmCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_ARM_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Bypass(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t NumberOfZones;
    uint8_t *ZoneIDList = NULL;
    uint8_t *ArmCode = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&NumberOfZones);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ZoneIDList = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(NumberOfZones)));

        if(ZoneIDList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)ZoneIDList, sizeof(uint8_t), NumberOfZones);
        }
    }
    else
        ZoneIDList = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ArmCode = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

        if(ArmCode == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)ArmCode, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
        }
    }
    else
        ArmCode = NULL;

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
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Bypass(Cluster, SendInfo, NumberOfZones, ZoneIDList, ArmCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_BYPASS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Emergency(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Emergency(Cluster, SendInfo);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_EMERGENCY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Fire(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Fire(Cluster, SendInfo);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_FIRE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Panic(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Panic(Cluster, SendInfo);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_PANIC_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Get_ZoneID_Map(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Get_ZoneID_Map(Cluster, SendInfo);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_GET_ZONEID_MAP_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Get_Zone_Info(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ZoneID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ZoneID);

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
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Get_Zone_Info(Cluster, SendInfo, ZoneID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_GET_ZONE_INFO_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Get_Panel_Status(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Get_Panel_Status(Cluster, SendInfo);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_GET_PANEL_STATUS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Get_Bypassed_Zone_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Get_Bypassed_Zone_List(Cluster, SendInfo);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_GET_BYPASSED_ZONE_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Client_Send_Get_Zone_Status(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_CL_IASACE_Get_Zone_Status_t *Request = NULL;

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

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Request = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_IASACE_Get_Zone_Status_t));

        if(Request == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_IASACE_Get_Zone_Status_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_IASACE_Get_Zone_Status_t *)Request);
        }
    }
    else
        Request = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Client_Send_Get_Zone_Status(Cluster, SendInfo, Request);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_CLIENT_SEND_GET_ZONE_STATUS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Set_Arm_Code(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *ArmCode = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ArmCode = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

        if(ArmCode == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)ArmCode, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
        }
    }
    else
        ArmCode = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Set_Arm_Code(Cluster, ArmCode);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_SET_ARM_CODE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Get_Arm_Code(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ArmCodeLength;
    uint8_t *ArmCode = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ArmCodeLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ArmCode = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(ArmCodeLength)));

        if(ArmCode == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)ArmCode, sizeof(uint8_t), ArmCodeLength);
        }
    }
    else
        ArmCode = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Get_Arm_Code(Cluster, ArmCodeLength, ArmCode);

        qsOutputLength = (4 + (QS_POINTER_HEADER_SIZE * 1));

      if(ArmCode != NULL)
         qsOutputLength = qsOutputLength + ((ArmCodeLength)*(1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_GET_ARM_CODE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ArmCode);

         if((qsResult == ssSuccess) && (ArmCode != NULL))
         {
             qsResult = PackedWrite_Array(qsOutputBuffer, (void *)ArmCode, sizeof(uint8_t), ArmCodeLength);
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Set_Panel_Status(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_CL_IASACE_Panel_Status_Info_t *PanelStatus = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        PanelStatus = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_IASACE_Panel_Status_Info_t));

        if(PanelStatus == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_IASACE_Panel_Status_Info_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_IASACE_Panel_Status_Info_t *)PanelStatus);
        }
    }
    else
        PanelStatus = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Set_Panel_Status(Cluster, PanelStatus);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_SET_PANEL_STATUS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Get_Panel_Status(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_CL_IASACE_Panel_Status_Info_t *PanelStatus = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        PanelStatus = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_IASACE_Panel_Status_Info_t));

        if(PanelStatus == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_IASACE_Panel_Status_Info_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_IASACE_Panel_Status_Info_t *)PanelStatus);
        }
    }
    else
        PanelStatus = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Get_Panel_Status(Cluster, PanelStatus);

        qsOutputLength = (4 + (CalcPackedSize_qapi_ZB_CL_IASACE_Panel_Status_Info_t((qapi_ZB_CL_IASACE_Panel_Status_Info_t *)PanelStatus)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_GET_PANEL_STATUS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)PanelStatus);

         if((qsResult == ssSuccess) && (PanelStatus != NULL))
         {
             qsResult = PackedWrite_qapi_ZB_CL_IASACE_Panel_Status_Info_t(qsOutputBuffer, (qapi_ZB_CL_IASACE_Panel_Status_Info_t *)PanelStatus);
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Add_Zone(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_CL_IASACE_Zone_Table_Entry_t *Request = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Request = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_IASACE_Zone_Table_Entry_t));

        if(Request == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_IASACE_Zone_Table_Entry_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_IASACE_Zone_Table_Entry_t *)Request);
        }
    }
    else
        Request = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Add_Zone(Cluster, Request);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_ADD_ZONE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Delete_Zone(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ZoneID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ZoneID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Delete_Zone(Cluster, ZoneID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_DELETE_ZONE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Set_Zone_Status(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ZoneID;
    uint16_t ZoneStatus;
    uint8_t AudibleNotification;
    qapi_ZB_CL_IASACE_Alarm_Status_t AlarmStatus;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ZoneID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&ZoneStatus);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AudibleNotification);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&AlarmStatus);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Set_Zone_Status(Cluster, ZoneID, ZoneStatus, AudibleNotification, AlarmStatus);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_SET_ZONE_STATUS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Set_Bypass_Permit(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ZoneID;
    qbool_t Permit;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ZoneID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Permit);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Set_Bypass_Permit(Cluster, ZoneID, Permit);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_SET_BYPASS_PERMIT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Set_Bypass(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ZoneID;
    qbool_t Bypass;
    qapi_ZB_CL_IASACE_Bypass_Result_t *BypassResult = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ZoneID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Bypass);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        BypassResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_IASACE_Bypass_Result_t));

        if(BypassResult == NULL)
            qsResult = ssAllocationError;
    }
    else
        BypassResult= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Set_Bypass(Cluster, ZoneID, Bypass, BypassResult);

        qsOutputLength = (4 + (BypassResult == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_SET_BYPASS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)BypassResult);

         if((qsResult == ssSuccess) && (BypassResult != NULL))
         {
             qsResult = PackedWrite_int(qsOutputBuffer, (int *)BypassResult);
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Find_Zone_By_ID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ZoneID;
    qapi_ZB_CL_IASACE_Zone_Table_Entry_t *ZoneInfo = NULL;
    uint16_t *ZoneStatus = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ZoneID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ZoneStatus = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(ZoneStatus == NULL)
            qsResult = ssAllocationError;
    }
    else
        ZoneStatus= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ZoneInfo = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_IASACE_Zone_Table_Entry_t));

        if(ZoneInfo == NULL)
            qsResult = ssAllocationError;
    }
    else
        ZoneInfo= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Find_Zone_By_ID(Cluster, ZoneID, ZoneInfo, ZoneStatus);

        qsOutputLength = (4 + (CalcPackedSize_qapi_ZB_CL_IASACE_Zone_Table_Entry_t((qapi_ZB_CL_IASACE_Zone_Table_Entry_t *)ZoneInfo)) + (ZoneStatus == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_FIND_ZONE_BY_ID_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ZoneStatus);

         if((qsResult == ssSuccess) && (ZoneStatus != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)ZoneStatus);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ZoneInfo);

         if((qsResult == ssSuccess) && (ZoneInfo != NULL))
         {
             qsResult = PackedWrite_qapi_ZB_CL_IASACE_Zone_Table_Entry_t(qsOutputBuffer, (qapi_ZB_CL_IASACE_Zone_Table_Entry_t *)ZoneInfo);
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Find_Zone_By_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint64_t ZoneAddress;
    qapi_ZB_CL_IASACE_Zone_Table_Entry_t *ZoneInfo = NULL;
    uint16_t *ZoneStatus = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_64(&qsInputBuffer, &qsBufferList, (uint64_t *)&ZoneAddress);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ZoneStatus = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(ZoneStatus == NULL)
            qsResult = ssAllocationError;
    }
    else
        ZoneStatus= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ZoneInfo = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_IASACE_Zone_Table_Entry_t));

        if(ZoneInfo == NULL)
            qsResult = ssAllocationError;
    }
    else
        ZoneInfo= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Find_Zone_By_Address(Cluster, ZoneAddress, ZoneInfo, ZoneStatus);

        qsOutputLength = (4 + (CalcPackedSize_qapi_ZB_CL_IASACE_Zone_Table_Entry_t((qapi_ZB_CL_IASACE_Zone_Table_Entry_t *)ZoneInfo)) + (ZoneStatus == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_FIND_ZONE_BY_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ZoneStatus);

         if((qsResult == ssSuccess) && (ZoneStatus != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)ZoneStatus);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ZoneInfo);

         if((qsResult == ssSuccess) && (ZoneInfo != NULL))
         {
             qsResult = PackedWrite_qapi_ZB_CL_IASACE_Zone_Table_Entry_t(qsOutputBuffer, (qapi_ZB_CL_IASACE_Zone_Table_Entry_t *)ZoneInfo);
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

SerStatus_t Handle_qapi_ZB_CL_IASACE_Server_Get_Zone_List(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    /* Create a temporary variable for the length of ZoneList. */
    uint32_t qsTmp_ListSize = 0;
    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Function parameters. */
    qapi_ZB_Cluster_t Cluster;
    uint8_t *ListSize = NULL;
    uint8_t *ZoneList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ListSize = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(ListSize == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)ListSize);
        }
    }
    else
        ListSize = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (ListSize != NULL))
    {
        ZoneList = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(*ListSize)));

        if(ZoneList == NULL)
            qsResult = ssAllocationError;
    }
    else
        ZoneList= NULL;

    if(ListSize != NULL)
      qsTmp_ListSize = *ListSize;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_IASACE_Server_Get_Zone_List(Cluster, ListSize, ZoneList);

        qsOutputLength = (4 + (ListSize == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 2));

      if((ListSize != NULL) && (ZoneList != NULL))
      {
         if(qsTmp_ListSize > *ListSize)
            qsTmp_ListSize = *ListSize;
         qsOutputLength = qsOutputLength + ((qsTmp_ListSize)*(1));
      }

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_IAS_ACE_FILE_ID, QAPI_ZB_CL_IASACE_SERVER_GET_ZONE_LIST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ListSize);

         if((qsResult == ssSuccess) && (ListSize != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)ListSize);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ZoneList);

         if((qsResult == ssSuccess) && (ZoneList != NULL) && (ListSize != NULL))
         {
             qsResult = PackedWrite_Array(qsOutputBuffer, (void *)ZoneList, sizeof(uint8_t), qsTmp_ListSize);
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
