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

 /******************************************************************************
 * spi_hal.c
 *
 * SPI Master side transport layer implementation
 *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qapi/qurt_error.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_thread.h"
#include "qapi/qurt_mutex.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_delay.h"
#include "qapi/qapi_dsr.h"
#include "qapi/qapi_fatal_err.h"
#include "qapi/qapi_spi_master.h"
#include "qapi/qapi_tlmm.h"
#include "common_defs.h"
#include "transport.h"
#include "spi_hal.h"
#include "qurt_timer.h"
#include "qurt_types.h"

// #define DEBUG
// #define DEBUG_VERBOSE

/* Enable the RX_LOOKAHEAD WORKAROUND */
#define CONFIG_SPI_RX_LOOKAHEAD_WAR

extern void PAL_CONSOLE_PRINTF(const char *format, ...);
#define printf PAL_CONSOLE_PRINTF

#if defined(DEBUG)
#define spihaldebug PAL_CONSOLE_PRINTF
#else
#define spihaldebug(args...)
#endif

extern void spi_hal_failure(void);      /* debug only */
#define FAIL_RETURN() \
do { \
        spi_hal_failure(); \
        return -1; \
} while(0)

/* Statistics for debug only */
unsigned int read_retry_stats[SPI_SLV_TRANS_RETRY_COUNT];
unsigned int write_retry_stats[SPI_SLV_TRANS_RETRY_COUNT];

/* A few convenience variables for debug and testing */
trans_device_t *spi_hal_tdev_dbg;
spi_device_t *spi_hal_dev_dbg;
qapi_GPIO_ID_t spi_hal_gpioid_dbg;

#define _COMPILE_TIME_ASSERT(assertion_name, predicate) \
    typedef char assertion_name[(predicate) ? 1 : -1];

_COMPILE_TIME_ASSERT(SPIM_INSTANCE_OK,
                     ((QAPI_SPIM_INSTANCE_1_E == 1) &&
                      (QAPI_SPIM_INSTANCE_2_E == 2) && (QAPI_SPIM_INSTANCE_3_E == 3) && (QAPI_SPIM_INSTANCE_4_E == 4)));

#define IS_VALID_DEV_ID(id) ASSERT(((id) >= 1) && ((id <= 4)))

int spi_hal_read_data(void *tdev, io_mode_t iomode, unsigned int addr, void *src, int count);
int spi_hal_write_data(void *tdev, io_mode_t iomode, unsigned int addr, void *src, int count);
int spi_hal_register_interrupt(void *tdev, transport_dsr_cb_t pfunc);
int spi_hal_deregister_interrupt(void *tdev);
void spi_hal_unmask_interrupt(void *tdev);
void spi_hal_mask_interrupt(void *tdev);
int spi_hal_enable_trans(void *tdev);
int spi_hal_disable_trans(void *tdev);
void spi_hal_gpio_isr(qapi_GPIOINT_Callback_Data_t data);
void spi_hal_config_freq(uint freq);

/* Wait for a SPIM transaction to complete. */
void spi_wait_for_transaction(spi_device_t * dev)
{
    uint32 result = 0;

    result = qurt_signal_wait(&dev->spi_signal, SPI_SIGNAL_DONE,
                              QURT_SIGNAL_ATTR_WAIT_ALL | QURT_SIGNAL_ATTR_CLEAR_MASK);

    ASSERT(result == 1);
}

/*
 * Called on completion of a qapi_SPIM_Full_Duplex request.
 * This callback simply signals that the transaction has completed.
 */
void spi_io_complete_cb(uint32_t i_status, void *i_ctxt)
{
    spi_device_t *dev = (spi_device_t *) i_ctxt;

    qurt_signal_set(&dev->spi_signal, SPI_SIGNAL_DONE);
}

void spi_config_init(spi_device_t * dev)
{
    qapi_SPIM_Config_WAR_t *cfg = (qapi_SPIM_Config_WAR_t *) & dev->spi_trans_config;

    cfg->SPIM_Clk_Polarity = QAPI_SPIM_CLK_IDLE_HIGH_E;
    cfg->SPIM_Shift_Mode = QAPI_SPIM_INPUT_FIRST_MODE_E;
    cfg->SPIM_CS_Polarity = QAPI_SPIM_CS_ACTIVE_LOW_E;
    cfg->SPIM_CS_Mode = QAPI_SPIM_CS_DEASSERT_E;
    cfg->SPIM_Clk_Always_On = QAPI_SPIM_CLK_NORMAL_E;
    cfg->SPIM_Bits_Per_Word = 0;        /* Set for each transaction */
    cfg->SPIM_Slave_Index = 0;
    cfg->min_Slave_Freq_Hz = 0;
    cfg->max_Slave_Freq_Hz = SPI_SLV_CLOCK_FREQUENCY_DEFAULT;   /* May be overridden */
    cfg->deassertion_Time_Ns = 0;
    cfg->loopback_Mode = 0;
    cfg->hs_Mode = 1;
}

#define SPI_CONFIG_WIDTH_SET(dev, width) \
    do {((qapi_SPIM_Config_WAR_t *)(&(dev)->spi_trans_config))->SPIM_Bits_Per_Word = 8*(width);} while(0)

/* Set SPI Clock frequency. See spi_hal.h for frequencies supported by QCA402x */
#define SPI_CONFIG_FREQ_SET(dev, freq) \
    do {((qapi_SPIM_Config_WAR_t *)(&(dev)->spi_trans_config))->max_Slave_Freq_Hz = (freq);} while(0)

/*
 * Read the value of a single SPI_SLV_REG.
 *
 * data_width is typically 2 (16-bits). The only exception is when
 * reading a single byte from SPI_SLV_REG_HOST_CTRL_RD_PORT.
 *
 * Returns 0 on success; non-zero on failure
 */
int spi_hal_reg_read(spi_device_t * dev, uint16 regaddr, uint16 * pRegData, spi_trans_bit_width_t data_width)
{
    uint32 result;
    uint16 spi_command;

    ASSERT(pRegData != NULL);

    /* Command phase (read from regaddr) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_SHORT);
    spi_command = (SPI_READ_16BIT_MODE)
        | (SPI_INTERNAL_16BIT_MODE)
        | (regaddr & (SPI_REG_ADDRESS_MASK));
    dev->tx_desc.buf_len = 2;
    dev->tx_desc.buf_phys_addr = &spi_command;
    result = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, &dev->tx_desc, NULL, spi_io_complete_cb, dev);
    if (result != 0) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

    /* Data phase (read into pRegData) */
    SPI_CONFIG_WIDTH_SET(dev, data_width);
    /* Setup read data buffer for register read only (hence tx_desc = NULL) */
    dev->rx_desc.buf_len = data_width;
    dev->rx_desc.buf_phys_addr = pRegData;
    result = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, NULL, &dev->rx_desc, spi_io_complete_cb, dev);
    if (result != 0) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

#if defined(DEBUG_VERBOSE)
    spihaldebug("%s: read@0x%0x yields value=0x%04x\r\n", __FUNCTION__, regaddr, *pRegData);
#endif

    return 0;
}

/*
 * Write a value into a single SPI_SLV_REG.
 *
 * data_width is typically 2 (16-bits). The only exception is when
 * writing a single byte to SPI_SLV_REG_HOST_CTRL_WR_PORT.
 *
 * Returns 0 on success; non-zero on failure
 */
int spi_hal_reg_write(spi_device_t * dev, uint16 regaddr, uint16 RegData, spi_trans_bit_width_t data_width)
{
    uint32 result = 0;
    uint16 spi_command = 0;
    uint8_t loc_buf[2];

    /* Command phase (write to regaddr) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_SHORT);
    spi_command = ((SPI_WRITE_16BIT_MODE) | (SPI_INTERNAL_16BIT_MODE) | (regaddr & SPI_REG_ADDRESS_MASK));
    dev->tx_desc.buf_len = 2;
    dev->tx_desc.buf_phys_addr = &spi_command;
    result = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, &dev->tx_desc, NULL, spi_io_complete_cb, dev);
    if (result != 0) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

    /* Data phase (write from loc_buf) */
    SPI_CONFIG_WIDTH_SET(dev, data_width);
    *((uint16 *) loc_buf) = RegData;    /* copy 2 bytes of data */
    dev->tx_desc.buf_len = data_width;
    dev->tx_desc.buf_phys_addr = loc_buf;
    result = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, &dev->tx_desc, NULL, spi_io_complete_cb, dev);
    if (result != 0) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

#if defined(DEBUG_VERBOSE)
    spihaldebug("%s: wrote@0x%0x value=0x%04x\r\n", __FUNCTION__, regaddr, RegData);
#endif

    return 0;
}

int spi_hal_default_spi_slave_config(spi_device_t * dev, uint16 spi_config_val)
{
    return spi_hal_reg_write(dev, SPI_SLV_REG_SPI_CONFIG, spi_config_val, SPI_TRANS_SHORT);
}

/*
 * Read 1 or more bytes from sequential address in HCR space.
 *
 * Most reads use incrementing addresses  but reads from
 * non-incrementing addresses are also supported (useful
 * for reading from COUNTER registers).
 */
int spi_hal_hcr_read(spi_device_t * dev, io_mode_t iomode, uint16 regaddr, uint8 * pRegData, uint32 count)
{
    int rv;
    uint16_t done_status;
    uint16 cmd;
    uint32 retry_count;
    uint32 result;

    ASSERT(count <= SPI_HCR_READSZ_MAX);

    /* Write count to HOST_CTRL_BYTE_SIZE */
    rv = spi_hal_reg_write(dev, SPI_SLV_REG_HOST_CTRL_BYTE_SIZE,
                           count | ((iomode & TRANSPORT_IO_FLAG_NONINCR) ? SPI_SLV_REG_HOST_CTRL_NOADDRINC : 0),
                           SPI_TRANS_SHORT);
    if (rv) {
        FAIL_RETURN();
    }

    /* Write command to 'read from regaddr' to HOST_CTRL_CONFIG */
    cmd = (HOST_CTRL_REG_DIR_RD | (regaddr & HOST_CTRL_REG_ADDRESS_MSK));
    cmd |= HOST_CTRL_REG_ENABLE;
    rv = spi_hal_reg_write(dev, SPI_SLV_REG_HOST_CTRL_CONFIG, cmd, SPI_TRANS_SHORT);

    /* Wait for read command to finish */
    done_status = 0;
    for (retry_count = SPI_SLV_TRANS_RETRY_COUNT; retry_count > 0; retry_count--) {
        rv = spi_hal_reg_read(dev, SPI_SLV_REG_SPI_STATUS, &done_status, SPI_TRANS_SHORT);
        if (rv) {
            FAIL_RETURN();
        }
        if (done_status & SPI_SLV_REG_SPI_STATUS_BIT_HOST_ACCESS_DONE_MSK) {
            break;
        }
        qapi_Task_Delay(SPI_SLV_IO_DELAY);
    }
    if (retry_count == 0) {
        spihaldebug("%s: Failed (%d) to read (@0x%x). Last done_status=0x%x\r\n",
                    __FUNCTION__, rv, regaddr, done_status);
        FAIL_RETURN();
    }
    read_retry_stats[SPI_SLV_TRANS_RETRY_COUNT - retry_count]++;

    /* Command phase (read from HOST_CTRL_RD_PORT) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_SHORT);
    cmd = (SPI_READ_16BIT_MODE)
        | (SPI_INTERNAL_16BIT_MODE)
        | (SPI_SLV_REG_HOST_CTRL_RD_PORT);
    dev->tx_desc.buf_len = 2;
    dev->tx_desc.buf_phys_addr = &cmd;
    result = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, &dev->tx_desc, NULL, spi_io_complete_cb, dev);
    if (result != 0) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

    /* Data phase (read into pRegData) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_BYTE);
    dev->rx_desc.buf_len = count;
    dev->rx_desc.buf_phys_addr = pRegData;
    result = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, NULL, &dev->rx_desc, spi_io_complete_cb, dev);
    if (result != 0) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

#if defined(CONFIG_SPI_RX_LOOKAHEAD_WAR)
#define HOST_INT_STATUS_ADDRESS                  0x00000400
#define RX_LOOKAHEAD_VALID_ADDRESS               0x00000405
#define RX_LOOKAHEAD0_ADDRESS                    0x00000408
#define INT_STATUS_ENABLE_ADDRESS                0x00000418
    /*
     * WORKAROUND specifically for LOOKAHEAD registers within an
     * HTC register refresh over SPI. This issue is not yet root caused.
     *
     * Symptoms: The RX_LOOKAHEAD_VALID register sometimes reads as 0
     * even when SPI_SLV_REG_RDBUF_BYTE_AVA >=4. Also, the RX_LOOKAHEADn
     * registers always contain garbage. In particular, when using only
     * endpoint0, RX_LOOKAHEAD0 does NOT match SPI_SLV_REG_RDBUF_LOOKAHEAD1/2.
     *
     * The workaround here is activated by an HTC Register Refresh -- that
     * is, a particular attempt to read status registers that include the
     * LOOKAHEAD registers. Such a read is issued in the normal way, but
     * selected values in the buffer to be returned are synthesized, based
     * on values of SPI_SLV registers, and used to override the values read.
     *
     * NB: Bytes of SPI_SLV_REG_RDBUF_LOOKAHEAD values 16-bit values
     * with the lowered number byte in the HIGH 8 bits; we swap.
     */
    if ((regaddr == HOST_INT_STATUS_ADDRESS) && (regaddr + count >= INT_STATUS_ENABLE_ADDRESS)) {
        uint8 *lavalidp = pRegData + RX_LOOKAHEAD_VALID_ADDRESS - regaddr;
        uint8 *la0buf = pRegData + RX_LOOKAHEAD0_ADDRESS - regaddr;
        uint16 la_value;
        uint16 bytes_avail;

        rv = spi_hal_reg_read(dev, SPI_SLV_REG_RDBUF_BYTE_AVA, &bytes_avail, SPI_TRANS_SHORT);
        if (bytes_avail >= 4) {
            *lavalidp = 1;

            rv = spi_hal_reg_read(dev, SPI_SLV_REG_RDBUF_LOOKAHEAD1, (uint16 *) & la_value, SPI_TRANS_SHORT);
            if (rv) {
                FAIL_RETURN();
            }

            la0buf[0] = (la_value >> 8) & 0xff;
            la0buf[1] = (la_value >> 0) & 0xff;

            rv = spi_hal_reg_read(dev, SPI_SLV_REG_RDBUF_LOOKAHEAD2, (uint16 *) & la_value, SPI_TRANS_SHORT);
            if (rv) {
                FAIL_RETURN();
            }
            la0buf[2] = (la_value >> 8) & 0xff;
            la0buf[3] = (la_value >> 0) & 0xff;
        } else {
            *lavalidp = 0;
            /* When Lookahead Valid == 0, Lookahead values don't matter */
        }
    }
#endif

    return 0;
}

/* Read a 1-byte Host Control Register */
int spi_hal_hcr_read_reg(spi_device_t * dev, uint16 regaddr, uint8 * pRegData)
{
    return spi_hal_hcr_read(dev, TRANSPORT_IO_FLAG_HCR_REGISTER, regaddr, pRegData, 1);
}

/*
 * Write 1 or more bytes to sequential address in HCR space.
 *
 * Unlike spi_hal_hcr_read, this interface supporpts only incrementing addresses.
 * (No TRANSPORT_IO_FLAG_NONINCR support for writes.)
 */
int spi_hal_hcr_write(spi_device_t * dev, uint16 regaddr, uint8 * pRegData, uint32 count)
{
    uint16_t done_status;
    uint16 cmd = 0;
    uint32 retry_count;
    qapi_Status_t status;
    int rv;

    ASSERT(count <= SPI_HCR_READSZ_MAX);

    /* Write count to HOST_CTRL_BYTE_SIZE */
    rv = spi_hal_reg_write(dev, SPI_SLV_REG_HOST_CTRL_BYTE_SIZE, count, SPI_TRANS_SHORT);
    if (rv) {
        FAIL_RETURN();
    }

    /* Command phase (write to HOST_CTRL_WR_PORT) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_SHORT);
    cmd = (SPI_WRITE_16BIT_MODE)
        | (SPI_INTERNAL_16BIT_MODE)
        | (SPI_SLV_REG_HOST_CTRL_WR_PORT);
    dev->tx_desc.buf_len = 2;
    dev->tx_desc.buf_phys_addr = &cmd;
    status = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, &dev->tx_desc, NULL, spi_io_complete_cb, dev);
    if (status != QAPI_OK) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

    /* Data phase (data from pRegData) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_BYTE);
    dev->tx_desc.buf_len = count;
    dev->tx_desc.buf_phys_addr = pRegData;
    status = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, &dev->tx_desc, NULL, spi_io_complete_cb, dev);
    if (status != QAPI_OK) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

    /* Write command to 'write to regaddr' to HOST_CTRL_CONFIG */
    cmd = (HOST_CTRL_REG_DIR_WR | (regaddr & HOST_CTRL_REG_ADDRESS_MSK));
    cmd |= HOST_CTRL_REG_ENABLE;
    rv = spi_hal_reg_write(dev, SPI_SLV_REG_HOST_CTRL_CONFIG, cmd, SPI_TRANS_SHORT);
    if (rv) {
        FAIL_RETURN();
    }

    /* Wait for write command to finish */
    done_status = 0;
    for (retry_count = SPI_SLV_TRANS_RETRY_COUNT; retry_count > 0; retry_count--) {
        (void)spi_hal_reg_read(dev, SPI_SLV_REG_SPI_STATUS, &done_status, SPI_TRANS_SHORT);
        if (done_status & SPI_SLV_REG_SPI_STATUS_BIT_HOST_ACCESS_DONE_MSK) {
            break;
        }
        qapi_Task_Delay(SPI_SLV_IO_DELAY);
    }
    if (retry_count == 0) {
        spihaldebug("%s: Failed (%d) to write (@0x%x). Last done_status=0x%x\r\n",
                    __FUNCTION__, status, regaddr, done_status);
        FAIL_RETURN();
    }
    write_retry_stats[SPI_SLV_TRANS_RETRY_COUNT - retry_count]++;

    return 0;
}

/* Write a 1-byte Host Control Register */
int spi_hal_hcr_write_reg(spi_device_t * dev, uint16 regaddr, uint8 RegData)
{
    uint8 reg_data = RegData;

    return spi_hal_hcr_write(dev, regaddr, &reg_data, 1);
}

int spi_hal_mboxfifo_read(spi_device_t * dev, uint16 regaddr, uint8 * pRegData, uint32 size)
{
    uint16 spi_command = 0;
    qapi_Status_t status;
    int rv;

#if defined(DEBUG)
    {
        uint16 avail = 0;

        /*
         * No need to check for space here. The caller uses a higher-level
         * LOOKAHEAD mechanism to insure that this read will work.
         */
        spi_hal_reg_read(dev, SPI_SLV_REG_RDBUF_BYTE_AVA, &avail, SPI_TRANS_SHORT);

        /*
         * NB: This may be an overly-conservative check.
         * Entire buffer doesn't need to be waiting before we begin to consume it.
         */
        if (avail < size) {
            FAIL_RETURN();
        }
    }
#endif

    /* Write size to DMA_SIZE */
    rv = spi_hal_reg_write(dev, SPI_SLV_REG_DMA_SIZE, size, SPI_TRANS_SHORT);
    if (rv) {
        FAIL_RETURN();
    }

    /* Command phase (read from regaddr) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_SHORT);
    spi_command = (SPI_READ_16BIT_MODE)
        | (SPI_EXTERNAL_16BIT_MODE)
        | (regaddr & SPI_REG_ADDRESS_MASK);
    dev->tx_desc.buf_len = 2;
    dev->tx_desc.buf_phys_addr = &spi_command;
    status = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, &dev->tx_desc, NULL, spi_io_complete_cb, dev);
    if (status != 0) {
        FAIL_RETURN();
    }

    spi_wait_for_transaction(dev);

    /* Data phase (read into pRegData) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_BYTE);
    dev->rx_desc.buf_len = size;
    dev->rx_desc.buf_phys_addr = pRegData;
    status = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, NULL, &dev->rx_desc, spi_io_complete_cb, dev);
    if (status != 0) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

    return 0;
}

int spi_hal_mboxfifo_write(spi_device_t * dev, uint16 regaddr, uint8 * pRegData, uint32 size)
{
    uint16 spi_command = 0;
    qapi_Status_t status;
    int rv;

#if defined(DEBUG)
    {
        uint16 avail = 0;
        /*
         * Upper layers use a Tx Credit system which guarantees that a
         * write to Quartz Slave will work. No need to re-validate here.
         */
        spi_hal_reg_read(dev, SPI_SLV_REG_WRBUF_SPC_AVA, &avail, SPI_TRANS_SHORT);

        if (avail < size) {
            FAIL_RETURN();
        }
    }
#endif

    /* Write size to DMA_SIZE */
    rv = spi_hal_reg_write(dev, SPI_SLV_REG_DMA_SIZE, size, SPI_TRANS_SHORT);
    if (rv) {
        FAIL_RETURN();
    }

    /* Command phase (write to regaddr) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_SHORT);
    spi_command = SPI_WRITE_16BIT_MODE | SPI_EXTERNAL_16BIT_MODE | (regaddr & SPI_REG_ADDRESS_MASK);
    dev->tx_desc.buf_len = 2;
    dev->tx_desc.buf_phys_addr = &spi_command;

    status = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, &dev->tx_desc, NULL, spi_io_complete_cb, dev);
    if (status) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

    /* Data phase (write from pRegData) */
    SPI_CONFIG_WIDTH_SET(dev, SPI_TRANS_BYTE);
    dev->tx_desc.buf_len = size;
    dev->tx_desc.buf_phys_addr = pRegData;
    status = qapi_SPIM_Full_Duplex(dev->hSPI, &dev->spi_trans_config, &dev->tx_desc, NULL, spi_io_complete_cb, dev);
    if (status) {
        FAIL_RETURN();
    }
    spi_wait_for_transaction(dev);

    return 0;
}

void spi_hal_int_task(void *h)
{
    trans_device_t *trans_dev = (trans_device_t *) h;
    uint32 signalled;
    spi_device_t *dev;
    transport_dsr_cb_t pfunc;

    dev = (spi_device_t *) trans_dev->dev;
    spihaldebug("%s: dev=%p\r\n", __FUNCTION__, dev);
    if (!dev) {
        QAPI_FATAL_ERR(0, 0, 0);
        qurt_signal_delete(&(dev->spi_isr_signal));
        qurt_thread_stop();
        return;
    }

    /* Clear any pending signal before going into the wait loop */
    qurt_signal_clear(&dev->spi_isr_signal, (SPI_HAL_ISR_TASK_TERM_EVT | SPI_HAL_ISR_TASK_EVT));
    spihaldebug("spi_hal_int_task: Started\r\n");

    for (;;) {
        spihaldebug("%s: top of loop\r\n", __FUNCTION__);

        signalled = qurt_signal_wait(&dev->spi_isr_signal,
                                     (SPI_HAL_ISR_TASK_TERM_EVT | SPI_HAL_ISR_TASK_EVT), QURT_SIGNAL_ATTR_CLEAR_MASK);

        if (signalled & SPI_HAL_ISR_TASK_TERM_EVT) {
            /* Signal back the requested thread to kill async task */
            spihaldebug("%s: Stopping\r\n", __FUNCTION__);
            qurt_signal_set(&(dev->spi_isr_task_completion), SPI_HAL_ISR_TASK_TERM_COMPLETE_EVT);
            qurt_signal_delete(&(dev->spi_isr_signal));
            qurt_thread_stop();
            break;
        }

        if (signalled & SPI_HAL_ISR_TASK_EVT) {
            pfunc = dev->dsr_cb;

            /* Call upper layer's registered DSR callback function */
            if (pfunc) {
                pfunc(trans_dev);
            }

            /*
             * The SPI interrupt was disabled in spi_hal_gpio_isr.
             * Re-enable it now, unless it was masked in the DSR.
             */
            if (!dev->is_intr_masked) {
                qapi_GPIOINT_Enable_Interrupt(dev->spi_intr_gpio_hdl, SPI_SLV_INTR_GPIO_NUM);
            }
        }
    }
}

void spi_hal_gpio_isr(qapi_GPIOINT_Callback_Data_t data)
{
    trans_device_t *trans_dev = (trans_device_t *) data;
    spi_device_t *dev;

    dev = (spi_device_t *) trans_dev->dev;
    if (!dev) {
        return;
    }

    /*
     * Temporarily disable the SPI interrupt and then wake the DSR thread.
     */

    qapi_GPIOINT_Disable_Interrupt(dev->spi_intr_gpio_hdl, SPI_SLV_INTR_GPIO_NUM);
    qurt_signal_set(&dev->spi_isr_signal, SPI_HAL_ISR_TASK_EVT);

}

/* SPI binding for Transport API */
static trans_dev_ops_t spi_ops = {
    .read_data = spi_hal_read_data,
    .write_data = spi_hal_write_data,
    .register_interrupt = spi_hal_register_interrupt,
    .deregister_interrupt = spi_hal_deregister_interrupt,
    .unmask_interrupt = spi_hal_unmask_interrupt,
    .mask_interrupt = spi_hal_mask_interrupt,
    .enable_trans = spi_hal_enable_trans,
    .disable_trans = spi_hal_disable_trans,
};

int spi_hal_read_data(void *tdev, io_mode_t iomode, unsigned int addr, void *dest, int count)
{
    trans_device_t *trans_dev = tdev;
    spi_device_t *dev;
    int rv;

    dev = trans_dev->dev;

    qurt_mutex_lock(&dev->spi_data_xfer_mutex);
    if (iomode & TRANSPORT_IO_FLAG_HCR_REGISTER) {
        rv = spi_hal_hcr_read(dev, iomode, addr, dest, count);
    } else {                    /* TRANSPORT_IO_FLAG_MBOX_FIFO */

        rv = spi_hal_mboxfifo_read(dev, addr, dest, count);
    }
    qurt_mutex_unlock(&dev->spi_data_xfer_mutex);

    return rv;
}

int spi_hal_write_data(void *tdev, io_mode_t iomode, unsigned int addr, void *src, int count)
{
    trans_device_t *trans_dev = tdev;
    spi_device_t *dev;
    int rv;

    dev = trans_dev->dev;

    qurt_mutex_lock(&dev->spi_data_xfer_mutex);
    if (iomode & TRANSPORT_IO_FLAG_HCR_REGISTER) {
        /* Handle Host Control Register writes */
        rv = spi_hal_hcr_write(dev, addr, src, count);
    } else {                    /* TRANSPORT_IO_FLAG_MBOXFIFO */

        /* Handle Mailbox FIFO writes */
        rv = spi_hal_mboxfifo_write(dev, addr, src, count);
    }
    qurt_mutex_unlock(&dev->spi_data_xfer_mutex);

    return rv;
}

int spi_hal_enable_trans(void *tdev)
{
    int rv;
    spi_device_t *dev = NULL;
    trans_device_t *trans_dev = tdev;

    if (!tdev) {
        FAIL_RETURN();
    }
    dev = (spi_device_t *) trans_dev->dev;

    rv = spi_hal_default_spi_slave_config(dev, SPI_CONFIG_DEFAULT);
    if (rv) {
        FAIL_RETURN();
    }
    qapi_Task_Delay(100);

    /* Enable the SPI interrupt */
    qapi_GPIOINT_Enable_Interrupt(dev->spi_intr_gpio_hdl, SPI_SLV_INTR_GPIO_NUM);

    return 0;
}

int spi_hal_disable_trans(void *tdev)
{
    spi_device_t *dev = NULL;
    trans_device_t *trans_dev = tdev;

    if (!tdev) {
        FAIL_RETURN();
    }
    dev = (spi_device_t *) trans_dev->dev;

    /* Disable IO */
    spi_hal_reg_write(dev, SPI_SLV_REG_SPI_CONFIG, 0, SPI_TRANS_SHORT);
    qapi_Task_Delay(SPI_SLV_IO_DELAY);

    qapi_GPIOINT_Disable_Interrupt(dev->spi_intr_gpio_hdl, SPI_SLV_INTR_GPIO_NUM);
    return 0;
}

int spi_hal_register_interrupt(void *tdev, transport_dsr_cb_t pfunc)
{
    spi_device_t *dev;
    trans_device_t *trans_dev = tdev;
    unsigned long intrstate;

    if (!tdev) {
        FAIL_RETURN();
    }
    dev = (spi_device_t *) trans_dev->dev;

    if (!dev) {
        FAIL_RETURN();
    }

    dev->dsr_cb = (void *)pfunc;

    INTR_BLOCK(intrstate);
    /* Register GPIO interrupt */
    if (QAPI_OK != qapi_GPIOINT_Register_Interrupt(dev->spi_intr_gpio_hdl,
                                                   SPI_SLV_INTR_GPIO_NUM,
                                                   spi_hal_gpio_isr,
                                                   (qapi_GPIOINT_Callback_Data_t) tdev,
                                                   QAPI_GPIOINT_TRIGGER_LEVEL_LOW_E, QAPI_GPIOINT_PRIO_HIGH_E, false)) {
        INTR_UNBLOCK(intrstate);
        FAIL_RETURN();
    }

/* TBDXXX: Call spi_hal_mask_interrupt and do it earlier and eliminate INTR_BLOCK/UNBLOCK? */
    /* We don't want to auto-enable this interrupt */
    qapi_GPIOINT_Disable_Interrupt(dev->spi_intr_gpio_hdl, SPI_SLV_INTR_GPIO_NUM);
    INTR_UNBLOCK(intrstate);

    qurt_mutex_lock(&dev->spi_data_xfer_mutex);

    spi_hal_reg_write(dev, SPI_SLV_REG_INTR_ENABLE, SPI_SLV_REG_INT_ALL_CPU, SPI_TRANS_SHORT);

    qurt_mutex_unlock(&dev->spi_data_xfer_mutex);

    return 0;
}

int spi_hal_deregister_interrupt(void *tdev)
{
    spi_device_t *dev = NULL;
    trans_device_t *trans_dev = tdev;

    dev = (spi_device_t *) trans_dev->dev;

    dev->dsr_cb = NULL;

    qurt_mutex_lock(&dev->spi_data_xfer_mutex);
    spi_hal_reg_write(dev, SPI_SLV_REG_INTR_ENABLE, 0x00, SPI_TRANS_SHORT);
    qurt_mutex_unlock(&dev->spi_data_xfer_mutex);

    qapi_GPIOINT_Disable_Interrupt(dev->spi_intr_gpio_hdl, SPI_SLV_INTR_GPIO_NUM);
    qapi_GPIOINT_Deregister_Interrupt(dev->spi_intr_gpio_hdl, SPI_SLV_INTR_GPIO_NUM);

    return 0;
}

/* Unmask (enable) interupts from the Target AT THE HOST without affecting Target state */
void spi_hal_unmask_interrupt(void *tdev)
{
    spi_device_t *dev;
    trans_device_t *trans_dev = tdev;
    unsigned long intrstate;

    dev = (spi_device_t *) trans_dev->dev;
    INTR_BLOCK(intrstate);
    qapi_GPIOINT_Enable_Interrupt(dev->spi_intr_gpio_hdl, SPI_SLV_INTR_GPIO_NUM);
    dev->is_intr_masked = FALSE;
    INTR_UNBLOCK(intrstate);
}

/* Mask (disable) interrupts from the device AT THE HOST without affecting Target state */
void spi_hal_mask_interrupt(void *tdev)
{
    spi_device_t *dev;
    trans_device_t *trans_dev = tdev;
    unsigned long intrstate;

    dev = (spi_device_t *) trans_dev->dev;
    INTR_BLOCK(intrstate);
    qapi_GPIOINT_Disable_Interrupt(dev->spi_intr_gpio_hdl, SPI_SLV_INTR_GPIO_NUM);
    dev->is_intr_masked = TRUE;
    INTR_UNBLOCK(intrstate);
}

int spi_hal_init(trans_device_t * tdev)
{
    spi_device_t *dev;
    uint16 reg_data;
    int rv;
    qapi_SPIM_Instance_t qup_instance;
    qapi_Status_t status;

    /* Allocate the device context */
    dev = (spi_device_t *) malloc(sizeof(spi_device_t));
    if (!dev) {
        spihaldebug("%s: Cannot malloc dev\r\n", __FUNCTION__);
        FAIL_RETURN();
    }

    spi_hal_tdev_dbg = tdev;
    spi_hal_dev_dbg = dev;

    tdev->ops = &spi_ops;
    tdev->dev = dev;

    memset(dev, 0, sizeof(*dev));
    dev->id = (tdev->id + QAPI_SPIM_INSTANCE_1_E);
    IS_VALID_DEV_ID(dev->id);

    qurt_signal_create(&dev->spi_signal);
    dev->isInit = TRUE;
    qurt_mutex_create(&dev->spi_data_xfer_mutex);
    qurt_signal_create(&dev->spi_isr_signal);
    qurt_signal_create(&dev->spi_isr_task_completion);

    qurt_thread_attr_set_name(&dev->spi_int_task_attr, SPI_HAL_INT_TASK_NAME);
    qurt_thread_attr_set_priority(&dev->spi_int_task_attr, SPI_HAL_INT_TASK_PRIO);
    qurt_thread_attr_set_stack_size(&dev->spi_int_task_attr, SPI_HAL_INT_TASK_STK_SIZE);

    if (QURT_EOK != qurt_thread_create(&dev->spi_int_task_id, &dev->spi_int_task_attr, spi_hal_int_task, (void *)tdev)) {
        spihaldebug("%s: Cannot create spi_int_task\r\n", __FUNCTION__);
        dev->spi_int_task_id = (unsigned long)NULL;
        goto ERROR;
    }

    spi_config_init(dev);

    qup_instance = dev->id;
    rv = qapi_SPIM_Open(qup_instance, &dev->hSPI);
    if (rv) {
        spihaldebug("%s: qapi_SPIM_Open failed (%d)\r\n", __FUNCTION__, rv);
        goto ERROR;
    }

    rv = qapi_SPIM_Enable(dev->hSPI);
    if (rv) {
        spihaldebug("%s: qapi_SPIM_Enable failed (%d)\r\n", __FUNCTION__, rv);
        goto ERROR;
    }

    /* Reset SPI Interface Block */
    rv = spi_hal_reg_write(dev, SPI_SLV_REG_SPI_CONFIG, SPI_SLV_REG_SPI_CONFIG_VAL_RESET, SPI_TRANS_SHORT);
    if (rv) {
        spihaldebug("%s: Failed to reset SPI block (%d)\r\n", __FUNCTION__, rv);
        goto ERROR;
    }

    qapi_Task_Delay(SPI_SLV_RESET_DELAY);

    /*
     * A register read value of 0xFFFF is used to detect the scenario of
     * SPI target disconnected.
     */
    reg_data = 0xFFFF;
    rv = spi_hal_reg_read(dev, SPI_SLV_REG_SPI_STATUS, &reg_data, SPI_TRANS_SHORT);
    if (rv) {
        spihaldebug("%s: Cannot read SPI_STATUS (%d)\r\n", __FUNCTION__, rv);
        goto ERROR;
    }
    if (reg_data == 0xFFFF) {
        spihaldebug("%s: SPI_STATUS value is invalid\r\n", __FUNCTION__);
        goto ERROR;
    }

    /* Pin configuration */
    dev->spi_intr_gpio_config.pin = SPI_SLV_INTR_GPIO_NUM;
    dev->spi_intr_gpio_config.func = 0;
    dev->spi_intr_gpio_config.dir = QAPI_GPIO_INPUT_E;
    dev->spi_intr_gpio_config.pull = QAPI_GPIO_NO_PULL_E;
    dev->spi_intr_gpio_config.drive = QAPI_GPIO_2P7MA_E;

    status = qapi_TLMM_Get_Gpio_ID(&dev->spi_intr_gpio_config, &dev->spi_intr_gpio_id);
    if (status != QAPI_OK) {
        spihaldebug("%s: Cannot get GPIO ID for interrupt pin (%d)\r\n", __FUNCTION__, status);
        goto ERROR;
    }

    spi_hal_gpioid_dbg = dev->spi_intr_gpio_id;

    status = qapi_TLMM_Config_Gpio(dev->spi_intr_gpio_id, &dev->spi_intr_gpio_config);
    if (status != QAPI_OK) {
        spihaldebug("%s: Cannot Configure GPIO interrupt pin (%d)\r\n", __FUNCTION__, status);
        goto ERROR;
    }

    /* We assume that the device is always present -- no hotplug.  */
    if (tdev->hif_callbacks.hif_trans_device_inserted != NULL) {
        if (tdev->hif_callbacks.hif_trans_device_inserted(tdev, FALSE) != 0) {
            spihaldebug("%s: hif_trans_device_inserted callback failed\r\n", __FUNCTION__);
            goto ERROR;
        }
    }
    spihaldebug("%s: success\r\n", __FUNCTION__);
    return 0;

 ERROR:
    /* TBDXXX: Disable, Close, free */
    dev->isInit = FALSE;
    tdev->hif_callbacks.hif_trans_device_inserted = NULL;
    tdev->hif_callbacks.hif_trans_device_removed = NULL;
    spi_hal_deinit(tdev);
    FAIL_RETURN();
}

int spi_hal_deinit(trans_device_t * tdev)
{
    spi_device_t *dev;

    if (!tdev) {
        FAIL_RETURN();
    }

    dev = tdev->dev;

    if (dev) {
        (void)qapi_SPIM_Disable(dev->hSPI);
        (void)qapi_SPIM_Close(dev->hSPI);

        /*
         * This shall also be called from hot plug device removal handler.
         * Since Quartz SDCC driver does not have hotplug functionality,
         * the device disconnect event is sent during de-initialization.
         */
        if (tdev->hif_callbacks.hif_trans_device_removed != NULL) {
            tdev->hif_callbacks.hif_trans_device_removed(tdev, FALSE);
        }

        if (dev->spi_intr_gpio_id) {
            qapi_TLMM_Release_Gpio_ID(&dev->spi_intr_gpio_config, dev->spi_intr_gpio_id);
            dev->spi_intr_gpio_id = 0;
        }

        spihaldebug("%s: Stop SPI intr task\r\n", __FUNCTION__);
        qurt_signal_set(&(dev->spi_isr_signal), SPI_HAL_ISR_TASK_TERM_EVT);

        /* Wait till the SPI intr task has died */
        qurt_signal_wait(&(dev->spi_isr_task_completion),
                         SPI_HAL_ISR_TASK_TERM_COMPLETE_EVT, QURT_SIGNAL_ATTR_CLEAR_MASK);
        spihaldebug("%s: async_task stopped\r\n", __FUNCTION__);

        qurt_signal_delete(&dev->spi_isr_task_completion);
        qurt_signal_delete(&dev->spi_signal);
        qurt_mutex_delete(&dev->spi_data_xfer_mutex);

        free(dev);
        tdev->ops = NULL;
        tdev->dev = NULL;
    }
    spihaldebug("%s: Done\r\n", __FUNCTION__);
    return 0;
}

/*
 * This hack allows high-level code to play with
 * SPI clock frequency of a single SPI device.
 *
 * This is intended for testing/demonstration purposes.
 */
void spi_hal_config_freq(uint freq)
{
    qurt_mutex_lock(&spi_hal_dev_dbg->spi_data_xfer_mutex);
    SPI_CONFIG_FREQ_SET(spi_hal_dev_dbg, freq);
    qurt_mutex_unlock(&spi_hal_dev_dbg->spi_data_xfer_mutex);
}

/* For debug, a convenient place to set a breakpoint */
__attribute__ ((noinline))
void spi_hal_failure(void)
{
    static unsigned int spi_hal_failure_count;
    spi_hal_failure_count++;
}
