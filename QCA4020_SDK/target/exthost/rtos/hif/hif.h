/*
 * Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
 * Copyright (c) 2004-2005 Qualcomm Atheros, Inc.
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

#ifndef _HIF_H_
#define _HIF_H_

#define DEBUG
#undef DEBUG

#define HIF_OK 0
#define HIF_PENDING 1
#define HIF_ERROR 2
#define HIF_EINVAL 3
#define HIF_ETRANSPORT 4

/* direction - Direction of transfer (HIF_READ/HIF_WRITE). */
#define HIF_READ 0x00000001
#define HIF_WRITE 0x00000002
#define HIF_DIR_MASK (HIF_READ | HIF_WRITE)

/* type - An interface may support different kind of read/write commands.
 * For example: SDIO supports CMD52/CMD53s. In case of MSIO it
 * translates to using different kinds of TPCs. The command type
 * is thus divided into a basic and an extended command and can
 * be specified using HIF_BASIC_IO/HIF_EXTENDED_IO.
 */
#define HIF_BASIC_IO 0x00000004
#define HIF_EXTENDED_IO 0x00000008
#define HIF_TYPE_MASK (HIF_BASIC_IO | HIF_EXTENDED_IO)

/* emode - This indicates the whether the command is to be executed in a
 * blocking or non-blocking fashion (HIF_SYNCHRONOUS/
 * HIF_ASYNCHRONOUS). The read/write data paths in HTCA have been
 * implemented using the asynchronous mode allowing the the bus
 * driver to indicate the completion of operation through the
 * registered callback routine. The requirement primarily comes
 * from the contexts these operations get called from (a driver's
 * transmit context or the ISR context in case of receive).
 * Support for both of these modes is essential.
 */
#define HIF_SYNCHRONOUS 0x00000010
#define HIF_ASYNCHRONOUS 0x00000020
#define HIF_EMODE_MASK (HIF_SYNCHRONOUS | HIF_ASYNCHRONOUS)

/* dmode - An interface may support different kinds of commands based on
 * the tradeoff between the amount of data it can carry and the
 * setup time. Byte and Block modes are supported (HIF_BYTE_BASIS/
 * HIF_BLOCK_BASIS). In case of latter, the data is rounded off
 * to the nearest block size by padding. The size of the block is
 * configurable at compile time using the HIF_BLOCK_SIZE and is
 * negotiated with the target during initialization after the
 * AR6000 interrupts are enabled.
 */
#define HIF_BYTE_BASIS 0x00000040
#define HIF_BLOCK_BASIS 0x00000080
#define HIF_DMODE_MASK (HIF_BYTE_BASIS | HIF_BLOCK_BASIS)

/* amode - This indicates if the address has to be incremented on AR6000
 * after every read/write operation (HIF_FIXED_ADDRESS/HIF_INCREMENTAL_ADDRESS).
 */
#define HIF_FIXED_ADDRESS 0x00000100
#define HIF_INCREMENTAL_ADDRESS 0x00000200
#define HIF_AMODE_MASK (HIF_FIXED_ADDRESS | HIF_INCREMENTAL_ADDRESS)

#define HIF_WR_ASYNC_BYTE_FIX \
        (HIF_WRITE | HIF_ASYNCHRONOUS | HIF_EXTENDED_IO | HIF_BYTE_BASIS | \
         HIF_FIXED_ADDRESS)
#define HIF_WR_ASYNC_BYTE_INC \
        (HIF_WRITE | HIF_ASYNCHRONOUS | HIF_EXTENDED_IO | HIF_BYTE_BASIS | \
         HIF_INCREMENTAL_ADDRESS)
#define HIF_WR_ASYNC_BLOCK_INC \
        (HIF_WRITE | HIF_ASYNCHRONOUS | HIF_EXTENDED_IO | HIF_BLOCK_BASIS | \
         HIF_INCREMENTAL_ADDRESS)
#define HIF_WR_SYNC_BYTE_FIX \
        (HIF_WRITE | HIF_SYNCHRONOUS | HIF_EXTENDED_IO | HIF_BYTE_BASIS | \
         HIF_FIXED_ADDRESS)
#define HIF_WR_SYNC_BYTE_INC \
        (HIF_WRITE | HIF_SYNCHRONOUS | HIF_EXTENDED_IO | HIF_BYTE_BASIS | \
         HIF_INCREMENTAL_ADDRESS)
#define HIF_WR_SYNC_BLOCK_INC \
        (HIF_WRITE | HIF_SYNCHRONOUS | HIF_EXTENDED_IO | HIF_BLOCK_BASIS | \
         HIF_INCREMENTAL_ADDRESS)
#define HIF_WR_ASYNC_BLOCK_FIX \
        (HIF_WRITE | HIF_ASYNCHRONOUS | HIF_EXTENDED_IO | HIF_BLOCK_BASIS | \
         HIF_FIXED_ADDRESS)
#define HIF_WR_SYNC_BLOCK_FIX \
        (HIF_WRITE | HIF_SYNCHRONOUS | HIF_EXTENDED_IO | HIF_BLOCK_BASIS | \
         HIF_FIXED_ADDRESS)
#define HIF_RD_SYNC_BYTE_INC \
        (HIF_READ | HIF_SYNCHRONOUS | HIF_EXTENDED_IO | HIF_BYTE_BASIS | \
         HIF_INCREMENTAL_ADDRESS)
#define HIF_RD_SYNC_BYTE_FIX \
        (HIF_READ | HIF_SYNCHRONOUS | HIF_EXTENDED_IO | HIF_BYTE_BASIS | \
         HIF_FIXED_ADDRESS)
#define HIF_RD_ASYNC_BYTE_FIX \
        (HIF_READ | HIF_ASYNCHRONOUS | HIF_EXTENDED_IO | HIF_BYTE_BASIS | \
         HIF_FIXED_ADDRESS)
#define HIF_RD_ASYNC_BLOCK_FIX \
        (HIF_READ | HIF_ASYNCHRONOUS | HIF_EXTENDED_IO | HIF_BLOCK_BASIS | \
         HIF_FIXED_ADDRESS)
#define HIF_RD_ASYNC_BYTE_INC \
        (HIF_READ | HIF_ASYNCHRONOUS | HIF_EXTENDED_IO | HIF_BYTE_BASIS | \
         HIF_INCREMENTAL_ADDRESS)
#define HIF_RD_ASYNC_BLOCK_INC \
        (HIF_READ | HIF_ASYNCHRONOUS | HIF_EXTENDED_IO | HIF_BLOCK_BASIS | \
         HIF_INCREMENTAL_ADDRESS)
#define HIF_RD_SYNC_BLOCK_INC \
        (HIF_READ | HIF_SYNCHRONOUS | HIF_EXTENDED_IO | HIF_BLOCK_BASIS | \
         HIF_INCREMENTAL_ADDRESS)
#define HIF_RD_SYNC_BLOCK_FIX \
        (HIF_READ | HIF_SYNCHRONOUS | HIF_EXTENDED_IO | HIF_BLOCK_BASIS | \
        HIF_FIXED_ADDRESS)

enum hif_device_config_opcode {
    HIF_DEVICE_GET_MBOX_BLOCK_SIZE,
    HIF_DEVICE_SET_CONTEXT,
    HIF_DEVICE_GET_CONTEXT,
};

/* HIF CONFIGURE definitions:
 *
 * HIF_DEVICE_GET_MBOX_BLOCK_SIZE
 * input : none
 * output : array of 4 uint32_t
 * notes: block size is returned for each mailbox (4)
 *
 * HIF_DEVICE_SET_CONTEXT
 * input : arbitrary pointer-sized value
 * output: none
 * notes: stores an arbitrary value which can be retrieved later
 *
 * HIF_DEVICE_GET_CONTEXT
 * input: none
 * output : arbitrary pointer-sized value
 * notes: retrieves an arbitrary value which was set earlier
 */
struct cbs_from_hif {
    void *context;              /* context to pass to the dsrhandler
                                 * note : rw_completion_hdl is provided the context
                                 * passed to hif_read_write
                                 */
    int (*rw_completion_hdl) (void *rw_context, int status);
    int (*dsr_hdl) (void *context);
};

struct cbs_from_os {
    void *context;              /* context to pass for all callbacks. */
    int (*dev_inserted_hdl) (void *context, void *hif_handle);
    int (*dev_removed_hdl) (void *context, void *hif_handle);
    int (*dev_suspend_hdl) (void *context);
    int (*dev_resume_hdl) (void *context);
    int (*dev_wakeup_hdl) (void *context);
#if defined(DEVICE_POWER_CHANGE)
    int (*dev_pwr_change_hdl) (void *context, HIF_DEVICE_POWER_CHANGE_TYPE config);
#endif                          /* DEVICE_POWER_CHANGE */
};

/* other interrupts (non-Recv) are pending, host
 * needs to read the register table to figure out what
 */
#define HIF_OTHER_EVENTS BIT(0)

#define HIF_RECV_MSG_AVAIL BIT(1)       /* pending recv packet */

struct hif_pending_events_info {
    uint32_t events;
    uint32_t look_ahead;
    uint32_t available_recv_bytes;
};

/* Function to get pending events.  */
typedef int (*HIF_PENDING_EVENTS_FUNC) (void *device, struct hif_pending_events_info * p_events, void *async_context);

#define HIF_MASK_RECV TRUE
#define HIF_UNMASK_RECV FALSE
/* function to mask recv events */
typedef int (*HIF_MASK_UNMASK_RECV_EVENT) (void *device, qbool_t mask, void *async_context);

#ifdef HIF_MBOX_SLEEP_WAR
/* This API is used to update the target sleep state */
void hif_set_mbox_sleep(void *device, qbool_t sleep, qbool_t wait, qbool_t cache);
#endif

/* This API is used to perform any global initialization of the HIF layer
 * and to set OS driver callbacks (i.e. insertion/removal) to the HIF layer
 */
int hif_init(struct cbs_from_os *callbacks);

/* This API allows the calling layer to attach callbacks from HIF */
int hif_attach(void *device, struct cbs_from_hif *callbacks);

/* This API allows the calling layer to detach callbacks from HIF */
void hif_detach(void *device);

void hif_set_handle(void *hif_handle, void *handle);

#if NOTUSED
int hif_sync_read(void *device, uint32_t address, uint8_t * buffer, uint32_t length, uint32_t request, void *context);
#endif

size_t hif_get_device_size(void);

/* This API is used to provide the read/write interface over the specific bus
 * interface.
 * address - Starting address in the AR6000's address space. For mailbox
 * writes, it refers to the start of the mbox boundary. It should
 * be ensured that the last byte falls on the mailbox's EOM. For
 * mailbox reads, it refers to the end of the mbox boundary.
 * buffer - Pointer to the buffer containg the data to be transmitted or
 * received.
 * length - Amount of data to be transmitted or received.
 * request - Characterizes the attributes of the command.
 */
int hif_read_write(void *device, uint32_t address, void *buffer, uint32_t length, uint32_t request, void *context);

/* This can be initiated from the unload driver context when the OS has no more
 * use for
 * the device.
 */
void hif_shutdown_device(void *device);
void hif_surprise_removed(void *device);

void hif_mask_interrupt(void *device);

void hif_unmask_interrupt(void *device);

int hif_configure_device(void *device, enum hif_device_config_opcode opcode, void *config, uint32_t config_len);

#define DIAG_TRANSFER_LIMIT 2048U       /* maximum number of bytes that can be handled
                                         * atomically by DiagRead/DiagWrite */

#ifdef FEATURE_RUNTIME_PM
/* Runtime power management API of HIF to control
 * runtime pm. During Runtime Suspend the get API
 * return -EAGAIN. The caller can queue the cmd or return.
 * The put API decrements the usage count.
 * The get API increments the usage count.
 * The API's are exposed to HTT and WMI Services only.
 */
int hif_pm_runtime_get(void *device);
int hif_pm_runtime_put(void *device);
void *hif_runtime_pm_prevent_suspend_init(const char *name);
void hif_runtime_pm_prevent_suspend_deinit(void *data);
int hif_pm_runtime_prevent_suspend(void *ol_sc, void *data);
int hif_pm_runtime_allow_suspend(void *ol_sc, void *data);
int hif_pm_runtime_prevent_suspend_timeout(void *ol_sc, void *data, unsigned int delay);
void hif_request_runtime_pm_resume(void *ol_sc);
#else
static inline int hif_pm_runtime_get(void *device)
{
    return 0;
}

static inline int hif_pm_runtime_put(void *device)
{
    return 0;
}

static inline int hif_pm_runtime_prevent_suspend(void *ol_sc, void *context)
{
    return 0;
}

static inline int hif_pm_runtime_allow_suspend(void *ol_sc, void *context)
{
    return 0;
}

static inline int hif_pm_runtime_prevent_suspend_timeout(void *ol_sc, void *context, unsigned int msec)
{
    return 0;
}

static inline void *hif_runtime_pm_prevent_suspend_init(const char *name)
{
    return NULL;
}

static inline void hif_runtime_pm_prevent_suspend_deinit(void *context)
{
}

static inline void hif_request_runtime_pm_resume(void *ol_sc)
{
}
#endif

#endif                          /* _HIF_H_ */
