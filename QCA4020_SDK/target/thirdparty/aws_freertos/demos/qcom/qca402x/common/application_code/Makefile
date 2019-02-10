# Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
# 2016 Qualcomm Atheros, Inc.
# All Rights Reserved.
# Copyright (c) 2018 Qualcomm Technologies, Inc.
# All rights reserved.
# Redistribution and use in source and binary forms, with or without modification, are permitted (subject to the limitations in the disclaimer below)
# provided that the following conditions are met:
# Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
# Neither the name of Qualcomm Technologies, Inc. nor the names of its contributors may be used to endorse or promote products derived
# from this software without specific prior written permission.
# NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
# BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
# OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#/***************************************************************************************
#    Copyright (c) 2015-2018 Linux Foundation.
#    All rights reserved.
#    
#    Redistribution and use in source and binary forms, with or without modification, 
#    are permitted (subject to the limitations in the disclaimer below)provided that 
#    the following conditions are met:
#
#    1.Redistributions of source code must retain the above copyright notice, this list
#      of conditions and the following disclaimer.
#    
#    2.Redistributions in binary form must reproduce the above copyright notice, this list
#      of conditions and the following disclaimer in the documentation and/or other 
#      materials provided with the distribution.
#    
#    3.Neither the name of [Owner Organization] nor the names of its contributors may be
#      used to endorse or promote products derived from this software without specific 
#      prior written permission.
#       
#    NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS 
#    LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
#    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
#    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR APARTICULAR PURPOSE ARE
#    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER ORCONTRIBUTORS BE LIABLEFOR ANY
#    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIALDAMAGES (INCLUDING,
#    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
#    OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
#    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE  OR OTHERWISE)
#    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
#    OF SUCH DAMAGE.
#
#****************************************************************************************/
#
#****************************************************************************************/
#    MakeFile to build FreeRTOS library with GCC, GNU tool chain
#
#    Please use this as reference file for building FreeRTOS Library. 
#
#    In order to build FreeRTOS library following dependencies has to be met - 
#    1. Update to INCLUDES PATH with location of FreeRTOS header files.
#    2. Update to INCLUDES PATH with location of FreeRTOSConfig.h
#    3. Update to INCLUDES PATH with location of portmacro.h
#    4. Update to SOURCE PATH with location of port.c
#
#****************************************************************************************/
default: all

OBJDIR = obj
OUTDIR = output
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
RM = rm -rf

#Specify COPT FLAGS
COPTS := -c -g -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mfloat-abi=hard \
	 -fno-inline-functions -Os -O3 -fno-zero-initialized-in-bss -std=c99 \
	 -fno-short-enums -mapcs-frame -gdwarf-3

#Specify preprocessor flag/feature defines
DEFINES := 

AWSROOT          = ../../../../..

#Specify Include paths here
INCLUDES := \
   -I./qcom_code \
   -I../config_files \
   -I$(AWSROOT)/lib/include \
   -I$(AWSROOT)/lib/include/private

#Set CFLAGS
CFLAGS = $(COPTS) $(DEFINES) $(INCLUDES)

#Specify Source files here
CSRCS = \
   $(AWSROOT)/lib/FreeRTOS/tasks.c \
   $(AWSROOT)/lib/FreeRTOS/queue.c \
   $(AWSROOT)/lib/FreeRTOS/stream_buffer.c \
   $(AWSROOT)/lib/FreeRTOS/event_groups.c \
   $(AWSROOT)/lib/FreeRTOS/list.c \
   $(AWSROOT)/lib/FreeRTOS/timers.c \
   $(AWSROOT)/lib/FreeRTOS/portable/MemMang/heap_4.c \
   ./qcom_code/port.c

#List of obj files
OBJS := $(CSRCS:.c=.o)

# Rule : all
all: free_rtos.lib

# Rule : free_rtos.lib
free_rtos.lib: $(OBJS)
	$(AR) -r $(OUTDIR)/$@ $(OUTDIR)/*.o

# Generate object files
%.o: %.c
	@echo Compiling $<	
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -c -o $(OUTDIR)/$(@F) $^

# Rule : clean
clean :
	rm -rf $(OUTDIR)

