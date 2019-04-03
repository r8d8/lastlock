/* Copyright (c) 2017 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/* 
 * Copyright (C) 2010--2016 Olaf Bergmann <bergmann@tzi.org>
 * 
 */
/*
 * For this file, which was received with alternative licensing options for  
 * distribution, Qualcomm Technologies, Inc. has selected the BSD license.
 */

#ifndef _QAPI_COAP_H
#define _QAPI_COAP_H

#include "qapi_ssl.h"
#include "qapi_socket.h"

#define QAPI_COAP_TOKEN_MAX_LEN 8
#define QAPI_COAP_BLOCK_MAX_LEN 8

#define QAPI_COAP_DEFAULT_MAX_WAIT_MS 90000
#define QAPI_COAP_DEFAULT_MAX_OBSERVER 30

#define QAPI_NI_MAXSERV 32
#define QAPI_NI_MAXHOST 32
#define QAPI_PATHMAX 32
#define QAPI_INTERFACE_NAME_LEN 8

typedef enum {
    QAPI_COAP_RESP_NONE=0,
    QAPI_COAP_RESP_ACK_ONLY = 0x0001,
    QAPI_COAP_RESP_ACK_DATA=0x0002,
    QAPI_COAP_RESP_ACK_SUBSCRIBE = 0x0004,
    QAPI_COAP_RESP_BLOCK2_MORE = 0x0008,
    QAPI_COAP_RESP_BLOCK2_LAST = 0x0010,
    QAPI_COAP_RESP_BLOCK1_MORE= 0x0020,
    QAPI_COAP_RESP_BLOCK1_LAST = 0x0040,
    QAPI_COAP_RESP_CLIENT_ERROR = 0x0080,
    QAPI_COAP_RESP_SERVER_ERROR = 0x0100,
    QAPI_COAP_RESP_TIMEOUT = 0x0200,
    QAPI_COAP_RESP_NO_MATCH = 0x8000,
}QAPI_COAP_RESP_CODE;

/* CoAP message types */
typedef enum {
        QAPI_COAP_MESSAGE_CON       = 0, /* confirmable message (requires ACK/RST) */
        QAPI_COAP_MESSAGE_NON       = 1 /* non-confirmable message (one-shot message) */
}qapi_Net_Coap_Msg_Type;


typedef enum {
        QAPI_COAP_PROTOCOL_UDP = 0x1,
        QAPI_COAP_PROTOCOL_TCP = 0x2    
}qapi_Net_Coap_Protocol_Type;

typedef enum{
        QAPI_COAP_PARAMETER_FLAG_OPTION  = 1,
        QAPI_COAP_PARAMETER_FLAG_TOKEN   = 2,
        QAPI_COAP_PARAMETER_FLAG_BLOCK   = 3,
        QAPI_COAP_PARAMETER_FLAG_TIMEOUT = 4
}qapi_Net_Coap_Para_Flag;

#define QAPI_COAP_INVALID_TID -1

typedef enum {
    QAPI_A_COAP_ERROR = -1,               /* Generic error return */
    QAPI_A_COAP_OK = 0                  /* success */
} QAPI_A_COAP_STATUS;


/* CoAP request methods */
typedef enum{
        QAPI_COAP_REQUEST_GET       = 1,
        QAPI_COAP_REQUEST_POST      = 2,
        QAPI_COAP_REQUEST_PUT       = 3,
        QAPI_COAP_REQUEST_DELETE    = 4
}qapi_Net_Coap_Request_Method;
    
typedef void qapi_Net_Coap_Context_t;
typedef int qapi_Net_Coap_Tid_t;
typedef unsigned char qapi_Net_Coap_Method_t;
typedef unsigned long qapi_Net_Coap_Tick_t;
typedef void qapi_Net_Coap_Resource_t;

typedef void (*qapi_Net_Coap_Client_CB_t)(void* arg, int32_t state, void* value, int32_t reserved);
/*
typedef enum{
        QAPI_COAP_SERVER_FLAG_UDP      = 0x01,
        QAPI_COAP_SERVER_FLAG_TCP      = 0x02
}qapi_Net_Coap_Server_Flag_Protocol;
*/
typedef enum{
        QAPI_COAP_SERVER_FLAG_IPV4      = 0x01,
        QAPI_COAP_SERVER_FLAG_IPV6      = 0x02
}qapi_Net_Coap_Server_Flag_Ip_Version;


/*** server **/
typedef struct qapi_Net_Coap_Server_Cfg_s{
    char interface_Name[QAPI_INTERFACE_NAME_LEN];
    char port_str[QAPI_NI_MAXSERV];
    unsigned int group_enabled;
    char group_str[QAPI_NI_MAXHOST];
    char cert_file[ QAPI_PATHMAX ];
    qapi_Net_Coap_Server_Flag_Ip_Version v4v6_enabled;
    qapi_Net_Coap_Protocol_Type protocol;
}qapi_Net_Coap_Server_Cfg_t;

///// resource 
typedef struct {
  unsigned int token_length:4; /* length of Token */
  unsigned int type:2;         /* type flag */
  unsigned int version:2;      /* protocol version */
  unsigned int code:8;         /* request method (value 1--10) or response
                                  code (value 40-255) */
  unsigned short id;           /* transaction id (network byte order!) */
  unsigned char token[];       /* the actual token, if any */
} qapi_Net_Coap_Hdr_t;

typedef struct {
  int max_size;          /**< allocated storage for options and data */
  qapi_Net_Coap_Hdr_t *hdr;          /**< Address of the first byte of the CoAP message.
                             *   This may or may not equal (coap_hdr_t*)(pdu+1)
                             *   depending on the memory management
                             *   implementation. */
  unsigned short max_delta; /**< highest option number */
  unsigned short length;    /**< PDU length (including header, options, data) */
  unsigned char *data;      /**< payload */

} qapi_Net_Coap_Pdu_t;

typedef struct {
  int length;    /* length of string */
  unsigned char *s; /* string data */
} qapi_Net_Coap_Str_t;

typedef struct qapi_Net_Coap_Address_s {
  int size;           /**< size of addr */
  union {
    struct sockaddr         sa;
    struct sockaddr_in      sin;
    struct sockaddr_in6     sin6;
  } addr;
} qapi_Net_Coap_Address_t;

typedef unsigned char qapi_Net_Coap_Opt_t;
typedef struct {
  unsigned short delta;
  int length;
  unsigned char *value;
} qapi_Net_Coap_Option_t;

#define QAPI_COAP_OPT_FILTER_SHORT 6
#define QAPI_COAP_OPT_FILTER_LONG  2

#if (QAPI_COAP_OPT_FILTER_SHORT + QAPI_COAP_OPT_FILTER_LONG > 16)
#error QAPI_COAP_OPT_FILTER_SHORT + QAPI_COAP_OPT_FILTER_LONG must be less or equal 16
#endif /* (COAP_OPT_FILTER_SHORT + COAP_OPT_FILTER_LONG > 16) */

#define QAPI_COAP_OPT_FILTER_SIZE					\
  (((QAPI_COAP_OPT_FILTER_SHORT + 1) >> 1) + QAPI_COAP_OPT_FILTER_LONG) +1
typedef uint16_t qapi_Net_Coap_Opt_Filter_t[QAPI_COAP_OPT_FILTER_SIZE];

typedef struct {
  int length;                /**< remaining length of PDU */
  unsigned short type;          /**< decoded option type */
  unsigned int bad:1;           /**< iterator object is ok if not set */
  unsigned int filtered:1;      /**< denotes whether or not filter is used */
  qapi_Net_Coap_Opt_t *next_option;      /**< pointer to the unparsed next option */
  qapi_Net_Coap_Opt_Filter_t filter;     /**< option filter */
} qapi_Net_Coap_Opt_Iterator_t;

typedef void (*qapi_Net_Coap_Method_Handler_t)
  (qapi_Net_Coap_Context_t*,
   qapi_Net_Coap_Resource_t*,
   qapi_Net_Coap_Address_t *,
   qapi_Net_Coap_Pdu_t *,
   qapi_Net_Coap_Str_t * /* token */,
   qapi_Net_Coap_Pdu_t * /* response */);

typedef struct qapi_Net_Coap_Attr_s {
  struct qapi_Net_Coap_Attr_t *next;
  qapi_Net_Coap_Str_t name;
  qapi_Net_Coap_Str_t value;
  int flags;
} qapi_Net_Coap_Attr_t;

typedef struct qapi_Net_Coap_Async_State_s {
  unsigned char flags;  /**< holds the flags to control behaviour */

  /**
   * Holds the internal time when the object was registered with a
   * resource. This field will be updated whenever
   * coap_register_async() is called for a specific resource.
   */
  qapi_Net_Coap_Tick_t created;

  /**
   * This field can be used to register opaque application data with the
   * asynchronous state object.
   */
  void *appdata;
  unsigned short message_id;       /**< id of last message seen */
  qapi_Net_Coap_Tid_t id;                   /**< transaction id */
  struct qapi_Net_Coap_Async_State_t *next; /**< internally used for linking */
  qapi_Net_Coap_Address_t peer;             /**< the peer to notify */
  int tokenlen;                 /**< length of the token */
  unsigned char token[];           /**< the token to use in a response */
} qapi_Net_Coap_Async_State_t;

#define QAPI_COAP_MAX_BLOCK_SZX      4
typedef struct {
  unsigned int num;       /**< block number */
  unsigned int m:1;       /**< 1 if more blocks follow, 0 otherwise */
  unsigned int szx:3;     /**< block size */
} qapi_Net_Coap_Block_t;

#define QAPI_COAP_RESPONSE_CODE(N) (((N)/100 << 5) | (N)%100)



/* CoAP option types (be sure to update check_critical when adding options */

#define QAPI_COAP_OPTION_IF_MATCH        1 /* C, opaque, 0-8 B, (none) */
#define QAPI_COAP_OPTION_URI_HOST        3 /* C, String, 1-255 B, destination address */
#define QAPI_COAP_OPTION_ETAG            4 /* E, opaque, 1-8 B, (none) */
#define QAPI_COAP_OPTION_IF_NONE_MATCH   5 /* empty, 0 B, (none) */
#define QAPI_COAP_OPTION_URI_PORT        7 /* C, uint, 0-2 B, destination port */
#define QAPI_COAP_OPTION_LOCATION_PATH   8 /* E, String, 0-255 B, - */
#define QAPI_COAP_OPTION_URI_PATH       11 /* C, String, 0-255 B, (none) */
#define QAPI_COAP_OPTION_CONTENT_FORMAT 12 /* E, uint, 0-2 B, (none) */
#define QAPI_COAP_OPTION_CONTENT_TYPE QAPI_COAP_OPTION_CONTENT_FORMAT
#define QAPI_COAP_OPTION_MAXAGE         14 /* E, uint, 0--4 B, 60 Seconds */
#define QAPI_COAP_OPTION_URI_QUERY      15 /* C, String, 1-255 B, (none) */
#define QAPI_COAP_OPTION_ACCEPT         17 /* C, uint,   0-2 B, (none) */
#define QAPI_COAP_OPTION_LOCATION_QUERY 20 /* E, String,   0-255 B, (none) */
#define QAPI_COAP_OPTION_PROXY_URI      35 /* C, String, 1-1034 B, (none) */
#define QAPI_COAP_OPTION_PROXY_SCHEME   39 /* C, String, 1-255 B, (none) */
#define QAPI_COAP_OPTION_SIZE1          60 /* E, uint, 0-4 B, (none) */


/* CoAP media type encoding */
#define QAPI_COAP_MEDIATYPE_TEXT_PLAIN                 0 /* text/plain (UTF-8) */
#define QAPI_COAP_MEDIATYPE_APPLICATION_LINK_FORMAT   40 /* application/link-format */
#define QAPI_COAP_MEDIATYPE_APPLICATION_XML           41 /* application/xml */
#define QAPI_COAP_MEDIATYPE_APPLICATION_OCTET_STREAM  42 /* application/octet-stream */
#define QAPI_COAP_MEDIATYPE_APPLICATION_RDF_XML       43 /* application/rdf+xml */
#define QAPI_COAP_MEDIATYPE_APPLICATION_EXI           47 /* application/exi  */
#define QAPI_COAP_MEDIATYPE_APPLICATION_JSON          50 /* application/json  */
#define QAPI_COAP_MEDIATYPE_APPLICATION_CBOR          60 /* application/cbor  */

#define QAPI_COAP_PARAMETER_TYPE_TOKEN_GENERIC        1 
#define QAPI_COAP_PARAMETER_TYPE_BLOCK_GENERIC        2 
#define QAPI_COAP_PARAMETER_TYPE_TIMEOUT_SEND         3 
#define QAPI_COAP_PARAMETER_TYPE_TIMEOUT_OBSERVER       4 


/* CoAP header option numbers */
#define QAPI_COAP_OPTION_OBSERVE  6         /* 0-3 B */
#define QAPI_COAP_OPTION_BLOCK2  23         /* 1-3 B */
#define QAPI_COAP_OPTION_BLOCK1  27         /* 1-3 B */
#define QAPI_COAP_OPTION_SIZE2  28          /* 0-4 B */


#define QAPI_COAP_TICKS_PER_SECOND 1000

typedef enum{
        QAPI_COAP_RESOURCE_FLAGS_RELEASE_URI = 0x1,
        QAPI_COAP_RESOURCE_FLAGS_NOTIFY_NON  = 0x0,
        QAPI_COAP_RESOURCE_FLAGS_NOTIFY_CON  = 0x2
}qapi_Net_Coap_Resource_Flags;

/* Definitions for Async Status Flags These flags can be used to control the
 * behaviour of asynchronous response generation.
 */
#define QAPI_COAP_ASYNC_CONFIRM   0x01  /**< send confirmable response */
#define QAPI_COAP_ASYNC_SEPARATE  0x02  /**< send separate response */
#define QAPI_COAP_ASYNC_OBSERVED  0x04  /**< the resource is being observed */

/**
 * @brief start coap client. 
 *
 * @return
 * 0 successful, none 0 failed.
 */
qapi_Status_t 
qapi_Net_Coap_Client_Start(void);

/**
 * @brief stop coap client. 
 *
 * @return
 * 0 successful, none 0 failed.
 */
qapi_Status_t 
qapi_Net_Coap_Client_Stop(void);

/**
 * @brief create a new coap client context. 
 *
 * @param[in] protocol   UDP or TCP.
 *
 * @param[in] sslCtx     SSL context for client.
 *
 * @param[in] callback   Pointer to the callback function; NULL for no support callback.
 *
 * @param[in] arg        Argument for the callback function.
 *
 *
 * @return
 * On qapi_Net_Coap_Context_t*, handle of coap client context; NULL for error.
 */
qapi_Net_Coap_Context_t*  //flags
qapi_Net_Coap_Client_New_Context(qapi_Net_Coap_Protocol_Type protocol, qapi_Net_SSL_Obj_Hdl_t sslCtx, qapi_Net_Coap_Client_CB_t cb, void* arg);


/**
 * @brief free coap client context. 
 *
 * @param[in] context   coap client context created in qapi_Net_Coap_Client_New_Context.
 *
 * @return
 * 0 successful, none 0 failed.
 */
qapi_Status_t 
qapi_Net_Coap_Client_Free_Context(qapi_Net_Coap_Context_t* context);

/**
 * @brief coap client SSL configurate. 
 *
 * @param[in] ctx         coap client context created in qapi_Net_Coap_Client_New_Context.
 *
 * @param[in] sslCfg      SSL configuation.
 *
 * @return
 * 0 successful, none 0 failed.
 */
qapi_Status_t
qapi_Net_Coap_Client_SSL_Config(qapi_Net_Coap_Context_t* ctx, qapi_Net_SSL_Config_t *sslCfg);


/**
 * @brief connect the coap server. 
 *
 * @param[in] ctx      coap client context created in qapi_Net_Coap_Client_New_Context.
 *
 * @param[in] server   coap server(e.g. 192.168.1.20).
 *
 * @param[in] port     coap server port.
 *
 * @return
 * 0 successful, none 0 failed.
 */
qapi_Status_t 
qapi_Net_Coap_Client_Connect(qapi_Net_Coap_Context_t* ctx, const char* server, uint16_t port);

/**
 * @brief connect the coap server. 
 *
 * @param[in] ctx      coap client context created in qapi_Net_Coap_Client_New_Context.
 *
 * @param[in] flags    indicate Option, Block, Token, Timeout.
 *
 * @param[in] type     indicate type of Option .
 *
 * @param[in] data     setting data.
 *
 * @param[in] length   length of setting data.
 *
 * @return
 * 0 successful, none 0 failed.
 */
qapi_Status_t 
qapi_Net_Coap_Client_Add_Parameter(qapi_Net_Coap_Context_t* ctx, qapi_Net_Coap_Para_Flag flags, unsigned short type, unsigned char *data, unsigned int length );


/**
 * @brief coap client send a message to server. 
 *
 * @param[in] ctx         coap client context created in qapi_Net_Coap_Client_New_Context.
 *
 * @param[in] resource    coap server resource (e.g. /time?ticks).
 *
 * @param[in] req_cfg     client configuration.
 * 
 * @return
 * 0 successful, none 0 failed.
 */                 
qapi_Status_t 
qapi_Net_Coap_Client_Send_Msg(qapi_Net_Coap_Context_t* ctx, 
                                                      const char* uri,
                                                  unsigned char*  payload,
                                                    unsigned int  payload_len,
                                    qapi_Net_Coap_Request_Method  method,
                                          qapi_Net_Coap_Msg_Type  msgtype);


/**
 * @brief init the coap server need to call before qapi_Net_Coap_Server_Start. 
 *
 * @param[in] cfg         coap server configuration.
 *
 * @param[in] sslCtx      SSL context for client.
 *
 * @return
 * On qapi_Net_Coap_Context_t*, handle of coap server context; NULL for error.
 */ 
qapi_Net_Coap_Context_t* 
qapi_Net_Coap_Server_New_Context(qapi_Net_Coap_Server_Cfg_t * cfg, qapi_Net_SSL_Obj_Hdl_t sslCtx );


/**
 * @brief start coap server need to call after qapi_Net_Coap_Server_Init. 
 *
 * @return
 * 0 successful, none 0 failed.
 */
qapi_Status_t 
qapi_Net_Coap_Server_Start(qapi_Net_Coap_Context_t* ctx);


/**
 * @brief stop coap server. 
 *
 * @return
 * 0 successful, none 0 failed.
 */
qapi_Status_t 
qapi_Net_Coap_Server_Stop(qapi_Net_Coap_Context_t* ctx);

/**
 * @brief coap server SSL configurate. 
 *
 * @param[in] ctx         coap client context created in qapi_Net_Coap_Client_New_Context.
 *
 * @param[in] sslCfg      SSL configuation.
 *
 * @return
 * 0 successful, none 0 failed.
 */
qapi_Status_t
qapi_Net_Coap_Server_SSL_Config(qapi_Net_Coap_Context_t* ctx, qapi_Net_SSL_Config_t *sslCfg);

/**
 * @brief init the resource of coap server need. 
 *
 * @param[in] uri         server resource(e.g. time, temperature).
 *
 * @param[in] len         lenght of uri.
 *
 * @param[in] len         server configuration.
 *
 * @return
 * On qapi_Net_Coap_Resource_t*, handle of coap server resource; NULL for error.
 */
qapi_Net_Coap_Resource_t* 
qapi_Net_Coap_Server_Resource_Init(const unsigned char *uri, int len, qapi_Net_Coap_Resource_Flags flags);


/**
 * @brief register resource handler. 
 *
 * @param[in] resource    server resource create in qapi_Net_Coap_Server_Resource_Init.
 *
 * @param[in] method      request methods (GET/PUT/POST/DELETE).
 *
 * @param[in] handler     resource handler.
 *
 * @return
 * 
 */
qapi_Status_t
qapi_Net_Coap_Server_Resource_Register_Handler(qapi_Net_Coap_Resource_t* resource, qapi_Net_Coap_Request_Method method, qapi_Net_Coap_Method_Handler_t handler);

/**
 * @brief add attribute of resource. 
 *
 * @param[in] resource    server resource create in qapi_Net_Coap_Server_Resource_Init.
 *
 * @param[in] name        attribute name (e.g. ct, title).
 *
 * @param[in] nlen        length of name.
 *
 * @param[in] val         value of name(e.g. Ticks) .
 *
 * @param[in] vlen        length of value.
 * 
 * @param[in] flags        length of value.
 *  
 * @return 
 * On qapi_Net_Coap_Resource_t*, handle of coap server resource; NULL for error.
 * 
 */
qapi_Status_t
qapi_Net_Coap_Server_Add_Attr(qapi_Net_Coap_Resource_t* resource, const unsigned char *name, int nlen, const unsigned char *val, int vlen, int flags);



/**
 * @brief add resource to server context. 
 *
 * @param[in] context     server context create in qapi_Net_Coap_Server_Init.
 *
 * @param[in] resource    server resource create in qapi_Net_Coap_Server_Resource_Init.
 *
 *  
 * @return
 * 
 */
qapi_Status_t
qapi_Net_Coap_Server_Add_Resource(qapi_Net_Coap_Context_t* context, qapi_Net_Coap_Resource_t* resource);


/**
 * @brief add option to resource handler response. 
 *
 * @param[in] pdu        handler response.
 *
 * @param[in] type       handler response tyep(e.g. content_type, uri_port).
 *
 * @param[in] len        the length of data.
 *
 * @param[in] data       the details of tyep(e.g. text_plain).
 *
 *  
 * @return
 * 0 successful, none 0 failed
 */
qapi_Status_t
qapi_Net_Coap_Server_Add_Option(qapi_Net_Coap_Pdu_t *pdu, unsigned short type, unsigned int len, const unsigned char *data);

/**
 * @brief add dta to resource handler response. 
 *
 * @param[in] pdu        handler response.
 *
 * @param[in] len        the length of data.
 *
 * @param[in] data       the details of tyep(e.g. text_plain).
 *
 *  
 * @return
 * 0 successful, none 0 failed
 */
qapi_Status_t
qapi_Net_Coap_Server_Add_Data(qapi_Net_Coap_Pdu_t *pdu, unsigned int len, const unsigned char *data);

/**
 * @brief find observer based on client address and token. 
 *
 * @param[in] resource   server resource create in qapi_Net_Coap_Server_Resource_Init.
 *
 * @param[in] peer       client address.
 *
 * @param[in] token      message token.
 *
 *  
 * @return
 */
qapi_Status_t
qapi_Net_Coap_Server_Find_Observer(qapi_Net_Coap_Resource_t* resource, const qapi_Net_Coap_Address_t *peer, const qapi_Net_Coap_Str_t *token);

/**
 * @brief find if pud has this type of option. 
 *
 * @param[in] pdu       pdu to check the option.
 *
 * @param[in] type      option type.
 *
 * @param[in] oi        option iterator.
 *
 *  
 * @return
 * return option if successful, none for failed.
 */
qapi_Net_Coap_Opt_t *
qapi_Net_Coap_Server_Check_Option(qapi_Net_Coap_Pdu_t *pdu, unsigned short type, qapi_Net_Coap_Opt_Iterator_t *oi);


/**
 * @brief get the data of pud . 
 *
 * @param[in] pdu       pdu to check the option.
 *
 * @param[out] len      data length.
 *
 * @param[out] data     data buffer.
 *
 *  
 * @return
 * 0 for successful , none 0 for failed
 */
qapi_Status_t
qapi_Net_Coap_Server_Get_Data(qapi_Net_Coap_Pdu_t *pdu, int *len, unsigned char **data);

/**
 * @brief add block to pdu . 
 *
 * @param[in] pdu          pdu to add block.
 *
 * @param[out] len         block length.
 *
 * @param[out] data        block data.
 *
 * @param[out] block_num   block number.
 *
 * @param[out] block_szx   block size.
 *  
 * @return
 * 0 for successful , none 0 for failed
 */
qapi_Status_t 
qapi_Net_Coap_Server_Add_Block(qapi_Net_Coap_Pdu_t *pdu, unsigned int len, const unsigned char *data, unsigned int block_num, unsigned char block_szx);


/**
 * @brief register separate response. 
 *
 * @param[in] context     server context create in qapi_Net_Coap_Server_Init.
 *
 * @param[in] peer        client address.
 *
 * @param[out] request    request packet from client.
 *
 * @param[out] flags      set separate or confirmed.
 *
 * @param[out] data       delay when sending separate response.
 *  
 * @return
 * 0 for successful , none 0 for failed
 */
qapi_Status_t
qapi_Net_Coap_Server_Register_Async(qapi_Net_Coap_Context_t* context, qapi_Net_Coap_Address_t *peer, qapi_Net_Coap_Pdu_t *request, unsigned char flags, unsigned int delay_ms);

/**
 * @brief set resource can be observered. 
 *
 * @param[in] resource   server resource create in qapi_Net_Coap_Server_Resource_Init.
 *
 * @param[out] value     1 for observer, 0 for non-observer.
 *
 * @return
 * 
 */
qapi_Status_t
qapi_Net_Coap_Server_Resource_Set_Observable(qapi_Net_Coap_Resource_t* resource, int value);

/**
 * @brief set resource dirty. 
 *
 * @param[in] resource   server resource create in qapi_Net_Coap_Server_Resource_Init.
 *
 * @param[out] value     1 dirty, 0 non-dirty.
 *
 * @return
 * 
 */
qapi_Status_t
qapi_Net_Coap_Server_Resource_Set_Dirty(qapi_Net_Coap_Resource_t* resource, int value);

#endif

