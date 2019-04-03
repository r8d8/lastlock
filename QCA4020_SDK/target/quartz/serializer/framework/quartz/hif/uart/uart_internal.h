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

#ifndef __TARGET_UART_INTERNAL_H__
#define __TARGET_UART_INTERNAL_H__

#include <stdint.h>
//#include "qsCommon.h"
#include "common.h"
#include "qapi_status.h"
#include "qapi_types.h"
#include "qapi_uart.h"

/* Information regarding buffers used by UART */
#define UART_RX_BUF_SIZE   2048
#define UART_RX_BUF_CNT    2

/* This structure is used when incomplete data is received through UART.
 * Uart Rx thread keeps track of required bytes and received bytes and send the packet for processing
 * only after complete data is received. */
typedef struct
{
    uint8_t   incompleteHeader;
    uint16_t  rqdBytes;
    uint16_t   bufPtr;
    char      *buf;
} IncompletePacket_t;


/* This structure holds information regarding each UART port.
 * Only 2 ports exist - QAPI_UART_DEBUG_PORT_E and QAPI_UART_HS_PORT_E */
typedef struct uartPortCxt_s {
    qapi_UART_Handle_t handle;                                    /* Uart handle */
    qbool_t            uart_Enabled;                              /* Flag to indicated if UART is enabled */
    char               rx_Buf[UART_RX_BUF_CNT][UART_RX_BUF_SIZE]; /* Receive buffer. Max 2 allowed */
    uint32_t           rx_Buf_Length[UART_RX_BUF_CNT];            /* Number of bytes received in a buffer */
    uint8_t            rx_In_Index;                               /* Index of buffer to be used for next Rx */
    uint8_t            rx_Out_Index;                              /* Index of buffer to be used for next Tx */
    volatile uint32_t  rx_Bufs_Free;                              /* Number of free Rx buffers */
    volatile uint32_t  bytes_To_Tx;                               /* Number of bytes to be transmitted */
    qurt_mutex_t       mutex;                                     /* Mutex */
    qurt_signal_t      event;                                     /* Semaphore for synchronization */
    qurt_thread_t      rxThread;                                  /* Thread to receive data on uart. */
    queue_t            rxQueue;                                   /* Queue of packets received */
    qurt_thread_t      txThread;                                  /* Thread to send data on uart. */
    queue_t            txQueue;                                   /* Queue of packets to be sent */
    IncompletePacket_t pending;                                   /* Pending packet */

} uartPortCxt_t;


/* Common context to hold UART related information */
typedef struct uartCommonCxt_s {
    uint8_t       numPortsInitialized;              /* Number of port initialized */
    qurt_mutex_t  mutex;                            /* Mutex */
    uartPortCxt_t *portCxt[QAPI_UART_MAX_PORTS_E];  /* Individual port contexts */
} uartCommonCxt_t;


uint32_t QsUartInit(uint32_t port);
uint32_t QsUartDeInit(uint32_t port);
uint32_t QsUartTransmit(uint32_t port, char *txBuf);

#endif /* __TARGET_UART_INTERNAL_H__ */
