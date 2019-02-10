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
#include "qapi_zb_zgp_common.h"
#include "qapi_zb_zgp_common_mnl.h"
#include "qapi_zb_common.h"

uint32_t CalcPackedSize_qapi_ZB_ZGP_GP_Data_Request_t(qapi_ZB_ZGP_GP_Data_Request_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_ZB_ZGP_GP_DATA_REQUEST_T_MIN_PACKED_SIZE;

        if(Structure->GPDASDU != NULL)
        {
            qsResult += (Structure->GPDASDULength);
        }
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_ZB_ZGP_Data_Confirm_t(qapi_ZB_ZGP_Data_Confirm_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_ZB_ZGP_DATA_CONFIRM_T_MIN_PACKED_SIZE;
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_ZB_ZGP_Key_Request_t(qapi_ZB_ZGP_Key_Request_t *Structure)
{
    return(Mnl_CalcPackedSize_qapi_ZB_ZGP_Key_Request_t(Structure));
}

uint32_t CalcPackedSize_qapi_ZB_ZGP_Event_t(qapi_ZB_ZGP_Event_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_ZB_ZGP_EVENT_T_MIN_PACKED_SIZE;

        switch(Structure->Event_Type)
        {
            case QAPI_ZB_ZGP_EVENT_TYPE_GP_DATA_CONFIRM_E:
                qsResult += CalcPackedSize_qapi_ZB_ZGP_Data_Confirm_t((qapi_ZB_ZGP_Data_Confirm_t *)&Structure->Data.GP_Data_Confirm);
                break;
            default:
                break;
        }
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_ZB_ZGP_GP_Data_Request_t(PackedBuffer_t *Buffer, qapi_ZB_ZGP_GP_Data_Request_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_ZB_ZGP_GP_Data_Request_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->TxOptions);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->ApplicationId);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->SrcId);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_64(Buffer, (uint64_t *)&Structure->GPDIEEEAddr);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Endpoint);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->GPDCommandId);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->GPDASDULength);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->GPEPHandle);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->gpTxQueueEntryLifeTime);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_PointerHeader(Buffer, (void *)Structure->GPDASDU);

         if((qsResult == ssSuccess) && (Structure->GPDASDU != NULL))
         {
             qsResult = PackedWrite_Array(Buffer, (void *)Structure->GPDASDU, sizeof(uint8_t), Structure->GPDASDULength);
         }

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_ZB_ZGP_Data_Confirm_t(PackedBuffer_t *Buffer, qapi_ZB_ZGP_Data_Confirm_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_ZB_ZGP_Data_Confirm_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->Status);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_32(Buffer, (uint32_t *)&Structure->GPEPHandle);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_ZB_ZGP_Key_Request_t(PackedBuffer_t *Buffer, qapi_ZB_ZGP_Key_Request_t *Structure)
{
    return(Mnl_PackedWrite_qapi_ZB_ZGP_Key_Request_t(Buffer, Structure));
}

SerStatus_t PackedWrite_qapi_ZB_ZGP_Event_t(PackedBuffer_t *Buffer, qapi_ZB_ZGP_Event_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_ZB_ZGP_Event_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_int(Buffer, (int *)&Structure->Event_Type);

         if(qsResult == ssSuccess)
         {
             switch(Structure->Event_Type)
             {
                 case QAPI_ZB_ZGP_EVENT_TYPE_GP_DATA_CONFIRM_E:
                  qsResult = PackedWrite_qapi_ZB_ZGP_Data_Confirm_t(Buffer, (qapi_ZB_ZGP_Data_Confirm_t *)&Structure->Data.GP_Data_Confirm);
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

SerStatus_t PackedRead_qapi_ZB_ZGP_GP_Data_Request_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_ZGP_GP_Data_Request_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_ZB_ZGP_GP_DATA_REQUEST_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->TxOptions);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->ApplicationId);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->SrcId);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_64(Buffer, BufferList, (uint64_t *)&Structure->GPDIEEEAddr);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Endpoint);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->GPDCommandId);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->GPDASDULength);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->GPEPHandle);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->gpTxQueueEntryLifeTime);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_PointerHeader(Buffer, BufferList, &qsPointerValid);

        if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
        {
            Structure->GPDASDU = AllocateBufferListEntry(BufferList, (sizeof(uint8_t)*(Structure->GPDASDULength)));

            if(Structure->GPDASDU == NULL)
            {
                qsResult = ssAllocationError;
            }
            else
            {
                qsResult = PackedRead_Array(Buffer, BufferList, (void *)Structure->GPDASDU, sizeof(uint8_t), Structure->GPDASDULength);
            }
        }
        else
            Structure->GPDASDU = NULL;

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_ZB_ZGP_Data_Confirm_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_ZGP_Data_Confirm_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_ZB_ZGP_DATA_CONFIRM_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->Status);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_32(Buffer, BufferList, (uint32_t *)&Structure->GPEPHandle);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_ZB_ZGP_Key_Request_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_ZGP_Key_Request_t *Structure)
{
    return(Mnl_PackedRead_qapi_ZB_ZGP_Key_Request_t(Buffer, BufferList, Structure));
}

SerStatus_t PackedRead_qapi_ZB_ZGP_Event_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_ZGP_Event_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_ZB_ZGP_EVENT_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->Event_Type);

        if(qsResult == ssSuccess)
        {
            switch(Structure->Event_Type)
            {
                case QAPI_ZB_ZGP_EVENT_TYPE_GP_DATA_CONFIRM_E:
                    qsResult = PackedRead_qapi_ZB_ZGP_Data_Confirm_t(Buffer, BufferList, (qapi_ZB_ZGP_Data_Confirm_t *)&Structure->Data.GP_Data_Confirm);
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
