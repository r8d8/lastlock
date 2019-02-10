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

#ifndef __QAPI_HMI_FUNC_H__
#define __QAPI_HMI_FUNC_H__

#include <stdint.h>
#include "qsCommon.h"

SerStatus_t Handle_qapi_HMI_Initialize(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_Shutdown(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_Get_Max_MSDU_Length(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MCPS_Data_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MCPS_Purge_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Associate_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Associate_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Disassociate_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Get_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Orphan_Response(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Reset_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Rx_Enable_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Scan_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_15p4_Scan_Duration_To_Milliseconds(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Set_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Start_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_MLME_Poll_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_Auto_Poll_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_DUT_Enable_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_DUT_Tx_Test_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_DUT_Rx_Test_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_DUT_Rx_Stat_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_DUT_Cca_Scan_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_DUT_Test_End_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_Enable_BBIF(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_NVM_Get_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);
SerStatus_t Handle_qapi_HMI_VS_NVM_Set_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);

FunctionHandler_t qapi_hmi_funclist[] =
{
   Handle_qapi_HMI_Initialize, /* Function Index = 0 */
   Handle_qapi_HMI_Shutdown, /* Function Index = 1 */
   Handle_qapi_HMI_Get_Max_MSDU_Length, /* Function Index = 2 */
   Handle_qapi_HMI_MCPS_Data_Request, /* Function Index = 3 */
   Handle_qapi_HMI_MCPS_Purge_Request, /* Function Index = 4 */
   Handle_qapi_HMI_MLME_Associate_Request, /* Function Index = 5 */
   Handle_qapi_HMI_MLME_Associate_Response, /* Function Index = 6 */
   Handle_qapi_HMI_MLME_Disassociate_Request, /* Function Index = 7 */
   Handle_qapi_HMI_MLME_Get_Request, /* Function Index = 8 */
   Handle_qapi_HMI_MLME_Orphan_Response, /* Function Index = 9 */
   Handle_qapi_HMI_MLME_Reset_Request, /* Function Index = 10 */
   Handle_qapi_HMI_MLME_Rx_Enable_Request, /* Function Index = 11 */
   Handle_qapi_HMI_MLME_Scan_Request, /* Function Index = 12 */
   Handle_qapi_HMI_15p4_Scan_Duration_To_Milliseconds, /* Function Index = 13 */
   Handle_qapi_HMI_MLME_Set_Request, /* Function Index = 14 */
   Handle_qapi_HMI_MLME_Start_Request, /* Function Index = 15 */
   Handle_qapi_HMI_MLME_Poll_Request, /* Function Index = 16 */
   Handle_qapi_HMI_VS_Auto_Poll_Request, /* Function Index = 17 */
   Handle_qapi_HMI_VS_DUT_Enable_Request, /* Function Index = 18 */
   Handle_qapi_HMI_VS_DUT_Tx_Test_Request, /* Function Index = 19 */
   Handle_qapi_HMI_VS_DUT_Rx_Test_Request, /* Function Index = 20 */
   Handle_qapi_HMI_VS_DUT_Rx_Stat_Request, /* Function Index = 21 */
   Handle_qapi_HMI_VS_DUT_Cca_Scan_Request, /* Function Index = 22 */
   Handle_qapi_HMI_VS_DUT_Test_End_Request, /* Function Index = 23 */
   Handle_qapi_HMI_VS_Enable_BBIF, /* Function Index = 24 */
   Handle_qapi_HMI_VS_NVM_Get_Request, /* Function Index = 25 */
   Handle_qapi_HMI_VS_NVM_Set_Request, /* Function Index = 26 */

};

#define QAPI_HMI_FUNC_LIST_SIZE   (sizeof(qapi_hmi_funclist) / sizeof(FunctionHandler_t))

#endif // __QAPI_HMI_FUNC_H__
