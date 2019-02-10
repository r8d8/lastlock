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

#ifndef _SPI_HAL_H
#define _SPI_HAL_H

#include "qapi_gpioint.h"
#include "qapi_tlmm.h"

/* SPI SLAVE MODULE registers */
#define SPI_SLV_REG_DMA_SIZE            0x0100  // DMA Size
#define SPI_SLV_REG_WRBUF_SPC_AVA       0x0200  // Write buffer space available
#define SPI_SLV_REG_RDBUF_BYTE_AVA      0x0300  // Read buffer byte available
#define SPI_SLV_REG_SPI_CONFIG          0x0400  // SPI configuration
#define SPI_SLV_REG_SPI_STATUS          0x0500  // SPI Status
#define SPI_SLV_REG_HOST_CTRL_BYTE_SIZE 0x0600  // Host control register access byte size

#define SPI_SLV_REG_HOST_CTRL_CONFIG    0x0700  // Host control register configure
#define SPI_SLV_REG_HOST_CTRL_NOADDRINC (1<<6)

#define SPI_SLV_REG_HOST_CTRL_RD_PORT   0x0800  // Host control register read port
#define SPI_SLV_REG_HOST_CTRL_WR_PORT   0x0A00  // Host control register write port
#define SPI_SLV_REG_INTR_CAUSE          0x0C00  // Interrupt cause

#define SPI_SLV_REG_INT_PACKET_AVAIL (1<<0)
#define SPI_SLV_REG_INT_RDBUF_ERROR  (1<<1)
#define SPI_SLV_REG_INT_WRBUF_ERROR  (1<<2)
#define SPI_SLV_REG_INT_ADDRESS_ERROR  (1<<3)
#define SPI_SLV_REG_INT_LOCAL_CPU (1<<4)
#define SPI_SLV_REG_INT_COUNTER  (1<<5)
#define SPI_SLV_REG_INT_CPU_ON  (1<<6)
#define SPI_SLV_REG_INT_ALL_CPU  (1<<7)
#define SPI_SLV_REG_INT_HCR_WR_DONE  (1<<8)
#define SPI_SLV_REG_INT_HCR_RD_DONE  (1<<9)
#define SPI_SLV_REG_INT_WRBUF_BELOW_WATERMARK  (1<<10)

#define SPI_SLV_REG_INTR_ENABLE         0x0D00  // Interrupt enable
#define SPI_SLV_REG_WRBUF_WRPTR         0x0E00  // Holds the write pointer for the write buffer
#define SPI_SLV_REG_WRBUF_RDPTR         0x0F00  // Holds the read pointer for the write buffer
#define SPI_SLV_REG_RDBUF_WRPTR         0x1000  // Holds the write pointer for the read buffer
#define SPI_SLV_REG_RDBUF_RDPTR         0x1100  // Holds the read pointer for the read buffer
#define SPI_SLV_REG_RDBUF_WATERMARK     0x1200  // Read buffer water mark
#define SPI_SLV_REG_WRBUF_WATERMARK     0x1300  // Write buffer water mark
#define SPI_SLV_REG_RDBUF_LOOKAHEAD1    0x1400  // Read buffer lookahead 1
#define SPI_SLV_REG_RDBUF_LOOKAHEAD2    0x1500  // Read buffer lookahead 2

#define SPI_SLV_MAX_IO_BUFFER_BYTES  3200

#define SPI_INTERNAL_8BIT_MODE   0x40
#define SPI_READ_8BIT_MODE       0x80
#define SPI_WRITE_8BIT_MODE      0x00

#define SPI_INTERNAL_16BIT_MODE  0x4000
#define SPI_EXTERNAL_16BIT_MODE  0x0000
#define SPI_READ_16BIT_MODE      0x8000
#define SPI_WRITE_16BIT_MODE     0x0000
#define SPI_REG_ADDRESS_MASK    ((1<<14) - 1)

#define SHIFT_ONE_BYTE            0x8
#define SPI_CMD_MASK_8BIT_MODE    0x3F
#define UPPER_2BYTE_MASK          0x00FF
#define LOWER_2BYTE_MASK          0xFF00

#define SPI_CMD_MASK_16BIT_MODE    0x3FFF

#define SPI_SLV_REG_SPI_CONFIG_VAL_RESET  (0x1 << 15)

#define SPI_SLV_REG_SPI_CONFIG_SWAP_BIT_LOC         0x2
#define SPI_SLV_REG_SPI_CONFIG_16BITMODE_BIT_LOC    0x1

#define SPI_SLV_REG_SPI_CONFIG_SWAP_BIT_MSK         ~(1<<SPI_SLV_REG_SPI_CONFIG_SWAP_BIT_LOC)
#define SPI_SLV_REG_SPI_CONFIG_16BITMODE_BIT_MSK    ~(1<<SPI_SLV_REG_SPI_CONFIG_16BITMODE_BIT_LOC)

#define SPI_SLV_REG_SPI_CONFIG_MBOX_INTR_EN           ( 0x1 << 8 )
#define SPI_SLV_REG_SPI_CONFIG_IO_ENABLE              ( 0x1 << 7 )
#define SPI_SLV_REG_SPI_CONFIG_KEEP_AWAKE_FOR_INTR    ( 0x1 << 4 )
#define SPI_SLV_REG_SPI_CONFIG_KEEP_AWAKE_EN          ( 0x1 << 3 )
#define SPI_SLV_REG_SPI_CONFIG_SWAP                   ( 0x1 << 2 )
#define SPI_SLV_REG_SPI_CONFIG_16BITMODE              ( 0x1 << 1 )
#define SPI_SLV_REG_SPI_CONFIG_PREFETCH_MODE          ( 0x1 << 0 )

/* Default setting for SPI_SLV_REG_SPI_CONFIG register */
#define SPI_CONFIG_DEFAULT (SPI_SLV_REG_SPI_CONFIG_IO_ENABLE | SPI_SLV_REG_SPI_CONFIG_PREFETCH_MODE)

#define READ_COUNT_2_BYTE 0x2

#define HOST_CTRL_REG_DIR_RD  (0x0 << 14)
#define HOST_CTRL_REG_DIR_WR  (0x1 << 14)
#define HOST_CTRL_REG_ENABLE  (0x1 << 15)

/* Should always work the first time....no retry needed.  */
#define SPI_SLV_TRANS_RETRY_COUNT 3
#define SPI_SLV_IO_DELAY 10 /* microseconds */

#define SPI_SLV_RESET_DELAY 10 /* microseconds */



#define HOST_CTRL_REG_ADDRESS_MSK  0x3FFF
#define SPI_SLV_REG_SPI_STATUS_BIT_HOST_ACCESS_DONE_MSK 0x1
#define SPI_SLV_REG_SPI_STATUS_BIT_HOST_ACCESS_DONE_VAL 0x1
#define SPI_SLV_INTR_GPIO_NUM 21

/*
 * Some valid values:
 * 3000000, 4000000, 6000000, 8000000, 12000000, 24000000, 48000000
 */
#define SPI_SLV_CLOCK_FREQUENCY_DEFAULT 3000000

#define SPI_HAL_INT_TASK_NAME         "SPIintr"
#define SPI_HAL_INT_TASK_PRIO         16
#define SPI_HAL_INT_TASK_STK_SIZE     1024

#define SPI_HAL_ISR_TASK_TERM_EVT     0x01
#define SPI_HAL_ISR_TASK_EVT          0x02

#define SPI_HAL_ISR_TASK_TERM_COMPLETE_EVT 0x04

/* Maximum number of bytes in HCR space that can be read at once over SPI */
#define SPI_HCR_READSZ_MAX 32

typedef enum spi_trans_width {
    SPI_TRANS_BYTE = 0x1,
    SPI_TRANS_SHORT = 0x2,
    SPI_TRANS_WORD = 0x4
} spi_trans_bit_width_t;

/*
 * WORKAROUND
 * This matches the ROM layout of the spi_config_t structure.
 * In particular, note that the final two fields are 8-bits each.
 */
typedef struct {
    qapi_SPIM_Clk_Polarity_t SPIM_Clk_Polarity;
    qapi_SPIM_Shift_Mode_t SPIM_Shift_Mode;
    qapi_SPIM_CS_Polarity_t SPIM_CS_Polarity;
    qapi_SPIM_CS_Mode_t SPIM_CS_Mode;
    qapi_SPIM_Clk_Mode_t SPIM_Clk_Always_On;
    uint8_t SPIM_Bits_Per_Word;
    uint8_t SPIM_Slave_Index;
    uint32_t min_Slave_Freq_Hz;
    uint32_t max_Slave_Freq_Hz;
    uint32_t deassertion_Time_Ns;
    uint8_t loopback_Mode;      /* <<<< 8-bit, to match ROM */
    uint8_t hs_Mode;            /* <<<< 8-bit, to match ROM */
} qapi_SPIM_Config_WAR_t;

typedef struct spi_device {
    uint32 id;
    qapi_SPIM_Config_t spi_trans_config;
    qurt_signal_t spi_signal;
#define SPI_SIGNAL_DONE 1
    qurt_thread_attr_t spi_int_task_attr;
    qurt_thread_t spi_int_task_id;      /* task to handle async commands */
    qurt_signal_t spi_isr_signal;
    qurt_signal_t spi_isr_task_completion;
    qapi_SPIM_Transfer_t tx_desc;
    qapi_SPIM_Transfer_t rx_desc;
    qapi_Instance_Handle_t spi_intr_gpio_hdl;
    qapi_GPIO_ID_t spi_intr_gpio_id;
    qapi_TLMM_Config_t spi_intr_gpio_config;
    qbool_t is_intr_masked;     /* interrupt is currently masked by upper layers of SW? */
    void *dsr_cb;
    void *hSPI;
    qurt_mutex_t spi_data_xfer_mutex;
    qbool_t isInit;
} spi_device_t;

int spi_hal_deinit(trans_device_t * tdev);
int spi_hal_init(trans_device_t * tdev);

#endif
