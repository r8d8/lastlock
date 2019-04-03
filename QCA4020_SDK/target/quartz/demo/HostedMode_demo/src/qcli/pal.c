/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
 * 2015-2016 Qualcomm Atheros, Inc.
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

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qapi_qsQuartz.h"

#include "qapi_types.h"

#include "pal.h"
#include "qcli.h"

#include "qurt_error.h"
#include "qurt_thread.h"
#include "qurt_signal.h"
#include "qurt_mutex.h"

#include "qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_uart.h"
#include "qapi/qapi_reset.h"
#include "qapi/qapi_tlmm.h"
#include "qapi/qapi_exhost_devcfg.h"

#ifdef WPAN_MODULES
#include "qsConfig.h"
#endif

#define va_list __builtin_va_list
#define va_arg __builtin_va_arg
#define va_start __builtin_va_start
#define va_end __builtin_va_end
#define va_copy __builtin_va_copy

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define PAL_THREAD_STACK_SIZE                           (2048)
#define PAL_THREAD_PRIORITY                             (20)


#define PAL_RECIEVE_BUFFER_SIZE                         (128)
#define PAL_WRITE_BUFFER_SIZE                           (128)
#define PAL_RECIEVE_BUFFER_COUNT                        (2)

#define PAL_EVENT_MASK_RECEIVE                          (0x00000001)
#define PAL_EVENT_MASK_TRANSMIT                         (0x00000002)

#define PAL_ENTER_CRITICAL()                            do { __asm("cpsid i"); } while(0)
#define PAL_EXIT_CRITICAL()                             do { __asm("cpsie i"); } while(0)

#define TAKE_LOCK(__lock__)             do{ (qurt_mutex_lock(&(__lock__))); } while(0)
#define RELEASE_LOCK(__lock__)          do { qurt_mutex_unlock(&(__lock__)); } while(0)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

typedef struct PAL_Context_s
{
    qbool_t            Initialized;
    qapi_UART_Handle_t Console_UART;
    qbool_t            Uart_Enabled;
    char               Rx_Buffer[PAL_RECIEVE_BUFFER_COUNT][PAL_RECIEVE_BUFFER_SIZE];
    char               Rx_Buffer_Length[PAL_RECIEVE_BUFFER_COUNT];
    char               Printf_Buffer[PAL_WRITE_BUFFER_SIZE];
    uint8_t            Rx_In_Index;
    uint8_t            Rx_Out_Index;
    volatile uint32_t  Rx_Buffers_Free;
    volatile uint32_t  BytesToTx;
    qurt_signal_t      Event;
    qurt_mutex_t       multitask_share_mutex;   /**< The Mutex used to share resources in multi-threads.   */
} PAL_Debug_Context_t;

static PAL_Debug_Context_t PAL_Debug_Context;

qbool_t Debug_Uart_Init(void);

void (*Dbg_Printf)(char *fmt, ...);

extern uint32_t data_unit_test();
extern uint32_t diag_unit_test();

/**
  @brief Main entry point of the application.
  */
static void Quartz_Hosted_Mode_Thread(void *Param)
{
#ifdef CONFIG_DAEMON_MODE
    if (QAPI_QS_OK != qapi_Qs_Init())
    {
        App_Dbg_Printf("Target hosted mode feature initialization failed.\r\n");
        return;
    }
    App_Dbg_Printf("Hosted mode feature initialization succeeded.\r\n");

#ifdef DATAPATH_TEST
    data_unit_test();
#endif /* DATAPATH_TEST */

#if defined(DIAG_RCV_TEST) || defined(DIAG_SEND_TEST)
    diag_unit_test();
#endif /* defined(DIAG_RCV_TEST) || defined(DIAG_SEND_TEST) */

    qurt_thread_stop();

#else  /* CONFIG_DAEMON_MODE */

    uint32_t i;
    uint32_t transport = 0;
    uint32_t ifname = 0;
    qapi_Exhost_Devcfg_t devcfg;
    qapi_Get_Exhost_Devcfg(&devcfg);

    for(i = 0; i < 2; i ++) {
        if( i == 0 ) 
        {    
            if( devcfg.uart_enable == 0 )
                continue;
            else {
                transport = QAPI_QS_UART_E;
                if(devcfg.uart_port == 0)
                    ifname = QAPI_UART_HS_PORT_E;
                else
                    ifname = QAPI_UART_DEBUG_PORT_E;
                App_Dbg_Printf("UART used for all service queues.\r\n");

            }
        } else if(i == 1) {
            if( devcfg.spi_enable == 0 )
                continue;
            else {
                transport = QAPI_QS_SPI_E;
                ifname = 0;
                App_Dbg_Printf("SPI used for all service queues.\r\n");
            }
        } else {
            continue;
        }
    
        if (QAPI_QS_OK != qapi_Qs_Init((uint8_t)QAPI_QS_MODULE_WLAN, transport, ifname))
            return;

#ifdef QS_WPAN_INIT_FWUPGRADE_THREAD
        if (QAPI_QS_OK != qapi_Qs_Init((uint8_t)QAPI_QS_MODULE_FWUPGRADE, transport, ifname))
            return;
#endif
        /* Check if BLE needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_BLE_THREAD
        if (QAPI_QS_OK != qapi_Qs_Init(QAPI_QS_MODULE_BLE, transport, ifname))
            return;
#endif

        /* Check if HMI needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_HMI_THREAD
        if (QAPI_QS_OK != qapi_Qs_Init(QAPI_QS_MODULE_HMI, transport, ifname))
            return;
#endif

        /* Check if Zigbee needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_ZB_THREAD
        if (QAPI_QS_OK != qapi_Qs_Init(QAPI_QS_MODULE_ZIGBEE, transport, ifname))
            return;
#endif

        /* Check if Thread needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_TWN_THREAD
        if (QAPI_QS_OK != qapi_Qs_Init(QAPI_QS_MODULE_THREAD, transport, ifname))
            return;
#endif

        /* Check if Coexistence needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_COEX_THREAD
        if (QAPI_QS_OK != qapi_Qs_Init(QAPI_QS_MODULE_COEX, transport, ifname))
            return;
#endif

        /* Check if HERH needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_HERH_THREAD
        if (QAPI_QS_OK != qapi_Qs_Init(QAPI_QS_MODULE_HERH, transport, ifname))
            return;
#endif
    }
    qurt_thread_stop();

#endif /* CONFIG_DAEMON_MODE */
}

/**
  @brief Function call to initialize the application.
  */
void app_init(qbool_t ColdBoot)
{
    qurt_signal_init(&(PAL_Debug_Context.Event));
    Debug_Uart_Init();
    Dbg_Printf = App_Dbg_Printf;
}

/**
  @brief Main entry point of the application.
  */
void app_start(qbool_t ColdBoot)
{
    qurt_thread_attr_t Thread_Attribte;
    qurt_thread_t      Thread_Handle;
    /* Start the main demo thread. */
    qurt_thread_attr_init(&Thread_Attribte);
    qurt_thread_attr_set_name(&Thread_Attribte, "Qz_Hosted");
    qurt_thread_attr_set_priority(&Thread_Attribte, PAL_THREAD_PRIORITY);
    qurt_thread_attr_set_stack_size(&Thread_Attribte, PAL_THREAD_STACK_SIZE);
    (void)qurt_thread_create(&Thread_Handle, &Thread_Attribte, Quartz_Hosted_Mode_Thread, NULL);
    return;
}

void PAL_Exit(void)
{
#ifdef CONFIG_DAEMON_MODE
    qapi_Qs_DeInit();

#else /* CONFIG_DAEMON_MODE */

    qapi_Qs_DeInit((uint8_t)QAPI_QS_MODULE_WLAN);
#ifdef QS_WPAN_INIT_FWUPGRADE_THREAD
    qapi_Qs_DeInit((uint8_t)QAPI_QS_MODULE_FWUPGRADE);
#endif
    /* Check if BLE needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_BLE_THREAD
    qapi_Qs_DeInit(QAPI_QS_MODULE_BLE);
#endif

    /* Check if HMI needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_HMI_THREAD
    qapi_Qs_DeInit(QAPI_QS_MODULE_HMI);
#endif

    /* Check if Zigbee needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_ZB_THREAD
    qapi_Qs_DeInit(QAPI_QS_MODULE_ZIGBEE);
#endif

    /* Check if Thread needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_TWN_THREAD
    qapi_Qs_DeInit(QAPI_QS_MODULE_THREAD);
#endif

    /* Check if Coexistence needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_COEX_THREAD
    qapi_Qs_DeInit(QAPI_QS_MODULE_COEX);
#endif

    /* Check if HERH needs to be initialized and initialize it. */
#ifdef QS_WPAN_INIT_HERH_THREAD
    qapi_Qs_DeInit(QAPI_QS_MODULE_HERH);
#endif
#endif /* CONFIG_DAEMON_MODE */
}

/**
 *  for debug output
 */

/**
  @brief This function handles receive callbacks from the UART.

  @param Num_Bytes[in] is the number of bytes received.
  @param CB_Data[in]   is the application defined callback data.  In this case
  it is the index of the buffer received on.
  */
static void Debug_Uart_Rx_CB(uint32 Num_Bytes, void* CB_Data)
{
    uint32_t Buffer_Index;

    Buffer_Index = (uint32_t)CB_Data;

    if(PAL_Debug_Context.Rx_Buffers_Free != 0)
    {
        /* See how much data can be read. */
        if(Num_Bytes > PAL_RECIEVE_BUFFER_SIZE)
        {
            Num_Bytes = PAL_RECIEVE_BUFFER_SIZE;
        }

        /* Note the amount of data that was read. */
        PAL_Debug_Context.Rx_Buffer_Length[Buffer_Index] = Num_Bytes;

        PAL_Debug_Context.Rx_In_Index ++;
        if(PAL_Debug_Context.Rx_In_Index == PAL_RECIEVE_BUFFER_COUNT)
        {
            PAL_Debug_Context.Rx_In_Index = 0;
        }

        PAL_ENTER_CRITICAL();
        PAL_Debug_Context.Rx_Buffers_Free --;
        PAL_EXIT_CRITICAL();

        /* Signal the event that data was received. */
        qurt_signal_set(&(PAL_Debug_Context.Event), PAL_EVENT_MASK_RECEIVE);
    }
}

/**
  @brief This function handles transmit callbacks from the UART.

  @param Num_Bytes[in] is the number of bytes transmitted.
  @param CB_Data[in]   is the application defined callback data.
  */
static void Debug_Uart_Tx_CB(uint32 Num_Bytes, void* CB_Data)
{
    if(PAL_Debug_Context.BytesToTx != 0)
    {
        PAL_Debug_Context.BytesToTx -= Num_Bytes;
        if(PAL_Debug_Context.BytesToTx == 0)
        {
            qurt_signal_set(&(PAL_Debug_Context.Event), PAL_EVENT_MASK_TRANSMIT);
        }
    }
}

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/
//char *Buffer = "PAL>";

qbool_t Debug_Uart_Init(void)
{
    qapi_UART_Port_Id_e     debug_port;
    qapi_UART_Open_Config_t Uart_Config;
    qapi_Exhost_Devcfg_t    devcfg;
    uint8_t                 Ret_Val;
    qapi_Get_Exhost_Devcfg(&devcfg);
    /* debug port use alternate uart port */
    if( devcfg.uart_port == 0 )
        debug_port = QAPI_UART_DEBUG_PORT_E;
    else 
        debug_port = QAPI_UART_HS_PORT_E;
    Uart_Config.baud_Rate        = 115200;
    Uart_Config.parity_Mode      = QAPI_UART_NO_PARITY_E;
    Uart_Config.num_Stop_Bits    = QAPI_UART_1_0_STOP_BITS_E;
    Uart_Config.bits_Per_Char    = QAPI_UART_8_BITS_PER_CHAR_E;
    Uart_Config.enable_Loopback  = FALSE;
    Uart_Config.enable_Flow_Ctrl = FALSE;
    Uart_Config.tx_CB_ISR        = Debug_Uart_Tx_CB;
    Uart_Config.rx_CB_ISR        = Debug_Uart_Rx_CB;

    qurt_mutex_create(&(PAL_Debug_Context.multitask_share_mutex));

    PAL_Debug_Context.Uart_Enabled     = true;
    
    if(qapi_UART_Open(&(PAL_Debug_Context.Console_UART), debug_port, &Uart_Config) == QAPI_OK)
    {
        Ret_Val = true;
    }
    else
    {
        Ret_Val = false;
    }
    return(Ret_Val);
}

void Debug_Console_Write(uint32_t Length, const char *Buffer)
{
    if((Length != 0) && (Buffer != NULL) && (PAL_Debug_Context.Uart_Enabled))
    {
        PAL_Debug_Context.BytesToTx = Length;

        /* Transmit the data. */
        if(qapi_UART_Transmit(PAL_Debug_Context.Console_UART, (char *)Buffer, Length, NULL) == QAPI_OK)
        {
            /* Wait for the packet to be sent. */
            qurt_signal_wait(&(PAL_Debug_Context.Event), PAL_EVENT_MASK_TRANSMIT, QURT_SIGNAL_ATTR_WAIT_ANY | QURT_SIGNAL_ATTR_CLEAR_MASK);
        }
    }
}

void App_Dbg_Printf(char *fmt, ...)
{
    va_list args;
    uint32_t Length;

    TAKE_LOCK(PAL_Debug_Context.multitask_share_mutex);

    va_start(args, fmt);
    Length = vsnprintf(PAL_Debug_Context.Printf_Buffer, sizeof(PAL_Debug_Context.Printf_Buffer), fmt, args);
    Debug_Console_Write(Length, PAL_Debug_Context.Printf_Buffer);
    va_end(args);
    
    RELEASE_LOCK(PAL_Debug_Context.multitask_share_mutex);
}
