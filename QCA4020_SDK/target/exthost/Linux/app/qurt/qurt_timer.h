/*
 * Copyright (c) 2015-2018 Qualcomm Technologies, Inc.
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

#ifndef QURT_TIMER_H
#define QURT_TIMER_H
/**
  @file qurt_timer.h
  @brief  Prototypes of qurt_timer API
  Qurt Timer APIs allow two different mechanisms for user notification on timer
  expiry; signal and callback. A user can choose one of them but not both.

  EXTERNAL FUNCTIONS
  None.

  INITIALIZATION AND SEQUENCING REQUIREMENTS
  None.
  */

#include "qurt_types.h"
//#include "qurt_signal_linux.h"

/*=============================================================================
  CONSTANTS AND MACROS
  =============================================================================*/

/*=============================================================================
  TYPEDEFS
  =============================================================================*/

/** QuRT timer types. */
typedef unsigned long  qurt_timer_t;


/**
  Gets the current timer ticks. The ticks are accumulated since the RTOS was started.

  @datatypes
#qurt_time_t

@return
Timer ticks since the system started.

@dependencies
None.

*/
qurt_time_t qurt_timer_get_ticks (void);

/**
  Converts the time value expressed in the specified time units to tick count.

  If the time in milliseconds is not a multiple of the systick duration in milliseconds,
  the API rounds up the returned ticks.

  @datatypes
#qurt_time_t \n
#qurt_time_unit_t

@param[in] time         Time value to convert.
@param[in] time_unit    Time units in which that value is expressed.

@return
Tick count in system ticks -- Conversion succeeded. \n
QURT_TIME_WAIT_FOREVER - Conversion failed.

@dependencies
None.

*/
qurt_time_t qurt_timer_convert_time_to_ticks(qurt_time_t time, qurt_time_unit_t time_unit );

/**
  Converts tick count to the time value expressed in the specified time units.

  @datatypes
#qurt_time_t \n
#qurt_time_unit_t

@param[in] ticks        Tick count to convert.
@param[in] time_unit    Time units in which that return value is expressed.

@return
Time value expressed in the specified time units -- Conversion succeeded. \n
QURT_TIME_WAIT_FOREVER - Conversion failed.

@dependencies
None.

*/
qurt_time_t qurt_timer_convert_ticks_to_time(qurt_time_t ticks, qurt_time_unit_t time_unit);

/** @} */ /* end_addtogroup timer_types */

#endif /* QURT_TIMER_H */
