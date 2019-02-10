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

#ifndef __QAPI_BLE_DIS_FUNC_H__
#define __QAPI_BLE_DIS_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_BLE_DIS_Initialize_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Initialize_Service_Handle_Range(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Cleanup_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_Number_Attributes(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Set_Manufacturer_Name(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_Manufacturer_Name(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Set_Model_Number(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_Model_Number(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Set_Serial_Number(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_Serial_Number(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Set_Hardware_Revision(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_Hardware_Revision(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Set_Firmware_Revision(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_Firmware_Revision(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Set_Software_Revision(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_Software_Revision(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Set_System_ID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_System_ID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Set_IEEE_Certification_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_IEEE_Certification_Data(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Set_PNP_ID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Query_PNP_ID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_BLE_DIS_Decode_PNP_ID(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_ble_dis_funclist[] =
{
   Handle_qapi_BLE_DIS_Initialize_Service, /* Function Index = 0 */
   Handle_qapi_BLE_DIS_Initialize_Service_Handle_Range, /* Function Index = 1 */
   Handle_qapi_BLE_DIS_Cleanup_Service, /* Function Index = 2 */
   Handle_qapi_BLE_DIS_Query_Number_Attributes, /* Function Index = 3 */
   Handle_qapi_BLE_DIS_Set_Manufacturer_Name, /* Function Index = 4 */
   Handle_qapi_BLE_DIS_Query_Manufacturer_Name, /* Function Index = 5 */
   Handle_qapi_BLE_DIS_Set_Model_Number, /* Function Index = 6 */
   Handle_qapi_BLE_DIS_Query_Model_Number, /* Function Index = 7 */
   Handle_qapi_BLE_DIS_Set_Serial_Number, /* Function Index = 8 */
   Handle_qapi_BLE_DIS_Query_Serial_Number, /* Function Index = 9 */
   Handle_qapi_BLE_DIS_Set_Hardware_Revision, /* Function Index = 10 */
   Handle_qapi_BLE_DIS_Query_Hardware_Revision, /* Function Index = 11 */
   Handle_qapi_BLE_DIS_Set_Firmware_Revision, /* Function Index = 12 */
   Handle_qapi_BLE_DIS_Query_Firmware_Revision, /* Function Index = 13 */
   Handle_qapi_BLE_DIS_Set_Software_Revision, /* Function Index = 14 */
   Handle_qapi_BLE_DIS_Query_Software_Revision, /* Function Index = 15 */
   Handle_qapi_BLE_DIS_Set_System_ID, /* Function Index = 16 */
   Handle_qapi_BLE_DIS_Query_System_ID, /* Function Index = 17 */
   Handle_qapi_BLE_DIS_Set_IEEE_Certification_Data, /* Function Index = 18 */
   Handle_qapi_BLE_DIS_Query_IEEE_Certification_Data, /* Function Index = 19 */
   Handle_qapi_BLE_DIS_Set_PNP_ID, /* Function Index = 20 */
   Handle_qapi_BLE_DIS_Query_PNP_ID, /* Function Index = 21 */
   Handle_qapi_BLE_DIS_Decode_PNP_ID, /* Function Index = 22 */

};

#define QAPI_BLE_DIS_FUNC_LIST_SIZE   (sizeof(qapi_ble_dis_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_BLE_DIS_FUNC_H__
