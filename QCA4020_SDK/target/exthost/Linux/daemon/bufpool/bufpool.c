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

#define DEFAULT_MAX_BUF_COUNT (20)

uint16_t buf_count = 0;
uint16_t buf_max_num = DEFAULT_MAX_BUF_COUNT;

pthread_mutex_t pool_lock = PTHREAD_MUTEX_INITIALIZER;

int bufpool_alloc(void* pCxt)
{
    return IOTD_OK;
}

int bufpool_free(void* pCxt)
{
    return IOTD_OK;
}

int buf_init(void* pCxt)
{
    IOTD_CXT_T* iotdCxt = (IOTD_CXT_T*)pCxt;
    cfg_ini* cfg;

    if(iotdCxt == NULL)
    {
        return IOTD_ERROR;
    }

    pthread_mutex_lock(&pool_lock);
    buf_count = 0;   
    cfg = &(iotdCxt->cfg);    
    buf_max_num = cfg->config_system.num_buffer;
    pthread_mutex_unlock(&pool_lock);
    
    return IOTD_OK;
}

void* buf_alloc(uint32_t size)
{
    char *buf = NULL;
    
    if(buf_count < buf_max_num){
        pthread_mutex_lock(&pool_lock);
        buf_count++;
        pthread_mutex_unlock(&pool_lock);
        if((buf = (char *)malloc(size)) != NULL){
            memset(buf, 0, size);
        }

        return buf;
    }else
        return NULL;

}

void buf_free(void* buf)
{
    pthread_mutex_lock(&pool_lock);
    buf_count--;
    pthread_mutex_unlock(&pool_lock);
    free(buf);
}
