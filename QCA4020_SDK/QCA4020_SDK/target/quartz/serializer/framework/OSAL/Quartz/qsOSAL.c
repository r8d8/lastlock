/*
 * Copyright (c) 2016-2017 Qualcomm Technologies, Inc.
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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "stringl.h"
#include "malloc.h"
#include "qsOSAL.h"

#include <qurt_types.h>
#include <qurt_error.h>
#include <qurt_mutex.h>
#include <qurt_pipe.h>
#include <qurt_signal.h>
#include <qurt_thread.h>
#include <qurt_timer.h>

/**
  The following type is a wrapper of the thread object used in this system.
  */
typedef struct Thread_Wrapper_Info_s
{
    Thread_t  Thread_Function;
    void     *Thread_Parameter;
} Thread_Wrapper_Info_t;

static void QSOSAL_Thread_Wrapper(void *User_Data);
static uint32_t QSOSAL_MillisecondsToTicks(uint32_t Milliseconds);

/**
  @brief This function is the thread wrapper.

  @param[in] User_Data is the thread wrapper info.
  */
static void QSOSAL_Thread_Wrapper(void *User_Data)
{
    Thread_Wrapper_Info_t *Thread_Wrapper_Info;

    if(User_Data != NULL)
    {
        Thread_Wrapper_Info = (Thread_Wrapper_Info_t *)User_Data;

        /* Call the actual thread function via the thread function pointer. */
        (*(Thread_Wrapper_Info->Thread_Function))(Thread_Wrapper_Info->Thread_Parameter);

        /* The actual thread terminated and we should free the User_Data. */
        QSOSAL_FreeMemory(User_Data);
    }

    /* Delete the current thread. */
    qurt_thread_stop();
}

/**
  @brief This function converts milliseconds to ticks.

  @param Milliseconds is the milliseoncds to be converted to ticks.

  @return
  The tick count equivalent of the provided time.
  */
static uint32_t QSOSAL_MillisecondsToTicks(uint32_t Milliseconds)
{
    return((uint32_t)(qurt_timer_convert_time_to_ticks((qurt_time_t)Milliseconds, QURT_TIME_MSEC)));
}

/**
  @brief This function creates a new thread in the system.

  @param[in] Thread_Info is the info about the thread to be created.

  @return
  pointer to a thread handle if success.
  NULL    if it is failed to create the thread.

*/
ThreadHandle_t QSOSAL_CreateThread(Thread_t ThreadFunction, unsigned int StackSize, void *ThreadParameter)
{
   ThreadHandle_t         Ret_Val;
   qurt_thread_t          thread_id;
   qurt_thread_attr_t     Thread_Attribute;
   Thread_Wrapper_Info_t *Thread_Wrapper_Info;

   if((ThreadFunction != NULL) && (StackSize > 0))
   {
      Thread_Wrapper_Info = (Thread_Wrapper_Info_t *)QSOSAL_AllocateMemory(sizeof(Thread_Wrapper_Info_t));

      if(Thread_Wrapper_Info != NULL)
      {
         /* Set up Thread_Wrapper_Info. */
         Thread_Wrapper_Info->Thread_Function  = ThreadFunction;
         Thread_Wrapper_Info->Thread_Parameter = ThreadParameter;

         /* Set up Thread_Attribute. */
         qurt_thread_attr_init(&Thread_Attribute);
         qurt_thread_attr_set_name(&Thread_Attribute, (char *)"QSOAL_Thread");
         qurt_thread_attr_set_priority(&Thread_Attribute, 5);
         qurt_thread_attr_set_stack_size(&Thread_Attribute, StackSize);

         /* Create thread. */
         if(qurt_thread_create(&thread_id, &Thread_Attribute, QSOSAL_Thread_Wrapper, Thread_Wrapper_Info) == QURT_EOK)
         {
             Ret_Val = (ThreadHandle_t)thread_id;
         }
         else
         {
            QSOSAL_FreeMemory(Thread_Wrapper_Info);
            Ret_Val = NULL;
         }
      }
      else
      {
         Ret_Val = NULL;
      }
   }
   else
   {
      Ret_Val = NULL;
   }

   return(Ret_Val);
}

/**
  @brief This function allocates a memory buffer with the specified size.

  @param[in] Size is the number of bytes to be allocated.

  @return
  A pointer to the allocated buffer on a successful allocation.
  NULL if it is failed to allocate the buffer.
  */
void *QSOSAL_AllocateMemory(uint32_t Size)
{
    void *Ret_Val;

    if(Size)
    {
        Ret_Val = malloc(Size);
    }
    else
    {
        Ret_Val = NULL;
    }

    return(Ret_Val);
}

/**
  @brief This function frees a specifed memory buffer.

  @param[in] Address is the pointer to the memory buffer to be freed.
  */
void QSOSAL_FreeMemory(void *Address)
{
    if(Address != NULL)
    {
        free(Address);
    }
}

/**
  @brief This function sets a number of bytes in specified memory buffer to
  a specific value.

  @param[in] Address is the pointer to the memory buffer.
  @param[in] Value   is the value to be set.
  @param[in] Size    is the number of bytes in the memory buffer to be set.
  */
void QSOSAL_MemInitialize(void *Address, uint8_t Value, uint32_t Size)
{
    if(Address != NULL)
    {
        memset(Address, Value, Size);
    }
}

/**
  @brief This function performs a memcpy.

  @param[in] Destination      is the buffer where the data will be copied to.
  @param[in] Source           is the buffer which holds the data to be copied.
  @param[in] Size             is the number of bytes to be
  copied.

  @return
  The actual number of bytes that is copied from source to destination.
  */
void QSOSAL_MemCopy(void *Destination, const void *Source, unsigned long Size)
{
    memcpy(Destination, Source, Size);
}

/**
  @brief This function performs a safe memcpy.

  @param[in] Destination      is the buffer where the data will be copied to.
  @param[in] Destination_Size is the size of the destination buffer.
  @param[in] Source           is the buffer which holds the data to be copied.
  @param[in] Source_Size      is the number of bytes to be copied.

  @return
  The actual number of bytes that is copied from source to destination.
  */
void QSOSAL_MemCopy_S(void *Destination, unsigned long Destination_Size, const void *Source, unsigned long Source_Size)
{
    if((Destination != NULL) && (Source != NULL))
    {
        memscpy(Destination, Destination_Size, Source, Source_Size);
    }
}

/**
  @brief This function compares two memory blocks with the given size.

  @param[in] Source1      is the buffer where the data will be copied to.
  @param[in] Source2      is the size of the destination buffer.
  @param[in] Compare_Size is the size of the memory block to be compared.

  @return
  0              -- if Source1 and Source2 are eaqul.
  positive vlaue -- if Source1 is greater than Source2.
  negative value -- if Source1 is less than Source2.
  */
int QSOSAL_MemCompare(const void *Source1, const void *Source2, unsigned long Compare_Size)
{
    int Ret_Val;

    Ret_Val = (int)memcmp(Source1, Source2, Compare_Size);

    return Ret_Val;
}

/**
  @brief This function creates a recursive mutex object.

  @return
  Pointer to the mutex object cretaed on success.
  NULL if it is failed to create the mutex object.
  */
Mutex_t QSOSAL_CreateMutex(Boolean_t CreateOwned)
{
    Mutex_t       Ret_Val;
    qurt_mutex_t *Qurt_Mutex;

    Qurt_Mutex = (qurt_mutex_t *)QSOSAL_AllocateMemory(sizeof(qurt_mutex_t));

    if(Qurt_Mutex != NULL)
    {
        qurt_mutex_init(Qurt_Mutex);

        if (CreateOwned)
        {
            QSOSAL_WaitMutex((Mutex_t)Qurt_Mutex, QSOSAL_INFINITE_WAIT);
        }

        Ret_Val = (Mutex_t)Qurt_Mutex;
    }
    else
    {
        Ret_Val = NULL;
    }

    return(Ret_Val);
}

/**
  @brief This function will wait on a recursive mutex object.

  @param[in] Mutex   is mutex object to be waited for.
  @param[in] Timeout is the waiting time (in milliseconds) for the mutex.

  @return
  true  if the mutex object is available.
  false if it is failed to wait for the mutex object.
  */
Boolean_t QSOSAL_WaitMutex(Mutex_t Mutex, unsigned long Timeout)
{
    Boolean_t   Ret_Val;
    int32_t     Result;
    qurt_time_t Ticks;

    if(Mutex != NULL)
    {
        if(Timeout == QSOSAL_INFINITE_WAIT)
        {
            Ticks = QURT_TIME_WAIT_FOREVER;
        }
        else
        {
            Ticks = (qurt_time_t)QSOSAL_MillisecondsToTicks(Timeout);
        }

        Result = qurt_mutex_lock_timed((qurt_mutex_t *)Mutex, Ticks);

        Ret_Val = (bool)(Result == QURT_EOK);
    }
    else
    {
        Ret_Val = false;
    }

    return(Ret_Val);
}

/**
  @brief This function relases on a recursive mutex object.

  @param[in] Mutex is mutex object to be released.

*/
void QSOSAL_ReleaseMutex(Mutex_t Mutex)
{
    if(Mutex != NULL)
    {
        qurt_mutex_unlock((qurt_mutex_t *)Mutex);
    }
}

/**
  @brief This function deletes on a recursive mutex object.

  @param[in] Mutex is mutex object to be deleted.

*/
void QSOSAL_CloseMutex(Mutex_t Mutex)
{
    if(Mutex != NULL)
    {
        qurt_mutex_destroy((qurt_mutex_t *)Mutex);
        QSOSAL_FreeMemory(Mutex);
    }
}

/**
  @brief This function creates an event object.

  @return
  Pointer to the event object on success.
  NULL if it is failed to create the event object.
  */
Event_t QSOSAL_CreateEvent(Boolean_t CreateSignalled)
{
    Event_t        Ret_Val;
    qurt_signal_t *Qurt_Event;

    Qurt_Event = (qurt_signal_t *)QSOSAL_AllocateMemory(sizeof(qurt_signal_t));

    if(Qurt_Event != NULL)
    {
        qurt_signal_init(Qurt_Event);

        if (CreateSignalled)
        {
            QSOSAL_SetEvent((Event_t)Qurt_Event);
        }

        Ret_Val = (Event_t)Qurt_Event;
    }
    else
    {
        Ret_Val = NULL;
    }

    return(Ret_Val);
}

/**
  @brief This function waits for an event to occur.

  @param[in]  Event   is the event to be waited for.
  @param[in]  Timeout is the waiting time (in milliseconds) for the event.
  @param[out] Event_Wait_Result is the event waiting result upon successful
  waiting.

  @return
  true  if the waiting is success and the caller should check the
  Event_Wait_Result.
  false if it is falied to wait for an event.

*/
Boolean_t QSOSAL_WaitEvent(Event_t Event, unsigned long Timeout)
{
    Boolean_t   Ret_Val;
    int32_t     Result;
    qurt_time_t Ticks;
    uint32_t    WaitResult;

    if(Event != NULL)
    {
        if(Timeout == QSOSAL_INFINITE_WAIT)
        {
            Ticks = QURT_TIME_WAIT_FOREVER;
        }
        else
        {
            Ticks = (qurt_time_t)QSOSAL_MillisecondsToTicks(Timeout);
        }

        Result = qurt_signal_wait_timed((qurt_signal_t *)Event, 0x01, QURT_SIGNAL_ATTR_WAIT_ANY, (uint32 *)&WaitResult, Ticks);

        Ret_Val = (bool)(Result == QURT_EOK);
    }
    else
    {
        Ret_Val = false;
    }

    return(Ret_Val);
}

/**
  @brief This function sets a specific event.

  @param[in] Event is the event to be set.
  */
void QSOSAL_SetEvent(Event_t Event)
{
    if(Event != NULL)
    {
        qurt_signal_set((qurt_signal_t *)Event, 0x01);
    }
}

/**
  @brief This function clears a specific event.

  @param[in] Event is the event to be clear.
  */
void QSOSAL_ClearEvent(Event_t Event)
{
    if(Event != NULL)
    {
        qurt_signal_clear((qurt_signal_t *)Event, 0x01);
    }
}

/**
  @brief This function deletes a specific event.

  @param[in] Event is the event to be deleted.
  */
void QSOSAL_CloseEvent(Event_t Event)
{
    if(Event != NULL)
    {
        qurt_signal_destroy((qurt_signal_t *)Event);
        QSOSAL_FreeMemory(Event);
    }
}

/**

  @brief This function creates a mail box object.

  @param[in] Mailbox_Slot is the number of the slots in the mail box.
  @param[in] Mailbox_Slot_Size is the size of the slot in the mail box.

  @return
  Pointer to the mail box object cretaed on success.
  NULL if it is failed to create the mail box object.
  */
Mailbox_t QSOSAL_CreateMailbox(unsigned int Number_Slots, unsigned int Slot_Size)
{
    Mailbox_t        Ret_Val;
    int32_t          Result;
    qurt_pipe_t      Pipe;
    qurt_pipe_attr_t Pipe_Attribute;

    /* Ensure that the parameters passed in appear valid.                */
    if((Number_Slots > 0) && (Slot_Size > 0))
    {
        /* Create the mailbox. */
        qurt_pipe_attr_init(&Pipe_Attribute);
        qurt_pipe_attr_set_elements(&Pipe_Attribute, Number_Slots);
        qurt_pipe_attr_set_element_size(&Pipe_Attribute, Slot_Size);

        Result = qurt_pipe_create(&Pipe, &Pipe_Attribute);
        if(Result == QURT_EOK)
        {
            Ret_Val = (Mailbox_t)Pipe;
        }
        else
        {
            Ret_Val = NULL;
        }
    }
    else
    {
        Ret_Val = NULL;
    }

    return(Ret_Val);
}

/**
  @brief This function adds a mail (data) into the mail box.

  @param[in] Mailbox is the mail box to be used.
  @param[in] Data is the data to be added into the mail box.

  @return
  true  if the data is add to mail box successfully.
  false if it is failed to add the mail to mail box.
  */
Boolean_t QSOSAL_AddMailbox(Mailbox_t Mailbox, void *MailboxData)
{
    Boolean_t    Ret_Val;
    int32_t      Result;

    if((Mailbox != NULL) && (MailboxData != NULL))
    {
        Result  = qurt_pipe_send_timed((qurt_pipe_t)Mailbox, MailboxData, QURT_TIME_WAIT_FOREVER);
        Ret_Val = (bool)(Result == QURT_EOK);
    }
    else
    {
        Ret_Val = false;
    }

    return(Ret_Val);
}

/**
  @brief This function waits for a mail in the mail box. If the mail is
  already there, this function will return immediately.

  @param[in]  Mailbox is the mail box to be waited.
  @param[in]  Timeout is the waiting time (in milliseconds) for the mail.
  @param[out] Data    is the buffer provided by user where the data in the
  mail box will be stored if the data is available.
  @return
  true  if the if the wait operation is success and the user should check
  the data.
  false if it is failed to wait for the mail box.
  */
Boolean_t QSOSAL_WaitMailbox(Mailbox_t Mailbox, void *MailboxData)
{
    Boolean_t Ret_Val;
    int32_t   Result;

    if((Mailbox != NULL) && (MailboxData != NULL))
    {
        Result  = qurt_pipe_receive_timed((qurt_pipe_t)Mailbox, MailboxData, QURT_TIME_WAIT_FOREVER);

        Ret_Val = (bool)(Result == QURT_EOK);
    }
    else
    {
        Ret_Val = false;
    }

    return(Ret_Val);
}

/**
  @brief This function deletes a mail object.

  @param[in]  Mailbox is the mail box to be deleted.
  */
void QSOSAL_DeleteMailbox(Mailbox_t Mailbox, QSOSAL_MailboxDeleteCallback_t MailboxDeleteCallback)
{
    if(Mailbox != NULL)
    {
        qurt_pipe_delete((qurt_pipe_t)Mailbox);
    }
}

/**
  @brief This function returns the current system ticks.

  @return
  The current system ticks.
  */
uint32_t QSOSAL_GetSystemTicks(void)
{
    return((uint32_t)(qurt_timer_get_ticks()));
}

/**
  @brief This function converts ticks to milliseconds.

  @param Ticks is the tick value to be converted.

  @return
  The time in milliseconds represented by the provided tick value.
  */
uint32_t QSOSAL_TicksToMilliseconds(uint32_t Ticks)
{
    return((uint32_t)qurt_timer_convert_ticks_to_time((qurt_time_t)Ticks, QURT_TIME_MSEC));
}

/**
  @brief This function will delay a task for the specified duration.

  @param[in] MilliSeconds is the time for the task to be delayed.
  */
void QSOSAL_Delay(uint32_t MilliSeconds)
{
    /* Verify that the input parameter is valid. */
    if(MilliSeconds)
    {
        qurt_thread_sleep((qurt_time_t)QSOSAL_MillisecondsToTicks(MilliSeconds));
    }
}

/**
  @brief This function initialize the OS abstraction layer and should be
  called before using any other APIs in OS abstraction layer.
  */
void QSOSAL_Init(void *UserParam)
{

}

/**
  @brief This function shuts down the OS abstraction layer.
  */
void QSOSAL_Cleanup(void)
{

}

