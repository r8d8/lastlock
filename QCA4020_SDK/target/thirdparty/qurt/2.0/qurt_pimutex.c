/*=======================================================================================
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
                           
                           
   qurt_pimutex.c 

   GENERAL DESCRIPTION 
     QuRT recursive mutex with priority inheritance functions

 ======================================================================================*/

#ifdef FEATURE_MUTEX_PI_RECURSIVE

#include "qurt_internal.h"
#include "FreeRTOS.h"
#include "semphr.h"

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

/*======================================================================
                          FUNCTIONS
=======================================================================*/
qurt_mutex_t qurt_mutex_memheap_init(void *lock)
{   
   /*Memory pointed to by "lock" is statically allocated by memheap*/
   SemaphoreHandle_t pMutex = xSemaphoreCreateRecursiveMutex();
   return (qurt_mutex_t)pMutex;
}

int qurt_mutex_create(qurt_mutex_t *lock)
{
   SemaphoreHandle_t pMutex;
      
   if(NULL != lock)
   {  
     /*Create the recursive mutex*/
      pMutex= xSemaphoreCreateRecursiveMutex();
      
      if(NULL != pMutex)
      {
         *lock = (qurt_mutex_t)pMutex;
         return QURT_EOK;
      }
      else
         return QURT_EFAILED;
   }
   return QURT_EINVALID;
}

int qurt_mutex_lock_timed(qurt_mutex_t *lock, qurt_time_t timeout)
{
   BaseType_t ret; 
   
   if(NULL == lock)
      return QURT_EINVALID;
   
   SemaphoreHandle_t pMutex = (SemaphoreHandle_t)*lock;
   
   /* mutex lock timed is not supported from ISR */
   ASSERT(0 == qurt_system_get_ipsr());
   
   if(NULL == pMutex)
      return QURT_EINVALID;
   
   ret = xSemaphoreTakeRecursive(pMutex , (TickType_t)timeout);
   if(pdPASS != ret)
   {
    return QURT_EFAILED_TIMEOUT;
   }
   return QURT_EOK;
}

void qurt_mutex_lock(qurt_mutex_t *lock)
{
   if(NULL == lock)
      return;
   
   SemaphoreHandle_t pMutex = (SemaphoreHandle_t)*lock;
   
   /* mutex lock timed is not supported from ISR */
   ASSERT(0 == qurt_system_get_ipsr());
   xSemaphoreTakeRecursive(pMutex , portMAX_DELAY);
}

void qurt_mutex_unlock(qurt_mutex_t *lock)
{
   if(NULL == lock)
      return;
   
   SemaphoreHandle_t pMutex = (SemaphoreHandle_t)*lock;
   xSemaphoreGiveRecursive(pMutex);
}

int qurt_mutex_try_lock(qurt_mutex_t *lock)
{
   BaseType_t ret; 
   SemaphoreHandle_t pMutex;
   
   if(NULL == lock)
      return QURT_EINVALID;
   
   pMutex = (SemaphoreHandle_t)*lock;   
   
   if(NULL == pMutex)
   {
      return QURT_EINVALID;
   }
   ret = xSemaphoreTakeRecursive(pMutex , 0);
   if(pdPASS != ret)
   {
      return QURT_EFAILED;
   }
   return QURT_EOK;
}

void qurt_mutex_memheap_destroy(void *lock)
{
   SemaphoreHandle_t pMutex = (SemaphoreHandle_t)lock;
   if(NULL != pMutex)
   {
      vSemaphoreDelete(pMutex);
   }
}

void qurt_mutex_delete(qurt_mutex_t *lock)
{
   SemaphoreHandle_t pMutex;
   
   if(NULL == lock)
      return;
   
   pMutex = (SemaphoreHandle_t *)*lock;
   if(NULL != pMutex)
   {
      vSemaphoreDelete(pMutex);
      *lock = 0;
   }
}

#endif /* FEATURE_MUTEX_PI_RECURSIVE */
