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
#include "qapi_zb_cl_wincover_common.h"
#include "qapi_zb_cl_common.h"

uint32_t CalcPackedSize_qapi_ZB_CL_WinCover_Client_Event_Data_t(qapi_ZB_CL_WinCover_Client_Event_Data_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_DATA_T_MIN_PACKED_SIZE;

        switch(Structure->Event_Type)
        {
            case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_ATTR_CUSTOM_READ_E:
                qsResult += CalcPackedSize_qapi_ZB_CL_Attr_Custom_Read_t((qapi_ZB_CL_Attr_Custom_Read_t *)&Structure->Data.Attr_Custom_Read);
                break;
            case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_ATTR_CUSTOM_WRITE_E:
                qsResult += CalcPackedSize_qapi_ZB_CL_Attr_Custom_Write_t((qapi_ZB_CL_Attr_Custom_Write_t *)&Structure->Data.Attr_Custom_Write);
                break;
            case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_DEFAULT_RESPONSE_E:
                qsResult += CalcPackedSize_qapi_ZB_CL_Default_Response_t((qapi_ZB_CL_Default_Response_t *)&Structure->Data.Default_Response);
                break;
            case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_COMMAND_COMPLETE_E:
                qsResult += CalcPackedSize_qapi_ZB_CL_Command_Complete_t((qapi_ZB_CL_Command_Complete_t *)&Structure->Data.Command_Complete);
                break;
            case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_UNPARSED_RESPONSE_E:
                qsResult += CalcPackedSize_qapi_ZB_CL_Unparsed_Response_t((qapi_ZB_CL_Unparsed_Response_t *)&Structure->Data.Unparsed_Response);
                break;
            default:
                break;
        }
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_ZB_CL_WinCover_Server_Action_t(qapi_ZB_CL_WinCover_Server_Action_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_ZB_CL_WINCOVER_SERVER_ACTION_T_MIN_PACKED_SIZE;
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_ZB_CL_WinCover_Server_Event_Data_t(qapi_ZB_CL_WinCover_Server_Event_Data_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_ZB_CL_WINCOVER_SERVER_EVENT_DATA_T_MIN_PACKED_SIZE;

        switch(Structure->Event_Type)
        {
            case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_ATTR_CUSTOM_READ_E:
                qsResult += CalcPackedSize_qapi_ZB_CL_Attr_Custom_Read_t((qapi_ZB_CL_Attr_Custom_Read_t *)&Structure->Data.Attr_Custom_Read);
                break;
            case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_ATTR_CUSTOM_WRITE_E:
                qsResult += CalcPackedSize_qapi_ZB_CL_Attr_Custom_Write_t((qapi_ZB_CL_Attr_Custom_Write_t *)&Structure->Data.Attr_Custom_Write);
                break;
            case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_UNPARSED_DATA_E:
                qsResult += CalcPackedSize_qapi_ZB_CL_Unparsed_Data_t((qapi_ZB_CL_Unparsed_Data_t *)&Structure->Data.Unparsed_Data);
                break;
            case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_ACTION_E:
                qsResult += CalcPackedSize_qapi_ZB_CL_WinCover_Server_Action_t((qapi_ZB_CL_WinCover_Server_Action_t *)&Structure->Data.Action);
                break;
            default:
                break;
        }
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_ZB_CL_WinCover_Client_Event_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_WinCover_Client_Event_Data_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_ZB_CL_WinCover_Client_Event_Data_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_int(Buffer, (int *)&Structure->Event_Type);

         if(qsResult == ssSuccess)
         {
             switch(Structure->Event_Type)
             {
                 case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_ATTR_CUSTOM_READ_E:
                  qsResult = PackedWrite_qapi_ZB_CL_Attr_Custom_Read_t(Buffer, (qapi_ZB_CL_Attr_Custom_Read_t *)&Structure->Data.Attr_Custom_Read);
                     break;
                 case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_ATTR_CUSTOM_WRITE_E:
                  qsResult = PackedWrite_qapi_ZB_CL_Attr_Custom_Write_t(Buffer, (qapi_ZB_CL_Attr_Custom_Write_t *)&Structure->Data.Attr_Custom_Write);
                     break;
                 case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_DEFAULT_RESPONSE_E:
                  qsResult = PackedWrite_qapi_ZB_CL_Default_Response_t(Buffer, (qapi_ZB_CL_Default_Response_t *)&Structure->Data.Default_Response);
                     break;
                 case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_COMMAND_COMPLETE_E:
                  qsResult = PackedWrite_qapi_ZB_CL_Command_Complete_t(Buffer, (qapi_ZB_CL_Command_Complete_t *)&Structure->Data.Command_Complete);
                     break;
                 case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_UNPARSED_RESPONSE_E:
                  qsResult = PackedWrite_qapi_ZB_CL_Unparsed_Response_t(Buffer, (qapi_ZB_CL_Unparsed_Response_t *)&Structure->Data.Unparsed_Response);
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

SerStatus_t PackedWrite_qapi_ZB_CL_WinCover_Server_Action_t(PackedBuffer_t *Buffer, qapi_ZB_CL_WinCover_Server_Action_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_ZB_CL_WinCover_Server_Action_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_int(Buffer, (int *)&Structure->Action);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_ZB_CL_WinCover_Server_Event_Data_t(PackedBuffer_t *Buffer, qapi_ZB_CL_WinCover_Server_Event_Data_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_ZB_CL_WinCover_Server_Event_Data_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_int(Buffer, (int *)&Structure->Event_Type);

         if(qsResult == ssSuccess)
         {
             switch(Structure->Event_Type)
             {
                 case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_ATTR_CUSTOM_READ_E:
                  qsResult = PackedWrite_qapi_ZB_CL_Attr_Custom_Read_t(Buffer, (qapi_ZB_CL_Attr_Custom_Read_t *)&Structure->Data.Attr_Custom_Read);
                     break;
                 case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_ATTR_CUSTOM_WRITE_E:
                  qsResult = PackedWrite_qapi_ZB_CL_Attr_Custom_Write_t(Buffer, (qapi_ZB_CL_Attr_Custom_Write_t *)&Structure->Data.Attr_Custom_Write);
                     break;
                 case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_UNPARSED_DATA_E:
                  qsResult = PackedWrite_qapi_ZB_CL_Unparsed_Data_t(Buffer, (qapi_ZB_CL_Unparsed_Data_t *)&Structure->Data.Unparsed_Data);
                     break;
                 case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_ACTION_E:
                  qsResult = PackedWrite_qapi_ZB_CL_WinCover_Server_Action_t(Buffer, (qapi_ZB_CL_WinCover_Server_Action_t *)&Structure->Data.Action);
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

SerStatus_t PackedRead_qapi_ZB_CL_WinCover_Client_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_WinCover_Client_Event_Data_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_DATA_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->Event_Type);

        if(qsResult == ssSuccess)
        {
            switch(Structure->Event_Type)
            {
                case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_ATTR_CUSTOM_READ_E:
                    qsResult = PackedRead_qapi_ZB_CL_Attr_Custom_Read_t(Buffer, BufferList, (qapi_ZB_CL_Attr_Custom_Read_t *)&Structure->Data.Attr_Custom_Read);
                    break;
                case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_ATTR_CUSTOM_WRITE_E:
                    qsResult = PackedRead_qapi_ZB_CL_Attr_Custom_Write_t(Buffer, BufferList, (qapi_ZB_CL_Attr_Custom_Write_t *)&Structure->Data.Attr_Custom_Write);
                    break;
                case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_DEFAULT_RESPONSE_E:
                    qsResult = PackedRead_qapi_ZB_CL_Default_Response_t(Buffer, BufferList, (qapi_ZB_CL_Default_Response_t *)&Structure->Data.Default_Response);
                    break;
                case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_COMMAND_COMPLETE_E:
                    qsResult = PackedRead_qapi_ZB_CL_Command_Complete_t(Buffer, BufferList, (qapi_ZB_CL_Command_Complete_t *)&Structure->Data.Command_Complete);
                    break;
                case QAPI_ZB_CL_WINCOVER_CLIENT_EVENT_TYPE_UNPARSED_RESPONSE_E:
                    qsResult = PackedRead_qapi_ZB_CL_Unparsed_Response_t(Buffer, BufferList, (qapi_ZB_CL_Unparsed_Response_t *)&Structure->Data.Unparsed_Response);
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

SerStatus_t PackedRead_qapi_ZB_CL_WinCover_Server_Action_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_WinCover_Server_Action_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_ZB_CL_WINCOVER_SERVER_ACTION_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->Action);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_ZB_CL_WinCover_Server_Event_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_ZB_CL_WinCover_Server_Event_Data_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_ZB_CL_WINCOVER_SERVER_EVENT_DATA_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_int(Buffer, BufferList, (int *)&Structure->Event_Type);

        if(qsResult == ssSuccess)
        {
            switch(Structure->Event_Type)
            {
                case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_ATTR_CUSTOM_READ_E:
                    qsResult = PackedRead_qapi_ZB_CL_Attr_Custom_Read_t(Buffer, BufferList, (qapi_ZB_CL_Attr_Custom_Read_t *)&Structure->Data.Attr_Custom_Read);
                    break;
                case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_ATTR_CUSTOM_WRITE_E:
                    qsResult = PackedRead_qapi_ZB_CL_Attr_Custom_Write_t(Buffer, BufferList, (qapi_ZB_CL_Attr_Custom_Write_t *)&Structure->Data.Attr_Custom_Write);
                    break;
                case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_UNPARSED_DATA_E:
                    qsResult = PackedRead_qapi_ZB_CL_Unparsed_Data_t(Buffer, BufferList, (qapi_ZB_CL_Unparsed_Data_t *)&Structure->Data.Unparsed_Data);
                    break;
                case QAPI_ZB_CL_WINCOVER_SERVER_EVENT_TYPE_ACTION_E:
                    qsResult = PackedRead_qapi_ZB_CL_WinCover_Server_Action_t(Buffer, BufferList, (qapi_ZB_CL_WinCover_Server_Action_t *)&Structure->Data.Action);
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
