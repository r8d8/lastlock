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
#include "qapi_status.h"
#include "qapi_types.h"
#include "qapi_uart.h"
#include "qapi_htc_slave.h"
#include "qurt_error.h"
#include "qurt_thread.h"
#include "common_cxt.h"
#include "spi_internal.h"


/*
 *  define empty Dbg_Printf function.
 *  app set it to real function.
 */
 
void Dbg_Printf_empty(char *fmt, ...)
{
    
}

void (*Dbg_Printf)(char *fmt, ...) = Dbg_Printf_empty;

 
void htc_sent_cb(uint32 instance, uint32 epid, uint32 bufarg);

/*
 *  buffer chain management
 *
 *  each of mbox endpoint has itself sending and receiving buffers.
 *  before data is sent, bufinfo is allocated from buffer, and fill the data, 
 *  and then call HTC sending function.
 *  after data is received, data is copied into data buufer from bufinfo.
 *
 */

 /*
 *  This function initializes bufinfo chain, it is called during SPI interface initialization
 *  @param epid  - endpoint ID.
 *  @param bufs_chain  - indicates buffer group(used to send or receive).
 *  
 */

qapi_HTC_bufinfo_t *htc_bufs_initialize(int epid, qapi_HTC_bufinfo_t *bufs_chain[])
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);
    qapi_HTC_bufinfo_t *bufchain;
    qapi_HTC_bufinfo_t *bufinfo;
    int i;
    char               *pbuf;
    
    //QCLI_Printf(qcli_dakota_htc_slave_group, "bufsz=%d\n", htc_bufsz_max);
    ASSERT(epid < QAPI_HTC_SLAVE_MAX_ENDPOINTS);
	
    bufchain = calloc(HTC_NUM_BUFFERS_PER_ENDPOINT, sizeof(qapi_HTC_bufinfo_t));
    ASSERT(bufchain);

    /* Remember for later so we can free this chain */
    bufs_chain[epid] = bufchain;

    for (i=0; i<HTC_NUM_BUFFERS_PER_ENDPOINT; i++) {
        bufinfo = &bufchain[i];

        QsGetBuf(&pbuf, spiCxt->htc_bufsz_max, BUF_TYPE_RX);
        bufinfo->buffer = (uint8 *)pbuf;
        ASSERT(bufinfo->buffer);

        bufinfo->buffer_offset = 0;
        bufinfo->actual_length = spiCxt->htc_bufsz_max;
        bufinfo->end_point = epid;
        bufinfo->next = &bufchain[i+1];
    }
    bufinfo->next = NULL;

    Dbg_Info_Printf("htc_bufs_initialize :%p count=%d\r\n", bufchain, i);

    return bufchain;
}

/*
 *  This function initializes HTC send buffers
 *  @param epid  - endpoint ID.
 *  
 */

qapi_HTC_bufinfo_t *htc_snd_bufs_init(int epid)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);
    qapi_HTC_bufinfo_t *bufchain;
    qapi_HTC_bufinfo_t *bufinfo;
    int i;

    Dbg_Info_Printf("htc_snd_bufs_init: epid=%d\r\n", epid);

    //QCLI_Printf(qcli_dakota_htc_slave_group, "bufsz=%d\n", htc_bufsz_max);
    ASSERT(epid < QAPI_HTC_SLAVE_MAX_ENDPOINTS);
	
    bufchain = calloc(HTC_NUM_SND_BUFFERS_PER_ENDPOINT, sizeof(qapi_HTC_bufinfo_t));
    ASSERT(bufchain);

    /* Remember for later so we can free this chain */
    spiCxt->htc_snd_bufchain[epid] = bufchain;

    for (i=0; i < HTC_NUM_SND_BUFFERS_PER_ENDPOINT; i++) {
        bufinfo = &bufchain[i];
        bufinfo->buffer_offset = 0;
        bufinfo->actual_length = spiCxt->htc_bufsz_max;
        bufinfo->end_point = epid;
        bufinfo->next = &bufchain[i+1];
    }
    bufinfo->next = NULL;

    Dbg_Info_Printf("htc_snd_bufs_init :%p count=%d\r\n", bufchain, i);

    return bufchain;
}

/*
 *  This function initializes HTC receiving buffers
 *  @param epid  - endpoint ID.
 *  
 */

qapi_HTC_bufinfo_t *htc_rcv_bufs_init(int epid)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);

    Dbg_Info_Printf("htc_rcv_bufs_init: epid=%d\r\n", epid);

    return htc_bufs_initialize(epid, spiCxt->htc_rcv_bufchain);
}

/*
 *  This function gets free bufinfo, it is called by get_snd_bufinfo and get_rcv_bufinfo
 *  @param epid  - endpoint ID.
 *  @param length  - buffer length.
 *  @param bufs_chain  - indicates buffer group(used to send or receive).
 *  
 */
qapi_HTC_bufinfo_t *get_bufinfo(int epid, int length, qapi_HTC_bufinfo_t *bufs_chain[])
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);
    qapi_HTC_bufinfo_t *bufinfo, *prev;
    int i;
    uint16_t   nbufs;

    ASSERT(epid < QAPI_HTC_SLAVE_MAX_ENDPOINTS);
   
    qurt_mutex_lock(&spiCxt->bufinfo_mutex);
        
    /* Remember for later so we can free this chain */
    bufinfo = bufs_chain[epid];
    if (bufinfo == NULL)
    {
        prev = NULL;
        goto end;
    }

    nbufs = (length + spiCxt->htc_bufsz_max - 1) / spiCxt->htc_bufsz_max;
    prev = bufinfo;

    for (i=0; i < nbufs && bufinfo != NULL; i++)
    {
		bufinfo->actual_length = spiCxt->htc_bufsz_max;
        prev = bufinfo;
        bufinfo = bufinfo->next;
    }

    if (i < nbufs)
    {
        prev = NULL;
        goto end;
    }

    prev->next = NULL;
    prev = bufs_chain[epid];

    bufs_chain[epid] = bufinfo;

	if (nbufs == 1)
		prev->actual_length = length;

end:
    qurt_mutex_unlock(&spiCxt->bufinfo_mutex);
    
    return prev;
}


/*
 *  This function gets HTC send bufinfo, it is called by SpiTxThread to get HTC send buffer
 *  @param epid  - endpoint ID.
 *  @param length  - needed buffer length.
 *  
 */

qapi_HTC_bufinfo_t *get_snd_bufinfo(int epid, int length)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);
    return get_bufinfo(epid, length, spiCxt->htc_snd_bufchain);
}

/*
 *  This function gets HTC receive bufinfo
 *  @param epid  - endpoint ID.
 *  @param length  - needed buffer length.
 *  
 */

qapi_HTC_bufinfo_t *get_rcv_bufinfo(int epid, int length)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);

    return get_bufinfo(epid, length, spiCxt->htc_rcv_bufchain);
}

/*
 *  This function free bufinfo for re-use, it is called by release_snd_bufinfo and release_rcv_bufinfo
 *  @param epid  - endpoint ID.
 *  @param bufInfo  - buffer that need to be release.
 *  @param bufs_chain  - indicates buffer group(used to send or receive).
 *  
 */

void release_bufinfo(int epid, qapi_HTC_bufinfo_t *pbuf, qapi_HTC_bufinfo_t *bufs_chain[])
{
    qapi_HTC_bufinfo_t *prev, *curr;
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);

    ASSERT(epid < QAPI_HTC_SLAVE_MAX_ENDPOINTS);

    qurt_mutex_lock(&spiCxt->bufinfo_mutex);

    if (pbuf == NULL)
        goto end;

    prev = pbuf;
    curr = pbuf;

    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    prev->next = bufs_chain[epid];
    bufs_chain[epid] = pbuf;
    
end:
    qurt_mutex_unlock(&spiCxt->bufinfo_mutex);
}

/*
 *  This function releases HTC send bufinfo, it is called by htc_sent_cb
 *  @param bufInfo  - buffer that need to be release.
 *  
 */
void release_snd_bufinfo(int epid, qapi_HTC_bufinfo_t *pbuf)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);

    release_bufinfo(epid, pbuf, spiCxt->htc_snd_bufchain);
    qurt_signal_set(&spiCxt->bufinfo_snd_signal, EVENT_SND_BUFOINF);
}

/*
 *  This function releases HTC receive bufinfo
 *  @param bufInfo  - buffer that need to be release.
 */

void release_rcv_bufinfo(int epid, qapi_HTC_bufinfo_t *pbuf)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);

    release_bufinfo(epid, pbuf, spiCxt->htc_rcv_bufchain);
}


/*
 * This function is thread
 * it used to write a buffer to SPI interface by waiting Tx Packet queue.
 * After transmitting the data, this function waits for the callback indicating transmission completed.
 */
static void SpiTxThread()
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);
    qapi_HTC_bufinfo_t *bufinfo = NULL, *p = NULL;
    char *txBuf = NULL;
    uint8_t *pdata = NULL;
    uint16_t nbufs = 0, i = 0, size = 0, totalSize = 0, padded_size;
    uint32_t signalSet = 0;
    qapi_HTCSlaveEndpointID_t epid = QAPI_HTC_SLAVE_ENDPOINT_ID0;
    int result = -1, ret;

    while(1)
    {
        result = qurt_signal_wait_timed(&spiCxt->txEvent, TX_EVENT, QURT_SIGNAL_ATTR_CLEAR_MASK,
                (uint32 *)&signalSet, QURT_TIME_WAIT_FOREVER);
        if(result != QURT_EOK)
        {
            /* This case will be TRUE when qurt_signal_destroy() is called. */
            Dbg_Printf("SpiTxThread signal fail\r\n");
            break;
        }

        /* Dequeue packet from Transmit queue. */
        while((ssSuccess == QsDeq(&spiCxt->txQueue, (void **)&txBuf)) && txBuf)
        {
			/* Find the length. */
			totalSize = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(txBuf);
          
            do {
                bufinfo = get_snd_bufinfo(epid, totalSize);


                if (bufinfo == NULL)
                {
                    //App_Dbg_Printf("SpiTxThread no sent buf\r\n");
                    qurt_signal_wait(&spiCxt->bufinfo_snd_signal, EVENT_SND_BUFOINF, QURT_SIGNAL_ATTR_CLEAR_MASK);
                }
            } while (bufinfo == NULL);

            p = bufinfo;
            padded_size = totalSize; //HTC_ROUND_UP(totalSize, SPI_BLOCKSIZE);

            nbufs = (padded_size + spiCxt->htc_bufsz_max - 1) / spiCxt->htc_bufsz_max;

            pdata = (uint8_t *)txBuf;

            for (i=0; i < nbufs && padded_size > 0 && p != NULL; i++)
            {
                if (padded_size > spiCxt->htc_bufsz_max)
                {
                    size = spiCxt->htc_bufsz_max;
                }
                else
                {
                    size = padded_size;
                }

                p->buffer = pdata;
                padded_size -= size;

                p->actual_length = size - HTC_HDR_SZ;
                p->end_point = epid;

                p=p->next;
                pdata += size;
            }

			spiCxt->dbg.sentCounter++;
			ret = qapi_HTC_Slave_Send_Data(spiCxt->htc_inst, epid, bufinfo);
            if(QAPI_OK == ret) {
                /* Wait for SEND to complete */
            }
            else {
                App_Dbg_Printf("SpiTxThread send fails %d\r\n", ret);
                /* Failure: Set len to 0 to inform MML that SEND failed. */
                WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(txBuf, 0);
            /* Enqueue the packet for MML which will then call the callback function */
                htc_sent_cb(spiCxt->htc_inst, epid, (uint32_t)bufinfo);
            }
        }
    }
    qurt_thread_stop();
}

/*
 * SPI receive thread
 * it used to write a buffer to SPI interface by waiting Rx Packet queue.
 * After transmitting the data, this function waits for the callback indicating transmission completed.
 */
static void SpiRxThread()
{
    qapi_HTC_bufinfo_t *bufinfo;
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);
    char *req = NULL;
    uint32_t signalSet = 0;
    int result = -1;
    
    while(1)
    {
        result = qurt_signal_wait_timed(&spiCxt->rxEvent, TX_EVENT, QURT_SIGNAL_ATTR_CLEAR_MASK,
                (uint32 *)&signalSet, QURT_TIME_WAIT_FOREVER);
        if(result != QURT_EOK)
        {
            /* This case will be TRUE when qurt_signal_destroy() is called. */
            Dbg_Printf("SpiRxThread signal fail\r\n");
            break;
        }

        /* Dequeue packet from Receive queue. */
        
        while (ssSuccess == QsDeq(&spiCxt->rxQueue, (void **)&bufinfo))
        {   
			spiCxt->dbg.rxCounter++;
			/*Get a new receive buffer so it can be queued to SPI slave*/
            if(ssFailure == QsGetBuf(&req, spiCxt->htc_bufsz_max, BUF_TYPE_RX))
            {
                Dbg_Printf("htc_recv_cb: fail to get buf\r\n");
                return;
            }
            
            bufinfo->buffer = (uint8_t *)req;
            bufinfo->actual_length = spiCxt->htc_bufsz_max;

            qapi_HTC_Slave_Receive_Data(spiCxt->htc_inst, bufinfo->end_point, bufinfo);
        }
    }
    qurt_thread_stop();
}


/*
 * This function is used to enqueue packet in SPI Tx queue. 
 * SPI Tx thread dequeue packets and sends then to host. 
 * @param bufInfo  - buffer that need to be sent.
 */
uint32_t QsSpiTransmit(char *buffer)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);

    if(!spiCxt || !buffer)
    {
        return ssFailure;
    }

    if(ssSuccess != QsEnq(&spiCxt->txQueue, (void *)buffer))
    {
        return ssFailure;
    }

    qurt_signal_set(&spiCxt->txEvent, TX_EVENT);
    return ssSuccess;
}

/*
 *
 * This function is a callback function, it is called by HTC after one packet is received
 * @param instance  SPI interface instance.
 * @param epid      mbox endpoint ID.
 * @param unused2   received buffer.
 *
 */

void htc_recv_cb(uint32 instance, uint32 epid, uint32 bufarg)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);

#ifdef  HIF_DEBUG
    uint32_t data_size, total_len;
#endif

    qapi_HTC_bufinfo_t *bufinfo = (qapi_HTC_bufinfo_t *)bufarg;


    if(bufinfo->actual_length <= QS_IOTD_HEADER_LEN)
    {
        Dbg_Printf("htc_recv_cb: buf len too small\r\n");
        // TODO
        return;
    }

#ifdef	HTC_LOOPTEST
    #define     HTC_TEST_YES        0x80
    #define     HTC_TEST_LOOPBACK   0x40
    #define     HTC_TEST_THROUGHPUT 0x20
    
	if (bufinfo->buffer[2] & HTC_TEST_YES)
	{
        int   flag;
        flag = bufinfo->buffer[2] & HTC_TEST_THROUGHPUT;
        
#ifdef  HIF_DEBUG
        if (flag == 0)
            Dbg_Info_Printf("htc_recv_cb: buffer[2]=0x%02X\r\n", bufinfo->buffer[2]);            
#endif        
		if (bufinfo->buffer[2] & HTC_TEST_LOOPBACK)
		{
			qapi_HTC_bufinfo_t  *snd_bufinfo;
			
#ifdef  HIF_DEBUG
            if (flag == 0)
                Dbg_Info_Printf("htc flag1: %02x len=%d\r\n", bufinfo->buffer[2], bufinfo->actual_length);
#endif
			snd_bufinfo = get_snd_bufinfo(epid, bufinfo->actual_length);
			snd_bufinfo->actual_length = bufinfo->actual_length - 4;

            if (flag == 0)
                memcpy(snd_bufinfo->buffer, bufinfo->buffer, bufinfo->actual_length);
            
			qapi_HTC_Slave_Receive_Data(spiCxt->htc_inst, epid, bufinfo);
		    qapi_HTC_Slave_Send_Data(spiCxt->htc_inst, epid, snd_bufinfo);
		}
		else
		{
			// htc layer tested packet
#ifdef  HIF_DEBUG
            if (flag == 0)
                Dbg_Info_Printf("htc flag1: %02x\r\n", bufinfo->buffer[2]);                
#endif
			qapi_HTC_Slave_Receive_Data(spiCxt->htc_inst, epid, bufinfo);			
		}
		return;
	}
#endif

#ifdef  HIF_DEBUG
    data_size = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(bufinfo->buffer);
    total_len = data_size+QS_HTC_HEADER_LEN;

    Dbg_Info_Printf("htc_recv_cb: epid=%d len=%d\r\n", epid, total_len);
#endif

    /* Process the received commands.
     * Services must free the memory after done. */
    if(ssSuccess == mmlEnq(bufinfo->buffer, MML_DIR_RCV))
    {
        if(ssSuccess != QsEnq(&spiCxt->rxQueue, (void *)bufinfo))
        {
            Dbg_Printf("htc_recv_cb: fail to get buf\r\n");
            return;            
        }
        qurt_signal_set(&spiCxt->rxEvent, TX_EVENT);
    }
    else
    {
        Dbg_Printf("htc_recv_cb: fail to mmlEnq\r\n");
        bufinfo->actual_length = spiCxt->htc_bufsz_max;        
        qapi_HTC_Slave_Receive_Data(spiCxt->htc_inst, epid, bufinfo);
    }
}

/*
 *
 * This function is a callback function, it is called by HTC after one packet is sent
 * @param instance  SPI interface instance.
 * @param epid      mbox endpoint ID.
 * @param unused2   sent buffer.
 *
 */
void htc_sent_cb(uint32 instance, uint32 epid, uint32 bufarg)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);
    qapi_HTC_bufinfo_t *bufinfo = (qapi_HTC_bufinfo_t *)bufarg;
    qapi_HTC_bufinfo_t *curr;

	if(bufinfo == NULL)
		ASSERT(0);
	
    curr = bufinfo;
    while (curr) {
        curr->actual_length = spiCxt->htc_bufsz_max;
        curr->buffer_offset = 0;
        ASSERT(curr->end_point == epid);

        /* Enqueue the packet for MML which will then call the callback function */
        mmlEnq((void *)curr->buffer, MML_DIR_SEND);
        curr = curr->next;

	}

    /* Enqueue the entire chain */
    release_snd_bufinfo(epid, bufinfo);
}

/*
 *
 * This function is a callback function, it is called by HTC after init done
 * @param instance  SPI interface instance.
 * @param unused1   n/a.
 * @param unused2   n/a.
 *
 */

void htc_init_done_cb(uint32 instance, uint32 unused1, uint32 unused2)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);

    qapi_HTC_Slave_Max_MsgSize_Get(instance, QAPI_HTC_SLAVE_ENDPOINT_ID0, &spiCxt->htc_bufsz_max);
    Dbg_Info_Printf("htc_init_done_cb msgsize=%d\r\n", spiCxt->htc_bufsz_max);

    qurt_signal_set(&spiCxt->HTC_init_done_signal, HTC_DEMO_WAITMASK_INITDONE);
}

/*
 *
 * This function is used to initialize SPI. it is called by TransportInit to initialize SPI interface
 * @param none.
 *
 */

uint32_t QsSPIInit()
{
    qapi_Status_t status;
    uint8 num_endpoints;
    spiCxt_t *spiCxt = NULL;
    qurt_thread_attr_t attr;
    int result = -1, waitmask;
    uint32_t retVal = ssSuccess;

    do
    {
        if (!qsCommonCxt->htcCxt[QS_SPI_E])
        {
            qsCommonCxt->htcCxt[QS_SPI_E] = (htcCxt_u*)malloc(sizeof(spiCxt_t));
            if(!qsCommonCxt->htcCxt[QS_SPI_E])
            {
                return ssFailure;
            }
            memset(qsCommonCxt->htcCxt[QS_SPI_E], 0, sizeof(spiCxt_t));

			
			// initializing variables

            qsCommonCxt->htcCxt[QS_SPI_E]->spiCxt.spi_initialized_flag = 0;
            qsCommonCxt->htcCxt[QS_SPI_E]->spiCxt.htc_inst = QAPI_HTC_SPI_SLAVE_INSTANCE_ID;
            qsCommonCxt->htcCxt[QS_SPI_E]->spiCxt.htc_bufsz_max = HTC_MAX_BUFSZ;
        }
        spiCxt = QH_SPI_CXT(qsCommonCxt);
        if (spiCxt->spi_initialized_flag)
        {
            return ssSuccess;
        }
        App_Dbg_Printf("QsSPIInit\r\n");

        qurt_signal_create(&spiCxt->HTC_init_done_signal);
        
        qurt_mutex_create(&spiCxt->bufinfo_mutex);
        qurt_signal_create(&spiCxt->bufinfo_snd_signal);
		qurt_signal_create(&spiCxt->init_sync);	
		qurt_signal_create(&spiCxt->bufinfo_rcv_signal);
	
		qurt_signal_create(&spiCxt->txEvent);
        if(ssSuccess != QsInitQueue(&spiCxt->txQueue))
        {
            retVal = ssFailure;
            break;
        }

        qurt_signal_create(&spiCxt->rxEvent);
		
        if(ssSuccess != QsInitQueue(&spiCxt->rxQueue))
        {
            retVal = ssFailure;
            break;
        }
		qurt_thread_sleep(50);		
        status = qapi_HTC_Slave_Init(spiCxt->htc_inst);
        if (status != QAPI_OK)
        {
            retVal = ssFailure;
            break;
        }

        status = qapi_HTC_Slave_Get_Num_Endpoints(spiCxt->htc_inst, &num_endpoints);
        if (status != QAPI_OK)
        {
            retVal = ssFailure;
            break;
        }

        status = qapi_HTC_Event_Register(spiCxt->htc_inst,
                QAPI_HTC_SLAVE_BUFFER_RECEIVED,
                htc_recv_cb, NULL);
        if (status != QAPI_OK)
        {
            retVal = ssFailure;
            break;
        }

        status = qapi_HTC_Event_Register(spiCxt->htc_inst,
                QAPI_HTC_SLAVE_BUFFER_SENT,
                htc_sent_cb, NULL);
        if (status != QAPI_OK)
        {
            retVal = ssFailure;
            break;
        }

        status = qapi_HTC_Event_Register(spiCxt->htc_inst,
                QAPI_HTC_SLAVE_INIT_COMPLETE,
                htc_init_done_cb, NULL);
        if (status != QAPI_OK)
        {
            retVal = ssFailure;
            break;
        }
     
        /* Kick off configuration negotiation */
        status = qapi_HTC_Slave_Start(spiCxt->htc_inst);
        if (status != QAPI_OK)
        {
            retVal = ssFailure;
            break;
        }

        spiCxt->spi_initialized_flag = 1;

    

        /* Start the SPI Tx thread. */
        qurt_thread_attr_init(&attr);
        qurt_thread_attr_set_name(&attr, "SpiTx");
        qurt_thread_attr_set_priority(&attr, SPI_THREAD_PRIORITY);
        qurt_thread_attr_set_stack_size(&attr, SPI_STACK_SIZE);
        result = qurt_thread_create(&spiCxt->txThread, &attr, SpiTxThread, NULL);
        if (QURT_EOK != result)
        {
            retVal = ssFailure;
            break;
        }
		
        /* Start the SPI Rx thread. */
        qurt_thread_attr_init(&attr);
        qurt_thread_attr_set_name(&attr, "SpiRx");
        qurt_thread_attr_set_priority(&attr, SPI_THREAD_PRIORITY);
        qurt_thread_attr_set_stack_size(&attr, SPI_STACK_SIZE);
        result = qurt_thread_create(&spiCxt->rxThread, &attr, SpiRxThread, NULL);
        if (QURT_EOK != result)
        {
            retVal = ssFailure;
            break;
        }
       
		Create_low_half_Thread();
		
		waitmask = qurt_signal_wait(&spiCxt->init_sync, HTC_DEMO_WAITMASK_INITDONE,
            QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);
			
		if ((waitmask & HTC_DEMO_WAITMASK_INITDONE) != HTC_DEMO_WAITMASK_INITDONE)
		{
			Dbg_Printf("SPI Init Failed\r\n");
            return ssFailure;
        }
		App_Dbg_Printf("Init complete\r\n");
        return ssSuccess;
    } while(0);

    QsSPIDeInit();
    return retVal;
}

/*
 * This function creates SPI bottom half thread, QsSPIInit call it for create thread
 * @param none.
 * 
 */

uint32_t Create_low_half_Thread()
{
    qurt_thread_attr_t attr;
    qurt_thread_t handle;
    int result = -1;

    /* Start the UART thread for receiving buf from host. */
    qurt_thread_attr_init(&attr);
    qurt_thread_attr_set_name(&attr, "QS_Half2");
    qurt_thread_attr_set_priority(&attr, SPI_THREAD_PRIORITY);
    qurt_thread_attr_set_stack_size(&attr, SPI_STACK_SIZE);
    result = qurt_thread_create(&handle, &attr, htc_init_low_half, (void *)NULL);
    if (QURT_EOK != result)
    {
        return ssFailure;
    }

    /* Wait for the new thread to start */
    return ssSuccess;
}

/*
 *
 * This function is SPI initialization bottom half thread.
 * @param param  pthread_create requirement, here, we don't use it.
 * 
 */

void htc_init_low_half(void *param)
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);
    qapi_Status_t status;
    uint32 waitmask;
    int epid;

    Dbg_Info_Printf("htc_init_low_half: #1\r\n");
    
	/*Signal the init thread to continue with initialization*/
	qurt_signal_set(&spiCxt->init_sync, HTC_DEMO_WAITMASK_INITDONE);
	
	/* Wait for initialization to complete */
    waitmask = qurt_signal_wait(&spiCxt->HTC_init_done_signal,
            HTC_DEMO_WAITMASK_INITDONE,
            QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);
    if ((waitmask & HTC_DEMO_WAITMASK_INITDONE) != HTC_DEMO_WAITMASK_INITDONE)
        return;
App_Dbg_Printf("1\n");
    status = qapi_HTC_Slave_Get_Num_Endpoints(spiCxt->htc_inst,
            &spiCxt->num_endpoints);
    if (status != QAPI_OK)
        return;

    spiCxt->htc_blksz = SPI_BLOCKSIZE;
    
    spiCxt->num_endpoints = 1;
    Dbg_Info_Printf("htc_init_low_half: nums=%d\r\n", spiCxt->num_endpoints);

    for (epid=0; epid<spiCxt->num_endpoints; epid++) {
        /* Use 1-buffer per message for now */
        status = qapi_HTC_Slave_Bufsz_Set(spiCxt->htc_inst,
                (qapi_HTCSlaveEndpointID_t)epid,
                spiCxt->htc_bufsz_max);
        if (status != QAPI_OK)
            return;

        status = qapi_HTC_Slave_Max_MsgSize_Set(spiCxt->htc_inst,
                (qapi_HTCSlaveEndpointID_t)epid,
                spiCxt->htc_bufsz_max);
        if (status != QAPI_OK)
            return;

        status = qapi_HTC_Slave_BlockSize_Set(spiCxt->htc_inst,
                (qapi_HTCSlaveEndpointID_t)epid,
                spiCxt->htc_blksz);

        if (status != QAPI_OK)
            return;
    }
App_Dbg_Printf("2\n");
    /* Supply receive buffers for each endpoint */
    for (epid=0; epid < spiCxt->num_endpoints; epid++) {
        qapi_HTC_bufinfo_t *bufchain;

        bufchain = htc_rcv_bufs_init(epid);
        if (bufchain == NULL)
        {
            Dbg_Printf("htc_init_low_half: no buffer for receive on %d\r\n", epid);
            return;
        }

        status = qapi_HTC_Slave_Receive_Data(spiCxt->htc_inst,
                epid, bufchain);
        if (status != QAPI_OK)
            return;

        bufchain = htc_snd_bufs_init(epid);

        if (bufchain == NULL)
        {
            Dbg_Printf("htc_init_low_half: no buffer for send on %d\r\n", epid);            
            return;
        }
    }
App_Dbg_Printf("3\n");
    qurt_thread_stop ();
}

/**
  @brief Turns off the SPI used by the demo.

  @return QT_SUCCESS if the SPI was deinitailized successfully or ssFailure if there was
  an error.
  */
uint32_t QsSPIDeInit()
{
    spiCxt_t *spiCxt = QH_SPI_CXT(qsCommonCxt);

    qapi_HTC_Event_Deregister(spiCxt->htc_inst,
            QAPI_HTC_SLAVE_BUFFER_RECEIVED);
    qapi_HTC_Event_Deregister(spiCxt->htc_inst,
            QAPI_HTC_SLAVE_BUFFER_SENT);
    qapi_HTC_Event_Deregister(spiCxt->htc_inst,
            QAPI_HTC_SLAVE_INIT_COMPLETE);
    qapi_HTC_Slave_Stop(spiCxt->htc_inst);
    qapi_HTC_Slave_Shutdown(spiCxt->htc_inst);

    qurt_signal_delete(&spiCxt->HTC_init_done_signal);

    qurt_signal_delete(&spiCxt->txEvent);
    QsDeInitQueue(&spiCxt->txQueue);
    return 0;
}

/*
 * htc_slave require this function
 */

void debug_buffer_print(qapi_HTC_bufinfo_t *buf, const char *str, int endpoint)
{
    int num = 0;
    //    QCLI_Printf(qcli_htc_slave_hdl,"BUFS-%d-%s: ", endpoint, str);
    if (buf == NULL) {
        //        QCLI_Printf(qcli_htc_slave_hdl, "none");
    }

    while (buf) {
        /*        QCLI_Printf(qcli_htc_slave_hdl, "[%d:0x%x:0x%x/0x%x] ",
                  num,
                  buf,
                  buf->buffer,
                  buf->actual_length);
                  */
        buf = buf->next;
        num++;
    }

    //    QCLI_Printf(qcli_htc_slave_hdl, "\n");
}

