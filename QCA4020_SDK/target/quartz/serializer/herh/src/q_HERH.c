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

#include "qapi_HERH.h"
#include "q_HERH.h"
#include "OSAL.h"

#define EVENT_FLAG_MASK             (0x00FFFFFF)

typedef struct HERH_Response_s
{
   struct HERH_Response_s *NextEntry;
   uint32_t                EventFlag;
   uint8_t                *Data;
   uint32_t                DataLength;
} HERH_Response_t;

typedef struct HERH_Context_s
{
   OSAL_Mutex_t     Mutex;
   OSAL_Event_t     Event;
   uint32_t         FreeEventMask;
   HERH_Response_t *ResponseList;
} HERH_Context_t;

static HERH_Context_t *HERH_Context;

static bool HERH_Initialize(void);
static uint32_t HERH_AllocateEventFlag(void);
static void HERH_FreeEventFlag(uint32_t EventFlag);
static HERH_Response_t *HERH_GetResponse(HERH_Handle_t HERH_Handle);

static bool HERH_Initialize(void)
{
   bool Ret_Val;

   HERH_Context = OSAL_Malloc(sizeof(HERH_Context_t));
   if(HERH_Context != NULL)
   {
      /* Set the HERH_Context to a known state. */
      OSAL_Memset(HERH_Context, 0, sizeof(HERH_Context_t));

      /* Initialize the FreeEventMask. */
      HERH_Context->FreeEventMask = 0xFFFFFFFF;

      /* Create the mutex. */
      HERH_Context->Mutex = OSAL_Create_Mutex();
      if(HERH_Context->Mutex != NULL)
      {
         /* Create the event. */
         HERH_Context->Event = OSAL_Create_Event();
         if(HERH_Context->Event != NULL)
         {
            Ret_Val = true;
         }
         else
         {
            Ret_Val = false;
         }
      }
      else
      {
         Ret_Val = false;
      }
   }
   else
   {
      Ret_Val = false;
   }

   return(Ret_Val);
}

static uint32_t HERH_AllocateEventFlag(void)
{
   uint32_t RetVal;

   for(RetVal = 1; RetVal != 0; RetVal = RetVal << 1)
   {
      if(RetVal & HERH_Context->FreeEventMask)
      {
         break;
      }
   }

   if(RetVal)
   {
      HERH_Context->FreeEventMask &= ~RetVal;
      OSAL_Clear_Event(HERH_Context->Event, RetVal);
   }

   return(RetVal);
}

static void HERH_FreeEventFlag(uint32_t EventFlag)
{
   HERH_Context->FreeEventMask |= EventFlag;
   OSAL_Clear_Event(HERH_Context->Event, EventFlag);
}

static HERH_Response_t *HERH_GetResponse(HERH_Handle_t HERH_Handle)
{
   HERH_Response_t *Ret_Val;
   HERH_Response_t *CurrentEntry;

   if(HERH_Handle != NULL)
   {
      CurrentEntry = HERH_Context->ResponseList;
      while((CurrentEntry != NULL) && (CurrentEntry != (HERH_Response_t *)HERH_Handle))
      {
         CurrentEntry = CurrentEntry->NextEntry;
      }

      Ret_Val = CurrentEntry;
   }
   else
   {
      Ret_Val = NULL;
   }

   return(Ret_Val);
}

/**
   @brief Initializes an event response handler. This should be called before
          the event is sent to the host that will expect a response.

   @return The handle for the response handler or NULL if there was an error.
*/
HERH_Handle_t HERH_Init_Response(void)
{
   HERH_Handle_t    Ret_Val;
   HERH_Response_t *NewEntry;
   HERH_Response_t *CurrentEntry;

   if((HERH_Context != NULL) || (HERH_Initialize()))
   {
      /* Take the mutex. */
      if(OSAL_Wait_Mutex(HERH_Context->Mutex, OSAL_WAIT_TIME_INFINITE))
      {
         /* Allocate a new response. */
         NewEntry = OSAL_Malloc(sizeof(HERH_Response_t));
         if(NewEntry != NULL)
         {
            /* Set the response entry to a known state. */
            OSAL_Memset(NewEntry, 0, sizeof(HERH_Response_t));

            NewEntry->EventFlag = HERH_AllocateEventFlag();
            if(NewEntry->EventFlag != 0)
            {
               /* Add the entry to response list. */
               CurrentEntry = HERH_Context->ResponseList;
               if(HERH_Context->ResponseList != NULL)
               {
                  /* Add the new entry to the end of the list. */
                  while(CurrentEntry->NextEntry != NULL)
                  {
                     CurrentEntry = CurrentEntry->NextEntry;
                  }

                  CurrentEntry->NextEntry = NewEntry;
               }
               else
               {
                  /* List is empty. */
                  HERH_Context->ResponseList = NewEntry;
               }

               Ret_Val = (HERH_Handle_t)(NewEntry);
            }
            else
            {
               Ret_Val = NULL;
            }

            if(Ret_Val == NULL)
            {
               if(NewEntry->EventFlag != 0)
               {
                  HERH_FreeEventFlag(NewEntry->EventFlag);
               }

               OSAL_Free(NewEntry);
            }
         }
         else
         {
            Ret_Val = NULL;
         }

         /* Release the mutex. */
         OSAL_Release_Mutex(HERH_Context->Mutex);
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
   @brief Waits for an event response from the host and provides the data when
          it arrives.

   @param[in]  HERH_Handle Handle returned by HERH_Init_Response.
   @param[in]  TimeOut     Time in milliseconds to wait for the response.
   @param[out] DataLength  Size of the buffer for the recieved response if
                           successful.
   @param[out] Data        Data for the received response if successful.

   @return true if the wait was successful or false if it timed out.
*/
qbool_t HERH_Wait_Response(HERH_Handle_t HERH_Handle, uint32_t TimeOut, uint32_t *DataLength, uint8_t **Data)
{
   HERH_Response_t *Response;
   qbool_t          Ret_Val;
   qbool_t          Result;
   uint32_t         Wait_Result;

   if((HERH_Context != NULL) && (DataLength != NULL) && (*Data == NULL))
   {
      /* Take the mutex. */
      if(OSAL_Wait_Mutex(HERH_Context->Mutex, OSAL_WAIT_TIME_INFINITE))
      {
         Response = HERH_GetResponse(HERH_Handle);
         if(Response != NULL)
         {
            /* The entry is found and set up the event wait condition. */
            Wait_Result = 0;
            Result = OSAL_Wait_Event(HERH_Context->Event, Response->EventFlag, TimeOut, &Wait_Result);
            if((Result) && (Wait_Result & Response->EventFlag))
            {
               *DataLength = Response->DataLength;
               *Data       = Response->Data;

               Ret_Val = true;
            }
            else
            {
               Ret_Val = false;
            }
         }
         else
         {
            Ret_Val = false;
         }

         /* Release the mutex. */
         OSAL_Release_Mutex(HERH_Context->Mutex);
      }
      else
      {
         Ret_Val = false;
      }
   }
   else
   {
      Ret_Val = false;
   }

   return(Ret_Val);
}

/**
   @brief Cleans up the response handler, including the received buffer. This
          should be called when the event handler is done.

   @param[in] Handle Handle returned by HERH_Init_Response.
*/
void HERH_Cleanup_Response(HERH_Handle_t HERH_Handle)
{
   HERH_Response_t *CurrentEntry;
   HERH_Response_t *EntryToRemove;

   if(HERH_Context != NULL)
   {
      /* Take the mutex. */
      if(OSAL_Wait_Mutex(HERH_Context->Mutex, OSAL_WAIT_TIME_INFINITE))
      {
         EntryToRemove = HERH_GetResponse(HERH_Handle);
         if(EntryToRemove != NULL)
         {
            /* Remove the entry from the list. */
            if(HERH_Context->ResponseList != NULL)
            {
               if(HERH_Context->ResponseList == EntryToRemove)
               {
                  HERH_Context->ResponseList = HERH_Context->ResponseList->NextEntry;
               }
               else
               {
                  CurrentEntry = HERH_Context->ResponseList;
                  while((CurrentEntry->NextEntry != NULL) && (CurrentEntry->NextEntry != EntryToRemove))
                  {
                     CurrentEntry = CurrentEntry->NextEntry;
                  }

                  if(CurrentEntry->NextEntry != NULL)
                  {
                     CurrentEntry = CurrentEntry->NextEntry->NextEntry;
                  }
               }

               if(EntryToRemove->Data != NULL)
               {
                  OSAL_Free(EntryToRemove->Data);
               }

               HERH_FreeEventFlag(EntryToRemove->EventFlag);
               OSAL_Free(EntryToRemove);
            }
         }

         /* Release the mutex. */
         OSAL_Release_Mutex(HERH_Context->Mutex);
      }
   }
}

/**
   @brief Funtion used to handle the data from the host side.

   This function will receive the data from host side and set the data arriving
   event. So a callback funtion blocking on this event will handle the data
   accordingly.

   @param[in] HERH_Handle Handle returned by HERH_Init_Response.
   @param[in] DataLength  Length of the data for the response.
   @param[in] Data        Data for the response.

   @return
     - QAPI_OK if ZigBee was initialized successfully.
     - A negative value if there was an error.
*/
void qapi_HEHR_Host_Data(HERH_Handle_t HERH_Handle, uint32_t DataLength, const uint8_t *Data)
{
   HERH_Response_t *Response;

   if((HERH_Context != NULL) && ((DataLength == 0) || (Data != NULL)))
   {
      Response = HERH_GetResponse(HERH_Handle);
      if(Response != NULL)
      {
         if(DataLength != 0)
         {
            Response->DataLength = DataLength;
            Response->Data       = OSAL_Malloc(DataLength);
            if(Response->Data != NULL)
            {
               OSAL_Memscpy(Response->Data, DataLength, Data, DataLength);

               /* Set the event. */
               OSAL_Set_Event(HERH_Context->Event, Response->EventFlag);
            }
         }
      }
   }
}

