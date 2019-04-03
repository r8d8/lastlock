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

#ifdef CONFIG_DAEMON_MODE

#ifndef __TARGET_MML_API_H__
#define __TARGET_MML_API_H__

#include <stdint.h>

/* Header length */
#define TOTAL_HEADER_LEN                      10

/* Service IDs */
#define MML_QAPI_SQ_ID                        0
#define MML_BLE_DATA_SQ_ID                    1
#define MML_WLAN_DATA_SQ_ID                   2
#define MML_THREAD_DATA_SQ_ID                 3
#define MML_MGMT_SQ_ID                        4
#define MML_DIAG_SQ_ID                        5
#define MML_NUM_SQ_ID                         6

/* Return values of data manager APIs */
typedef enum MmlReturnCodes_e
{
    MML_SUCCESS_E,
    MML_FAILURE_E,
    MML_UNKNOWN_CMD_E,
    MML_MEMORY_FAILURE_E,
    MML_INVALID_DATA_E,
    MML_INVALID_SQ_ID_E,
    MML_SQ_ID_IN_USE
} MmlReturnCodes_t;


/* Callback function prototype for RX complete and Tx complete.
 *
 * @param       SqId              Service ID.
 * @param       BufLen            Length of buffer.
 * @param       Buf               Character buffer.
 * @param       ServiceCxt        Service specified context. Set by services when callback is registered.
 * @param       ServiceData       Service specific data used only for QAPIs at this point. It will be set to 
 *                                NULL while calling callbacks for mgmt,diag and datamanager services.
 *
 * @return      MML_API_SUCCESS_E for success, non-zero for failure.
 */
typedef void (* mmlCb_t)(uint8_t SqId, uint16_t BufLen, char *Buf, void *ServiceCxt, void *ServiceData);


/*
 * Transmit data to host for given service ID.
 * Caller of this API should allocate 'required bytes + TOTAL_HEADER_LEN' and use TOTAL_HEADER_LEN as an offset
 * for start of the data.
 * First TOTAL_HEADER_LEN will be filled by this API.
 * BufLen is for total uffer length including TOTAL_HEADER_LEN bytes.
 * ServiceData parameter is for QAPI internal use. It will be ignored for other services.
 *
 * @param       SqId              Service ID.
 * @param       BufLen            Length of allocated buffer (including TOTAL_HEADER_LEN).
 * @param       Buf               Buffer to be transmitted.
 * @param       ServiceData       Service specific data used only for QAPIs at this point. Mgmt,diag and 
                                  datamanager services should set this to NULL.
 *
 * @return      MML_API_SUCCESS_E for success, non-zero for failure.
 */ 
MmlReturnCodes_t mmlServiceQueueSend(uint8_t SqId, uint16_t BufLen, char *Buf, void *ServiceData);


/*
 * Use this API to register callback functions and application specific context for a given serivice queue ID.
 *
 * After a packet is received from host for given service ID, set 'msgRcvdCb' will be called.
 * This function MUST use mmlReleaseBuf() to free the memory. It MUST NOT use library free() function.
 * mmlReleaseBuf() must be called for both- success and failure.
 * Callback set as 'msgSentCb' is called when transmission of a packet from Quartz to host completes successfully.
 * Freeing of the sent memory block depends on the service specific application which should use this callback 
 * for the same.  Callback 'msgSentCb' MUST NOT use mmlReleaseBuf() function.
 *
 * Application context set by application will be returned to the users in both above callbacks.
 *
 * @param       SqId              Service ID.
 * @param       msgRcvdCb         This callback will be called when a diag packet is received from host.
 * @param       msgSentCb         This callback will be called when diag packet is successfully sent to host.
 * @param       appCxt            Application context.
 *
 * @return      MML_API_SUCCESS_E for success, non-zero for failure.
 */
MmlReturnCodes_t mmlServiceRegisterCb(uint8_t SqId, mmlCb_t msgRcvdCb, mmlCb_t msgSentCb, void *serviceCxt);


/*
 * Use this API to de-register callback functions and application specific context for a given serivice queue ID.
 *
 * @param       SqId              Service ID.
 * @param       appCxt            Application context.
 *
 * @return      MML_API_SUCCESS_E for success, non-zero for failure.
 */
MmlReturnCodes_t mmlServiceDeregisterCb(uint8_t SqId, void *appCxt);


/*
 * API to release buffers received from host.
 * msgRcvdCb callback functions MUST use this API instead of standard library free() API.
 * msgSentCb callback function MUST NOT use this API. 
 * sent packet.
 *
 * @param       SqId              Service ID.
 * @param       Buffer            Buffer to be freed.
 *
 * @return      MML_API_SUCCESS_E for success, non-zero for failure.
 */
MmlReturnCodes_t mmlReleaseBuf(uint8_t SqId, char *Buffer);


#endif /* __TARGET_MML_API_H__ */
#endif /* CONFIG_DAEMON_MODE */


