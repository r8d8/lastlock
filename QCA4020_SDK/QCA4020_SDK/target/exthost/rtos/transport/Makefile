
# Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
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

# Choose which interconnect to use (EXACTLY ONE of these)
ifeq ($(CFG_INTERCONNECT_SPI),)
ifeq ($(CFG_INTERCONNECT_SDIO),)
  CFG_INTERCONNECT_SPI = false
  CFG_INTERCONNECT_SDIO = true
endif
endif

CSRCS := transport.c spi_hal.c sdio_hal.c
OBJS := $(CSRCS:%.c=%.o)
CC := arm-none-eabi-gcc

ROOTDIR := ../../..

INCLUDES := -I"$(ROOTDIR)/include" \
            -I"$(ROOTDIR)/include/qapi" \
	    -I../include \
	    -I.


COPTS := -c -g -mcpu=cortex-m4 -mthumb -fno-short-enums -O2 -ffunction-sections -Wall
CFLAGS := $(COPTS) $(INCLUDES)
CFLAGS += -D V2
CFLAGS += -D _WANT_IO_C99_FORMATS

ifeq ($(CFG_INTERCONNECT_SPI),true)
   CFLAGS += -D SPI_TRANSPORT
endif

ifeq ($(CFG_INTERCONNECT_SDIO),true)
   CFLAGS += -D SDIO_TRANSPORT
endif

all: $(OBJS)
	$(foreach D, $(LIBS), $(MAKE) -C $(D) all;)

clean:
	$(foreach D, $(LIBS), $(MAKE) -C $(D) clean;)
	rm -f *.o

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
