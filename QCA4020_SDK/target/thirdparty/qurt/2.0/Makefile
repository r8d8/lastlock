#/*=====================================================================
#   Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
#    
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted (subject to the limitations in the
#   disclaimer below) provided that the following conditions are met:
#    
#      * Redistributions of source code must retain the above copyright
#        notice, this list of conditions and the following disclaimer.
#    
#      * Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials provided
#        with the distribution.
#    
#      * Neither the name of The Linux Foundation nor the names of its
#        contributors may be used to endorse or promote products derived
#        from this software without specific prior written permission.
#    
#   NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
#   GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
#   HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
#   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
#   IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
#   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
#   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
#   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
#   IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
#   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
#
#=====================================================================*/
#    MakeFile to build QuRT library with GCC, GNU tool chain.
#
#    Please use this as reference file for building QuRT Library. 
#
#    In order to build QuRT library following dependencies has to be met - 
#    1. Update to INCLUDES PATH with location of QuRT header files and 
#       other header files supplied by SDK.
#    2. Update to INCLUDES PATH with location of FreeRTOS header files.
#
#=====================================================================*/

default: all

OBJDIR = obj
OUTDIR = output
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
RM = rm -rf

#Specify COPT FLAGS
COPTS := -c -g -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mfloat-abi=hard -fno-inline-functions -Os -O3 -fno-zero-initialized-in-bss -std=c99 -fno-short-enums -mapcs-frame -gdwarf-3

#Specify preprocessor flag/feature defines
DEFINES := -D FEATURE_MUTEX_PI_RECURSIVE -D QURT_THREAD_MAX_PRIORITIES=32

ROOT=../../..
AWSROOT=../../aws_freertos/
AWSCOMM=$(AWSROOT)/demos/qcom/qca402x/common

#Specify Include paths here
INCLUDES := \
   -I$(AWSCOMM)/application_code/qcom_code \
   -I$(AWSCOMM)/config_files \
   -I$(AWSROOT)/lib/include \
   -I$(AWSROOT)/lib/include/private \
   -I$(ROOT)/include/bsp
   
#Set CFLAGS
CFLAGS = $(COPTS) $(DEFINES) $(INCLUDES)
ASFLAGS = $(ASOPTS)

#Specify Source files here
CSRCS_EXCLUDE = qurt_interrupt.c
CSRCS = $(filter-out $(CSRCS_EXCLUDE),$(wildcard *.c))
SRCS_SOM = qurt_interrupt.c qurt_interrupt_asm.S

#List of obj files   
OBJS := $(CSRCS:.c=.o)
OBJS_SOM = qurt_interrupt.o qurt_interrupt_asm.o

# Rule : all
all: qurt.lib qurt_shared.lib

# Rule : qurt.lib 
qurt.lib: $(OBJS)
	$(AR) -r $(OUTDIR)/$@ $(filter-out $(OBJS_SOM), $(OUTDIR)/*.o)
   
# Rule : qurt_shared.lib 
qurt_shared.lib: $(OBJS_SOM)
	$(AR) -r $(OUTDIR)/$@ $(OUTDIR)/qurt_interrupt.o $(OUTDIR)/qurt_interrupt_asm.o
    
# Generate object files
%.o: %.c
	@echo Compiling $<	
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -c -o $(OUTDIR)/$(@F) $^
   
# Generate object files
%.o: %.S
	@echo Compiling $<	
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -c -o $(OUTDIR)/$(@F) $^
    
# Rule : clean
clean :
	rm -rf $(OUTDIR)

