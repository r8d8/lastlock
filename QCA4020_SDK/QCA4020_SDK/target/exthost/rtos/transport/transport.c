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

#include "com_dtypes.h"
#include "qapi/qapi_types.h"
#include "qapi/qapi_status.h"
#include "qapi/qurt_thread.h"
#include "qapi/qurt_types.h"
#include "qapi/qurt_error.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_mutex.h"
#include "common_defs.h"
#include "transport.h"
#include "malloc.h"
#if defined(SDIO_TRANSPORT)
#include "qapi/qapi_master_sdcc.h"
#include "sdio_hal.h"
#endif
#if defined(SPI_TRANSPORT)
#include "qapi/qapi_spi_master.h"
#include "spi_hal.h"
#endif
#include "string.h"

#if !defined(SPI_TRANSPORT) && !defined(SDIO_TRANSPORT)
#error "Must define a transport: SPI or SDIO"
#endif

#if defined(SPI_TRANSPORT) && defined(SDIO_TRANSPORT)
/*
 * The reason this transport layer is implemented with
 * an actual table as opposed to macros that map to either
 * SPI or SDIO: Platforms may wish to simultaneously
 * support multiple QCA402x devices -- one SPI and another
 * SDIO.
 *
 * FUTURE: Optimize the common case where only a single
 * bus type, known as build-time, is used. In that case
 * we could eliminate the transport layer and instead
 * statically bind the appropriate SPI/SDIO functions
 * to "trans_" identifiers.
 */
#error "Must define exactly one transport: SPI or SDIO"
#endif

#if defined(DEBUG)
extern void PAL_CONSOLE_PRINTF(const char *format, ...);
#define transdebug PAL_CONSOLE_PRINTF
#else
#define transdebug(args...)
#endif

/* Called once during host initialization */
int trans_init(hif_callbacks_t * callbacks)
{

    int rv;
    trans_device_t *tdev = NULL;

    /*
     * QCA402x has no hotplug support for SDIO/SPI.
     * We assume one or two targets are statically wired during boot.
     */

    /* SDIO Instance */
#ifdef SDIO_TRANSPORT
    tdev = (trans_device_t *) malloc(sizeof(trans_device_t));

    if (tdev == NULL) {
        transdebug("%s: cannot malloc tdev\r\n", __FUNCTION__);
        return -1;
    }

    memset(tdev, 0, sizeof(trans_device_t));

    /* Populate transfer context from devcfg */
    tdev->id = 0;               /* SDCC 0 instance */
    tdev->transport = HTC_TRANSPORT_SDIO;

    memcpy(&tdev->hif_callbacks, callbacks, sizeof(hif_callbacks_t));

    rv = sdio_hal_init(tdev);

    if (rv) {
        transdebug("%s: sdio_hal_init returns %d\r\n", __FUNCTION__, rv);
        free(tdev);
    }
#endif

#ifdef SPI_TRANSPORT
    tdev = (trans_device_t *) malloc(sizeof(trans_device_t));

    if (!tdev) {
        transdebug("%s: cannot malloc tdev\r\n", __FUNCTION__);
        return -1;;
    }
    memset(tdev, 0, sizeof(*tdev));

    /* Populate transfer context from devcfg */
    tdev->id = 0;               /* SPI 0  instance */
    tdev->transport = HTC_TRANSPORT_SPI;

    memcpy(&tdev->hif_callbacks, callbacks, sizeof(hif_callbacks_t));

    rv = spi_hal_init(tdev);
    transdebug("%s: spi_hal_init returns %d\r\n", __FUNCTION__, rv);

    if (rv) {
        free(tdev);
    }
#endif

    return rv;
}

/* Called once during host shutdown */
int trans_deinit(trans_device_t * tdev)
{
    int rv;

    if (tdev->transport == HTC_TRANSPORT_SDIO) {
#if defined(SDIO_TRANSPORT)
        rv = sdio_hal_deinit(tdev);
#else
        rv = -1;
#endif
    } else {
#if defined(SPI_TRANSPORT)
        rv = spi_hal_deinit(tdev);
#else
        rv = -1;
#endif
    }

    free(tdev);

    return rv;
}

void trans_set_hifcontext(trans_device_t * tdev, void *hifdevice)
{
    tdev->context = hifdevice;
}

void *trans_get_hifcontext(trans_device_t * tdev)
{
    return tdev->context;
}

int trans_reset_target(trans_device_t * tdev)
{
    return 0;
}

int trans_read_data(trans_device_t * tdev, io_mode_t iomode, unsigned int addr, void *src, int count)
{
    return tdev->ops->read_data(tdev, iomode, addr, src, count);
}

int trans_write_data(trans_device_t * tdev, io_mode_t iomode, unsigned int addr, void *src, int count)
{
    return tdev->ops->write_data(tdev, iomode, addr, src, count);
}

int trans_register_interrupt(trans_device_t * tdev, transport_dsr_cb_t pfunc)
{
    return tdev->ops->register_interrupt(tdev, pfunc);
}

int trans_deregister_interrupt(trans_device_t * tdev)
{
    return tdev->ops->deregister_interrupt(tdev);
}

void trans_unmask_interrupt(trans_device_t * tdev)
{
    tdev->ops->unmask_interrupt(tdev);
}

void trans_mask_interrupt(trans_device_t * tdev)
{
    tdev->ops->mask_interrupt(tdev);
}

int trans_enable_trans(trans_device_t * tdev)
{
    return tdev->ops->enable_trans(tdev);
}

int trans_disable_trans(trans_device_t * tdev)
{
    return tdev->ops->disable_trans(tdev);
}
