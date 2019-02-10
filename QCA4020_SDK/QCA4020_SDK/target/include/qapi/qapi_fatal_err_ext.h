#ifndef __QAPI_FATAL_ERR_EXT_H__
#define __QAPI_FATAL_ERR_EXT_H__

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

/*==============================================================================
 *
 *                          FATAL ERROR MANAGER EXTENSION
 *
 *============================================================================*/
 /** @file qapi_fatal_err_ext.h
 *
 * @addtogroup qapi_fatal_err_ext
 * @{
 *
 * @brief Fatal Error Manager Extension(FEME)
 *
 * @details This is an extension to FEM (i.e. Fatal Error Manager published via
 *          qapi_fatal_err.h). This exposes a QAPI to retrieve the fatal error
 *          information persistent in the AON segment after fatal error that had
 *          occured and resulted in an implicit software cold reset.
 *
 * @code {.c}
 *
 *    * The code snippet below demonstrates the use of this interface.
 *    * It retrieves fatal error information persistent in the AON segment
 *    * after fatal error that had occured and resulted in an implicit software
 *    * cold reset.
 *    * The error information populated comprises of line number, file name
 *    * prefixed with core name. Include qapi_fatal_err_ext.h for the QAPI
 *    * declaration.
 *
 *
 *   qapi_Err_Info_t err_info;

 *   qapi_get_err_info(&err_info);
 *   tf_msg( "Lineno = [%d]\r\n", err_info.lineno);
 *   tf_msg( "Core and File name = [%s]\r\n", err_info.errString);
 *
 * @endcode
 *
 * @}
 */


/*==============================================================================

                               INCLUDE FILES

==============================================================================*/

#include "qapi/qapi_types.h"

/*==============================================================================

                                   MACROS

==============================================================================*/
#if !defined(_PACKED_START)
    #if (defined(__CC_ARM) || defined(__GNUC__))
        /* ARM and GCC compilers */
        #define _PACKED_START
    #elif (defined(__ICCARM__))
    /* IAR compiler */
        #define _PACKED_START       __packed
    #else
        #define _PACKED_START
    #endif
#endif

#if !defined(_PACKED_END)
    #if (defined(__CC_ARM) || defined(__GNUC__))
        /* ARM and GCC compilers */
        #define _PACKED_END  __attribute__ ((packed))
    #elif (defined(__ICCARM__))
        /* IAR compiler */
        #define _PACKED_END
    #else
        #define _PACKED_END
    #endif
#endif

/**
 * Fatal error specific macros.
 */
/**< Maximum filename length that causes error fatal. */
#define QAPI_ERR_INFO_EXT_MAX_FILE_LEN          50
/**< Maximum corename length which results in error fatal.
     e.g. "M4: " or "M0: ". */
#define QAPI_ERR_INFO_EXT_MAX_CORENAME_LEN      4
/**< Maximum error string length that comprises of corename followed by
     filename that causes error fatal. Error string format is as follows:
        <char string       >
        <Corename: Filename>
  e.g.  <M0: abc.c> */
#define QAPI_ERR_INFO_EXT_MAX_ERR_STR_LEN   \
        (QAPI_ERR_INFO_EXT_MAX_CORENAME_LEN + QAPI_ERR_INFO_EXT_MAX_FILE_LEN)

/*==============================================================================

                               TYPE DEFINITIONS

==============================================================================*/

/** @addtogroup qapi_fatal_err_ext
@{ */

/**
 * Fatal Error Debug information structure.
 *
 * This structure is used to capture the line number and module name prefixed
 * with the corename of the source file where a fatal error was detected.
 * Reference to an instance of this structure is passed as a parameter to the
 * qapi_get_err_info() function, to retrieve the corresponding fatal error
 * information.
 * Format: Line number as integer (Fixed: 2 octets) followed by
 *         string comprising of corename (Fixed: 4 octets) and
 *         filename (Variable, Maximum: 50 octets) described below:
 *              <uint16_t><char string       >
 *              <Lineno  ><Corename: Filename>
 *         e.g. <100     ><M0: abc.c>
 */
typedef _PACKED_START struct
{
  uint16_t     lineno;
  /**< Line number in the source module. */

    char errString[QAPI_ERR_INFO_EXT_MAX_ERR_STR_LEN];
  /**< Pointer to the source file name. */ 
} _PACKED_END qapi_Err_Info_t;

/** @} */ /* end_addtogroup qapi_fatal_err_ext */

/*==============================================================================

                            FUNCTION DECLARATIONS

==============================================================================*/

/*==============================================================================
  FUNCTION      qapi_get_err_info
==============================================================================*/

/** @addtogroup qapi_fatal_err_ext
@{ */

/**
 * Retrieve the Fatal Error Debug information.
 *
 * The preseved debug information stored at fatal error in AON segments can be
 * successfully read back post the implicit software cold reset triggered by the
 * fatal error. Preserved information captures minimal error information
 * comprising of the source line number and module name prefixed with the
 * corename.
 *
 * @param[in] err_const Reference to the structure that records line number and
 *                      module name prefixed with core name.
 *
 * @note This function when called after a software cold reset owing to fatal
 *       error, can successfully retrieve the preserved error information. This
 *       error information is overriden on every fatal error, so it corresponds
 *       to the last fatal error caused.
 */
qapi_Status_t qapi_get_err_info(qapi_Err_Info_t *err_info);

/** @} */ /* end_addtogroup qapi_fatal_err_ext */ 

/*==================================================================================
  MACRO         QAPI_FATAL_ERR
==================================================================================*/



#endif /* __QAPI_FATAL_ERR_EXT_H__ */
