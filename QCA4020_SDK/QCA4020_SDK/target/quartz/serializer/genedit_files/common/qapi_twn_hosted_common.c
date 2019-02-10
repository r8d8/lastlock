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
#include "qapi_twn.h"
#include "qsCommon.h"
#include "qsPack.h"
#include "qapi_twn_hosted_common.h"
#include "qapi_twn_hosted_common_mnl.h"
#include "qapi_twn_common.h"

uint32_t CalcPackedSize_qapi_TWN_Hosted_Socket_Info_t(qapi_TWN_Hosted_Socket_Info_t *Structure)
{
    return(Mnl_CalcPackedSize_qapi_TWN_Hosted_Socket_Info_t(Structure));
}

uint32_t CalcPackedSize_qapi_TWN_Hosted_UDP_Transmit_Data_t(qapi_TWN_Hosted_UDP_Transmit_Data_t *Structure)
{
    return(Mnl_CalcPackedSize_qapi_TWN_Hosted_UDP_Transmit_Data_t(Structure));
}

uint32_t CalcPackedSize_qapi_TWN_Hosted_Event_Data_t(qapi_TWN_Hosted_Event_Data_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_TWN_HOSTED_EVENT_DATA_T_MIN_PACKED_SIZE;

        switch(Structure->Type)
        {
            case QAPI_TWN_HOSTED_UDP_TRANSMIT_E:
                if(Structure->Data.qapi_TWN_Hosted_UDP_Transmit_Data != NULL)
                    qsResult += CalcPackedSize_qapi_TWN_Hosted_UDP_Transmit_Data_t((qapi_TWN_Hosted_UDP_Transmit_Data_t *)Structure->Data.qapi_TWN_Hosted_UDP_Transmit_Data);
                break;
            default:
                break;
        }
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_TWN_Hosted_Socket_Info_t(PackedBuffer_t *Buffer, qapi_TWN_Hosted_Socket_Info_t *Structure)
{
    return(Mnl_PackedWrite_qapi_TWN_Hosted_Socket_Info_t(Buffer, Structure));
}

SerStatus_t PackedWrite_qapi_TWN_Hosted_UDP_Transmit_Data_t(PackedBuffer_t *Buffer, qapi_TWN_Hosted_UDP_Transmit_Data_t *Structure)
{
    return(Mnl_PackedWrite_qapi_TWN_Hosted_UDP_Transmit_Data_t(Buffer, Structure));
}

SerStatus_t PackedWrite_qapi_TWN_Hosted_Event_Data_t(PackedBuffer_t *Buffer, qapi_TWN_Hosted_Event_Data_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_TWN_Hosted_Event_Data_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_int(Buffer, (int *)&Structure->Type);

         if(qsResult == ssSuccess)
         {
             switch(Structure->Type)
             {
                 case QAPI_TWN_HOSTED_UDP_TRANSMIT_E:
                     qsResult = PackedWrite_qapi_TWN_Hosted_UDP_Transmit_Data_t(Buffer, (qapi_TWN_Hosted_UDP_Transmit_Data_t *)Structure->Data.qapi_TWN_Hosted_UDP_Transmit_Data);
                     break;
                 default:
                     break;
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

SerStatus_t PackedRead_qapi_TWN_Hosted_Socket_Info_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Hosted_Socket_Info_t *Structure)
{
    return(Mnl_PackedRead_qapi_TWN_Hosted_Socket_Info_t(Buffer, BufferList, Structure));
}

SerStatus_t PackedRead_qapi_TWN_Hosted_UDP_Transmit_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Hosted_UDP_Transmit_Data_t *Structure)
{
    return(Mnl_PackedRead_qapi_TWN_Hosted_UDP_Transmit_Data_t(Buffer, BufferList, Structure));
}

SerStatus_t PackedRead_qapi_TWN_Hosted_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_TWN_Hosted_Event_Data_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_TWN_HOSTED_EVENT_DATA_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->Type);

        if(qsResult == ssSuccess)
        {
            switch(Structure->Type)
            {
                case QAPI_TWN_HOSTED_UDP_TRANSMIT_E:
                    Structure->Data.qapi_TWN_Hosted_UDP_Transmit_Data = AllocateBufferListEntry(BufferList, sizeof(qapi_TWN_Hosted_UDP_Transmit_Data_t));

                    if(Structure->Data.qapi_TWN_Hosted_UDP_Transmit_Data == NULL)
                    {
                        qsResult = ssAllocationError;
                    }
                    else
                    {
                        qsResult = PackedRead_qapi_TWN_Hosted_UDP_Transmit_Data_t(Buffer, BufferList, (qapi_TWN_Hosted_UDP_Transmit_Data_t *)Structure->Data.qapi_TWN_Hosted_UDP_Transmit_Data);
                    }
                    break;
                default:
                    break;
            }
        }

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}
