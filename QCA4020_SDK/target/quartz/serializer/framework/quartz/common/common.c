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

/* Each buffer is made up of 4 bytes of metadata and then the data buffer. */
#define ALLOC_BYTES_SIZE             2
#define USED_BYTES_SIZE              2
#define METADATA_SIZE                (ALLOC_BYTES_SIZE + USED_BYTES_SIZE)
#define TOTAL_BUF_SIZE(databuf_size) (METADATA_SIZE + (databuf_size))
#define ALLOCSIZE_PTR(buf)           (&(((char *)(buf))[0]))
#define USEDSIZE_PTR(buf)            (&(((char *)(buf))[2]))
#define DATABUF_PTR(buf)             (&(((char *)(buf))[METADATA_SIZE]))
#define METADATA_PTR(dataBuf)        (((char *)(dataBuf)) - METADATA_SIZE)

qsCommonCxt_t *qsCommonCxt = NULL;

static int WaitCounter;	/*Temporary debug counter.. remove soon..*/

static SerStatus_t BufpoolInit(void *cxt)
{
    char *Buf = NULL;
    bufPool_t *BufPool = NULL;
    int index = 0;
    uint16_t Size = 0;
    uint32_t ret_Val = ssSuccess;
    qsCommonCxt_t *commonCxt = QH_COMMON_CXT(cxt);
    int buf_Cnt = 0;

    if(!commonCxt)
    {
        return ssFailure;
    }

    /* Buffer pools are already initialized */
    if(commonCxt->bufPool[0])
    {
        return ssSuccess;
    }

    for(index = 0; index < BUF_NUM_LISTS; index++)
    {
        commonCxt->bufPool[index] = (bufPool_t *)malloc(sizeof(bufPool_t));
        if(!commonCxt->bufPool[index])
        {
            ret_Val = ssFailure;
            break;
        }

        BufPool = commonCxt->bufPool[index];
        memset(BufPool, 0, sizeof(bufPool_t));

        BufPool->count = 0;
        if(QURT_EOK != qurt_mutex_create(&BufPool->mutex))
        {
            ret_Val = ssFailure;
            break;
        }

        switch(index)
        {
			case BUF_INDEX_64:
                BufPool->threshold = BUF_NUM_64;
                Size = BUF_SIZE_64;
                break;
				
            case BUF_INDEX_128:
                BufPool->threshold = BUF_NUM_128;
                Size = BUF_SIZE_128;
                break;

            case BUF_INDEX_256:
                BufPool->threshold = BUF_NUM_256;
                Size = BUF_SIZE_256;
                break;

            case BUF_INDEX_512:
                BufPool->threshold = BUF_NUM_512;
                Size = BUF_SIZE_512;
                break;

            case BUF_INDEX_1024:
                BufPool->threshold = BUF_NUM_1024;
                Size = BUF_SIZE_1024;
                break;

            case BUF_INDEX_2048:
                BufPool->threshold = BUF_NUM_2048;
                Size = BUF_SIZE_2048;
                break;
        }

        if(ssSuccess != QsInitQueue(&BufPool->queue))
        {
            ret_Val = ssFailure;
            break;
        }

        for (buf_Cnt = 0; buf_Cnt < BufPool->threshold; buf_Cnt++)
        {
            Buf = (char *)malloc(TOTAL_BUF_SIZE(Size));
            if (!Buf)
            {
                ret_Val = ssFailure;
                break;
            }
            memset(Buf, 0, TOTAL_BUF_SIZE(Size));
            memcpy(ALLOCSIZE_PTR(Buf), &Size, ALLOC_BYTES_SIZE);
			ret_Val = QsEnq(&BufPool->queue, Buf);
			if(ssSuccess != ret_Val)
			{
				break;
			}
			BufPool->count++;
        }

        if(ssSuccess != ret_Val)
        {
            break;
        }

        ret_Val = ssSuccess;
    }

    return ret_Val;
}

static void BufpoolDeInit(void *cxt)
{
    bufPool_t *BufPool = NULL;
    int index = 0;

    qsCommonCxt_t *commonCxt = QH_COMMON_CXT(cxt);
    if(!commonCxt)
        return;

    for(index = 0; index < BUF_NUM_LISTS; index++)
    {
        BufPool = commonCxt->bufPool[index];
        if(!BufPool)
            continue;

        QsDeInitQueue(&BufPool->queue);
        qurt_mutex_delete(&BufPool->mutex);
        free(BufPool);
        commonCxt->bufPool[index] = NULL;
    }
    return;
}

static SerStatus_t TransportDeInit(void *cxt)
{
    uint32_t ret_Val = ssSuccess;
    qapi_Exhost_Devcfg_t *devcfgCxt = QH_DEVCFG_CXT(cxt);

    if( !devcfgCxt )
    {
        return ssFailure;
    }

    if( devcfgCxt->uart_enable != 0) {
        if( devcfgCxt->uart_port == 0 )  //high speed uart
            ret_Val = QsUartDeInit(QAPI_UART_HS_PORT_E);
        else
            ret_Val = QsUartDeInit(QAPI_UART_DEBUG_PORT_E);
    }

    if( devcfgCxt->spi_enable != 0)
    {
        ret_Val = QsSPIDeInit();
    }

    return ret_Val;
}

/* Common transport layer initialization */
static SerStatus_t TransportInit(void *cxt)
{
    uint32_t ret_Val = ssSuccess;
    qapi_Exhost_Devcfg_t *devcfgCxt = QH_DEVCFG_CXT(cxt);

    if( !devcfgCxt )
    {
        return ssFailure;
    }

    if( devcfgCxt->uart_enable != 0) {
        if( devcfgCxt->uart_port == 0 )  //high speed uart
            ret_Val = QsUartInit(QAPI_UART_HS_PORT_E);
        else
            ret_Val = QsUartInit(QAPI_UART_DEBUG_PORT_E);
    }

    if( (ret_Val == ssSuccess) && (devcfgCxt->spi_enable != 0) )
    {
        ret_Val = QsSPIInit();
    }
    return ret_Val;
}

/* Deinitialize devcfg context. */
static void DevcfgDeInit(void *Cxt)
{
    qapi_Exhost_Devcfg_t *devcfgCxt = QH_DEVCFG_CXT(Cxt);

    if( devcfgCxt != NULL )
        free(devcfgCxt);
    QH_COMMON_CXT(Cxt)->devcfgCxt = NULL;
}

/* Initialize Devcfg context. */
static SerStatus_t DevcfgInit(void *Cxt)
{
    qapi_Exhost_Devcfg_t *devcfgCxt = QH_DEVCFG_CXT(Cxt);

    if(QH_COMMON_CXT(Cxt)->devcfgCxt)
    {
        return ssSuccess;
    }

    do
    {
        QH_COMMON_CXT(Cxt)->devcfgCxt = (qapi_Exhost_Devcfg_t *)malloc(sizeof(qapi_Exhost_Devcfg_t));
        devcfgCxt = QH_DEVCFG_CXT(Cxt);
        if(!devcfgCxt)
        {
            break;
        }

        memset(devcfgCxt, 0, sizeof(qapi_Exhost_Devcfg_t));
        if( qapi_Get_Exhost_Devcfg(devcfgCxt) != QAPI_OK )
        {
            break;
        }

        /* init is done with no error */
        return ssSuccess;
    } while(0);

    return ssFailure;
}

SerStatus_t QsInit()
{
    qsCommonCxt_t *commonCxt = NULL;

    if(qsCommonCxt)
    {
        return ssFailure;
    }

    /* Allocate common context */
    qsCommonCxt = (qsCommonCxt_t *)malloc(sizeof(qsCommonCxt_t));
    if(!qsCommonCxt)
    {
        goto Error;
    }
    commonCxt = qsCommonCxt;
    memset(commonCxt, 0, sizeof(qsCommonCxt_t));

    /* Initialize buffer pool */
    if(ssSuccess != BufpoolInit(commonCxt))
    {
        goto Error;
    }

    /* Initialize devCfg */
    if(ssSuccess != DevcfgInit(commonCxt))
    {
        goto Error;
    }

    /* Initialize transports depending on the devCfg */
    if(ssSuccess != TransportInit(commonCxt) )
    {
        goto Error;
    }

    /* Initialize MML and datamanager only for the daemon mode */
    if(ssSuccess != mmlInit(commonCxt))
    {
        goto Error;
    }

#ifdef CONFIG_TARGET_IOTDMGR
    /* Initialize management framework between target and daemon */
    if(ssSuccess != MgmtInit(commonCxt))
    {
        goto Error;
    }
#endif

#ifdef CONFIG_TARGET_DATAMGR
    /* Datamanager initialization */
    if(ssSuccess != DMInit(commonCxt))
    {
        goto Error;
    }
#endif

#ifdef CONFIG_TARGET_DIAGMGR
    /* Diagmanager initialization */
    if(ssSuccess != DiagInit(commonCxt))
    {
        goto Error;
    }
#endif

#ifdef CONFIG_TARGET_QAPI
    /* Initialize QAPI serialization framework */
    if(ssSuccess != QapiInit(commonCxt))
    {
        goto Error;
    }
#endif

    return ssSuccess;

Error:
    (void)QsDeInit();
    return ssFailure;
}


SerStatus_t QsDeInit()
{
    qsCommonCxt_t *commonCxt = qsCommonCxt;
    if(!commonCxt)
    {
        return ssFailure;
    }

#ifdef CONFIG_TARGET_QAPI
    QapiDeInit(commonCxt);
#endif
#ifdef CONFIG_TARGET_DIAGMGR
    DiagDeInit(commonCxt);
#endif
#ifdef CONFIG_TARGET_DATAMGR
    DMDeInit(commonCxt);
#endif
#ifdef CONFIG_TARGET_IOTDMGR
    MgmtDeInit(commonCxt);
#endif

    mmlDeInit(commonCxt);
    TransportDeInit(commonCxt);
    DevcfgDeInit(commonCxt);
    BufpoolDeInit(commonCxt);
    free(commonCxt);
    qsCommonCxt = NULL;
    return ssSuccess;
}

SerStatus_t QsInitQueue(queue_t *Q)
{
    if(!Q)
        return ssFailure;

    Q->head = NULL;
    Q->tail = NULL;
    if(QURT_EOK != qurt_mutex_create(&Q->mutex))
        return ssFailure;

    return ssSuccess;
}

SerStatus_t QsFreeQueue(queue_t *Q)
{
    bufInfo_t *buf = NULL;

    /* Delete all the items in given queue */
    qurt_mutex_lock(&Q->mutex);
    while(Q->head)
    {
        buf = (bufInfo_t *)Q->head;
        Q->head = buf->next;
        free(buf->buf);
        free(buf);
    }
    Q->tail = NULL;
    qurt_mutex_unlock(&Q->mutex);
    return ssSuccess;
}

SerStatus_t QsDeInitQueue(queue_t *Q)
{
    if(!Q)
        return ssFailure;

    if(ssSuccess == QsFreeQueue(Q))
    {
        qurt_mutex_delete(&Q->mutex);
        return ssSuccess;
    }
    return ssFailure;
}

SerStatus_t QsEnq(queue_t *Q, void *Buf)
{
    bufInfo_t *BufInfo = NULL;
    if(!Q || !Buf)
    {
        return ssFailure;
    }

    /* Encapsulate data buffer in a shell */
    BufInfo = (bufInfo_t *)malloc(sizeof(bufInfo_t));
    if(!BufInfo)
    {
        return ssFailure;
    }
    BufInfo->buf = Buf;
    BufInfo->next = NULL;

    /* Enqueue the buffer at the end of the queue */
    qurt_mutex_lock(&Q->mutex);
    if(!Q->head && !Q->tail)
    {
        Q->head = (void *)BufInfo;
        Q->tail = (void *)BufInfo;
    }
    else
    {
        ((bufInfo_t *)Q->tail)->next = BufInfo;
        Q->tail = (void *)BufInfo;
    }
    qurt_mutex_unlock(&Q->mutex);
    return ssSuccess;
}

SerStatus_t QsDeq(queue_t *Q, void **buf)
{
    bufInfo_t *BufInfo = NULL;

    if(!buf)
        return ssFailure;

    *buf = NULL;

    if(!Q || !Q->mutex)
        return ssFailure;

    /* Dequeue a buffer from the head of the queue */
    qurt_mutex_lock(&Q->mutex);
    if(Q->head)
    {
        BufInfo = (bufInfo_t *)Q->head;
        Q->head = BufInfo->next;
        if (!Q->head)
        {
            Q->tail = NULL;
        }

        /* Free the wrapper and return the data buffer pointer */
        *buf = BufInfo->buf;
        free(BufInfo);
        qurt_mutex_unlock(&Q->mutex);
        return ssSuccess;
    }

    qurt_mutex_unlock(&Q->mutex);
    return ssFailure;
}


SerStatus_t QsGetBuf(char **Buf, uint16_t Size, uint8_t type)
{
    bufPool_t *BufPool = NULL;
    uint16_t alloc_Bytes = 0;
    void *tempBuf = NULL;

    if (!Buf)
        return ssInvalidParameter;

    *Buf = NULL;
	
	/*Find the best fit pool for requested size. If that pool is empty, try the next one.
	  If all pools are empty, wait for a few ticks and try again. This will let the pool get
	  replenished*/
	do{
		if(Size <= BUF_SIZE_64)
		{
			BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_64);			
			alloc_Bytes = BUF_SIZE_64;
			if(type == BUF_TYPE_RESP){
				/*The get request is for a response type frame, give it higher priority*/
				if(BufPool->count){
					break;
				}
			}else{
				/*Ensure that some small buffers are reserved for RESPONSE packets*/
				if(BufPool->count > RESP_BUF_MIN_THRESHOLD){
					/*We have enough in reserve, use this buffer*/
					break;
				}
			}
		}
		if(Size <= BUF_SIZE_128)
		{
			BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_128);
			alloc_Bytes = BUF_SIZE_128;
			if(BufPool->count){
				break;
			}
		}
		if(Size <= BUF_SIZE_256)
		{
			BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_256);
			alloc_Bytes = BUF_SIZE_256;
			if(BufPool->count)
				break;
		}
		if(Size <= BUF_SIZE_512)
		{
			BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_512);
			alloc_Bytes = BUF_SIZE_512;
			if(BufPool->count)
				break;

		}
		if(Size <= BUF_SIZE_1024)
		{
			BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_1024);
			alloc_Bytes = BUF_SIZE_1024;
			if(BufPool->count)
				break;
		}
		if(Size <= BUF_SIZE_2048)
		{
			BufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_2048);
			alloc_Bytes = BUF_SIZE_2048;
			if(type == BUF_TYPE_RX){
				/*Special case, someone is asking for RX buffer, give it higher priority*/
				if(BufPool->count)
					break;
			}else{
				/*Generix request, only allow if we are above the RX buf threshold*/
				if(BufPool->count > RX_BUF_MIN_THRESHOLD)
					break;
				
			}
		}
		if(Size > BUF_SIZE_2048)
		{
			return ssInvalidParameter;
		}
		WaitCounter++;
	    qurt_thread_sleep(QS_BUFPOOL_WAIT_TIME);
	} while(1);

    if(BufPool && (ssSuccess == QsDeq(&BufPool->queue, &tempBuf)) && tempBuf)
    {
		qurt_mutex_lock(&BufPool->mutex);
        BufPool->count--;
		qurt_mutex_unlock(&BufPool->mutex);
    }
    else
    {		
		/*This should not fail*/
		ASSERT(0);
	}

    memcpy(ALLOCSIZE_PTR(tempBuf), &alloc_Bytes, ALLOC_BYTES_SIZE);
    memcpy(USEDSIZE_PTR(tempBuf), &Size, USED_BYTES_SIZE);
//    memset(DATABUF_PTR(tempBuf), 0, Size);
    *Buf = DATABUF_PTR(tempBuf);
    return ssSuccess;
}


SerStatus_t QsReleaseBuf(char *Buf)
{
    bufPool_t *bufPool = NULL;
    uint16_t alloc_Bytes = 0;

    if(!Buf)
        return ssInvalidParameter;

    /* Each buffer has METADATA_SIZE metadata before the data */
    Buf = METADATA_PTR(Buf);
    memcpy(&alloc_Bytes, ALLOCSIZE_PTR(Buf), ALLOC_BYTES_SIZE);

    switch(alloc_Bytes)
    {
		 case BUF_SIZE_64:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_64);
            break;
			
        case BUF_SIZE_128:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_128);
            break;

        case BUF_SIZE_256:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_256);
            break;

        case BUF_SIZE_512:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_512);
            break;

        case BUF_SIZE_1024:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_1024);
            break;

        case BUF_SIZE_2048:
            bufPool = QH_BUFPOOL(qsCommonCxt, BUF_INDEX_2048);
            break;

        default:
            bufPool = NULL;
            break;
    }

    if(bufPool)
    {
        /* Replenish the global free list if it is running low on buffers */
        if(ssSuccess == QsEnq(&bufPool->queue, Buf))
        {
            qurt_mutex_lock(&bufPool->mutex);
            bufPool->count++;
            qurt_mutex_unlock(&bufPool->mutex);
            return ssSuccess;
        }
    }

    free(Buf);
    return ssSuccess;
}

uint16_t QsSizeOf(char *buf)
{
    uint16_t len = 0;
    if(!buf || !METADATA_PTR(buf) || !USEDSIZE_PTR(METADATA_PTR(buf)))
        return len;

    memcpy(&len, USEDSIZE_PTR(METADATA_PTR(buf)), USED_BYTES_SIZE);
    return len;
}

#endif /* CONFIG_DAEMON_MODE */

