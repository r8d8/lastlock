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
#include "qapi_ble.h"
#include "qsCommon.h"
#include "qsPack.h"
#include "qapi_ble_cgmstypes_common.h"
#include "qapi_ble_bttypes_common.h"

uint32_t CalcPackedSize_qapi_BLE_CGMS_Time_Offset_Range_t(qapi_BLE_CGMS_Time_Offset_Range_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_BLE_CGMS_TIME_OFFSET_RANGE_T_MIN_PACKED_SIZE;

        qsResult += CalcPackedSize_16((uint16_t *)&Structure->Minimum);

        qsResult += CalcPackedSize_16((uint16_t *)&Structure->Maximum);
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_BLE_CGMS_RACP_Response_Code_t(qapi_BLE_CGMS_RACP_Response_Code_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_BLE_CGMS_RACP_RESPONSE_CODE_T_MIN_PACKED_SIZE;
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_BLE_CGMS_Calibration_Record_t(qapi_BLE_CGMS_Calibration_Record_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_BLE_CGMS_CALIBRATION_RECORD_T_MIN_PACKED_SIZE;

        qsResult += CalcPackedSize_16((uint16_t *)&Structure->Calibration_Glucose_Concentration);

        qsResult += CalcPackedSize_16((uint16_t *)&Structure->Calibration_Time);

        qsResult += CalcPackedSize_16((uint16_t *)&Structure->Next_Calibration_Time);

        qsResult += CalcPackedSize_16((uint16_t *)&Structure->Calibration_Data_Record_Number);
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_BLE_CGMS_Time_Offset_Range_t(PackedBuffer_t *Buffer, qapi_BLE_CGMS_Time_Offset_Range_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_CGMS_Time_Offset_Range_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->Minimum);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->Maximum);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_BLE_CGMS_RACP_Response_Code_t(PackedBuffer_t *Buffer, qapi_BLE_CGMS_RACP_Response_Code_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_CGMS_RACP_Response_Code_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Request_Op_Code);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Response_Code_Value);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_BLE_CGMS_Calibration_Record_t(PackedBuffer_t *Buffer, qapi_BLE_CGMS_Calibration_Record_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_CGMS_Calibration_Record_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->Calibration_Glucose_Concentration);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->Calibration_Time);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Calibration_Type_Sample_Location);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->Next_Calibration_Time);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->Calibration_Data_Record_Number);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Calibration_Status);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_BLE_CGMS_Time_Offset_Range_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_CGMS_Time_Offset_Range_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_BLE_CGMS_TIME_OFFSET_RANGE_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->Minimum);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->Maximum);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_BLE_CGMS_RACP_Response_Code_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_CGMS_RACP_Response_Code_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_BLE_CGMS_RACP_RESPONSE_CODE_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Request_Op_Code);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Response_Code_Value);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_BLE_CGMS_Calibration_Record_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_CGMS_Calibration_Record_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_BLE_CGMS_CALIBRATION_RECORD_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->Calibration_Glucose_Concentration);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->Calibration_Time);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Calibration_Type_Sample_Location);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->Next_Calibration_Time);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->Calibration_Data_Record_Number);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Calibration_Status);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}
