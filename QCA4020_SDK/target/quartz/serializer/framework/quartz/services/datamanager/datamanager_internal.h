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

#ifndef __TARGET_DATAMANAGER_INTERNAL_H__
#define __TARGET_DATAMANAGER_INTERNAL_H__

#include <stdint.h>
#include "common.h"
#include "qsPack.h"

#define DM_STACK_SIZE            1024
#define DM_PRIORITY              10

#define CREATE_RESP_EVENT           0x0001
#define DESTROY_RESP_EVENT          0x0002
#define LINK_STATE_RESP_EVENT       0x0004
#define QUERY_PREFIX_RESP_EVENT     0x0008
#define ADD_IP_RESP_EVENT           0x0010
#define DEL_IP_RESP_EVENT           0x0020
#define ADD_ROUTE_RESP_EVENT        0x0040
#define DEL_ROUTE_RESP_EVENT        0x0080
#define ADD_MCAST_RESP_EVENT        0x0100
#define DEL_MCAST_RESP_EVENT        0x0200
#define DEL_PREFIX_MATCH_EVENT      0x0400

#define DM_HEADER_LEN            6 /* 1 byte command ID, 1 byte reserved, 4 bytes interface ID */
#define DM_TOTAL_LEN(x)          ((x) + DM_HEADER_LEN)
#define DM_MAC_LENGTH            0x06
#define DM_IPV6_ADDRESS_LENGTH   16
#define DM_IPV6_PREFIX_LENGTH    8

#define DM_CMDID(_x)             (((uint8_t *)(_x))[0])
#define DM_RESP(_x)              ((_x) + DM_HEADER_LEN)

#define QS_IOTD_MAX_DATA_INTERFACE  5
#define IFNAME_MAX_LENGTH           16

/* Types of data messages */
typedef enum {
    DM_INTERFACE_CREATE_REQ,
    DM_INTERFACE_CREATE_RESP,
    DM_INTERFACE_DESTROY_REQ,
    DM_INTERFACE_DESTROY_RESP,
    DM_INTERFACE_LINK_STATE_REQ,
    DM_INTERFACE_LINK_STATE_RESP,
    DM_INTERFACE_QUERY_PREFIX_REQ,
    DM_INTERFACE_QUERY_PREFIX_RESP,
    DM_INTERFACE_DATA,
    DM_INTERFACE_ADD_IP,         /*Add IPv6 address to interface*/
    DM_INTERFACE_DEL_IP,         /*Delete IPv6 address from interface*/
    DM_INTERFACE_ADD_MCAST,      /*Subscribe to Multicast group*/
    DM_INTERFACE_DEL_MCAST,      /*Remove all mcast subscriptions*/
    DM_INTERFACE_ADD_ROUTE,      /*Add route to interface*/
    DM_INTERFACE_DEL_ROUTE,      /*Remove all routes from interface*/
	DM_INTERFACE_PREFIX_MATCH,   /*Find longest prefix match*/
} DmMsgTypes_e;


/* Return values of data manager APIs */
typedef enum {
    DM_SUCCESS_E,
    DM_FAILURE_E,
    DM_UNKNOWN_CMD_E,
    DM_INVALID_PARAMETER_E,
    DM_INVALID_LENGTH_E,
    DM_MEMORY_ERROR_E,
    DM_CREATE_IF_IN_PROGRESS_E, /* Interface creation already in progress */
    DM_CMD_IN_PROGRESS_E,       /* A command for same interface already in progress */
} DmReturnCodes_e;


/* Types of interface - used for DmIfInitReq_s*/
typedef enum {
    DM_IF_TAP, /* TAP interface */
    DM_IF_TUN  /* TUN interface */
} DmIfTypes_e;


/* Link states - used for DmLinkStateReq_t */
typedef enum {
    DM_LINK_DOWN, /* Used to set the interface down */
    DM_LINK_UP    /* Used to set the interface up */
} DmLinkState_e;

/* Callback used for data received on an interface.
 * @param         PayloadLen      Length of payload.
 * @param         Payload         Payload.
 */
typedef void (* DMCallback_t)(uint16_t PayloadLen, void *Payload);


/* Data interface context */
typedef struct dataIfCxt_s {
    uint8_t       cmdInProgess; /* Set when a command on interface is awaiting response */
    uint8_t       inUse;        /* Indicates if an interface is in use */
    uint8_t       type;         /* Type- TUN or TAP*/
    uint8_t       nameLen;      /* Length of interface name string */
    uint32_t      ifId;         /* ID assigned when interface is created*/
    DMCallback_t  cb;           /* Callback function of data received on the interface */
    char          name[IFNAME_MAX_LENGTH]; /* Interface name string */
    qurt_signal_t signal;       /* Signal for data agent Rx thread and the thread blocked for command response */
    queue_t rxQueue; /* Queue to received incoming commands and packets */
} dataIfCxt_t;


/* Data manager context */
typedef struct dataMgrCxt_s {
    int8_t createInProgress; /* Set to index for which interface creation is in progress. Set to -1 when completed */
    qurt_thread_t rxThread;  /* Data Mgr command handler thread*/
    qurt_mutex_t mutex;      /* Mutex for atomic operations on data manager context */
    qurt_signal_t signal;    /* Signal for synchronization between MML and data agent */
    dataIfCxt_t interfaces[QS_IOTD_MAX_DATA_INTERFACE]; /* Interface entries */
} dataMgrCxt_t;


/* Packed structure for data message header sent between host and target */
typedef PACKED struct DmHeader_s {
    uint8_t CmdId;    /* Command ID of type DmMsgTypes_e */
    uint8_t Reserved; /* Reserved for future use */
    uint32_t IfId;    /* Interface ID (set when interface is created) */
} PACKED_END DmHeader_t;


/* Structure used for sending interface init command to host */
typedef PACKED struct DmIfInitReq_s {
    DmHeader_t Header;               /* Command header */
    uint8_t IfType;                  /* DmIfTypes_e */
    uint8_t Mac[DM_MAC_LENGTH];      /* MAC address used only for TAP interface */
    uint8_t NameLen;                 /* Length of inteface name */
    uint8_t Name[IFNAME_MAX_LENGTH]; /* Interface name. */
    DMCallback_t Cb;                 /* Callback for data received on interface (if command succeeds) */
} PACKED_END DmIfInitReq_t;
#define DM_IFINITREQ_T_SIZE(_x)    (8 + (_x))


/* Structure used for sending interface destroy command to host */
typedef PACKED struct DmIfDestroyReq_s {
    DmHeader_t Header; /* Command header */
} PACKED_END DmIfDestroyReq_t;
#define DM_IFDESTROYREQ_T_SIZE     (sizeof(DmIfDestroyReq_t))


/* Structure used for sending data related commands to host */
typedef PACKED struct DmLinkStateReq_s {
    DmHeader_t Header; /* Command header */
    uint8_t State;     /* Link state of type DmLinkState_e */
} PACKED_END DmLinkStateReq_t;
#define DM_LINKSTATEREQ_T_SIZE     (sizeof(DmLinkStateReq_t))


/* Structure used for sending prefix query request to host */
typedef PACKED struct DmPrefixQueryReq_s {
    DmHeader_t Header; /* Command header */
} PACKED_END DmPrefixQueryReq_t;
#define DM_PREFIXQUERYREQ_T_SIZE   (sizeof(DmPrefixQueryReq_t))


typedef PACKED struct DmIPv6AddrInfo_s {
    uint8_t Address[DM_IPV6_ADDRESS_LENGTH]; /* IPV6 address */
} PACKED_END DmIPv6AddrInfo_t;

typedef PACKED struct DmPrefixInfo_s {
    uint32_t PrefixLength;      /* Prefix length */
    DmIPv6AddrInfo_t Prefix;    /* Prefix address */
    uint32_t ValidLifetime;     /* Valid lifetime */
    uint32_t PreferredLifetime; /* Preferred lifetime */
    uint32_t Flags;             /* Flag */
} PACKED_END DmPrefixInfo_t;
#define DM_PREFIXINFO_T_SIZE   (sizeof(DmPrefixInfo_t))

/* Structure used for receiving prefix query response from host */
typedef PACKED struct DmPrefixQueryResp_s {
    uint8_t Status;       /* Response */
    uint8_t NumPrefix;    /* Number of prefixes */
    DmPrefixInfo_t *Info; /* Prefixes. Datamanager will allocate memory for this member, sender of requeust should
                             free the memory when response is received */
} PACKED_END DmPrefixQueryResp_t;

/* Structure used for sending/receiving data to/from host*/
typedef PACKED struct DmData_s {
    DmHeader_t Header; /* Command header */
    uint16_t Len;      /* Payload length */
    char Payload[1];   /* Payload. Caller should allocate extra memory required for the data. */
} PACKED_END DmData_t;
#define DM_DATA_T_SIZE(_x) (sizeof(DmData_t) - 1 + ((DmData_t *)_x)->Len)

typedef PACKED struct DmAddIPAddress_s {
    DmHeader_t Header; /* Command header */
    DmIPv6AddrInfo_t IpAddress;   /*IPv6 address to add to the interface*/
    uint32_t PrefixLen;           /*Prefix length*/
} PACKED_END DmAddIPAddress_t;

typedef PACKED struct DmDelIPAddress_s {
    DmHeader_t Header; /* Command header */
} PACKED_END DmDelIPAddress_t;

typedef PACKED struct DmAddRoute_s {
    DmHeader_t Header;      /* Command header */
    DmIPv6AddrInfo_t Route; /*IPv6 route to add to the interface*/
    uint32_t PrefixLen;     /*Prefix length*/
} PACKED_END DmAddRoute_t;

typedef PACKED struct DmDelRoute_s {
    DmHeader_t Header; /* Command header */
} PACKED_END DmDelRoute_t;

typedef PACKED struct DmAddMcast_s {
    DmHeader_t Header; /* Command header */
    DmIPv6AddrInfo_t Mcast;   /*IPv6 Multicast address to add to the interface*/	
} PACKED_END DmAddMcast_t;

typedef PACKED struct DmDelMcast_s {
    DmHeader_t Header; /* Command header */
} PACKED_END DmDelMcast_t;

typedef PACKED struct DmPrefixMatch_s {
    DmHeader_t Header; /* Command header */
	DmIPv6AddrInfo_t ipAddr; /*IPv6 addr for prefix matching*/
} PACKED_END DmPrefixMatch_t;

typedef PACKED struct DmPrefixMatchResp_s {
    uint8_t Status; /* Response status*/
	uint32_t matchLen; /*Number of matching bits*/
} PACKED_END DmPrefixMatchResp_t;

/*
 * Initialize data manager context.
 *
 * @param       Cxt       Pointers to the common context.
 */
uint32_t DMInit(void *Cxt);


/*
 * Deinitialize data manager context.
 *
 * @param       Cxt       Pointers to the common context.
 */
void DMDeInit(void *Cxt);


/*
 * Send given command to host.
 * This API waits until the response is received, hence calling thread will be blocked.
 *
 * Caller is responsible to allocate and free the memory for 'Input' argument.
 *
 * This API returns the command response from host as return value, any other data required by the caller should use
 * 'Output' pointers to retrive the data depending on the command types, see the note below for more details.
 * If there are any pointers in the response strucutre, API will allocate required memory and caller will be
 * responsible of freeing this memory, example DmPrefixQueryResp_t, caller must free the memory for 'Info' member.
 *
 * When one 'interface creation' is in progress, no other interface can be created until the first command completes.
 * If another interface creation command is given, DM_CREATE_IF_IN_PROGRESS will be returned to the caller.
 * Caller should decide to sleep for some time and try again or abort the operation.
 *
 * Similarly, on any given interface, only one command can be in progress at a time. If another command is given before
 * the first completes, DM_CMD_IN_PROGRESS will be returned to the caller.
 *
 * @param[in]       SqId       Service ID: BLE_DATA_SQ_ID, WLAN_DATA_SQ_ID, THREAD_DATA_SQ_ID.
 * @param[in]       Input      Data for the requested command, see note.
 * @param[in,out]   Output     Pointer to retrive response data from host (except the return value), see note.
 *
 *
 * @return      Response from the host will be returned to the caller of this API.
 *
 *
 * @note
 * Following are the types to be used by callers for each command type:
 * --------------------------------------------------------------------------------------------------------------------
 *      Command type                           Input                       Output
 * --------------------------------------------------------------------------------------------------------------------
 *      DM_INTERFACE_CREATE_REQ                DmIfInitReq_t*              uint32_t*
 *      DM_INTERFACE_DESTROY_REQ               DmIfDestroyReq_t*           NULL (Ignored)
 *      DM_INTERFACE_LINK_STATE_REQ            DmLinkStateReq_t*           NULL (Ignored)
 *      DM_INTERFACE_QUERY_PREFIX_REQ          DmPrefixQueryReq_t*         DmPrefixQueryResp_t*
 *      DM_INTERFACE_DATA                      DmData_t*                   NULL (Ignored)
 *
 */
uint32_t DMSendCmd(uint8_t SqId, const void *Input, void *Output);

#endif /* __TARGET_DATAMANAGER_INTERNAL_H__ */
#endif /* CONFIG_DAEMON_MODE */

