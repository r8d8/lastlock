/*======================================================================
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
                           
   qurt_init.c

   GENERAL DESCRIPTION 
     QuRT initialization functions

 ======================================================================*/

#include "qurt_internal.h"
#include "FreeRTOS.h"

/*======================================================================
                          EXTERNAL
 ======================================================================*/

/*======================================================================
                          MACROS
 ======================================================================*/
#ifndef configTOTAL_HEAP_SIZE
/* This value is specific to Free_RTOS heap */
#define configTOTAL_HEAP_SIZE 0xA000
#endif

/*======================================================================
                          TYPEDEFS
 ======================================================================*/
/*======================================================================
                          GLOBALS
=======================================================================*/
qurt_info_t qurt_info;
uint8_t *ucHeap;

/*======================================================================
                          FUNCTIONS
=======================================================================*/
int qurt_init(void *arg)
{
   qurt_data_t *qurt_data = ( qurt_data_t *)arg;
   _qurt_info_t *_qurt_info = (_qurt_info_t *)&qurt_info;
   
   ASSERT(qurt_data != NULL);
   /* Initialize FreeRTOS Heap  */
   ucHeap = (uint8_t * )(qurt_data->hPtr);
   
   /* Initialize qurt_info */   
   _qurt_info->rtos_heap_start = ucHeap;
   _qurt_info->rtos_heap_size  = configTOTAL_HEAP_SIZE;
     
   if(_qurt_info->bsphook != NULL)
   {
      _qurt_info->bsphook();
   }
   
   /* start scheduler, no return */
   vTaskStartScheduler();
   
   /* control should never reach here*/
   return QURT_EFATAL;
}

/* BSP hook that need to be set if low for mode is desired */
void qurt_power_register_idle_hook(void (*entrypoint) (uint32))
{
   _qurt_info_t *_qurt_info = (_qurt_info_t *)&qurt_info;
   _qurt_info->idlehook = entrypoint;
}

/* BSP hook that need to be set before qurt_init gets invoked */
void qurt_system_register_bsp_hook(void (*entrypoint) (void))
{
   _qurt_info_t *_qurt_info = (_qurt_info_t *)&qurt_info;
   _qurt_info->bsphook = entrypoint;
}

/* Idle hook FreeRTOS Expect for Low Power Mode */
void vPortSuppressTicksAndSleep(TickType_t idle_time )
{
   _qurt_info_t *_qurt_info = (_qurt_info_t *)&qurt_info;
   if(_qurt_info->idlehook != NULL)
   {  
      _qurt_info->idle_time = (uint32)idle_time;
      _qurt_info->idlehook(idle_time);
   }
}

uint32 qurt_system_get_idle_time( void )
{  
	_qurt_info_t *_qurt_info = (_qurt_info_t *)&qurt_info;
    return _qurt_info->idle_time;
}