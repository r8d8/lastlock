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
#include "qapi_zb_cl_ota_qz_mnl.h"
#include "qapi_zb_cl_ota_common.h"
#include "qapi_zb_cl_ota_qz_cb.h"

SerStatus_t Handle_qapi_ZB_CL_OTA_Create_Client(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_CL_OTA_Client_Config_t *Client_Config = NULL;
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

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Client_Config = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_OTA_Client_Config_t));

        if(Client_Config == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_OTA_Client_Config_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_OTA_Client_Config_t *)Client_Config);
        }
    }
    else
        Client_Config = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_OTA_Create_Client(ZB_Handle, Cluster, Cluster_Info, Client_Config, QZ_qapi_ZB_CL_OTA_Client_CB_t_Handler, CB_Param);

        qsOutputLength = (4 + (Cluster == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_CREATE_CLIENT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_OTA_Create_Server(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_CL_OTA_Server_Config_t *Server_Config = NULL;
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

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Server_Config = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_OTA_Server_Config_t));

        if(Server_Config == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_OTA_Server_Config_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_OTA_Server_Config_t *)Server_Config);
        }
    }
    else
        Server_Config = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_OTA_Create_Server(ZB_Handle, Cluster, Cluster_Info, Server_Config, QZ_qapi_ZB_CL_OTA_Server_CB_t_Handler, CB_Param);

        qsOutputLength = (4 + (Cluster == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_CREATE_SERVER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_OTA_Populate_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_OTA_Populate_Attributes(Server, AttributeCount, AttributeList);

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

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_POPULATE_ATTRIBUTES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_OTA_Client_Discover(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_ZB_CL_OTA_Client_Discover(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_ZB_CL_OTA_Client_Reset(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_OTA_Client_Reset(Cluster);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_CLIENT_RESET_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_OTA_Client_Upgrade_End(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_Status_t Status;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Status);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_OTA_Client_Upgrade_End(Cluster, Status);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_CLIENT_UPGRADE_END_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_OTA_Query_Next_Image(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_CL_OTA_Image_Definition_t *Image_Definition = NULL;
    uint8_t Field_Control;
    uint16_t Hardware_Version;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Field_Control);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&Hardware_Version);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Image_Definition = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_OTA_Image_Definition_t));

        if(Image_Definition == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_OTA_Image_Definition_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_OTA_Image_Definition_t *)Image_Definition);
        }
    }
    else
        Image_Definition = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_OTA_Query_Next_Image(Cluster, Image_Definition, Field_Control, Hardware_Version);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_QUERY_NEXT_IMAGE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_OTA_Image_Block_Start_Transfer(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_OTA_Image_Block_Start_Transfer(Cluster);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_IMAGE_BLOCK_START_TRANSFER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_OTA_Image_Notify(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_CL_General_Send_Info_t *Send_Info = NULL;
    uint8_t Notify_Payload_Type;
    uint8_t Jitter;
    qapi_ZB_CL_OTA_Image_Definition_t *Image_Definition = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Notify_Payload_Type);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Jitter);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Send_Info = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_General_Send_Info_t));

        if(Send_Info == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_General_Send_Info_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_General_Send_Info_t *)Send_Info);
        }
    }
    else
        Send_Info = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Image_Definition = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_OTA_Image_Definition_t));

        if(Image_Definition == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_OTA_Image_Definition_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_OTA_Image_Definition_t *)Image_Definition);
        }
    }
    else
        Image_Definition = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_OTA_Image_Notify(Cluster, Send_Info, Notify_Payload_Type, Jitter, Image_Definition);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_IMAGE_NOTIFY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_OTA_Image_Block_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_APSDE_Data_Indication_t *APSDEData = NULL;
    qapi_ZB_CL_Header_t *ZCLHeader = NULL;
    qapi_ZB_CL_OTA_Image_Block_Response_t *ResponseData = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        APSDEData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_APSDE_Data_Indication_t));

        if(APSDEData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_APSDE_Data_Indication_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_APSDE_Data_Indication_t *)APSDEData);
        }
    }
    else
        APSDEData = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ZCLHeader = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_Header_t));

        if(ZCLHeader == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_Header_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_Header_t *)ZCLHeader);
        }
    }
    else
        ZCLHeader = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ResponseData = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_OTA_Image_Block_Response_t));

        if(ResponseData == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_OTA_Image_Block_Response_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_OTA_Image_Block_Response_t *)ResponseData);
        }
    }
    else
        ResponseData = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_OTA_Image_Block_Response(Cluster, APSDEData, ZCLHeader, ResponseData);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_OTA_FILE_ID, QAPI_ZB_CL_OTA_IMAGE_BLOCK_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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
