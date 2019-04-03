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

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


#include "pal.h"
#include "qcli.h"
#include "qcli_api.h"

#include "qurt_error.h"
#include "qurt_thread.h"
#include "qurt_signal.h"

#include "osal_types.h"
#include "uart.h"
/*-------------------------------------------------------------------------
* Macros / Constants / typedef
*-----------------------------------------------------------------------*/

#define UART_EVENT_MASK_RECEIVE                          (0x00000001)
#define UART_EVENT_MASK_TRANSMIT                         (0x00000001)

#define ID_2_UART(id) (UART_ID_VAVLID(id)? &g_uart_ctrl[id] : NULL)

#define UART_BUF_IDX_INC(idx) {idx++; if (idx >= UART_BUF_COUNT) idx = 0;}
/*-------------------------------------------------------------------------
* Structure & Enum defination
*-----------------------------------------------------------------------*/



#define UART_BUF_COUNT 2

typedef struct UART_s
{
    qapi_UART_Port_Id_e id;
    qapi_UART_Handle_t  handle;
    qbool_t             enabled;

    uint32_t                     baud_rate;
    qapi_UART_Parity_Mode_e      parity_mode;
    qapi_UART_Num_Stop_Bits_e    num_stop_bits;
    qapi_UART_Bits_Per_Char_e    bits_per_char;
    qbool_t                      enable_loopback;
    qbool_t                      enable_flow_ctrl;
    
    UART_BUF_T          uart_buf[UART_BUF_COUNT];
    uint32_t            buf_idx_ready; 
    
    volatile uint32_t   byte_to_tx;
    qurt_signal_t       event_rd;
    qurt_signal_t       event_wr;

    uint64_t    tx_bytes;
    uint64_t    rx_bytes;

} UART_t;

/*-------------------------------------------------------------------------
* Global Variables
*-----------------------------------------------------------------------*/
UART_t g_uart_ctrl[QAPI_UART_MAX_PORTS_E];

/*-------------------------------------------------------------------------
* Extern Variables
*-----------------------------------------------------------------------*/
extern QCLI_Group_Handle_t qcli_uart_handle;

/*-------------------------------------------------------------------------
* Function defination
*-----------------------------------------------------------------------*/

static void uart_tx_cb(uint32 num_bytes, void* cb_data)
{
    UART_t *uart = (UART_t *)cb_data;
    
   if(uart->byte_to_tx != 0)
   {
      uart->byte_to_tx -= num_bytes;
      if(uart->byte_to_tx == 0)
      {
         qurt_signal_set(&(uart->event_wr), UART_EVENT_MASK_TRANSMIT);
      }
   }
}

static void uart_rx_cb_common(qapi_UART_Port_Id_e id, uint32 num_bytes, void* cb_data)
{
    UART_t *uart = NULL;
    uint32 buf_idx = (uint32)cb_data;


    uart = ID_2_UART(id);
    if (NULL == uart){
        return;
    }
    if (buf_idx >= UART_BUF_COUNT){
        return;
    }

    if (0 == num_bytes){
        return;
    }
    
    /* See how much data can be read. */
    uart->uart_buf[buf_idx].size = (num_bytes <= UART_RX_BUF_SIZE) ?
                                        num_bytes : UART_RX_BUF_SIZE;\
    
    qurt_signal_set(&(uart->event_rd), UART_EVENT_MASK_RECEIVE);
}

static void uart_rx_cb_for_debug_port(uint32 num_bytes, void* cb_data)
{
    uart_rx_cb_common(QAPI_UART_DEBUG_PORT_E, num_bytes, cb_data);
}
static void uart_rx_cb_for_hs_port(uint32 num_bytes, void* cb_data)
{
    uart_rx_cb_common(QAPI_UART_HS_PORT_E, num_bytes, cb_data);
}


qapi_Status_t uart_init(
    qapi_UART_Port_Id_e id,
    uint32_t                     baud_rate,
    qapi_UART_Parity_Mode_e      parity_mode,
    qapi_UART_Num_Stop_Bits_e    num_stop_bits,
    qapi_UART_Bits_Per_Char_e    bits_per_char,
    qbool_t                      enable_loopback,
    qbool_t                      enable_flow_ctrl
    )
{
    UART_t *uart = NULL;
    qapi_UART_Open_Config_t uart_config;
    qapi_Status_t status;
    uint32_t idx;
    
    uart = ID_2_UART(id);
    if (NULL == uart){
        return QAPI_ERR_INVALID_PARAM;
    }

    if (uart->enabled){
        return QAPI_ERR_INVALID_PARAM;
    }

    memset(uart, 0, sizeof(UART_t));

    qurt_signal_init(&(uart->event_rd));
    qurt_signal_init(&(uart->event_wr));
    uart->id = id;
    
    memset(&uart_config, 0, sizeof(qapi_UART_Open_Config_t));
    uart_config.baud_Rate        = uart->baud_rate = baud_rate;
    uart_config.parity_Mode      = uart->parity_mode = parity_mode;
    uart_config.num_Stop_Bits    = uart->num_stop_bits = num_stop_bits;
    uart_config.bits_Per_Char    = uart->bits_per_char = bits_per_char;
    uart_config.enable_Loopback  = uart->enable_loopback = enable_loopback;
    uart_config.enable_Flow_Ctrl = uart->enable_flow_ctrl = enable_flow_ctrl;
    uart_config.tx_CB_ISR        = uart_tx_cb;
    uart_config.rx_CB_ISR        = (QAPI_UART_DEBUG_PORT_E == id) ? 
                                        uart_rx_cb_for_debug_port
                                        : uart_rx_cb_for_hs_port;

    status = qapi_UART_Open(&(uart->handle), uart->id, &uart_config);
    if (status != QAPI_OK){
        goto fail;
    }

    uart->buf_idx_ready = 0;
    for (idx = 0; idx < UART_BUF_COUNT; idx++){
        uart->uart_buf[idx].size = 0;
        status = qapi_UART_Receive(uart->handle, 
                        (char*)uart->uart_buf[idx].data, 
                        UART_RX_BUF_SIZE,
                        (void*)idx);

        if (status != QAPI_OK){
            qapi_UART_Close(uart->handle);
            goto fail;
        }
    }

    uart->enabled = TRUE;
    return QAPI_OK;
    
fail:
    return status;
}

qapi_Status_t uart_deinit(qapi_UART_Port_Id_e id)
{
    UART_t *uart = NULL;

    uart = ID_2_UART(id);
    if (NULL == uart){
        return QAPI_ERR_INVALID_PARAM;
    }

    if (!uart->enabled){
        return QAPI_OK;
    }
    uart->enabled = FALSE;
    qurt_signal_destroy(&(uart->event_rd));
    qurt_signal_destroy(&(uart->event_wr));
    return(qapi_UART_Close(uart->handle));
}

/**
   @brief This function is used to write a buffer to the uart port. Note
          that when this function returns, all data from the buffer will
          be written to the uart port or buffered locally.

   @param Length is the length of the data to be written.
   @param Buffer is a pointer to the buffer to be written to the console.
*/
qapi_Status_t uart_write(
    qapi_UART_Port_Id_e id,
    const char *buf,
    uint32_t len)
{
    UART_t *uart = NULL;
    qapi_Status_t status;

    
    uart = ID_2_UART(id);
    if (NULL == uart || !uart->enabled 
        || 0 == len || NULL == buf){
        return QAPI_ERR_INVALID_PARAM;
    }

    uart->byte_to_tx = len;
    status = qapi_UART_Transmit(uart->handle, (char *)buf, len, uart);
    if (QAPI_OK != status){
        return status;
    }

    /* Wait for the packet to be sent. */
    qurt_signal_wait(&(uart->event_wr), 
            UART_EVENT_MASK_TRANSMIT, 
            QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);
    uart->tx_bytes += len; //Update stats
    
    return QAPI_OK;
}

int32_t uart_read(
    qapi_UART_Port_Id_e id,
    uint8_t *buf,
    uint32_t len,
    int32_t timeout)
{  
    UART_t *uart = NULL;
    UART_BUF_T *uart_buf = NULL;
    uint32_t copy_len;
    qapi_Status_t status;
    uint32_t idx;
    uint32_t signal_set;
    int32_t ret;

    
    uart = ID_2_UART(id);
    if (NULL == uart || !uart->enabled){
        return -1;
    }

    if (NULL == buf || 0 == len){
        return -1;
    }
    
    if (0 == uart->uart_buf[0].size 
        && 0 == uart->uart_buf[1].size){
        ret = qurt_signal_wait_timed(&(uart->event_rd),             
                UART_EVENT_MASK_RECEIVE,             
                QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK,
                &signal_set,
                timeout);
        if (QURT_EFAILED_TIMEOUT == ret){
            return 0;
        }
        if (QURT_EOK != ret){
            return -1;
        }
    }

    if (0 == uart->uart_buf[0].size 
        && 0 == uart->uart_buf[1].size){
        //QCLI_Printf(qcli_uart_handle, "No byte is ready for reading.\n");
        return 0;
    }
    idx = uart->buf_idx_ready;

    
    uart_buf = &uart->uart_buf[idx];
    copy_len = uart_buf->size;
    
    if (copy_len > len){
        QCLI_Printf(qcli_uart_handle, "Rx buffer is too short!\n");
        copy_len = len;
    }
    memcpy(buf, uart_buf->data, copy_len);
    uart->rx_bytes += uart_buf->size; //Update stats

    uart_buf->size = 0; //Reset it.
    status = qapi_UART_Receive(uart->handle, 
                    (char*)uart_buf->data, 
                    UART_RX_BUF_SIZE,
                    (void*)idx);
    if (QAPI_OK != status){
        QCLI_Printf(qcli_uart_handle, "Buf enqueue failed (idx = %d).\n", idx);
        copy_len = -1;
        goto exit;
    }
    UART_BUF_IDX_INC(uart->buf_idx_ready);
    
exit:
    return copy_len;
}


qbool_t uart_enabled(qapi_UART_Port_Id_e id)
{
    UART_t *uart = NULL;

    uart = ID_2_UART(id);
    if (NULL == uart){
        return FALSE;
    }

    return uart->enabled;
}

qapi_Status_t uart_get_stats(
    qapi_UART_Port_Id_e id, 
    uint64_t *tx_bytes, 
    uint64_t *rx_bytes
    )
{
    UART_t *uart = NULL;

    uart = ID_2_UART(id);
    if (NULL == uart){
        return QAPI_ERR_INVALID_PARAM;
    }

    if (NULL == tx_bytes || NULL == rx_bytes){
        return QAPI_ERR_INVALID_PARAM;
    }

    *tx_bytes = uart->tx_bytes;
    *rx_bytes = uart->rx_bytes;
    
    return QAPI_OK;
}

qapi_Status_t uart_clear_stats(qapi_UART_Port_Id_e id) 
{
    UART_t *uart = NULL;

    uart = ID_2_UART(id);
    if (NULL == uart){
        return QAPI_ERR_INVALID_PARAM;
    }

    uart->tx_bytes = 0;
    uart->rx_bytes = 0;
    
    return QAPI_OK;
}


qapi_Status_t uart_get_param(
    qapi_UART_Port_Id_e id, 
    uint32_t                     *baud_rate,
    qapi_UART_Parity_Mode_e      *parity_mode,
    qapi_UART_Num_Stop_Bits_e    *num_stop_bits,
    qapi_UART_Bits_Per_Char_e    *bits_per_char,
    qbool_t                      *enable_loopback,
    qbool_t                      *enable_flow_ctrl
    )
{
    UART_t *uart = NULL;

    uart = ID_2_UART(id);
    if (NULL == uart){
        return QAPI_ERR_INVALID_PARAM;
    }

    if (NULL == baud_rate
        || NULL == parity_mode
        || NULL == num_stop_bits
        || NULL == bits_per_char
        || NULL == enable_loopback
        || NULL == enable_flow_ctrl
        ){
        return QAPI_ERR_INVALID_PARAM;
    }

    *baud_rate = uart->baud_rate;
    *parity_mode = uart->parity_mode;
    *num_stop_bits = uart->num_stop_bits;
    *bits_per_char = uart->bits_per_char;
    *enable_loopback= uart->enable_loopback;
    *enable_flow_ctrl = uart->enable_flow_ctrl;

    return QAPI_OK;
}

