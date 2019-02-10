#ifndef QURT_INTERNAL_H
#define QURT_INTERNAL_H
/*=============================================================================
   Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
    
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
                           
                        
   qurt_internal.h

   GENERAL DESCRIPTION 
     QuRT internal functions and typedefs

=============================================================================*/
#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================
                                 CONSTANTS AND MACROS
=============================================================================*/ 
#undef ASSERT 
#define ASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/*======================================================================
                                Constants
======================================================================*/

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

#define TRUE   1   /* Boolean true value. */
#define FALSE  0   /* Boolean false value. */

#ifndef NULL
  #define NULL  ( (void *) 0)
#endif

/* Time */
#define QURT_TIME_NO_WAIT       0x00000000
#define QURT_TIME_WAIT_FOREVER  0xFFFFFFFF

/* OS object size */
#define QURT_INFO_OBJ_SIZE_BYTES             64
#define QURT_MUTEX_OBJ_SIZE_BYTES            64
#define QURT_SIGNAL_OBJ_SIZE_BYTES           64 
#define QURT_THREAD_ATTR_OBJ_SIZE_BYTES      128
#define QURT_TIMER_OBJ_SIZE_BYTES            128
#define QURT_PIPE_ATTR_OBJ_SIZE_BYTES        16 

/* Signal attributes */
#define QURT_SIGNAL_ATTR_WAIT_ANY    0x00000001
#define QURT_SIGNAL_ATTR_WAIT_ALL    0x00000002
#define QURT_SIGNAL_ATTR_CLEAR_MASK  0x00000004

/* Thread attributes */
#define QURT_THREAD_ATTR_PRIORITY_MAX        0
#define QURT_THREAD_ATTR_PRIORITY_DEFAULT    16
#define QURT_THREAD_ATTR_PRIORITY_MIN        31
#define QURT_THREAD_ATTR_NAME_MAXLEN         10
#define QURT_THREAD_DEFAULT_STACK_SIZE       128   

/* Timer attributes */
#define QURT_TIMER_ONESHOT              0x01   /**< one short timer .*/
#define QURT_TIMER_PERIODIC             0x02   /**< periodic timer  .*/
#define QURT_TIMER_NO_AUTO_START        0x04   /**< No Auto Activate.*/
#define QURT_TIMER_AUTO_START           0x08   /**< Default, Auto Activate */

/* Error codes */
#define QURT_EOK                 0  /**< Operation successfully performed. */
#define QURT_EFATAL             -1  /**< FATAL error which should never happen. */
#define QURT_EVAL               -2  /**< Wrong values for parameters. The specified page does not exist. */
#define QURT_EMEM               -3  /**< Not enough memory to perform operation.*/
#define QURT_EINVALID           -4  /**< Invalid argument value, invalid key. */ 
#define QURT_EFAILED_TIMEOUT    -5  /**< time out. */
#define QURT_EUNKNOWN           -6  /**< Defined but never used in BLAST. */
#define QURT_EFAILED            -7  /**< Operation failed. */
#define QURT_ENOMSGS            -8  /**< Message queue empty. */
#define QURT_ENOTALLOWED        -9  /**< Operation not allowed. */

/*======================================================================
                              Standard Types
======================================================================*/

/* The following definitions are the same across platforms*/
#ifndef _ARM_ASM_

#ifndef _BOOLEAN_DEFINED
typedef  unsigned char      boolean;     /* Boolean value type. */
#define _BOOLEAN_DEFINED
#endif

#ifndef _UINT32_DEFINED
typedef  unsigned long int  uint32;      /* Unsigned 32 bit value */
#define _UINT32_DEFINED
#endif

#ifndef _UINT16_DEFINED
typedef  unsigned short     uint16;      /* Unsigned 16 bit value */
#define _UINT16_DEFINED
#endif

#ifndef _UINT8_DEFINED
typedef  unsigned char      uint8;       /* Unsigned 8  bit value */
#define _UINT8_DEFINED
#endif

#ifndef _INT32_DEFINED
typedef  signed long int    int32;       /* Signed 32 bit value */
#define _INT32_DEFINED
#endif

#ifndef _INT16_DEFINED
typedef  signed short       int16;       /* Signed 16 bit value */
#define _INT16_DEFINED
#endif

#ifndef _INT8_DEFINED
typedef  signed char        int8;        /* Signed 8  bit value */
#define _INT8_DEFINED
#endif

#ifndef _INT64_DEFINED
   typedef long long           int64;
   #define _INT64_DEFINED
#endif

#ifndef _UINT64_DEFINED
   typedef unsigned long long  uint64;
   #define _UINT64_DEFINED
#endif
  
#endif /* _ARM_ASM_ */

/*=============================================================================
                        TYPEDEFS
=============================================================================*/
/* qurt info */
typedef struct _qurt_info_t
{
  void (*idlehook) (uint32);
  void (*bsphook)(void);
  uint8 *rtos_heap_start;
  unsigned long rtos_heap_size; 
  uint32 idle_time;
}_qurt_info_t; 

/* qurt_interrupt_handler_func_ptr_t type */
typedef void (*qurt_interrupt_handler_func_ptr_t) ( uint32 n_irq );

/** qurt_time_t types. */
typedef uint32 qurt_time_t;

/** qurt_time_unit_t types.*/
typedef enum {
  QURT_TIME_TICK ,                  /**< -- Return time in Ticks */
  QURT_TIME_MSEC ,                  /**< -- Return time in Milliseconds */
  QURT_TIME_NONE=0xFFFFFFFF         /**< -- Identifier to use if no particular return type is needed */ 
}qurt_time_unit_t;

/** QuRT init data_types **/
typedef struct qurt_data_s
{
  /* Pointer to the heap used by RTOS */
  void *hPtr;
  /* Reserved pointer for future use */
  void *rPtr;
} qurt_data_t;

/** QuRT info type */
typedef struct qurt_info  /* 8 byte aligned */
{
   unsigned long long _bSpace[QURT_INFO_OBJ_SIZE_BYTES/sizeof(unsigned long long)];
}qurt_info_t;

/** QuRT mutex type */
typedef unsigned int qurt_mutex_t;

/** QuRT signal type */
typedef unsigned int qurt_signal_t;

/** Thread ID type */
typedef unsigned long qurt_thread_t;

/** Thread attributes structure */
typedef struct qurt_thread_attr  /* 8 byte aligned */
{
   unsigned long long _bSpace[QURT_THREAD_ATTR_OBJ_SIZE_BYTES/sizeof(unsigned long long)];
}qurt_thread_attr_t;

/** qurt_timer_t types.*/
typedef unsigned long  qurt_timer_t;

/** qurt_timer_cb_func_t types. */
typedef void (*qurt_timer_callback_func_t)( void *);

typedef struct qurt_timer_attr  /* 8 byte aligned */
{
   unsigned long long _bSpace[QURT_TIMER_OBJ_SIZE_BYTES/sizeof(unsigned long long)];
}qurt_timer_attr_t;

/** Represents pipes.*/
typedef void * qurt_pipe_t;

/**  Represents pipe attributes. */
typedef struct qurt_pipe_attr  /* 8 byte aligned */
{
   unsigned long long _bSpace[QURT_PIPE_ATTR_OBJ_SIZE_BYTES/sizeof(unsigned long long)];
}qurt_pipe_attr_t;

/*=============================================================================
                                    FUNCTIONS
=============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* QURT_INTERNAL_H */

