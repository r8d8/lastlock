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
#include "qapi_twn.h"
#include "qapi_twn_qz_mnl.h"
#include "qapi_twn_common.h"
#include "qapi_twn_qz_cb.h"

SerStatus_t Handle_qapi_TWN_Initialize(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t *TWN_Handle = NULL;
    uint32_t CB_Param;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CB_Param);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        TWN_Handle = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_Handle_t));

        if(TWN_Handle == NULL)
            qsResult = ssAllocationError;
    }
    else
        TWN_Handle= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Initialize(TWN_Handle, QZ_qapi_TWN_Event_CB_t_Handler, CB_Param);

        qsOutputLength = (4 + (TWN_Handle == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_INITIALIZE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)TWN_Handle);

         if((qsResult == ssSuccess) && (TWN_Handle != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)TWN_Handle);
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

SerStatus_t Handle_qapi_TWN_Shutdown(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qapi_TWN_Shutdown(TWN_Handle);

    qsOutputLength = 0;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_SHUTDOWN_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Start(TWN_Handle);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_START_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Stop(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Stop(TWN_Handle);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_STOP_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Get_Device_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_Device_Configuration_t *Configuration = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Configuration = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_Device_Configuration_t));

        if(Configuration == NULL)
            qsResult = ssAllocationError;
    }
    else
        Configuration= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Get_Device_Configuration(TWN_Handle, Configuration);

        qsOutputLength = (4 + (CalcPackedSize_qapi_TWN_Device_Configuration_t((qapi_TWN_Device_Configuration_t *)Configuration)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_GET_DEVICE_CONFIGURATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Configuration);

         if((qsResult == ssSuccess) && (Configuration != NULL))
         {
             qsResult = PackedWrite_qapi_TWN_Device_Configuration_t(qsOutputBuffer, (qapi_TWN_Device_Configuration_t *)Configuration);
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

SerStatus_t Handle_qapi_TWN_Set_Device_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_Device_Configuration_t *Configuration = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Configuration = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_Device_Configuration_t));

        if(Configuration == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_Device_Configuration_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_Device_Configuration_t *)Configuration);
        }
    }
    else
        Configuration = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Set_Device_Configuration(TWN_Handle, Configuration);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_SET_DEVICE_CONFIGURATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Get_Network_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_Network_Configuration_t *Configuration = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Configuration = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_Network_Configuration_t));

        if(Configuration == NULL)
            qsResult = ssAllocationError;
    }
    else
        Configuration= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Get_Network_Configuration(TWN_Handle, Configuration);

        qsOutputLength = (4 + (CalcPackedSize_qapi_TWN_Network_Configuration_t((qapi_TWN_Network_Configuration_t *)Configuration)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_GET_NETWORK_CONFIGURATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Configuration);

         if((qsResult == ssSuccess) && (Configuration != NULL))
         {
             qsResult = PackedWrite_qapi_TWN_Network_Configuration_t(qsOutputBuffer, (qapi_TWN_Network_Configuration_t *)Configuration);
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

SerStatus_t Handle_qapi_TWN_Set_Network_Configuration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_Network_Configuration_t *Configuration = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Configuration = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_Network_Configuration_t));

        if(Configuration == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_Network_Configuration_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_Network_Configuration_t *)Configuration);
        }
    }
    else
        Configuration = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Set_Network_Configuration(TWN_Handle, Configuration);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_SET_NETWORK_CONFIGURATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Add_Border_Router(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_Border_Router_t *Border_Router = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Border_Router = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_Border_Router_t));

        if(Border_Router == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_Border_Router_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_Border_Router_t *)Border_Router);
        }
    }
    else
        Border_Router = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Add_Border_Router(TWN_Handle, Border_Router);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_ADD_BORDER_ROUTER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Remove_Border_Router(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_IPv6_Prefix_t *Prefix = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Prefix = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_IPv6_Prefix_t));

        if(Prefix == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_IPv6_Prefix_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_IPv6_Prefix_t *)Prefix);
        }
    }
    else
        Prefix = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Remove_Border_Router(TWN_Handle, Prefix);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_REMOVE_BORDER_ROUTER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Add_External_Route(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_External_Route_t *External_Route = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        External_Route = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_External_Route_t));

        if(External_Route == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_External_Route_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_External_Route_t *)External_Route);
        }
    }
    else
        External_Route = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Add_External_Route(TWN_Handle, External_Route);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_ADD_EXTERNAL_ROUTE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Remove_External_Route(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_IPv6_Prefix_t *Prefix = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Prefix = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_IPv6_Prefix_t));

        if(Prefix == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_IPv6_Prefix_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_IPv6_Prefix_t *)Prefix);
        }
    }
    else
        Prefix = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Remove_External_Route(TWN_Handle, Prefix);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_REMOVE_EXTERNAL_ROUTE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Register_Server_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Register_Server_Data(TWN_Handle);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_REGISTER_SERVER_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Set_IP_Stack_Integration(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qbool_t Enabled;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Enabled);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Set_IP_Stack_Integration(TWN_Handle, Enabled);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_SET_IP_STACK_INTEGRATION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Commissioner_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Start(TWN_Handle);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_START_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Commissioner_Stop(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Stop(TWN_Handle);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_STOP_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Commissioner_Add_Joiner(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    uint64_t Extended_Address;
    char *PSKd = NULL;
    uint32_t Timeout;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_64(&qsInputBuffer, &qsBufferList, (uint64_t *)&Extended_Address);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Timeout);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        PSKd = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

        if(PSKd == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)PSKd, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
        }
    }
    else
        PSKd = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Add_Joiner(TWN_Handle, Extended_Address, PSKd, Timeout);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_ADD_JOINER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Commissioner_Remove_Joiner(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    uint64_t Extended_Address;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_64(&qsInputBuffer, &qsBufferList, (uint64_t *)&Extended_Address);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Remove_Joiner(TWN_Handle, Extended_Address);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_REMOVE_JOINER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Commissioner_Set_Provisioning_URL(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    char *Provisioning_URL = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Provisioning_URL = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

        if(Provisioning_URL == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Provisioning_URL, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
        }
    }
    else
        Provisioning_URL = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Set_Provisioning_URL(TWN_Handle, Provisioning_URL);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_SET_PROVISIONING_URL_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Commissioner_Generate_PSKc(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    char *Passphrase = NULL;
    char *Network_Name = NULL;
    uint64_t Extended_PAN_ID;
    uint8_t *PSKc = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_64(&qsInputBuffer, &qsBufferList, (uint64_t *)&Extended_PAN_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Passphrase = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

        if(Passphrase == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Passphrase, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
        }
    }
    else
        Passphrase = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Network_Name = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

        if(Network_Name == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Network_Name, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
        }
    }
    else
        Network_Name = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        PSKc = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

        if(PSKc == NULL)
            qsResult = ssAllocationError;
    }
    else
        PSKc= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Generate_PSKc(TWN_Handle, Passphrase, Network_Name, Extended_PAN_ID, PSKc);

        qsOutputLength = (4 + (PSKc == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_GENERATE_PSKC_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)PSKc);

         if((qsResult == ssSuccess) && (PSKc != NULL))
         {
             qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)PSKc);
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

SerStatus_t Handle_qapi_TWN_Joiner_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_Joiner_Info_t *Joiner_Info = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Joiner_Info = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_Joiner_Info_t));

        if(Joiner_Info == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_Joiner_Info_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_Joiner_Info_t *)Joiner_Info);
        }
    }
    else
        Joiner_Info = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Joiner_Start(TWN_Handle, Joiner_Info);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_JOINER_START_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Joiner_Stop(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Joiner_Stop(TWN_Handle);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_JOINER_STOP_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Set_PSKc(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    uint8_t *PSKc = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        PSKc = AllocateBufferListEntry(&qsBufferList, 16);

        if(PSKc == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)PSKc, 1, 16);
        }
    }
    else
        PSKc = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Set_PSKc(TWN_Handle, PSKc);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_SET_PSKC_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_IPv6_Add_Unicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_IPv6_Prefix_t *Prefix = NULL;
    qbool_t Preferred;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Preferred);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Prefix = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_IPv6_Prefix_t));

        if(Prefix == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_IPv6_Prefix_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_IPv6_Prefix_t *)Prefix);
        }
    }
    else
        Prefix = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_IPv6_Add_Unicast_Address(TWN_Handle, Prefix, Preferred);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_IPV6_ADD_UNICAST_ADDRESS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_IPv6_Remove_Unicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_TWN_IPv6_Remove_Unicast_Address(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_TWN_IPv6_Subscribe_Multicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_TWN_IPv6_Subscribe_Multicast_Address(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_TWN_IPv6_Unsubscribe_Multicast_Address(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_TWN_IPv6_Unsubscribe_Multicast_Address(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_TWN_Set_Ping_Response_Enabled(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qbool_t Enabled;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Enabled);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Set_Ping_Response_Enabled(TWN_Handle, Enabled);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_SET_PING_RESPONSE_ENABLED_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Become_Router(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Become_Router(TWN_Handle);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_BECOME_ROUTER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Become_Leader(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Become_Leader(TWN_Handle);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_BECOME_LEADER_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Start_Border_Agent(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_TWN_Start_Border_Agent(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_TWN_Stop_Border_Agent(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_TWN_Stop_Border_Agent(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_TWN_Clear_Persistent_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Clear_Persistent_Data(TWN_Handle);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_CLEAR_PERSISTENT_DATA_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Set_Max_Poll_Period(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    uint32_t Period;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Period);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Set_Max_Poll_Period(TWN_Handle, Period);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_SET_MAX_POLL_PERIOD_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Commissioner_Send_Mgmt_Get(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    uint8_t *TlvBuffer = NULL;
    uint8_t Length;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        TlvBuffer = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

        if(TlvBuffer == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)TlvBuffer, sizeof(uint8_t), Length);
        }
    }
    else
        TlvBuffer = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Send_Mgmt_Get(TWN_Handle, TlvBuffer, Length);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_SEND_MGMT_GET_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Commissioner_Send_Mgmt_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_Commissioning_Dataset_t *Dataset = NULL;
    uint8_t *TlvBuffer = NULL;
    uint8_t Length;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        TlvBuffer = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

        if(TlvBuffer == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)TlvBuffer, sizeof(uint8_t), Length);
        }
    }
    else
        TlvBuffer = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Dataset = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_Commissioning_Dataset_t));

        if(Dataset == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_Commissioning_Dataset_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_Commissioning_Dataset_t *)Dataset);
        }
    }
    else
        Dataset = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Send_Mgmt_Set(TWN_Handle, Dataset, TlvBuffer, Length);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_SEND_MGMT_SET_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Commissioner_Send_PanId_Query(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_TWN_Commissioner_Send_PanId_Query(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_TWN_Commissioner_Get_Session_Id(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    uint16_t *SessionId = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        SessionId = AllocateBufferListEntry(&qsBufferList, sizeof(uint16_t));

        if(SessionId == NULL)
            qsResult = ssAllocationError;
    }
    else
        SessionId= NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Get_Session_Id(TWN_Handle, SessionId);

        qsOutputLength = (4 + (SessionId == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_GET_SESSION_ID_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)SessionId);

         if((qsResult == ssSuccess) && (SessionId != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)SessionId);
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

SerStatus_t Handle_qapi_TWN_Commissioner_Send_Mgmt_Active_Get(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_TWN_Commissioner_Send_Mgmt_Active_Get(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_TWN_Commissioner_Send_Mgmt_Active_Set(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_Operational_Dataset_t *Dataset = NULL;
    uint8_t *TlvBuffer = NULL;
    uint8_t Length;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        TlvBuffer = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Length)));

        if(TlvBuffer == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)TlvBuffer, sizeof(uint8_t), Length);
        }
    }
    else
        TlvBuffer = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        Dataset = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_TWN_Operational_Dataset_t));

        if(Dataset == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_TWN_Operational_Dataset_t(&qsInputBuffer, &qsBufferList, (qapi_TWN_Operational_Dataset_t *)Dataset);
        }
    }
    else
        Dataset = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Commissioner_Send_Mgmt_Active_Set(TWN_Handle, Dataset, TlvBuffer, Length);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_COMMISSIONER_SEND_MGMT_ACTIVE_SET_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Get_Unicast_Addresses(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    /* Create a temporary variable for the length of AddressList. */
    uint32_t qsTmp_AddressListSize = 0;
    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Function parameters. */
    qapi_TWN_Handle_t TWN_Handle;
    qapi_TWN_IPv6_Prefix_t *AddressList = NULL;
    uint32_t *AddressListSize = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        AddressListSize = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(AddressListSize == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)AddressListSize);
        }
    }
    else
        AddressListSize = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (AddressListSize != NULL))
    {
        AddressList = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_TWN_IPv6_Prefix_t)*(*AddressListSize)));

        if(AddressList == NULL)
            qsResult = ssAllocationError;
    }
    else
        AddressList= NULL;

    if(AddressListSize != NULL)
      qsTmp_AddressListSize = *AddressListSize;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Get_Unicast_Addresses(TWN_Handle, AddressList, AddressListSize);

        qsOutputLength = (4 + (AddressListSize == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 2));

      if((AddressListSize != NULL) && (AddressList != NULL))
      {
         if(qsTmp_AddressListSize > *AddressListSize)
            qsTmp_AddressListSize = *AddressListSize;
         for (qsIndex = 0; qsIndex < qsTmp_AddressListSize; qsIndex++)
         {
            qsOutputLength = qsOutputLength + CalcPackedSize_qapi_TWN_IPv6_Prefix_t((qapi_TWN_IPv6_Prefix_t *)&AddressList[qsIndex]);
         }
      }

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_GET_UNICAST_ADDRESSES_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)AddressListSize);

         if((qsResult == ssSuccess) && (AddressListSize != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)AddressListSize);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)AddressList);

         if((qsResult == ssSuccess) && (AddressList != NULL) && (AddressListSize != NULL))
         {
             for (qsIndex = 0; qsIndex < qsTmp_AddressListSize; qsIndex++)
             {
                 if(qsResult == ssSuccess)
                     qsResult = PackedWrite_qapi_TWN_IPv6_Prefix_t(qsOutputBuffer, &((qapi_TWN_IPv6_Prefix_t *)AddressList)[qsIndex]);
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

SerStatus_t Handle_qapi_TWN_Set_Key_Sequence(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    uint32_t Sequence;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Sequence);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Set_Key_Sequence(TWN_Handle, Sequence);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_SET_KEY_SEQUENCE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_TWN_Set_DTLS_Handshake_Timeout(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_TWN_Handle_t TWN_Handle;
    uint8_t Timeout;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&TWN_Handle);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Timeout);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_TWN_Set_DTLS_Handshake_Timeout(TWN_Handle, Timeout);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_TWN, QAPI_TWN_FILE_ID, QAPI_TWN_SET_DTLS_HANDSHAKE_TIMEOUT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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
