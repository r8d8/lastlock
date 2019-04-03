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
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
                           
                        
   qurt_pipe.c 

   GENERAL DESCRIPTION 
     QuRT Pipe functions

 ======================================================================*/

#include "qurt_internal.h"
#include "FreeRTOS.h"
#include "queue.h"

/*======================================================================
                          EXTERNAL
 ======================================================================*/
 
extern uint32 qurt_system_get_ipsr( void );

/*======================================================================
                        MACROS
 ======================================================================*/

/*======================================================================
                          TYPEDEFS
 ======================================================================*/
/** Pipe attributes */
typedef struct _qurt_pipe_attr {
  uint32 elements;             /**< Number of elements. */
  uint32 element_size;          /**< Size of element.    */
}_qurt_pipe_attr;

/*======================================================================
                          FUNCTIONS
=======================================================================*/

void qurt_pipe_attr_init (qurt_pipe_attr_t *attr)
{
   _qurt_pipe_attr *pattr = (_qurt_pipe_attr *)attr;
   pattr->elements = 0;
   pattr->element_size = 0;
}

void qurt_pipe_attr_set_elements (qurt_pipe_attr_t *attr, uint32 elements)
{
   _qurt_pipe_attr *pattr = (_qurt_pipe_attr *)attr;  
   pattr->elements = elements;
}

void qurt_pipe_attr_set_element_size (qurt_pipe_attr_t *attr, uint32 element_size)
{
   _qurt_pipe_attr *pattr = (_qurt_pipe_attr *)attr;  
   pattr->element_size = element_size;
}

int qurt_pipe_create(qurt_pipe_t *pipe, qurt_pipe_attr_t *attr)
{
   _qurt_pipe_attr *pattr = (_qurt_pipe_attr *)attr; 
   QueueHandle_t xQueue = NULL;
   
   if(NULL == pattr)
   {
     return QURT_EINVALID;
   }
   xQueue = xQueueCreate( pattr->elements, pattr->element_size);
   if (NULL == xQueue)
   {
      return QURT_EFAILED ;
   }
   
   *pipe = (qurt_pipe_t)xQueue; 
   return QURT_EOK;
}

void qurt_pipe_delete(qurt_pipe_t pipe)
{
   if( NULL != pipe)
   {
      vQueueDelete((QueueHandle_t)pipe);
   }
}

int qurt_pipe_send_timed(qurt_pipe_t pipe, void *data, qurt_time_t timeout)
{
   BaseType_t ret;
   if( NULL == pipe)
   {
     return QURT_EINVALID;
   }
   
   /* send an item over pipe is not supported from ISR */
   ASSERT(0 == qurt_system_get_ipsr());
   
   ret = xQueueSendToBack((QueueHandle_t)pipe, (const void *)data, timeout);
   if(pdPASS != ret )
   {
    return QURT_EFAILED_TIMEOUT;
   }
   return QURT_EOK;  
}

void qurt_pipe_send(qurt_pipe_t pipe, void *data)
{
   /* send an item over pipe is not supported from ISR */
   ASSERT(0 == qurt_system_get_ipsr());
   qurt_pipe_send_timed( pipe, data, portMAX_DELAY);
}

int qurt_pipe_try_send(qurt_pipe_t pipe, void *data)
{
   BaseType_t ret;
   /*higher_prio_task_woken must be initialised to pDFALSE */
   BaseType_t higher_prio_task_woken = pdFALSE;
   
   if( NULL == pipe)
   {
     return QURT_EINVALID;
   }
   /* if running in thread mode */
   if( 0 == qurt_system_get_ipsr())
   {
      ret = xQueueSendToBack((QueueHandle_t)pipe, (const void *)data, 0);
   }
   else
   {
      ret = xQueueSendToBackFromISR((QueueHandle_t)pipe, (const void *)data, 
                                    &higher_prio_task_woken);
   }
   
   if(pdPASS != ret )
   {
    return QURT_EFAILED;
   }
   /*Calling xQueueSendToBackFromISR within an ISR routine can potentially
   cause a task that was blocked on queue to leave the blocked state.
   A context switch should be performed if unblocked task has priority equal
   or greater then task executing before interrupt was taken. If 
   higher_prio_task_woken is true then a context switch should be requested */ 
   portYIELD_FROM_ISR(higher_prio_task_woken);
   
   return QURT_EOK; 
}

int qurt_pipe_receive_timed(qurt_pipe_t pipe, void *data, qurt_time_t timeout)
{
   BaseType_t ret;
   if( NULL == pipe)
   {
     return QURT_EINVALID;
   }
   
   /* receive an item over pipe is not supported from ISR */
   ASSERT(0 == qurt_system_get_ipsr());
   
   /* receive an item over pipe is not supported from ISR */
   ret = xQueueReceive((QueueHandle_t)pipe, data, timeout);
   if(pdPASS != ret )
   {
    return QURT_EFAILED_TIMEOUT;
   }
   return QURT_EOK; 
}

void qurt_pipe_receive(qurt_pipe_t pipe, void *data)
{
   /* receive an item over pipe is not supported from ISR */
   ASSERT(0 == qurt_system_get_ipsr());
   qurt_pipe_receive_timed( pipe, data, portMAX_DELAY);
}

int qurt_pipe_try_receive(qurt_pipe_t pipe, void *data)
{
   BaseType_t ret;
   /*higher_prio_task_woken must be initialised to pDFALSE */
   BaseType_t higher_prio_task_woken = pdFALSE;
   
   if( NULL == pipe)
   {
     return QURT_EINVALID;
   }
   /* if running in thread mode */
   if( 0 == qurt_system_get_ipsr())
   {
      ret = xQueueReceive((QueueHandle_t)pipe, data, 0);
   }
   else
   {
      ret = xQueueReceiveFromISR((QueueHandle_t)pipe, data, &higher_prio_task_woken);
   }
   
   if(pdPASS != ret )
   {
    return QURT_EFAILED;
   }
   
   /*Calling xQueueReceiveFromISR within an ISR routine can potentially
   cause a task that was blocked on queue to leave the blocked state.
   A context switch should be performed if unblocked task has priority equal
   or greater then task executing before interrupt was taken. If 
   higher_prio_task_woken is true then a context switch should be requested */ 
   portYIELD_FROM_ISR(higher_prio_task_woken);
   
   return QURT_EOK; 
}

int qurt_pipe_flush(qurt_pipe_t pipe)
{
   if( NULL == pipe)
   {
     return QURT_EINVALID;
   }
   
   if ( pdPASS != xQueueReset((QueueHandle_t)pipe))
   {
    return QURT_EFAILED ;
   }
   return QURT_EOK; 
}
