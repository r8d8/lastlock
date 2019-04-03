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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "iotd_context.h"
#include "mml.h"
#include "dataManager.h"
#include "ipcManager.h"
#include "iotdManager.h"
#include "bufpool.h"

/********************************************************************************/
/* unit test setting */
//#define UNIT_TESTS

/*******************************************************************************/
extern void run_unit_tests(void* pCxt);
extern int cfg_init(void* cxt);

/********************************************************************************/
int run_daemon = 1;

/********************************************************************************/

int init_cxt(void** pCxt)
{
    if((*pCxt = malloc(sizeof(IOTD_CXT_T))) == NULL)
    {
        exit(EXIT_FAILURE);
    }

    memset(*pCxt, 0, sizeof(IOTD_CXT_T));
    return IOTD_OK;
}


int deinit_cxt(void* pCxt)
{
    if(pCxt)
        free(pCxt);

    return IOTD_OK;
}

int init_log(const char* ident)
{
    /* Open system log */
    openlog(ident, LOG_PID|LOG_CONS, LOG_DAEMON);
    syslog(LOG_INFO, "Started iot daemon");
    return 0;
}

int init_modules(void* pCxt)
{
    if(cfg_init(pCxt) != IOTD_OK){
        return IOTD_ERROR;
    }

    if(dbg_init(pCxt) != IOTD_OK){
        return IOTD_ERROR;
    }

    if( buf_init(pCxt) != IOTD_OK) {
            return IOTD_ERROR;
    }

    if(mml_init(pCxt) != IOTD_OK){
        return IOTD_ERROR;
    }

    if( iotdManagement_init(pCxt) != IOTD_OK) {
        return IOTD_ERROR;
    }
    
    if(ipcManager_init(pCxt) != IOTD_OK){
        return IOTD_ERROR;
    }

    if(diagManager_init(pCxt) != IOTD_OK){
        return IOTD_ERROR;
    }

    if(dataManager_init(pCxt)!= IOTD_OK){
        return IOTD_ERROR;
    }

    return IOTD_OK;
}

int deinit_modules(void* pCxt)
{
    if(dataManager_deinit(pCxt) != IOTD_OK){
        return IOTD_ERROR;
    }

    diagManager_deinit(pCxt);

    ipcManager_deinit(pCxt);

    iotdManagement_deinit(pCxt);

    mml_deinit(pCxt);

    return IOTD_OK;
}

#ifdef DAEMONIZE
/**
 * \brief This function will daemonize this app
 */
static void start_daemon()
{
    pid_t proc_id = 0;

    /* Fork new process*/
    if((proc_id = fork()) < 0)
    {
        exit(EXIT_FAILURE);
    }

    /* fork successful */
    if (proc_id > 0)
    {
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0)
    {
        exit(EXIT_FAILURE);
    }


    return;
}
#endif /* DAEMONIZE */

void handle_signal(int sig)
{
    syslog(LOG_INFO, "Received signal %d\n",sig);
    run_daemon = 0;
    return;
}

void handle_sighup(int sig)
{
}

/* Main function */
int main(int argc, char *argv[])
{
    IOTD_CXT_T* pCxt;

#ifdef DAEMONIZE
    start_daemon();
#endif /* DAEMONIZE */

    /* Daemon will handle following signals */
    signal(SIGINT, handle_signal);
    signal(SIGHUP, handle_sighup);
    signal(SIGTERM, handle_signal);

    /*Initialize daemon context*/
    init_cxt((void**)&pCxt);

    init_log(argv[0]);

    /*Has caller provided a configuration file, if so check it first*/
    if(argc > 1)
        pCxt->cfg_file = argv[1];
    else
        pCxt->cfg_file = NULL;
 
    /*Initialize iot daemon modules*/
    if(init_modules(pCxt) != IOTD_OK){
        goto STOP_DAEMON;
    }

#ifdef GPIO_PROFILING
    setupGPIOToggle(42);
#endif

    IOTD_LOG(LOG_TYPE_CRIT,"***** IOT Daemon started ****\n");

    while(run_daemon)
    {
        sleep(1);
#ifdef UNIT_TESTS
        run_unit_tests(pCxt);
#endif
        run_throughput_test(pCxt);
    }

STOP_DAEMON:
    IOTD_LOG(LOG_TYPE_CRIT,"!!!! Stopping IOT Daemon !!!!\n");
    deinit_modules(pCxt);

    deinit_cxt(pCxt);
    return 0;
}
