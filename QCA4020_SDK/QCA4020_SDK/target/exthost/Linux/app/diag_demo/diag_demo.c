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

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <mqueue.h>
#include <pthread.h>
#include <time.h>
#include "diag_api.h"

#define MAX_BUF_SIZE        1024
#define HEADER_LEN          20
#define DEFAULT_BUF_LEN     256

static int check_usage(int argc, char *argv[])
{
    if( argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        printf("diag_demo [interval] [packet_size]\n");
        exit(0);
    }
    return 1;
}

/*
 * 
 */
int main(int argc, char *argv[])
{
    void* hdl = NULL;
    char *buf_s = NULL, *buf_r = NULL;
    char *endptr, *str;
    long len = 0;
    int buf_len = DEFAULT_BUF_LEN;
    int i, interval, ret;
    struct   timespec  end, tm ;
    
    check_usage(argc, argv);
    
    if( argc < 2) 
    {
        interval = 1;
        buf_len = DEFAULT_BUF_LEN;
    } else {
        str = argv[1];
        interval = (int) strtol(str, &endptr, 10);
        
        if( argc > 2)
        {
            str = argv[2];
            buf_len = (int) strtol(str, &endptr, 10);
            buf_len=buf_len>MAX_BUF_SIZE?MAX_BUF_SIZE:buf_len;
        }
    }
    buf_s = malloc(buf_len+HEADER_LEN);
    buf_r = malloc(buf_len+HEADER_LEN);
    if( (buf_s == NULL) || (buf_r == NULL) )
    {
        printf("Error to malloc....\n");
        return -1;
    } 
    
    /* init sending buffer */
    for(i=0; i < buf_len; i++)
    {
        buf_s[i] = (char ) i&0xff;
    }
    
    hdl = diag_open("/iotdiag");
    if(!hdl)
        return -1;

    clock_gettime(CLOCK_REALTIME, &end);

    end.tv_sec += interval;
    ret = 1;
    
    while(1) {
        clock_gettime(CLOCK_REALTIME, &tm);
        if( (tm.tv_sec >= end.tv_sec) && (tm.tv_nsec >= end.tv_nsec) )
            break;
        /* send test data */
        if( diag_send(hdl, 0, buf_s, buf_len) == -1)
        {
            printf("Fail to send test data ....\nTest abort\n");
            break;
        }
        
        /* receive test data */
        if((ret = diag_recv(hdl, buf_r, buf_len+HEADER_LEN, 5500)) != -1){
            /* compare receive data */
            if( memcmp(buf_s, buf_r, buf_len) != 0 )
            {
                printf("Received data don't match original data\nTest abort\n");
                break;
            }    
            len += ret;
        } else {
            break;
        }
    }
    diag_close(hdl);
    if( buf_s != NULL)
        free(buf_s);
    if( buf_r != NULL)
        free(buf_r);
    
    printf("Sent and Received %ld bytes with %d seconds (%ldkbps)\n", len, interval, len/interval/1000*8);
    
    return 1;
}
