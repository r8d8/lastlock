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

#include <stdlib.h>
#include "mml_api.h"
#include "qurt_error.h"
#include "qurt_thread.h"
#include "qurt_timer.h"
#include "pal.h"

#define STACK            1024
#define PRIORITY         10

#ifdef CONFIG_TARGET_DATAMGR
#include "datamanager_internal.h"
#endif

#ifdef DIAG_SEND_TEST
#include "qapi_diag_mml_if.h"
#include "qapi/qapi.h"
#include "qapi_diag_msg.h"
qapi_diag_tr_service_context_t diag_tr_service_ctx;
#endif /* #ifdef DIAG_SEND_TEST */

#ifdef DATAPATH_TEST
void DataPathTestCb(uint16_t len, void *arg)
{
    return;
}

static void DataTestThread(void *Param)
{
    DmIfInitReq_t InitReq;
    DmLinkStateReq_t LinkStateReq;
    DmPrefixQueryReq_t PrefixReq;
    DmPrefixQueryResp_t PrefixResp;
    DmIfDestroyReq_t DestroyReq;
    DmAddIPAddress_t IPAddReq;
    DmDelIPAddress_t IPDelReq;
    DmAddRoute_t RouteAddReq;
    DmDelRoute_t RouteDelReq;
    DmAddMcast_t McastAddReq;
    DmDelMcast_t McastDelReq;
	DmPrefixMatch_t PrefixMatchReq;
	DmPrefixMatchResp_t PrefixMatchResp;
    char *ifname = "IF0";
    uint32_t ifId = 0;
    uint8_t mac[6] = {0x00,0x15,0x58,0x2e,0x65,0x62};
    uint8_t ip[16] = {0x20,0x0d,0x01,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a};
    uint8_t route[16] = {0x20,0x02,0x0d,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01};
    uint8_t group[16] = {0xff,0x02,0x01,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a};
	uint8_t ipAddr[16] = {0x20,0x0d,0x11,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfc};
    uint32_t dataTest_Ret_Val = 0;

    qurt_thread_sleep(qurt_timer_convert_time_to_ticks(1000,QURT_TIME_MSEC));

    /* Create interface InitReq */
    memset(&InitReq, 0, sizeof(InitReq));
    InitReq.Header.CmdId = DM_INTERFACE_CREATE_REQ;
    InitReq.IfType = DM_IF_TUN;
    memcpy(InitReq.Mac, mac, DM_MAC_LENGTH);
    InitReq.NameLen = strlen(ifname)+1;
    memcpy(InitReq.Name, ifname, InitReq.NameLen);
    InitReq.Cb = DataPathTestCb;
    dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &InitReq, &ifId);

    /* Linkstate set */
    if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&LinkStateReq, 0, sizeof(LinkStateReq));
        LinkStateReq.Header.CmdId = DM_INTERFACE_LINK_STATE_REQ;
        LinkStateReq.Header.IfId = ifId;
        LinkStateReq.State = DM_LINK_UP;
        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &LinkStateReq, NULL);
    }

    /* Destroy interface */
    if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&PrefixReq, 0, sizeof(PrefixReq));
        PrefixReq.Header.CmdId = DM_INTERFACE_QUERY_PREFIX_REQ;
        PrefixReq.Header.IfId = ifId;
        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &PrefixReq, &PrefixResp);
        if(PrefixResp.Info)
            free(PrefixResp.Info);
    }

    if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&IPAddReq, 0, sizeof(DmAddIPAddress_t));
        IPAddReq.Header.CmdId = DM_INTERFACE_ADD_IP;
        IPAddReq.Header.IfId = ifId;
        memcpy(IPAddReq.IpAddress.Address, ip, 16);
        IPAddReq.PrefixLen = 64;
        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &IPAddReq, NULL);
    }

    if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&RouteAddReq, 0, sizeof(DmAddRoute_t));
        RouteAddReq.Header.CmdId = DM_INTERFACE_ADD_ROUTE;
        RouteAddReq.Header.IfId = ifId;
        memcpy((RouteAddReq.Route.Address), route, 16);
        RouteAddReq.PrefixLen = 64;
        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &RouteAddReq, NULL);
    }

    if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&McastAddReq, 0, sizeof(DmAddMcast_t));
        McastAddReq.Header.CmdId = DM_INTERFACE_ADD_MCAST;
        McastAddReq.Header.IfId = ifId;
        memcpy(&(McastAddReq.Mcast.Address), group, 16);

        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &McastAddReq, NULL);
    }

	if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&PrefixMatchReq, 0, sizeof(DmPrefixMatch_t));
        PrefixMatchReq.Header.CmdId = DM_INTERFACE_PREFIX_MATCH;
        PrefixMatchReq.Header.IfId = ifId;
		memcpy(&(PrefixMatchReq.ipAddr.Address), ipAddr, 16);
        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &PrefixMatchReq, &PrefixMatchResp);
    }
	
    qurt_thread_sleep(qurt_timer_convert_time_to_ticks(3000,QURT_TIME_MSEC));
    if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&McastDelReq, 0, sizeof(DmDelMcast_t));
        McastDelReq.Header.CmdId = DM_INTERFACE_DEL_MCAST;
        McastDelReq.Header.IfId = ifId;

        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &McastDelReq, NULL);
    }

    qurt_thread_sleep(qurt_timer_convert_time_to_ticks(1000,QURT_TIME_MSEC));
    if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&RouteDelReq, 0, sizeof(DmDelRoute_t));
        RouteDelReq.Header.CmdId = DM_INTERFACE_DEL_ROUTE;
        RouteDelReq.Header.IfId = ifId;

        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &RouteDelReq, NULL);
    }

    qurt_thread_sleep(qurt_timer_convert_time_to_ticks(1000,QURT_TIME_MSEC));
    if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&IPDelReq, 0, sizeof(DmDelIPAddress_t));
        IPDelReq.Header.CmdId = DM_INTERFACE_DEL_IP;
        IPDelReq.Header.IfId = ifId;

        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &IPDelReq, NULL);
    }
    /* Destroy interface */
    if(ssSuccess == dataTest_Ret_Val)
    {
        memset(&DestroyReq, 0, sizeof(DestroyReq));
        DestroyReq.Header.CmdId = DM_INTERFACE_DESTROY_REQ;
        DestroyReq.Header.IfId = ifId;
        dataTest_Ret_Val = DMSendCmd(BLE_DATA_SQ_ID, &DestroyReq, NULL);
    }

    qurt_thread_stop();
}

uint32_t data_unit_test()
{
            qurt_thread_attr_t attr1;
            qurt_thread_t handle1;
            int result1 = -1;
            qurt_thread_attr_init(&attr1);
            qurt_thread_attr_set_name(&attr1, "DATATEST");
            qurt_thread_attr_set_priority(&attr1, PRIORITY);
            qurt_thread_attr_set_stack_size(&attr1, STACK);
            result1 = qurt_thread_create(&handle1, &attr1, DataTestThread, NULL);
            if (QURT_EOK != result1)
            {
                return 1;
            }
    return 0;
}
#endif /* DATAPATH_TEST */


#if defined(DIAG_RCV_TEST) || defined(DIAG_SEND_TEST)

#ifndef DIAG_INIT_COLD
void DiagTestMsgRcvCb(uint8_t SqId, uint16_t bufLen, char *buf, void *serviceCxt, void *serviceData)
{
    uint16_t totalLen = bufLen + TOTAL_HEADER_LEN;
    char *sendBuf = (char *)malloc(totalLen);
    memset(sendBuf, 0, totalLen);

    memcpy(&sendBuf[TOTAL_HEADER_LEN], buf, bufLen);
    mmlReleaseBuf(SqId, buf);

    if(MML_SUCCESS_E != mmlServiceQueueSend(SqId, bufLen+TOTAL_HEADER_LEN, sendBuf, NULL))
    {
        /* Free the buffer in case of error */
        free(sendBuf);
        return;
    }
    return;
}
#endif /* DIAG_INIT_COLD  */

void DiagTestMsgSentCb(uint8_t SqId, uint16_t bufLen, char *buf, void *serviceCxt, void *serviceData)
{
    free(buf);
    return;
}

static void DiagTestThread(void *Param)
{
//    qurt_thread_sleep(qurt_timer_convert_time_to_ticks(1000,QURT_TIME_MSEC));

#ifdef DIAG_RCV_TEST
#ifndef DIAG_INIT_COLD
    /* Register for MML queue. */
    (void)mmlServiceRegisterCb(MML_DIAG_SQ_ID, DiagTestMsgRcvCb, DiagTestMsgSentCb, NULL);
#endif /* DIAG_INIT_COLD */
#endif /* #ifdef DIAG_RCV_TEST */

#ifdef DIAG_SEND_TEST
    qurt_thread_sleep(qurt_timer_convert_time_to_ticks(1,QURT_TIME_MSEC));

    QAPI_DIAG_MSG_ARG0(QAPI_DIAG_MSG_SYSBUF_HDL, 0, QAPI_DIAG_MSG_LVL_MED, \
                        "Log-1\n");
    QAPI_DIAG_MSG_ARG0(QAPI_DIAG_MSG_SYSBUF_HDL, 0, QAPI_DIAG_MSG_LVL_MED, \
                        "Log-2\n");
    QAPI_DIAG_MSG_ARG0(QAPI_DIAG_MSG_SYSBUF_HDL, 0, QAPI_DIAG_MSG_LVL_MED, \
                        "Log-3\n");
    QAPI_DIAG_MSG_ARG0(QAPI_DIAG_MSG_SYSBUF_HDL, 0, QAPI_DIAG_MSG_LVL_MED, \
                        "Logging done\n");
#endif /* DIAG_SEND_TEST */

    qurt_thread_stop();
}

uint32_t diag_unit_test()
{
    qurt_thread_attr_t attr2;
    qurt_thread_t handle2;
    int result2 = -1;
    qurt_thread_attr_init(&attr2);
    qurt_thread_attr_set_name(&attr2, "DIAGTEST");
    qurt_thread_attr_set_priority(&attr2, PRIORITY);
    qurt_thread_attr_set_stack_size(&attr2, STACK);
    result2 = qurt_thread_create(&handle2, &attr2, DiagTestThread, NULL);
    if (QURT_EOK != result2)
    {
        return 1;
    }
    return 0;
}
#endif /* defined(DIAG_RCV_TEST) || defined(DIAG_SEND_TEST) */


