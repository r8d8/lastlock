/*======================================================================
   Copyright (c) 2015-2016, 2018 The Linux Foundation. All rights reserved.
    
   Redistribution and use in source and binary forms, with or without
   modification, are permitted (subject to the limitations in the
   disclaimer below) provided that the following conditions are met:
    
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
    
      * Redistributions in binary form must reproduce the above
        copyright notice, this list of conditions and the following
        disclaimer in the documentation and/or other materials provided
        with the distribution.
    
      * Neither the name of The Linux Foundation nor the names of its
        contributors may be used to endorse or promote products derived
        from this software without specific prior written permission.
    
   NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
   GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
   HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
   IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
                           
   qurt_system.c 

   GENERAL DESCRIPTION 
     QuRT CPU specific port functions

 ======================================================================*/

#include "qurt_internal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timetick.h"

/*======================================================================
                          EXTERNAL
 ======================================================================*/
/*======================================================================
                          MACROS
 ======================================================================*/

/*======================================================================
                          TYPEDEFS
 ======================================================================*/
#if defined (__GNUC__)

uint32 qurt_system_get_ipsr( void ) __attribute__ (( naked ));

#endif

#if defined(__ARMCC_VERSION)

uint32 qurt_system_get_ipsr( void );

#endif
/*======================================================================
                          FUNCTIONS
=======================================================================*/
#if defined (__GNUC__)

uint32 qurt_system_get_ipsr( void )
{
  __asm volatile
  (
		"	mrs r0, ipsr   \n" 
		"	bx r14   \n" 
  );
}

#endif /* __GNUC__ */

#if defined(__ARMCC_VERSION)

__asm uint32 qurt_system_get_ipsr( void )
{
	PRESERVE8

	mrs r0, ipsr
	bx r14
}

#endif /* __ARMCC_VERSION */

uint32 qurt_system_power_systick_restore( uint64 tsleep, uint32 syst_rvr, uint32 syst_cvr )
{
   uint32 tick_missed_abs;
   uint32 tick_missed_partial;
   uint32 reload_prog;
   static boolean b_reference_tick_initialized = FALSE;
   static uint64 rtc_reference_tick = 0ul;
   static uint64 systick_reference_tick = 0ul;
   int32 systick_drift = 0;
   uint64 systick_delta = 0ul;
   uint64 rtc_delta_in_systick = 0ul;
   uint64 rtc_tick_temp = 0ul;
   uint64 systick_temp = 0ul;
   uint32 next_unblock_time = 0u;

   if (!b_reference_tick_initialized)
   {
       /* initialize reference ticks if they have not been initialized. */
       rtc_reference_tick = (uint64) timetick_get64();
       systick_reference_tick = (uint64) xTaskGetTickCount();
       b_reference_tick_initialized = TRUE;
   }

   if( tsleep > syst_cvr)
   {
      tick_missed_abs = 1 + (tsleep - syst_cvr)/syst_rvr;
      tick_missed_partial = (tsleep - syst_cvr)%syst_rvr; 
   }
   else
   {
      tick_missed_abs = 1 + (syst_cvr - tsleep )/syst_rvr;
      tick_missed_partial = (syst_cvr- tsleep)%syst_rvr;
   }

   rtc_tick_temp = (uint64) timetick_get64();
   systick_temp = (uint64) xTaskGetTickCount();

   /* It's very important to use strict greater than while comparing systick_temp
    * and systick_reference_tick. If >= was used and the first time this function
    * got called was after a long sleep (e.g. greater than 10ms), then the mechanism
    * would falsely consider SysTick running fast because rtc_delta_in_systick 
    * woudl be equal to zero whereas systick_delta would be greater than zero. */
   if (rtc_tick_temp > rtc_reference_tick && systick_temp > systick_reference_tick)
   {
       // convert RTC ticks into SysTick
       /* There is no practical reason to add overflow check here because SYSTICK_RATE_HZ
        * would never go beyond SYSTEM_CLOCK. RTC clock will wrap around every 37.2 hours. */
       rtc_delta_in_systick = (rtc_tick_temp - rtc_reference_tick) * configTICK_RATE_HZ / configSYSTICK_CLOCK_HZ;
       // systick_delta measures how much SysTick is off compared to RTC
       systick_delta = systick_temp - systick_reference_tick + tick_missed_abs;
   } else
   {
       // reset reference tick if wrap around happens
       rtc_reference_tick = (uint64) timetick_get64();
       systick_reference_tick = (uint64) xTaskGetTickCount();
   }
   
   /* We make the assumption that the two clock will never be different by more
    * than 248 days. */
   if (rtc_delta_in_systick < systick_delta)
   {
       // SysTick is running faster than it should
       systick_drift = (int32) (systick_delta - rtc_delta_in_systick);
   } else
   {
       // SysTick is running slower than it should
       systick_drift = -((int32) (rtc_delta_in_systick - systick_delta));
   }

   if (systick_drift > 0)
   {
       /* if SysTick is running faster than it should, skip as many tick_missed_abs
        * as possible. */
       if (tick_missed_abs > systick_drift)
       {
            tick_missed_abs -= (uint32) systick_drift;
       } else
       {
           tick_missed_abs = 0;
       }
   } else if (systick_drift < 0)
   {
       /* if SysTick is running slower than it should, add the difference in 
        * SysTick to tick_missed_abs. */
       tick_missed_abs += (uint32) (-systick_drift);
   }

   next_unblock_time = xTaskGetNextTaskUnblockTime();
   if (tick_missed_abs + systick_temp > next_unblock_time)
   {
       tick_missed_abs = 
       tick_missed_abs - (tick_missed_abs + systick_temp - next_unblock_time);
   }

   reload_prog = syst_rvr - tick_missed_partial;
   vTaskStepTick(tick_missed_abs);
   return reload_prog;
}
