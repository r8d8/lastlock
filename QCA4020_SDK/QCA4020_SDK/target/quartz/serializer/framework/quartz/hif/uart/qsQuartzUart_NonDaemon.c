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


#ifndef CONFIG_DAEMON_MODE

#include <stdlib.h>
#include "qsQuartz_NonDaemon.h"
#include "qsQuartzUart.h"
#include "qsMml.h"

#include "qurt_error.h"
#include "qurt_thread.h"
#include "qapi/qapi_exhost_devcfg.h"

#define STACK_SIZE        2048
#define THREAD_PRIORITY   10

#define ENTER_CRITICAL()       do { __asm("cpsid i"); } while(0)
#define EXIT_CRITICAL()        do { __asm("cpsie i"); } while(0)

#define SET_CB_DATA(port,index)   ((uint8_t)((((port) & 0x0F) << 4) | ((index) & 0xF)))
#define GET_PORT(data)            ((uint8_t)(((data) >> 4) & 0x0F))
#define GET_INDEX(data)           ((uint8_t)((data) & 0x0F))


/* This structure is used when incomplete data is received through UART.
 * Uart Rx thread keeps track of required bytes and received bytes and send the packet for processing
 * only after complete data is received. */
typedef struct
{
    uint8_t   lenPtr;
    uint8_t   dataPtr;
    uint16_t  rmngLenBytes;
    uint16_t  rmngDataBytes;
    char      *buf;
} IncompletePacket_t;

/*
 * This function handles transmit callbacks from the UART driver.
 * @param Num_Bytes[in] is the number of bytes transmitted.
 * @param Cb_Data[in]   is the application defined callback data
 */
void QsUartTxCb(uint32_t num_Bytes, void* cb_Data)
{
    uint32_t port = (uint32_t)cb_Data;
    uartPortCxt_t *portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);

    ENTER_CRITICAL();
    /* Invalid buffer index or invalid port or uninitialized context */
    if(!portCxt || (QAPI_UART_MAX_PORTS_E <= port))
    {
        EXIT_CRITICAL();
        return;
    }

    if(portCxt->bytes_To_Tx != 0)
    {
        portCxt->bytes_To_Tx -= num_Bytes;
        if(portCxt->bytes_To_Tx == 0)
        {
            EXIT_CRITICAL();
            qurt_signal_set(&(portCxt->event), TX_COMPLETE_EVENT);
            return;
        }
    }

    EXIT_CRITICAL();
    return;
}

/*
 * This function handles receive callbacks from the UART.
 * @param num_Bytes[in] - Number of bytes received.
 * @param cb_Data[in] - Application defined callback data, set to the index of the buffer received on.
 */
void QsUartRxCb(uint32_t num_Bytes, void* cb_Data)
{
    uint32_t data = (uint32_t)cb_Data;
    uint32_t index = GET_INDEX(data);
    uint32_t port = GET_PORT(data);
    uartPortCxt_t *portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);

    ENTER_CRITICAL();
    if(!portCxt || !portCxt->rx_Bufs_Free)
    {
        EXIT_CRITICAL();
        return;
    }

    /* See how much data can be read. */
    if(num_Bytes > UART_RX_BUF_SIZE)
    {
        num_Bytes = UART_RX_BUF_SIZE;
    }

    /* Note the amount of data that was read. */
    portCxt->rx_Buf_Length[index] = num_Bytes;
    portCxt->rx_In_Index++;
    if(portCxt->rx_In_Index == UART_RX_BUF_CNT)
    {
        portCxt->rx_In_Index = 0;
    }
    portCxt->rx_Bufs_Free--;
    EXIT_CRITICAL();

    /* Signal the event that data was received. */
    qurt_signal_set(&(portCxt->event), RX_EVENT);
    return;
}

/* This is the thread to process incoming QAPIs, data, management packets. */
void UartRxThread(void *param)
{
    uint32_t cb_Data = 0, cur_Index = 0, signal_Set = 0, ret_Val = ssSuccess;
    uint16_t total_Size = 0, rcvd_Len = 0, rcvd_DataLen = 0;
    int32_t result = 0;
    char *buf = NULL;
    bufInfo_t *req_Buf = NULL;
    char *req = NULL;
    uartPortCxt_t *portCxt = NULL;
    static IncompletePacket_t pending_Packet = {0, 0, 0, 0, NULL};


    uint32_t port = (uint32_t)param;
    portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);
    qurt_signal_set(&portCxt->event, QS_THREAD_READY);

#ifdef QSTXLOOP
    while(1)
    {
        QsUartTransmit((uint32_t)param, sizeof("Writing to UART\n"), "Writing to UART\n");
        qurt_thread_sleep(20);
    }
#endif /* QSTXLOOP */

    /* Loop waiting for incoming data. */
    while(1)
    {
        /* Wait for data to be received */
        while(portCxt->rx_Bufs_Free == UART_RX_BUF_CNT)
        {
            result = qurt_signal_wait_timed(&portCxt->event, RX_EVENT, QURT_SIGNAL_ATTR_CLEAR_MASK,
                    (uint32 *)&signal_Set, QURT_TIME_WAIT_FOREVER);
            if(result != QURT_EOK)
            {
                /* This case will be TRUE when qurt_signal_destroy() is called. */
                ret_Val = ssFailure;
                break;
            }
        }

        do
        {
            /* Information of received data. */
            cur_Index = portCxt->rx_Out_Index;
            buf = portCxt->rx_Buf[cur_Index];
            rcvd_Len = portCxt->rx_Buf_Length[cur_Index];

            /* No pending incomplete packets */
            if((0 == pending_Packet.rmngLenBytes) && (0 == pending_Packet.rmngDataBytes))
            {
                /* If received length is less than the required HTC+MML header, copy data into a temporary
                 * buffer and wait for remaining bytes */
                if(rcvd_Len < QS_TOTAL_LENGTH_FIELD_SIZE)
                {
                    pending_Packet.buf = (char *)malloc(QS_TOTAL_LENGTH_FIELD_SIZE);
                    if(!pending_Packet.buf)
                    {
                        ret_Val = ssAllocationError;
                        break;
                    }
                    memcpy(pending_Packet.buf, buf, rcvd_Len);
                    pending_Packet.lenPtr = rcvd_Len;
                    pending_Packet.rmngLenBytes = QS_TOTAL_LENGTH_FIELD_SIZE - rcvd_Len;
                    ret_Val = ssIncompleteData;
                    break;
                }

                /* Complete HTC+MML header was received, find the length and get buffer. */
                total_Size = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(buf);
                if(ssSuccess != QsGetBuf(&req_Buf, total_Size))
                {
                    /* If buffer pool doesn't have free buffer, memory is alocated using malloc.
                     * If both of these fail, it indicates that the system is out of memory. */
                    ret_Val = ssAllocationError;
                    break;
                }
                req = req_Buf->buf;
                memcpy(req, buf, rcvd_Len);

                /* In case of incomplete payload received - copy received data and wait for
                 * remaining bytes. */
                if(rcvd_Len < total_Size)
                {
                    pending_Packet.rmngDataBytes = total_Size - rcvd_Len;
                    pending_Packet.dataPtr = rcvd_Len;
                    pending_Packet.buf = (char *)req_Buf;
                    ret_Val = ssIncompleteData;
                    break;
                }

                /* Complete packet received. */
                ret_Val = ssSuccess;
                break;
            }
            else if(pending_Packet.rmngLenBytes)
            {
                /* Header was incomplete in the previous Rx */
                if(rcvd_Len < pending_Packet.rmngLenBytes)
                {
                    // Header length is only 2 bytes so this condition won't happen
                }

                memcpy(pending_Packet.buf + pending_Packet.lenPtr, buf, pending_Packet.rmngLenBytes);
                rcvd_DataLen = rcvd_Len - pending_Packet.rmngLenBytes;

                total_Size = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(pending_Packet.buf);
                if(ssSuccess != QsGetBuf(&req_Buf, total_Size))
                {
                    /* If buffer pool doesn't have free buffer, memory is alocated using malloc.
                     * If both of these fail, it indicates that the system is out of memory. */
                    ret_Val = ssAllocationError;
                    break;
                }
                req = req_Buf->buf;

                /* Copy total length into new buffer */
                memcpy(req, pending_Packet.buf, QS_TOTAL_LENGTH_FIELD_SIZE);
                /* Copy remaining received bytes into new buffer */
                memcpy(req + QS_TOTAL_LENGTH_FIELD_SIZE,
                        pending_Packet.buf + pending_Packet.rmngLenBytes,
                        rcvd_DataLen);

                /* Reset incomplete packet structure */
                pending_Packet.rmngLenBytes = 0;
                pending_Packet.dataPtr = rcvd_DataLen + QS_TOTAL_LENGTH_FIELD_SIZE;
                pending_Packet.rmngDataBytes = total_Size - (rcvd_DataLen + QS_TOTAL_LENGTH_FIELD_SIZE);
                free(pending_Packet.buf);
                pending_Packet.buf = (char *)req_Buf;
            }
            else /* (pending_Packet.rmngDataBytes > 0) */
            {
                /* Length was received in previous Rx but remaining data was incomplete. */
                memcpy(((bufInfo_t *)pending_Packet.buf)->buf + pending_Packet.dataPtr, buf, rcvd_Len);
                pending_Packet.dataPtr = pending_Packet.dataPtr + rcvd_Len;
                pending_Packet.rmngDataBytes = pending_Packet.rmngDataBytes - rcvd_Len;
            }

            /* Complete packet received */
            if(0 == pending_Packet.rmngDataBytes)
            {
                req_Buf = (bufInfo_t *)pending_Packet.buf;
                /* Reset incomplete packet structure */
                pending_Packet.lenPtr = 0;
                pending_Packet.dataPtr = 0;
                pending_Packet.rmngLenBytes = 0;
                pending_Packet.rmngDataBytes = 0;
                pending_Packet.buf = NULL;
                ret_Val = ssSuccess;
                break;
            }
        } while(0);

        /* Complete packet was received, process it */
        if(ssSuccess == ret_Val)
        {
#ifdef LATENCY_DEBUG
            QsUartTransmit(port, total_Size, req);
#else
            /* Process the received command. Underlying functions must free the memory after done. */
            if(ssSuccess != QH_QZ_ENQ(req_Buf, MML_DIRECTION_RX))
            {
                QsReleaseBuf(req_Buf);
            }
#endif /* LATENCY_DEBUG */
        }
        else if(ssAllocationError == ret_Val)
        {
            break;
        }

        /* Adjust the indexes for the free buffers. */
        ENTER_CRITICAL();
        portCxt->rx_Out_Index++;
        if(portCxt->rx_Out_Index == UART_RX_BUF_CNT)
        {
            portCxt->rx_Out_Index = 0;
        }
        portCxt->rx_Bufs_Free++;
        EXIT_CRITICAL();
        /* Queue the current buffer for new incoming data */
        cb_Data = SET_CB_DATA(port,cur_Index);
        qapi_UART_Receive(portCxt->handle, (char *)(portCxt->rx_Buf[cur_Index]), UART_RX_BUF_SIZE, (void *)cb_Data);
    }

    qurt_thread_stop();
}

/* This function is used to write a buffer to UART port.
 * After transmitting the data, this function waits for the callback indicating transmission completed. */
uint32_t QsUartTransmit(uint32_t port, uint32_t len, char *buf)
{
    uartCommonCxt_t *uartCxt = NULL;
    uartPortCxt_t *portCxt = NULL;

    uartCxt = QH_UART_CXT(qsCommonCxt);
    if(!uartCxt || !len || !buf)
    {
        return ssFailure;
    }

    qurt_mutex_lock(&uartCxt->mutex);
    portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);
    if(portCxt && portCxt->uart_Enabled)
    {
        portCxt->bytes_To_Tx = len;
        if(QAPI_OK == qapi_UART_Transmit(portCxt->handle, buf, len, (void *)port))
        {
            qurt_signal_wait(&portCxt->event, TX_COMPLETE_EVENT, QURT_SIGNAL_ATTR_CLEAR_MASK);
            qurt_mutex_unlock(&uartCxt->mutex);
            return ssSuccess;
        }
    }
    qurt_mutex_unlock(&uartCxt->mutex);
    return ssFailure;
}

/* Initialize the UART used by the demo. */
static uint32_t UartPortInit(qapi_UART_Port_Id_e port)
{
    qapi_UART_Open_Config_t uart_Cfg;
    qapi_Exhost_Devcfg_t devcfg;
    uint8_t index = 0;
    uint32_t cb_Data = 0;
    uartPortCxt_t *portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);

    if(!portCxt)
    {
        return ssFailure;
    }

    qapi_Get_Exhost_Devcfg(&devcfg);    
    uart_Cfg.baud_Rate        = devcfg.uart_baud_rate;
    uart_Cfg.parity_Mode      = QAPI_UART_NO_PARITY_E;
    uart_Cfg.num_Stop_Bits    = QAPI_UART_1_0_STOP_BITS_E;
    uart_Cfg.bits_Per_Char    = QAPI_UART_8_BITS_PER_CHAR_E;
    uart_Cfg.enable_Loopback  = FALSE;
    uart_Cfg.enable_Flow_Ctrl = TRUE;
    uart_Cfg.tx_CB_ISR        = QsUartTxCb; /* Transmission complete callback */
    uart_Cfg.rx_CB_ISR        = QsUartRxCb; /* Reception complete callback */

    /* Open the UART port. */
    qurt_mutex_lock(&portCxt->mutex);
    if(QAPI_OK == qapi_UART_Open(&portCxt->handle, port, &uart_Cfg))
    {
        portCxt->uart_Enabled = TRUE;
        qurt_mutex_unlock(&portCxt->mutex);

        /* Queue the buffers for incoming buf */
        for(index = 0; index < UART_RX_BUF_CNT; index ++)
        {
            cb_Data = SET_CB_DATA(port,index);
            if(QAPI_OK != qapi_UART_Receive(portCxt->handle, (char *)(portCxt->rx_Buf[index]),
                        UART_RX_BUF_SIZE, (void *)cb_Data))
            {
                return ssFailure;
            }
        }
        return ssSuccess;
    }
    return ssFailure;
}

uint32_t CreateUartThread(uint32_t port)
{
    qurt_thread_attr_t attr;
    int result = -1;
    uint32_t signal_Set = 0;
    uartPortCxt_t *portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);

    /* Start the UART Rx thread. */
    qurt_thread_attr_init(&attr);
    qurt_thread_attr_set_name(&attr, "Qh_UartRx");
    qurt_thread_attr_set_priority(&attr, THREAD_PRIORITY);
    qurt_thread_attr_set_stack_size(&attr, STACK_SIZE);
    result = qurt_thread_create(&portCxt->RxThread, &attr, UartRxThread, (void *)port);
    if (QURT_EOK != result)
    {
        return ssFailure;
    }

    /* Wait for the new thread to start */
    result = qurt_signal_wait_timed(&portCxt->event,
            QS_THREAD_READY, QURT_SIGNAL_ATTR_CLEAR_MASK,
            &signal_Set, QURT_TIME_WAIT_FOREVER);
    if(QURT_EOK != result)
    {
        return ssFailure;
    }
    return ssSuccess;
}


/* This function is used to initialize UART, corresponding global portCxt, receiver thread. */
uint32_t QsUartInit(uint32_t port)
{
    uartCommonCxt_t *uartCxt = NULL;
    uartPortCxt_t *portCxt = NULL;

    if(QAPI_UART_MAX_PORTS_E <= port)
    {
        return ssFailure;
    }

    if (!qsCommonCxt->htcCxt[QS_UART_E])
    {
        qsCommonCxt->htcCxt[QS_UART_E] = (htcCxt_u*)malloc(sizeof(htcCxt_u));
        if(!qsCommonCxt->htcCxt[QS_UART_E])
        {
            return ssFailure;
        }
        memset(qsCommonCxt->htcCxt[QS_UART_E], 0, sizeof(htcCxt_u));
        if(QURT_EOK != qurt_mutex_create(&qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.mutex))
        {
            return ssFailure;
        }
        qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.numPortsInitialized = 0;
    }

    uartCxt = QH_UART_CXT(qsCommonCxt);

    /* Return ssSuccess if same UART port is used for multiple modules */
    qurt_mutex_lock(&uartCxt->mutex);
    portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);
    if(portCxt)
    {
        qurt_mutex_lock(&portCxt->mutex);
        portCxt->ref_Cnt++;
        qurt_mutex_unlock(&portCxt->mutex);
        qurt_mutex_unlock(&uartCxt->mutex);
        return ssSuccess;
    }

    /* Initialize the global UART portCxt */
    uartCxt->portCxt[port] = (uartPortCxt_t *)malloc(sizeof(uartPortCxt_t));
    if(!uartCxt->portCxt[port])
    {
        qurt_mutex_unlock(&uartCxt->mutex);
        return ssFailure;
    }

    portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);
    memset(portCxt, 0, sizeof(uartPortCxt_t));
    portCxt->ref_Cnt++; /* Indicates number of modules using this UART port */
    portCxt->rx_Bufs_Free = UART_RX_BUF_CNT;
    if(QURT_EOK != qurt_mutex_create(&portCxt->mutex))
    {
        qurt_mutex_unlock(&uartCxt->mutex);
        return ssFailure;
    }
    if(QURT_EOK != qurt_signal_create(&portCxt->event))
    {
        qurt_mutex_unlock(&uartCxt->mutex);
        return ssFailure;
    }

    /* Configure and open UART port. */
    if(ssSuccess == UartPortInit((qapi_UART_Port_Id_e)port))
    {
        if(ssSuccess == CreateUartThread(port))
        {
            uartCxt->numPortsInitialized++;
            qurt_mutex_unlock(&uartCxt->mutex);
            return ssSuccess;
        }
    }

    /* Error */
    qurt_mutex_unlock(&uartCxt->mutex);
    (void)QsUartDeInit(port);
    return ssFailure;
}



/**
  @brief Turns off the UART used by the demo.

  @return QT_SUCCESS if the UART was deinitailized successfully or ssFailure if there was
  an error.
  */
uint32_t QsUartDeInit(uint32_t port)
{
    uartPortCxt_t *portCxt = NULL;

    qurt_mutex_lock(&qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.mutex);
    if((QAPI_UART_MAX_PORTS_E <= port) || !qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.portCxt[port])
    {
        qurt_mutex_unlock(&qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.mutex);
        return ssFailure;
    }

    portCxt = qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.portCxt[port];
    qurt_mutex_lock(&portCxt->mutex);

    if(portCxt->ref_Cnt)
    {
        portCxt->ref_Cnt--;
        /* If other modules are using this UART port, decrement the reference count and return */
        if(portCxt->ref_Cnt)
        {
            qurt_mutex_unlock(&portCxt->mutex);
            qurt_mutex_unlock(&qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.mutex);
            return ssSuccess;
        }
    }

    /* If this was the last module using this uart port, destroy the context */
    /* qurt_signal_destroy() will wake up qt_Uart_Thread and it will exit. */
    qurt_signal_delete(&portCxt->event);

    if (TRUE == portCxt->uart_Enabled)
    {
        (void)qapi_UART_Close(portCxt->handle);
        portCxt->uart_Enabled = FALSE;
    }

    qurt_mutex_unlock(&portCxt->mutex);
    qurt_mutex_delete(&portCxt->mutex);

    free(portCxt);
    qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.portCxt[port] = NULL;
    qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.numPortsInitialized--;

    if (!qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.numPortsInitialized)
    {
        qurt_mutex_unlock(&qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.mutex);
        qurt_mutex_delete(&qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.mutex);
        qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.mutex = 0;
    }
    else
    {
        qurt_mutex_unlock(&qsCommonCxt->htcCxt[QS_UART_E]->uartCxt.mutex);
    }

    return ssSuccess;
}


#endif /* CONFIG_DAEMON_MODE */

