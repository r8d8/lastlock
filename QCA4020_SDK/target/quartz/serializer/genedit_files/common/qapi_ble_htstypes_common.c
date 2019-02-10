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
#include "qapi_ble_htstypes_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_gatttype_common.h"

uint32_t CalcPackedSize_qapi_BLE_HTS_Temperature_Data_t(qapi_BLE_HTS_Temperature_Data_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_BLE_HTS_TEMPERATURE_DATA_T_MIN_PACKED_SIZE;
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_BLE_HTS_Temperature_Measurement_Header_t(qapi_BLE_HTS_Temperature_Measurement_Header_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_BLE_HTS_TEMPERATURE_MEASUREMENT_HEADER_T_MIN_PACKED_SIZE;

        qsResult += CalcPackedSize_qapi_BLE_HTS_Temperature_Data_t((qapi_BLE_HTS_Temperature_Data_t *)&Structure->Temperature);
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_BLE_HTS_Temperature_Measurement_With_Time_Stamp_t(qapi_BLE_HTS_Temperature_Measurement_With_Time_Stamp_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_BLE_HTS_TEMPERATURE_MEASUREMENT_WITH_TIME_STAMP_T_MIN_PACKED_SIZE;

        qsResult += CalcPackedSize_qapi_BLE_HTS_Temperature_Measurement_Header_t((qapi_BLE_HTS_Temperature_Measurement_Header_t *)&Structure->Measurement_Header);

        qsResult += CalcPackedSize_qapi_BLE_GATT_Date_Time_Characteristic_t((qapi_BLE_GATT_Date_Time_Characteristic_t *)&Structure->Time_Stamp);
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_BLE_HTS_Temperature_Measurement_Without_Time_Stamp_t(qapi_BLE_HTS_Temperature_Measurement_Without_Time_Stamp_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_BLE_HTS_TEMPERATURE_MEASUREMENT_WITHOUT_TIME_STAMP_T_MIN_PACKED_SIZE;

        qsResult += CalcPackedSize_qapi_BLE_HTS_Temperature_Measurement_Header_t((qapi_BLE_HTS_Temperature_Measurement_Header_t *)&Structure->Measurement_Header);
    }

    return(qsResult);
}

uint32_t CalcPackedSize_qapi_BLE_HTS_Valid_Range_t(qapi_BLE_HTS_Valid_Range_t *Structure)
{
    uint32_t qsResult;

    if(Structure == NULL)
    {
        qsResult = 0;
    }
    else
    {
        qsResult = QAPI_BLE_HTS_VALID_RANGE_T_MIN_PACKED_SIZE;

        qsResult += CalcPackedSize_16((uint16_t *)&Structure->Lower_Bounds);

        qsResult += CalcPackedSize_16((uint16_t *)&Structure->Upper_Bounds);
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_BLE_HTS_Temperature_Data_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Temperature_Data_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_HTS_Temperature_Data_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Value0);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Value1);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Value2);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Exponent);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_BLE_HTS_Temperature_Measurement_Header_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Temperature_Measurement_Header_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_HTS_Temperature_Measurement_Header_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Flags);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_qapi_BLE_HTS_Temperature_Data_t(Buffer, (qapi_BLE_HTS_Temperature_Data_t *)&Structure->Temperature);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_BLE_HTS_Temperature_Measurement_With_Time_Stamp_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Temperature_Measurement_With_Time_Stamp_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_HTS_Temperature_Measurement_With_Time_Stamp_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_qapi_BLE_HTS_Temperature_Measurement_Header_t(Buffer, (qapi_BLE_HTS_Temperature_Measurement_Header_t *)&Structure->Measurement_Header);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_qapi_BLE_GATT_Date_Time_Characteristic_t(Buffer, (qapi_BLE_GATT_Date_Time_Characteristic_t *)&Structure->Time_Stamp);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Temperature_Type);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_BLE_HTS_Temperature_Measurement_Without_Time_Stamp_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Temperature_Measurement_Without_Time_Stamp_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_HTS_Temperature_Measurement_Without_Time_Stamp_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_qapi_BLE_HTS_Temperature_Measurement_Header_t(Buffer, (qapi_BLE_HTS_Temperature_Measurement_Header_t *)&Structure->Measurement_Header);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_8(Buffer, (uint8_t *)&Structure->Temperature_Type);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedWrite_qapi_BLE_HTS_Valid_Range_t(PackedBuffer_t *Buffer, qapi_BLE_HTS_Valid_Range_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;

    if(Buffer->Remaining >= CalcPackedSize_qapi_BLE_HTS_Valid_Range_t(Structure))
    {
        if(Structure != NULL)
        {
         if(qsResult == ssSuccess)
             qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->Lower_Bounds);

         if(qsResult == ssSuccess)
             qsResult = PackedWrite_16(Buffer, (uint16_t *)&Structure->Upper_Bounds);

        }
    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_BLE_HTS_Temperature_Data_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Temperature_Data_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_BLE_HTS_TEMPERATURE_DATA_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Value0);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Value1);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Value2);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Exponent);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_BLE_HTS_Temperature_Measurement_Header_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Temperature_Measurement_Header_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_BLE_HTS_TEMPERATURE_MEASUREMENT_HEADER_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Flags);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_qapi_BLE_HTS_Temperature_Data_t(Buffer, BufferList, (qapi_BLE_HTS_Temperature_Data_t *)&Structure->Temperature);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_BLE_HTS_Temperature_Measurement_With_Time_Stamp_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Temperature_Measurement_With_Time_Stamp_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_BLE_HTS_TEMPERATURE_MEASUREMENT_WITH_TIME_STAMP_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_qapi_BLE_HTS_Temperature_Measurement_Header_t(Buffer, BufferList, (qapi_BLE_HTS_Temperature_Measurement_Header_t *)&Structure->Measurement_Header);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_qapi_BLE_GATT_Date_Time_Characteristic_t(Buffer, BufferList, (qapi_BLE_GATT_Date_Time_Characteristic_t *)&Structure->Time_Stamp);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Temperature_Type);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_BLE_HTS_Temperature_Measurement_Without_Time_Stamp_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Temperature_Measurement_Without_Time_Stamp_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_BLE_HTS_TEMPERATURE_MEASUREMENT_WITHOUT_TIME_STAMP_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_qapi_BLE_HTS_Temperature_Measurement_Header_t(Buffer, BufferList, (qapi_BLE_HTS_Temperature_Measurement_Header_t *)&Structure->Measurement_Header);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_8(Buffer, BufferList, (uint8_t *)&Structure->Temperature_Type);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}

SerStatus_t PackedRead_qapi_BLE_HTS_Valid_Range_t(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, qapi_BLE_HTS_Valid_Range_t *Structure)
{
    SerStatus_t qsResult = ssSuccess;
    Boolean_t   qsPointerValid = FALSE;

    UNUSED(qsPointerValid);

    if(Buffer->Remaining >= QAPI_BLE_HTS_VALID_RANGE_T_MIN_PACKED_SIZE)
    {
        if(qsResult == ssSuccess)
            qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->Lower_Bounds);

        if(qsResult == ssSuccess)
            qsResult = PackedRead_16(Buffer, BufferList, (uint16_t *)&Structure->Upper_Bounds);

    }
    else
    {
        qsResult = ssInvalidLength;
    }

    return(qsResult);
}
