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

#include <stdlib.h>
#include "common_cxt.h"
#include "qurt_error.h"

#ifdef CONFIG_DAEMON_MODE

/* HTC header format:
 * Bytes 0-1: Total packet length (including header)
 * Bytes 2-3: Reserved field */
static void AddHtcHeader(char *BufPtr, uint16_t TotalLength)
{
    HtcHeader_t *header = (HtcHeader_t *)HTC_HEADER(BufPtr);
    WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&header->TotalLength, TotalLength); /* Total length */
    WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&header->Reserved, 0); /* Reserved */
    return;
}

/* MML header format:
 * Bytes 0: Service ID
 * Bytes 1: Reserved field.
 * Bytes 2-5: Cookie */
static void AddMmlHeader(char *BufPtr, uint8_t SqId, uint32_t Cookie)
{
    MmlHeader_t *header = (MmlHeader_t *)MML_HEADER(BufPtr);
    WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8(&header->SqId, SqId); /* Service ID */
    WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8(&header->Reserved, 0); /* Reserved */
    WRITE_UNALIGNED_LITTLE_ENDIAN_UINT32(&header->Cookie, Cookie); /* Cookie */
    return;
}

/* All services should call this API to send packets to daemon.
 * ServiceData will be ignored for all services except QAPI */
MmlReturnCodes_t mmlServiceQueueSend(uint8_t SqId, uint16_t BufLen, char *Buf, void *serviceData)
{
    serviceQueue_t *serviceInfo = NULL;
    uartPortCxt_t *portCxt = NULL; 
    
    if(!Buf || !BufLen)
    {
        return MML_INVALID_DATA_E;
    }

    AddHtcHeader(Buf, BufLen);

    if(SqId == MML_QAPI_SQ_ID)
    {
        AddMmlHeader(Buf, SqId, (uint32_t)serviceData);
    }
    else
    {
        AddMmlHeader(Buf, SqId, 0);
    }

    /* Before sending any message to host, confirm that message sent and rcv callbacks
     * are registered for the given service queue ID */
    serviceInfo = QH_MML_SERVICE_INFO(qsCommonCxt, SqId);
    if(!serviceInfo || !serviceInfo->msgRcvdCb || !serviceInfo->msgSentCb)
    {
        return MML_INVALID_SQ_ID_E;
    }

    portCxt = QH_UART_PORT_CXT(qsCommonCxt, QAPI_UART_HS_PORT_E);
    if( (portCxt != NULL) && (portCxt->uart_Enabled == TRUE) )
    {
        return QsUartTransmit(QAPI_UART_HS_PORT_E, Buf);
    } 

    portCxt = QH_UART_PORT_CXT(qsCommonCxt, QAPI_UART_DEBUG_PORT_E);
    if( (portCxt != NULL) && (portCxt->uart_Enabled == TRUE) )
    {
        return QsUartTransmit(QAPI_UART_DEBUG_PORT_E, Buf);
    } 
    
    return QsSpiTransmit(Buf);
}

MmlReturnCodes_t mmlServiceRegisterCb(uint8_t SqId, mmlCb_t msgRcvdCb, mmlCb_t msgSentCb, void *serviceCxt)
{
    serviceQueue_t *serviceInfo = QH_MML_SERVICE_INFO(qsCommonCxt, SqId);
    /* Check if service context for the given service queue ID s intialized and confirmed that
     * callbacks haven't already been registered for the same. */
    if(serviceInfo)
    {
        if(serviceInfo->msgRcvdCb || serviceInfo->msgSentCb || serviceInfo->serviceCxt)
        {
            return MML_SQ_ID_IN_USE;
        }
    
        serviceInfo->msgRcvdCb = msgRcvdCb;
        serviceInfo->msgSentCb = msgSentCb;
        serviceInfo->serviceCxt = serviceCxt;
        return MML_SUCCESS_E;
    }
    return MML_FAILURE_E;
}

MmlReturnCodes_t mmlServiceDeregisterCb(uint8_t SqId, void *serviceCxt)
{
    serviceQueue_t *serviceInfo = QH_MML_SERVICE_INFO(qsCommonCxt, SqId);
    if(serviceInfo && (serviceInfo->serviceCxt == serviceCxt))
    {
        serviceInfo->msgRcvdCb = NULL;
        serviceInfo->msgSentCb = NULL;
        serviceInfo->serviceCxt = NULL;
        return MML_SUCCESS_E;
    }
    return MML_FAILURE_E;
}

/* Release function to be called by service specifc RCV callbacks */
MmlReturnCodes_t mmlReleaseBuf(uint8_t SqId, char *Buf)
{
    if(!Buf)
        return MML_FAILURE_E;

    /* Rcv complete callbacks set by the services accept buffer length and 
     * pointer to start of the service related data in the received buffer.
     * However, the buffer also has QS_IOTD_HEADER_LEN bytes at the beginning.
     * Hence following logic first goes to the original start of the buffer and frees
     * complete buffer.
     * This is why callbacks MUST use this function and not standard library free() */
    char *original_buf_ptr = Buf - QS_IOTD_HEADER_LEN;
    if(original_buf_ptr)
    {
        if(ssSuccess == QsReleaseBuf(original_buf_ptr))
            return MML_SUCCESS_E;
    }
    return MML_FAILURE_E;
}


#endif /* CONFIG_DAEMON_MODE */

