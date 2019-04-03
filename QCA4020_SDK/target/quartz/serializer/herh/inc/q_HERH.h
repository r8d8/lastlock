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

#ifndef  __Q_HERH_H__
#define  __Q_HERH_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <stdint.h>
#include "qapi_HERH.h"
#include "qapi/qapi_types.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define HERH_RESPONSE_TIMEOUT                                               (50)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes an event response handler. This should be called before
          the event is sent to the host that will expect a response.

   @return The handle for the response handler or NULL if there was an error.
*/
HERH_Handle_t HERH_Init_Response(void);

/**
   @brief Waits for an event response from the host and provides the data when
          it arrives.

   @param[in]  Handle     Handle returned by HERH_Init_Response.
   @param[in]  TimeOut    Time in milliseconds to wait for the response.
   @param[out] DataLength Size of the buffer for the recieved response if
                          successful.
   @param[out] Data       Data for the received response if successful.

   @return true if the wait was successful or false if it timed out.
*/
qbool_t HERH_Wait_Response(HERH_Handle_t Handle, uint32_t TimeOut, uint32_t *DataLength, uint8_t **Data);

/**
   @brief Cleans up the response handler, including the received buffer. This
          should be called when the event handler is done.

   @param[in] Handle Handle returned by HERH_Init_Response.
*/
void HERH_Cleanup_Response(HERH_Handle_t Handle);

#endif // ] #ifndef __QAPI_ZB_SERIALIZER_H__

/** @} */


