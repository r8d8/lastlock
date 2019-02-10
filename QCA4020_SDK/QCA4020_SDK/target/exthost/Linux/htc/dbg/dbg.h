/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
 * Copyright (c) 2004-2006 Atheros Communications Inc.
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

#ifndef _DBG_H_
#define _DBG_H_

enum {
    HTC_PRINT_GRP0_HIF=0x01,
    HTC_PRINT_GRP1=0x02,
    HTC_PRINT_GRP2=0x04,
    HTC_PRINT_GRP_WORK_TASK=0x04,
    HTC_PRINT_GRP3=0x08,
	 HTC_PRINT_GRP4=0x10,
	 HTC_PRINT_GRP5=0x20,
	 HTC_PRINT_GRP6=0x40,
	 HTC_PRINT_GRP7=0x80,
	 HTC_PRINT_GRP8=0x100,
	 HTC_PRINT_GRP9=0x200,
	HTC_PRINT_GRP10=0x400,
	HTC_PRINT_GRP11=0x800,
	HTC_PRINT_GRP12=0x1000,
	HTC_PRINT_GRP13=0x2000,
	HTC_PRINT_GRP14=0x4000,
	HTC_PRINT_GRP15=0x8000,
	HTC_PRINT_GRP16=0x10000,
	HTC_PRINT_GRP17=0x20000,
	HTC_PRINT_GRP0= 0x40000,

    HTC_PRINT_GRP_ERR= 0x80000000,    
};

#ifdef  DEBUG_HTC
void HTCPrintf(uint32_t print, char *fmt,...);
#else
#define HTCPrintf(print, fmt,...)
#endif

void HTCPrintSetMask (int pos, uint32_t new_mask);
void htc_printf(char *fmt,...);

#endif
