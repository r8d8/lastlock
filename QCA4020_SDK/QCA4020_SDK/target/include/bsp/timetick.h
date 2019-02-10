#ifndef TIMETICK_H
#define TIMETICK_H
/*=============================================================================

                   T I M E T I C K   D R I V E R   

GENERAL DESCRIPTION
  Timetick driver routines to read the system time and program the timer interrupts.

EXTERNALIZED FUNCTIONS

  timetick_get64
    Returns the 64 bit current system timer's count.
 
  timetick_set_matchval
   Programs the comparator for the next timer interrupt.

  timetick_cvt_to_ticks
   Converts time from a specified unit to ticks.

  timetick_cvt_from_ticks
   Converts ticks to a specified time unit.

  timetick_enable 
   Enables the timer interrupt.
 
  timetick_init_calibration
   Calibrates the M4 timer.

  timetick_capture_timer
    Captures the global timer sample. 

INITIALIZATION AND SEQUENCING REQUIREMENTS
    None


Copyright (c) 2015 by QUALCOMM Technologies, Inc.  All Rights Reserved.

=============================================================================*/

/*=============================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.ioe/1.0/v2/rom/release/api/systemdrivers/timetick/timetick.h#3 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
06/23/15   pbitra     File created.

=============================================================================*/

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/

#include "com_dtypes.h"

/*=============================================================================

                           DATA DEFINITIONS

=============================================================================*/
/**
 * Various units supported by the timetick module
 */


typedef enum {
  T_TICK,     /**< -- Return time in Ticks */
  T_USEC,     /**< -- Return time in Microseconds */
  T_MSEC,     /**< -- Return time in Milliseconds */
  T_SEC,      /**< -- Return time in Seconds */
  T_MIN,      /**< -- Return time in Minutes */
  T_HOUR,     /**< -- Return time in Hours */

  T_NONE=T_TICK  /**< -- Identifier to use if no paticular return type is needed */ 

}
timetick_unit_type;

/**
 * Timers supported by the timetick module
 */
typedef enum {
  T_ACTIVE,  
  T_SLEEP
}
timetick_timer_type;

/**
 * Time, in Systemtimer tick counts
 */
typedef uint64                    timetick_type64;
typedef uint32                    timetick_type32;
/*=============================================================================

                           FUNCTION DEFINITIONS

=============================================================================*/

/* =========================================================================
FUNCTION TIMETICK_GET64

DESCRIPTION
  Read the System timer count registers, and return the 64 bit current count.

DEPENDENCIES
  None.

RETURN VALUE
  current timetick value

SIDE EFFECTS
  None

=========================================================================*/

timetick_type64 timetick_get64 (void);

/* =========================================================================
FUNCTION TIMETICK_SET_MATCHVAL

DESCRIPTION
  Program the comparator for the next timer interrupt.

DEPENDENCIES
  None.

RETURN VALUE
  None

SIDE EFFECTS
  None

=========================================================================*/

void timetick_set_matchval(timetick_timer_type timer, uint32 match_val);


/* =========================================================================
FUNCTION TIMETICK_CVT_TO_TICKS

DESCRIPTION
   Converts time from a specified unit to ticks

DEPENDENCIES
  None.

RETURN VALUE
  Converted ticks.

SIDE EFFECTS
  None

=========================================================================*/

timetick_type64 timetick_cvt_to_ticks(uint64,timetick_unit_type );



/* =========================================================================
FUNCTION TIMETICK_CVT_FROM_TICKS

DESCRIPTION
   Converts ticks to a specified time unit.

DEPENDENCIES
  None.

RETURN VALUE
  Converted time.

SIDE EFFECTS
  None

=========================================================================*/
uint64 timetick_cvt_from_ticks(timetick_type64, timetick_unit_type );

/* =========================================================================
FUNCTION TIMETICK_ENABLE

DESCRIPTION
  Enable the Timer interrupt.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None

=========================================================================*/
void timetick_enable (timetick_timer_type timer,boolean en);

/* =========================================================================
FUNCTION timetick_init_calibration

DESCRIPTION
  This API sets up a software timer and a dsr to aid in calibrating the 
  AON timer. 

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None

=========================================================================*/
void timetick_init_calibration(void);

/* =========================================================================
FUNCTION TIMETICK_CAPTURE_TIMER

DESCRIPTION
    Gives sample of global timer and fractional timer after asserting 
    RTC_CAPTURE.

DEPENDENCIES
  None.

RETURN VALUE
  Returns the global timer sample 

SIDE EFFECTS
  None

=========================================================================*/

void timetick_capture_timer (timetick_type32* count, timetick_type32* fract_count);

/* =========================================================================
FUNCTION timetick_calibrate_timer_sync

DESCRIPTION
  This is the function used to calibrate timer synchronously.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None

=========================================================================*/
void timetick_calibrate_timer_sync(void);

#endif /* TIMETICK_H */
