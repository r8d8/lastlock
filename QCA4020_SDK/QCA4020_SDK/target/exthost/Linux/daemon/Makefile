# Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
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

OBJDIR = output/obj
OUTDIR = output
OUTFILE = iotd
ROOT_PATH=../../..
QUARTZ_PATH=$(ROOT_PATH)/quartz
SERIALIZER_DIR=$(QUARTZ_PATH)/serializer
EXTHOST_PATH=$(ROOT_PATH)/exthost

HTC_DIR=../htc
HTC_DBG_DIR=$(HTC_DIR)/dbg
HTC_DBG_SRCS=$(HTC_DBG_DIR)/dbg.c
HTC_DBG_OBJS= $(patsubst $(HTC_DBG_DIR)/%.c,$(OBJDIR)/%.o,$(HTC_DBG_SRCS))

HTC_MBOX_DIR=$(HTC_DIR)/htc_mbox
HTC_MBOX_SRCS= $(HTC_MBOX_DIR)/htc_event_signal.c  \
                $(HTC_MBOX_DIR)/htc_mbox_recv.c	$(HTC_MBOX_DIR)/htc_mbox_utils.c\
                $(HTC_MBOX_DIR)/htc_mbox.c	$(HTC_MBOX_DIR)/htc_mbox_events.c $(HTC_MBOX_DIR)/htc_mbox_send.c\
                $(HTC_MBOX_DIR)/htc_mbox_compl.c  $(HTC_MBOX_DIR)/htc_mbox_intr.c $(HTC_MBOX_DIR)/htc_mbox_task.c


HTC_HIF_DIR=../hif/spi
HTC_HIF_SRCS=$(HTC_HIF_DIR)/hif.c $(HTC_HIF_DIR)/hif_spi_isr.c $(HTC_HIF_DIR)/spi_rw.c
HTC_HIF_OBJS= $(patsubst $(HTC_HIF_DIR)/%.c,$(OBJDIR)/%.o,$(HTC_HIF_SRCS))

HTC_MBOX_OBJS= $(patsubst $(HTC_MBOX_DIR)/%.c,$(OBJDIR)/%.o,$(HTC_MBOX_SRCS))

# Sources to compile
CSRCS := daemon.c \
         ipc/ipcManager.c \
         ipc/diagManager.c \
         queue/queue.c \
         mml/mml.c \
         mml/spi/htc_mbox_event_handlers.c \
         mml/spi/spi_iface_init.c \
         mml/htc/htc.c  \
         bufpool/bufpool.c \
         net/dataManager.c \
         net/dataManager_utils.c \
         hif/hifUart.c \
         cfg/parse_config.c \
         iotd/iotdManager.c \
         iotd/throughputTest.c \
         dbg/iotd_dbg.c \
         util/utils.c
         
CSRCS += unittest/unittest.c

INCLUDES := -I"include" \
            -I"$(SERIALIZER_DIR)/framework/common" \
            -I"$(SERIALIZER_DIR)/framework/OSAL/include" \
            -I"$(SERIALIZER_DIR)/framework/quartz"\
            -I"$(SERIALIZER_DIR)/framework/host"\
            -I"$(ROOT_PATH)/include/qapi"\
            -I"$(EXTHOST_PATH)/Linux" \
            -I"$(EXTHOST_PATH)/Linux/htc/htc_mbox" \
            -I"$(EXTHOST_PATH)/Linux/htc/dbg" \
            -I"mml"

DEFINES := -DCONFIG_DAEMON_MODE

ifeq ($(HTC_DEBUG),true)
DEFINES += -DDEBUG_HTC
endif

LD = ld

COPTS = -c -pthread -g -Wall
LDFLAGS = -lpthread -lrt -g
OBJS := $(CSRCS:%.c=$(OBJDIR)/%.o)

ifdef HOST_CROSS_COMPILE
  ifeq ($(HOST_CROSS_COMPILE),dakota)
    CC := arm-openwrt-linux-muslgnueabi-gcc
    export STAGING_DIR := $(CURDIR)
  endif
  ifeq ($(HOST_CROSS_COMPILE),ipq40xx)
    CC := arm-openwrt-linux-muslgnueabi-gcc
    export STAGING_DIR := $(CURDIR)
  endif
  ifeq ($(HOST_CROSS_COMPILE),ipq807x)
    CC := arm-openwrt-linux-muslgnueabi-gcc
    export STAGING_DIR := $(CURDIR)
  endif
  ifeq ($(HOST_CROSS_COMPILE),ipq807x_64)
    CC := aarch64-openwrt-linux-gcc
    export STAGING_DIR := $(CURDIR)
  endif
  ifeq ($(HOST_CROSS_COMPILE),ar71xx)
    CC := mips-openwrt-linux-uclibc-gcc
    export STAGING_DIR := $(CURDIR)
  endif  
  ifeq ($(HOST_CROSS_COMPILE),x86_32)
    COPTS += -m32
    LDFLAGS += -m32
  endif
endif

CFLAGS := $(COPTS) $(DEFINES) $(INCLUDES)

all: $(OBJS) $(HTC_MBOX_OBJS) $(HTC_DBG_OBJS) $(HTC_HIF_OBJS) $(HTC_OBJS)
	$(CC) -o $(OUTDIR)/$(OUTFILE) $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling $< $@
	$(CC) $(CFLAGS) $< -o $(@)

$(OBJDIR)/%.o:	$(HTC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo Compiling $< $@
	$(CC) $(CFLAGS) -DUSER_SPACE -I$(HTC_DBG_DIR) -I$(HTC_HIF_DIR) -I$(HTC_DIR) $< -o $(@)

$(OBJDIR)/%.o:	$(HTC_MBOX_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo Compiling $< $@
	$(CC) $(CFLAGS) -DUSER_SPACE -I$(HTC_DBG_DIR) -I$(HTC_HIF_DIR) -I$(HTC_DIR) -I$(HTC_MBOX_DIR) $< -o $(@)

$(OBJDIR)/%.o:	$(HTC_DBG_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo Compiling $< $@
	$(CC) $(CFLAGS) -DUSER_SPACE -I$(HTC_DBG_DIR) -I$(HTC_HIF_DIR) -I$(HTC_DIR) $< -o $(@)

$(OBJDIR)/%.o:	$(HTC_HIF_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo Compiling $< $@
	$(CC) $(CFLAGS) -DUSER_SPACE -I$(HTC_DBG_DIR) -I$(HTC_HIF_DIR) -I$(HTC_DIR) -I$(HTC_MBOX_DIR) $< -o $(@)

clean:
	rm -rf output/
	
