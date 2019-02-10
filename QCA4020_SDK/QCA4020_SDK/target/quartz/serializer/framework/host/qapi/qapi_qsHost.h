/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
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

#ifndef __QAPI_QSHOST_H__
#define __QAPI_QSHOST_H__

#include <stdint.h>

#define QAPI_QS_OK             (0x00)
#define QAPI_QS_ERR            (0x01)

#define QAPI_QS_UART_E         (0x00)
#define QAPI_QS_SPI_E          (0x01)
#define QAPI_QS_SDIO_E         (0x02)

#define QAPI_QS_MODULE_WLAN         (0x00)
#define QAPI_QS_MODULE_BLE          (0x01)
#define QAPI_QS_MODULE_HMI          (0x02)
#define QAPI_QS_MODULE_ZIGBEE       (0x03)
#define QAPI_QS_MODULE_THREAD       (0x04)
#define QAPI_QS_MODULE_COEX         (0x05)
#define QAPI_QS_MODULE_HERH         (0x06)
#define QAPI_QS_MODULE_FWUPGRADE    (0x07)
#define QAPI_QS_MODULE_TLMM         (0x08)
#define QAPI_QS_MODULE_MAX          (0x09)
#define QAPI_QS_HELLO_REQ_E         (0x0E)
#define QAPI_QS_HELLO_RESP_E        (0x0F)

#define QAPI_QS_EVENT_SERVER_EXIT     (0x01<<0)
#define QAPI_QS_EVENT_TARGET_ASSERT   (0x01<<1)

typedef void (* WlanCb_t)(uint8_t dev_Id, uint32_t cb_Id, void *app_Cxt, void  *buf, uint32_t buf_Len);
typedef void (* WpanCb_t)(uint8_t module, uint8_t fileId, uint16_t eventId, uint32_t buf_Len, uint8_t *buf);
typedef void (* eventCb_t)(uint32_t eventId, void *param);

#ifdef CONFIG_DAEMON_MODE

/* Sets target device ID.
 * DO NOT include this function in customer documentation.
 * This is to be used only by TABI for internal testing.

  @param targetId    Target ID to be set.

  @return 0 for success, non-zero for failure.
*/
uint32_t qapi_Qs_Set_Target_Id(uint8_t targetId);

/* Applications should use this QAPI to initialize the target for hosted mode.

  @param serverName   Name of daemon server queue.
  @param maxMsgSize   Maximum possible message size.
  @param maxMsgCnt    Maximum possible message count.

  @return 0 for success, non-zero for failure.
*/
uint32_t qapi_Qs_Init(char *serverName, uint16_t maxMsgSize, uint16_t maxMsgCnt);

/* Applications should use this QAPI to deinitialize hosted mode feature */
uint32_t qapi_Qs_DeInit();

/* Applications should use this QAPI to register event callback.

  @param cb           Event callback.
  @param parameter    Parameter to pass the callback.

  @return 0 for success, non-zero for failure.
*/
uint32_t qapi_Qs_Register_Cb(eventCb_t cb, void *parameter);

#else

/* Applications must initialize each required module, transport will be initialized internally.
 * device_Name: Name of the actual device to be used for transport
 * Multiple modules can use the same device */
uint32_t qapi_Qs_Init(uint8_t module, uint32_t transport, char *device_Name);

/* Whenever applications send a QAPI request to set a callback function for asynchronous event, this function must be
 * called to set a  callback locally on host for the given module.
 * WLAN module must have callback of type WlanCb_t
 * BLE must have a callback of type WpanCb_t */
uint32_t qapi_Qs_DeInit(uint8_t module);

#endif /* CONFIG_DAEMON_MODE */
#endif /* __QAPI_QSHOST_H__ */

