/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc. 
 * All Rights Reserved. 
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * $QTI_LICENSE_QDN_C
 *
 * Amazon FreeRTOS QCOM-based PKCS#11 V1.0.0
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


/**
 * @file pkcs11.c
 * @brief This file deviates from the FreeRTOS style standard for some function names and
 * data types in order to maintain compliance with the PKCS#11 standard.
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "FreeRTOSIPConfig.h"
#include "aws_pkcs11_config.h"
#include "task.h"
#include "aws_crypto.h"
#include "aws_pkcs11.h"

#include "aws_clientcredential.h"

/* C runtime includes. */
#include <stdio.h>
#include <string.h>

#include "qapi_crypto.h"

#define pkcs11NO_OPERATION    ( ( CK_MECHANISM_TYPE ) 0xFFFFFFFFF )


/**
 * @brief Session structure.
 */
typedef struct P11Session
{
    CK_ULONG ulState;
    CK_BBOOL xOpened;
    CK_MECHANISM_TYPE xOperationInProgress;
    CK_BBOOL xFindObjectInit;
    CK_BBOOL xFindObjectComplete;
    CK_OBJECT_CLASS xFindObjectClass;

    /* For QCOM*/
    CK_KEY_TYPE xKeyType;
    qapi_Crypto_Obj_Hdl_t xTmpPublicKeyObj;
    qapi_Crypto_Obj_Hdl_t xPersistentPublicKeyObjHdl;
    qapi_Crypto_Obj_Hdl_t xPersistentPrivateKeyObjHdl;
    CK_OBJECT_HANDLE xVerifyKey;
    uint8_t * pucCertData;
    uint32_t ulCerDataLength;
    BaseType_t xFreeCert;
    uint8_t * pucKeyData;
    uint32_t ulKeyDataLength;
    BaseType_t xFreeKey;
    qapi_Crypto_Op_Hdl_t xDigestOpHdl;
} P11Session_t, * P11SessionPtr_t;

/**
 * @brief Cryptoki module attribute definitions.
 */
#define pkcs11SLOT_ID                      1
#define pkcs11OBJECT_HANDLE_PUBLIC_KEY     1
#define pkcs11OBJECT_HANDLE_PRIVATE_KEY    2
#define pkcs11OBJECT_HANDLE_CERTIFICATE    3

#define pkcs11SUPPORTED_KEY_BITS           2048


/**
 * @brief Helper definitions.
 */
#define pkcs11CREATE_OBJECT_MIN_ATTRIBUTE_COUNT                  3
#define pkcs11CERTIFICATE_ATTRIBUTE_COUNT                        3
#define pkcs11PUBLIC_KEY_ATTRIBUTE_COUNT                         3
#define pkcs11PRIVATE_KEY_ATTRIBUTE_COUNT                        4

#define pkcs11CREATE_OBJECT_CLASS_ATTRIBUTE_INDEX                0
#define pkcs11CREATE_OBJECT_CERTIFICATE_VALUE_ATTRIBUTE_INDEX    1
#define pkcs11CREATE_OBJECT_PRIVATE_KEY_TYPE_INDEX    1
#define pkcs11CREATE_OBJECT_PUBLIC_KEY_TYPE_INDEX    1
#define pkcs11CREATE_OBJECT_CERTIFICATE_TYPE_ATTRIBUTE_INDEX     2
#define pkcs11CREATE_OBJECT_PUBLIC_KEY_VALUE_ATTRIBUTE_INDEX     2
#define pkcs11CREATE_OBJECT_PRIVATE_KEY_VALUE_ATTRIBUTE_INDEX    3

#define pkcs11GENERATE_KEY_PAIR_KEYTYPE_ATTRIBUTE_INDEX          0
#define pkcs11GENERATE_KEY_PAIR_ECPARAMS_ATTRIBUTE_INDEX         1

/**
 * @brief Write file to filesystem (see PAL).
 */
extern BaseType_t PKCS11_PAL_SaveFile( char * pcFileName,
                                       uint8_t * pucData,
                                       uint32_t ulDataSize );

/**
 * @brief Read file from filesystem (see PAL).
 */
extern BaseType_t PKCS11_PAL_ReadFile( char * pcFileName,
                                       uint8_t ** ppucData,
                                       uint32_t * pulDataSize );

/**
 * @brief Free the buffer allocated in PKCS11_PAL_ReadFile (see PAL).
 */
extern void PKCS11_PAL_ReleaseFileData( uint8_t * pucBuffer,
                                        uint32_t ulBufferSize );
/*-----------------------------------------------------------*/

/**
 * @brief Maps an opaque caller session handle into its internal state structure.
 */
P11SessionPtr_t prvSessionPointerFromHandle( CK_SESSION_HANDLE xSession )
{
    return ( P11SessionPtr_t ) xSession; /*lint !e923 Allow casting integer type to pointer for handle. */
}
/*-----------------------------------------------------------*/
/**
 * @brief Parse the public key from certificate or publickey pem file.
 */
static int prvParsePubKeyFromPem(CK_KEY_TYPE CK_PTR CK_Type,
		const char *pem,
		const char* pass_Phrase,
		qapi_Crypto_Obj_Hdl_t *hdl)
{
    qapi_Status_t status = QAPI_OK;

    *CK_Type = CKK_RSA;
     status = qapi_Crypto_Transient_Obj_Import_From_Pem(
                QAPI_CRYPTO_OBJ_TYPE_RSA_PUBLIC_KEY_E,
                pem, 
                NULL, 
                hdl);

    if( QAPI_OK != status )
    {
        *CK_Type = CKK_ECDSA;
        status = qapi_Crypto_Transient_Obj_Import_From_Pem(
                QAPI_CRYPTO_OBJ_TYPE_ECDSA_PUBLIC_KEY_E,
                pem, 
                NULL, 
                hdl);
    }

    return status;
}
/*-----------------------------------------------------------*/
/**
 * @brief Load the default key and certificate from storage.
 */
static CK_RV prvLoadAndInitializeDefaultCertificateAndKey( P11SessionPtr_t pxSession )
{
    CK_RV xResult = 0;
    uint8_t * pucCertificateData = NULL;
    uint32_t ulCertificateDataLength = 0;
    BaseType_t xFreeCertificate = pdFALSE;
    uint8_t * pucKeyData = NULL;
    uint32_t ulKeyDataLength = 0;
    BaseType_t xFreeKey = pdFALSE;
    qapi_Status_t status = QAPI_OK;
    
    if(NULL == pxSession)
        return pdFALSE;
    /* Read the certificate from storage. */
    if( pdFALSE == PKCS11_PAL_ReadFile( pkcs11configFILE_NAME_CLIENT_CERTIFICATE,
                                        &pxSession->pucCertData,
                                        &pxSession->ulCerDataLength) )
    {
        configPRINTF(("use default cert\n"));
        pucCertificateData = ( uint8_t * ) clientcredentialCLIENT_CERTIFICATE_PEM;
        ulCertificateDataLength = clientcredentialCLIENT_CERTIFICATE_LENGTH;
    }
    else
    {
        pxSession->xFreeCert = pdTRUE;
    }

    /* Read the private key from storage. */
    if( pdFALSE == PKCS11_PAL_ReadFile( pkcs11configFILE_NAME_KEY,
                                        &pxSession->pucKeyData,
                                        &pxSession->ulKeyDataLength) )
    {
        configPRINTF(("use default key\n"));
        pucKeyData = ( uint8_t * ) clientcredentialCLIENT_PRIVATE_KEY_PEM;
        ulKeyDataLength = clientcredentialCLIENT_PRIVATE_KEY_LENGTH;
    }
    else
    {
        pxSession->xFreeKey = pdTRUE;
    }

    /*--------------parse cert file-----------------*/
    /*try RSA*/
    status = prvParsePubKeyFromPem(
                &pxSession->xKeyType,
                pxSession->pucCertData,
                NULL,
                &pxSession->xPersistentPublicKeyObjHdl);
    if( QAPI_OK != status )
    {
        configPRINTF(("parse cert failed\n"));
        xResult = CKR_ARGUMENTS_BAD;
        goto cert_clean_up;
    }

    /*--------------private key--------------*/
    if(CKK_RSA == pxSession->xKeyType)
    {
         status = qapi_Crypto_Transient_Obj_Import_From_Pem(
                QAPI_CRYPTO_OBJ_TYPE_RSA_KEYPAIR_E,
               pxSession->pucKeyData,
                NULL,
                &pxSession->xPersistentPrivateKeyObjHdl);
         if(QAPI_OK != status)
        {
            //qapi_Crypto_Transient_Obj_Free(pxSession->xPersistentPublicKeyObjHdl);
            configPRINTF(("parse key failed\n"));
            xResult = CKR_ARGUMENTS_BAD;
            goto cert_clean_up;
        }                        
    }
    else if(CKK_ECDSA == pxSession->xKeyType)
    {
         status = qapi_Crypto_Transient_Obj_Import_From_Pem(
                QAPI_CRYPTO_OBJ_TYPE_ECDSA_KEYPAIR_E,
                pxSession->pucKeyData,
                NULL,
                &pxSession->xPersistentPrivateKeyObjHdl);
         if(QAPI_OK != status)
        {
            //qapi_Crypto_Transient_Obj_Free(pxSession->xPersistentPublicKeyObjHdl);
            xResult = CKR_ARGUMENTS_BAD;
            goto cert_clean_up;
        }                        
    }
    else
    {
            xResult = CKR_ARGUMENTS_BAD;
            configPRINTF(("Unkown key type\n"));
            goto cert_clean_up;
    }

    return xResult;
cert_clean_up:

     /* Clean-up. */
    if( ( NULL != pucCertificateData ) && ( pdTRUE == xFreeCertificate ) )
    {
        PKCS11_PAL_ReleaseFileData( pucCertificateData, ulCertificateDataLength );
    }

    if( ( NULL != pucKeyData ) && ( pdTRUE == xFreeKey ) )
    {
        PKCS11_PAL_ReleaseFileData( pucKeyData, ulKeyDataLength );
    }

    return xResult;
}

/*-----------------------------------------------------------*/
/*
 * PKCS#11 module implementation.
 */

/**
 * @brief PKCS#11 interface functions implemented by this Cryptoki module.
 */
static CK_FUNCTION_LIST prvP11FunctionList =
{
    { CRYPTOKI_VERSION_MAJOR, CRYPTOKI_VERSION_MINOR },
    C_Initialize,
    C_Finalize,
    NULL, /*C_GetInfo */
    C_GetFunctionList,
    C_GetSlotList,
    NULL, /*C_GetSlotInfo*/
    NULL, /*C_GetTokenInfo*/
    NULL, /*C_GetMechanismList*/
    NULL, /*C_GetMechansimInfo */
    NULL, /*C_InitToken*/
    NULL, /*C_InitPIN*/
    NULL, /*C_SetPIN*/
    C_OpenSession,
    C_CloseSession,
    NULL, /*C_CloseAllSessions*/
    NULL, /*C_GetSessionInfo*/
    NULL, /*C_GetOperationState*/
    NULL, /*C_SetOperationState*/
    NULL, /*C_Login*/
    NULL, /*C_Logout*/
    C_CreateObject,
    NULL, /*C_CopyObject*/
    C_DestroyObject,
    NULL, /*C_GetObjectSize*/
    C_GetAttributeValue,
    NULL, /*C_SetAttributeValue*/
    C_FindObjectsInit,
    C_FindObjects,
    C_FindObjectsFinal,
    NULL, /*C_EncryptInit*/
    NULL, /*C_Encrypt*/
    NULL, /*C_EncryptUpdate*/
    NULL, /*C_EncryptFinal*/
    NULL, /*C_DecryptInit*/
    NULL, /*C_Decrypt*/
    NULL, /*C_DecryptUpdate*/
    NULL, /*C_DecryptFinal*/
    C_DigestInit,//C_DigestInit,
    NULL, /*C_Digest*/
    C_DigestUpdate,//C_DigestUpdate,
    NULL, /* C_DigestKey*/
    C_DigestFinal,//C_DigestFinal,
    C_SignInit,
    C_Sign,
    NULL, /*C_SignUpdate*/
    NULL, /*C_SignFinal*/
    NULL, /*C_SignRecoverInit*/
    NULL, /*C_SignRecover*/
    C_VerifyInit,
    C_Verify,
    NULL, /*C_VerifyUpdate*/
    NULL, /*C_VerifyFinal*/
    NULL, /*C_VerifyRecoverInit*/
    NULL, /*C_VerifyRecover*/
    NULL, /*C_DigestEncryptUpdate*/
    NULL, /*C_DecryptDigestUpdate*/
    NULL, /*C_SignEncryptUpdate*/
    NULL, /*C_DecryptVerifyUpdate*/
    NULL, /*C_GenerateKey*/
    NULL,//C_GenerateKeyPair,
    NULL, /*C_WrapKey*/
    NULL, /*C_UnwrapKey*/
    NULL, /*C_DeriveKey*/
    NULL, /*C_SeedRandom*/
    C_GenerateRandom,
    NULL, /*C_GetFunctionStatus*/
    NULL, /*C_CancelFunction*/
    NULL  /*C_WaitForSlotEvent*/
};

/**
 * @brief Initialize the Cryptoki module for use.
 */
#if !defined( pkcs11configC_INITIALIZE_ALT )
    CK_DEFINE_FUNCTION( CK_RV, C_Initialize )( CK_VOID_PTR pvInitArgs )
    { /*lint !e9072 It's OK to have different parameter name. */
        ( void ) ( pvInitArgs );

        /* Ensure that the FreeRTOS heap is used. */
        CRYPTO_ConfigureHeap();

        return CKR_OK;
    }
#endif

/**
 * @brief Un-initialize the Cryptoki module.
 */
CK_DEFINE_FUNCTION( CK_RV, C_Finalize )( CK_VOID_PTR pvReserved )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;

    if( NULL != pvReserved )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }

    return xResult;
}

/**
 * @brief Query the list of interface function pointers.
 */
CK_DEFINE_FUNCTION( CK_RV, C_GetFunctionList )( CK_FUNCTION_LIST_PTR_PTR ppxFunctionList )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;

    if( NULL == ppxFunctionList )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }
    else
    {
        *ppxFunctionList = &prvP11FunctionList;
    }

    return xResult;
}

/**
 * @brief Query the list of slots. A single default slot is implemented.
 */
CK_DEFINE_FUNCTION( CK_RV, C_GetSlotList )( CK_BBOOL xTokenPresent,
                                            CK_SLOT_ID_PTR pxSlotList,
                                            CK_ULONG_PTR pulCount )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;

    ( void ) ( xTokenPresent );

    if( NULL == pulCount )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }
    else if( NULL == pxSlotList )
    {
        *pulCount = 1;
    }
    else
    {
        if( 0u == *pulCount )
        {
            xResult = CKR_BUFFER_TOO_SMALL;
        }
        else
        {
            pxSlotList[ 0 ] = pkcs11SLOT_ID;
            *pulCount = 1;
        }
    }

    return xResult;
}

/**
 * @brief Start a session for a cryptographic command sequence.
 */
CK_DEFINE_FUNCTION( CK_RV, C_OpenSession )( CK_SLOT_ID xSlotID,
                                            CK_FLAGS xFlags,
                                            CK_VOID_PTR pvApplication,
                                            CK_NOTIFY xNotify,
                                            CK_SESSION_HANDLE_PTR pxSession )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSessionObj = NULL;

    ( void ) ( xSlotID );
    ( void ) ( pvApplication );
    ( void ) ( xNotify );

    /* Check arguments. */
    if( NULL == pxSession )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }
#if 0
    /* For legacy reasons, the CKF_SERIAL_SESSION bit MUST always be set. */
    if( CKR_OK == xResult && 0 == ( CKF_SERIAL_SESSION & xFlags ) )
    {
        xResult = CKR_SESSION_PARALLEL_NOT_SUPPORTED;
    }
#endif
    /*
     * Make space for the context.
     */
    if( CKR_OK == xResult )
    {
        pxSessionObj = ( P11SessionPtr_t ) pvPortMalloc( sizeof( P11Session_t ) ); /*lint !e9087 Allow casting void* to other types. */

        if( NULL == pxSessionObj )
        {
            xResult = CKR_HOST_MEMORY;
        }
    }

    /*
     * Initialize RNG.
     */
/////////////////

    if( CKR_OK == xResult )
    {
        memset( pxSessionObj, 0, sizeof( P11Session_t ) );
    }

////////////////

    if( CKR_OK == xResult )
    {
        /*
         * Assign the session.
         */

        pxSessionObj->ulState =
            0u != ( xFlags & CKF_RW_SESSION ) ? CKS_RW_PUBLIC_SESSION : CKS_RO_PUBLIC_SESSION;
        pxSessionObj->xOpened = CK_TRUE;

        /*
         * Return the session.
         */

        *pxSession = ( CK_SESSION_HANDLE ) pxSessionObj; /*lint !e923 Allow casting pointer to integer type for handle. */
    }

    /*
     *   Initialize the operation in progress.
     */
    if( CKR_OK == xResult )
    {
        pxSessionObj->xOperationInProgress = pkcs11NO_OPERATION;
    }

    if( ( NULL != pxSessionObj ) && ( CKR_OK != xResult ) )
    {
        vPortFree( pxSessionObj );
    }

    return xResult;
}

/**
 * @brief Terminate a session and release resources.
 */
CK_DEFINE_FUNCTION( CK_RV, C_CloseSession )( CK_SESSION_HANDLE xSession )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );

    if( NULL != pxSession )
    {
        /*
         * Tear down the session.
         */

        if( NULL != pxSession->xTmpPublicKeyObj)
        {
            qapi_Crypto_Transient_Obj_Free(pxSession->xTmpPublicKeyObj);
        }

        /* Free the public key context if it exists. */
        if( NULL != pxSession->xPersistentPrivateKeyObjHdl)
        {
            qapi_Crypto_Transient_Obj_Free(pxSession->xPersistentPrivateKeyObjHdl);
        }

        if( NULL != pxSession->xPersistentPublicKeyObjHdl)
        {
            qapi_Crypto_Transient_Obj_Free(pxSession->xPersistentPublicKeyObjHdl);
        }

        if( pdTRUE == pxSession->xFreeCert  && NULL != pxSession->pucCertData)
        {
            free(pxSession->pucCertData);
        }

        if( pdTRUE == pxSession->xFreeKey && NULL != pxSession->pucKeyData)
        {
            free(pxSession->pucKeyData);
        }

        vPortFree( pxSession );
    }
    else
    {
        xResult = CKR_SESSION_HANDLE_INVALID;
    }

    return xResult;
}

/**
 * @brief Provides import and storage of a single client certificate and
 * associated private key.
 */
CK_DEFINE_FUNCTION( CK_RV, C_CreateObject )( CK_SESSION_HANDLE xSession,
                                             CK_ATTRIBUTE_PTR pxTemplate,
                                             CK_ULONG ulCount,
                                             CK_OBJECT_HANDLE_PTR pxObject )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );
    void * pvContext = NULL;
    int32_t lMbedTLSParseResult = ~0;
    qapi_Crypto_Obj_Hdl_t transient_obj_hdl = 0;
    qapi_Crypto_Obj_Hdl_t persistent_obj_hdl = 0;
    qapi_Status_t status;
    uint32_t obj_type;
    CK_KEY_TYPE xKeyType;
    /*
     * Check parameters.
     */
    if( ( pkcs11CREATE_OBJECT_MIN_ATTRIBUTE_COUNT > ulCount ) ||
        ( NULL == pxTemplate ) ||
        ( NULL == pxObject ) )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }

    if( CKR_OK == xResult )
    {
        if( ( CKA_CLASS != pxTemplate[ pkcs11CREATE_OBJECT_CLASS_ATTRIBUTE_INDEX ].type ) ||
            ( sizeof( CK_OBJECT_CLASS ) != pxTemplate[ pkcs11CREATE_OBJECT_CLASS_ATTRIBUTE_INDEX ].ulValueLen ) )
        {
            xResult = CKR_ARGUMENTS_BAD;
        }
    }

    /*
     * Handle the object by class.
     */

    if( CKR_OK == xResult )
    {
        switch( *( ( uint32_t * ) pxTemplate[ pkcs11CREATE_OBJECT_CLASS_ATTRIBUTE_INDEX ].pValue ) )
        {
            case CKO_CERTIFICATE:

                /* Validate the attribute count for this object class. */
                if( pkcs11CERTIFICATE_ATTRIBUTE_COUNT != ulCount )
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }

                /* Validate the next attribute type. */
                if( CKA_VALUE != pxTemplate[ pkcs11CREATE_OBJECT_CERTIFICATE_VALUE_ATTRIBUTE_INDEX ].type )
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }

                /*try to parse the pem*/
                 status = prvParsePubKeyFromPem(
                            &xKeyType,
                            pxTemplate[ pkcs11CREATE_OBJECT_CERTIFICATE_VALUE_ATTRIBUTE_INDEX ].pValue, 
                            NULL, 
                            &transient_obj_hdl);
                if( QAPI_OK != status )
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }

                if( *( ( uint32_t * ) pxTemplate[ pkcs11CREATE_OBJECT_CERTIFICATE_TYPE_ATTRIBUTE_INDEX ].pValue )
                    == pkcs11CERTIFICATE_TYPE_USER )
                {
                    qapi_Crypto_Transient_Obj_Free(transient_obj_hdl);
                    /* Write out the client certificate. */
                    if( pdFALSE == PKCS11_PAL_SaveFile( pkcs11configFILE_NAME_CLIENT_CERTIFICATE,
                                                        pxTemplate[ pkcs11CREATE_OBJECT_CERTIFICATE_VALUE_ATTRIBUTE_INDEX ].pValue,
                                                        pxTemplate[ pkcs11CREATE_OBJECT_CERTIFICATE_VALUE_ATTRIBUTE_INDEX ].ulValueLen ) )
                    {
                        xResult = CKR_DEVICE_ERROR;
                        break;
                    }
                    else
                    {
                        /* If successful, set object handle to certificate. */
                        *pxObject = pkcs11OBJECT_HANDLE_CERTIFICATE;
                    }
                }
                else if( *( ( uint32_t * ) pxTemplate[ pkcs11CREATE_OBJECT_CERTIFICATE_TYPE_ATTRIBUTE_INDEX ].pValue )
                         == pkcs11CERTIFICATE_TYPE_ROOT )
                {
                    /* Ignore writing the default root certificate. */
                    qapi_Crypto_Transient_Obj_Free(transient_obj_hdl);
                }

                break;

            case CKO_PUBLIC_KEY:

                /* Validate the attribute count for this object class. */
                if( pkcs11PUBLIC_KEY_ATTRIBUTE_COUNT != ulCount )
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }

                /* Validate the next attribute type. */
                if( CKA_VALUE != pxTemplate[ pkcs11CREATE_OBJECT_PUBLIC_KEY_VALUE_ATTRIBUTE_INDEX ].type )
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }

                if(NULL == pxSession)
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }

                /*Follow Amazon pkcs code,public key is saved in session*/
                if(NULL != pxSession->xTmpPublicKeyObj)
                {
                    qapi_Crypto_Transient_Obj_Free(pxSession->xTmpPublicKeyObj);
                }

                 /*try to parse the pem*/
                 status = prvParsePubKeyFromPem(
                            &xKeyType,
                            pxTemplate[ pkcs11CREATE_OBJECT_PUBLIC_KEY_VALUE_ATTRIBUTE_INDEX ].pValue, 
                            NULL, 
                            &pxSession->xTmpPublicKeyObj);
                if( QAPI_OK != status )
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }
               
                /* If successful, set object handle to public key. */
                //pxSession->xPersistentPublicKeyObjHdl = pxSession->xTmpPublicKeyObj;
                *pxObject = pkcs11OBJECT_HANDLE_PUBLIC_KEY;
           
                break;

            case CKO_PRIVATE_KEY:

                /* Validate the attribute count for this object class. */
                if( pkcs11PRIVATE_KEY_ATTRIBUTE_COUNT != ulCount )
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }
                
                /* Find the key type. */
                if( CKA_KEY_TYPE != pxTemplate[ pkcs11CREATE_OBJECT_PRIVATE_KEY_TYPE_INDEX ].type )
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }
                //pxSession maybe NULL.
                //pxSession->xPrivateKeyType = pxTemplate[ pkcs11CREATE_OBJECT_PRIVATE_KEY_TYPE_INDEX ].pValue,
                
                /* Find the key bytes. */
                if( CKA_VALUE != pxTemplate[ pkcs11CREATE_OBJECT_PRIVATE_KEY_VALUE_ATTRIBUTE_INDEX ].type )
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }

                if(CKK_RSA == *( ( uint32_t * ) pxTemplate[ pkcs11CREATE_OBJECT_PRIVATE_KEY_TYPE_INDEX ].pValue))
                {
                     status = qapi_Crypto_Transient_Obj_Import_From_Pem(
                            QAPI_CRYPTO_OBJ_TYPE_RSA_KEYPAIR_E,
                            pxTemplate[ pkcs11CREATE_OBJECT_PRIVATE_KEY_VALUE_ATTRIBUTE_INDEX ].pValue, 
                            NULL,
                            &transient_obj_hdl);
                     if(QAPI_OK != status)
                    {
                        xResult = CKR_ARGUMENTS_BAD;
                        break;
                    }
                }
                else if(CKK_ECDSA== *( ( uint32_t * ) pxTemplate[ pkcs11CREATE_OBJECT_PRIVATE_KEY_TYPE_INDEX ].pValue))
                {
                     status = qapi_Crypto_Transient_Obj_Import_From_Pem(
                            QAPI_CRYPTO_OBJ_TYPE_ECDSA_KEYPAIR_E,
                            pxTemplate[ pkcs11CREATE_OBJECT_PRIVATE_KEY_VALUE_ATTRIBUTE_INDEX ].pValue, 
                            NULL, 
                            &transient_obj_hdl);
                     if(QAPI_OK != status)
                    {
                        xResult = CKR_ARGUMENTS_BAD;
                        break;
                    }
                }
                else
                {
                    xResult = CKR_ARGUMENTS_BAD;
                    break;
                }

                /* Write out the key. */
                qapi_Crypto_Transient_Obj_Free(transient_obj_hdl);
                if( pdFALSE == PKCS11_PAL_SaveFile( pkcs11configFILE_NAME_KEY,
                                                    pxTemplate[ pkcs11CREATE_OBJECT_PRIVATE_KEY_VALUE_ATTRIBUTE_INDEX ].pValue,
                                                    pxTemplate[ pkcs11CREATE_OBJECT_PRIVATE_KEY_VALUE_ATTRIBUTE_INDEX ].ulValueLen ) )
                {
                    xResult = CKR_DEVICE_ERROR;
                    break;
                }
                else
                {
                    /* If successful, set object handle to private key. */
                    *pxObject = pkcs11OBJECT_HANDLE_PRIVATE_KEY;
                }
                break;

            default:
                xResult = CKR_ARGUMENTS_BAD;
        }
    }

    return xResult;
}

/**
 * @brief Free resources attached to an object handle.
 */
CK_DEFINE_FUNCTION( CK_RV, C_DestroyObject )( CK_SESSION_HANDLE xSession,
                                              CK_OBJECT_HANDLE xObject )
{   /*lint !e9072 It's OK to have different parameter name. */
#if 0
    if ( pkcs11OBJECT_HANDLE_PRIVATE_KEY != xObject &&
        pkcs11OBJECT_HANDLE_PUBLIC_KEY != xObject &&
        pkcs11OBJECT_HANDLE_CERTIFICATE != xObject )
        configPRINTF(("need to handle it!!!\n"));
#endif
    return CKR_OK;
}

/**
 * @brief Query the value of the specified cryptographic object attribute.
 */
CK_DEFINE_FUNCTION( CK_RV, C_GetAttributeValue )( CK_SESSION_HANDLE xSession,
                                                  CK_OBJECT_HANDLE xObject,
                                                  CK_ATTRIBUTE_PTR pxTemplate,
                                                  CK_ULONG ulCount )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );
    CK_VOID_PTR pvAttr = NULL;
    CK_ULONG ulAttrLength = 0;
    CK_ULONG xP11KeyType, iAttrib, xKeyBitLen;
    qapi_Crypto_Obj_Info_t obj_info;
    qapi_Status_t status;

    status = qapi_Crypto_Obj_Info_Get(pxSession->xPersistentPrivateKeyObjHdl, &obj_info);
    if(status != QAPI_OK) {
    	return pdFALSE;
    }
    
    if( NULL == pxTemplate )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }
    else
    {
        /*
         * Enumerate the requested attributes.
         */

        for( iAttrib = 0; iAttrib < ulCount && CKR_OK == xResult; iAttrib++ )
        {
            /*
             * Get the attribute data and size.
             */

            switch( pxTemplate[ iAttrib ].type )
            {
                case CKA_KEY_TYPE:
                        xP11KeyType = pxSession->xKeyType;

                        //xResult = CKR_ATTRIBUTE_VALUE_INVALID;
                    /*
                     * Map the private key type between APIs.
                     */
                    ulAttrLength = sizeof( xP11KeyType );
                    pvAttr = &xP11KeyType;
                    break;

                case CKA_VALUE:

                    switch( xObject )
                    {
                        case pkcs11OBJECT_HANDLE_CERTIFICATE:
                            pvAttr = ( CK_VOID_PTR ) pxSession->pucCertData; /*lint !e9005 !e9087 Allow casting other types to void*. */
                            ulAttrLength = pxSession->ulCerDataLength;
                            break;

                        case pkcs11OBJECT_HANDLE_PUBLIC_KEY:
                            pvAttr = ( CK_VOID_PTR ) ( &pxSession->xTmpPublicKeyObj);
                            ulAttrLength = sizeof( qapi_Crypto_Obj_Hdl_t );
                            break;

                        default:
                            xResult = CKR_ARGUMENTS_BAD;
                            break;
                    }

                    break;

                case CKA_MODULUS_BITS:
                case CKA_PRIME_BITS:

                    /*
                     * Key strength size query, handled the same for RSA or ECDSA
                     * in this port.
                     */
                    xKeyBitLen = obj_info.key_Size;
                    ulAttrLength = sizeof( xKeyBitLen );
                    pvAttr = &xKeyBitLen;
                    break;

                case CKA_VENDOR_DEFINED:
                    /*do nothing*/
                    break;

                default:
                    xResult = CKR_ATTRIBUTE_TYPE_INVALID;
                    break;
            }

            if( CKR_OK == xResult )
            {
                /*
                 * Copy out the data and size.
                 */

                if( NULL != pxTemplate[ iAttrib ].pValue )
                {
                    if( pxTemplate[ iAttrib ].ulValueLen < ulAttrLength )
                    {
                        xResult = CKR_BUFFER_TOO_SMALL;
                    }
                    else
                    {
                        memcpy( pxTemplate[ iAttrib ].pValue, pvAttr, ulAttrLength );
                    }
                }

                pxTemplate[ iAttrib ].ulValueLen = ulAttrLength;
            }
        }
    }

    return xResult;
}

/**
 * @brief Begin an enumeration sequence for the objects of the specified type.
 */
CK_DEFINE_FUNCTION( CK_RV, C_FindObjectsInit )( CK_SESSION_HANDLE xSession,
                                                CK_ATTRIBUTE_PTR pxTemplate,
                                                CK_ULONG ulCount )
{   /*lint !e9072 It's OK to have different parameter name. */
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );
    CK_RV xResult = CKR_OK;

    ( void ) ( ulCount );

    /*
     * Check parameters.
     */
    if( NULL == pxTemplate )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }
    else
    {
        /*
         * Allow filtering on a single object class attribute.
         */

        pxSession->xFindObjectInit = CK_TRUE;
        pxSession->xFindObjectComplete = CK_FALSE;
        memcpy( &pxSession->xFindObjectClass,
                pxTemplate[ 0 ].pValue,
                sizeof( CK_OBJECT_CLASS ) );
    }

    return xResult;
}

/**
 * @brief Query the objects of the requested type.
 */
CK_DEFINE_FUNCTION( CK_RV, C_FindObjects )( CK_SESSION_HANDLE xSession,
                                            CK_OBJECT_HANDLE_PTR pxObject,
                                            CK_ULONG ulMaxObjectCount,
                                            CK_ULONG_PTR pulObjectCount )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;
    BaseType_t xDone = pdFALSE;
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );

    /*
     * Check parameters.
     */
    if( ( NULL == pxObject ) ||
        ( NULL == pulObjectCount ) )
    {
        xResult = CKR_ARGUMENTS_BAD;
        xDone = pdTRUE;
    }

    if( ( pdFALSE == xDone ) &&
        ( ( CK_BBOOL ) CK_FALSE == pxSession->xFindObjectInit ) )
    {
        xResult = CKR_OPERATION_NOT_INITIALIZED;
        xDone = pdTRUE;
    }

    if( ( pdFALSE == xDone ) && ( 0u == ulMaxObjectCount ) )
    {
        xResult = CKR_ARGUMENTS_BAD;
        xDone = pdTRUE;
    }

    if( ( pdFALSE == xDone ) && ( ( CK_BBOOL ) CK_TRUE == pxSession->xFindObjectComplete ) )
    {
        *pulObjectCount = 0;
        xResult = CKR_OK;
        xDone = pdTRUE;
    }

    /*
     * Load the default private key and certificate.
     */

    if( ( pdFALSE == xDone ) && ( NULL == pxSession->xPersistentPublicKeyObjHdl ) )
    {
        if( CKR_OK != ( xResult = prvLoadAndInitializeDefaultCertificateAndKey( pxSession ) ) )
        {
            xDone = pdTRUE;
        }
    }

    if( pdFALSE == xDone )
    {
        /*
         * Return object handles based on find type.
         */
        switch( pxSession->xFindObjectClass )
        {
            case CKO_PRIVATE_KEY:
                *pxObject = pkcs11OBJECT_HANDLE_PRIVATE_KEY;
                *pulObjectCount = 1;
                break;

            case CKO_PUBLIC_KEY:
                *pxObject = pkcs11OBJECT_HANDLE_PUBLIC_KEY;
                *pulObjectCount = 1;
                break;

            case CKO_CERTIFICATE:
                *pxObject = pkcs11OBJECT_HANDLE_CERTIFICATE;
                *pulObjectCount = 1;
                break;

            default:
                *pxObject = 0;
                *pulObjectCount = 0;
                break;
        }

        pxSession->xFindObjectComplete = CK_TRUE;
    }

    return xResult;
}

/**
 * @brief Terminate object enumeration.
 */
CK_DEFINE_FUNCTION( CK_RV, C_FindObjectsFinal )( CK_SESSION_HANDLE xSession )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );

    /*
     * Check parameters.
     */

    if( ( CK_BBOOL ) CK_FALSE == pxSession->xFindObjectInit )
    {
        xResult = CKR_OPERATION_NOT_INITIALIZED;
    }
    else
    {
        /*
         * Clean-up find objects state.
         */

        pxSession->xFindObjectInit = CK_FALSE;
        pxSession->xFindObjectComplete = CK_FALSE;
        pxSession->xFindObjectClass = 0;
    }

    return xResult;
}

CK_DEFINE_FUNCTION( CK_RV, C_DigestInit )( CK_SESSION_HANDLE xSession,
                                           CK_MECHANISM_PTR pMechanism )
{
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );

    if( pxSession == NULL )
    {
        xResult = CKR_SESSION_HANDLE_INVALID;
    }

    if( pMechanism->mechanism != CKM_SHA256 )
    {
        xResult = CKR_MECHANISM_INVALID;
    }

    /*
     * Initialize the requested hash type
     */
    if( xResult == CKR_OK )
    {
        if (QAPI_OK != qapi_Crypto_Op_Alloc(QAPI_CRYPTO_ALG_SHA256_E, QAPI_CRYPTO_MODE_DIGEST_E, 0, &pxSession->xDigestOpHdl))
        {
            xResult = CKR_FUNCTION_FAILED;
        }
        else
        {
            pxSession->xOperationInProgress = pMechanism->mechanism;
        }
    }

    return xResult;
}

CK_DEFINE_FUNCTION( CK_RV, C_DigestUpdate )( CK_SESSION_HANDLE xSession,
                                             CK_BYTE_PTR pPart,
                                             CK_ULONG ulPartLen )
{
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );
    CK_ULONG ulHashLen = pcks11SHA256_DIGEST_LENGTH; 

    if( pxSession == NULL )
    {
        xResult = CKR_SESSION_HANDLE_INVALID;
    }
    else if( pxSession->xOperationInProgress != CKM_SHA256 )
    {
        xResult = CKR_OPERATION_NOT_INITIALIZED;
    }

    if( xResult == CKR_OK )
    {
        int i;
        if (QAPI_OK != qapi_Crypto_Op_Digest_Update(pxSession->xDigestOpHdl, (void*)pPart, (uint32_t)ulPartLen))
        //memset(pxSession->xDigestValue,0,pcks11SHA256_DIGEST_LENGTH);
        //if (QAPI_OK != qapi_Crypto_Op_Digest_Final(pxSession->xDigestOpHdl, (void*)pPart, (uint32_t)ulPartLen, pxSession->xDigestValue, &ulHashLen)) 
        {
            xResult = CKR_FUNCTION_FAILED;
            configPRINTF(("digest failed\n"));
            pxSession->xOperationInProgress = pkcs11NO_OPERATION;
            qapi_Crypto_Op_Free(pxSession->xDigestOpHdl);
        }
        
    }

    return xResult;
}

CK_DEFINE_FUNCTION( CK_RV, C_DigestFinal )( CK_SESSION_HANDLE xSession,
                                            CK_BYTE_PTR pDigest,
                                            CK_ULONG_PTR pulDigestLen )
{
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );

    if( pxSession == NULL )
    {
        xResult = CKR_SESSION_HANDLE_INVALID;
    }
    else if( pxSession->xOperationInProgress != CKM_SHA256 )
    {
        xResult = CKR_OPERATION_NOT_INITIALIZED;
        pxSession->xOperationInProgress = pkcs11NO_OPERATION;
    }

    if( xResult == CKR_OK )
    {
        if( pDigest == NULL )
        {
            /* Supply the required buffer size. */
            *pulDigestLen = pcks11SHA256_DIGEST_LENGTH;
        }
        else
        {
            if( *pulDigestLen < pcks11SHA256_DIGEST_LENGTH )
            {
                xResult = CKR_BUFFER_TOO_SMALL;
            }
            else
            {
                //memcpy(pDigest,pxSession->xDigestValue,pcks11SHA256_DIGEST_LENGTH);
                if (QAPI_OK != qapi_Crypto_Op_Digest_Final(pxSession->xDigestOpHdl, (void*)NULL, (uint32_t)0, pDigest, pulDigestLen)) 
                 {
                    xResult = CKR_DATA_INVALID;
                }
                
                qapi_Crypto_Op_Free(pxSession->xDigestOpHdl);
                pxSession->xOperationInProgress = pkcs11NO_OPERATION;
            }
        }
    }

    return xResult;
}

/**
 * @brief Begin a digital signature generation session.
 */
CK_DEFINE_FUNCTION( CK_RV, C_SignInit )( CK_SESSION_HANDLE xSession,
                                         CK_MECHANISM_PTR pxMechanism,
                                         CK_OBJECT_HANDLE xKey )
{
    CK_RV xResult = CKR_OK;

    /*lint !e9072 It's OK to have different parameter name. */
    ( void ) ( xSession );
    ( void ) ( xKey );

    if( NULL == pxMechanism )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }
  
    return xResult;
}

/**
 * @brief Digitally sign the indicated cryptographic hash bytes.
 */
CK_DEFINE_FUNCTION( CK_RV, C_Sign )( CK_SESSION_HANDLE xSession,
                                     CK_BYTE_PTR pucData,
                                     CK_ULONG ulDataLen,
                                     CK_BYTE_PTR pucSignature,
                                     CK_ULONG_PTR pulSignatureLen )
{   /*lint !e9072 It's OK to have different parameter name. */
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession = prvSessionPointerFromHandle( xSession );
    qapi_Crypto_Op_Hdl_t sign_hdl;
    uint32_t alg;
    uint32_t max_key_size;
    
    if( NULL == pulSignatureLen )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }

    if( CKR_OK == xResult )
    {
        if( NULL == pucSignature )
        {
            *pulSignatureLen = pkcs11SUPPORTED_KEY_BITS / 8;
        }
        else
        {
            /*
             * Check algorithm support.
             */
            if( CKR_OK == xResult )
            {
                if( ( CK_ULONG ) cryptoSHA256_DIGEST_BYTES != ulDataLen )
                {
                    xResult = CKR_DATA_LEN_RANGE;
                }
            }

            /*
             * Sign the data.
             */
            if( CKR_OK == xResult )
            {
                if(CKK_RSA == pxSession->xKeyType)
                {
                    alg = QAPI_CRYPTO_ALG_RSASSA_PKCS1_V1_5_SHA256_E;
                    max_key_size = 0x800; /* To be consistent with qapi_Crypto_Transient_Obj_Import_From_Pem()*/
                }
                else if(CKK_ECDSA == pxSession->xKeyType)
                {
                    alg = QAPI_CRYPTO_ALG_ECDSA_P256_E;
                    max_key_size = QAPI_CRYPTO_ECC_P256_PRIVATE_KEY_BITS;
                }
                
                /* Allocate sign operation */
                if (QAPI_OK != qapi_Crypto_Op_Alloc(alg, QAPI_CRYPTO_MODE_SIGN_E, max_key_size, 
                            &sign_hdl))
                {
                    configPRINTF(("\nFailed to alloc op\n"));
                    return CKR_FUNCTION_FAILED;
                }

                /* Copy private key from keypair object for sign operation */
                if (QAPI_OK != qapi_Crypto_Op_Key_Set(sign_hdl, pxSession->xPersistentPrivateKeyObjHdl))
                {
                    configPRINTF(("\nFailed to set pvt key\n"));
                    return CKR_FUNCTION_FAILED;
                }
            
                if (QAPI_OK != qapi_Crypto_Op_Sign_Digest(sign_hdl, NULL, 0, pucData, ulDataLen, pucSignature, pulSignatureLen))
                {
                    configPRINTF(("\nFailed to sign\n"));
                    xResult = CKR_FUNCTION_FAILED;
                }
                qapi_Crypto_Op_Free(sign_hdl);
            }
        }
    }

    return xResult;
}

/**
 * @brief Begin a digital signature verification session.
 */
CK_DEFINE_FUNCTION( CK_RV, C_VerifyInit )( CK_SESSION_HANDLE xSession,
                                           CK_MECHANISM_PTR pxMechanism,
                                           CK_OBJECT_HANDLE xKey )
{
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession;
    pxSession = prvSessionPointerFromHandle( xSession ); 
 
    /*lint !e9072 It's OK to have different parameter name. */
    ( void ) ( xSession );
    ( void ) ( xKey );

    if( NULL == pxMechanism )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }

    if(pxSession)
    {
        pxSession->xVerifyKey = xKey;
    }
    return xResult;
}

/**
 * @brief Verify the digital signature of the specified data using the public
 * key attached to this session.
 */
CK_DEFINE_FUNCTION( CK_RV, C_Verify )( CK_SESSION_HANDLE xSession,
                                       CK_BYTE_PTR pucData,
                                       CK_ULONG ulDataLen,
                                       CK_BYTE_PTR pucSignature,
                                       CK_ULONG ulSignatureLen )
{
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSession;
    qapi_Crypto_Op_Hdl_t verify_hdl;
    uint32_t alg;
    uint32_t max_key_size;
    qapi_Crypto_Obj_Hdl_t publickey_obj;
    /*
     * Check parameters.
     */
    if( ( NULL == pucData ) ||
        ( NULL == pucSignature ) )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }
    else
    {
        pxSession = prvSessionPointerFromHandle( xSession ); /*lint !e9072 It's OK to have different parameter name. */
        if(CKK_RSA == pxSession->xKeyType)
        {
            alg = QAPI_CRYPTO_ALG_RSASSA_PKCS1_V1_5_SHA256_E;
            max_key_size = 0x800; /* To be consistent with qapi_Crypto_Transient_Obj_Import_From_Pem()*/
        }
        else if(CKK_ECDSA == pxSession->xKeyType)
        {
            alg = QAPI_CRYPTO_ALG_ECDSA_P256_E;
            max_key_size = QAPI_CRYPTO_ECC_P256_PUBLIC_KEY_BITS;
        }
        else
        {
            return CKR_ARGUMENTS_BAD;
        }
        
        /* Allocate sign operation */
        if (QAPI_OK != qapi_Crypto_Op_Alloc(alg, QAPI_CRYPTO_MODE_VERIFY_E, max_key_size, 
                    &verify_hdl))
        {
            configPRINTF(("\nFailed to alloc op\n"));
            return CKR_FUNCTION_FAILED;
        }

        /* Copy public key from keypair object for verify operation */
        /*which public key to use?*/
        if( pkcs11OBJECT_HANDLE_CERTIFICATE == pxSession->xVerifyKey)
            publickey_obj = pxSession->xPersistentPublicKeyObjHdl;
        else if(pkcs11OBJECT_HANDLE_PUBLIC_KEY == pxSession->xVerifyKey)
            publickey_obj = pxSession->xTmpPublicKeyObj;
        else{
            /*use default  public  key to verify*/
            publickey_obj = pxSession->xPersistentPublicKeyObjHdl;
        }
        if (QAPI_OK != qapi_Crypto_Op_Key_Set(verify_hdl, publickey_obj))
        {
            configPRINTF(("\nFailed to set  key\n"));
            return CKR_FUNCTION_FAILED;
        }
    
        if (QAPI_OK != qapi_Crypto_Op_Verify_Digest(verify_hdl, NULL, 0, pucData, ulDataLen, pucSignature, ulSignatureLen))
        {
            configPRINTF(("\nFailed to verify\n"));
            xResult = CKR_SIGNATURE_INVALID;
        }
        qapi_Crypto_Op_Free(verify_hdl);
    }

    /* Return the signature verification result. */
    return xResult;
}


/**
 * @brief Generate a new assymetric keyset.
 */
CK_DEFINE_FUNCTION( CK_RV, C_GenerateKeyPair )( CK_SESSION_HANDLE xSession,
                                                CK_MECHANISM_PTR pxMechanism,
                                                CK_ATTRIBUTE_PTR pxPublicKeyTemplate,
                                                CK_ULONG ulPublicKeyAttributeCount,
                                                CK_ATTRIBUTE_PTR pxPrivateKeyTemplate,
                                                CK_ULONG ulPrivateKeyAttributeCount,
                                                CK_OBJECT_HANDLE_PTR pxPublicKey,
                                                CK_OBJECT_HANDLE_PTR pxPrivateKey )
{
    CK_RV xResult = CKR_OK;
    P11SessionPtr_t pxSessionObj = prvSessionPointerFromHandle( xSession );

    //Todo...
    return xResult;
}

/**
 * @brief Generate cryptographically random bytes.
 */
CK_DEFINE_FUNCTION( CK_RV, C_GenerateRandom )( CK_SESSION_HANDLE xSession,
                                               CK_BYTE_PTR pucRandomData,
                                               CK_ULONG ulRandomLen )
{
    CK_RV xResult = CKR_OK;
    /*lint !e9072 It's OK to have different parameter name. */
    P11SessionPtr_t pxSessionObj = prvSessionPointerFromHandle( xSession );

    if( ( NULL == pucRandomData ) ||
        ( ulRandomLen == 0 ) )
    {
        xResult = CKR_ARGUMENTS_BAD;
    }
    else
    {
        if(QAPI_OK != qapi_Crypto_Random_Get(pucRandomData,ulRandomLen))
        {
            xResult = CKR_FUNCTION_FAILED;
        }
    }

    return xResult;
}
