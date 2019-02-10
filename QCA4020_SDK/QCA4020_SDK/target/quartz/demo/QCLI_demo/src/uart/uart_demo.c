/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
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

/*Description:
* System supports two UART ports in total.
* Since console UART is necessary  in QCLI_demo, this demo shows scenario of 
* one console UART and one data UART working together.
*  (1) console UART: result of PAL_Uart_port_id_get()
*  (2) data UART   : The rest UART
* 
* Please note that console UART and data UART are able to be switched by qcli_console_switch()
* 
* In order to disable both UARTs:
*   (1) Call PAL_Uart_Deinit()   (only disables console UART)
*   (2) Refer to qcli_uart_disable() to disable another UART if it's enabled before.
*
*
* For other use case:
* 1. Support two DEBUG UARTS:
*   (1) Disable CFG_FEATURE_UART_DEMO in ioesw_proc\quartz\demo\QCLI_demo\build\gcc\Makefile(or build.bat)
*   (2) J58 is used as console port by default.
*   (3) Enable pktlog/dbglog functionality to use J52 UART as debug port.
* 2. Support two DATA UARTS:
*   (1) Disable console port by PAL_Uart_Deinit()
*   (2) Two DATA UARTs are already supported in quartz\demo\QCLI_demo\src\uart\uart.c.
*       Please follow DATA UART example of uart_demo.c to apply another UART as DATA UART.
*       Relevant APIs:
*            uart_init
*            uart_deinit
*            uart_enabled
*            uart_write
*            uart_read
*            uart_get_stats
*            uart_clear_stats
*            uart_get_param
*/

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <stdarg.h>
#include "stringl.h"

#include "qapi_types.h"
     
#include "pal.h"
#include "qcli.h"
#include <qcli_api.h>

#include "qurt_error.h"
#include "qurt_thread.h"
#include "qurt_signal.h"
#include "qapi_delay.h"
     
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_uart.h"
     
#include "osal_types.h"
//#include "OSAL.h"

#include "qapi_netservices.h"
#include "netutils.h"       /* time_struct_t */

#include "uart.h"
#include "uart_demo.h"
 /*-------------------------------------------------------------------------
 * Macros / Constants / typedef
 *-----------------------------------------------------------------------*/
typedef void *OSAL_Mailbox_t;

#define UART_DBG
#ifdef UART_DBG
#define UART_PRINTF(...)     QCLI_Printf(qcli_uart_handle, __VA_ARGS__)
#else
#define UART_PRINTF(x, ...)
#endif



#define A_ERROR    -1
#define INVALID_SOCKFD    -1


#define TCP_BUF_LEN 1480
#define UART_TIMEOUT_TICKS  10

#define CLIENT_TX_CACHE_BUF_SIZE    1480

#define MBOX_SLOT_NUM               64    

#define UART_THREAD_STACK_SIZE                           (2048)
#define UART_THREAD_PRIORITY                             (12)

#define DATA_UART_ID_GET() ((QAPI_UART_DEBUG_PORT_E == g_console_uart_id) ?  \
                        QAPI_UART_HS_PORT_E : QAPI_UART_DEBUG_PORT_E)

#define SET_WORK_MODE(mode)     (g_work_mode = mode)

#define MODE_IS_SERVER()   (WORK_MODE_SERVER == g_work_mode)
#define MODE_IS_ECHO()     (WORK_MODE_ECHO == g_work_mode)
#define MODE_IS_IDLE()     (WORK_MODE_IDLE == g_work_mode)
#define MODE_IS_RUNNING()  (!MODE_IS_IDLE())

#define IN_RANGE(val, min, max) (val >=min && val <= max)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define MUTEX_LOCK(__lock__)      ((qurt_mutex_lock_timed(&(__lock__), QURT_TIME_WAIT_FOREVER)) == QURT_EOK)
#define MUTEX_UNLOCK(__lock__)   do { qurt_mutex_unlock(&(__lock__)); } while(0)

 /*-------------------------------------------------------------------------
 * Structure & Enum defination
 *-----------------------------------------------------------------------*/
typedef enum{
    WORK_MODE_ECHO = 0,
    WORK_MODE_SERVER = 1,
    WORK_MODE_IDLE = 2
}WORK_MODE_E;

 /*-------------------------------------------------------------------------
 * Function declaration
 *-----------------------------------------------------------------------*/

QCLI_Command_Status_t qcli_uart_enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
QCLI_Command_Status_t qcli_uart_disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
QCLI_Command_Status_t qcli_start_server(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
QCLI_Command_Status_t qcli_stop_server(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
QCLI_Command_Status_t qcli_start_echo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
QCLI_Command_Status_t qcli_stop_echo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
QCLI_Command_Status_t qcli_console_switch(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
QCLI_Command_Status_t qcli_get_info(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
QCLI_Command_Status_t qcli_clear_stats(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
void uart_rx_thread_start(uint32_t uart_id);
void uart_tx_thread_start(uint32_t uart_id);
int32_t uart_tcp_server_start(uint32_t uart_id, uint32_t ip_addr, uint16_t tcp_port);
char *ip2str(uint32_t ip);
int32_t mailbox_init(int32_t slot_num);
int32_t mailbox_deinit();

/*-------------------------------------------------------------------------
* Extern Variables
*-----------------------------------------------------------------------*/
extern OSAL_Mailbox_t OSAL_Create_Mailbox(uint32_t Mailbox_Slot, uint32_t Mailbox_Slot_Size);
extern qbool_t OSAL_Add_To_Mailbox(OSAL_Mailbox_t Mailbox, void *Data);
extern qbool_t OSAL_Wait_Mailbox(OSAL_Mailbox_t Mailbox, uint32_t Timeout, void *Data);
extern void OSAL_Delete_Mailbox(OSAL_Mailbox_t Mailbox);
extern uint32_t OSAL_Get_System_Ticks(void);


 /*-------------------------------------------------------------------------
 * Global Variables
 *-----------------------------------------------------------------------*/
QCLI_Group_Handle_t qcli_uart_handle;  /* Handle for our QCLI Command Group. */

WORK_MODE_E g_work_mode = WORK_MODE_IDLE;

OSAL_Mailbox_t g_mail_box = NULL;
int32_t mbox_size = 0;
int32_t mbox_size_max = 0;
qurt_mutex_t mbox_mutex;

qbool_t uart_tx_task_stop = TRUE;
qbool_t uart_rx_task_stop = TRUE;

int32_t g_uart_serv_sock_fd = INVALID_SOCKFD;
int32_t g_uart_client_sock_fd = INVALID_SOCKFD;
uint64_t g_server_tx_bytes = 0;
uint64_t g_server_rx_bytes = 0;

uint8_t *client_tx_cache_buf = NULL;
int32_t client_tx_cache_len = 0;

int32_t g_console_uart_id = -1;

uint32_t baud_rate_set[2][10] = {{300, 4800, 9600, 115200},
                                {4800, 9600, 115200, 500000, 1000000, 2000000, 4000000}};


const QCLI_Command_t uart_cmd_list[] =
{
    // cmd_function    start_thread         cmd_string               usage_string                   description
    { qcli_uart_enable,         false,      "Enable",           "Type \"enable\" to get more info on usage",     "Enable Uart port"   },
    { qcli_uart_disable,        false,      "Disable",          "",                      "Disable Uart port"   },
    { qcli_start_server,        true,       "StartServer",      "<ipAddr> <TcpPort>",    "Start server"   },
    { qcli_stop_server,         false,      "StopServer",       "",                      "Stop server"   },
    { qcli_start_echo,          false,      "StartEcho",        "",                      "start echo"   },
    { qcli_stop_echo,           false,      "StopEcho",         "",                      "Stop echo"   },
    { qcli_console_switch,      false,      "SwitchConsole",    "",                      "Switch console uart port"   },
    { qcli_get_info,            false,      "info",             "",    "Get information of uart port."   },
    { qcli_clear_stats,         false,      "ClearStats",       "",    "Clear UART and TCP server stats."   },
};

const QCLI_Command_Group_t uart_cmd_group =
{
    "UART",
    (sizeof(uart_cmd_list) / sizeof(uart_cmd_list[0])),
    uart_cmd_list
};

 /*-------------------------------------------------------------------------
 * Function defination
 *-----------------------------------------------------------------------*/
void Initialize_Uart_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    qcli_uart_handle = QCLI_Register_Command_Group(NULL, &uart_cmd_group);
    if(qcli_uart_handle)
    {
        UART_PRINTF("UART Registered \n");
    }
    g_console_uart_id = PAL_Uart_port_id_get();
    SET_WORK_MODE(WORK_MODE_IDLE);
}

void uart_enable_help(void)
{
    uint32_t uart_id = DATA_UART_ID_GET();
    int32_t i;
    
    UART_PRINTF("enable <baudRate> <parity> <stopBits> <bitsPerChar> <loopback> <flowCtrl>\n");
    UART_PRINTF("\tbaudRate   : ");
    for (i = 0; i < ARRAY_SIZE(baud_rate_set[uart_id]); i++){
        if (0 == baud_rate_set[uart_id][i]){
            continue;
        }
        UART_PRINTF("%d ", baud_rate_set[uart_id][i]);
    }
    
    UART_PRINTF("\n");
    
    UART_PRINTF("\tparity     : 0 - No Parity, 1 - Odd, 2 - Even, 3 - Space\n");
    UART_PRINTF("\tstopBits   : 0 - 0.5 bits, 1 - 1.0 bits, 2 - 1.5 bits, 3 - 2.0 bits\n");
    UART_PRINTF("\tbitsPerChar: 0 - 5 bits, 1 - 6 bits, 2 - 7 bits, 3 - 8 bits\n");
    UART_PRINTF("\tloopback   : 0 - disable, 1 - enable\n");
    UART_PRINTF("\tflowCtrl   : 0 - disable, 1 - enable\n");
    UART_PRINTF("\tExample: \n");
    UART_PRINTF("\tenable 115200 0 1 3 0 0\n");

    return;
}

qbool_t check_baud_rate(uint32_t uart_id, uint32_t baud_rate)
{
    int32_t i;
    
    for (i = 0; i < ARRAY_SIZE(baud_rate_set[uart_id]); i++){
        if (baud_rate_set[uart_id][i] == baud_rate){
            return TRUE;
        }
    }

    return FALSE;
}

QCLI_Command_Status_t qcli_uart_enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t uart_id = DATA_UART_ID_GET();
    uint32_t                     baud_rate;
    qapi_UART_Parity_Mode_e      parity_mode;
    qapi_UART_Num_Stop_Bits_e    num_stop_bits;
    qapi_UART_Bits_Per_Char_e    bits_per_char;
    qbool_t                      enable_loopback;
    qbool_t                      enable_flow_ctrl;

    qapi_Status_t status;

    if (uart_enabled(uart_id)){
        UART_PRINTF("Uart port %d is already enabled\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }

    if( Parameter_Count != 6 || !Parameter_List ) {
        uart_enable_help();
        return QCLI_STATUS_SUCCESS_E;
    }

    baud_rate = Parameter_List[0].Integer_Value;
    parity_mode = Parameter_List[1].Integer_Value;
    num_stop_bits = Parameter_List[2].Integer_Value;
    bits_per_char = Parameter_List[3].Integer_Value;
    enable_loopback = Parameter_List[4].Integer_Value ? TRUE : FALSE;
    enable_flow_ctrl = Parameter_List[5].Integer_Value ? TRUE : FALSE;;

    if (!check_baud_rate(uart_id, baud_rate)){
        UART_PRINTF("Baud rate(%d) invalid.\n", baud_rate);
        return QCLI_STATUS_ERROR_E;
    }
    
    if (!IN_RANGE(parity_mode, QAPI_UART_NO_PARITY_E, QAPI_UART_SPACE_PARITY_E)){
        UART_PRINTF("parity_mode(%d) invalid.\n", parity_mode);
        return QCLI_STATUS_ERROR_E;
    }
    if (!IN_RANGE(num_stop_bits, QAPI_UART_0_5_STOP_BITS_E, QAPI_UART_2_0_STOP_BITS_E)){
        UART_PRINTF("num_stop_bits(%d) invalid.\n", num_stop_bits);
        return QCLI_STATUS_ERROR_E;
    }
    if (!IN_RANGE(bits_per_char, QAPI_UART_5_BITS_PER_CHAR_E, QAPI_UART_8_BITS_PER_CHAR_E)){
        UART_PRINTF("bits_per_char(%d) invalid.\n", bits_per_char);
        return QCLI_STATUS_ERROR_E;
    }
    
    
    UART_PRINTF("Open uart port %d\n", uart_id);
    status = uart_init(uart_id,
                    baud_rate,
                    parity_mode,
                    num_stop_bits,
                    bits_per_char,
                    enable_loopback,
                    enable_flow_ctrl
                    );
    if (status != QAPI_OK){
        UART_PRINTF("Enable uart port failed.");
        return QCLI_STATUS_ERROR_E;
    }
    
    return QCLI_STATUS_SUCCESS_E;
}

QCLI_Command_Status_t qcli_uart_disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t uart_id = DATA_UART_ID_GET();
    qapi_Status_t status;

    //Check status of UART port
    if (!uart_enabled(uart_id)){
        UART_PRINTF("ERROR: UART %d is not enabled.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }

    if (MODE_IS_RUNNING()){
        UART_PRINTF("ERROR: Server/ECHO need to be stopped at first.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }
    
    UART_PRINTF("Close uart port %d\n", uart_id);
    g_server_tx_bytes = 0;
    g_server_rx_bytes = 0;
    mbox_size_max = 0;
    status = uart_deinit(uart_id);
    if (status != QAPI_OK){
        UART_PRINTF("uart_deinit failed.");
        return QCLI_STATUS_ERROR_E;
    }
    
    return QCLI_STATUS_SUCCESS_E;
}


QCLI_Command_Status_t qcli_start_server(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t uart_id = DATA_UART_ID_GET();
    uint32_t ip_addr;
    uint16_t tcp_port;
    int32_t ret;

    
    if( Parameter_Count != 2 
        || !Parameter_List ) {
      return QCLI_STATUS_USAGE_E;
    }

     //Check status of UART port
    if (!uart_enabled(uart_id)){
        UART_PRINTF("ERROR: UART %d is not enabled.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }

    if (MODE_IS_RUNNING()){
        UART_PRINTF("ERROR: Server/ECHO need to be stopped at first.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }
    
    ret = inet_pton(AF_INET, Parameter_List[0].String_Value, &ip_addr);
    tcp_port = Parameter_List[1].Integer_Value;

    UART_PRINTF("Start server(%s:%d) for Uart port %d\n", 
            Parameter_List[0].String_Value, tcp_port, uart_id);
    
    SET_WORK_MODE(WORK_MODE_SERVER);
    ret = uart_tcp_server_start(uart_id, ip_addr, tcp_port);
    if (0 != ret){
        UART_PRINTF("Start server failed.");
        return QCLI_STATUS_ERROR_E;
    }
    
    return QCLI_STATUS_SUCCESS_E;
}

QCLI_Command_Status_t qcli_stop_server(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    
    uint32_t uart_id = DATA_UART_ID_GET();


     //Check status of UART port
    if (!uart_enabled(uart_id)){
        UART_PRINTF("ERROR: UART %d is not enabled.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }
    
    if (!MODE_IS_SERVER()){
        UART_PRINTF("ERROR: Server is not started.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }
    
    UART_PRINTF("Stop server of uart %d\n", uart_id);
    SET_WORK_MODE(WORK_MODE_IDLE);
    
    return QCLI_STATUS_SUCCESS_E;
}

QCLI_Command_Status_t qcli_start_echo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t uart_id = DATA_UART_ID_GET();

     //Check status of UART port
    if (!uart_enabled(uart_id)){
        UART_PRINTF("ERROR: UART %d is not enabled.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }

    if (MODE_IS_RUNNING()){
        UART_PRINTF("ERROR: Server/ECHO need to be stopped at first.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }
    
    UART_PRINTF("Start echo.\n");
    SET_WORK_MODE(WORK_MODE_ECHO);
    
    if (0 != mailbox_init(MBOX_SLOT_NUM)){
        UART_PRINTF("Mail box init failed.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    uart_tx_thread_start(uart_id);
    uart_rx_thread_start(uart_id);

    return QCLI_STATUS_SUCCESS_E;
}

QCLI_Command_Status_t qcli_stop_echo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t uart_id = DATA_UART_ID_GET();
    
     //Check status of UART port
    if (!uart_enabled(uart_id)){
        UART_PRINTF("ERROR: UART %d is not enabled.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }

    if (!MODE_IS_ECHO()){
        UART_PRINTF("ERROR: Echo is not started.\n", uart_id);
        return QCLI_STATUS_ERROR_E;
    }
    
    UART_PRINTF("Stop echo.\n");
    SET_WORK_MODE(WORK_MODE_IDLE);
    
    while(!uart_rx_task_stop || !uart_tx_task_stop){
        qurt_thread_sleep(100);
    }
    mailbox_deinit();
    
    return QCLI_STATUS_SUCCESS_E;
}

QCLI_Command_Status_t qcli_console_switch(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    int32_t uart_id_new;

    uart_id_new = (QAPI_UART_DEBUG_PORT_E == g_console_uart_id) ?
                        QAPI_UART_HS_PORT_E : QAPI_UART_DEBUG_PORT_E;
    if (uart_enabled(uart_id_new)){
        UART_PRINTF("New console port(%d) needs to be disabled before switch", uart_id_new);
        return QCLI_STATUS_ERROR_E;
    }
    UART_PRINTF("Switch console uart port: %d->%d\n", g_console_uart_id, uart_id_new);
    
    PAL_Uart_Deinit();
    PAL_Uart_Init2(uart_id_new);
    g_console_uart_id = uart_id_new;
    
    return QCLI_STATUS_SUCCESS_E;
}

QCLI_Command_Status_t qcli_get_info(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t uart_id= DATA_UART_ID_GET();
    uint64_t uart_tx_bytes;
    uint64_t uart_rx_bytes;

    qbool_t     enabled;
    uint32_t                     baud_rate;
    qapi_UART_Parity_Mode_e      parity_mode;
    qapi_UART_Num_Stop_Bits_e    num_stop_bits;
    qapi_UART_Bits_Per_Char_e    bits_per_char;
    qbool_t                      enable_loopback;
    qbool_t                      enable_flow_ctrl;

    qapi_Status_t status;


    if (Parameter_Count > 0){
        return QCLI_STATUS_USAGE_E;
    }

    enabled = uart_enabled(uart_id);
    
    UART_PRINTF("UART %d: %s\n", uart_id, enabled ? "Enabled" : "Disabled");
    //UART_PRINTF("CTS/RTS supported: %s\n", QAPI_UART_HS_PORT_E == uart_id ? "Yes":"No");
    if (!enabled){
        return QCLI_STATUS_SUCCESS_E;
    }
    
    status = uart_get_stats(uart_id, &uart_tx_bytes, &uart_rx_bytes);
    if (QAPI_OK != status){
        UART_PRINTF("ERROR: Failed to get uart stats. status %d\n", status);
        return QCLI_STATUS_ERROR_E;
    }

    status = uart_get_param(uart_id, 
        &baud_rate, &parity_mode, &num_stop_bits,
        &bits_per_char, &enable_loopback, &enable_flow_ctrl);
    if (QAPI_OK != status){
        UART_PRINTF("ERROR: Failed to get uart param.\n", status);
        return QCLI_STATUS_ERROR_E;
    }
    
    UART_PRINTF("baud %d, parity %s, stopbits %s, bitsPerChar %d, loopback %s, flowctrl %s\n", 
            baud_rate,
            (parity_mode == QAPI_UART_NO_PARITY_E) ?"No"
                :(parity_mode == QAPI_UART_ODD_PARITY_E) ? "Odd"
                :(parity_mode == QAPI_UART_EVEN_PARITY_E) ? "Even"
                :(parity_mode == QAPI_UART_SPACE_PARITY_E) ? "Space":"Invalid",
            (num_stop_bits == QAPI_UART_0_5_STOP_BITS_E) ?"0.5"
                :(num_stop_bits == QAPI_UART_1_0_STOP_BITS_E) ? "1.0"
                :(num_stop_bits == QAPI_UART_1_5_STOP_BITS_E) ? "1.5"
                :(num_stop_bits == QAPI_UART_2_0_STOP_BITS_E) ? "2.0":"invalid",
            (bits_per_char == QAPI_UART_5_BITS_PER_CHAR_E) ?5
                :(bits_per_char == QAPI_UART_6_BITS_PER_CHAR_E) ? 6
                :(bits_per_char == QAPI_UART_7_BITS_PER_CHAR_E) ? 7
                :(bits_per_char == QAPI_UART_8_BITS_PER_CHAR_E) ? 8:-1,
            enable_loopback ? "on":"off",
            enable_flow_ctrl ? "on":"off"
            );

    UART_PRINTF("Work mode: %s\n", MODE_IS_SERVER()?"Server"
                                    : MODE_IS_ECHO()?"Echo":"Idle");
    UART_PRINTF("  UART tx: %llu Bytes\n", uart_tx_bytes);
    UART_PRINTF("  UART rx: %llu Bytes\n", uart_rx_bytes);
    UART_PRINTF("  Server tx: %llu Bytes\n", g_server_tx_bytes);
    UART_PRINTF("  Server rx: %llu Bytes\n", g_server_rx_bytes);
    UART_PRINTF("  mbox_size_max: %u Bytes\n", mbox_size_max);
    
    return QCLI_STATUS_SUCCESS_E;
}

QCLI_Command_Status_t qcli_clear_stats(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t uart_id = DATA_UART_ID_GET();

    qapi_Status_t status;

    if (Parameter_Count > 0){
        return QCLI_STATUS_USAGE_E;
    }

    g_server_tx_bytes = 0;
    g_server_rx_bytes = 0;
    mbox_size = 0;
    mbox_size_max = 0;
    
    status = uart_clear_stats(uart_id);
    if (QAPI_OK == status){
        UART_PRINTF("Cleared.\n");
        return QCLI_STATUS_SUCCESS_E;
    }
    else{
        UART_PRINTF("Clear failed.\n");
        return QCLI_STATUS_ERROR_E;
    }
}

int32_t mailbox_init(int32_t slot_num)
{
    g_mail_box = OSAL_Create_Mailbox(slot_num, sizeof(void*));
    if (NULL == g_mail_box){
        UART_PRINTF("Mail box created failed.\n");
        return -1;
    }
    
    qurt_mutex_init(&mbox_mutex);
    
    mbox_size = 0;
    mbox_size_max = 0;

    return 0;
}

int32_t mailbox_deinit()
{
    OSAL_Delete_Mailbox(g_mail_box);
    qurt_mutex_destroy(&mbox_mutex);
    mbox_size = 0;
    mbox_size_max = 0;

    return 0;
}

int32_t tcp_socket_init(uint32_t ip_addr, uint16_t tcp_port)
{
    int32_t sock_fd = -1;
    int family;
    struct sockaddr_in local_addr;
    uint32_t addr_len;
    int opt;
    int32_t ret;
    
    //Create
    family = AF_INET;
    sock_fd = qapi_socket(family, SOCK_STREAM, 0);
    if (A_ERROR == sock_fd){
        UART_PRINTF("ERROR: Socket created failed.\n");
        return -1;
    }

    //Bind
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_port = htons(tcp_port);
    local_addr.sin_family = family;
    local_addr.sin_addr.s_addr = ip_addr;
    addr_len = sizeof(struct sockaddr_in);
    ret = qapi_bind(sock_fd, (struct sockaddr *)&local_addr, addr_len);
    if (A_ERROR == ret){
        UART_PRINTF("ERROR: bind failed\n");
        qapi_socketclose(sock_fd);
        return -1;
    }
    
    //Set Opt
    /* set to non-blocking mode */
	ret = qapi_setsockopt(sock_fd, SOL_SOCKET, SO_NBIO, NULL, 0);
    if (A_ERROR == ret){
        UART_PRINTF("ERROR: set socketopt non-blocking failed\n");
        qapi_socketclose(sock_fd);
        return -1;
    }

    opt = 1;
    ret = qapi_setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (A_ERROR == ret){
        UART_PRINTF("ERROR: set socketopt SO_REUSEADDR to be 1 failed\n");
        qapi_socketclose(sock_fd);
        return -1;
    }
    
    return sock_fd;
}

int32_t client_socket_get(int32_t server_sock)
{
    int32_t client_sock = 0;
    struct sockaddr_in foreign_addr;
    struct sockaddr *from;
    int32_t fromlen;
    int32_t ret;

    int32_t window_size = 65536;   /*Default size is 32K */
    int32_t window_size_len = sizeof(int32_t);

    
    from = (struct sockaddr *)&foreign_addr;
    fromlen = sizeof(struct sockaddr_in);

    //Listen
    ret = qapi_listen(server_sock, 1);
    if (A_ERROR == ret){
        UART_PRINTF("ERROR: listen failed\n");
        return INVALID_SOCKFD;
    }

    //Accept
    while(TRUE){
        if (!MODE_IS_RUNNING()){
            return INVALID_SOCKFD;
        }
        client_sock = qapi_accept(server_sock, from, &fromlen);
        if (INVALID_SOCKFD == client_sock){
            qurt_thread_sleep(1000);
            continue;
        }
        else{
            UART_PRINTF("New client: %s:%d\n", 
                ip2str(htonl(from->u.sin.sin_addr.s_addr)),
                from->sa_port);
            break;
        }
    }

    /* Set non-blocking mode */
	ret = qapi_setsockopt(client_sock, SOL_SOCKET, SO_NBIO, NULL, 0);
    if (A_ERROR == ret){
        UART_PRINTF("ERROR: set socketopt non-blocking failed\n");
        qapi_socketclose(client_sock);
        return INVALID_SOCKFD;
    }
    
    qapi_setsockopt(client_sock,SOL_SOCKET, SO_SNDBUF, &window_size, window_size_len);
    if (0 != ret){
        UART_PRINTF("Set socket window size failed.\n");
        qapi_socketclose(client_sock);
        return INVALID_SOCKFD;
    }
    else{
        UART_PRINTF("Set client socket window size = %d OK\n", window_size);
    }

    return client_sock;
}


int uart_sprintf(char *buf, char *format, ...)
{
   int     ret_val;
   va_list args;

   va_start(args, format);
   ret_val = vsprintf(buf, format, args);
   va_end(args);

   return(ret_val);
}

char *ip2str(uint32_t ip)
{
    static char buf[32] = {0};
    uart_sprintf(buf, "%u.%u.%u.%u", 
        (ip>>24) & 0xff,
        (ip>>16) & 0xff,
        (ip>>8) & 0xff,
        (ip>>0) & 0xff
        );
    return buf;
}

int32_t send_to_client(int32_t sock_fd, uint8_t *buf, int32_t len)
{
    static uint32_t old_ticks = 0;
    static uint32_t new_ticks = 0;
    
    qbool_t is_sent = FALSE;
    int32_t tx_len;
    int32_t ret;


    if (0 == client_tx_cache_len && 0 == len){
        return 0;
    }
    
    //Update ticks
    if (0 == old_ticks){ //Init
        old_ticks = OSAL_Get_System_Ticks();
    }
    new_ticks = OSAL_Get_System_Ticks();

    //Send packet to WiFi
    if (client_tx_cache_len + len >= CLIENT_TX_CACHE_BUF_SIZE){  //Over length
        //UART_PRINTF("Over length\n");
        tx_len = client_tx_cache_len;
        ret = qapi_send(sock_fd, (char*)client_tx_cache_buf, tx_len, 0);
        is_sent = TRUE;
        memcpy(&client_tx_cache_buf[0], buf, len);
        client_tx_cache_len = len;
    }
    else{  
        memcpy(&client_tx_cache_buf[client_tx_cache_len], buf, len); 
        client_tx_cache_len += len;
        
        if (new_ticks - old_ticks >= UART_TIMEOUT_TICKS){  //Over time
            tx_len = client_tx_cache_len;
            old_ticks = new_ticks;  //Update Old ticks.
            ret = qapi_send(sock_fd, (char*)client_tx_cache_buf, tx_len, 0);
            is_sent = TRUE;
            client_tx_cache_len = 0;
        }
    }

    if (is_sent){
        if (-1 == ret){
            UART_PRINTF("Socket send %d bytes failed.errno = %d\n", tx_len, qapi_errno(sock_fd));
            return -1;
        }
        if (ret != tx_len){
            UART_PRINTF("Socket send: Expected %d bytes, actual %d bytes\n", tx_len, ret);
        }
        g_server_tx_bytes += ret;
    }
    
    return 0;
}

int32_t init_tx_cache_buf()
{
    client_tx_cache_buf = (uint8_t *)malloc(CLIENT_TX_CACHE_BUF_SIZE);
    if (NULL == client_tx_cache_buf){
        UART_PRINTF("ERROR: failed to alloc tx cache buf\n");
        return -1;
    }
    client_tx_cache_len = 0;  /*Init value*/
    return 0;
}

int32_t deinit_tx_cache_buf()
{
    if (NULL != client_tx_cache_buf){
        free(client_tx_cache_buf);
        client_tx_cache_buf = NULL;
    }
    client_tx_cache_len = 0;
    return 0;
}

static void uart_rx_thread(void *Param)
{
    qapi_UART_Port_Id_e uart_id = (qapi_UART_Port_Id_e)Param;
    int32_t sock_fd = g_uart_client_sock_fd;
    
    UART_BUF_T *uart_buf = NULL;
    uint8_t *mbox_buf = NULL;
    int32_t mbox_len = 0;
    int32_t ret;


    uart_rx_task_stop = FALSE;

    uart_buf = (UART_BUF_T *)malloc(sizeof(UART_BUF_T));
    if (NULL == uart_buf){
        UART_PRINTF("ERROR: failed to alloc uart buf\n");
        goto exit;
    }
    if (MODE_IS_SERVER()){
        if (0 != init_tx_cache_buf()){
            UART_PRINTF("ERROR: failed to init cache buf\n");
            goto exit;
        }
    }
    
    
    while(TRUE){
        if (!MODE_IS_RUNNING()){
            goto exit;
        }
        
        //Receive data from UART
        uart_buf->size = uart_read(uart_id, uart_buf->data, UART_RX_BUF_SIZE, UART_TIMEOUT_TICKS);
        if (-1 == uart_buf->size){ //Error
            goto exit;
        }

        if (MODE_IS_SERVER()){
            ret = send_to_client(sock_fd, uart_buf->data, uart_buf->size);
            if (0 != ret){
                UART_PRINTF("ERROR: failed to send buf to client\n");
                //goto exit;
            }
        }
        else if (MODE_IS_ECHO()){
            if (0 == uart_buf->size){
                continue;
            }
            
            /*Send actual size instead of whole UART_BUF_T*/
            mbox_buf = (uint8_t *)malloc(uart_buf->size + sizeof(mbox_len));
            if (NULL == mbox_buf){
                UART_PRINTF("Fail to allocate buf ro mbox\n");
                goto exit;
            }
            mbox_len = uart_buf->size;
            memcpy(mbox_buf, &mbox_len, sizeof(mbox_len));
            memcpy(mbox_buf + sizeof(mbox_len), uart_buf->data, mbox_len);
            
            if (OSAL_Add_To_Mailbox(g_mail_box, &mbox_buf)){
                if (MUTEX_LOCK(mbox_mutex)){
                    mbox_size += mbox_len;
                    if (mbox_size_max < mbox_size){
                        mbox_size_max = mbox_size;
                    }
                    MUTEX_UNLOCK(mbox_mutex);
                }
                else{
                    UART_PRINTF("mutex lock failed.\n");
                }
            }
            else{
                UART_PRINTF("ERROR: Add to mailbox failed.\n");
            }
        }
    }
    

exit:
    UART_PRINTF("UART %d rx thread quit.\n", uart_id);
    if (NULL != uart_buf){
        free(uart_buf);
    }
    deinit_tx_cache_buf();
    
    uart_rx_task_stop = TRUE;
    qurt_thread_stop();
}


static void uart_tx_thread(void *Param)
{
    qapi_UART_Port_Id_e uart_id = (qapi_UART_Port_Id_e)Param;
    qapi_Status_t status;

    uint8_t *mbox_buf = NULL;
    int32_t mbox_len = 0;

    
    uart_tx_task_stop = FALSE;
    
    while(TRUE){
        if(OSAL_Wait_Mailbox(g_mail_box, 100, &mbox_buf))
        {
            
            memcpy(&mbox_len, mbox_buf, sizeof(mbox_len));
            //UART_PRINTF("Recv %d bytes from mailbox\n", mbox_len);
            status = uart_write(uart_id, (char*)(mbox_buf + sizeof(mbox_len)), mbox_len);
            if (MUTEX_LOCK(mbox_mutex)){
                mbox_size -= mbox_len;
                MUTEX_UNLOCK(mbox_mutex);
            }
            else{
                UART_PRINTF("mutex lock failed.\n");
            }
            
            free(mbox_buf);
            if (status != QAPI_OK){
                UART_PRINTF("Error: Uart writing failed.\n");
                goto exit;
            }
        }
        else{
            if (!MODE_IS_RUNNING()){
                goto exit;
            }
        }
    }

exit:
    UART_PRINTF("UART %d tx thread quit.\n", uart_id);
    uart_tx_task_stop = TRUE;
    qurt_thread_stop();
}

void uart_rx_thread_start(uint32_t uart_id)
{
    qurt_thread_attr_t thread_attr;
    qurt_thread_t      thread_handle;
    int                result;
    char task_name[16] = {0};

    uart_sprintf(task_name, "UartRx%d", uart_id);
    UART_PRINTF("Start task: %s\n", task_name);
    /* Start the main demo thread. */
    qurt_thread_attr_init(&thread_attr);
    qurt_thread_attr_set_name(&thread_attr, task_name);
    qurt_thread_attr_set_priority(&thread_attr, UART_THREAD_PRIORITY);
    qurt_thread_attr_set_stack_size(&thread_attr, UART_THREAD_STACK_SIZE);
    result = qurt_thread_create(&thread_handle, 
                    &thread_attr, 
                    uart_rx_thread, 
                    (void*)uart_id);
    if(result != QURT_EOK)
    {
        UART_PRINTF("Failed to start thread %s.\n", task_name);
    }

}

void uart_tx_thread_start(uint32_t uart_id)
{
    qurt_thread_attr_t thread_attr;
    qurt_thread_t      thread_handle;
    int                result;
    char task_name[16] = {0};

    uart_sprintf(task_name, "UartTx%d", uart_id);
    UART_PRINTF("Start task: %s\n", task_name);
    /* Start the main demo thread. */
    qurt_thread_attr_init(&thread_attr);
    qurt_thread_attr_set_name(&thread_attr, task_name);
    qurt_thread_attr_set_priority(&thread_attr, UART_THREAD_PRIORITY);
    qurt_thread_attr_set_stack_size(&thread_attr, UART_THREAD_STACK_SIZE);
    result = qurt_thread_create(&thread_handle, 
                    &thread_attr, 
                    uart_tx_thread, 
                    (void*)uart_id);
    if(result != QURT_EOK)
    {
        UART_PRINTF("Failed to start thread %s.\n", task_name);
    }
}

    
int32_t uart_tcp_server_start(uint32_t uart_id, uint32_t ip_addr, uint16_t tcp_port)
{
    int32_t server_sock = INVALID_SOCKFD;
    int32_t client_sock = INVALID_SOCKFD;
    fd_set rd_set;
    fd_set tmp_rd_set;
    int32_t sock_num;
    
    uint8_t *buf = NULL;
    int32_t len;
    //int32_t ret;
    qapi_Status_t status;


    buf = (uint8_t *)malloc(TCP_BUF_LEN);
    if (NULL == buf){
        UART_PRINTF("ERROR: Failed to alloc memory for tcp rx buf\n");
        //Fail message
        return -1;
    }

    //Create server socket
    server_sock = tcp_socket_init(ip_addr, tcp_port);
    if (INVALID_SOCKFD == server_sock){
    UART_PRINTF("ERROR: Init tcp socket failed.\n");
        goto exit;
    }
    g_uart_serv_sock_fd = server_sock;

    //Get client socket
    client_sock = client_socket_get(server_sock);
    if (INVALID_SOCKFD == client_sock){
        if (!MODE_IS_SERVER()){
            UART_PRINTF("Server quit.\n");
            goto exit;
        }
        else{
            UART_PRINTF("ERROR: Failed to get client socket.\n");
            goto exit;
        }
    }
    g_uart_client_sock_fd = client_sock;
    g_server_tx_bytes = 0;  //Reset stats
    g_server_rx_bytes = 0;  //Reset stats

    uart_rx_thread_start(uart_id);
    
    /* Loop waiting for received data. */
    qapi_fd_zero(&rd_set);
    qapi_fd_set(client_sock, &rd_set);
    while(TRUE){
        if (!MODE_IS_SERVER()){
            UART_PRINTF("UART %d tx thread quit.\n", uart_id);
            break;
        }
        tmp_rd_set = rd_set; //Restore fd set every time
        sock_num = qapi_select(&tmp_rd_set, NULL, NULL, 100);
        if (0 == sock_num){
            continue;
        }
        if (qapi_fd_isset(client_sock, &tmp_rd_set)){
            //Receive data from clientSockFd
            len = qapi_recv(client_sock, (char*)buf, TCP_BUF_LEN, 0);
            if (-1 == len){
                UART_PRINTF("ERROR: qapi_recv failed with ret %d\n", len);
                break;
            }
            if ( 0 == len){
                UART_PRINTF("Recv 0 bytes, errno = %d\n", qapi_errno(g_uart_client_sock_fd));
                continue;
            }
            g_server_rx_bytes += len;
            //Send data to UART
            //UART_PRINTF("Write %d bytes to uart id %d\n", len, uart_id);
            status = uart_write(uart_id, (char *)buf, len);
            if (QAPI_OK != status){
                UART_PRINTF("ERROR: uart_write failed with ret %d\n", status);
                break;
            }            
        }

     }

exit:
    if (server_sock != INVALID_SOCKFD){
        qapi_socketclose(server_sock);
        g_uart_serv_sock_fd = INVALID_SOCKFD;
    }
    if (client_sock != INVALID_SOCKFD){
        qapi_socketclose(client_sock);
        g_uart_client_sock_fd = INVALID_SOCKFD;
    }
    if (buf != NULL){
        free(buf);
    }
    
    return 0;
}

