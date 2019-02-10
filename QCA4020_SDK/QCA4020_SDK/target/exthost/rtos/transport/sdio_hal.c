/*
 * Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
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

 /*
  * SDIO bus Master side transport
  */

#include <stdio.h>
#include "stdlib.h"
#include "stdint.h"
#include "qurt_mutex.h"
#include "qurt_signal.h"
#include "qapi/qurt_thread.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_tlmm.h"
#include "qapi/qapi_slp.h"
#include "qapi/qapi_master_sdcc.h"
#include <qurt_timer.h>
#include "transport.h"
#include "common_defs.h"
#include "sdio_hal.h"

// #define DEBUG

extern void PAL_CONSOLE_PRINTF(const char *format, ...);

#if defined(DEBUG)
#define sdiohaldebug PAL_CONSOLE_PRINTF
#else
#define sdiohaldebug(args...)
#endif

extern void sdio_hal_failure(void);     /* debug */
#define FAIL_RETURN() \
do { \
        sdio_hal_failure(); \
        return -1; \
} while(0)

/* Prototypes */
static int sdio_hal_read_data(void *tdev, io_mode_t iomode, unsigned int addr, void *src, int count);
static int sdio_hal_write_data(void *tdev, io_mode_t iomode, unsigned int addr, void *src, int count);
static int sdio_hal_register_interrupt(void *tdev, transport_dsr_cb_t pfunc);
static int sdio_hal_deregister_interrupt(void *tdev);
void sdio_hal_unmask_interrupt(void *tdev);
void sdio_hal_mask_interrupt(void *tdev);
static int sdio_hal_enable_func(void *tdev);
static int sdio_hal_disable_func(void *tdev);

// #define SDIO_DUMP_READ
// #define SDIO_DUMP_WRITE

static trans_dev_ops_t sdio_ops = {
    .read_data = sdio_hal_read_data,
    .write_data = sdio_hal_write_data,
    .register_interrupt = sdio_hal_register_interrupt,
    .deregister_interrupt = sdio_hal_deregister_interrupt,
    .unmask_interrupt = sdio_hal_unmask_interrupt,
    .mask_interrupt = sdio_hal_mask_interrupt,
    .enable_trans = sdio_hal_enable_func,
    .disable_trans = sdio_hal_disable_func,
};

/* A few convenience variables for debug and testing */
trans_device_t *sdio_hal_tdev_dbg;
sdio_device_t *sdio_hal_dev_dbg;

#if defined(DEBUG)
void sdio_dump_bytes(uint8 * buf, uint32 count)
{
    int i;

    for (i = 0; i < count; i++) {
        sdiohaldebug(" %02x ", buf[i]);
    }
    sdiohaldebug("\r\n");
}
#endif

int cmd52_func0_read_byte(void *sdio_Handle, uint32 reg_Addr, uint8 * pmybyte)
{
    qapi_Status_t status;
    uint32 dev_Fn = 0;

    status = qapi_SDCCM_Send_Receive_Byte(sdio_Handle, QAPI_SDCC_DIR_READ_E, dev_Fn,
                                        reg_Addr, QAPI_SDCC_DIR_READ_E, pmybyte);
    if (status != QAPI_OK) {
        FAIL_RETURN();
    }

    return 0;
}

int cmd52_func0_write_byte(void *sdio_Handle, uint32 reg_Addr, uint8 mybyte)
{
    qapi_Status_t status;
    uint32 dev_Fn = 0;

    status = qapi_SDCCM_Send_Receive_Byte(sdio_Handle, QAPI_SDCC_DIR_WRITE_E, dev_Fn,
                                         reg_Addr, mybyte, NULL);
    if (status != QAPI_OK) {
        FAIL_RETURN();
    }

    return 0;
}

int sdio_hal_read_data(void *tdev, io_mode_t iomode, unsigned int addr, void *buf, int count)
{
    uint32 flags;
    uint32 dev_Fn = 1;
    qapi_Status_t status = QAPI_OK;
    sdio_device_t *dev;
    trans_device_t *trans_dev = tdev;
    int addr_incr;

    if (!tdev) {
        FAIL_RETURN();
    }

    dev = (sdio_device_t *) trans_dev->dev;

    flags = QAPI_SDCC_DIR_READ_E;
    if ((iomode & TRANSPORT_IO_FLAG_NONINCR)) {
        addr_incr = 0;
    } else {
        flags |= QAPI_SDCC_OP_INC_ADDR_E;
        addr_incr = 1;
    }

    if ((count % SDIO_BLOCK_SIZE) == 0) {
        flags |= QAPI_SDCC_BLOCK_MODE_E;
    }

    /*
     * SDIO can use Receive_Data_Ext to read data from the Target unless
     * we are reading from an area of the Target's address space that
     * may have holes. This should never occur when reading from mailbox
     * FIFOs but it may occur while reading from registers. (But it cannot
     * occur if the address is non-incrementing.)
     */
    if ((iomode & TRANSPORT_IO_FLAG_HCR_REGISTER) && addr_incr) {
        int i;
        uint8 *bytebuf = buf;
        unsigned int tmp_addr;

        /*
         * This ASSERT is intended to catch unanticipated usage of this module.
         * Reading many bytes one at a time should "work" but it's inefficient
         * so we  should avoid this.
         */
        ASSERT(count < 32);

        /* See sdcc_hc_fifo_mode_rw, too... */
        for (i=0, tmp_addr = addr; i<count; i++, tmp_addr += addr_incr) {
            status = qapi_SDCCM_Send_Receive_Byte(dev->handle, flags, dev_Fn,
                                                    tmp_addr, QAPI_SDCC_DIR_READ_E, &bytebuf[i]);
            if (status != QAPI_OK) {
                sdiohaldebug("%s: Failed (%d) to recv byte#%d from 0x%x\r\n",
                                 __FUNCTION__, status, i, tmp_addr);
                FAIL_RETURN();
            }
        }
    } else {
        status = qapi_SDCCM_Receive_Data_Ext(dev->handle, flags, dev_Fn, addr, count, buf);
        if (status != QAPI_OK) {
            sdiohaldebug("%s: Failed (%d) to recv data\r\n", __FUNCTION__, status);
            FAIL_RETURN();
        }
    }

#if defined(SDIO_DUMP_READ)
    sdiohaldebug("Read %d bytes from addr 0x%x:\r\n", count addr);
    sdio_dump_bytes(buf, count);
#endif

    return 0;
}

int sdio_hal_write_data(void *tdev, io_mode_t iomode, unsigned int addr, void *src, int count)
{
    uint32 flags;
    uint32 dev_Fn = 1;
    qapi_Status_t status = QAPI_OK;
    sdio_device_t *dev;
    trans_device_t *trans_dev = tdev;
    int addr_incr;

    if (!tdev) {
        FAIL_RETURN();
    }

    dev = (sdio_device_t *) trans_dev->dev;

    flags = QAPI_SDCC_DIR_WRITE_E;
    if ((iomode & TRANSPORT_IO_FLAG_NONINCR)) {
        addr_incr = 0;
    } else {
        flags |= QAPI_SDCC_OP_INC_ADDR_E;
        addr_incr = 1;
    }

    if ((count % SDIO_BLOCK_SIZE) == 0) {
        flags |= QAPI_SDCC_BLOCK_MODE_E;
    }

    if (iomode & TRANSPORT_IO_FLAG_HCR_REGISTER) {
        int i;
        uint8 *bytebuf = src;
        unsigned int tmp_addr;

        for (i=0, tmp_addr = addr; i<count; i++, tmp_addr += addr_incr) {
            status = qapi_SDCCM_Send_Receive_Byte(dev->handle, flags, dev_Fn,
                                                    tmp_addr, bytebuf[i], NULL);
            if (status != QAPI_OK) {
                sdiohaldebug("%s: Failed (%d) to send byte#%d to 0x%x\r\n",
                                 __FUNCTION__, status, i, tmp_addr);
                FAIL_RETURN();
            }
        }
    } else {
        status = qapi_SDCCM_Send_Data_Ext(dev->handle, flags, dev_Fn, addr, count, src);
        if (status != QAPI_OK) {
            sdiohaldebug("%s: Failed (%d) to send data\r\n", __FUNCTION__, status);
            FAIL_RETURN();
        }
    }


#if defined(SDIO_DUMP_WRITE)
    sdiohaldebug("Sent %d bytes to addr 0x%x:\r\n", count, addr);
    sdio_dump_bytes(src, count);
#endif

    return 0;
}

void sdio_hal_unmask_interrupt(void *tdev)
{
    trans_device_t *trans_dev = tdev;
    sdio_device_t *dev = (sdio_device_t *) trans_dev->dev;

    (void)qapi_SDCCM_EnableDisableIrq(dev->handle, TRUE);
}

void sdio_hal_mask_interrupt(void *tdev)
{
    trans_device_t *trans_dev = tdev;
    sdio_device_t *dev = (sdio_device_t *) trans_dev->dev;

    (void)qapi_SDCCM_EnableDisableIrq(dev->handle, FALSE);
}

int sdio_hal_register_interrupt(void *tdev, transport_dsr_cb_t pfunc)
{
    int rv;
    qapi_Status_t status;
    uint8 mybyte;
    sdio_device_t *dev;
    trans_device_t *trans_dev = tdev;

    if (!tdev) {
        FAIL_RETURN();
    }

    dev = (sdio_device_t *) trans_dev->dev;

    /*
     * We don't want to auto-enable interrupts from the Target
     * yet so disable them at the Host controller.
     */
    sdio_hal_mask_interrupt(tdev);

    /* Now it's safe to enable interrupts at the Target-side */
    rv = cmd52_func0_read_byte(dev->handle, SDIO_CCCR_IENx, &mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to read IENx\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }

    mybyte |= SDIO_CCCR_IENx_MASTER | SDIO_CCCR_IENx_IEN1;
    rv = cmd52_func0_write_byte(dev->handle, SDIO_CCCR_IENx, mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to set IENx bits\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }

    /* And finally register a handler with the underlying Host Controller driver */
    status = qapi_SDCCM_Intr_Register(dev->handle, pfunc, tdev);
    if (status != QAPI_OK) {
        sdiohaldebug("%s: Failed (%d) to register interrupt handler\r\n", __FUNCTION__, status);
        FAIL_RETURN();
    }

    sdiohaldebug("%s: Interrupt registered for handle=0x%x!\r\n", __FUNCTION__, dev->handle);

    return 0;
}

int sdio_hal_deregister_interrupt(void *tdev)
{
    qapi_Status_t status;
    int rv;
    uint8 mybyte;
    sdio_device_t *dev;
    trans_device_t *trans_dev = tdev;
    unsigned long intrstate;

    if (!tdev) {
        FAIL_RETURN();
    }
    dev = (sdio_device_t *) trans_dev->dev;

    rv = cmd52_func0_read_byte(dev->handle, SDIO_CCCR_IENx, &mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to read interrupt enable bits\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }

    mybyte &= ~(SDIO_CCCR_IENx_MASTER | SDIO_CCCR_IENx_IEN1);
    rv = cmd52_func0_write_byte(dev->handle, SDIO_CCCR_IENx, mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to clear interrupt enable bits\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }

    INTR_BLOCK(intrstate);
    status = qapi_SDCCM_EnableDisableIrq(dev->handle, FALSE);
    if (status != QAPI_OK) {
        sdiohaldebug("%s: Failed( %d) to disable interrupts\r\n", __FUNCTION__, status);
        INTR_UNBLOCK(intrstate);
        FAIL_RETURN();
    }

    status = qapi_SDCCM_Intr_Deregister(dev->handle);
    if (status != QAPI_OK) {
        sdiohaldebug("%s: Failed( %d) to deregister interrupt handler\r\n", __FUNCTION__, status);
        INTR_UNBLOCK(intrstate);
        FAIL_RETURN();
    }
    INTR_UNBLOCK(intrstate);

    return 0;
}

int sdio_hal_enable_func(void *tdev)
{
    int rv;
    qapi_Status_t status;
    uint8 mybyte;
    sdio_device_t *dev;
    trans_device_t *trans_dev = tdev;
    int desired_block_size;

    if (!tdev) {
        FAIL_RETURN();
    }

    dev = (sdio_device_t *) trans_dev->dev;

    /* Async int delay */
    rv = cmd52_func0_read_byte(dev->handle, CCCR_SDIO_ASYNC_INT_DELAY_ADDRESS, &mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to read async int delay\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }

    mybyte = (mybyte & ~CCCR_SDIO_ASYNC_INT_DELAY_MASK) |
        ((dev->asyncintdelay << CCCR_SDIO_ASYNC_INT_DELAY_LSB) & CCCR_SDIO_ASYNC_INT_DELAY_MASK);
    rv = cmd52_func0_write_byte(dev->handle, CCCR_SDIO_ASYNC_INT_DELAY_ADDRESS, mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to set async delay\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }

    sdiohaldebug("%s: Enabling Func 1\r\n", __FUNCTION__);
    rv = cmd52_func0_write_byte(dev->handle, SDIO_CCCR_IOEx, SDIO_CCCR_IOEx_IOE1);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to enable Func 1\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }

    /* Write 16-bit block size with two byte-sized writes. */
    desired_block_size = dev->sdio_Config.block_Size;
    mybyte = desired_block_size & 0xff;
    rv = cmd52_func0_write_byte(dev->handle, SDIO_FBR_BLOCK_SIZE, mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to set block size byte 0\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }
    mybyte = (desired_block_size >> 8) & 0xff;
    rv = cmd52_func0_write_byte(dev->handle, SDIO_FBR_BLOCK_SIZE+1, mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to set block size byte 1\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }

    /* Enable interrupts */
    status = qapi_SDCCM_EnableDisableIrq(dev->handle, TRUE);
    if (status != QAPI_OK) {
        sdiohaldebug("%s: Failed (%d) to enable interrupts\r\n", __FUNCTION__, status);
        FAIL_RETURN();
    }

    return 0;
}

int sdio_hal_disable_func(void *tdev)
{
    qapi_Status_t status;
    int rv;
    sdio_device_t *dev;
    trans_device_t *trans_dev = tdev;

    if (!tdev) {
        FAIL_RETURN();
    }
    dev = (sdio_device_t *) trans_dev->dev;

    sdiohaldebug("%s: Enter\r\n", __FUNCTION__);

    rv = cmd52_func0_write_byte(dev->handle, SDIO_CCCR_IOEx, 0); /* disable */
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to disable Func 1\r\n", __FUNCTION__, rv);
        FAIL_RETURN();
    }

    /* Disable the card interrupt */
    status = qapi_SDCCM_EnableDisableIrq(dev->handle, FALSE);
    if (status != QAPI_OK) {
        sdiohaldebug("%s: Failed (%d) to disable interrupts\r\n", __FUNCTION__, status);
        FAIL_RETURN();
    }

    return 0;
}

int sdio_hal_init(trans_device_t * tdev)
{
    int rv;
    qapi_Status_t status;
    uint8 mybyte;
    sdio_device_t *dev;

    sdiohaldebug("%s:Enter\r\n", __FUNCTION__);

    dev = (sdio_device_t *) malloc(sizeof(sdio_device_t));
    if (!dev) {
        sdiohaldebug("%s: malloc failed\r\n", __FUNCTION__);
        FAIL_RETURN();
    }

    sdio_hal_tdev_dbg = tdev;
    sdio_hal_dev_dbg = dev;

    memset(dev, 0, sizeof(*dev));
    dev->id = tdev->id;
    tdev->dev = (void *)dev;

    /* TBD: Populate device configuration from DevCfg */
    dev->sdio_Config.adma_Descr_Items = SDIO_ADMA_DESCR_ITEMS;  /* adma descriptor items */
    dev->sdio_Config.SDCC_Bus_Width = SDIO_BUS_WIDTH;   /* sdio bus width 1 bit or 4 bits */
    dev->sdio_Config.freq = SDIO_FREQ_DEFAULT;  /* bus frequency */
    dev->sdio_Config.block_Size = SDIO_BLOCK_SIZE;      /* block size */

    dev->asyncintdelay = 2;

    status = qapi_SDCCM_Init(&dev->sdio_Config, &dev->handle);
    if (status != QAPI_OK) {
        sdiohaldebug("%s: Failed (%d) to init SDIO\r\n", __FUNCTION__, status);
        goto error;
    }

    status = qapi_SDCCM_Open(dev->handle);
    if (status != QAPI_OK) {
        sdiohaldebug("%s: Failed (%d) to open SDIO\r\n", __FUNCTION__, status);
        qapi_SDCCM_Deinit(dev->handle);
        goto error;

    }

    rv = cmd52_func0_read_byte(dev->handle, SDIO_CCCR_REVISION, &mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to read revision\r\n", __FUNCTION__, rv);
        qapi_SDCCM_Close(dev->handle);
        qapi_SDCCM_Deinit(dev->handle);
        goto error;
    }
    sdiohaldebug("%s: SDIO revision=%d CCCR revision=%d\r\n", __FUNCTION__,
                        ((mybyte >> 4) & 0x0F),
                        (mybyte & 0x0F));

    rv = cmd52_func0_read_byte(dev->handle, SDIO_CCCR_DRIVE_STRENGTH, &mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to read drive strength\r\n", __FUNCTION__, rv);
        qapi_SDCCM_Close(dev->handle);
        qapi_SDCCM_Deinit(dev->handle);
        goto error;
    }

    mybyte = (mybyte & (~(SDIO_DRIVE_DTSx_MASK << SDIO_DRIVE_DTSx_SHIFT)))
             | SDIO_DTSx_SET_TYPE_D;
    rv = cmd52_func0_write_byte(dev->handle, SDIO_CCCR_DRIVE_STRENGTH, mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to write DTSx\r\n", __FUNCTION__, rv);
        qapi_SDCCM_Close(dev->handle);
        qapi_SDCCM_Deinit(dev->handle);
        goto error;

    }

    rv = cmd52_func0_read_byte(dev->handle, CCCR_SDIO_DRIVE_STRENGTH_ENABLE_ADDR, &mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to read Drive Strength Enable\r\n", __FUNCTION__, rv);
        qapi_SDCCM_Close(dev->handle);
        qapi_SDCCM_Deinit(dev->handle);
        goto error;

    }
    mybyte = (mybyte & (~CCCR_SDIO_DRIVE_STRENGTH_ENABLE_MASK))
             | CCCR_SDIO_DRIVE_STRENGTH_ENABLE_A
             | CCCR_SDIO_DRIVE_STRENGTH_ENABLE_C
             | CCCR_SDIO_DRIVE_STRENGTH_ENABLE_D;
    rv = cmd52_func0_write_byte(dev->handle, CCCR_SDIO_DRIVE_STRENGTH_ENABLE_ADDR, mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to set drive strength enable\r\n", __FUNCTION__, rv);
        qapi_SDCCM_Close(dev->handle);
        qapi_SDCCM_Deinit(dev->handle);
        goto error;
    }

    /* MMC bus width, set it to sdio_Config.SDCC_Bus_Width */
    mybyte = SDIO_BUS_CD_DISABLE | SDIO_BUS_WIDTH_4BIT;
    rv = cmd52_func0_write_byte(dev->handle, SDIO_CCCR_IF, mybyte);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to set bus width\r\n", __FUNCTION__, rv);
        qapi_SDCCM_Close(dev->handle);
        qapi_SDCCM_Deinit(dev->handle);
        goto error;
    }

    tdev->ops = &sdio_ops;

    /*
     * Platform SDCC driver does not support hotplug.
     * Assume the device is always present.
     */
    if ((tdev->hif_callbacks.hif_trans_device_inserted != NULL) && (status == QAPI_OK)) {
        tdev->hif_callbacks.hif_trans_device_inserted(tdev, FALSE);
    }

    return 0;

 error:
    free(dev);
    FAIL_RETURN();
}

int sdio_hal_deinit(trans_device_t * tdev)
{
    qapi_Status_t status;
    int rv;
    sdio_device_t *dev;

    if (!tdev) {
        FAIL_RETURN();
    }

    dev = (sdio_device_t *) tdev->dev;

    /*
     * On some platform, this may be called from a hot plug device remove handler.
     * On this platform the device disconnect event is sent only during de-initialization.
     */
    if (tdev->hif_callbacks.hif_trans_device_removed) {
        tdev->hif_callbacks.hif_trans_device_removed(tdev, FALSE);
    }

    /* Reset SDIO Card */
    rv = cmd52_func0_write_byte(dev->handle, SDIO_CCCR_ABORT, SDIO_IO_RESET);
    if (rv) {
        sdiohaldebug("%s: Failed (%d) to reset SDIO Card\r\n", __FUNCTION__, rv);
    }

    status = qapi_SDCCM_Close(dev->handle);
    if (status != QAPI_OK) {
        FAIL_RETURN();
    }

    qapi_SDCCM_Deinit(dev->handle);

    free(dev);
    tdev->dev = NULL;
    tdev->ops = NULL;

    return 0;
}

/*
 * This hack allows high-level code to play with
 * SDIO clock frequency of a single SDIO device.
 *
 * This is intended for testing/demonstration purposes.
 */
void sdio_hal_config_freq(uint freq)
{
    extern qapi_Status_t qapi_SDCCM_clk_set(qapi_SDCC_Handle sdcc_Handle, unsigned int freq);

    (void)qapi_SDCCM_clk_set(sdio_hal_dev_dbg->handle, freq);
}


/* For debug, a convenient place to set a breakpoint */
__attribute__ ((noinline))
void sdio_hal_failure(void)
{
    static unsigned int sdio_hal_failure_count;
    sdio_hal_failure_count++;
}
