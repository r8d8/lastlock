/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc. 
 * All Rights Reserved. 
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * $QTI_LICENSE_QDN_C
 *
 * Amazon FreeRTOS SECURE SOCKET for QCOM QCA402X  V1.0.0
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
//#include "FreeRTOS.h"
//#include "FreeRTOSConfig.h"
#include "aws_secure_sockets.h"
#include "aws_tls.h"
#include "task.h"

/* Unity includes. */
#include "unity_internals.h"

/* Third-party  include. */
#include "qapi_socket.h"
#include "aws_wifi.h"
#include "pal.h" 
#include "qurt_timer.h"

/**
* @brief Flag indicating that socket send operations are not permitted.
*
* If a WR shutdown in SOCKETS_Shutdown() is invoked, this flag is
* set in the socket's xShutdownFlags member.
*/
#define securesocketsSOCKET_WRITE_CLOSED_FLAG    ( 1UL << 1 )

/**
* @brief Flag indicating that socket receive operations are not permitted.
*
* If a RD shutdown in SOCKETS_Shutdown() is invoked, this flag is
* set in the socket's xShutdownFlags member.
*/
#define securesocketsSOCKET_READ_CLOSED_FLAG     ( 1UL << 2 )

/**
 * @brief A flag to indicate whether or not the socket is connected.
 *
 */
#define securesocketsSOCKET_IS_CONNECTED                ( 1UL << 3 )

/**
 * @brief A flag to indicate that the socket is non-blocked.
 *
 */
#define securesocketsSOCKET_IS_NONBLOCK                ( 1UL << 4 )

#define IPV4_FRAGMENTATION_THRESHOLD        1576

#define tcpconfigASSERT( x )    if( ( x ) == 0 ) TEST_ABORT()

/* Internal context structure. */
typedef struct SSOCKETContext
{
    Socket_t xSocket;
    char * pcDestination;
    void * pvTLSContext;
    BaseType_t xRequireTLS;
    BaseType_t xSendFlags;
    BaseType_t xRecvFlags;
    BaseType_t xFlags;
    TickType_t ulSendTimeout;
    TickType_t ulRecvTimeout;
    char * pcServerCertificate;
    uint32_t ulServerCertificateLength;
    qapi_fd_set_t rd_set;
} SSOCKETContext_t, * SSOCKETContextPtr_t;

#define A_MEMZERO(obj, size) memset((obj), 0, (size))
/*
 * Helper routines.
 */

/*-----------------------------------------------------------*/

/*
 * Interface routines.
 */
/*-----------------------------------------------------------*/

Socket_t SOCKETS_Socket( int32_t lDomain,
                         int32_t lType,
                         int32_t lProtocol )
{
    int32_t lStatus = SOCKETS_ERROR_NONE;
    int32_t xSocket = 0;
    SSOCKETContextPtr_t pxContext = NULL;
    int32_t retry = 20;

#if 1
    /* Ensure that only supported values are supplied. */
    tcpconfigASSERT( lDomain == SOCKETS_AF_INET );
    tcpconfigASSERT( lType == SOCKETS_SOCK_STREAM );
    tcpconfigASSERT( lProtocol == SOCKETS_IPPROTO_TCP );
#else
    /* Ensure that only supported values are supplied. */
    if((SOCKETS_AF_INET !=  lDomain) || (SOCKETS_SOCK_STREAM != lType) || (SOCKETS_IPPROTO_TCP != lProtocol))
        return SOCKETS_SOCKET_ERROR;
#endif
    /* Allocate the internal context structure. */
    pxContext = pvPortMalloc( sizeof( SSOCKETContext_t ) );

    if( pxContext != NULL )
    {
        memset( pxContext, 0, sizeof( SSOCKETContext_t ) );
        /* Create the wrapped socket. */
        do{
            xSocket = qapi_socket( SOCKETS_AF_INET,
                                   SOCKETS_SOCK_STREAM,
                                   0 ); /*xProtocol*/
            if(xSocket == -1)
                vTaskDelay(pdMS_TO_TICKS(500));
        }while ( retry-- > 0 && xSocket == -1);
        if( xSocket != SOCKETS_SOCKET_ERROR )
        {
            pxContext->xSocket = ( Socket_t ) xSocket;
            /* Set default timeouts. */
            pxContext->ulRecvTimeout = pdMS_TO_TICKS(socketsconfigDEFAULT_RECV_TIMEOUT);
            pxContext->ulSendTimeout = pdMS_TO_TICKS(socketsconfigDEFAULT_SEND_TIMEOUT);

            qapi_fd_zero(&pxContext->rd_set);
        }
        else /* Driver could not allocate socket. */
        {
            lStatus = SOCKETS_SOCKET_ERROR;
            dconfigPRINTF(("Create socket error:%d\n",xSocket));
            vPortFree( pxContext );
        }        
    }
    else /* Malloc failed. */
    {
        lStatus = SOCKETS_ENOMEM;
        dconfigPRINTF(("Create socket out of mem\n"));
    }

    if( lStatus != SOCKETS_ERROR_NONE )
    {
        pxContext = SOCKETS_INVALID_SOCKET;
    }
    return pxContext;
}
/*-----------------------------------------------------------*/
int32_t SOCKETS_Close( Socket_t xSocket )
{
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket;
    int32_t lStatus = SOCKETS_ERROR_NONE;

    if( ( NULL != pxContext ) && ( SOCKETS_INVALID_SOCKET != pxContext ) )
    {
        if( NULL != pxContext->pcDestination )
        {
            vPortFree( pxContext->pcDestination );
        }
        if( NULL != pxContext->pcServerCertificate )
        {
            vPortFree( pxContext->pcServerCertificate );
        }
        if( pdTRUE == pxContext->xRequireTLS )
        {
            TLS_Cleanup( pxContext->pvTLSContext );
        }

        qapi_fd_zero( &pxContext->rd_set);
        lStatus = qapi_socketclose( ( int ) pxContext->xSocket );
        
        pxContext->xFlags = 0;
        vPortFree( pxContext );
    }
    else
    {
        lStatus = SOCKETS_EINVAL;
    }
    //dconfigPRINTF(("after socket close heap:%d\n",xPortGetFreeHeapSize()));
    return lStatus;
}
/*-----------------------------------------------------------*/

int32_t SOCKETS_Connect( Socket_t xSocket,
                         SocketsSockaddr_t * pxAddress,
                         Socklen_t xAddressLength )
{
    int32_t xStatus = SOCKETS_ERROR_NONE;
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket;
    TLSParams_t xTLSParams = { 0 };
    struct sockaddr_in xTempAddress = { 0 };

    if( ( SOCKETS_INVALID_SOCKET != pxContext ) && ( NULL != pxAddress ) )
    {
        /* Connect the wrapped socket. */
        /* The driver code expects the endianess of the address and port in host order */
        xTempAddress.sin_addr.s_addr = pxAddress->ulAddress;
        xTempAddress.sin_family = pxAddress->ucSocketDomain;
        xTempAddress.sin_port = pxAddress->usPort;

        //dconfigPRINTF(("s_addr:%08x,port:%d,socket:%x\n",xTempAddress.sin_addr.s_addr,xTempAddress.sin_port,pxContext->xSocket));

        xStatus = qapi_connect( ( int ) pxContext->xSocket,
                                (struct sockaddr*)&xTempAddress,
                                sizeof(struct sockaddr_in) );
        /* Negotiate TLS if requested. */
        if( SOCKETS_ERROR_NONE == xStatus )
        {
            
            if( pdTRUE == pxContext->xRequireTLS )
            {
                xTLSParams.ulSize = sizeof( xTLSParams );
                xTLSParams.pcDestination = pxContext->pcDestination;
                xTLSParams.pcServerCertificate = pxContext->pcServerCertificate;
                xTLSParams.ulServerCertificateLength = pxContext->ulServerCertificateLength;
                xTLSParams.pvCallerContext = pxContext;
                xTLSParams.pxNetworkRecv = NULL;
                xTLSParams.pxNetworkSend = NULL;

                xStatus = TLS_Init( &pxContext->pvTLSContext, &xTLSParams );

                if( SOCKETS_ERROR_NONE == xStatus )
                {
                    xStatus = TLS_Connect( pxContext->pvTLSContext );
                }
            }
            
            if( SOCKETS_ERROR_NONE == xStatus )
            {
                pxContext->xFlags |= securesocketsSOCKET_IS_CONNECTED;
                xStatus = qapi_fd_set(pxContext->xSocket, &pxContext->rd_set);
            }
        }
    }
    else
    {
        xStatus = SOCKETS_SOCKET_ERROR;
    }

    if(xStatus != SOCKETS_ERROR_NONE )
        dconfigPRINTF(("connect:SOCKETS_SOCKET_ERROR\n"));
    return xStatus;
}
/*-----------------------------------------------------------*/


/* Convert IP address in uint32_t to comma separated bytes. */
#define UINT32_IPADDR_TO_CSV_BYTES( a )                     \
    ( ( a ) & 0xFF ), ( ( ( a ) >> 8 ) & 0xFF ), \
   ( ( ( a ) >> 16 ) & 0xFF ), ( ( ( a ) >> 24 ) & 0xFF )

/*-----------------------------------------------------------*/

uint32_t SOCKETS_GetHostByName( const char * pcHostName )
{
    uint32_t ulAddr = 0;

    if( strlen( pcHostName ) <= ( size_t ) securesocketsMAX_DNS_NAME_LENGTH )
    {
        WIFI_GetHostIP( ( char * ) pcHostName, ( uint8_t * ) &ulAddr );
        dconfigPRINTF( ( "Looked up %s as %d.%d.%d.%d\r\n",
                        pcHostName,
                        UINT32_IPADDR_TO_CSV_BYTES( ulAddr ) ) );
    }
    else
    {
        dconfigPRINTF( ( "Malformed URL, Host name: %s is too long.", pcHostName ) );
    }

    /* This api is to return the address in network order.  So  mask off this line.*/
    //ulAddr = SOCKETS_htonl( ulAddr );

    return ulAddr;
}

/*-----------------------------------------------------------*/

int32_t SOCKETS_Recv( Socket_t xSocket,
                      void * pvBuffer,
                      size_t xBufferLength,
                      uint32_t ulFlags )
{
    int32_t lStatus = SOCKETS_SOCKET_ERROR;
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket;
    int32_t conn_sock;
    qapi_fd_set_t rd_set = pxContext->rd_set;
    uint32_t timeout = qurt_timer_convert_ticks_to_time(pxContext->ulRecvTimeout, QURT_TIME_MSEC);
    uint32_t timeout_left = pdMS_TO_TICKS(timeout % 50);
    
    if( ( SOCKETS_INVALID_SOCKET != xSocket ) &&
        ( NULL != pvBuffer ) &&
        ( securesocketsSOCKET_IS_CONNECTED & pxContext->xFlags ) &&
        ( ( securesocketsSOCKET_READ_CLOSED_FLAG & pxContext->xFlags ) == 0UL ) )
    {
        rd_set = pxContext->rd_set;
        pxContext->xRecvFlags = ( BaseType_t ) ulFlags; /* but not used now.*/
        if((securesocketsSOCKET_IS_NONBLOCK & pxContext->xFlags) || (timeout < 50))
        {
            timeout = 0;
        }
        conn_sock = qapi_select(&rd_set, NULL, NULL, timeout);
        if(conn_sock > 0 && qapi_fd_isset(pxContext->xSocket, &rd_set))
        {
            if( pdTRUE == pxContext->xRequireTLS )
            {
                /* Receive through TLS pipe, if negotiated. */
                lStatus = TLS_Recv( pxContext->pvTLSContext, pvBuffer, xBufferLength );
            }
            else
            {
                /* Receive unencrypted. */
                lStatus = qapi_recv( pxContext->xSocket, pvBuffer, xBufferLength, 0);
            }
        }
        else
        {
            lStatus = SOCKETS_EWOULDBLOCK;
        }
        
        if(0 == conn_sock && timeout_left)
        {
                TickType_t time_begin = xTaskGetTickCount();
                for( ; ; )
                {
                     conn_sock = qapi_select(&rd_set, NULL, NULL, 0);
                     if(conn_sock > 0 && qapi_fd_isset(pxContext->xSocket, &rd_set))
                     {
                        if( pdTRUE == pxContext->xRequireTLS )
                        {
                            /* Receive through TLS pipe, if negotiated. */
                            lStatus = TLS_Recv( pxContext->pvTLSContext, pvBuffer, xBufferLength );
                        }
                        else
                        {
                            /* Receive unencrypted. */
                            lStatus = qapi_recv( pxContext->xSocket, pvBuffer, xBufferLength, MSG_DONTWAIT);
                        }
                    }
                    if(0 == conn_sock && (xTaskGetTickCount() - time_begin < timeout_left))
                    {
                        vTaskDelay( 1 );
                    }
                    else
                    {
                        lStatus = SOCKETS_EWOULDBLOCK;
                        break;
                    }
                }
        }
    }
    else
    {
        lStatus = SOCKETS_SOCKET_ERROR;
    }

    //configPRINTF(("recv satus:%d,RCVTIMEO:%d,fd_set:%d\n",lStatus,pxContext->ulRecvTimeout,pxContext->rd_set.fd_count));
    return lStatus;
}
/*-----------------------------------------------------------*/

int32_t SOCKETS_Send( Socket_t xSocket,
                      const void * pvBuffer,
                      size_t xDataLength,
                      uint32_t ulFlags )
{
    /* The WiFi module refuses to send data if it exceeds this threshold defined in
     * atheros_stack_offload.h. */
    const uint32_t ulSendMaxLength = IPV4_FRAGMENTATION_THRESHOLD;
    int32_t lWritten = 0, lWrittenPerLoop = 0;
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket;
    uint32_t ulToRemain, ulBufferPos, ulToSend;
    uint8_t retry = 5;

    if( ( SOCKETS_INVALID_SOCKET != pxContext ) &&
        ( NULL != pvBuffer ) &&
        ( securesocketsSOCKET_IS_CONNECTED & pxContext->xFlags ) &&
        ( ( securesocketsSOCKET_WRITE_CLOSED_FLAG & pxContext->xFlags ) == 0UL ) )
    {
        pxContext->xSendFlags = ( BaseType_t ) ulFlags; /* but not used now.*/


        for(
            ulToRemain = xDataLength, ulBufferPos = 0, ulToSend = 0 ;
            ulToRemain ;
            ulBufferPos += ulToSend, ulToRemain -= ulToSend
            )
        {
            ulToSend = ulToRemain > ulSendMaxLength ? ulSendMaxLength : ulToRemain;
            /* Send through TLS pipe, if negotiated. */
            if( pdTRUE == pxContext->xRequireTLS )
                {
                    lWrittenPerLoop = TLS_Send( pxContext->pvTLSContext,
                                    &( ( unsigned char const * ) pvBuffer )[ ulBufferPos ],
                                    ulToSend);
                    qapi_Task_Delay(1000);
                }
            else{
                    lWrittenPerLoop = qapi_send( pxContext->xSocket,
                                  &( ( unsigned char const * ) pvBuffer )[ ulBufferPos ],
                                  ulToSend, 0);
                }

            /* Error code < 0. */
            if( lWrittenPerLoop < 0 )
            {
                int sock_err = 0;
                sock_err = qapi_errno(pxContext->xSocket);
                //dconfigPRINTF(("ret:%d,socket err :%d\n",lWrittenPerLoop,sock_err));
                if(retry--)
                {
                    vTaskDelay( 50 );
                    continue;
                }
                else
                {
                    dconfigPRINTF(("send error!!!\n"));
                }
                /* Set the error code to be returned */
                lWritten = lWrittenPerLoop;
                break;
            }

            /* Number of lWritten bytes. */
            lWritten += lWrittenPerLoop;

            if( lWrittenPerLoop != ulToSend )
            {
                break;
            }
        }         
    }
    else
    {
        lWritten = SOCKETS_SOCKET_ERROR;
    }

    return lWritten;
}
/*-----------------------------------------------------------*/

int32_t SOCKETS_SetSockOpt( Socket_t xSocket,
                            int32_t lLevel,
                            int32_t lOptionName,
                            const void * pvOptionValue,
                            size_t xOptionLength )
{
    int32_t lStatus = SOCKETS_ERROR_NONE;
    uint32_t ulTimeoutInMilliseconds;
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket;

    if( ( NULL != pxContext ) && ( SOCKETS_INVALID_SOCKET != pxContext ) )
    {
        switch( lOptionName )
        {
            case SOCKETS_SO_SERVER_NAME_INDICATION:
                if( 0 == ( pxContext->xFlags & securesocketsSOCKET_IS_CONNECTED ))
                {
                    /* Non-NULL destination string indicates that SNI extension should
                    * be used during TLS negotiation. */
                    if( NULL == ( pxContext->pcDestination =
                              ( char * ) pvPortMalloc( 1 + xOptionLength ) ) )
                    {
                        lStatus = SOCKETS_ENOMEM;
                    }
                    else
                    {
                        memcpy( pxContext->pcDestination, pvOptionValue, xOptionLength );
                        pxContext->pcDestination[ xOptionLength ] = '\0';
                    }
                }
                else
                {
                    lStatus = SOCKETS_SOCKET_ERROR;
                    dconfigPRINTF( ( "ERROR: SNI must be set before connection is established.\r\n" ) );
                }
                break;

            case SOCKETS_SO_TRUSTED_SERVER_CERTIFICATE:
                if( 0 == ( pxContext->xFlags & securesocketsSOCKET_IS_CONNECTED ))
                {
                    /* Non-NULL server certificate field indicates that the default trust
                    * list should not be used. */
                    if( NULL == ( pxContext->pcServerCertificate =
                                    ( char * ) pvPortMalloc( xOptionLength ) ) )
                    {
                        lStatus = SOCKETS_ENOMEM;
                    }
                    else
                    {
                        memcpy( pxContext->pcServerCertificate, pvOptionValue, xOptionLength );
                        pxContext->ulServerCertificateLength = xOptionLength;
                    }
                }
                else
                {
                    lStatus = SOCKETS_SOCKET_ERROR;
                    dconfigPRINTF( ( "ERROR: Certificate must be set before connection is established.\r\n" ) );
                }
                break;

            case SOCKETS_SO_REQUIRE_TLS:
                if( 0 == ( pxContext->xFlags & securesocketsSOCKET_IS_CONNECTED ))
                    pxContext->xRequireTLS = pdTRUE;
                else
                    lStatus = SOCKETS_SOCKET_ERROR;
                break;

            case SOCKETS_SO_NONBLOCK:
                if( securesocketsSOCKET_IS_CONNECTED & pxContext->xFlags )
                {
                    pxContext->xFlags |= securesocketsSOCKET_IS_NONBLOCK;
                }
                else
                {
                    lStatus = SOCKETS_SOCKET_ERROR;
                }
                break;
            case SOCKETS_SO_RCVTIMEO:
                ulTimeoutInMilliseconds = *( ( const uint32_t * ) pvOptionValue ); 
                if( 0 == ulTimeoutInMilliseconds)
                    ulTimeoutInMilliseconds = pdMS_TO_TICKS(QAPI_NET_WAIT_FOREVER);
                pxContext->xFlags &= ~securesocketsSOCKET_IS_NONBLOCK;                
                pxContext->ulRecvTimeout = ulTimeoutInMilliseconds;               
                break;
            case SOCKETS_SO_SNDTIMEO:
                 /* Read the passed value. */
                ulTimeoutInMilliseconds = *( ( const uint32_t * ) pvOptionValue ); /*lint !e9079 !e9087 uint32_t type is expected. This function will hard-fault if the wrong type is passed. */
                if( 0 == ulTimeoutInMilliseconds)
                    ulTimeoutInMilliseconds = pdMS_TO_TICKS(QAPI_NET_WAIT_FOREVER);
                pxContext->xFlags &= ~securesocketsSOCKET_IS_NONBLOCK;
                pxContext->ulSendTimeout = ulTimeoutInMilliseconds;
                break;

            default:
                /* Invalid option. */
                dconfigPRINTF(("Unsupport sockopt.\n"));
                lStatus = SOCKETS_EINVAL;
        }
    }
    else
    {
        lStatus = SOCKETS_SOCKET_ERROR;
    }

    return lStatus;
}
/*-----------------------------------------------------------*/

int32_t SOCKETS_Shutdown( Socket_t xSocket,
                          uint32_t ulHow )
{
    SSOCKETContextPtr_t pxSecureSocket = ( SSOCKETContextPtr_t) xSocket;
    int32_t lRetVal = SOCKETS_EINVAL;

    /* Ensure that a valid socket was passed. */
    if( ( SOCKETS_INVALID_SOCKET != pxSecureSocket ) )
    {
        switch( ulHow )
        {
            case SOCKETS_SHUT_RD:
                /* Further receive calls on this socket should return error. */
                pxSecureSocket->xFlags |= securesocketsSOCKET_READ_CLOSED_FLAG;

                /* Return success to the user. */
                lRetVal = SOCKETS_ERROR_NONE;
                break;

            case SOCKETS_SHUT_WR:
                /* Further send calls on this socket should return error. */
                pxSecureSocket->xFlags |= securesocketsSOCKET_WRITE_CLOSED_FLAG;

                /* Return success to the user. */
                lRetVal = SOCKETS_ERROR_NONE;
                break;

            case SOCKETS_SHUT_RDWR:
                /* Further send or receive calls on this socket should return error. */
                pxSecureSocket->xFlags |= securesocketsSOCKET_READ_CLOSED_FLAG;
                pxSecureSocket->xFlags |= securesocketsSOCKET_WRITE_CLOSED_FLAG;

                /* Return success to the user. */
                lRetVal = SOCKETS_ERROR_NONE;
                break;

            default:
                /* An invalid value was passed for ulHow. */
                lRetVal = SOCKETS_EINVAL;
                break;
        }
    }
    return lRetVal;
}
/*-----------------------------------------------------------*/
extern BaseType_t TLS_Sys_Init();
BaseType_t SOCKETS_Init( void )
{
     BaseType_t xResult = pdPASS;
    xResult = TLS_Sys_Init();
    /* Empty initialization for qcom chip. */
    return xResult;
}
