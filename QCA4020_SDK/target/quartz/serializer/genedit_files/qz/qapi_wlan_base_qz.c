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
#include "qapi_wlan.h"
#include "qapi_wlan_base_qz_mnl.h"
#include "qapi_wlan_base_common.h"
#include "qapi_wlan_base_qz_cb.h"

SerStatus_t Handle_qapi_WLAN_Coex_Control(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_WLAN_Coex_Config_Data_t *data = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        data = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_WLAN_Coex_Config_Data_t));

        if(data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_WLAN_Coex_Config_Data_t(&qsInputBuffer, &qsBufferList, (qapi_WLAN_Coex_Config_Data_t *)data);
        }
    }
    else
        data = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Coex_Control(data);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_COEX_CONTROL_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_Get_WLAN_Coex_Stats(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_WLAN_Coex_Stats_t *WLAN_CoexStats = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        WLAN_CoexStats = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_WLAN_Coex_Stats_t));

        if(WLAN_CoexStats == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_WLAN_Coex_Stats_t(&qsInputBuffer, &qsBufferList, (qapi_WLAN_Coex_Stats_t *)WLAN_CoexStats);
        }
    }
    else
        WLAN_CoexStats = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_Get_WLAN_Coex_Stats(WLAN_CoexStats);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_GET_WLAN_COEX_STATS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_Enable(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    qapi_WLAN_Enable_e enable;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&enable);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Enable(enable);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_ENABLE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_Add_Device(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Add_Device(device_ID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_ADD_DEVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_Remove_Device(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Remove_Device(device_ID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_REMOVE_DEVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_Start_Scan(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;
    qapi_WLAN_Start_Scan_Params_t *scan_Params = NULL;
    qapi_WLAN_Store_Scan_Results_e store_Scan_Results;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&store_Scan_Results);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        scan_Params = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_WLAN_Start_Scan_Params_t));

        if(scan_Params == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_WLAN_Start_Scan_Params_t(&qsInputBuffer, &qsBufferList, (qapi_WLAN_Start_Scan_Params_t *)scan_Params);
        }
    }
    else
        scan_Params = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Start_Scan(device_ID, scan_Params, store_Scan_Results);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_START_SCAN_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_Get_Scan_Results(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    SerStatus_t        qsResult = ssSuccess;
    BufferListEntry_t *qsBufferList = NULL;
    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };
    uint32_t           qsOutputLength = 0;
    uint32_t           qsIndex = 0;
    Boolean_t          qsPointerValid = FALSE;

    /* Create a temporary variable for the length of scan_Info. */
    uint32_t qsTmp_num_Results = 0;
    UNUSED(qsPointerValid);
    UNUSED(qsIndex);

    /* Return value. */
    qapi_Status_t qsRetVal = 0;

    /* Function parameters. */
    uint8_t device_ID;
    qapi_WLAN_BSS_Scan_Info_t *scan_Info = NULL;
    int16_t *num_Results = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        num_Results = AllocateBufferListEntry(&qsBufferList, sizeof(int16_t));

        if(num_Results == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)num_Results);
        }
    }
    else
        num_Results = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (num_Results != NULL))
    {
        scan_Info = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_WLAN_BSS_Scan_Info_t)*(*num_Results)));

        if(scan_Info == NULL)
            qsResult = ssAllocationError;
    }
    else
        scan_Info= NULL;

    if(num_Results != NULL)
      qsTmp_num_Results = *num_Results;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Get_Scan_Results(device_ID, scan_Info, num_Results);

        qsOutputLength = (4 + (num_Results == NULL ? 0 : 2) + (QS_POINTER_HEADER_SIZE * 2));

      if((num_Results != NULL) && (scan_Info != NULL))
      {
         if(qsTmp_num_Results > *num_Results)
            qsTmp_num_Results = *num_Results;
         for (qsIndex = 0; qsIndex < qsTmp_num_Results; qsIndex++)
         {
            qsOutputLength = qsOutputLength + CalcPackedSize_qapi_WLAN_BSS_Scan_Info_t((qapi_WLAN_BSS_Scan_Info_t *)&scan_Info[qsIndex]);
         }
      }

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_GET_SCAN_RESULTS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)num_Results);

         if((qsResult == ssSuccess) && (num_Results != NULL))
         {
             qsResult = PackedWrite_16(qsOutputBuffer, (uint16_t *)num_Results);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)scan_Info);

         if((qsResult == ssSuccess) && (scan_Info != NULL) && (num_Results != NULL))
         {
             for (qsIndex = 0; qsIndex < qsTmp_num_Results; qsIndex++)
             {
                 if(qsResult == ssSuccess)
                     qsResult = PackedWrite_qapi_WLAN_BSS_Scan_Info_t(qsOutputBuffer, &((qapi_WLAN_BSS_Scan_Info_t *)scan_Info)[qsIndex]);
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

SerStatus_t Handle_qapi_WLAN_Commit(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Commit(device_ID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_COMMIT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_Set_Callback(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
    return(Mnl_Handle_qapi_WLAN_Set_Callback(qsBuffer, qsLength, qsOutputBuffer, uId));
}

SerStatus_t Handle_qapi_WLAN_Disconnect(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Disconnect(device_ID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_DISCONNECT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_Set_Param(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;
    uint16_t group_ID;
    uint16_t param_ID;
    void *data = NULL;
    uint32_t length;
    qapi_WLAN_Wait_For_Status_e wait_For_Status;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&group_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&param_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&length);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&wait_For_Status);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        data = AllocateBufferListEntry(&qsBufferList, (1*(length)));

        if(data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)data, 1, length);
        }
    }
    else
        data = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Set_Param(device_ID, group_ID, param_ID, data, length, wait_For_Status);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_SET_PARAM_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_Get_Param(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;
    uint16_t group_ID;
    uint16_t param_ID;
    void *data = NULL;
    uint32_t *length = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&group_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_16(&qsInputBuffer, &qsBufferList, (uint16_t *)&param_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        length = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(length == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)length);
        }
    }
    else
        length = NULL;

    if(!length || !(*length))
    {
        qsResult = ssInvalidParameter;
    }
    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (length != NULL))
    {
        data = AllocateBufferListEntry(&qsBufferList, (1*(*length)));

        if(data == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)data, 1, *length);
        }
    }
    else
        data = NULL;

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        length = AllocateBufferListEntry(&qsBufferList, sizeof(uint32_t));

        if(length == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)length);
        }
    }
    else
        length = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Get_Param(device_ID, group_ID, param_ID, data, length);

        qsOutputLength = (4 + (length == NULL ? 0 : 4) + (length == NULL ? 0 : 4) + (QS_POINTER_HEADER_SIZE * 3));

      if((length != NULL) && (data != NULL))
         qsOutputLength = qsOutputLength + ((*length)*(1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_GET_PARAM_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)length);

         if((qsResult == ssSuccess) && (length != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)length);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)data);

         if((qsResult == ssSuccess) && (data != NULL) && (length != NULL))
         {
             qsResult = PackedWrite_Array(qsOutputBuffer, (void *)data, 1, *length);
         }

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)length);

         if((qsResult == ssSuccess) && (length != NULL))
         {
             qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)length);
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

SerStatus_t Handle_qapi_WLAN_Suspend_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint32_t suspend_Time_In_Ms;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&suspend_Time_In_Ms);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Suspend_Start(suspend_Time_In_Ms);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_SUSPEND_START_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_Raw_Send(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;
    qapi_WLAN_Raw_Send_Params_t *raw_Params = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        raw_Params = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_WLAN_Raw_Send_Params_t));

        if(raw_Params == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_WLAN_Raw_Send_Params_t(&qsInputBuffer, &qsBufferList, (qapi_WLAN_Raw_Send_Params_t *)raw_Params);
        }
    }
    else
        raw_Params = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_Raw_Send(device_ID, raw_Params);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_RAW_SEND_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_WPS_Start(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;
    qapi_WLAN_WPS_Connect_Action_e connect_Action;
    qapi_WLAN_WPS_Mode_e mode;
    char *pin = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&connect_Action);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_int(&qsInputBuffer, &qsBufferList, (int *)&mode);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        pin = AllocateBufferListEntry(&qsBufferList, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));

        if(pin == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)pin, 1, (strlen((const char *)(&qsInputBuffer)->CurrentPos)+1));
        }
    }
    else
        pin = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_WPS_Start(device_ID, connect_Action, mode, pin);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_WPS_START_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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

SerStatus_t Handle_qapi_WLAN_WPS_Await_Completion(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint32_t device_ID;
    qapi_WLAN_Netparams_t *net_Params = NULL;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&device_ID);

    if(qsResult == ssSuccess)
        qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

    if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
    {
        net_Params = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_WLAN_Netparams_t));

        if(net_Params == NULL)
        {
            qsResult = ssAllocationError;
        }
        else
        {
            qsResult = PackedRead_qapi_WLAN_Netparams_t(&qsInputBuffer, &qsBufferList, (qapi_WLAN_Netparams_t *)net_Params);
        }
    }
    else
        net_Params = NULL;

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_WPS_Await_Completion(device_ID, net_Params);

        qsOutputLength = (4 + (CalcPackedSize_qapi_WLAN_Netparams_t((qapi_WLAN_Netparams_t *)net_Params)) + (QS_POINTER_HEADER_SIZE * 1));

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_WPS_AWAIT_COMPLETION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
        {
            /* Write return value and/or output parameters packed. */
             if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)net_Params);

         if((qsResult == ssSuccess) && (net_Params != NULL))
         {
             qsResult = PackedWrite_qapi_WLAN_Netparams_t(qsOutputBuffer, (qapi_WLAN_Netparams_t *)net_Params);
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

SerStatus_t Handle_qapi_WLAN_WPS_Connect(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
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
    uint8_t device_ID;

    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

    /* Read function parameters. */
    if(qsResult == ssSuccess)
        qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&device_ID);

    /* Call the QAPI function and handle the response. */
    if(qsResult == ssSuccess)
    {
        qsRetVal = qapi_WLAN_WPS_Connect(device_ID);

        qsOutputLength = 4;

        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_WLAN, QAPI_WLAN_BASE_FILE_ID, QAPI_WLAN_WPS_CONNECT_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
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
