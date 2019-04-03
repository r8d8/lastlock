/* 
 * Copyright (c) 2018  Qualcomm Technologies, Inc.
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

 /** @file qapi_exhost_devcfg.h
* @addtogroup qapi_Exhost_Devcfg
 * @{
 *
 *  @details The exhost_devcfg module provides api to get dev configure setting for 
 *  exhost interface.
 *
 *
 * @}
*/

#ifndef _QAPI_EXHOST_DEVCFG_H_
#define _QAPI_EXHOST_DEVCFG_H_

#define MAX_NUM_SERVICE_QUEUE          (6)

 /** @addtogroup qapi_Exhost_Devcfg
@{ */
 
/*----------------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------------*/
 
/**
 * Represents a set of exhost device configure setting.
 *
 */
typedef struct {
    uint32_t heart_beat_enable;
    /**< 0: disable exhost heart beat, 1: enable exhost heart beat */
    uint32_t heart_beat_interval;
    /**< exhost heart beat interval unit:second */
    uint32_t uart_enable;
    /**< 0: disable exhost uart interface, 1: enable exhost uart interface */
    uint32_t uart_device_id;
    /**< exhost uart device id */
    uint32_t uart_port;
    /**< 0: quartz high speed uart port, 1: quartz debug uart port */
    uint32_t  uart_baud_rate;
    /**< uart port baud rate */
    uint32_t  uart_flowcontrol;
    /**< 0: disable uart HW flow control, 1: enable uart HW flow control */
    uint32_t uart_num_of_sq;
    /**< number of service queues for UART interface */
    uint8_t uart_sq_ids[MAX_NUM_SERVICE_QUEUE];
    /**< service queue id list for UART interface */
    uint32_t  spi_enable;
    /**< 0: disable exhost spi interface, 1: enable exhost spi interface */
    uint32_t spi_device_id;
    /**< exhost spi device id */
    uint32_t spi_block_size;
    /**< exhost spi block size */
    uint32_t spi_num_of_sq;
    /**< number of service queues for SPI interface */
    uint8_t spi_sq_ids[MAX_NUM_SERVICE_QUEUE];
    /**< service queue id list for SPI interface */
} qapi_Exhost_Devcfg_t;

/** @} */ /* end_addtogroup qapi_Exhost_Devcfg */ 

/*----------------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------------*/
 
/* Exhost Devcfg APIs */
/** @addtogroup qapi_Exhost_Devcfg
@{ */
 
/**
 * @brief Get Exhost Device Configure
 *
 * @param[out] devcfg    Exhost Devcfg
 *
 * @return
 * On success, QAPI_OK is returned; on error, QAPI_ERROR is returned.
 */
qapi_Status_t qapi_Get_Exhost_Devcfg(qapi_Exhost_Devcfg_t *devcfg);


/** @} */ /* end_addtogroup qapi_Exhost_Devcfg */ 

#endif /* _QAPI_EXHOST_DEVCFG_H_ */
