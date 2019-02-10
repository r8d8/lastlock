/*****< QSOSAL.c >*************************************************************/
/*      Copyright 2000 - 2014 Stonestreet One.                                */
/*      All Rights Reserved.                                                  */
/*                                                                            */
/*  QSOSAL - Stonestreet One Bluetooth Stack Kernel Implementation for        */
/*             Windows (WIN32).                                               */
/*                                                                            */
/*  Author:  Damon Lange                                                      */
/*                                                                            */
/*** MODIFICATION HISTORY *****************************************************/
/*                                                                            */
/*   mm/dd/yy  F. Lastname    Description of Modification                     */
/*   --------  -----------    ------------------------------------------------*/
/*   05/30/01  D. Lange       Initial creation.                               */
/*   12/18/01  R. Sledge      Port to Linux                                   */
/*   02/05/08  D. Wooldridge  Incorporate functions security module requires  */
/*   10/24/17  R. McCord      Added replacements for banned functions.        */
/******************************************************************************/
#include <windows.h>
#include <windowsx.h>
#include <stdint.h>

#include "qsOSAL.h"      /* QSOSAL Kernel Prototypes/Constants.               */

/* In case the compiler does not support exception handling, define  */
/* the exception handling to do nothing.                             */
#ifndef __QSOSALTRY

#define __QSOSALTRY                __try

#endif

#ifndef __QSOSALEXCEPT

#define __QSOSALEXCEPT(_x)         __except(_x)

#endif

/* The following constant allows QSOSAL Kernel safe function         */
/* implementations to use CRT functions.                             */
/* * NOTE * If QSOSAL_KERNEL_USE_C_RUN_TIME_IMPLEMENTATION is defined*/
/*          and set to 1, then the QSOSAL Kernel safe functions will */
/*          use an implementation that uses CRT functions. If NOT    */
/*          defined or set to 0, then the QSOSAL Kernel safe         */
/*          functions will use an implementation without CRT         */
/*          functions. This functionality has been primarily provided*/
/*          since static analysis will flag some CRT functions as    */
/*          banned functions.                                        */
#ifndef QSOSAL_KERNEL_USE_C_RUN_TIME_IMPLEMENTATION
#define QSOSAL_KERNEL_USE_C_RUN_TIME_IMPLEMENTATION     1
#endif

/* The following constant defines the maximum number of characters   */
/* that may be output by the QSOSAL_OutputMessage() function.        */
#ifndef QSOSAL_KERNEL_MAX_OUTPUT_MESSAGE_LENGTH
#define QSOSAL_KERNEL_MAX_OUTPUT_MESSAGE_LENGTH         127
#endif

/* The following definition is the Windows Message ID of the Windows */
/* Message that is used to post messages to a mailbox that is backed */
/* by Windows Message Queues instead of the generic Mailbox          */
/* implementation.                                                   */
#define WINDOWS_MESSAGE_QUEUE_MESSAGE_ID                 (WM_USER + 1000)

/* The following structure is a container structure that exists to   */
/* map the OS Thread Function to the QSOSAL Kernel Thread Function   */
/* (it doesn't totally map in a one to one relationship/mapping).    */
typedef struct _tagThreadWrapperInfo_t
{
    Thread_t  ThreadFunction;
    void     *ThreadParameter;
    HANDLE    ThreadHandle;
} ThreadWrapperInfo_t;

/* The following type declaration represents the entire state        */
/* information for a Mailbox.  This structure is used with all of    */
/* the Mailbox functions contained in this module.                   */
typedef struct _tagMailboxHeader_t
{
    Event_t       Event;
    Mutex_t       Mutex;
    unsigned int  HeadSlot;
    unsigned int  TailSlot;
    unsigned int  OccupiedSlots;
    unsigned int  NumberSlots;
    unsigned int  SlotSize;
    void         *Slots;
    uint32_t       ThreadID;
} MailboxHeader_t;

/* Internal Variables to this Module (Remember that all variables    */
/* declared static are initialized to 0 automatically by the         */
/* compiler as part of standard C/C++).                              */
static unsigned long DebugZoneMask = DEBUG_ZONES;

/* The following constant represents the number of bytes that are    */
/* displayed on an individual line when using the DumpData()         */
/* function.                                                         */
#define MAXIMUM_BYTES_PER_ROW                  (16)

/* Internal Function Prototypes.                                     */
static uint8_t ConsoleWrite(char *Message, int Length);
static DWORD WINAPI ThreadWrapper(void *UserData);

/* The following function is used to send a string of characters to  */
/* the Console or Output device.  The function takes as its first    */
/* parameter a pointer to a string of characters to be output.  The  */
/* second parameter indicates the number of bytes in the character   */
/* string that is to be output.                                      */
static uint8_t ConsoleWrite(char *Message, int Length)
{
    /* Check to make sure that the Debug String appears to be semi-valid.*/
    if((Message) && (Length))
    {
        printf(Message);
    }

    return(0);
}

/* The following function is a function that represents the native   */
/* thread type for the operating system. This function does nothing  */
/* more than to call the QSOSAL Thread function of the specified     */
/* format (parameters/calling convention/etc.). The UserData         */
/* parameter that is passed to this function is a pointer to a       */
/* ThreadWrapperInfo_t structure which will contain the actual QSOSAL*/
/* Thread Information. This function will free this pointer using the*/
/* QSOSAL_FreeMemory() function (which means that the Thread         */
/* Information structure needs to be allocated with the              */
/* QSOSAL_AllocateMemory() function.                                 */
static DWORD WINAPI ThreadWrapper(void *UserData)
{
    DWORD ret_val = 0;

    if(UserData)
    {
        ret_val = (DWORD)((*(((ThreadWrapperInfo_t *)UserData)->ThreadFunction))(((ThreadWrapperInfo_t *)UserData)->ThreadParameter));

        /* If there was a Thread Handle passed to us, make sure we close  */
        /* it as the Thread is finished executing.                        */
        if(((ThreadWrapperInfo_t *)UserData)->ThreadHandle)
            CloseHandle(((ThreadWrapperInfo_t *)UserData)->ThreadHandle);

        QSOSAL_FreeMemory(UserData);
    }

    return(ret_val);
}

/* The following function is responsible for delaying the current    */
/* task for the specified duration (specified in Milliseconds).      */
/* * NOTE * Very small timeouts might be smaller in granularity than */
/*          the system can support !!!!                              */
void QSOSAL_Delay(unsigned long MilliSeconds)
{
    /* Simply wrap the OS supplied Sleep/Delay function.                 */
    Sleep(MilliSeconds);
}

/* The following function is responsible for creating an actual Mutex*/
/* (Binary Semaphore). The Mutex is unique in that if a Thread       */
/* already owns the Mutex, and it requests the Mutex again it will be*/
/* granted the Mutex. This is in Stark contrast to a Semaphore that  */
/* will block waiting for the second acquisition of the Sempahore.   */
/* This function accepts as input whether or not the Mutex is        */
/* initially Signalled or not. If this input parameter is TRUE then  */
/* the caller owns the Mutex and any other threads waiting on the    */
/* Mutex will block. This function returns a NON-NULL Mutex Handle if*/
/* the Mutex was successfully created, or a NULL Mutex Handle if the */
/* Mutex was NOT created. If a Mutex is successfully created, it can */
/* only be destroyed by calling the QSOSAL_CloseMutex() function (and*/
/* passing the returned Mutex Handle).                               */
Mutex_t QSOSAL_CreateMutex(Boolean_t CreateOwned)
{
    Mutex_t ret_val;

    /* Simply wrap the OS supplied Create Mutex function.                */
    ret_val = (Mutex_t)CreateMutex(NULL, (BOOLEAN)CreateOwned, NULL);

    return(ret_val);
}

/* The following function is responsible for waiting for the         */
/* specified Mutex to become free. This function accepts as input the*/
/* Mutex Handle to wait for, and the Timeout (specified in           */
/* Milliseconds) to wait for the Mutex to become available. This     */
/* function returns TRUE if the Mutex was successfully acquired and  */
/* FALSE if either there was an error OR the Mutex was not acquired  */
/* in the specified Timeout. It should be noted that Mutexes have the*/
/* special property that if the calling Thread already owns the Mutex*/
/* and it requests access to the Mutex again (by calling this        */
/* function and specifying the same Mutex Handle) then it will       */
/* automatically be granted the Mutex. Once a Mutex has been granted */
/* successfully (this function returns TRUE), then the caller MUST   */
/* call the QSOSAL_ReleaseMutex() function.                          */
/* * NOTE * There must exist a corresponding QSOSAL_ReleaseMutex()   */
/*          function call for EVERY successful QSOSAL_WaitMutex()    */
/*          function call or a deadlock will occur in the system !!! */
Boolean_t QSOSAL_WaitMutex(Mutex_t Mutex, unsigned long Timeout)
{
    Boolean_t ret_val;

    /* Simply wrap the OS supplied Wait Mutex function.                  */
    if(WaitForSingleObject((HANDLE)Mutex, Timeout) == WAIT_OBJECT_0)
        ret_val = TRUE;
    else
        ret_val = FALSE;

    return(ret_val);
}

/* The following function is responsible for releasing a Mutex that  */
/* was successfully acquired with the QSOSAL_WaitMutex() function.   */
/* This function accepts as input the Mutex that is currently owned. */
/* * NOTE * There must exist a corresponding QSOSAL_ReleaseMutex()   */
/*          function call for EVERY successful QSOSAL_WaitMutex()    */
/*          function call or a deadlock will occur in the system !!! */
void QSOSAL_ReleaseMutex(Mutex_t Mutex)
{
    /* Simply wrap the OS supplied Release Mutex function.               */
    ReleaseMutex((HANDLE)Mutex);
}

/* The following function is responsible for destroying a Mutex that */
/* was created successfully via a successful call to the             */
/* QSOSAL_CreateMutex() function. This function accepts as input the */
/* Mutex Handle of the Mutex to destroy. Once this function is       */
/* completed the Mutex Handle is NO longer valid and CANNOT be used. */
/* Calling this function will cause all outstanding                  */
/* QSOSAL_WaitMutex() functions to fail with an error.               */
void QSOSAL_CloseMutex(Mutex_t Mutex)
{
    /* Simply wrap the OS supplied Close Mutex function.                 */
    CloseHandle((HANDLE)Mutex);
}

/* The following function is responsible for creating an actual      */
/* Event. The Event is unique in that it only has two states. These  */
/* states are Signalled and Non-Signalled. Functions are provided to */
/* allow the setting of the current state and to allow the option of */
/* waiting for an Event to become Signalled. This function accepts as*/
/* input whether or not the Event is initially Signalled or not. If  */
/* this input parameter is TRUE then the state of the Event is       */
/* Signalled and any QSOSAL_WaitEvent() function calls will          */
/* immediately return. This function returns a NON-NULL Event Handle */
/* if the Event was successfully created, or a NULL Event Handle if  */
/* the Event was NOT created. If an Event is successfully created, it*/
/* can only be destroyed by calling the QSOSAL_CloseEvent() function */
/* (and passing the returned Event Handle).                          */
Event_t QSOSAL_CreateEvent(Boolean_t CreateSignalled)
{
    Event_t ret_val;

    /* Simply wrap the OS supplied Create Event function.                */
    ret_val = (Event_t)CreateEvent(NULL, TRUE, (BOOLEAN)CreateSignalled, NULL);

    return(ret_val);
}

/* The following function is responsible for waiting for the         */
/* specified Event to become Signalled. This function accepts as     */
/* input the Event Handle to wait for, and the Timeout (specified in */
/* Milliseconds) to wait for the Event to become Signalled. This     */
/* function returns TRUE if the Event was set to the Signalled State */
/* (in the Timeout specified) or FALSE if either there was an error  */
/* OR the Event was not set to the Signalled State in the specified  */
/* Timeout. It should be noted that Signalls have a special property */
/* in that multiple Threads can be waiting for the Event to become   */
/* Signalled and ALL calls to QSOSAL_WaitEvent() will return TRUE    */
/* whenever the state of the Event becomes Signalled.                */
Boolean_t QSOSAL_WaitEvent(Event_t Event, unsigned long Timeout)
{
    Boolean_t ret_val;

    /* Simply wrap the OS supplied Wait Event function.                  */
    if(WaitForSingleObject((HANDLE)Event, Timeout) == WAIT_OBJECT_0)
        ret_val = TRUE;
    else
        ret_val = FALSE;

    return(ret_val);
}

/* The following function is responsible for changing the state of   */
/* the specified Event to the Non-Signalled State. Once the Event is */
/* in this State, ALL calls to the QSOSAL_WaitEvent() function will  */
/* block until the State of the Event is set to the Signalled State. */
/* This function accepts as input the Event Handle of the Event to   */
/* set to the Non-Signalled State.                                   */
void QSOSAL_ResetEvent(Event_t Event)
{
    /* Simply wrap the OS supplied Reset Event function.                 */
    ResetEvent((HANDLE)Event);
}

/* The following function is responsible for changing the state of   */
/* the specified Event to the Signalled State. Once the Event is in  */
/* this State, ALL calls to the QSOSAL_WaitEvent() function will     */
/* return. This function accepts as input the Event Handle of the    */
/* Event to set to the Signalled State.                              */
void QSOSAL_SetEvent(Event_t Event)
{
    /* Simply wrap the OS supplied Set Event function.                   */
    SetEvent((HANDLE)Event);
}

/* The following function is responsible for destroying an Event that*/
/* was created successfully via a successful call to the             */
/* QSOSAL_CreateEvent() function. This function accepts as input the */
/* Event Handle of the Event to destroy. Once this function is       */
/* completed the Event Handle is NO longer valid and CANNOT be used. */
/* Calling this function will cause all outstanding                  */
/* QSOSAL_WaitEvent() functions to fail with an error.               */
void QSOSAL_CloseEvent(Event_t Event)
{
    /* Simply wrap the OS supplied Close Event function.                 */
    CloseHandle((HANDLE)Event);
}

/* The following function is provided to allow a mechanism to        */
/* actually allocate a Block of Memory (of at least the specified    */
/* size).  This function accepts as input the size (in Bytes) of the */
/* Block of Memory to be allocated.  This function returns a NON-NULL*/
/* pointer to this Memory Buffer if the Memory was successfully      */
/* allocated, or a NULL value if the memory could not be allocated.  */
void *QSOSAL_AllocateMemory(unsigned long MemorySize)
{
    void *ret_val;

    volatile unsigned int X = 0;

    X++;

    /* Simply wrap the OS supplied memory allocation function.           */
    ret_val = GlobalAllocPtr(GMEM_FIXED, MemorySize);

    return(ret_val);
}

/* The following function is responsible for de-allocating a Block of*/
/* Memory that was successfully allocated with the                   */
/* QSOSAL_AllocateMemory() function. This function accepts a NON-NULL*/
/* Memory Pointer which was returned from the QSOSAL_AllocateMemory()*/
/* function. After this function completes the caller CANNOT use ANY */
/* of the Memory pointed to by the Memory Pointer.                   */
void QSOSAL_FreeMemory(void *MemoryPointer)
{
    volatile unsigned int X = 0;

    X++;

    /* Before proceeding any further we need to make sure that the       */
    /* parameters that were passed to us appear semi-valid.              */
    if(MemoryPointer)
        GlobalFreePtr(MemoryPointer);
}

/* The following function is responsible for copying a block of      */
/* memory of the specified size from the specified source pointer to */
/* the specified destination memory pointer. This function accepts as*/
/* input a pointer to the memory block that is to be Destination     */
/* Buffer (first parameter), a pointer to memory block that points to*/
/* the data to be copied into the destination buffer, and the size   */
/* (in bytes) of the Data to copy. The Source and Destination Memory */
/* Buffers must contain AT LEAST as many bytes as specified by the   */
/* Size parameter.                                                   */
/* ** NOTE ** This function is deprecated and should NOT be used.    */
/*            This function has been replaced by the                 */
/*            QSOSAL_MemCopy_S() function.                           */
/* * NOTE * This function does not allow the overlapping of the      */
/*          Source and Destination Buffers !!!!                      */
void QSOSAL_MemCopy(void *Destination, const void *Source, unsigned long Size)
{
    /* Simply wrap the C Run-Time memcpy() function.                     */
    memcpy(Destination, Source, Size);
}

/* The following function is responsible for copying a block of      */
/* memory of the specified size from the specified source pointer to */
/* the specified destination memory pointer. The first parameter to  */
/* this function is a pointer to the destination buffer. The second  */
/* parameter is the size of the destination buffer. The third        */
/* parameter is a pointer to the source buffer. The final parameter  */
/* is the number of bytes to copy from the source buffer to the      */
/* destination buffer.                                               */
/* * NOTE * It is the caller's responsibility to make sure that the  */
/*          input parameters are valid.                              */
/* * NOTE * This function does NOT allow overlapping of the source   */
/*          and destination buffers. If this functionality is        */
/*          required, then the QSOSAL_MemMove_S() function MUST be   */
/*          used.                                                    */
void QSOSAL_MemCopy_S(void *Destination, unsigned long DestSize, const void *Source, unsigned long Count)
{
#if (!QSOSAL_KERNEL_USE_C_RUN_TIME_IMPLEMENTATION)
    uint8_t *_Destination;
    uint8_t *_Source;
#endif

    /* Make sure the input parameters are valid.                         */
    if((Destination) && (DestSize) && (Source) && (Count) && ((size_t)Destination != (size_t)Source) && (Count <= DestSize))
    {

#if QSOSAL_KERNEL_USE_C_RUN_TIME_IMPLEMENTATION

        /* Simply wrap the C Run-Time memcpy() function.                  */
        memcpy(Destination, Source, (size_t)Count);

#else

        /* Store the destination and source as byte pointers.             */
        /* * NOTE * This has been done to enforce consistency across      */
        /*          platforms and prevent void pointer issues that may or */
        /*          may not occur depending on the platform.              */
        _Destination = (uint8_t *)Destination;
        _Source      = (uint8_t *)Source;

        /* Copy the data from the source buffer into the destination      */
        /* buffer.                                                        */
        while(Count--)
        {
            *_Destination++ = *_Source++;
        }

#endif

    }
}

/* The following function is responsible for moving a block of memory*/
/* of the specified size from the specified source pointer to the    */
/* specified destination memory pointer. This function accepts as    */
/* input a pointer to the memory block that is to be Destination     */
/* Buffer (first parameter), a pointer to memory block that points to*/
/* the data to be copied into the destination buffer, and the size   */
/* (in bytes) of the Data to copy. The Source and Destination Memory */
/* Buffers must contain AT LEAST as many bytes as specified by the   */
/* Size parameter.                                                   */
/* ** NOTE ** This function is deprecated and should NOT be used.    */
/*            This function has been replaced by the                 */
/*            QSOSAL_MemMove_S() function.                           */
/* * NOTE * This function DOES allow the overlapping of the Source   */
/*          and Destination Buffers.                                 */
void QSOSAL_MemMove(void *Destination, const void *Source, unsigned long Size)
{
    /* Simply wrap the C Run-Time memmove() function.                    */
    memmove(Destination, Source, Size);
}

/* The following function is responsible for moving a block of memory*/
/* of the specified size from the specified source pointer to the    */
/* specified destination memory pointer. The first parameter to this */
/* function is a pointer to the destination buffer. The second       */
/* parameter is the size of the destination buffer. The third        */
/* parameter is a pointer to the source buffer. The final parameter  */
/* is the number of bytes to copy from the source buffer to the      */
/* destination buffer. This function returns TRUE if the move was    */
/* successful. Otherwise FALSE is returned.                          */
/* * NOTE * It is the caller's responsibility to make sure that the  */
/*          input parameters are valid.                              */
/* * NOTE * This function DOES allow overlapping of the source and   */
/*          destination buffers. If the source and destination       */
/*          buffers do NOT overlap, then the user should call the    */
/*          QSOSAL_MemCopy_S() function.                             */
void QSOSAL_MemMove_S(void *Destination, unsigned long DestSize, const void *Source, unsigned long Count)
{
#if (!QSOSAL_KERNEL_USE_C_RUN_TIME_IMPLEMENTATION)
    uint8_t *_Destination;
    uint8_t *_Source;
#endif

    /* Make sure the input parameters are valid.                         */
    if((Destination) && (DestSize) && (Source) && (Count) && ((size_t)Destination != (size_t)Source) && (Count <= DestSize))
    {

#if QSOSAL_KERNEL_USE_C_RUN_TIME_IMPLEMENTATION

        /* Simply wrap the C Run-Time memmove() function.                 */
        memmove(Destination, Source, (size_t)Count);

#else

        /* Store the destination and source as byte pointers.             */
        /* * NOTE * This has been done to enforce consistency across      */
        /*          platforms and prevent void pointer issues that may or */
        /*          may not occur depending on the platform.              */
        _Destination = (uint8_t *)Destination;
        _Source      = (uint8_t *)Source;

        /* Check to see if the source buffer overlaps the destination     */
        /* buffer.                                                        */
        /* * NOTE * If this is the case, then copying the data in the     */
        /*          forward direction will overwrite data before it is    */
        /*          copied. Therefore, we will copy the data in the       */
        /*          reverse direction to prevent overwriting the data.    */
        if(((size_t)_Destination > (size_t)_Source) && ((size_t)_Source + Count >= (size_t)_Destination))
        {
            /* Set the Source and Destination buffer addresses to the last */
            /* byte that would have been copied in the forward direction.  */
            _Source      += (Count - 1);
            _Destination += (Count - 1);

            /* Copy the data from the Source buffer into the Destination   */
            /* buffer.                                                     */
            while(Count--)
            {
                *_Destination-- = *_Source--;
            }
        }
        else
        {
            /* Copy the data from the Source buffer into the Destination   */
            /* buffer.                                                     */
            while(Count--)
            {
                *_Destination++ = *_Source++;
            }
        }

#endif

    }
}

/* The following function is provided to allow a mechanism to fill   */
/* a block of memory with the specified value.  This function accepts*/
/* as input a pointer to the Data Buffer (first parameter) that is   */
/* to filled with the specified value (second parameter).  The       */
/* final parameter to this function specifies the number of bytes    */
/* that are to be filled in the Data Buffer.  The Destination        */
/* Buffer must point to a Buffer that is AT LEAST the size of        */
/* the Size parameter.                                               */
void QSOSAL_MemInitialize(void *Destination, unsigned char Value, unsigned long Size)
{
    /* Simply wrap the C Run-Time memset() function.                     */
    memset(Destination, Value, Size);
}

/* The following function is provided to allow a mechanism to        */
/* Compare two blocks of memory to see if the two memory blocks      */
/* (each of size Size (in bytes)) are equal (each and every byte up  */
/* to Size bytes).  This function returns a negative number if       */
/* Source1 is less than Source2, zero if Source1 equals Source2, and */
/* a positive value if Source1 is greater than Source2.              */
int QSOSAL_MemCompare(const void *Source1, const void *Source2, unsigned long Size)
{
    /* Simply wrap the C Run-Time memcmp() function.                     */
    return(memcmp(Source1, Source2, Size));
}

/* The following function is provided to allow a mechanism to Compare*/
/* two blocks of memory to see if the two memory blocks (each of size*/
/* Size (in bytes)) are equal (each and every byte up to Size bytes) */
/* using a Case-Insensitive Compare.  This function returns a        */
/* negative number if Source1 is less than Source2, zero if Source1  */
/* equals Source2, and a positive value if Source1 is greater than   */
/* Source2.                                                          */
int QSOSAL_MemCompareI(const void *Source1, const void *Source2, unsigned long Size)
{
#ifdef _MSC_VER
    return(_memicmp(Source1, Source2, Size));
#else
    return(memicmp(Source1, Source2, Size));
#endif
}

/* The following function is provided to allow a mechanism to copy a */
/* source NULL Terminated ASCII (character) string to the specified  */
/* Destination String Buffer. The first parameter is a pointer to the*/
/* destination buffer string. The second parameter is a pointer to   */
/* the source NULL Terminated ASCII (character) string. The final    */
/* parameter is the size of the destination buffer.                  */
/* * NOTE * It is the caller's responsibility to make sure that the  */
/*          input parameters are valid.                              */
/* * NOTE * This function guarantees that the destination buffer     */
/*          string has been NULL terminated provided that the        */
/*          destination buffer is valid and has room for the NULL    */
/*          terminator.                                              */
void QSOSAL_StringCopy_S(char *Destination, unsigned long DestSize, const char *Source)
{
#ifdef _MSC_VER

    /* Simply wrap the C Run-Time strcpy_s() function.                   */
    strcpy_s(Destination, (size_t)DestSize, Source);

#else

#if (!QSOSAL_KERNEL_USE_C_RUN_TIME_IMPLEMENTATION)
    unsigned long SourceLength;
#endif

    /* Make sure the input parameters are valid.                         */
    if((Destination) && (Source) && (DestSize) && ((size_t)Destination != (size_t)Source))
    {

#if QSOSAL_KERNEL_USE_C_RUN_TIME_IMPLEMENTATION

        /* If the length of the source string is greater than or equal to */
        /* the length of the destination buffer, then the source string   */
        /* will be truncated.                                             */
        if(strlen(Source) >= DestSize)
        {
            /* Use the C Run-Time memcpy() function to copy the truncated  */
            /* source string to the destination buffer.                    */
            /* * NOTE * We cannot modify the source string since it is     */
            /*          constant.                                          */
            memcpy(Destination, Source, (DestSize - 1));
            Destination[DestSize - 1] = '\0';
        }
        else
        {
            /* Simply wrap the C Run-Time strcpy() function.               */
            strcpy(Destination, Source);
        }

#else

        /* If the source string length is greater than or equal to the    */
        /* length of the destination buffer, then the source string will  */
        /* be truncated.                                                  */
        if((SourceLength = strlen(Source)) >= DestSize)
        {
            /* Set the remaining length of the destination buffer to the   */
            /* position of the NULL terminator.                            */
            DestSize--;
        }
        else
        {
            /* Set the remaining length of the destination buffer to the   */
            /* position of the NULL terminator.                            */
            DestSize = SourceLength;
        }

        /* Set the NULL terminator.                                       */
        Destination[DestSize] = '\0';

        /* While there is room in the destination buffer, copy the source */
        /* string to the destination buffer.                              */
        while(DestSize--)
        {
            *(Destination++) = *(Source++);
        }

#endif

    }
    else
    {
        /* If the destination buffer is valid, make sure that it is NULL  */
        /* terminated.                                                    */
        if((Destination) && (DestSize))
        {
            Destination[0] = '\0';
        }
    }

#endif
}

/* The following function is provided to allow a mechanism to        */
/* determine the Length (in characters) of the specified NULL        */
/* Terminated ASCII (character) String.  This function accepts as    */
/* input a pointer to a NULL Terminated ASCII String and returns     */
/* the number of characters present in the string (NOT including     */
/* the terminating NULL character).                                  */
unsigned int QSOSAL_StringLength(const char *Source)
{
    /* Simply wrap the C Run-Time strlen() function.                     */
    return((unsigned int)strlen(Source));
}

/* The following function is provided to allow a mechanism to write a*/
/* NULL Terminated ASCII (character) format string to a destination  */
/* NULL Terminated ASCII (character) buffer. The first parameter is a*/
/* pointer to the destination NULL Terminated ASCII (character)      */
/* string. The second parameter is the size of the destination string*/
/* buffer. The third parameter is a pointer to the NULL Terminated   */
/* ASCII (character) format string. The final parameter holds the    */
/* arguments for the format string. If successful, this function     */
/* returns the length of the destination string. Otherwise a negative*/
/* value is returned, which represents an error.                     */
/* * NOTE * It is the caller's responsibility to make sure that the  */
/*          input parameters are valid.                              */
/* * NOTE * This function guarantees that the destination buffer     */
/*          string has been NULL terminated provided that the        */
/*          destination buffer is valid and has room for the NULL    */
/*          terminator.                                              */
int QSOSAL_SprintF_S(char *Destination, unsigned long DestSize, const char *Format, ...)
{
    int     ret_val;
    va_list args;

    va_start(args, Format);

    /* Simply wrap the C Run-Time vsnprintf_s() function.                */
    /* * NOTE * _TRUNCATE informs vsnprintf_S() to write as many         */
    /*          characters that can be written to the buffer.            */
#ifdef _MSC_VER
    ret_val = vsnprintf_s(Destination, (size_t)DestSize, _TRUNCATE, Format, args);
#else
#ifdef __BORLANDC__
    ret_val = vsnprintf(Destination, (size_t)DestSize, Format, args);
#else
    ret_val = vsnprintf_s(Destination, (size_t)DestSize, Format, args);
#endif
#endif

    /* Check if the string has been truncated.                           */
    /* * NOTE * vsnprintf_s() returns -1 if the string has been          */
    /*          truncated.                                               */
    if((ret_val == -1) || ((unsigned long)ret_val >= DestSize))
    {
        /* The string has been truncated so the number of characters      */
        /* written is the maximum that can be stored by the destination   */
        /* buffer.                                                        */
        Destination[--DestSize] = '\0';
        ret_val                 = DestSize;
    }

    va_end(args);

    return(ret_val);
}

/* The following function is provided to allow a means for the       */
/* programmer to create a seperate thread of execution.  This        */
/* function accepts as input the Function that represents the        */
/* Thread that is to be installed into the system as its first       */
/* parameter.  The second parameter is the size of the Threads       */
/* Stack (in bytes) required by the Thread when it is executing.     */
/* The final parameter to this function represents a parameter that  */
/* is to be passed to the Thread when it is created.  This function  */
/* returns a NON-NULL Thread Handle if the Thread was successfully   */
/* created, or a NULL Thread Handle if the Thread was unable to be   */
/* created.  Once the thread is created, the only way for the Thread */
/* to be removed from the system is for the Thread function to run   */
/* to completion.                                                    */
/* * NOTE * There does NOT exist a function to Kill a Thread that    */
/*          is present in the system.  Because of this, other means  */
/*          needs to be devised in order to signal the Thread that   */
/*          it is to terminate.                                      */
ThreadHandle_t QSOSAL_CreateThread(Thread_t ThreadFunction, unsigned int StackSize, void *ThreadParameter)
{
    ThreadHandle_t       ret_val;
    ThreadWrapperInfo_t *ThreadWrapperInfo;

    /* Wrap the OS Thread Creation function.                             */
    /* * NOTE * Becuase the OS Thread function and the QSOSAL Thread     */
    /*          function are not necessarily the same, we will wrap the  */
    /*          QSOSAL Thread within the real OS thread.                 */
    if(ThreadFunction)
    {
        /* First we need to allocate memory for a ThreadWrapperInfo_t     */
        /* structure to hold the data we are going to pass to the thread. */
        if((ThreadWrapperInfo = (ThreadWrapperInfo_t *)QSOSAL_AllocateMemory(sizeof(ThreadWrapperInfo_t))) != NULL)
        {
            /* Memory allocated, populate the structure with the correct   */
            /* information.                                                */
            ThreadWrapperInfo->ThreadFunction  = ThreadFunction;
            ThreadWrapperInfo->ThreadParameter = ThreadParameter;

            /* * NOTE * We are creating the Thread as suspended.  This is  */
            /*          because we need to pass the thread handle to the   */
            /*          Thread Wrapper so that it can be closed when the   */
            /*          thread exits.  We will simply note the Thread      */
            /*          Handle in the Thread Wrapper Information (returned */
            /*          from CreateThread()) and then simply resume the    */
            /*          thread (i.e.  allow it start running).             */
            ret_val = (ThreadHandle_t)CreateThread(NULL, StackSize, ThreadWrapper, (void *)ThreadWrapperInfo, CREATE_SUSPENDED, NULL);

            if(ret_val)
            {
                ThreadWrapperInfo->ThreadHandle = ret_val;

                ResumeThread(ThreadWrapperInfo->ThreadHandle);
            }
            else
                QSOSAL_FreeMemory(ThreadWrapperInfo);
        }
        else
            ret_val = NULL;
    }
    else
        ret_val = NULL;

    /* Return the result to the caller.                                  */
    return(ret_val);
}

/* The following function is provided to allow a mechanism to        */
/* retrieve the handle of the thread which is currently executing.   */
/* This function require no input parameters and will return a valid */
/* ThreadHandle upon success.                                        */
ThreadHandle_t QSOSAL_CurrentThreadHandle(void)
{
    ThreadHandle_t ret_val;

    /* Simply return the Current Thread Handle that is executing.        */
    ret_val = (ThreadHandle_t)GetCurrentThreadId();

    return(ret_val);
}

/* The following function is provided to allow a mechanism to create */
/* a Mailbox. A Mailbox is a Data Store that contains slots (all of  */
/* the same size) that can have data placed into (and retrieved      */
/* from). Once Data is placed into a Mailbox (via the                */
/* QSOSAL_AddMailbox() function, it can be retreived by using the    */
/* QSOSAL_WaitMailbox() function. Data placed into the Mailbox is    */
/* retrieved in a FIFO method. This function accepts as input the    */
/* Maximum Number of Slots that will be present in the Mailbox and   */
/* the Size of each of the Slots. This function returns a NON-NULL   */
/* Mailbox Handle if the Mailbox is successfully created, or a NULL  */
/* Mailbox Handle if the Mailbox was unable to be created.           */
Mailbox_t QSOSAL_CreateMailbox(unsigned int NumberSlots, unsigned int SlotSize)
{
    MSG              Msg;
    Mailbox_t        ret_val;
    MailboxHeader_t *MailboxHeader;

    /* Before proceeding any further we need to make sure that the       */
    /* parameters that were passed to us appear semi-valid.              */
    if((NumberSlots) && (SlotSize))
    {
        /* Parameters appear semi-valid, so now let's allocate enough     */
        /* Memory to hold the Mailbox Header AND enough space to hold     */
        /* all requested Mailbox Slots.                                   */
        if((MailboxHeader = (MailboxHeader_t *)QSOSAL_AllocateMemory(sizeof(MailboxHeader_t)+(NumberSlots*SlotSize))) != NULL)
        {
            /* Memory successfully allocated so now let's create an        */
            /* Event that will be used to signal when there is Data        */
            /* present in the Mailbox.                                     */
            if((MailboxHeader->Event = QSOSAL_CreateEvent(FALSE)) != NULL)
            {
                /* Event created successfully, now let's create a Mutex     */
                /* that will guard access to the Mailbox Slots.             */
                if((MailboxHeader->Mutex = QSOSAL_CreateMutex(FALSE)) != NULL)
                {
                    /* Everything successfully created, now let's initialize */
                    /* the state of the Mailbox such that it contains NO     */
                    /* Data.                                                 */
                    MailboxHeader->NumberSlots   = NumberSlots;
                    MailboxHeader->SlotSize      = SlotSize;
                    MailboxHeader->HeadSlot      = 0;
                    MailboxHeader->TailSlot      = 0;
                    MailboxHeader->OccupiedSlots = 0;
                    MailboxHeader->Slots         = ((unsigned char *)MailboxHeader) + sizeof(MailboxHeader_t);
                    MailboxHeader->ThreadID      = 0;

                    /* All finished, return success to the caller (the       */
                    /* Mailbox Header).                                      */
                    ret_val                      = (Mailbox_t)MailboxHeader;
                }
                else
                {
                    /* Error creating the Mutex, so let's free the Event     */
                    /* we created, Free the Memory for the Mailbox itself    */
                    /* and return an error to the caller.                    */
                    QSOSAL_CloseEvent(MailboxHeader->Event);

                    QSOSAL_FreeMemory(MailboxHeader);

                    ret_val = NULL;
                }
            }
            else
            {
                /* Error creating the Data Available Event, so let's free   */
                /* the Memory for the Mailbox itself and return an error    */
                /* to the caller.                                           */
                QSOSAL_FreeMemory(MailboxHeader);

                ret_val = NULL;
            }
        }
        else
            ret_val = NULL;
    }
    else
    {
        /* Check to see if the caller has specified zero for both         */
        /* parameters.  This will be a special flag that says we should   */
        /* simply create a Windows Message Queue.                         */
        if((!NumberSlots) && (SlotSize))
        {
            /* Parameters specify Windows Message Queue, so now let's      */
            /* allocate enough Memory to hold the Mailbox Header.          */
            /* * NOTE * We do not need to allocate any Mailbox Slots.      */
            if((MailboxHeader = (MailboxHeader_t *)QSOSAL_AllocateMemory(sizeof(MailboxHeader_t))) != NULL)
            {
                /* Initialize the Mailbox Header to a known state.          */
                QSOSAL_MemInitialize(MailboxHeader, 0, sizeof(MailboxHeader_t));

                /* Note the Size of each individual Slot.                   */
                MailboxHeader->SlotSize = SlotSize;

                /* Next, establish a Message Queue to receive Messages into.*/
                PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE);

                /* Finally, note the Thread ID so that we can Post Messages */
                /* into it.                                                 */
                MailboxHeader->ThreadID = GetCurrentThreadId();

                /* Return All finished, return success to the caller (the   */
                /* Mailbox Header).                                         */
                ret_val = (Mailbox_t)MailboxHeader;
            }
            else
                ret_val = NULL;
        }
        else
            ret_val = NULL;
    }

    /* Return the result to the caller.                                  */
    return(ret_val);
}

/* The following function is provided to allow a means to Add data to*/
/* the Mailbox (where it can be retrieved via the                    */
/* QSOSAL_WaitMailbox() function. This function accepts as input the */
/* Mailbox Handle of the Mailbox to place the data into and a pointer*/
/* to a buffer that contains the data to be added. This pointer      */
/* *MUST* point to a data buffer that is AT LEAST the Size of the    */
/* Slots in the Mailbox (specified when the Mailbox was created) and */
/* this pointer CANNOT be NULL. The data that the MailboxData pointer*/
/* points to is placed into the Mailbox where it can be retrieved via*/
/* the QSOSAL_WaitMailbox() function.                                */
/* * NOTE * This function copies from the MailboxData Pointer the    */
/*          first SlotSize Bytes. The SlotSize was specified when the*/
/*          Mailbox was created via a successful call to the         */
/*          QSOSAL_CreateMailbox() function.                         */
Boolean_t QSOSAL_AddMailbox(Mailbox_t Mailbox, void *MailboxData)
{
    void      *SlotData;
    Boolean_t  ret_val;

    /* Before proceeding any further make sure that the Mailbox Handle   */
    /* and the MailboxData pointer that was specified appears semi-valid.*/
    if((Mailbox) && (MailboxData))
    {
        /* Check to see if this Mailbox specifies a Windows Message Queue */
        /* or not.                                                        */
        if((((MailboxHeader_t *)Mailbox)->NumberSlots) && (((MailboxHeader_t *)Mailbox)->Event) && (!((MailboxHeader_t *)Mailbox)->ThreadID))
        {
            /* Since we are going to change the Mailbox we need to acquire */
            /* the Mutex that is guarding access to it.                    */
            if(QSOSAL_WaitMutex(((MailboxHeader_t *)Mailbox)->Mutex, QSOSAL_INFINITE_WAIT))
            {
                /* Before adding the data to the Mailbox, make sure that the*/
                /* Mailbox is not already full.                             */
                if(((MailboxHeader_t *)Mailbox)->OccupiedSlots < ((MailboxHeader_t *)Mailbox)->NumberSlots)
                {
                    /* Mailbox is NOT full, so add the specified User Data to*/
                    /* the next available free Mailbox Slot.                 */
                    QSOSAL_MemCopy(&(((unsigned char *)(((MailboxHeader_t *)Mailbox)->Slots))[((MailboxHeader_t *)Mailbox)->HeadSlot*((MailboxHeader_t *)Mailbox)->SlotSize]), MailboxData, ((MailboxHeader_t *)Mailbox)->SlotSize);

                    /* Update the Next available Free Mailbox Slot (taking   */
                    /* into account wrapping the pointer).                   */
                    if(++(((MailboxHeader_t *)Mailbox)->HeadSlot) == ((MailboxHeader_t *)Mailbox)->NumberSlots)
                        ((MailboxHeader_t *)Mailbox)->HeadSlot = 0;

                    /* Update the Number of occupied slots to signify that   */
                    /* there was additional Mailbox Data added to the        */
                    /* Mailbox.                                              */
                    ((MailboxHeader_t *)Mailbox)->OccupiedSlots++;

                    /* Signal the Event that specifies that there is indeed  */
                    /* Data present in the Mailbox.                          */
                    QSOSAL_SetEvent(((MailboxHeader_t *)Mailbox)->Event);

                    /* Finally, return success to the caller.                */
                    ret_val = TRUE;
                }
                else
                    ret_val = FALSE;

                /* All finished with the Mailbox, so release the Mailbox    */
                /* Mutex that we currently hold.                            */
                QSOSAL_ReleaseMutex(((MailboxHeader_t *)Mailbox)->Mutex);
            }
            else
                ret_val = FALSE;
        }
        else
        {
            if((!((MailboxHeader_t *)Mailbox)->NumberSlots) && (!((MailboxHeader_t *)Mailbox)->Event) && (((MailboxHeader_t *)Mailbox)->ThreadID))
            {
                /* Windows Message Queue is specified by this Mailbox.      */
                /* Allocate the space for the Slot data and copy the data   */
                /* into it.                                                 */
                if((SlotData = (void *)QSOSAL_AllocateMemory(((MailboxHeader_t *)Mailbox)->SlotSize)) != NULL)
                {
                    /* All that is left to do is to copy the data into the   */
                    /* newly allocated memory and Post the Message to the    */
                    /* Waiting Thread.                                       */
                    QSOSAL_MemCopy(SlotData, MailboxData, ((MailboxHeader_t *)Mailbox)->SlotSize);

                    PostThreadMessage(((MailboxHeader_t *)Mailbox)->ThreadID, WINDOWS_MESSAGE_QUEUE_MESSAGE_ID, (WPARAM)NULL, (LPARAM)SlotData);

                    /* Finally, return success to the caller.                */
                    ret_val = TRUE;
                }
                else
                    ret_val = FALSE;
            }
            else
                ret_val = FALSE;
        }
    }
    else
        ret_val = FALSE;

    /* Return the result to the caller.                                  */
    return(ret_val);
}

/* The following function is provided to allow a means to retrieve   */
/* data from the specified Mailbox. This function will block until   */
/* either Data is placed in the Mailbox or an error with the Mailbox */
/* was detected. This function accepts as its first parameter a      */
/* Mailbox Handle that represents the Mailbox to wait for the data   */
/* with. This function accepts as its second parameter, a pointer to */
/* a data buffer that is AT LEAST the size of a single Slot of the   */
/* Mailbox (specified when the QSOSAL_CreateMailbox() function was   */
/* called). The MailboxData parameter CANNOT be NULL. This function  */
/* will return TRUE if data was successfully retrieved from the      */
/* Mailbox or FALSE if there was an error retrieving data from the   */
/* Mailbox. If this function returns TRUE then the first SlotSize    */
/* bytes of the MailboxData pointer will contain the data that was   */
/* retrieved from the Mailbox.                                       */
/* * NOTE * This function copies to the MailboxData Pointer the data */
/*          that is present in the Mailbox Slot (of size SlotSize).  */
/*          The SlotSize was specified when the Mailbox was created  */
/*          via a successful call to the QSOSAL_CreateMailbox()      */
/*          function.                                                */
Boolean_t QSOSAL_WaitMailbox(Mailbox_t Mailbox, void *MailboxData)
{
    MSG       Msg;
    BOOL      GetMessageReturn;
    Boolean_t ret_val;

    /* Before proceeding any further make sure that the Mailbox Handle   */
    /* and the MailboxData pointer that was specified appears semi-valid.*/
    if((Mailbox) && (MailboxData))
    {
        /* Check to see if this Mailbox specifies a Windows Message Queue */
        /* or not.                                                        */
        if((((MailboxHeader_t *)Mailbox)->NumberSlots) && (((MailboxHeader_t *)Mailbox)->Event) && (!((MailboxHeader_t *)Mailbox)->ThreadID))
        {
            /* Next, we need to block until there is at least one Mailbox  */
            /* Slot occupied by waiting on the Data Available Event.       */
            if(QSOSAL_WaitEvent(((MailboxHeader_t *)Mailbox)->Event, QSOSAL_INFINITE_WAIT))
            {
                /* Since we are going to update the Mailbox, we need to     */
                /* acquire the Mutex that guards access to the Mailox.      */
                if(QSOSAL_WaitMutex(((MailboxHeader_t *)Mailbox)->Mutex, QSOSAL_INFINITE_WAIT))
                {
                    /* Let's double check to make sure that there does indeed*/
                    /* exist at least one slot with Mailbox Data present in  */
                    /* it.                                                   */
                    if(((MailboxHeader_t *)Mailbox)->OccupiedSlots)
                    {
                        /* Flag success to the caller.                        */
                        ret_val = TRUE;

                        /* Now copy the Data into the Memory Buffer specified */
                        /* by the caller.                                     */
                        QSOSAL_MemCopy(MailboxData, &((((unsigned char *)((MailboxHeader_t *)Mailbox)->Slots))[((MailboxHeader_t *)Mailbox)->TailSlot*((MailboxHeader_t *)Mailbox)->SlotSize]), ((MailboxHeader_t *)Mailbox)->SlotSize);

                        /* Now that we've copied the data into the Memory     */
                        /* Buffer specified by the caller we need to mark the */
                        /* Mailbox Slot as free.                              */
                        if(++(((MailboxHeader_t *)Mailbox)->TailSlot) == ((MailboxHeader_t *)Mailbox)->NumberSlots)
                            ((MailboxHeader_t *)Mailbox)->TailSlot = 0;

                        ((MailboxHeader_t *)Mailbox)->OccupiedSlots--;

                        /* If there is NO more data available in this Mailbox */
                        /* then we need to flag it as such by Resetting the   */
                        /* Mailbox Data available Event.                      */
                        if(!((MailboxHeader_t *)Mailbox)->OccupiedSlots)
                            QSOSAL_ResetEvent(((MailboxHeader_t *)Mailbox)->Event);
                    }
                    else
                    {
                        /* Internal error, flag that there is NO Data present */
                        /* in the Mailbox (by resetting the Data Available    */
                        /* Event) and return failure to the caller.           */
                        QSOSAL_ResetEvent(((MailboxHeader_t *)Mailbox)->Event);

                        ret_val = FALSE;
                    }

                    /* All finished with the Mailbox, so release the Mailbox */
                    /* Mutex that we currently hold.                         */
                    QSOSAL_ReleaseMutex(((MailboxHeader_t *)Mailbox)->Mutex);
                }
                else
                    ret_val = FALSE;
            }
            else
                ret_val = FALSE;
        }
        else
        {
            if((!((MailboxHeader_t *)Mailbox)->NumberSlots) && (!((MailboxHeader_t *)Mailbox)->Event) && (((MailboxHeader_t *)Mailbox)->ThreadID))
            {
                /* Simply Wait until a Message is available.  Note that     */
                /* GetMessage() does not return until a Message is          */
                /* available, and returns FALSE if a WM_QUIT Message is     */
                /* posted to the Message Queue.                             */
                GetMessageReturn = GetMessage(&Msg, NULL, 0, 0);

                if((GetMessageReturn != (BOOL)0) && (GetMessageReturn != (BOOL)(-1)))
                {
                    if(Msg.lParam)
                    {
                        /* Now copy the Data into the Memory Buffer specified */
                        /* by the caller.                                     */
                        QSOSAL_MemCopy(MailboxData, (void *)Msg.lParam, ((MailboxHeader_t *)Mailbox)->SlotSize);

                        /* Free the Slot Data that was allocated to hold the  */
                        /* Message.                                           */
                        QSOSAL_FreeMemory((void *)Msg.lParam);

                        /* Flag success to the caller.                        */
                        ret_val = TRUE;
                    }
                    else
                        ret_val = FALSE;
                }
                else
                    ret_val = FALSE;
            }
            else
                ret_val = FALSE;
        }
    }
    else
        ret_val = FALSE;

    /* Return the result to the caller.                                  */
    return(ret_val);
}

/* The following function is responsible for destroying a Mailbox    */
/* that was created successfully via a successful call to the        */
/* QSOSAL_CreateMailbox() function. This function accepts as input   */
/* the Mailbox Handle of the Mailbox to destroy. Once this function  */
/* is completed the Mailbox Handle is NO longer valid and CANNOT be  */
/* used. Calling this function will cause all outstanding            */
/* QSOSAL_WaitMailbox() functions to fail with an error. The final   */
/* parameter specifies an (optional) callback function that is called*/
/* for each queued Mailbox entry. This allows a mechanism to free any*/
/* resources that might be associated with each individual Mailbox   */
/* item.                                                             */
void QSOSAL_DeleteMailbox(Mailbox_t Mailbox, QSOSAL_MailboxDeleteCallback_t MailboxDeleteCallback)
{
    MSG Msg;

    /* Before proceeding any further make sure that the Mailbox Handle   */
    /* that was specified appears semi-valid.                            */
    if(Mailbox)
    {
        /* Check to see if this Mailbox specifies a Windows Message Queue */
        /* or not.                                                        */
        if((((MailboxHeader_t *)Mailbox)->NumberSlots) && (((MailboxHeader_t *)Mailbox)->Event) && (!((MailboxHeader_t *)Mailbox)->ThreadID))
        {
            /* Mailbox appears semi-valid, so let's free all Events and    */
            /* Mutexes, perform any mailbox deletion callback actions, and */
            /* finally free the Memory associated with the Mailbox itself. */
            if(((MailboxHeader_t *)Mailbox)->Event)
                QSOSAL_CloseEvent(((MailboxHeader_t *)Mailbox)->Event);

            if(((MailboxHeader_t *)Mailbox)->Mutex)
                QSOSAL_CloseMutex(((MailboxHeader_t *)Mailbox)->Mutex);

            /* Check to see if a Mailbox Delete Item Callback was          */
            /* specified.                                                  */
            if(MailboxDeleteCallback)
            {
                /* Now loop though all of the occupied slots and call the   */
                /* callback with the slot data.                             */
                while(((MailboxHeader_t *)Mailbox)->OccupiedSlots)
                {
                    __QSOSALTRY
                    {
                        (*MailboxDeleteCallback)(&((((unsigned char *)((MailboxHeader_t *)Mailbox)->Slots))[((MailboxHeader_t *)Mailbox)->TailSlot*((MailboxHeader_t *)Mailbox)->SlotSize]));
                    }
                    __QSOSALEXCEPT(1)
                    {
                        /* Do Nothing.                                        */
                    }

                    /* Now that we've called back with the data, we need to  */
                    /* advance to the next slot.                             */
                    if(++(((MailboxHeader_t *)Mailbox)->TailSlot) == ((MailboxHeader_t *)Mailbox)->NumberSlots)
                        ((MailboxHeader_t *)Mailbox)->TailSlot = 0;

                    /* Flag that there is one less occupied slot.            */
                    ((MailboxHeader_t *)Mailbox)->OccupiedSlots--;
                }
            }
        }
        else
        {
            if((!((MailboxHeader_t *)Mailbox)->NumberSlots) && (!((MailboxHeader_t *)Mailbox)->Event) && (((MailboxHeader_t *)Mailbox)->ThreadID))
            {
                /* Posting a WM_QUIT message will cause the Message Loop to */
                /* return zero, which will cause the QSOSAL_WaitMailbox()   */
                /* function to return FALSE.                                */
                PostThreadMessage(((MailboxHeader_t *)Mailbox)->ThreadID, WM_QUIT, (WPARAM)NULL, (LPARAM)NULL);

                /* Now let's remove any items from the Message Queue and    */
                /* call back the specified callback.                        */
                if(MailboxDeleteCallback)
                {
                    /* Loop though all remaining messages and notify the     */
                    /* caller of the data.                                   */
                    while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
                    {
                        if(Msg.lParam)
                        {
                            __QSOSALTRY
                            {
                                (*MailboxDeleteCallback)((void *)Msg.lParam);
                            }
                            __QSOSALEXCEPT(1)
                            {
                                /* Do Nothing.                                  */
                            }

                            /* Free the Slot Data that was allocated to hold   */
                            /* the Message.                                    */
                            QSOSAL_FreeMemory((void *)Msg.lParam);
                        }
                    }
                }
            }
        }

        /* All finished cleaning up the Mailbox, simply free all          */
        /* memory that was allocated for the Mailbox.                     */
        QSOSAL_FreeMemory(Mailbox);
    }
}

/* The following function is used to initialize the Platform module. */
/* The Platform module relies on some static variables that are used */
/* to coordinate the abstraction.  When the module is initially      */
/* started from a cold boot, all variables are set to the proper     */
/* state.  If the Warm Boot is required, then these variables need to*/
/* be reset to their default values.  This function sets all static  */
/* parameters to their default values.                               */
/* * NOTE * The implementation is free to pass whatever information  */
/*          required in this parameter.                              */
void QSOSAL_Init(void *UserParam)
{
    /* Verify that the parameter passed in appears valid.                */
    if(UserParam)
    {
    }

    /* Initialize the Debug Zones.                                       */
    DebugZoneMask = DBG_ZONE_ANY;
    DebugZoneMask = DBG_ZONE_CRITICAL_ERROR | DBG_ZONE_ENTER_EXIT | DBG_ZONE_GENERAL | DBG_ZONE_DEVELOPMENT;
}

/* The following function is used to cleanup the Platform module.    */
void QSOSAL_DeInit(void)
{
}

/* Write out the specified NULL terminated Debugging String to the   */
/* Debug output.                                                     */
void QSOSAL_OutputMessage(const char *DebugString, ...)
{
    int           ret_val;
    va_list       args;
    char          DebugMsgBuffer[QSOSAL_KERNEL_MAX_OUTPUT_MESSAGE_LENGTH+1];

    va_start(args, DebugString);

    /* Simply wrap the C Run-Time vsnprintf_s() function.                */
    /* * NOTE * _TRUNCATE informs vsnprintf_S() to write as many         */
    /*          characters that can be written to the buffer.            */
#ifdef _MSC_VER
    ret_val = vsnprintf_s(DebugMsgBuffer, sizeof(DebugMsgBuffer), _TRUNCATE, DebugString, args);
#else
#ifdef __BORLANDC__
    ret_val = vsnprintf(DebugMsgBuffer, sizeof(DebugMsgBuffer), DebugString, args);
#else
    ret_val = vsnprintf_s(DebugMsgBuffer, sizeof(DebugMsgBuffer), DebugString, args);
#endif
#endif

    /* Check if the string has been truncated.                           */
    /* * NOTE * vsnprintf_s() returns -1 if the string has been          */
    /*          truncated.                                               */
    if((ret_val == -1) || ((unsigned long)ret_val >= sizeof(DebugMsgBuffer)))
    {
        /* The string has been truncated so the number of characters      */
        /* written is the maximum that can be stored by the destination   */
        /* buffer.                                                        */
        ret_val                 = (sizeof(DebugMsgBuffer) - 1);
        DebugMsgBuffer[ret_val] = '\0';

    }

    va_end(args);

    /* Write the debug message to the console.                           */
    ConsoleWrite(DebugMsgBuffer, ret_val);
}

/* The following function is used to set the Debug Mask that controls*/
/* which debug zone messages get displayed.  The function takes as   */
/* its only parameter the Debug Mask value that is to be used.  Each */
/* bit in the mask corresponds to a debug zone.  When a bit is set,  */
/* the printing of that debug zone is enabled.                       */
void QSOSAL_SetDebugMask(unsigned long DebugMask)
{
    DebugZoneMask = DebugMask;
}

/* The following function is a utility function that can be used to  */
/* determine if a specified Zone is currently enabled for debugging. */
int QSOSAL_TestDebugZone(unsigned long Zone)
{
    return(DebugZoneMask & Zone);
}

/* The following function is responsible for displaying binary debug */
/* data.  The first parameter to this function is the length of data */
/* pointed to by the next parameter.  The final parameter is a       */
/* pointer to the binary data to be  displayed.                      */
int QSOSAL_DumpData(unsigned int DataLength, const unsigned char *DataPtr)
{
    int           ret_val;
    char          Buffer[80];
    char         *BufPtr;
    char         *HexBufPtr;
    uint8_t        DataByte;
    unsigned int  Index;
    static char   HexTable[] = "0123456789ABCDEF\n";
    static char   Header1[]  = "       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  ";
    static char   Header2[]  = " -----------------------------------------------------------------------\n";

    /* Before proceeding any further, lets make sure that the parameters */
    /* passed to us appear semi-valid.                                   */
    if((DataLength > 0) && (DataPtr != NULL))
    {
        /* The parameters which were passed in appear to be at least      */
        /* semi-valid, next write the header out to the file.             */
        QSOSAL_OutputMessage(Header1);
        QSOSAL_OutputMessage(HexTable);
        QSOSAL_OutputMessage(Header2);

        /* Limit the number of bytes that will be displayed in the dump.  */
        if(DataLength > MAX_DBG_DUMP_BYTES)
        {
            DataLength = MAX_DBG_DUMP_BYTES;
        }

        /* Now that the Header is written out, let's output the Debug     */
        /* Data.                                                          */
        QSOSAL_MemInitialize(Buffer, ' ', sizeof(Buffer));
        BufPtr    = Buffer + QSOSAL_SprintF_S(Buffer, sizeof(Buffer), " %05X ", 0);
        HexBufPtr = Buffer + sizeof(Header1)-1;
        for(Index=0; Index < DataLength;)
        {
            Index++;
            DataByte     = *DataPtr++;
            *BufPtr++    = HexTable[(uint8_t)(DataByte >> 4)];
            *BufPtr      = HexTable[(uint8_t)(DataByte & 0x0F)];
            BufPtr      += 2;
            /* Check to see if this is a printable character and not a     */
            /* special reserved character.  Replace the non-printable      */
            /* characters with a period.                                   */
            *HexBufPtr++ = (char)(((DataByte >= ' ') && (DataByte <= '~') && (DataByte != '\\') && (DataByte != '%'))?DataByte:'.');
            if(((Index % MAXIMUM_BYTES_PER_ROW) == 0) || (Index == DataLength))
            {
                /* We are at the end of this line, so terminate the data    */
                /* compiled in the buffer and send it to the output device. */
                *HexBufPtr++ = '\n';
                *HexBufPtr   = 0;
                QSOSAL_OutputMessage(Buffer);
                if(Index != DataLength)
                {
                    /* We have more to process, so prepare for the next line.*/
                    QSOSAL_MemInitialize(Buffer, ' ', sizeof(Buffer));
                    BufPtr    = Buffer + QSOSAL_SprintF_S(Buffer, sizeof(Buffer), " %05X ", Index);
                    HexBufPtr = Buffer + sizeof(Header1)-1;
                }
                else
                {
                    /* Flag that there is no more data.                      */
                    HexBufPtr = NULL;
                }
            }
        }
        /* Check to see if there is partial data in the buffer.           */
        if(HexBufPtr > 0)
        {
            /* Terminate the buffer and output the line.                   */
            *HexBufPtr++ = '\n';
            *HexBufPtr   = 0;
            QSOSAL_OutputMessage(Buffer);
        }
        QSOSAL_OutputMessage("\n");

        /* Finally, set the return value to indicate success.             */
        ret_val = 0;
    }
    else
    {
        /* An invalid parameter was enterer.                              */
        ret_val = -1;
    }
    return(ret_val);
}

