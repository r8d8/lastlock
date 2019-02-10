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

#ifndef __QS_WPAN_CONFIG_H__
#define __QS_WPAN_CONFIG_H__

/* This configuration file defines how threads and modules are mapped
 * under host QAPI serialization for BLE, 802.15.4, and Coexistence
 * technologies.
 *
 * The main consideration for this configuration is limiting RAM
 * usage by allowing modules to share threads and other resources
 * when possible. One example of this is the sharing of a thread
 * between the Zigbee and Thread protocols (whose stacks are mutually
 * exclusive on QCA4020). Another is Coexistence, which requires
 * few commands and can share resources with another technology.
 *
 * This configuration also allows threads to not be initialized when
 * a module will not be used, for example a BLE-only host
 * application.
 *
 * In order for two modules to share a thread, set both of their
 * mappings to the same value. For instance:
 *    #define QS_WPAN_HMI_MODULE_MAPPING         QS_WPAN_USE_HMI_THREAD
 *    #define QS_WPAN_TWN_MODULE_MAPPING         QS_WPAN_USE_HMI_THREAD
 *
 * To not initialize a resource, set its mapping to
 * QS_WPAN_NOT_INITIALIZED. For example:
 *    #define QS_WPAN_HMI_MODULE_MAPPING         QS_WPAN_NOT_INITIALIZED
 *
 * NOTE: HERH (Host Event Response Handler) ***must*** not share
 * a thread with any module that uses it in order to operate.
 * At the time of this writing, Zigbee is the only module that uses
 * HERH. Sharing a thread between Zigbee and HERH will result in a
 * deadlock.
*/

/* Defines the thread/resources each WPAN module will use. */
#define QS_WPAN_NOT_INITIALIZED           (0x00)
#define QS_WPAN_USE_BLE_THREAD            (0x01)
#define QS_WPAN_USE_HMI_THREAD            (0x02)
#define QS_WPAN_USE_TWN_THREAD            (0x03)
#define QS_WPAN_USE_ZB_THREAD             (0x04)
#define QS_WPAN_USE_COEX_THREAD           (0x05)
#define QS_WPAN_USE_HERH_THREAD           (0x06)
#define QS_WPAN_USE_FWUPGRADE_THREAD      (0x07)
#define QS_WPAN_USE_TLMM_THREAD           (0x08)

/* Defines which module's resources each module type will use. */
#define QS_WPAN_BLE_MODULE_MAPPING        QS_WPAN_USE_BLE_THREAD
#define QS_WPAN_HMI_MODULE_MAPPING        QS_WPAN_USE_HMI_THREAD
#define QS_WPAN_TWN_MODULE_MAPPING        QS_WPAN_USE_HMI_THREAD
#define QS_WPAN_ZB_MODULE_MAPPING         QS_WPAN_USE_HMI_THREAD
#define QS_WPAN_COEX_MODULE_MAPPING       QS_WPAN_USE_BLE_THREAD
#define QS_WPAN_HERH_MODULE_MAPPING       QS_WPAN_USE_HERH_THREAD   // See note above on HERH resources.
#define QS_WPAN_FWUPGRADE_MODULE_MAPPING  QS_WPAN_USE_HERH_THREAD
#define QS_WPAN_TLMM_MODULE_MAPPING  QS_WPAN_USE_HERH_THREAD

/* Helper macros for the application to determine if a module needs */
/* to be initialized, no need to modify. */
#if ((QS_WPAN_BLE_MODULE_MAPPING       == QS_WPAN_USE_BLE_THREAD) || (QS_WPAN_HMI_MODULE_MAPPING  == QS_WPAN_USE_BLE_THREAD) || \
     (QS_WPAN_TWN_MODULE_MAPPING       == QS_WPAN_USE_BLE_THREAD) || (QS_WPAN_ZB_MODULE_MAPPING   == QS_WPAN_USE_BLE_THREAD) || \
     (QS_WPAN_COEX_MODULE_MAPPING      == QS_WPAN_USE_BLE_THREAD) || (QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD) || \
     (QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD) || (QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_BLE_THREAD) )
   #define QS_WPAN_INIT_BLE_THREAD
#endif

#if ((QS_WPAN_BLE_MODULE_MAPPING       == QS_WPAN_USE_HMI_THREAD) || (QS_WPAN_HMI_MODULE_MAPPING  == QS_WPAN_USE_HMI_THREAD) || \
     (QS_WPAN_TWN_MODULE_MAPPING       == QS_WPAN_USE_HMI_THREAD) || (QS_WPAN_ZB_MODULE_MAPPING   == QS_WPAN_USE_HMI_THREAD) || \
     (QS_WPAN_COEX_MODULE_MAPPING      == QS_WPAN_USE_HMI_THREAD) || (QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD) || \
     (QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD) || (QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_HMI_THREAD) )
   #define QS_WPAN_INIT_HMI_THREAD
#endif

#if ((QS_WPAN_BLE_MODULE_MAPPING       == QS_WPAN_USE_TWN_THREAD) || (QS_WPAN_HMI_MODULE_MAPPING  == QS_WPAN_USE_TWN_THREAD) || \
     (QS_WPAN_TWN_MODULE_MAPPING       == QS_WPAN_USE_TWN_THREAD) || (QS_WPAN_ZB_MODULE_MAPPING   == QS_WPAN_USE_TWN_THREAD) || \
     (QS_WPAN_COEX_MODULE_MAPPING      == QS_WPAN_USE_TWN_THREAD) || (QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD) || \
     (QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD) || (QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_TWN_THREAD) )
   #define QS_WPAN_INIT_TWN_THREAD
#endif

#if ((QS_WPAN_BLE_MODULE_MAPPING       == QS_WPAN_USE_ZB_THREAD) || (QS_WPAN_HMI_MODULE_MAPPING  == QS_WPAN_USE_ZB_THREAD) || \
     (QS_WPAN_TWN_MODULE_MAPPING       == QS_WPAN_USE_ZB_THREAD) || (QS_WPAN_ZB_MODULE_MAPPING   == QS_WPAN_USE_ZB_THREAD) || \
     (QS_WPAN_COEX_MODULE_MAPPING      == QS_WPAN_USE_ZB_THREAD) || (QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD) || \
     (QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD) || (QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_ZB_THREAD) )
   #define QS_WPAN_INIT_ZB_THREAD
#endif

#if ((QS_WPAN_BLE_MODULE_MAPPING       == QS_WPAN_USE_HERH_THREAD) || (QS_WPAN_HMI_MODULE_MAPPING  == QS_WPAN_USE_HERH_THREAD) || \
     (QS_WPAN_TWN_MODULE_MAPPING       == QS_WPAN_USE_HERH_THREAD) || (QS_WPAN_ZB_MODULE_MAPPING   == QS_WPAN_USE_HERH_THREAD) || \
     (QS_WPAN_COEX_MODULE_MAPPING      == QS_WPAN_USE_HERH_THREAD) || (QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD) || \
     (QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD) || (QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_HERH_THREAD) )
   #define QS_WPAN_INIT_HERH_THREAD
#endif

#if ((QS_WPAN_BLE_MODULE_MAPPING       == QS_WPAN_USE_COEX_THREAD) || (QS_WPAN_HMI_MODULE_MAPPING  == QS_WPAN_USE_COEX_THREAD) || \
     (QS_WPAN_TWN_MODULE_MAPPING       == QS_WPAN_USE_COEX_THREAD) || (QS_WPAN_ZB_MODULE_MAPPING   == QS_WPAN_USE_COEX_THREAD) || \
     (QS_WPAN_COEX_MODULE_MAPPING      == QS_WPAN_USE_COEX_THREAD) || (QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD) || \
     (QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD) || (QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_COEX_THREAD) )
   #define QS_WPAN_INIT_COEX_THREAD
#endif

#if ((QS_WPAN_BLE_MODULE_MAPPING       == QS_WPAN_USE_FWUPGRADE_THREAD) || (QS_WPAN_HMI_MODULE_MAPPING  == QS_WPAN_USE_FWUPGRADE_THREAD) || \
     (QS_WPAN_TWN_MODULE_MAPPING       == QS_WPAN_USE_FWUPGRADE_THREAD) || (QS_WPAN_ZB_MODULE_MAPPING   == QS_WPAN_USE_FWUPGRADE_THREAD) || \
     (QS_WPAN_COEX_MODULE_MAPPING      == QS_WPAN_USE_FWUPGRADE_THREAD) || (QS_WPAN_HERH_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD) || \
     (QS_WPAN_FWUPGRADE_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD) || (QS_WPAN_TLMM_MODULE_MAPPING == QS_WPAN_USE_FWUPGRADE_THREAD) )
   #define QS_WPAN_INIT_FWUPGRADE_THREAD
#endif

#endif // __QS_WPAN_CONFIG_H__

