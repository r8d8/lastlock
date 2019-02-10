/*======================================================================
   Copyright (c) 2015-2017, The Linux Foundation. All rights reserved.
    
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
                           
   qurt_thread.c 

   GENERAL DESCRIPTION 
     QuRT thread functions
 ======================================================================*/

#include "qurt_internal.h"
#include "FreeRTOS.h"


#if (QURT_THREAD_ATTR_PRIORITY_MAX >= configMAX_PRIORITIES)
   #error "QuRT Maximum Priority is not supported"
#endif

/*======================================================================
                          EXTERNAL
 ======================================================================*/
extern uint32 qurt_system_get_ipsr( void );
extern size_t strlcpy(char *dst, const char *src, size_t siz);
/*======================================================================
                        MACROS
 ======================================================================*/

/*======================================================================
                          TYPEDEFS
 ======================================================================*/
/** Thread attributes */
typedef struct _qurt_thread_attr {
   char name[QURT_THREAD_ATTR_NAME_MAXLEN]; /**< Thread name. */
   unsigned short priority;                 /**< Thread priority.   */
   unsigned int   stack_size;               /**< Thread stack size. */
   void *stack_addr;                        /**< Stack address base */
}_qurt_thread_attr;


/*======================================================================
                          FUNCTIONS
=======================================================================*/

void qurt_thread_attr_init (qurt_thread_attr_t *attr)
{
   _qurt_thread_attr *pattr = (_qurt_thread_attr *)attr;
   pattr->name[0] = 0;
   pattr->priority = QURT_THREAD_ATTR_PRIORITY_DEFAULT;
   pattr->stack_size = 0;
   pattr->stack_addr = 0;
}

void qurt_thread_attr_set_name (qurt_thread_attr_t *attr, const char *name)
{
   _qurt_thread_attr *pattr = (_qurt_thread_attr *)attr;  
   strlcpy (pattr->name, name, QURT_THREAD_ATTR_NAME_MAXLEN);
   pattr->name[QURT_THREAD_ATTR_NAME_MAXLEN - 1] = 0;
}

void qurt_thread_attr_set_priority (qurt_thread_attr_t *attr, uint16 priority)
{
   _qurt_thread_attr *pattr = (_qurt_thread_attr *)attr;    
   pattr->priority = (QURT_THREAD_MAX_PRIORITIES -1) - priority;
}

void qurt_thread_attr_set_stack_size (qurt_thread_attr_t *attr, uint32 stack_size)
{
   _qurt_thread_attr *pattr = (_qurt_thread_attr *)attr;    
   pattr->stack_size = stack_size;
}

int qurt_thread_create(qurt_thread_t *thread_id, qurt_thread_attr_t *attr, void (*entrypoint) (void *), void *arg)
{
   _qurt_thread_attr *pattr = (_qurt_thread_attr *)attr; 
   BaseType_t ret;
   
   if(NULL == pattr || (pattr->priority > QURT_THREAD_MAX_PRIORITIES -1))
   {
     return QURT_EINVALID;
   }
   ret = xTaskCreate((TaskFunction_t)entrypoint, pattr->name, pattr->stack_size/sizeof(StackType_t), 
                     arg, pattr->priority, (void *)thread_id);

   if (ret != pdPASS)
   {
    if(ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY )
    {    
      return QURT_EMEM;
    }
    else
    {
      return QURT_EFAILED ;
    }
   }  
   return QURT_EOK;
}

qurt_thread_t qurt_thread_get_id (void)
{
   return (qurt_thread_t)xTaskGetCurrentTaskHandle();
}

int qurt_thread_get_priority(qurt_thread_t thread_id)
{
   if(NULL == (void *)thread_id)
   {
      return QURT_EINVALID;
   }
   /* convert the freertos priority scheme back to qurt */
   int qurt_prio = (QURT_THREAD_MAX_PRIORITIES -1) - 
                   uxTaskPriorityGet((TaskHandle_t)thread_id);
   return qurt_prio;
}

int qurt_thread_set_priority (qurt_thread_t thread_id, uint16 newprio)
{
   /* convert the qurt priority scheme to freertos */
   newprio = (QURT_THREAD_MAX_PRIORITIES -1) - newprio;
   if(newprio > QURT_THREAD_MAX_PRIORITIES -1)
   {
      return QURT_EINVALID;
   }
   if(NULL == (void *)thread_id)
   {
      return QURT_EINVALID;
   }
   /* vTaskPrioritySet does not have return code */
   vTaskPrioritySet((TaskHandle_t)thread_id, newprio);
   return QURT_EOK;
} 

int qurt_thread_set_fp_enable(qurt_thread_t thread_id, uint16 fp_enable_flag)
{
   /* Stub */
}

int qurt_thread_get_name  (char *name, uint8 max_len)
{
   char *thread_name = NULL; 
   int thread_name_length = 0;
   
   if(NULL == name)
   {
      return QURT_EINVALID;
   }
   thread_name = pcTaskGetTaskName(xTaskGetCurrentTaskHandle());
   if(NULL == thread_name)
   {
    return thread_name_length;
   }
   thread_name_length = strlcpy (name, thread_name, max_len);
   if(thread_name_length > max_len)
   {
     return max_len - 1;
   }
   return thread_name_length;
} 

int qurt_thread_suspend (qurt_thread_t thread_id)
{
   if(NULL == (void *)thread_id)
   {
      return QURT_EINVALID;
   }
   vTaskSuspend((TaskHandle_t)thread_id);
   return QURT_EOK;
}

int qurt_thread_resume (qurt_thread_t thread_id)
{
   if(NULL == (void *)thread_id)
   {
      return QURT_EINVALID;
   }

   /* if running in thread mode */
   if( 0 == qurt_system_get_ipsr())
   {
      vTaskResume((TaskHandle_t)thread_id);
      return QURT_EOK;
   }
   else
   {
      /* check return code to know if context switch will happen ? */
      xTaskResumeFromISR((TaskHandle_t)thread_id);
      return QURT_EOK;
   }
}

void qurt_thread_yield (void)
{
  taskYIELD();
}

void qurt_thread_stop (void)
{
  vTaskDelete(NULL);
}

void qurt_thread_sleep (qurt_time_t duration)
{
   vTaskDelay(duration);
}