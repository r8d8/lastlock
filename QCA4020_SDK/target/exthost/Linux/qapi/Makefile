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

ROOT_PATH:=../../..
LINUX_PATH:=..
INCLUDE_DIR:=$(ROOT_PATH)/include
QUARTZ_PATH:=$(ROOT_PATH)/quartz
SERIALIZER_DIR:=$(QUARTZ_PATH)/serializer
OUTPUT_DIR:=output
DAEMON_MODE:=true

CSRCS:=$(wildcard $(SERIALIZER_DIR)/framework/common/*.c) \
                  $(wildcard $(SERIALIZER_DIR)/framework/host/*.c) \
                  $(wildcard $(SERIALIZER_DIR)/framework/host/qapi/*.c) \
                  $(wildcard $(SERIALIZER_DIR)/framework/OSAL/Linux/*.c) \
                  $(wildcard $(SERIALIZER_DIR)/genedit_files/common/qapi*.c) \
                  $(wildcard $(SERIALIZER_DIR)/genedit_files/host/qapi*.c) \
                  $(wildcard $(SERIALIZER_DIR)/manual/common/qapi*.c) \
                  $(wildcard $(SERIALIZER_DIR)/manual/host/qapi*.c)

INCLUDE_DIRS := $(ROOT_PATH)/include \
                $(LINUX_PATH)/daemon/include \
                $(SERIALIZER_DIR)/genedit_files/common/include \
                $(SERIALIZER_DIR)/genedit_files/host/include \
                $(SERIALIZER_DIR)/genedit_files/fileID \
                $(SERIALIZER_DIR)/manual/common/include \
                $(SERIALIZER_DIR)/manual/host/include \
                $(SERIALIZER_DIR)/manual/host/common \
                $(SERIALIZER_DIR)/../../include/qapi \
                $(SERIALIZER_DIR)/../../include \
                $(SERIALIZER_DIR)/framework/common \
                $(SERIALIZER_DIR)/framework/config \
                $(SERIALIZER_DIR)/framework/host \
                $(SERIALIZER_DIR)/framework/OSAL/include


DEFINES := -D ENABLE_P2P_MODE

ifeq ($(DAEMON_MODE),true)
  DEFINES += -D CONFIG_DAEMON_MODE
endif

CFLAGS := -g -pthread -Wall $(DEFINES) -std=gnu99

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
    CC := gcc
    CFLAGS += -m32
  endif
else
  CC := gcc
endif

CFLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))

LDFLAGS = -lpthread -lrt

OBJS:= ${CSRCS:.c=.o}
QAPI_HOST_HEADERS:= $(wildcard $(SERIALIZER_DIR)/genedit_files/host/include/*_host.h)

.PHONY:
all: host_serializer

.PHONY:
makedir:
	@mkdir -p $(OUTPUT_DIR)
	@chmod 777 $(OUTPUT_DIR)

.PHONY:
host_serializer: makedir $(OBJS)
	ar -cvq $(OUTPUT_DIR)/host_serializer.a $(OBJS)
	@cp -f $(QAPI_HOST_HEADERS) $(INCLUDE_DIR)/qapi/.
	@cp -f $(SERIALIZER_DIR)/manual/host/common/*.h $(INCLUDE_DIR)/qapi/.
	@cp -f $(SERIALIZER_DIR)/framework/host/qapi/qapi_qsHost.h $(INCLUDE_DIR)/qapi_qsHost.h

.PHONY:
clean:
	rm -rf $(INCLUDE_DIR)/qapi/qapi_host_common.h
	rm -rf $(INCLUDE_DIR)/qapi/*_host.h
	rm -rf $(INCLUDE_DIR)/qapi_qsHost.h
	rm -rf $(OBJS)
	rm -rf $(OUTPUT_DIR)
