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

#ifndef  __SPI_HW_H_INCLUDED

#define  __SPI_HW_H_INCLUDED

#define HIF_ACTIVE_MBOX_INDEX (0)

#define HIF_MBOX_BLOCK_SIZE                32
#define HIF_MBOX_BASE_ADDR                 0x800
#define HIF_MBOX_WIDTH                     0x800

#define ATH_TRANS_ADDR_MASK 0x7FFF  

#define HIF_MBOX_START_ADDR(mbox)  (HIF_MBOX_BASE_ADDR + mbox * HIF_MBOX_WIDTH)

typedef struct spi_read_data_s {
	uint8_t  space[2];
	union  {
		uint8_t   val8;
		uint16_t  val16;
		uint32_t  val32;
	} real_data;
} spi_read_data_t;

typedef union mb_status_s {
	uint32_t  mb_status_val;
	struct  {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint8_t  gmbox_rx_avail;
		uint8_t  host_int_status2;
		uint8_t  rx_lookahead_valid;
		uint8_t  mbox_fram;
#else
		uint8_t  mbox_fram;
		uint8_t  rx_lookahead_valid;
		uint8_t  host_int_status2;
		uint8_t  gmbox_rx_avail;
#endif
	} status_byte;
} mb_status_t;

typedef union mailbox_transfer_s {
	uint16_t  status;
	uint16_t  buf_size;
	uint8_t   *pbuf;
} mailbox_transfer_t;

typedef struct spi_hw_ctxt_s {
	mb_status_t  mb_status;
} spi_hw_ctxt_t;

int read_mailboxs(mailbox_transfer_t *pXfer, int size);		

#endif
