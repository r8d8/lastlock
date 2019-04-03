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

#ifndef __UART_H__
#define __UART_H__

#include "qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_uart.h"

#define UART_RX_BUF_SIZE  1024
#define UART_ID_VAVLID(id) (id >=0 && id < QAPI_UART_MAX_PORTS_E)

typedef struct{
    uint8_t data[UART_RX_BUF_SIZE];
    int32_t size;
}UART_BUF_T;

qapi_Status_t uart_init(
    qapi_UART_Port_Id_e id,
    uint32_t                     baud_rate,
    qapi_UART_Parity_Mode_e      parity_mode,
    qapi_UART_Num_Stop_Bits_e    num_stop_bits,
    qapi_UART_Bits_Per_Char_e    bits_per_char,
    qbool_t                      enable_loopback,
    qbool_t                      enable_flow_ctrl
    );
qapi_Status_t uart_deinit(qapi_UART_Port_Id_e id);

qapi_Status_t uart_write(
    qapi_UART_Port_Id_e id,
    const char *buf,
    uint32_t len);

/*
 Read data from UART until data is received or specified timeout interval is exceeded.
 
 The timeout value can be expressed either as a time value (expressed in system ticks), 
 which specifies the timeout interval, or a symbolic constant indicating whether the 
 API should wait forever.

 @param[in] id   --UART port id
 @param[out] buf --buffer to store received data
 @param[in] len  --Length of buffer. Recommended to be not less than UART_RX_BUF_SIZE to avoid data loss.
 @param[in] timeout --How long this API will wait for data.
                        - QURT_TIME_NO_WAIT :Return immediately without any waiting.
                        - QURT_TIME_WAIT_FOREVER : Wait data forever
                        - Timeout value (in system ticks) -- Return after waiting for a
                          specified time value if there is no data from UART. 
*/
int32_t uart_read(
    qapi_UART_Port_Id_e id,
    uint8_t *buf,
    uint32_t len,
    int32_t timeout  /*Unit: system tick*/
    );

qbool_t uart_enabled(qapi_UART_Port_Id_e id);

qapi_Status_t uart_get_stats(
    qapi_UART_Port_Id_e id, 
    uint64_t *tx_bytes, 
    uint64_t *rx_bytes
    );
qapi_Status_t uart_clear_stats(qapi_UART_Port_Id_e id);

qapi_Status_t uart_get_param(
    qapi_UART_Port_Id_e id, 
    uint32_t                     *baud_rate,
    qapi_UART_Parity_Mode_e      *parity_mode,
    qapi_UART_Num_Stop_Bits_e    *num_stop_bits,
    qapi_UART_Bits_Per_Char_e    *bits_per_char,
    qbool_t                      *enable_loopback,
    qbool_t                      *enable_flow_ctrl
    );

#endif
