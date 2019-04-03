/*
 * Copyright (c) 2015-2018 Qualcomm Technologies, Inc.
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
#include <unistd.h>
#include <sys/sysinfo.h>
#include "qurt_timer.h"

qurt_time_t qurt_timer_convert_time_to_ticks(qurt_time_t time, qurt_time_unit_t unit_of_time )
{
    long int ticks_per_second = sysconf(_SC_CLK_TCK);

    switch (unit_of_time)
    {
        case QURT_TIME_TICK :
            return time;

        case QURT_TIME_MSEC :
            return (((time * ticks_per_second) + 999)/1000); // Round up

        case QURT_TIME_SEC :
            return (time * ticks_per_second); // Round up

        default :
            return QURT_TIME_WAIT_FOREVER;
    }
}

qurt_time_t qurt_timer_convert_ticks_to_time(qurt_time_t ticks, qurt_time_unit_t time_unit)
{
    long int ticks_per_second = sysconf(_SC_CLK_TCK);

    switch (time_unit)
    {
        case QURT_TIME_TICK :
            return ticks;

        case QURT_TIME_MSEC :
            return ((ticks * 1000)/ticks_per_second);

        case QURT_TIME_SEC :
            return (ticks/ticks_per_second);

        default :
            return QURT_TIME_WAIT_FOREVER;
    }
}


qurt_time_t qurt_timer_get_ticks (void)
{
    struct sysinfo info;
    long int ticks_per_second = sysconf(_SC_CLK_TCK);

    if(0 != sysinfo(&info))
    {
        printf("sysinfo() failed\n");
    }

    return ((uint32)(info.uptime * ticks_per_second));
}

