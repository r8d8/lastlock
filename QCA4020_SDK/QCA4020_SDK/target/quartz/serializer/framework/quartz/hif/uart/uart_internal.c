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

#ifdef CONFIG_DAEMON_MODE

#include <stdlib.h>
#include "common_cxt.h"
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

uint32_t InitPendingPacket(IncompletePacket_t *packet, uint16_t rcvdLen, uint16_t rqdLen, char *buf)
{
    packet->buf = (char *)malloc(rqdLen);
    if(!packet->buf)
    {
        return ssAllocationError;
    }
    memcpy(packet->buf, buf, rcvdLen);
    packet->bufPtr = rcvdLen;
    packet->rqdBytes = rqdLen - rcvdLen;
    packet->incompleteHeader = 1;
    return ssIncompleteData;
}

void UpdatePendingPacket(IncompletePacket_t *packet, uint16_t rqdBytes, uint16_t bufPtr, void *buf)
{
    packet->rqdBytes = rqdBytes;
    packet->bufPtr = bufPtr;
    packet->buf = buf;
    if(!rqdBytes)
        packet->incompleteHeader = 0;
    return;
}

static char* UpdateBuffer(uartPortCxt_t *portCxt, char *dst, char *src, uint16_t len, uint16_t *rcvd_Len, void *buf)
{
    memcpy(dst, src, len);
    src += len;
    (*rcvd_Len) -= len;

    /* Enqueue the completed packet. */
    if(buf)
        (void)QsEnq(&portCxt->rxQueue, buf);

    return src;
}

static char* GetBuf(char *buf, uint16_t *totalSize)
{
    char *bufInfo = NULL;
    uint16_t size = 0;

    /* Find the length and get buffer. */
    size = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(buf);
    if(!size)
        return NULL;
    
    /* Get buffer from pool.
     * Respective services will call QsReleaseBuf() to replenish the pool. */
    QsGetBuf(&bufInfo, size, BUF_TYPE_RX);
    *totalSize = size;
    return bufInfo;
}

/* This is the thread to process incoming QAPIs, data, management packets. */
void UartRxThread(void *param)
{
    uint32_t cb_Data = 0, cur_Index = 0, signal_Set = 0, ret_Val = ssSuccess;
    uint16_t total_Size = 0, rcvd_Len = 0, rqd_DataLen = 0;
    int32_t result = 0;
    char *buf = NULL, *req = NULL;
    uartPortCxt_t *portCxt = NULL;

    uint32_t port = (uint32_t)param;
    portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);
    qurt_signal_set(&portCxt->event, QS_THREAD_READY);

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
                if(portCxt->pending.buf)
                {
                    free(portCxt->pending.buf);
                }
                qurt_thread_stop();
            }
        }

        /*****************************************************************************************************
         * Every time Rx interrupt is received, buffer may hold one or more packets.
         * Last packet may be incomplete.
         * First 2 bytes in all packets give the total length of packet.
         *
         * Loop breaks when all received bytes are put into one or more packets in rxQueue.
         * Only the complete packets are processed after the loop.
         * Incomplete packet is tracked using static 'pending_packet' variable, as there can be
         * only 1 incomplete packet per Rx event.
         *
         * Possible cases for each Rx buffer are as following:
         * (1) No previously incomplete packets pending - so start of a new packet at ccurent buffer pointer.
         *
         * (2) Previous Rx event had only 1 byte for the pending packet hence couldn't calculate total size.
         *     Current buffer holds at least one remaining byte of length field.
         *
         * (3) Previous Rx event had at least 2 bytes for the pending packet hence total size is known 
         *     but data was incomplete.
         * 
         ****************************************************************************************************/
        cur_Index = portCxt->rx_Out_Index;
        buf = portCxt->rx_Buf[cur_Index];
        rcvd_Len = portCxt->rx_Buf_Length[cur_Index];
        ret_Val = ssSuccess;
        while(rcvd_Len)
        {
            req = NULL;

            /*******************************************************************************************/
            /* Start of new packet, no previously pending incomplete packets */
            if(!portCxt->pending.rqdBytes) {
                if(rcvd_Len < QS_TOTAL_LENGTH_FIELD_SIZE) {
                    ret_Val = InitPendingPacket(&portCxt->pending, rcvd_Len, QS_TOTAL_LENGTH_FIELD_SIZE, buf);
                    break;
                }

                req = GetBuf(buf, &total_Size);
                if(!req) {
                    ret_Val = ssFailure;
                    break;
                }

                if(rcvd_Len < total_Size) {
                    memcpy(req, buf, rcvd_Len);
                    /* Current Rx buffer missing some of the required bytes. */
                    UpdatePendingPacket(&portCxt->pending, total_Size - rcvd_Len, 
                                        rcvd_Len, req);

                    memcpy(req, buf, rcvd_Len);
                    ret_Val = ssIncompleteData;
                    break;
                }
                else {
                    /* One or more than one packets received in Rx buffer */
                    buf = UpdateBuffer(portCxt, req, buf, total_Size, &rcvd_Len, req);
                    /* continue to start of while(rcvd_Len) */
                }
            }

            /******************************************************************************************/
            /* Header was incomplete in the previous Rx */
            else if(portCxt->pending.incompleteHeader)
            {
                // Header length is only 2 bytes so this condition won't happen.
                if(rcvd_Len < portCxt->pending.rqdBytes) { }

                buf = UpdateBuffer(portCxt, portCxt->pending.buf + portCxt->pending.bufPtr,
                                buf, portCxt->pending.rqdBytes, &rcvd_Len, NULL);

                req = GetBuf(portCxt->pending.buf, &total_Size);
                if(!req) {
                    ret_Val = ssFailure;
                    break;
                }

                memcpy(req, portCxt->pending.buf, QS_TOTAL_LENGTH_FIELD_SIZE);
                rqd_DataLen = total_Size - QS_TOTAL_LENGTH_FIELD_SIZE;
                free(portCxt->pending.buf);
                UpdatePendingPacket(&portCxt->pending, 0, 0, NULL);

                if(rcvd_Len < rqd_DataLen) {
                    /* Current Rx buffer missing some of the required bytes. */
                    memcpy(req + QS_TOTAL_LENGTH_FIELD_SIZE, buf, rcvd_Len);
                    UpdatePendingPacket(&portCxt->pending, rqd_DataLen - rcvd_Len,
                                        QS_TOTAL_LENGTH_FIELD_SIZE + rcvd_Len, req);

                    ret_Val = ssIncompleteData;
                    break;
                }
                else {
                    /* One or more than one packets received in Rx buffer. */
                    buf = UpdateBuffer(portCxt, req + QS_TOTAL_LENGTH_FIELD_SIZE, \
                                               buf, rqd_DataLen, &rcvd_Len, req);
                    /* continue to start of while(rcvd_Len) */
                }
            }

            /*******************************************************************************************/
            /* Incomplete packet was received in previous Rx interrupt. */
            else {
                req = portCxt->pending.buf;
                if(rcvd_Len < portCxt->pending.rqdBytes)
                {
                    /* Current Rx buffer missing some of the required bytes. */
                    memcpy(req + portCxt->pending.bufPtr, buf, rcvd_Len);
                    UpdatePendingPacket(&portCxt->pending, portCxt->pending.rqdBytes - rcvd_Len,
                                        portCxt->pending.bufPtr + rcvd_Len, req);
                    ret_Val = ssIncompleteData;
                    break;
                }
                else
                {
                    /* One or more than one packets received in Rx buffer.
                     * Add new packet in queue and continue to start of while(rcvd_Len). */
                    req = portCxt->pending.buf;
                    buf = UpdateBuffer(portCxt, req + portCxt->pending.bufPtr, \
                                    buf, portCxt->pending.rqdBytes, &rcvd_Len, req);
                    UpdatePendingPacket(&portCxt->pending, 0, 0, NULL);
                    /* continue to start of while(rcvd_Len) */
                }
            }
        }

        /* ret_Val = ssSuccess when one/more complete packets are received.
         * ret_Val = ssIncompleteData when incomplete packet is received along with some complete ones.
         */
        if((ssSuccess == ret_Val) || (ssIncompleteData == ret_Val))
        {
            while((ssSuccess == QsDeq(&portCxt->rxQueue, (void **)&req)) && req)
            {
                /* Process the received commands.
                 * Services must free the memory after done. */
                if(ssSuccess != mmlEnq(req, MML_DIR_RCV))
                {
                    QsReleaseBuf(req);
                }
                req = NULL;
            }
        }
        else {
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
//        memset(portCxt->rx_Buf[cur_Index], 0, UART_RX_BUF_SIZE);
        qapi_UART_Receive(portCxt->handle, (char *)(portCxt->rx_Buf[cur_Index]), UART_RX_BUF_SIZE, (void *)cb_Data);
    }

    if(portCxt->pending.buf)
    {
        free(portCxt->pending.buf);
    }
    qurt_thread_stop();
}


/* This is the thread to process incoming QAPIs, data, management packets. */
void UartTxThread(void *param)
{
    uint32_t signal_Set = 0, port = 0, retVal = 0;
    int32_t result = 0;
    char *txBuf = NULL;
    uartCommonCxt_t *uartCxt = NULL;
    uartPortCxt_t *portCxt = NULL;

    uartCxt = QH_UART_CXT(qsCommonCxt);
    if(!uartCxt)
    {
        return;
    }

    port = (uint32_t)param;
    portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);

    /* Loop waiting for incoming data. */
    while(portCxt && portCxt->uart_Enabled)
    {
        result = qurt_signal_wait_timed(&portCxt->event, TX_EVENT, QURT_SIGNAL_ATTR_CLEAR_MASK,
                (uint32 *)&signal_Set, QURT_TIME_WAIT_FOREVER);
        if(result != QURT_EOK)
        {
            /* This case will be TRUE when qurt_signal_destroy() is called. */
            break;
        }

        /* Dequeue packet from UART queue. */
        while((ssSuccess == QsDeq(&portCxt->txQueue, (void **)&txBuf)) && txBuf)
        {
            ENTER_CRITICAL();
			/* Find the length. */
			portCxt->bytes_To_Tx = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(txBuf);
            EXIT_CRITICAL();

            retVal = qapi_UART_Transmit(portCxt->handle, txBuf, portCxt->bytes_To_Tx, (void *)port);
            if(QAPI_OK == retVal) {
                /* Wait for Tx to complete */
                qurt_signal_wait(&portCxt->event, TX_COMPLETE_EVENT, QURT_SIGNAL_ATTR_CLEAR_MASK);
            }
            else {
                /* Failure: Set len to 0 to inform MML that SEND failed. */
				WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(txBuf, 0);
            }

            /* Enqueue the packet for MML which will then call service specific callback function. */
            retVal = mmlEnq(txBuf, MML_DIR_SEND);

            if(QAPI_OK != retVal)
            {
                /* Free txBuf shell which was added in mmlServiceQueueSend(). */
                free(txBuf);

                /* Possible memory leak here as txBuf->buf cannot be freed by this thread.
                 * txBuf->buf is provided by services which could be a static or dynamic */
            }

            /* If success, mmlTxCompleteThread() will free the txBuf shell and service 
             * specific Tx complete callback will free the data buffer */
            txBuf = NULL;
        }
    }
    qurt_thread_stop();
}

/* This function is used to enqueue packet in UART Tx queue. 
 * Uart Tx thread dequeue packets and sends then to host. */
uint32_t QsUartTransmit(uint32_t port, char *txBuf)
{
    uartPortCxt_t *portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);

    if(!portCxt || !txBuf)
    {
        return ssFailure;
    }

    if(ssSuccess != QsEnq(&portCxt->txQueue, (void *)txBuf))
    {
        return ssFailure;
    }

    qurt_signal_set(&portCxt->event, TX_EVENT);
    return ssSuccess;
}

/* Initialize the UART used by the demo. */
static uint32_t UartPortInit(qapi_UART_Port_Id_e port)
{
    qapi_UART_Open_Config_t uart_Cfg;
    uint8_t index = 0;
    uint32_t cb_Data = 0;
    uartPortCxt_t *portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);

    if(!portCxt)
    {
        return ssFailure;
    }

#ifdef CONFIG_CDB_PLATFORM
    uart_Cfg.baud_Rate        = 115200;
#else
    uart_Cfg.baud_Rate        = 2000000;
#endif
    uart_Cfg.parity_Mode      = QAPI_UART_NO_PARITY_E;
    uart_Cfg.num_Stop_Bits    = QAPI_UART_1_0_STOP_BITS_E;
    uart_Cfg.bits_Per_Char    = QAPI_UART_8_BITS_PER_CHAR_E;
    uart_Cfg.enable_Loopback  = FALSE;
#ifdef CONFIG_CDB_PLATFORM
    uart_Cfg.enable_Flow_Ctrl = FALSE;
#else
    uart_Cfg.enable_Flow_Ctrl = TRUE;
#endif /* CONFIG_CDB_PLATFORM */
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

uint32_t CreateUartThreads(uint32_t port)
{
    qurt_thread_attr_t attr;
    int result = -1;
    uint32_t signal_Set = 0;
    uartPortCxt_t *portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);

    /* Start the UART Rx thread. */
    qurt_thread_attr_init(&attr);
    qurt_thread_attr_set_name(&attr, "QsUartRx");
    qurt_thread_attr_set_priority(&attr, THREAD_PRIORITY);
    qurt_thread_attr_set_stack_size(&attr, STACK_SIZE);
    result = qurt_thread_create(&portCxt->rxThread, &attr, UartRxThread, (void *)port);
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

    /* Start the UART Tx thread. */
    qurt_thread_attr_init(&attr);
    qurt_thread_attr_set_name(&attr, "QsUartTx");
    qurt_thread_attr_set_priority(&attr, THREAD_PRIORITY);
    qurt_thread_attr_set_stack_size(&attr, STACK_SIZE);
    result = qurt_thread_create(&portCxt->rxThread, &attr, UartTxThread, (void *)port);
    if (QURT_EOK != result)
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
    uint32_t retVal = ssFailure;

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

    do
    {
        /* Return ssSuccess if same UART port is used for multiple modules */
        qurt_mutex_lock(&uartCxt->mutex);
        portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);
        qurt_mutex_unlock(&uartCxt->mutex);
        if(portCxt)
        {
            return ssSuccess;
        }

        /* Initialize the global UART portCxt */
        uartCxt->portCxt[port] = (uartPortCxt_t *)malloc(sizeof(uartPortCxt_t));
        if(!uartCxt->portCxt[port])
        {
            retVal = ssFailure;
            break;
        }

        portCxt = QH_UART_PORT_CXT(qsCommonCxt, port);
        memset(portCxt, 0, sizeof(uartPortCxt_t));
        portCxt->rx_Bufs_Free = UART_RX_BUF_CNT;

        if(QURT_EOK != qurt_mutex_create(&portCxt->mutex))
        {
            retVal = ssFailure;
            break;
        }

        if(QURT_EOK != qurt_signal_create(&portCxt->event))
        {
            retVal = ssFailure;
            break;
        }

        /* Configure and open UART port. */
        if(ssSuccess == UartPortInit((qapi_UART_Port_Id_e)port))
        {
            if(ssSuccess != CreateUartThreads(port))
            {
                retVal = ssFailure;
                break;
            }

            if(ssSuccess != QsInitQueue(&portCxt->txQueue))
            {
                retVal = ssFailure;
                break;
            }

            if(ssSuccess != QsInitQueue(&portCxt->rxQueue))
            {
                retVal = ssFailure;
                break;
            }

            qurt_mutex_lock(&uartCxt->mutex);
            uartCxt->numPortsInitialized++;
            qurt_mutex_unlock(&uartCxt->mutex);
            return ssSuccess;            
        }
    } while(0);

    /* Error */
    qurt_mutex_unlock(&uartCxt->mutex);
    (void)QsUartDeInit(port);
    return retVal;
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

    QsDeInitQueue(&portCxt->txQueue);
    QsDeInitQueue(&portCxt->rxQueue);

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

