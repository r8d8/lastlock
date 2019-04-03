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
#include "qapi_zb.h"
#include "qsCommon.h"
#include "qsPack.h"
#include "qapi_zb_zdp_common.h"
#include "qapi_zb_zdp_common_mnl.h"
#include "qapi_zb_common.h"
#include "qapi_zb_aps_common.h"

uint32_t Mnl_CalcPackedSize_qapi_ZB_ZDP_Extended_Simple_Desc_Rsp_t(qapi_ZB_ZDP_Extended_Simple_Desc_Rsp_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_ZB_ZDP_EXTENDED_SIMPLE_DESC_RSP_T_MIN_PACKED_SIZE;

        if(Structure->AppClusterList != NULL)
        {
            qsResult += (((Structure->AppInputClusterCount) + (Structure->AppOutputClusterCount)) * (2));
        }
    }

    return(qsResult);
}

SerStatus_t Mnl_PackedWrite_qapi_ZB_ZDP_Extended_Simple_Desc_Rsp_t(PackedBuffer_t *Buffer, qapi_ZB_ZDP_Extended_Simple_Desc_Rsp_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    uint32_t    qsIndex;
    uint8_t     totalClusterCount;

    if(Buffer->Remaining >= CalcPackedSize_qapi_ZB_ZDP_Extended_Simple_Desc_Rsp_t(Structure))
    {
        if(Structure != NULL)
        {
            if(qsResult == ssSuccess)
                qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->Status);

            if(qsResult == ssSuccess)
                qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->NwkAddrOfInterest);

            if(qsResult == ssSuccess)
                qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Endpoint);

            if(qsResult == ssSuccess)
                qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->AppInputClusterCount);

            if(qsResult == ssSuccess)
                qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->AppOutputClusterCount);

            if(qsResult == ssSuccess)
                qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->StartIndex);

            if(qsResult == ssSuccess)
                qsResult = PackedWrite_PointerHeader(Buffer, (void *)Structure->AppClusterList);

            if((qsResult == ssSuccess) && (Structure->AppClusterList != NULL))
            {
                totalClusterCount = ((Structure->AppInputClusterCount) + (Structure->AppOutputClusterCount));
                for (qsIndex = 0; ((qsIndex < totalClusterCount) && (qsResult == ssSuccess)); qsIndex++)
                {
                    qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->AppClusterList[qsIndex]);
                }
            }
        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t Mnl_PackedRead_qapi_ZB_ZDP_Extended_Simple_Desc_Rsp_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_ZDP_Extended_Simple_Desc_Rsp_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_ZB_ZDP_EXTENDED_SIMPLE_DESC_RSP_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->Status);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->NwkAddrOfInterest);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Endpoint);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->AppInputClusterCount);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->AppOutputClusterCount);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->StartIndex);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_PointerHeader(Buffer, BufferList, &qsPointerValid);

        if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
        {
            Structure->AppClusterList = AllocateBufferListEntry(BufferList, (sizeof(uint16_t)*((Structure->AppInputClusterCount) + (Structure->AppOutputClusterCount))));

            if(Structure->AppClusterList == NULL)
            {
                qsResult = ssAllocationError;
            }
            else
            {
                qsResult = PackedRead_Array(Buffer, BufferList, (void *)Structure->AppClusterList, sizeof(uint16_t), ((Structure->AppInputClusterCount) + (Structure->AppOutputClusterCount)));
            }
        }
        else
            Structure->AppClusterList = NULL;
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}
