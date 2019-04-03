/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc. 
 * All Rights Reserved. 
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * $QTI_LICENSE_QDN_C
 *
 * Amazon FreeRTOS Crypto V1.0.2
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
#include "aws_crypto.h"


/* C runtime includes. */
#include <string.h>

/* Qualcomm Technologies includes*/
#include "qapi_status.h"
#include "qapi_crypto.h"
#include "qapi_ssl_cert.h"


//#define dconfigPRINTF( x ) configPRINTF( (x) )
/**
 * @brief Internal signature verification context structure
 */
typedef struct SignatureVerificationState
{
    BaseType_t xAsymmetricAlgorithm;
    BaseType_t xHashAlgorithm;

    qapi_Crypto_Op_Hdl_t opHdl;
    uint8_t doDigestOK;
    /* save HASH value*/
    uint8_t ucSHA[ cryptoSHA256_DIGEST_BYTES ];
    size_t xHashLength;
} SignatureVerificationState_t, * SignatureVerificationStatePtr_t;

/*
 * Helper routines
 */
#if 0
/**
 * @brief Implements libc calloc semantics using the FreeRTOS heap
 */
static void * prvCalloc( size_t xNmemb,
                         size_t xSize )
{
    void * pvNew = pvPortMalloc( xNmemb * xSize );

    if( NULL != pvNew )
    {
        memset( pvNew, 0, xNmemb * xSize );
    }

    return pvNew;
}
#endif

/**
 * @brief Verifies a cryptographic signature based on the signer
 * certificate, hash algorithm, and the data that was signed.
 */
static BaseType_t prvVerifySignature( char * pcSignerCertificate,
                                      size_t xSignerCertificateLength,
                                      BaseType_t xHashAlgorithm,
                                      uint8_t * pucHash,
                                      size_t xHashLength,
                                      BaseType_t xSignatureAlgorithm,
                                      uint8_t * pucSignature,
                                      size_t xSignatureLength )
{
    BaseType_t xResult = pdTRUE;
    qapi_Crypto_Obj_Hdl_t obj_hdl;
    qapi_Crypto_Op_Hdl_t verify_hdl;
    uint32_t alg;
    uint32_t curve_id;
    uint32_t obj_type;
    uint32_t max_key_size = 0;
    
    /* Parse cert*/
    if( cryptoASYMMETRIC_ALGORITHM_RSA == xSignatureAlgorithm )
    {
        //QAPI_CRYPTO_OBJ_TYPE_RSA_PUBLIC_KEY_E
        if(QAPI_OK != qapi_Crypto_Transient_Obj_Import_From_Pem(QAPI_CRYPTO_OBJ_TYPE_RSA_PUBLIC_KEY_E, pcSignerCertificate, NULL, &obj_hdl))
        {
            dconfigPRINTF(("trans pem failed\n"));
            return pdFALSE;
        }
    }else if(cryptoASYMMETRIC_ALGORITHM_ECDSA == xSignatureAlgorithm)
    {
        if(QAPI_OK != qapi_Crypto_Transient_Obj_Import_From_Pem(QAPI_CRYPTO_OBJ_TYPE_ECDSA_PUBLIC_KEY_E, pcSignerCertificate, NULL, &obj_hdl))
        {
            dconfigPRINTF(("ECDSA trans pem  failed\n"));
            return pdFALSE;
        }
    }

    /* set alg and key size  */
    if( cryptoASYMMETRIC_ALGORITHM_RSA == xSignatureAlgorithm )
    {
        if(cryptoSHA256_DIGEST_BYTES == xHashLength )
        {
            alg = QAPI_CRYPTO_ALG_RSASSA_PKCS1_V1_5_SHA256_E;
            //max_key_size = QAPI_CRYPTO_HMAC_SHA1_MAX_KEY_BITS;
        }
        else if(cryptoSHA1_DIGEST_BYTES == xHashLength )
        {
            alg = QAPI_CRYPTO_ALG_RSASSA_PKCS1_V1_5_SHA1_E;
            //max_key_size = QAPI_CRYPTO_HMAC_SHA256_MAX_KEY_BITS;
        }
         obj_type = QAPI_CRYPTO_OBJ_TYPE_RSA_PUBLIC_KEY_E;
         max_key_size = 8 * 0x100; /* To be consistent with qapi_Crypto_Transient_Obj_Import_From_Pem()*/
    }
    else if( cryptoASYMMETRIC_ALGORITHM_ECDSA == xSignatureAlgorithm )
    {
        if(QAPI_OK != qapi_Crypto_Obj_Val_Attrib_Get(obj_hdl,QAPI_CRYPTO_ATTR_ECC_CURVE_E,&curve_id,NULL))
        {
            dconfigPRINTF(("fail to get curve id\n"));
            return pdFALSE;
        }
        
        switch (curve_id)
        {
          case QAPI_CRYPTO_ECC_CURVE_NIST_P192:
            alg = QAPI_CRYPTO_ALG_ECDSA_P192_E;
            max_key_size = QAPI_CRYPTO_ECC_P192_PUBLIC_KEY_BITS;
            break;
          case QAPI_CRYPTO_ECC_CURVE_NIST_P224:
            alg = QAPI_CRYPTO_ALG_ECDSA_P224_E;
            max_key_size = QAPI_CRYPTO_ECC_P224_PUBLIC_KEY_BITS;
            break;
          case QAPI_CRYPTO_ECC_CURVE_NIST_P256:
            alg = QAPI_CRYPTO_ALG_ECDSA_P256_E;
            max_key_size = QAPI_CRYPTO_ECC_P256_PUBLIC_KEY_BITS;
            break;
          case QAPI_CRYPTO_ECC_CURVE_NIST_P384:
            alg = QAPI_CRYPTO_ALG_ECDSA_P384_E;
            max_key_size = QAPI_CRYPTO_ECC_P384_PUBLIC_KEY_BITS;
            break;
          case QAPI_CRYPTO_ECC_CURVE_NIST_P521:
            alg = QAPI_CRYPTO_ALG_ECDSA_P521_E;
            max_key_size = QAPI_CRYPTO_ECC_P521_PUBLIC_KEY_BITS;
            break;
          default:
            dconfigPRINTF(("unkown curve id\n"));
            return pdFALSE;
        }
        obj_type = QAPI_CRYPTO_OBJ_TYPE_ECDSA_PUBLIC_KEY_E;
    }
    else
    {
        dconfigPRINTF(("\nwrong algorithm\n"));
        return pdFALSE;
    }

    /* Allocate key size */
    if (QAPI_OK != qapi_Crypto_Op_Alloc(alg, QAPI_CRYPTO_MODE_VERIFY_E, max_key_size, &verify_hdl)) {
        dconfigPRINTF(("\nFailed to alloc verify op\n"));
        xResult = pdFALSE;
        goto Error_Exit;
    }

    /* Copy public key from keypair object for verify operation */
    if (QAPI_OK != qapi_Crypto_Op_Key_Set(verify_hdl, obj_hdl))
    {
        dconfigPRINTF(("\nFailed to set public key\n"));
        xResult = pdFALSE;
        goto Exit;
    }

    /* Verify signature */
    if (QAPI_OK != qapi_Crypto_Op_Verify_Digest(verify_hdl, NULL, 0, pucHash, xHashLength, pucSignature, xSignatureLength))
    {
        dconfigPRINTF(("Verify failed\n"));
        xResult = pdFALSE;
        goto Exit;
    }
Exit:
    qapi_Crypto_Op_Free(verify_hdl);
Error_Exit:    
    qapi_Crypto_Transient_Obj_Free(obj_hdl);
    return xResult; 
}

/*
 * Interface routines
 */
/**
 * @brief Overrides CRT heap callouts to use FreeRTOS instead
 */
void CRYPTO_ConfigureHeap( void )
{
    /*qcom chip will not use it.*/
}

/**
 * @brief Creates signature verification context.
 */
BaseType_t CRYPTO_SignatureVerificationStart( void ** ppvContext,
                                              BaseType_t xAsymmetricAlgorithm,
                                              BaseType_t xHashAlgorithm )
{
    BaseType_t xResult = pdTRUE;
    SignatureVerificationStatePtr_t pxCtx = NULL;

    /*
     * Allocate the context
     */
    if( NULL == ( pxCtx = ( SignatureVerificationStatePtr_t ) pvPortMalloc(
                      sizeof( *pxCtx ) ) ) ) /*lint !e9087 Allow casting void* to other types. */
    {
        xResult = pdFALSE;
    }

    if( pdTRUE == xResult )
    {
        *ppvContext = pxCtx;

        /*
         * Store the algorithm identifiers
         */
        pxCtx->xAsymmetricAlgorithm = xAsymmetricAlgorithm;
        pxCtx->xHashAlgorithm = xHashAlgorithm;
        pxCtx->doDigestOK = 0;
        /*
         * Initialize the requested hash type
         */
        if( cryptoHASH_ALGORITHM_SHA1 == pxCtx->xHashAlgorithm )
        {
            pxCtx->xHashLength = cryptoSHA1_DIGEST_BYTES;
            if (qapi_Crypto_Op_Alloc(QAPI_CRYPTO_ALG_SHA1_E, QAPI_CRYPTO_MODE_DIGEST_E, 0, &pxCtx->opHdl) != QAPI_OK)  //QAPI_OK is 0
                xResult = pdFALSE;
        }
        else if( cryptoHASH_ALGORITHM_SHA256 == pxCtx->xHashAlgorithm )
        {
            pxCtx->xHashLength = cryptoSHA256_DIGEST_BYTES;
            if (qapi_Crypto_Op_Alloc(QAPI_CRYPTO_ALG_SHA256_E, QAPI_CRYPTO_MODE_DIGEST_E, 0, &pxCtx->opHdl) != QAPI_OK) 
                xResult = pdFALSE;
        }
        else
        {
             dconfigPRINTF(("Wrong Hash Algorithm\n"));
             xResult = pdFALSE;
        }
    }

    return xResult;
}
/**
 * @brief Adds bytes to an in-progress hash for subsequent signature
 * verification.
 */
void CRYPTO_SignatureVerificationUpdate( void * pvContext,
                                         uint8_t * pucData,
                                         size_t xDataLength )
{
    SignatureVerificationStatePtr_t pxCtx = ( SignatureVerificationStatePtr_t ) pvContext; /*lint !e9087 Allow casting void* to other types. */

    /*
     * Add the data to the hash of the requested type
     */
    if (QAPI_OK == qapi_Crypto_Op_Digest_Final(pxCtx->opHdl, (void*)pucData, (uint32_t)xDataLength, pxCtx->ucSHA, &pxCtx->xHashLength)) 
    {
        pxCtx->doDigestOK = 1;
    }
}

/**
 * @brief Performs signature verification on a cryptographic hash.
 */
BaseType_t CRYPTO_SignatureVerificationFinal( void * pvContext,
                                              char * pcSignerCertificate,
                                              size_t xSignerCertificateLength,
                                              uint8_t * pucSignature,
                                              size_t xSignatureLength )
{
    BaseType_t xResult = pdTRUE;
    SignatureVerificationStatePtr_t pxCtx =
        ( SignatureVerificationStatePtr_t ) pvContext; /*lint !e9087 Allow casting void* to other types. */

     /*
     * Verify the signature
     */
    if( pxCtx->doDigestOK )
    {
            xResult = prvVerifySignature( pcSignerCertificate,
                                  xSignerCertificateLength,
                                  pxCtx->xHashAlgorithm,
                                  pxCtx->ucSHA,
                                  pxCtx->xHashLength,
                                  pxCtx->xAsymmetricAlgorithm,
                                  pucSignature,
                                  xSignatureLength );
    }
    else
    {
        dconfigPRINTF(("\nqapi_Crypto_Op_Digest_Final failed\n"));
        xResult = pdFALSE;
    }
    /*
    * Clean-up
    */
    qapi_Crypto_Op_Free(pxCtx->opHdl);
    vPortFree( pxCtx );

    return xResult;
}
