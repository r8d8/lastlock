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
#include "qapi_zb_cl_qz_mnl.h"
#include "qapi_zb_cl_common.h"
#include "qapi_zb_cl_qz_cb.h"

SerStatus_t Handle_qapi_ZB_CL_Register_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint32_t CB_Param;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ZB_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CB_Param);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Register_Callback(ZB_Handle, QZ_qapi_ZB_CL_Event_CB_t_Handler, CB_Param);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_REGISTER_CALLBACK_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Unregister_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ZB_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Unregister_Callback(ZB_Handle, QZ_qapi_ZB_CL_Event_CB_t_Handler);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_UNREGISTER_CALLBACK_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Create_Cluster(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_ZB_CL_Create_Cluster(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_ZB_CL_Destroy_Cluster(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
        qsRetVal = qapi_ZB_CL_Destroy_Cluster(Cluster);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_DESTROY_CLUSTER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Get_Cluster_Info(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *Endpoint = NULL;
    uint16_t *ProfileId = NULL;
    uint16_t *ClusterId = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Endpoint = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(Endpoint == NULL)
            qsResult = ssAllocationError;
    }
    else
        Endpoint= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ProfileId = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(ProfileId == NULL)
            qsResult = ssAllocationError;
    }
    else
        ProfileId= NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        ClusterId = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(ClusterId == NULL)
            qsResult = ssAllocationError;
    }
    else
        ClusterId= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Get_Cluster_Info(Cluster, Endpoint, ProfileId, ClusterId);

        qsOutputLength = (4 + (Endpoint == NULL ? 0 : 1) + (ProfileId == NULL ? 0 : 2) + (ClusterId == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 3));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_GET_CLUSTER_INFO_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Endpoint);

         if((qsResult == ssSuccess) && (Endpoint != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Endpoint);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ProfileId);

         if((qsResult == ssSuccess) && (ProfileId != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)ProfileId);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ClusterId);

         if((qsResult == ssSuccess) && (ClusterId != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)ClusterId);
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

SerStatus_t Handle_qapi_ZB_CL_Set_Profile_ID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t ProfileID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&ProfileID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Set_Profile_ID(Cluster, ProfileID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_SET_PROFILE_ID_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Set_Min_Security(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_CL_Security_Level_t MinSecurity;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&MinSecurity);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Set_Min_Security(Cluster, MinSecurity);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_SET_MIN_SECURITY_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Set_Tx_Options(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t TxOptions;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&TxOptions);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Set_Tx_Options(Cluster, TxOptions);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_SET_TX_OPTIONS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Get_Tx_Options(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *TxOptions = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        TxOptions = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(TxOptions == NULL)
            qsResult = ssAllocationError;
    }
    else
        TxOptions= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Get_Tx_Options(Cluster, TxOptions);

        qsOutputLength = (4 + (TxOptions == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_GET_TX_OPTIONS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)TxOptions);

         if((qsResult == ssSuccess) && (TxOptions != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)TxOptions);
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

SerStatus_t Handle_qapi_ZB_CL_Set_Discover_Route(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qbool_t DiscoverRoute;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&DiscoverRoute);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Set_Discover_Route(Cluster, DiscoverRoute);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_SET_DISCOVER_ROUTE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Get_Discover_Route(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qbool_t *DiscoverRoute = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        DiscoverRoute = AllocateBufferListEntry(&qsBufferList, sizeof(qbool_t));

        if(DiscoverRoute == NULL)
            qsResult = ssAllocationError;
    }
    else
        DiscoverRoute= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Get_Discover_Route(Cluster, DiscoverRoute);

        qsOutputLength = (4 + (DiscoverRoute == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_GET_DISCOVER_ROUTE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)DiscoverRoute);

         if((qsResult == ssSuccess) && (DiscoverRoute != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)DiscoverRoute);
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

SerStatus_t Handle_qapi_ZB_CL_Set_Radius(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t Radius;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Radius);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Set_Radius(Cluster, Radius);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_SET_RADIUS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Get_Radius(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t *Radius = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Radius = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(Radius == NULL)
            qsResult = ssAllocationError;
    }
    else
        Radius= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Get_Radius(Cluster, Radius);

        qsOutputLength = (4 + (Radius == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_GET_RADIUS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Radius);

         if((qsResult == ssSuccess) && (Radius != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Radius);
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

SerStatus_t Handle_qapi_ZB_CL_Send_Command(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qbool_t ResponseExpected;
    qapi_ZB_CL_Header_t *ZCL_Header = NULL;
    uint16_t PayloadLength;
    uint8_t *Payload = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ResponseExpected);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&PayloadLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Payload = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(PayloadLength)));

        if(Payload == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Payload, sizeof(uint8_t), PayloadLength);
        }
    }
    else
        Payload = NULL;

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
        ZCL_Header = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_ZB_CL_Header_t));

        if(ZCL_Header == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_ZB_CL_Header_t(&qsInputBuffer, &qsBufferList, (qapi_ZB_CL_Header_t *)ZCL_Header);
        }
    }
    else
        ZCL_Header = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Send_Command(Cluster, SendInfo, ResponseExpected, ZCL_Header, PayloadLength, Payload);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_SEND_COMMAND_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Read_Local_Attribute(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_ZB_Cluster_t Cluster;
    uint16_t AttrId;
    uint16_t *Length = NULL;
    uint8_t *Data = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

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
        qsRetVal = qapi_ZB_CL_Read_Local_Attribute(Cluster, AttrId, Length, Data);

        qsOutputLength = (4 + (Length == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

      if((Length != NULL) && (Data != NULL))
      {
         if(qsTmp_Length > *Length)
            qsTmp_Length = *Length;
         qsOutputLength = qsOutputLength + ((qsTmp_Length)*(1));
      }

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_READ_LOCAL_ATTRIBUTE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Write_Local_Attribute(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t AttrId;
    uint16_t Length;
    uint8_t *Data = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

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
        qsRetVal = qapi_ZB_CL_Write_Local_Attribute(Cluster, AttrId, Length, Data);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_WRITE_LOCAL_ATTRIBUTE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Read_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t AttrCount;
    uint16_t *AttrIdList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AttrCount);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        AttrIdList = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(AttrCount)));

        if(AttrIdList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)AttrIdList, sizeof(uint16_t), AttrCount);
        }
    }
    else
        AttrIdList = NULL;

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
        qsRetVal = qapi_ZB_CL_Read_Attributes(Cluster, SendInfo, AttrCount, AttrIdList);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_READ_ATTRIBUTES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Write_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t AttrCount;
    qapi_ZB_CL_Write_Attr_Record_t *AttrRecordList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AttrCount);

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
        AttrRecordList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_ZB_CL_Write_Attr_Record_t)*(AttrCount)));

        if(AttrRecordList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < AttrCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_ZB_CL_Write_Attr_Record_t(&qsInputBuffer, &qsBufferList, &((qapi_ZB_CL_Write_Attr_Record_t *)AttrRecordList)[qsIndex]);
            }
        }
    }
    else
        AttrRecordList = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Write_Attributes(Cluster, SendInfo, AttrCount, AttrRecordList);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_WRITE_ATTRIBUTES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Configure_Reporting(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ReportCount;
    qapi_ZB_CL_Attr_Reporting_Config_Record_t *ReportRecordList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ReportCount);

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
        ReportRecordList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_ZB_CL_Attr_Reporting_Config_Record_t)*(ReportCount)));

        if(ReportRecordList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < ReportCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_ZB_CL_Attr_Reporting_Config_Record_t(&qsInputBuffer, &qsBufferList, &((qapi_ZB_CL_Attr_Reporting_Config_Record_t *)ReportRecordList)[qsIndex]);
            }
        }
    }
    else
        ReportRecordList = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Configure_Reporting(Cluster, SendInfo, ReportCount, ReportRecordList);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_CONFIGURE_REPORTING_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Read_Reporting_Config(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ReportCount;
    qapi_ZB_CL_Attr_Record_t *ReportConfigList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ReportCount);

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
        ReportConfigList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_ZB_CL_Attr_Record_t)*(ReportCount)));

        if(ReportConfigList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < ReportCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_ZB_CL_Attr_Record_t(&qsInputBuffer, &qsBufferList, &((qapi_ZB_CL_Attr_Record_t *)ReportConfigList)[qsIndex]);
            }
        }
    }
    else
        ReportConfigList = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Read_Reporting_Config(Cluster, SendInfo, ReportCount, ReportConfigList);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_READ_REPORTING_CONFIG_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Discover_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint16_t StartAttrId;
    uint8_t AttrIdCount;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&StartAttrId);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AttrIdCount);

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
        qsRetVal = qapi_ZB_CL_Discover_Attributes(Cluster, SendInfo, StartAttrId, AttrIdCount);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_DISCOVER_ATTRIBUTES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Read_Attributes_Structured(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t AttrCount;
    qapi_ZB_CL_Read_Attr_Structured_t *AttrStructuredList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AttrCount);

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
        AttrStructuredList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_ZB_CL_Read_Attr_Structured_t)*(AttrCount)));

        if(AttrStructuredList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < AttrCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_ZB_CL_Read_Attr_Structured_t(&qsInputBuffer, &qsBufferList, &((qapi_ZB_CL_Read_Attr_Structured_t *)AttrStructuredList)[qsIndex]);
            }
        }
    }
    else
        AttrStructuredList = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Read_Attributes_Structured(Cluster, SendInfo, AttrCount, AttrStructuredList);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_READ_ATTRIBUTES_STRUCTURED_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Write_Attributes_Structured(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t AttrCount;
    qapi_ZB_CL_Write_Attr_Structured_Record_t *AttrStructuredList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&AttrCount);

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
        AttrStructuredList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_ZB_CL_Write_Attr_Structured_Record_t)*(AttrCount)));

        if(AttrStructuredList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < AttrCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_ZB_CL_Write_Attr_Structured_Record_t(&qsInputBuffer, &qsBufferList, &((qapi_ZB_CL_Write_Attr_Structured_Record_t *)AttrStructuredList)[qsIndex]);
            }
        }
    }
    else
        AttrStructuredList = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Write_Attributes_Structured(Cluster, SendInfo, AttrCount, AttrStructuredList);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_WRITE_ATTRIBUTES_STRUCTURED_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Report_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t ReportCount;
    qapi_ZB_CL_Attr_Report_t *ReportList = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ReportCount);

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
        ReportList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_ZB_CL_Attr_Report_t)*(ReportCount)));

        if(ReportList == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            for (qsIndex = 0; qsIndex < ReportCount; qsIndex++)
            {
                if(qsResult == ssSuccess)
                    qsResult = PackedRead_qapi_ZB_CL_Attr_Report_t(&qsInputBuffer, &qsBufferList, &((qapi_ZB_CL_Attr_Report_t *)ReportList)[qsIndex]);
            }
        }
    }
    else
        ReportList = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Report_Attributes(Cluster, SendInfo, ReportCount, ReportList);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_REPORT_ATTRIBUTES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Default_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_Status_t Status;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Status);

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

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Default_Response(Cluster, APSDEData, ZCLHeader, Status);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_DEFAULT_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_ZB_CL_Generic_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    uint8_t CommandId;
    uint8_t PayloadLength;
    uint8_t *PayLoad = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Cluster);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&CommandId);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&PayloadLength);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        PayLoad = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(PayloadLength)));

        if(PayLoad == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)PayLoad, sizeof(uint8_t), PayloadLength);
        }
    }
    else
        PayLoad = NULL;

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

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_ZB_CL_Generic_Response(Cluster, APSDEData, ZCLHeader, CommandId, PayloadLength, PayLoad);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_ZB, QAPI_ZB_CL_FILE_ID, QAPI_ZB_CL_GENERIC_RESPONSE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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
