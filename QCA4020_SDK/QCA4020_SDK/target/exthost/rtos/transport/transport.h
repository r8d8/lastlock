/*
 * Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
 * Copyright (c) 2015-2016 Qualcomm Atheros, Inc.
 * All Rights Reserved
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

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

typedef enum {
    HTC_TRANSPORT_SDIO = 0,
    HTC_TRANSPORT_SPI
} HTC_TARGET_TRANSPORT;

/* Types of read/write */
typedef unsigned int io_mode_t; /* combination of IO_FLAG's, below */
#define TRANSPORT_IO_FLAG_HCR_REGISTER 1        /* Access an HCR register */
#define TRANSPORT_IO_FLAG_MBOXFIFO     2        /* Access a mailbox FIFO */
#define TRANSPORT_IO_FLAG_NONINCR      4        /* Non-incrementing bus address (e.g. credit counter) */

/*
 * Type of DSR callback function.
 * Register via spi_hal_register_interrupt.
 * Called from transport layer in (thread context) when an interrupt occurs.
 */
typedef void (*transport_dsr_cb_t) (void *pcontext);

typedef int (*read_data_t) (void *tdev, io_mode_t iomode, unsigned int addr, void *src, int count);
typedef int (*write_data_t) (void *tdev, io_mode_t iomode, unsigned int addr, void *src, int count);
typedef int (*register_interrupt_t) (void *tdev, transport_dsr_cb_t pfunc);
typedef int (*deregister_interrupt_t) (void *tdev);
typedef void (*unmask_interrupt_t) (void *tdev);
typedef void (*mask_interrupt_t) (void *tdev);
typedef int (*enable_func_t) (void *tdev);
typedef int (*disable_func_t) (void *tdev);

typedef struct trans_dev_ops {
    read_data_t read_data;
    write_data_t write_data;
    register_interrupt_t register_interrupt;
    deregister_interrupt_t deregister_interrupt;
    unmask_interrupt_t unmask_interrupt;
    mask_interrupt_t mask_interrupt;
    enable_func_t enable_trans;
    disable_func_t disable_trans;
} trans_dev_ops_t;

typedef int (*hif_trans_device_func_t) (void *dev, qbool_t hotplug);

typedef struct hif_callbacks {
    hif_trans_device_func_t hif_trans_device_inserted;
    hif_trans_device_func_t hif_trans_device_removed;
} hif_callbacks_t;

typedef struct trans_device {
    uint32 id;
    trans_dev_ops_t *ops;
    void *context;
    void *dev;
    hif_callbacks_t hif_callbacks;
    HTC_TARGET_TRANSPORT transport;
} trans_device_t;

/* prototypes */
int trans_reset_target(trans_device_t * tdev);
void trans_set_hifcontext(trans_device_t * tdev, void *hifdevice);
void *trans_get_hifcontext(trans_device_t * tdev);

/* Inlines */
int trans_read_data(trans_device_t * tdev, io_mode_t iomode, unsigned int addr, void *src, int count);
int trans_write_data(trans_device_t * tdev, io_mode_t iomode, unsigned int addr, void *src, int count);
int trans_register_interrupt(trans_device_t * tdev, transport_dsr_cb_t pfunc);
int trans_deregister_interrupt(trans_device_t * tdev);
void trans_unmask_interrupt(trans_device_t * tdev);
void trans_mask_interrupt(trans_device_t * tdev);
int trans_enable_trans(trans_device_t * tdev);
int trans_disable_trans(trans_device_t * tdev);

/* Called once during host initialization */
int trans_init(hif_callbacks_t * callbacks);

/* Called once during host shutdown */
int trans_deinit(trans_device_t * tdev);

#endif
