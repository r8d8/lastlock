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
 * @file aws_pkcs11_pal.c
 * @brief NXP LPC54018 IoT module file save and read implementation  
 * for PKCS#11  based on mbedTLS with for software keys. This
 * file deviates from the FreeRTOS style standard for some function names and
 * data types in order to maintain compliance with the PKCS#11 standard.
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "FreeRTOSIPConfig.h"
#include "aws_crypto.h"
#include "task.h"
#include "aws_pkcs11.h"
#include "aws_pkcs11_config.h"

/* Flash write */
#include "qapi_status.h"
#include "qapi_fs.h"

/* C runtime includes. */
#include <stdio.h>
#include <string.h>

/*-----------------------------------------------------------*/

/**
 * @brief Writes a file to local storage.
 *
 * Port-specific file write for crytographic information.
 *
 * @param[in] pcFileName    The name of the file to be written to.
 * @param[in] pucData       Data buffer to be written to file
 * @param[in] pulDataSize   Size (in bytes) of file data.
 *
 * @return pdTRUE if data was saved successfully to file,
 * pdFALSE otherwise.
 */
 #define FS_AWS_MOUNT_POINT "/spinor/aws/"
BaseType_t PKCS11_PAL_SaveFile( char * pcFileName,
                        uint8_t * pucData,
                        uint32_t ulDataSize )
{
    int fd = -1;
    qapi_Status_t status = QAPI_OK;
    uint32_t bytes_written = 0;
    uint32_t file_path_length = strlen(FS_AWS_MOUNT_POINT) + strlen(pcFileName) + 1;
    char *file_path = malloc( file_path_length );
    
    if ( file_path == NULL ) {
    	configPRINTF(("ERROR: Unable to allocate memory\r\n"));
    	return QAPI_ERR_NO_MEMORY;
    }
    memset(file_path, 0, file_path_length);

    memcpy(file_path, FS_AWS_MOUNT_POINT, strlen(FS_AWS_MOUNT_POINT));
    uint32_t strlcat_ret = strlcat(file_path, pcFileName, file_path_length);
    if(strlcat_ret >= file_path_length) {
    	status = QAPI_ERROR;
        goto fs_write_cleanup;
    }

    status = qapi_Fs_Open(file_path, QAPI_FS_O_CREAT | QAPI_FS_O_WRONLY, &fd);
    if ( QAPI_OK != status ) {
        configPRINTF(("Failed on a call to qapi_Fs_Open()\r\n"));
        goto fs_write_cleanup;
    }
    
    status = qapi_Fs_Write(fd, pucData, ulDataSize, &bytes_written);
    if ( (QAPI_OK != status) || (bytes_written != ulDataSize) ) {
        configPRINTF(("Failed on a call to qapi_Fs_Write()\r\n"));
        status = QAPI_ERROR;
    }
fs_write_cleanup:
    free(file_path);
    if ( fd >= 0 ) {
        qapi_Fs_Close(fd);
    }

    if ( QAPI_OK != status ) {
        return pdFALSE;
    }

    return pdTRUE;
}

/*-----------------------------------------------------------*/

/**
 * @brief Reads a file from local storage.
 *
 * Port-specific file access for crytographic information.
 *
 * @sa PKCS11_ReleaseFileData
 *
 * @param[in] pcFileName    The name of the file to be read.
 * @param[out] ppucData     Pointer to buffer for file data.
 * @param[out] pulDataSize  Size (in bytes) of data located in file.
 *
 * @return pdTRUE if data was retrieved successfully from files,
 * pdFALSE otherwise.
 */
BaseType_t PKCS11_PAL_ReadFile( char * pcFileName,
                        uint8_t ** ppucData,
                        uint32_t * pulDataSize )
{
    int fd = -1;
    qapi_Status_t status = QAPI_OK;
    uint32_t bytes_read = 0;
    struct qapi_fs_stat_type stat;
    uint8_t *p_buffer = NULL;
    uint32_t file_path_length = strlen(FS_AWS_MOUNT_POINT) + strlen(pcFileName) + 1;
    char *file_path = malloc( file_path_length );
        
    if ( file_path == NULL ) {
    	configPRINTF(("ERROR: Unable to allocate memory\r\n"));
    	return QAPI_ERR_NO_MEMORY;
    }
    memset(file_path, 0, file_path_length);

    memcpy(file_path, FS_AWS_MOUNT_POINT, strlen(FS_AWS_MOUNT_POINT));
    uint32_t strlcat_ret = strlcat(file_path, pcFileName, file_path_length);
    if(strlcat_ret >= file_path_length) {
    	status = QAPI_ERROR;
        goto fs_write_cleanup;
    }

    status = qapi_Fs_Stat(file_path, &stat);
    if ( QAPI_OK != status ) {
        configPRINTF(("Failed on a call to qapi_Fs_Stat():%d\r\n",status));
        goto fs_write_cleanup;
    }

	p_buffer = (uint8_t*)malloc(stat.st_size);
	if(p_buffer == NULL) {
        configPRINTF(("Failed to allocate memory.\r\n"));
		status = QAPI_ERR_NO_MEMORY;
        goto fs_write_cleanup;
	}

    status = qapi_Fs_Open(file_path, QAPI_FS_O_RDONLY, &fd);
    if ( QAPI_OK != status ) {
        configPRINTF(("Failed on a call to qapi_Fs_Open()\r\n"));
        goto fs_write_cleanup;
    }

    status = qapi_Fs_Read(fd, p_buffer, stat.st_size, &bytes_read);
    if( (QAPI_OK != status) || (bytes_read != stat.st_size) ) {
        configPRINTF(("Failed to read file (status=%d).\r\n", status));
    	*ppucData = NULL;
    	*pulDataSize = 0;
    } else {
    	*ppucData = p_buffer;
    	*pulDataSize = stat.st_size;
    }

fs_write_cleanup:
    free(file_path);
    if ( fd >= 0 ) {
        qapi_Fs_Close(fd);
    }

    if ( QAPI_OK != status ) {
        return pdFALSE;
    }

    return pdTRUE;    
}


/**
 * @brief Cleanup after PKCS11_ReadFile().
 *
 * @param[in] pucBuffer The buffer to free.
 * @param[in] ulBufferSize The length of the above buffer.
 */
void PKCS11_PAL_ReleaseFileData( uint8_t * pucBuffer,
                                 uint32_t ulBufferSize )
{
    /* Unused parameters. */
    ( void ) ulBufferSize;

    free( pucBuffer );
}


/**
 *      PKCS#11 Override
 *
 */

/**
 * @brief Initialize the Cryptoki module for use.
 *
 * Overrides the implementation of C_Initialize in 
 * aws_pkcs11_mbedtls.c when pkcs11configC_INITIALIZE_ALT
 * is defined.
 */
#ifndef pkcs11configC_INITIALIZE_ALT
#error QCA402x requires alternate C_Initialization
#endif 

CK_DEFINE_FUNCTION( CK_RV, C_Initialize )( CK_VOID_PTR pvInitArgs )
{   /*lint !e9072 It's OK to have different parameter name. */
    ( void ) ( pvInitArgs );
    uint32_t status = CKR_OK;

    return status;
}
