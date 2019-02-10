/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc. 
 * All Rights Reserved. 
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * $QTI_LICENSE_QDN_C
 *
 * Amazon FreeRTOS TLS for QCOM QCA402X  V1.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "FreeRTOSIPConfig.h"
#include "aws_tls.h"
#include "aws_crypto.h"
//#include "aws_pkcs11.h"
#include "semphr.h"
#include "task.h"
#include "aws_clientcredential.h"
#include "aws_default_root_certificates.h"

/*qapi*/
#include "qapi_ssl.h"
#include "qapi_crypto.h"

/* C runtime includes. */
#include <string.h>
#include <time.h>
#include <stdio.h>


#define CFG_PACKET_SIZE_MAX_TX 1576 
#define CFG_PACKET_SIZE_MAX_RX 1556 

 /*It's used to get a CA file name to store in FLASH*/

 #define LEN_CA_NAME 32
/**
 * @brief Internal context structure.
 *
 * @param[in] pcDestination Server location, can be a DNS name or IP address.
 * @param[in] pcServerCertificate Server X.509 certificate in PEM format to trust.
 * @param[in] ulServerCertificateLength Length in bytes of the server certificate.
 * @param[in] pxNetworkRecv Callback for receiving data on an open TCP socket.
 * @param[in] pxNetworkSend Callback for sending data on an open TCP socket.
 * @param[in] pvCallerContext Opaque pointer provided by caller for above callbacks.
 * @param[out] sslCtx Handle to an SSL object.
 * @param[out] ssl Handle to an SSL connection.
 * @param[out] config Structure to configure an SSL connection.
 * @param[in] config_set Whether to do config.
 * @param[out]  role Active as client
 */
typedef struct TLSContext
{
    const char * pcDestination;
    const char * pcServerCertificate;
    uint32_t ulServerCertificateLength;
    const char ** ppcAlpnProtocols;
    uint32_t ulAlpnProtocolsCount;

    NetworkRecv_t pxNetworkRecv;
    NetworkSend_t pxNetworkSend;
    void * pvCallerContext;

    /* qcom TLS */
    qapi_Net_SSL_Obj_Hdl_t sslCtx;
    qapi_Net_SSL_Con_Hdl_t ssl;
    qapi_Net_SSL_Config_t   config;
    uint8_t      config_set;
    qapi_Net_SSL_Role_t role;    
    char caname[LEN_CA_NAME];
} TLSContext_t;

/*
 * Helper routines.
 */

static int prvGetHashName( const char * cert,
                          uint32_t len,
                          char* hash_name)
{
    qapi_Crypto_Op_Hdl_t opHdl;
    uint32_t name_len = 32;
    int i;
    int32_t status;

    status = qapi_Crypto_Op_Alloc(QAPI_CRYPTO_ALG_SHA1_E, QAPI_CRYPTO_MODE_DIGEST_E, 0, &opHdl);
    if (QAPI_OK == status)  //QAPI_OK is 0
    {
        if (QAPI_OK != qapi_Crypto_Op_Digest_Update(opHdl, (void*)cert, 32))
        {
            dconfigPRINTF(("\nFailed to digest update\n"));
            return -1;
        }
        if (QAPI_OK != qapi_Crypto_Op_Digest_Update(opHdl, (void*)cert, 64) ) 
        {
            dconfigPRINTF(("\nFailed to digest update\n"));
            return -1;
        }
        if (QAPI_OK != qapi_Crypto_Op_Digest_Final(opHdl, (void*)cert, (uint32_t)len-32-64, hash_name, &name_len))
        {
            dconfigPRINTF(("digest failed\n"));
            return -1;
        }
#if 0
        dconfigPRINTF(("Calc HASH name :%d.\n",name_len));
        for(i = 0; i< name_len; i++)
        {
             dconfigPRINTF((" %x ",hash_name[i]));
        }
#endif
        qapi_Crypto_Op_Free(opHdl);
        return name_len;
    }
    else
    {
        dconfigPRINTF(("qapi_Crypto_Op_Alloc failed,status:%d\n",status));
        return -1;
    }
}
static SemaphoreHandle_t g_tls_semaph;
BaseType_t TLS_Sys_Init()
{
    g_tls_semaph = xSemaphoreCreateMutex();
    if (NULL == g_tls_semaph)
        return pdFALSE;
    return pdPASS;
}
/*
 * Interface routines.
 */
BaseType_t TLS_Init( void ** ppvContext,
                     TLSParams_t * pxParams )
{
    BaseType_t xResult = 0;
    TLSContext_t * pCtx = NULL;
    int xNameLen;

    /* Allocate an internal context. */
    pCtx = ( TLSContext_t * ) pvPortMalloc( sizeof( TLSContext_t ) ); /*lint !e9087 !e9079 Allow casting void* to other types. */

    if( NULL != pCtx )
    {
        memset( pCtx, 0, sizeof( TLSContext_t ) );
        *ppvContext = pCtx;

        /* Initialize the context. */
        pCtx->pcDestination = pxParams->pcDestination;
        pCtx->pcServerCertificate = pxParams->pcServerCertificate;
        pCtx->ulServerCertificateLength = pxParams->ulServerCertificateLength;
        pCtx->ppcAlpnProtocols = pxParams->ppcAlpnProtocols;
        pCtx->ulAlpnProtocolsCount = pxParams->ulAlpnProtocolsCount;
        pCtx->pxNetworkRecv = pxParams->pxNetworkRecv;
        pCtx->pxNetworkSend = pxParams->pxNetworkSend;
        pCtx->pvCallerContext = pxParams->pvCallerContext;

        /*ssl */
        /*calculate the HASH name*/
        if(pCtx->pcServerCertificate)
        {
            xNameLen = prvGetHashName(pCtx->pcServerCertificate, pCtx->ulServerCertificateLength,pCtx->caname);
            if(-1 == xNameLen)
            {
                dconfigPRINTF(("Calc HASH name failed.\n"));
                return QAPI_ERROR;
            }
        }
        pCtx->role = QAPI_NET_SSL_CLIENT_E;
        pCtx->sslCtx = qapi_Net_SSL_Obj_New(pCtx->role);
        if (pCtx->sslCtx == QAPI_NET_SSL_INVALID_HANDLE)
        {
            return QAPI_ERROR;
        }

        /*Set SNI*/
        if(pCtx->pcDestination)
        {
            pCtx->config.sni_Name = pCtx->pcDestination;
            pCtx->config.sni_Name_Size = strlen(pCtx->pcDestination);
            pCtx->config_set = 1;
        }
    }
    else
    {
        xResult = ( BaseType_t ) QAPI_ERROR;
    }

    return xResult;
}

/*-----------------------------------------------------------*/

#ifdef QCOMTLS_DEBUG_C
    static void prvTlsDebugPrint( void * ctx,
                                  int level,
                                  const char * file,
                                  int line,
                                  const char * str )
    {
        /* Unused parameters. */
        ( void ) ctx;
        ( void ) file;
        ( void ) line;

        /* Send the debug string to the portable logger. */
        vLoggingPrintf( "TLS: |%d| %s", level, str );
    }
#endif /* ifdef MBEDTLS_DEBUG_C */

/*-----------------------------------------------------------*/
char* cert_with_key = "aws_cert_and_key_pemtobin";
char* defulat_calist = "defulat_calist_pemtobin";
qapi_Net_SSL_Cert_List_t cafile_list;
BaseType_t TLS_Connect( void * pvContext )
{
    BaseType_t xResult = 0;
    TLSContext_t * pCtx = ( TLSContext_t * ) pvContext; /*lint !e9087 !e9079 Allow casting void* to other types. */
    qapi_Net_SSL_Cert_Info_t cert_info;
    qapi_CA_Info_t ca_info;
    qapi_Status_t status;
    const TickType_t xTimeout = pdMS_TO_TICKS( 10000UL );

    if (pdTRUE == xSemaphoreTake(g_tls_semaph, xTimeout))
    {
    if (QAPI_OK != qapi_Net_SSL_Cert_Load(pCtx->sslCtx, QAPI_NET_SSL_CERTIFICATE_E, cert_with_key))
    {
        dconfigPRINTF(("cert load failed\n"));
            xSemaphoreGive(g_tls_semaph);
        xResult = QAPI_ERROR;
        goto ssl_error;
    }
    
    if( NULL != pCtx->pcServerCertificate)
    {
            uint32_t isCAstored = 0;
            int32_t i, numFiles;
             numFiles = qapi_Net_SSL_Cert_List(QAPI_NET_SSL_CA_LIST_E, &cafile_list);
             for (i=0; i<numFiles; i++)
            {
                if( 0 == strcmp(cafile_list.name[i],pCtx->caname))
                {
                    isCAstored = 1;
                    break;
                }
            }
            if(0 == isCAstored)
            {
                /* change PEM format to bin format */
                memset(&cert_info, 0, sizeof(cert_info));
                memset(&ca_info, 0, sizeof(ca_info));
                ca_info.ca_Buf = (uint8_t *)pCtx->pcServerCertificate;
                ca_info.ca_Size = pCtx->ulServerCertificateLength;
                cert_info.cert_Type = QAPI_NET_SSL_PEM_CA_LIST_E;
                cert_info.info.pem_CA_List.ca_Cnt = 1;
                cert_info.info.pem_CA_List.ca_Info[0] = &ca_info;

                status = qapi_Net_SSL_Cert_Store(&cert_info, pCtx->caname);
                if(QAPI_OK != status)
                {
                    dconfigPRINTF(("ssl ca store failed:%d\n",status));
                    xSemaphoreGive(g_tls_semaph);
                    xResult = QAPI_ERROR;
                    goto ssl_error;
                }
            }

            if (QAPI_OK != qapi_Net_SSL_Cert_Load(pCtx->sslCtx, QAPI_NET_SSL_CA_LIST_E, pCtx->caname))
            {
                dconfigPRINTF(("ca load failed\n"));
                xSemaphoreGive(g_tls_semaph);
                xResult = QAPI_ERROR;
                goto ssl_error;
            }
        }
        else
        {
            /*use default calist*/
            if (QAPI_OK != qapi_Net_SSL_Cert_Load(pCtx->sslCtx, QAPI_NET_SSL_CA_LIST_E, defulat_calist))
            {
                dconfigPRINTF(("ca load failed\n"));
                xSemaphoreGive(g_tls_semaph);
                xResult = QAPI_ERROR;
                goto ssl_error;
            }
        }        
        xSemaphoreGive(g_tls_semaph);
    }
    
    pCtx->ssl = qapi_Net_SSL_Con_New(pCtx->sslCtx, QAPI_NET_SSL_TLS_E);
    qapi_Net_SSL_Fd_Set(pCtx->ssl, *((int32_t*)pCtx->pvCallerContext)); //get pvCallerContext->xsocket.

    // configure the SSL connection
    if (pCtx->config_set)
    {
        if (qapi_Net_SSL_Configure(pCtx->ssl, &pCtx->config) < QAPI_OK)
        {
            xResult = QAPI_ERROR;
            goto ssl_error;
        }
    }
    status = qapi_Net_SSL_Connect(pCtx->ssl);
    if (status != QAPI_SSL_OK_HS)
    {
        dconfigPRINTF(("ssl connect failed:%d,pCtx->ssl:%d\n",status,pCtx->ssl));
        xResult = QAPI_ERROR;
        if (status == QAPI_ERR_SSL_CERT_CN)
            {
                /** The peer's SSL certificate is trusted, CN matches the host name, time is expired */
                dconfigPRINTF(("ERROR: The certificate is expired\n"));
            }
            else if (status == QAPI_ERR_SSL_CERT_TIME)
            {
                /** The peer's SSL certificate is trusted, CN does NOT match the host name, time is valid */
                dconfigPRINTF(("ERROR: The certificate is trusted, but the host name is not valid\n"));
            }
            else if (status == QAPI_ERR_SSL_CERT_NONE)
            {
                /** The peer's SSL certificate is trusted, CN does NOT match host name, time is expired */
                dconfigPRINTF(("ERROR: The certificate is expired and the host name is not valid\n"));
            }
            else
            {
                dconfigPRINTF(("ERROR: SSL connect failed\n"));
            }
        
        goto ssl_error;
    }
    return xResult;
    
ssl_error:
    if (pCtx->ssl != QAPI_NET_SSL_INVALID_HANDLE)
    {
        qapi_Net_SSL_Shutdown(pCtx->ssl);
        pCtx->ssl = QAPI_NET_SSL_INVALID_HANDLE;
    }
    return xResult;
}

/*-----------------------------------------------------------*/

BaseType_t TLS_Recv( void * pvContext,
                     unsigned char * pucReadBuffer,
                     size_t xReadLength )
{
    BaseType_t xResult = 0;
    TLSContext_t * pCtx = ( TLSContext_t * ) pvContext; /*lint !e9087 !e9079 Allow casting void* to other types. */
    int32_t xRead = 0;

    if(CFG_PACKET_SIZE_MAX_TX < xReadLength)
    {
        xReadLength = CFG_PACKET_SIZE_MAX_TX;
    }

    if( NULL != pCtx )
    {
            xResult = qapi_Net_SSL_Read(pCtx->ssl,
                                        pucReadBuffer,
                                        xReadLength);
    }

    return xResult;
}

/*-----------------------------------------------------------*/

BaseType_t TLS_Send( void * pvContext,
                     const unsigned char * pucMsg,
                     size_t xMsgLength )
{
    BaseType_t xResult = 0;
    TLSContext_t * pCtx = ( TLSContext_t * ) pvContext; /*lint !e9087 !e9079 Allow casting void* to other types. */
    size_t xWritten = 0;

    if(CFG_PACKET_SIZE_MAX_TX < xMsgLength)
        xMsgLength = CFG_PACKET_SIZE_MAX_TX;

    if( NULL != pCtx )
    {
            xResult = qapi_Net_SSL_Write(pCtx->ssl,
                         pucMsg,
                         xMsgLength);
    }

    return xResult;
}

/*-----------------------------------------------------------*/

void TLS_Cleanup( void * pvContext )
{
    TLSContext_t * pCtx = ( TLSContext_t * ) pvContext; /*lint !e9087 !e9079 Allow casting void* to other types. */

    if( NULL != pCtx )
    {
        if (pCtx->ssl)
        {
            qapi_Net_SSL_Shutdown(pCtx->ssl);
            pCtx->ssl = QAPI_NET_SSL_INVALID_HANDLE;
        }

        if (pCtx->sslCtx)
        {
            qapi_Net_SSL_Obj_Free(pCtx->sslCtx);
            pCtx->sslCtx = QAPI_NET_SSL_INVALID_HANDLE;
        }
    }
    /* Free memory. */
    vPortFree( pCtx );
}
