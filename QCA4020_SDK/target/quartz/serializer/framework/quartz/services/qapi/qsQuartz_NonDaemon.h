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

#ifndef __QS_QUARTZ_NONDAEMON_H__
#define __QS_QUARTZ_NONDAEMON_H__

#ifndef CONFIG_DAEMON_MODE


#include "qsCommon.h"
#include "qurt_thread.h"
#include "qurt_mutex.h"
#include "qurt_signal.h"
#include "qapi_status.h"
#include "qapi_types.h"
#include "qapi_uart.h"


/**********************************************************************************************************************/
/*************************************************   CONSTANTS   ******************************************************/
/**********************************************************************************************************************/

/* Events for Tx and Rx */
#define RX_EVENT           0x02
#define TX_READY_EVENT     0x04
#define TX_COMPLETE_EVENT  0x08

/* Information regarding buffers used by UART */
#define UART_RX_BUF_SIZE   2048
#define UART_RX_BUF_CNT    2

/* Multiple buffer lists of with buffer sizes 128, 256, 512, 1024 and 2048 bytes will be allocated during
 * initialization. Depending on the required size, appropriate buffer will be given to the applications */
#define BUF_NUM_LISTS      5
#define BUF_SIZE_128       128
#define BUF_NUM_128        8
#define BUF_INDEX_128      0
#define BUF_SIZE_256       256
#define BUF_NUM_256        4
#define BUF_INDEX_256      1
#define BUF_SIZE_512       512
#define BUF_NUM_512        2
#define BUF_INDEX_512      2
#define BUF_SIZE_1024      1024
#define BUF_NUM_1024       1
#define BUF_INDEX_1024     3
#define BUF_SIZE_2048      2048
#define BUF_NUM_2048       1
#define BUF_INDEX_2048     4


/**********************************************************************************************************************/
/**************************************************   STRUCTURES   ****************************************************/
/**********************************************************************************************************************/

/* Structure to for a queue. Enqueue and dequeue APIs use 'mutex' for atoic operations */
typedef struct queue_s {
    void         *head; /* queue head */
    void         *tail; /* queue tail */
    qurt_mutex_t mutex; /* Mutex for atomic operations on the queue */
} queue_t;


/* This structure holds state for each module */
typedef struct moduleCxt_s {
    uint16_t       transport; /* Type of transport for the given module */
    uint16_t       ifname;    /* Interface name - uased only for UART. See qapi_UART_Port_Id_e  */
    uint32_t       mask;      /* Mask used for module related signals */
    qurt_mutex_t   mutex;     /* Mutex */
    qurt_signal_t  event;     /* Semaphore for synchronization */
    queue_t        queue;     /* Queue of packets received from host for a given module */
} moduleCxt_t;


/* Common context for all the modules */
typedef struct moduleCommonCxt_s {
    uint8_t        numModulesInitialized; /* Number of modules initialized */
    qurt_mutex_t   mutex;                 /* Mutex */
    moduleCxt_t    *cxts[QS_MODULE_MAX];  /* Individual module contexts */
} moduleCommonCxt_t;


/* This structure holds information regarding each UART port. 
 * Only 2 ports exist - QAPI_UART_DEBUG_PORT_E and QAPI_UART_HS_PORT_E */
typedef struct uartPortCxt_s {
    uint32_t           ref_Cnt;                                   /* Number of modules using he port */
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
    qurt_thread_t      RxThread;                                  /* Thread to receive data on uart. */
} uartPortCxt_t;


/* Common context to hold UART related information */
typedef struct uartCommonCxt_s {
    uint8_t       numPortsInitialized;              /* Number of port initialized */
    qurt_mutex_t  mutex;                            /* Mutex */
    uartPortCxt_t *portCxt[QAPI_UART_MAX_PORTS_E];  /* Individual port contexts */
} uartCommonCxt_t;


/* Context for SPI mode */
typedef struct spiCxt_s {
} spiCxt_t;


/* HTC context */
typedef union htcCxt_u {
    uartCommonCxt_t    uartCxt;  /* Common UART context */
    spiCxt_t           spiCxt;   /* SPI context */
} htcCxt_u;


/* This structure defines buffers used for resquests and responses */
typedef struct bufInfo_s {
    uint16_t size;           /* Size 'buf' */
    char *buf;               /* Character buffer */
    struct bufInfo_s* next;  /* Next buffer in the list */
} bufInfo_t;


/* Linked list of buffers */
typedef struct bufPool_s {
    qurt_mutex_t mutex;  /* Mutex to ensure atomic operations on the count */
    uint16_t threshold;  /* Maximum buffers in a given buffer pool */
    uint16_t count;      /* Number of available free buffers */
    queue_t queue;       /* Queue of free buffers */
} bufPool_t;


/* Common target structure with all the contexts */
typedef struct qsCommonCxt_s {
    bufPool_t *bufPool[BUF_NUM_LISTS];     /* Free buffer pool */
    moduleCommonCxt_t *moduleCxt;          /* Common context for module information */
    htcCxt_u *htcCxt[QS_TRANSPORT_MAX_E];  /* HTC context */
} qsCommonCxt_t;
extern qsCommonCxt_t *qsCommonCxt;


/* Defintion of a function which handles API calls.
 * @param Buffer Buffer of the packed data for the function.
 * @param Length Length of the packed data.
 * @return Status result for parsing the function's information. This does not
 * include the return value of the API.
 */
typedef SerStatus_t (*FunctionHandler_t)(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);


/* Information for an entry in a file info list. */
typedef struct FileEntry_s
{
   FunctionHandler_t *FunctionList;   /* List of function handlers for the file. */
   uint16_t           FunctionCount;  /* Number of functions in the list. */
   uint16_t           Flags;          /* Flags for the function (future support). */
} FileEntry_t;



/**********************************************************************************************************************/
/**************************************************   FUNCTIONS   *****************************************************/
/**********************************************************************************************************************/

/*
 * Initialize Quartz serializer feature.
 *
 * @param       ModuleID          ID of the module to be initialized.
 * @param       TransportID       ID of the transport type.
 * @param       Ifname            Interface namet.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsInit(uint8_t ModuleID, uint32_t TransportID, uint32_t Ifname);


/*
 * Deinitialize Quartz serializer feature.
 *
 * @param       ModuleID          ID of the module to be de-initialized.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsDeInit(uint8_t ModuleID);


/*
 * Initialize given queue serializer feature.
 *
 * @param       Q                 Pointer to the queue to be initialized.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsInitQueue(queue_t *Q);


/*
 * Delete all entries from given queue.
 *
 * @param       Q                 Pointer to the queue to be freed.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsFreeQueue(queue_t *Q);


/*
 * Deinitialize given queue serializer feature.
 * This functions first frees the items in the queue and then deletes the queue.
 *
 * @param       Q                 Pointer to the queue to be deinitialized.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsDeInitQueue(queue_t *Q);


/*
 * Enqueue buffer in the given queue.
 *
 * @param       Q                 Pointer to the queue.
 * @param       Buf               Object to be enqueued.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsEnq(queue_t *Q, bufInfo_t *Buf);


/*
 * Dequeue reqeust from given queue.
 *
 * @param       Q                 Pointer to the queue.
 * @param       BufPtr            Pointer to retrieve the dequeued buffer.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsDeq(queue_t *Q, bufInfo_t **BufPtr);


/*
 * Enqueue QAPI request received from the host.
 *
 * @param       Buffer            Object to be enqueued.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsEnqQapi(bufInfo_t *Buffer);


/*
 * Dequeue QAPI request received  from the host.
 *
 * @param       ModuleID          Module ID of to find respective queue.
 * @param       ReqBufPtr         Pointer to retrieve the dequeued buffer.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsDeqQapi(uint8_t ModuleID, bufInfo_t **ReqBufPtr);


/*
 * Get buffer of type bufInfo_t from the buffer pool.
 *
 * @param       BufInfo           Pointer to retrieve buffer.
 * @param       Size              Required buffer size.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsGetBuf(bufInfo_t **BufInfo, uint16_t Size);


/*
 * Release a buffer of type bufInfo_t.
 *
 * @param       BufInfo           Buffer to be freed.

 * @return      0 for success, non-zero for failure.
 */
SerStatus_t QsReleaseBuf(bufInfo_t *BufInfo);

/*
 * Allocates a packed buffer.
 *
 * @param       ModuleID          ID of the module sending this packet.
 * @param       FileID            ID of the file sending this packet.
 * @param       FunctionID        ID of the function sending this packet.
 * @param       PackedBuffer      Pointer to the packed buffer to be allocated.
 * @param       Size              Required size of the buffer.
 *
 * @return      TRUE: Success, FALSE: Failure
 */
Boolean_t AllocatePackedBuffer(uint8_t *UID, qsPacketType_t PacketType, uint8_t ModuleID, uint16_t FileID, uint16_t FunctionID, PackedBuffer_t *PackedBuffer, uint16_t Size);


/*
 * Frees a packed buffer.
 * @param       PackedBuffer      Pointer to the packed buffer to be freed.
 */
void FreePackedBuffer(PackedBuffer_t *PackedBuffer);


/*
 * Sends an asynchronous event packet.
 *
 * @param       InputBuffer       Pointer to the packed buffer to send.
 */
SerStatus_t SendEvent(PackedBuffer_t *InputBuffer);


/* 
 * Creates an error packet to send to the host.
 *
 * @param       ModuleID          ID of the module sending this packet.
 * @param       FileID            ID of the file sending this packet.
 * @param       FunctionID        ID of the function sending this packet.
 * @param       PackedBuffer      Pointer to the packed buffer to send.
 * @param       UID               Unique ID, copied from the QAPI command request packet.
 *
 * @return      TRUE: Success, FALSE: Failure
*/
Boolean_t CreateErrorPacket(uint8_t ModuleID, uint16_t FileID, uint16_t FunctionID, PackedBuffer_t *PackedBuffer, uint8_t *UID);


/* Creates an error callback packet to send to the host.
 *
 * @param       ModuleID          ID of the module sending this packet.
 * @param       FileID            ID of the file sending this packet.
 * @param       CallbackID        ID of the callback sending this packet.
 */
void SendErrorCallback(uint8_t ModuleID, uint8_t FileID, uint16_t CallbackID);



/**********************************************************************************************************************/
/***************************************************   MACROS   *******************************************************/
/**********************************************************************************************************************/

/* Macros to retrieve individual contexts */
#define QH_COMMON_CXT(cxt)                    ((cxt) ? ((qsCommonCxt_t *)(cxt)) : NULL)

#define QH_BUFPOOL(cxt,i)                     (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->bufPool[(i)] : NULL)

#define QH_MODULE_CMN_CXT(cxt)                (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->moduleCxt : NULL)
#define QH_IS_MODULE_VALID(module)            ((((module) >= 0) && ((module) < QS_MODULE_MAX)) ? 1 : 0)
#define QH_MODULE_INFO_CXT(cxt,module)        ((QH_MODULE_CMN_CXT(cxt) && QH_IS_MODULE_VALID(module)) ? \
                                                QH_MODULE_CMN_CXT(cxt)->cxts[(module)] : NULL)

#define QH_HTC_CXT(cxt,transport)             (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->htcCxt[(transport)] : NULL)

#define QH_UART_CXT(cxt)                      (QH_HTC_CXT(cxt,QS_UART_E) ? &QH_HTC_CXT(cxt,QS_UART_E)->uartCxt : NULL)
#define QH_IS_PORT_VALID(port)                ((((port) >= 0) && ((port) < QAPI_UART_MAX_PORTS_E)) ? 1 : 0 )
#define QH_UART_PORT_CXT(cxt,port)            ((QH_UART_CXT(cxt) && QH_IS_PORT_VALID(port)) ? \
                                                QH_UART_CXT(cxt)->portCxt[(port)] : NULL)

#define QH_SPI_CXT(cxt)                       (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->htcCxt[QS_SPI_E]->spiCxt : NULL)


#define QH_QZ_ENQ(buf,dir)                    QsEnqQapi((buf))
#define QH_QZ_DEQ(sqid,reqbufptr,dir,arg)     QsDeqQapi((*arg),(reqbufptr))
#define QH_QZ_TRANSMIT(len,buffer)            Transmit((len),(buffer))

#endif /* CONFIG_DAEMON_MODE */
#endif /* __QS_QUARTZ_NONDAEMON_H__ */


