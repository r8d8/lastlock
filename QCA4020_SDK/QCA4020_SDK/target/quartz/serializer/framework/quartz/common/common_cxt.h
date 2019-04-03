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

#ifndef __TARGET_COMMMON_CXT_H__
#define __TARGET_COMMMON_CXT_H__

#include "mml_internal.h"
#include "uart_internal.h"
#include "spi_internal.h"
#include "qapi_exhost_devcfg.h"

#ifdef CONFIG_TARGET_QAPI
#include "qsQuartz.h"
#endif

#ifdef CONFIG_TARGET_DATAMGR
#include "datamanager_internal.h"
#endif

#ifdef CONFIG_TARGET_IOTDMGR
#include "mgmt_internal.h"
#endif

#ifdef CONFIG_TARGET_DIAGMGR
#include "diag_internal.h"
#endif

/* HTC context */
typedef union htcCxt_u {
    uartCommonCxt_t    uartCxt;  /* Common UART context */
    spiCxt_t           spiCxt;   /* SPI context */
} htcCxt_u;

/* Common target structure with all the contexts */
typedef struct qsCommonCxt_s {
    bufPool_t *bufPool[BUF_NUM_LISTS];     /* Free buffer pool */
    mmlCxt_t *mmlCxt;                      /* MML context */
    htcCxt_u *htcCxt[QS_TRANSPORT_MAX_E];  /* HTC context */
    qapi_Exhost_Devcfg_t *devcfgCxt;       /* devcfg context */  

#ifdef CONFIG_TARGET_QAPI
    moduleCommonCxt_t *moduleCxt;          /* Common context for module information */
#endif

#ifdef CONFIG_TARGET_DATAMGR
    dataMgrCxt_t *dataMgrCxt;              /* Datamanager context */
#endif

#ifdef CONFIG_TARGET_IOTDMGR
    mgmtCxt_t *mgmtCxt;                    /* Management context */
#endif

#ifdef CONFIG_TARGET_DIAGMGR
    diagCxt_t *diagCxt;                    /* Diag context */
#endif

} qsCommonCxt_t;
extern qsCommonCxt_t *qsCommonCxt;

/* Macros to retrieve individual contexts */
#define QH_COMMON_CXT(cxt)                    ((cxt) ? ((qsCommonCxt_t *)(cxt)) : NULL)

#define QH_BUFPOOL(cxt,i)                     (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->bufPool[(i)] : NULL)

#define QH_MML_CXT(cxt)                       (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->mmlCxt : NULL)
#define QH_MML_IS_QID_VALID(qid)              (((((qid) & 0xF) >= 0) && (((qid) & 0xF) < NUM_SQ_ID)) ? 1 : 0 )
#define QH_MML_SERVICE_INFO(cxt,qid)          ((QH_MML_CXT(cxt) && QH_MML_IS_QID_VALID(qid)) ? (QH_MML_CXT(cxt)->sq[(qid)]) : NULL)
#define QH_MML_SERVICE_RXQUEUE(cxt,qid)       (QH_MML_SERVICE_INFO(cxt,qid) ? &(QH_MML_SERVICE_INFO(cxt,qid)->rxQueue) : NULL)
#define QH_MML_SERVICE_TXCOMPLETEQUEUE(cxt)   (QH_MML_CXT(cxt) ? &(QH_MML_CXT(cxt)->txCompleteQueue) : NULL)

#define QH_HTC_CXT(cxt,transport)             (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->htcCxt[(transport)] : NULL)

#define QH_UART_CXT(cxt)                      (QH_HTC_CXT(cxt,QS_UART_E) ? &QH_HTC_CXT(cxt,QS_UART_E)->uartCxt : NULL)
#define QH_IS_PORT_VALID(port)                ((((port) >= 0) && ((port) < QAPI_UART_MAX_PORTS_E)) ? 1 : 0 )
#define QH_UART_PORT_CXT(cxt,port)            ((QH_UART_CXT(cxt) && QH_IS_PORT_VALID(port)) ? \
                                                QH_UART_CXT(cxt)->portCxt[(port)] : NULL)

#define QH_SPI_CXT(cxt)                       (QH_COMMON_CXT(cxt) ? &(QH_COMMON_CXT(cxt)->htcCxt[QS_SPI_E]->spiCxt) : NULL)

#ifdef CONFIG_TARGET_QAPI
#define QH_MODULE_CMN_CXT(cxt)                (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->moduleCxt : NULL)
#define QH_IS_MODULE_VALID(module)            ((((module) >= 0) && ((module) < QS_MODULE_MAX)) ? 1 : 0)
#define QH_MODULE_INFO_CXT(cxt,module)        ((QH_MODULE_CMN_CXT(cxt) && QH_IS_MODULE_VALID(module)) ? \
                                                QH_MODULE_CMN_CXT(cxt)->cxts[(module)] : NULL)
#endif


#ifdef CONFIG_TARGET_DATAMGR
#define QH_DATAMGR_CXT(cxt)                   (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->dataMgrCxt : NULL)
#define QH_DATAMGR_IF_CXT(cxt)                (QH_DATAMGR_CXT(cxt) ? QH_DATAMGR_CXT(cxt)->interfaces : NULL)
#define QH_DATAMGR_SIGNAL(cxt)                (QH_DATAMGR_CXT(cxt) ? &QH_DATAMGR_CXT(cxt)->signal : NULL)
#endif

#ifdef CONFIG_TARGET_IOTDMGR
#define QH_MGMT_CXT(cxt)                      (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->mgmtCxt : NULL)
#define QH_MGMT_SIGNAL(cxt)                   (QH_MGMT_CXT(cxt) ? &QH_MGMT_CXT(cxt)->signal : NULL)
#endif

#ifdef CONFIG_TARGET_DIAGMGR
#define QH_DIAG_CXT(cxt)                      (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->diagCxt : NULL)
#define QH_DIAG_SIGNAL(cxt)                   (QH_DIAG_CXT(cxt) ? &QH_DIAG_CXT(cxt)->signal : NULL)
#endif

#define QH_DEVCFG_CXT(cxt)                    (QH_COMMON_CXT(cxt) ? QH_COMMON_CXT(cxt)->devcfgCxt : NULL)

#endif /* #ifndef __TARGET_COMMMON_CXT_H__ */
#endif /* CONFIG_DAEMON_MODE */
