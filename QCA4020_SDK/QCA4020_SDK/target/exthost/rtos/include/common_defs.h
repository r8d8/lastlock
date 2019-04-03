/*
 * Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
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

#ifndef __EXTHOST_RTOS_COMMON_DEFS_H__
#define __EXTHOST_RTOS_COMMON_DEFS_H__

/*
 * This header is a place for definitions which are used by multiple
 * Host modules but are not currently provided by underlying system
 * software.
 */

#define ASSERT( __bool ) \
    do { \
        if (0 == (__bool)) { \
            __asm volatile("bkpt 0"); \
        } \
    } while (0)

/*
 * Macros to block/unblock interrupts.
 * Caller declares "unsigned long intrstate" on stack in order to use these.
 * TBD: Should be QAPIs
 */
extern unsigned long core_platform_int_lock(void);
extern unsigned long core_platform_int_free(void);
#define INTR_BLOCK(intrstate)    do { (intrstate) = core_platform_int_lock(); } while(0)
#define INTR_UNBLOCK(intrstate)  do { if(!(intrstate)) { core_platform_int_free(); } } while(0)

/*
 * Return a 64-bit tick counter that can be used
 * to measure passage of time.
 * TBD: Should be a QAPI
 */
extern uint64 timetick_get64(void);

/* Sleep for some number of milliseconds */
#define Sleep(msec)    do { \
                              qurt_time_t qtime;\
                              qtime = qurt_timer_convert_time_to_ticks((msec), QURT_TIME_MSEC);\
                              qurt_thread_sleep(qtime);\
                          } while (0)

/* Fill a buffer with random values */
#define RANDOM_BUFFER_FILL(buf, bufsz) (void)qapi_Crypto_Random_Get((buf), (bufsz))

/* Some compilers predefine __FILENAME__; other predefine __FILE__ */
#if !defined(__FILENAME__)
#define __FILENAME__ __FILE__
#endif

#endif /* __EXTHOST_RTOS_COMMON_DEFS_H__ */
