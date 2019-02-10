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

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "qapi_status.h"
#include "coap_demo.h"
#include "bench.h"
#include "qapi_netservices.h"
#include "qapi_socket.h"
#include "qapi_ns_gen_v4.h"
#include "qapi_ns_gen_v6.h"
#include "qapi_coap.h"
#include "qurt_thread.h"
#include "qurt_timer.h"
#include "qurt_error.h"
#include "bench.h"

extern QCLI_Group_Handle_t qcli_net_handle;

#define COAP_PRINTF(...) QCLI_Printf(qcli_net_handle, __VA_ARGS__)

#define MAX_COAP_PDU_LENGTH                                  256
#define QAPI_COAP_PAYLOAD_START                              0xFF
#define MAX_PRINTF_LENGTH                                    256
#define isdigit(c)  ( (((c) >= '0') && ((c) <= '9')) ? (1) : (0) )



/*************************
  ****COAP SERVER DEMO****
  *************************/

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

static time_t clock_offset;
static time_t my_clock_base = 0;


#define COAP_CLIENT_CONTEXT_MAX  4
typedef struct coap_demo_client_s{ 
    uint32_t                idx;
    qapi_Net_Coap_Protocol_Type proto_type;
    qbool_t                 security;
    qapi_Net_Coap_Context_t* ctx; 
	qapi_Net_SSL_Obj_Hdl_t sslCtx;
    qapi_Net_SSL_Config_t *sslCfg;    
}coap_demo_client_t;
coap_demo_client_t *coap_client[COAP_CLIENT_CONTEXT_MAX] = {0};
qbool_t client_demo_started = FALSE;

typedef struct coap_demo_server_t{    
    qapi_Net_Coap_Context_t* ctx;
    qapi_Net_Coap_Server_Cfg_t* req_cfg; 
	qapi_Net_SSL_Obj_Hdl_t sslCtx;
    qapi_Net_SSL_Config_t *sslCfg; 
}coap_demo_server_t;
coap_demo_server_t *coap_server;


typedef struct {
  unsigned char code;
  char *media_type;
} content_type_t;


static void coap_client_help(void)
{
    COAP_PRINTF("coap-client <index> <udp/tcp> [-b [num,]size] [-B seconds] \n");
    COAP_PRINTF("[-e text] [-m method] [-N] \n");
    COAP_PRINTF("[-s duration] [-v ipv4/ipv6] URI\n");
    COAP_PRINTF("    index            1-4 client index\n");
    COAP_PRINTF("    URI              can be an absolute or relative coap URI,\n");
    COAP_PRINTF("    -b [num, size]  block size to be used in GET/PUT/POST requests\n");
    COAP_PRINTF("                    (value must be a multiple of 16 not larger than 1024)\n");
    COAP_PRINTF("                    If num is present, the request chain will start at\n");
    COAP_PRINTF("                    block num\n");
    COAP_PRINTF("    -B seconds      break operation after waiting given seconds(default is 90)\n");          
    COAP_PRINTF("    -e text         include text as payload (use percent-encoding for\n");
    COAP_PRINTF("                    non-ASCII characters)\n");
    COAP_PRINTF("    -m method       request method (get|put|post|delete), default is 'get'\n");
    COAP_PRINTF("    -N              send NON-confirmable message\n");
    COAP_PRINTF("    -s duration     subscribe for given duration [s]\n");
    COAP_PRINTF("    -t type         content type\n");
    COAP_PRINTF("    -T token        include specified token\n");
    COAP_PRINTF("example:\n");
    COAP_PRINTF("   coap client udp 0 -m get coap://192.168.1.100/\n");
    COAP_PRINTF("   coap client udp 0 -m get coap://[2001::1]/\n");
    COAP_PRINTF("   coap client tcp 1 -m get /time?ticks\n");
#ifdef CONFIG_NET_SSL_DEMO
	sslconfig_help("coap client index sslconfig");
#endif    
}
static void coap_server_help(void)
{
    COAP_PRINTF(" coap_server <udp/tcp/dual>   -v v4  -p 443\n");
    COAP_PRINTF("    -v v4/v6/v4v6   support ipv4/ipv6\n");
    COAP_PRINTF("    -c cert.bin     certificate\n");
    COAP_PRINTF("    -i interface    interface wlan0/wlan1\n");    
    COAP_PRINTF("example:\n");
    COAP_PRINTF("   coap server udp  -v v4 -c cert.bin -p 443\n");
    COAP_PRINTF("   coap server tcp  -v v4v6\n");
#ifdef CONFIG_NET_SSL_DEMO
	sslconfig_help("coap server sslconfig");
#endif     
}


int
demo_coap_split_uri(unsigned char *str_var, int len, unsigned int *port, char* server, int* server_len, unsigned char* security, char* query, int* query_len) {
  unsigned char *p, *q;
  int secure = 0, res = 0;

  if (!str_var )
    return -1;

  *port = 5683;

  /* search for scheme */
  p = str_var;
  if (*p == '/') {
    q = p;
    goto path;
  }

  q = (unsigned char *)"coap";
  while (len && *q && (*p) == *q) {
    ++p; ++q; --len;
  }
  
  /* If q does not point to the string end marker '\0', the schema
   * identifier is wrong. */
  if (*q) {
    res = -1;
    goto error;
  }

  /* There might be an additional 's', indicating the secure version: */
  if (len && (secure = (*p) == 's')) {
    ++p; --len;
    *port = 5684;
    *security = 1;
  } else {
    *security = 0;
  }

  q = (unsigned char *)"://";
  while (len && *q && (*p) == *q) {
    ++p; ++q; --len;
  }

  if (*q) {
    res = -2;
    goto error;
  }

  /* p points to beginning of Uri-Host */
  q = p;
  if (len && *p == '[') {	/* IPv6 address reference */
    ++p;
    
    while (len && *q != ']') {
      ++q; --len;
    }

    if (!len || *q != ']' || p == q) {
      res = -3;
      goto error;
    } 

    strncpy(server, (char*)p, q-p);
    server[q - p] = '\0';
    *server_len = q-p;
    ++q; --len;
  } else {			/* IPv4 address or FQDN */
    while (len && *q != ':' && *q != '/' && *q != '?') {
      *q = (*q);
      ++q;
      --len;
    }

    if (p == q) {
      res = -3;
      goto error;
    }
    strncpy(server, (char*)p, q-p);
    *server_len = q-p;
    server[q - p] = '\0';
  }

  /* check for Uri-Port */
  if (len && *q == ':') {
    p = ++q;
    --len;
    
    while (len && isdigit(*q)) {
      ++q;
      --len;
    }

    if (p < q) {		/* explicit port number given */
      int uri_port = 0;
    
      while (p < q)
	uri_port = uri_port * 10 + (*p++ - '0');

      /* check if port number is in allowed range */
      if (uri_port > 65535) {
	res = -4;
	goto error;
      }
      *port = uri_port;
    } 
  }
  
 path:		 /* at this point, p must point to an absolute path */

  if (!len)
    goto end;

  if (len && *q == '/') {
   p = q;
   strncpy(query, (char*)p,len);
   *query_len = len;
   query[len] = '\0';
    len = 0;
  }

  end:
  return len ? -1 : 0;
  
  error:
  return res;
}



unsigned char *
demo_coap_opt_value(unsigned char  *opt) {
  int ofs = 1;

  switch (*opt & 0xf0) {
  case 0xf0:
//    debug("illegal option delta\n");
    return 0;
  case 0xe0:
    ++ofs;
    /* fall through */
  case 0xd0:
    ++ofs;
    break;
  default:
    ;
  }

  switch (*opt & 0x0f) {
  case 0x0f:
//    debug("illegal option length\n");
    return 0;
  case 0x0e:
    ++ofs;
    /* fall through */
  case 0x0d:
    ++ofs;
    break;
  default:
    ;
  }

  return (unsigned char *)opt + ofs;
}
unsigned short
demo_coap_opt_length(const unsigned char  *opt) {
  unsigned short length;

  length = *opt & 0x0f;
  switch (*opt & 0xf0) {
  case 0xf0:
 //   debug("illegal option delta\n");
    return 0;
  case 0xe0:
    ++opt;
    /* fall through to skip another byte */
  case 0xd0:
    ++opt;
    /* fall through to skip another byte */
  default:
    ++opt;
  }

  switch (length) {
  case 0x0f:
  //  debug("illegal option length\n");
    return 0;
  case 0x0e:
    length = (*opt++ << 8) + 269;
    /* fall through */
  case 0x0d:
    length += *opt++;
    break;
  default:
    ;
  }
  return length;
}
//unsigned char *coap_opt_value(coap_opt_t *opt);
#define DEMO_COAP_OPT_VALUE(opt) demo_coap_opt_value((unsigned char *)opt)
#define DEMO_COAP_OPT_LENGTH(opt) demo_coap_opt_length(opt)

int demo_coap_fls(unsigned int i) {
  int n;
  for (n = 0; i; n++)
    i >>= 1;
  return n;
}
unsigned int
demo_coap_decode_var_bytes(unsigned char *buf,unsigned int len) {
  unsigned int i, n = 0;
  for (i = 0; i < len; ++i)
    n = (n << 8) + buf[i];

  return n;
}

unsigned int
demo_coap_encode_var_bytes(unsigned char *buf, unsigned int val) {
  unsigned int n, i;

  for (n = 0, i = val; i && n < sizeof(val); ++n)
    i >>= 8;

  i = n;
  while (i--) {
    buf[i] = val & 0xff;
    val >>= 8;
  }

  return n;
}

#define DEMO_COAP_OPT_BLOCK_LAST(opt) \
  (DEMO_COAP_OPT_LENGTH(opt) ? (DEMO_COAP_OPT_VALUE(opt) + (DEMO_COAP_OPT_LENGTH(opt)-1)) : 0)

/** Returns the value of the More-bit of a Block option @p opt. */
#define DEMO_COAP_OPT_BLOCK_MORE(opt) \
  (DEMO_COAP_OPT_LENGTH(opt) ? (*DEMO_COAP_OPT_BLOCK_LAST(opt) & 0x08) : 0)

/** Returns the value of the SZX-field of a Block option @p opt. */
#define DEMO_COAP_OPT_BLOCK_SZX(opt)  \
  (DEMO_COAP_OPT_LENGTH(opt) ? (*DEMO_COAP_OPT_BLOCK_LAST(opt) & 0x07) : 0)

unsigned int demo_coap_opt_block_num(const qapi_Net_Coap_Opt_t *block_opt);
/** Returns the value of the num of a Block option @p opt. */
#define DEMO_COAP_OPT_BLOCK_NUM(opt) \
      demo_coap_opt_block_num(opt)


unsigned int
demo_coap_opt_block_num(const unsigned char *block_opt) {
  unsigned int num = 0;
  unsigned short len;
  
  len = demo_coap_opt_length(block_opt);

  if (len == 0) {
    return 0;
  }
  
  if (len > 1) {
    num = demo_coap_decode_var_bytes(DEMO_COAP_OPT_VALUE(block_opt), 
				DEMO_COAP_OPT_LENGTH(block_opt) - 1);
  }
  
  return (num << 4) | ((*DEMO_COAP_OPT_BLOCK_LAST(block_opt) & 0xF0) >> 4);
}

int
demo_cmdline_blocksize(char *arg, unsigned int* num, unsigned int* szx) {
  unsigned short size;

again:
  size = 0;
  while(*arg && *arg != ',')
    size = size * 10 + (*arg++ - '0');

  if (*arg == ',') {
    arg++;
    *num = size;
    goto again;
  }

  if (size)
    *szx = (demo_coap_fls(size >> 4) - 1) & 0x07;

  return 0;
}


#define INDEX "This is a test server made with libcoap!"

static void
hnd_get_index(qapi_Net_Coap_Context_t* ctx,
              qapi_Net_Coap_Resource_t* resource,
              qapi_Net_Coap_Address_t *peer,
              qapi_Net_Coap_Pdu_t *request,
              qapi_Net_Coap_Str_t *token,
              qapi_Net_Coap_Pdu_t *response) {
  unsigned char buf[3];

  response->hdr->code = QAPI_COAP_RESPONSE_CODE(205); 
  qapi_Net_Coap_Server_Add_Option(response,
                  QAPI_COAP_OPTION_CONTENT_TYPE,
                  demo_coap_encode_var_bytes(buf, QAPI_COAP_MEDIATYPE_TEXT_PLAIN), buf); 
  qapi_Net_Coap_Server_Add_Option(response,
                  QAPI_COAP_OPTION_MAXAGE,
                  demo_coap_encode_var_bytes(buf, 0x2ffff), buf);
  qapi_Net_Coap_Server_Add_Data(response, strlen(INDEX), (unsigned char *)INDEX); 
}

static void
hnd_get_time(qapi_Net_Coap_Context_t*  ctx,
             qapi_Net_Coap_Resource_t* resource,
             qapi_Net_Coap_Address_t *peer,
             qapi_Net_Coap_Pdu_t *request,
             qapi_Net_Coap_Str_t *token,
             qapi_Net_Coap_Pdu_t *response) {
  qapi_Net_Coap_Opt_Iterator_t opt_iter;
  qapi_Net_Coap_Opt_t *option;
  unsigned char buf[40];
  int len;
  qapi_Net_Coap_Tick_t now;
  qapi_Net_Coap_Tick_t t;
   
  /* if my_clock_base was deleted, we pretend to have no such resource */
  response->hdr->code =
    my_clock_base ? QAPI_COAP_RESPONSE_CODE(205) : QAPI_COAP_RESPONSE_CODE(404);

  if (qapi_Net_Coap_Server_Find_Observer(resource, peer, token)) {
    /* FIXME: need to check for resource->dirty? */
    qapi_Net_Coap_Server_Add_Option(response,
                    QAPI_COAP_OPTION_OBSERVE,
                   // demo_coap_encode_var_bytes(buf, ctx->observe), buf);
                   demo_coap_encode_var_bytes(buf, 0x1), buf);
  }

  if (my_clock_base)
    qapi_Net_Coap_Server_Add_Option(response,
                    QAPI_COAP_OPTION_CONTENT_FORMAT,
                    demo_coap_encode_var_bytes(buf, QAPI_COAP_MEDIATYPE_TEXT_PLAIN), buf);

  qapi_Net_Coap_Server_Add_Option(response,
                  QAPI_COAP_OPTION_MAXAGE,
                  demo_coap_encode_var_bytes(buf, 0x01), buf);

  if (my_clock_base) {

    /* calculate current time */
    t = app_get_time(NULL);    
    now = my_clock_base + t ;

    if (request != NULL
        && (option = (qapi_Net_Coap_Opt_t *)qapi_Net_Coap_Server_Check_Option(request, QAPI_COAP_OPTION_URI_QUERY, &opt_iter))
        && memcmp(DEMO_COAP_OPT_VALUE(option), "ticks",
        min(5, DEMO_COAP_OPT_LENGTH(option))) == 0) {
          /* output ticks */
          len = snprintf((char *)buf,
                         min(sizeof(buf),
                             response->max_size - response->length),
                             "%u s, %u ms", (unsigned int)(now/QAPI_COAP_TICKS_PER_SECOND), (unsigned int)(now%QAPI_COAP_TICKS_PER_SECOND));
          qapi_Net_Coap_Server_Add_Data(response, len, buf);

    }    
  }
}

static void
hnd_put_time(qapi_Net_Coap_Context_t* ctx,
             qapi_Net_Coap_Resource_t* resource,
             qapi_Net_Coap_Address_t *peer,
             qapi_Net_Coap_Pdu_t *request,
             qapi_Net_Coap_Str_t *token,
             qapi_Net_Coap_Pdu_t *response) {
  int size;
  unsigned char *data;
  char buf[16] = {0};

  /* FIXME: re-set my_clock_base to clock_offset if my_clock_base == 0
   * and request is empty. When not empty, set to value in request payload
   * (insist on query ?ticks). Return Created or Ok.
   */
  /* if my_clock_base was deleted, we pretend to have no such resource */
  response->hdr->code =
    my_clock_base ? QAPI_COAP_RESPONSE_CODE(204) : QAPI_COAP_RESPONSE_CODE(201);

  //resource->dirty = 1;

  qapi_Net_Coap_Server_Resource_Set_Dirty(resource,1);
  qapi_Net_Coap_Server_Get_Data(request, &size, &data);


  if (size == 0){        /* re-init */
    my_clock_base = clock_offset;
  } else { 
    memcpy(buf, data, size);
    buf[size] = '\0';
    COAP_PRINTF("PUT Time: %s %d\n", buf, atoi(buf));
    my_clock_base = atoi(buf)*QAPI_COAP_TICKS_PER_SECOND;
  }
}

static void
hnd_delete_time(qapi_Net_Coap_Context_t* ctx,
                qapi_Net_Coap_Resource_t* resource,
                qapi_Net_Coap_Address_t *peer,
                qapi_Net_Coap_Pdu_t *request,
                qapi_Net_Coap_Str_t *token,
                qapi_Net_Coap_Pdu_t *response) {                
  my_clock_base = 0;    /* mark clock as "deleted" */
  response->hdr->code =
    my_clock_base ? QAPI_COAP_RESPONSE_CODE(500) : QAPI_COAP_RESPONSE_CODE(202);

}


static void
hnd_post_test(qapi_Net_Coap_Context_t* ctx,
                qapi_Net_Coap_Resource_t* resource,
                qapi_Net_Coap_Address_t *peer,
                qapi_Net_Coap_Pdu_t *request,
                qapi_Net_Coap_Str_t *token,
                qapi_Net_Coap_Pdu_t *response) {                         
    int size;
    unsigned char *data;
    int i;
    char buf[64] = {0};
    /* FIXME: re-set my_clock_base to clock_offset if my_clock_base == 0
     * and request is empty. When not empty, set to value in request payload
     * (insist on query ?ticks). Return Created or Ok.
     */
    
    /* if my_clock_base was deleted, we pretend to have no such resource */
    response->hdr->code = QAPI_COAP_RESPONSE_CODE(204);
     
    qapi_Net_Coap_Server_Get_Data(request, &size, &data);
    
    if (size == 0){        /* re-init */
      COAP_PRINTF("Post Test!");
    } else {
      for (i=size; i>=0; i--){
        buf[size-i] = *(data+i-1); 
      }
      COAP_PRINTF("Post Test: %s\n", buf);
    }
}

static void
hnd_block1_test(qapi_Net_Coap_Context_t* ctx,
                qapi_Net_Coap_Resource_t* resource,
                qapi_Net_Coap_Address_t *peer,
                qapi_Net_Coap_Pdu_t *request,
                qapi_Net_Coap_Str_t *token,
                qapi_Net_Coap_Pdu_t *response) {                   
    int size;
    unsigned char *data;
    char buf[64] = {0};
    unsigned char buf_block[4] = {0};
    qapi_Net_Coap_Opt_t *block_opt;
    qapi_Net_Coap_Opt_Iterator_t opt_iter;
    qapi_Net_Coap_Block_t block;

    qapi_Net_Coap_Server_Get_Data(request, &size, &data);
    
    if (size > 0) {
      size = (size<=63)?size:63;
      memcpy(buf, data, size);
      buf[size] = '\0';
      COAP_PRINTF("Block1 Test: %s\n", buf);
    }
    
    block_opt = qapi_Net_Coap_Server_Check_Option(request, QAPI_COAP_OPTION_BLOCK1, &opt_iter);
    
    if (block_opt) { /* handle Block1 */
    block.m = DEMO_COAP_OPT_BLOCK_MORE(block_opt)?1:0;    
    block.szx = DEMO_COAP_OPT_BLOCK_SZX(block_opt);
    block.num = DEMO_COAP_OPT_BLOCK_NUM(block_opt);    

    response->hdr->code = block.m?QAPI_COAP_RESPONSE_CODE(231):QAPI_COAP_RESPONSE_CODE(204);

    COAP_PRINTF("Block1 num %u, m %u, size %u\n", block.num, block.m, (1<<(block.szx+4)));     
    memset(buf, 0, sizeof(buf));
    qapi_Net_Coap_Server_Add_Option(response,
                QAPI_COAP_OPTION_BLOCK1,
                demo_coap_encode_var_bytes(buf_block,
                ( (block.num<< 4)) | (block.m<< 3 )| block.szx), buf_block);
    }
}

static void
hnd_block2_test(qapi_Net_Coap_Context_t* ctx,
                qapi_Net_Coap_Resource_t* resource,
                qapi_Net_Coap_Address_t *peer,
                qapi_Net_Coap_Pdu_t *request,
                qapi_Net_Coap_Str_t *token,
                qapi_Net_Coap_Pdu_t *response) {                 
    unsigned char buf[32] = {0};
    qapi_Net_Coap_Opt_t *block_opt;
    qapi_Net_Coap_Opt_Iterator_t opt_iter;
    qapi_Net_Coap_Block_t block;
         
    
    block_opt = qapi_Net_Coap_Server_Check_Option(request, QAPI_COAP_OPTION_BLOCK2, &opt_iter);
    if (!block_opt){
        block.num = 0;
        block.szx = (demo_coap_fls(16 >> 4) - 1) & 0x07;
        block.m = strlen(INDEX) > 16;
    } else {
        block.num = DEMO_COAP_OPT_BLOCK_NUM(block_opt);
        block.szx = (demo_coap_fls(16 >> 4) - 1) & 0x07;
        block.m = ((block.num+1) * (1 << (block.szx + 4)) < strlen(INDEX));
    }
    COAP_PRINTF("Block2 num %u, m %u, size %u\n", block.num, block.m, (1<<(block.szx+4)));     
    
    response->hdr->code = QAPI_COAP_RESPONSE_CODE(205);
    
    qapi_Net_Coap_Server_Add_Option(response,
                QAPI_COAP_OPTION_BLOCK2,
                demo_coap_encode_var_bytes(buf,
                (block.num << 4) | (block.m<< 3) | block.szx), buf);

    qapi_Net_Coap_Server_Add_Block(response, strlen(INDEX),  (unsigned char*)INDEX, block.num,  block.szx);
}


static void
hnd_get_async(qapi_Net_Coap_Context_t* ctx,
                qapi_Net_Coap_Resource_t* resource,
                qapi_Net_Coap_Address_t *peer,
                qapi_Net_Coap_Pdu_t *request,
                qapi_Net_Coap_Str_t *token,
                qapi_Net_Coap_Pdu_t *response) {         
  qapi_Net_Coap_Opt_Iterator_t opt_iter;
  qapi_Net_Coap_Opt_t *option;
  unsigned long delay = 5;
  int size;

  option = qapi_Net_Coap_Server_Check_Option(request, QAPI_COAP_OPTION_URI_QUERY, &opt_iter);
  if (option) {
    unsigned char *p = DEMO_COAP_OPT_VALUE(option);

    delay = 0;
    for (size = DEMO_COAP_OPT_LENGTH(option); size; --size, ++p)
      delay = delay * 10 + (*p - '0');
  }

  qapi_Net_Coap_Server_Register_Async(ctx,
                              peer,
                              request,
                              QAPI_COAP_ASYNC_SEPARATE | QAPI_COAP_ASYNC_CONFIRM,
                              (QAPI_COAP_TICKS_PER_SECOND * delay));
}

static void
init_resources(qapi_Net_Coap_Context_t* *ctx) {
  qapi_Net_Coap_Resource_t* r;

  r = qapi_Net_Coap_Server_Resource_Init(NULL, 0, 0);
  qapi_Net_Coap_Server_Resource_Register_Handler(r, QAPI_COAP_REQUEST_GET, hnd_get_index);

  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"ct", 2, (unsigned char *)"0", 1, 0);
  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"title", 5, (unsigned char *)"\"General Info\"", 14, 0);
  qapi_Net_Coap_Server_Add_Resource(ctx, r);

  /* store clock base to use in /time */
  my_clock_base = clock_offset;

  r = qapi_Net_Coap_Server_Resource_Init((unsigned char *)"time", 4, QAPI_COAP_RESOURCE_FLAGS_NOTIFY_CON);
  qapi_Net_Coap_Server_Resource_Register_Handler(r, QAPI_COAP_REQUEST_GET, hnd_get_time);
  qapi_Net_Coap_Server_Resource_Register_Handler(r, QAPI_COAP_REQUEST_PUT, hnd_put_time);
  qapi_Net_Coap_Server_Resource_Register_Handler(r, QAPI_COAP_REQUEST_DELETE, hnd_delete_time);

  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"ct", 2, (unsigned char *)"0", 1, 0);
  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"title", 5, (unsigned char *)"\"Internal Clock\"", 16, 0);
  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"rt", 2, (unsigned char *)"\"Ticks\"", 7, 0);

  qapi_Net_Coap_Server_Resource_Set_Observable(r, 1);
  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"if", 2, (unsigned char *)"\"clock\"", 7, 0);

  qapi_Net_Coap_Server_Add_Resource(ctx, r);

  r = qapi_Net_Coap_Server_Resource_Init((unsigned char *)"async", 5, 0);
  qapi_Net_Coap_Server_Resource_Register_Handler(r, QAPI_COAP_REQUEST_GET, hnd_get_async);

  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"ct", 2, (unsigned char *)"0", 1, 0);
  qapi_Net_Coap_Server_Add_Resource(ctx, r);

  
  r = qapi_Net_Coap_Server_Resource_Init((unsigned char *)"post_test", 9, 0);
  qapi_Net_Coap_Server_Resource_Register_Handler(r, QAPI_COAP_REQUEST_POST, hnd_post_test);

  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"ct", 2, (unsigned char *)"0", 1, 0);
  qapi_Net_Coap_Server_Add_Resource(ctx, r);

  r = qapi_Net_Coap_Server_Resource_Init((unsigned char *)"block1_test", 11, 0);
  qapi_Net_Coap_Server_Resource_Register_Handler(r, QAPI_COAP_REQUEST_POST, hnd_block1_test);

  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"ct", 2, (unsigned char *)"0", 1, 0);
  qapi_Net_Coap_Server_Add_Resource(ctx, r);

    r = qapi_Net_Coap_Server_Resource_Init((unsigned char *)"block2_test", 11, 0);
  qapi_Net_Coap_Server_Resource_Register_Handler(r, QAPI_COAP_REQUEST_GET, hnd_block2_test);

  qapi_Net_Coap_Server_Add_Attr(r, (unsigned char *)"ct", 2, (unsigned char *)"0", 1, 0);
  qapi_Net_Coap_Server_Add_Resource(ctx, r);

}


/*
 *             [0]  [1]  [2]   [3]         [4] [5]  [6] [7] [8]     [9]
 *  net coap server tcp  -A  192.168.1.102 -v ipv4  -p  443 -c  device.cert.bin  
 *  net coap server start
 *  net coap server stop
 */
QCLI_Command_Status_t
coap_server_test(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List) 
{
    int i= 1;  
    qapi_Net_Coap_Server_Cfg_t * pCoapServer = NULL;

    if ((Parameter_Count == 2) ){
        if(strcmp(Parameter_List[1].String_Value, "stop")== 0){
            if(coap_server){
                if(qapi_Net_Coap_Server_Stop(coap_server->ctx) != 0) {
                    COAP_PRINTF("Coap stop error!\r\n");  
                    return QCLI_STATUS_ERROR_E;            
                }            
                if (coap_server->req_cfg){
                    free(coap_server->req_cfg);
                    coap_server->req_cfg = NULL;
                } 
                if (coap_server->sslCfg){
                    free(coap_server->sslCfg);
                    coap_server->sslCfg = NULL;
                }
                if (QAPI_NET_SSL_INVALID_HANDLE != coap_server->sslCtx){
                    qapi_Net_SSL_Obj_Free(coap_server->sslCtx);
                    coap_server->sslCtx = QAPI_NET_SSL_INVALID_HANDLE;
                }
                free(coap_server);
                coap_server = NULL;
            }
            else
                COAP_PRINTF("coap server is NULL!\r\n");  
            COAP_PRINTF("coap server stopped!\r\n");  
            return QCLI_STATUS_SUCCESS_E;
        }
        if(strcmp(Parameter_List[1].String_Value, "start")== 0){
            if(coap_server){
                if(qapi_Net_Coap_Server_Start(coap_server->ctx) != 0){
                    COAP_PRINTF("Coap start error!\r\n");  
                    return QCLI_STATUS_ERROR_E;
                }
            }else{
                    COAP_PRINTF("coap server not start!\r\n");  
            }
            COAP_PRINTF("coap server start successfully!\r\n");  
            return QCLI_STATUS_SUCCESS_E;
        }
    }else if(strncmp(Parameter_List[1].String_Value, "sslconfig", 3) == 0 || strcmp(Parameter_List[1].String_Value, "sslcfg") == 0){

    /*           [0]        [1]     [2]      [3]    [4]  [5] [6]   [7]
     * net coap server sslconfig  protocol  TLS1.2 time  1   alert 0
     */
        QCLI_Command_Status_t status;

        if(coap_server == NULL){
            COAP_PRINTF("coap server is NULL!\n");
            return QCLI_STATUS_SUCCESS_E;
        }
        
        if (Parameter_Count < 2)
        {
            COAP_PRINTF("What are SSL parameters?\n");
            coap_server_help();
            return QCLI_STATUS_SUCCESS_E;
        }

        if (coap_server->sslCfg == NULL)
        {
            coap_server->sslCfg = malloc(sizeof(qapi_Net_SSL_Config_t));
            if (coap_server->sslCfg == NULL)
            {
                COAP_PRINTF("Allocation failure\n");
                return QCLI_STATUS_ERROR_E;
            }
            memset(coap_server->sslCfg, 0, sizeof(qapi_Net_SSL_Config_t));
        }
        else
        {
            /* free previous ssl parameters */
            ssl_free_config_parameters(coap_server->sslCfg);
        }

        /* Parse SSL config parameters from command line */
        status = ssl_parse_config_parameters(
                        Parameter_Count-2,
                        &Parameter_List[2],
                        coap_server->sslCfg,
                        0,
                        TRUE);
        if (status == QCLI_STATUS_USAGE_E)
        {   
            ssl_free_config_parameters(coap_server->sslCfg);
            free(coap_server->sslCfg);
            coap_server->sslCfg = NULL;
            return QCLI_STATUS_ERROR_E;
        }

        /* always uses TLS. If configured for DTLS, silently ignore */
        if (coap_server->sslCfg->protocol <= QAPI_NET_SSL_DTLS_E ||
            coap_server->sslCfg->protocol > QAPI_NET_SSL_PROTOCOL_TLS_1_2)
        {
            coap_server->sslCfg->protocol = 0;
        }
        return status;
    }
    else if(Parameter_Count <= 3){
        coap_server_help();
        return QCLI_STATUS_ERROR_E;
    }

    
    coap_server = (coap_demo_server_t *)malloc(sizeof(coap_demo_server_t));
    if (!coap_server){
        COAP_PRINTF("No Memory!\r\n");    
        return QCLI_STATUS_ERROR_E;
    }
    memset(coap_server, 0, sizeof(coap_demo_server_t));

    coap_server->req_cfg = (qapi_Net_Coap_Server_Cfg_t *)malloc(sizeof(qapi_Net_Coap_Server_Cfg_t));
    if (!coap_server->req_cfg){
        COAP_PRINTF("No Memory!\r\n");    
        return QCLI_STATUS_ERROR_E;
    }
    pCoapServer = coap_server->req_cfg;
    memset(pCoapServer, 0, sizeof(qapi_Net_Coap_Server_Cfg_t));

    clock_offset = app_get_time(NULL);


    if(strcmp(Parameter_List[1].String_Value, "udp") == 0 )
    {
        pCoapServer->protocol = QAPI_COAP_PROTOCOL_UDP;
        i++;
    }else if(strcmp(Parameter_List[1].String_Value, "tcp") == 0)
    {
        pCoapServer->protocol = QAPI_COAP_PROTOCOL_TCP;
        i++;
    }else if(strcmp(Parameter_List[1].String_Value, "dual") == 0)
    {
        pCoapServer->protocol = QAPI_COAP_PROTOCOL_UDP | QAPI_COAP_PROTOCOL_TCP;
        i++;
    }else
    {
        COAP_PRINTF("unknown protocol, udp or tcp");
        goto COAP_SERVER_ERROR;
    }
    
    while ((Parameter_Count > i)&&(strlen(Parameter_List[i].String_Value) == 2)) {
        switch (*(Parameter_List[i].String_Value+1)) {
             case 'i' :
                strncpy(pCoapServer->interface_Name, Parameter_List[++i].String_Value, QAPI_INTERFACE_NAME_LEN);
                break;
            case 'g' :
                strncpy(pCoapServer->group_str, Parameter_List[++i].String_Value, QAPI_NI_MAXHOST-1);
                pCoapServer->group_enabled = TRUE ;
                break;
            case 'p' :
                strncpy(pCoapServer->port_str, Parameter_List[++i].String_Value, QAPI_NI_MAXSERV-1);
                break;
            case 'v' :
                if (strcmp(Parameter_List[++i].String_Value, "v6") == 0){
                    pCoapServer->v4v6_enabled = QAPI_COAP_SERVER_FLAG_IPV6 ;
                } else  if (strcmp(Parameter_List[i].String_Value, "v4") == 0){
                    pCoapServer->v4v6_enabled = QAPI_COAP_SERVER_FLAG_IPV4 ;
                } else if(strcmp(Parameter_List[i].String_Value, "v4v6") == 0){
                    pCoapServer->v4v6_enabled = QAPI_COAP_SERVER_FLAG_IPV4 | QAPI_COAP_SERVER_FLAG_IPV6 ;
                }else{
                  COAP_PRINTF("wrong ip protocol!");
                  goto COAP_SERVER_ERROR;
                }
                break;
            case 'c' :
                strncpy(pCoapServer->cert_file, Parameter_List[++i].String_Value, QAPI_PATHMAX-1);
                pCoapServer->cert_file[sizeof(pCoapServer->cert_file) - 1] = '\0';
      
                /* Create an SSL object */
                coap_server->sslCtx = qapi_Net_SSL_Obj_New(QAPI_NET_SSL_SERVER_E);
                if (coap_server->sslCtx == QAPI_NET_SSL_INVALID_HANDLE)
                {
                    goto COAP_SERVER_ERROR;
                }      
                if (pCoapServer->cert_file != NULL && pCoapServer->cert_file[0] != '\0')
                {
                    qapi_Net_SSL_Cert_Type_t cert_type;
                    int rc;
      
                    //cert_type = (role == QAPI_NET_SSL_SERVER_E) ? QAPI_NET_SSL_CERTIFICATE_E : QAPI_NET_SSL_CA_LIST_E;
                    cert_type = QAPI_NET_SSL_CERTIFICATE_E;
                    rc = qapi_Net_SSL_Cert_Load(coap_server->sslCtx , cert_type, pCoapServer->cert_file);
                    if (rc != 0)
                    {
                        qapi_Net_SSL_Obj_Free(coap_server->sslCtx );
                        goto COAP_SERVER_ERROR;
                    }
                }
                break;
              
            default:
                goto COAP_SERVER_ERROR;
        }
        i++;
    }


    if( (coap_server->ctx = qapi_Net_Coap_Server_New_Context(pCoapServer,coap_server->sslCtx)) == NULL )
    {
        COAP_PRINTF("coap server init error\n");
        goto COAP_SERVER_ERROR;
    }
    
    if(coap_server->sslCfg != NULL){
        if(qapi_Net_Coap_Server_SSL_Config(coap_server->ctx, coap_server->sslCfg) != QCLI_STATUS_SUCCESS_E)
        {
            COAP_PRINTF("coap server SSL Config error!\n");
            goto COAP_SERVER_ERROR;
        }
    }

    init_resources(coap_server->ctx);

    return QCLI_STATUS_SUCCESS_E;

COAP_SERVER_ERROR:
    COAP_PRINTF("coap server start FAIL.\n");
    qapi_Net_Coap_Server_Stop(coap_server->ctx);
    if (coap_server->req_cfg){
        free(coap_server->req_cfg);
        coap_server->req_cfg = NULL;
    } 
    if (coap_server->sslCfg){
        free(coap_server->sslCfg);
        coap_server->sslCfg = NULL;
    } 
    if (coap_server){
        free(coap_server);
        coap_server = NULL;
    }                     
    return QCLI_STATUS_ERROR_E;

}

/**
 * Calculates decimal value from hexadecimal ASCII character given in
 * @p c. The caller must ensure that @p c actually represents a valid
 * heaxdecimal character, e.g. with isxdigit(3).
 *
 * @hideinitializer
 */
#define hexchar_to_dec(c) ((c) & 0x40 ? ((c) & 0x0F) + 9 : ((c) & 0x0F))

qapi_Net_Coap_Method_t
cmdline_method(char *arg) {
  static char *methods[] =
    { 0, "get", "post", "put", "delete", 0};
  unsigned char i;

  for (i=1; methods[i] && strcasecmp(arg,methods[i]) != 0 ; ++i)
    ;

  return i;     /* note that we do not prevent illegal methods */
}


/*
 * By default, any CLI option need a parameter. 
 * If one option don't need a parameter, add it here.
 */
int coap_is_cli_option_need_parameter(char cli_option)
{
    switch (cli_option)
    {
    case 'N':
        return 0;

    default:
        break;
    }
    return 1;
}

void demo_coap_client_cb_test(void* arg, int32_t state, void* value, int32_t reserved)
{       
        qapi_Net_Coap_Pdu_t *rcv_pdu = (qapi_Net_Coap_Pdu_t *)value;;        
        coap_demo_client_t *pCoapClient = (coap_demo_client_t *)arg;
        unsigned char *p = NULL;
        int j=0;

        for (j=0; j<COAP_CLIENT_CONTEXT_MAX; j++){
              if (coap_client[j]!= NULL 
                && coap_client[j] == pCoapClient){
                     break;
              }
        }
        if(j >= COAP_CLIENT_CONTEXT_MAX){
            COAP_PRINTF("CB can not find the context!\n");
            return;
        }
        
        COAP_PRINTF("=========> coap client %d Received: state=%d\n",j+1, state); 
        if(state == QAPI_COAP_RESP_TIMEOUT){
            COAP_PRINTF("=========> state= TIMEOUT\n"); 
            return;
        }
        if(rcv_pdu && rcv_pdu->length && rcv_pdu->hdr){
            if(rcv_pdu->data){ 
                int hdr_len;
                int data_len;
                int tmp_len;
                uint8_t * data = NULL;
                p = rcv_pdu->data++; // skip the payload marker 0xff
                hdr_len = p - (unsigned char *)rcv_pdu->hdr;
                data_len = rcv_pdu->length - hdr_len;
                COAP_PRINTF("(%s,%d) hdr_len=%d\n",__FUNCTION__,__LINE__,hdr_len);
                COAP_PRINTF("=========> coap client Received: data length %d , \"", data_len);
              

                if ((data = malloc(MAX_PRINTF_LENGTH+1)) == NULL)
                {
                    COAP_PRINTF("coap Client Demo malloc error %d\n", state);
                    return;
                }
    			/*print buffer is only 256B*/
                if( data_len > MAX_PRINTF_LENGTH)
                {
                    tmp_len = data_len;
                    while(tmp_len > MAX_PRINTF_LENGTH)
                    {
                        memcpy(data, p, MAX_PRINTF_LENGTH);
                        data[MAX_PRINTF_LENGTH] = '\0';
                        COAP_PRINTF("%s", data);
                        p += MAX_PRINTF_LENGTH;
                        tmp_len -= MAX_PRINTF_LENGTH;

                    }
                    if( tmp_len > 0 )
                    {
                        memcpy(data, p, tmp_len);
                        data[tmp_len] = '\0';
                        COAP_PRINTF("%s", data);

                    }
                }
                else
                {
                    memcpy(data, p, data_len);
                    data[data_len] = '\0';
                    COAP_PRINTF("%s", data);
                }
                 COAP_PRINTF("\"\n");
                free(data);     
               
            }
        }
    return;
}

int32_t coap_free_client(coap_demo_client_t *coap_client)
{
    if (NULL == coap_client){
        return -1;
    }

    if (QAPI_NET_SSL_INVALID_HANDLE != coap_client->sslCtx){
        qapi_Net_SSL_Obj_Free(coap_client->sslCtx);
    }
    
    if (NULL != coap_client->sslCfg){
        free(coap_client->sslCfg);
    }
    
    free(coap_client);
    return 0;
}

int32_t coap_client_list_init(void)
{
    coap_demo_client_t *p_client;
    int i;
    int j;

    for (i = 0; i < COAP_CLIENT_CONTEXT_MAX; i++){
        p_client = (coap_demo_client_t*)malloc(sizeof(coap_demo_client_t));
        if (NULL == p_client){
            COAP_PRINTF("[%d]Memory allocation failed\n", __LINE__);
            for (j = 0; j < i; j++){
                free(coap_client[j]);
            }
            return -1;
        }
        memset(p_client, 0, sizeof(coap_demo_client_t));
        p_client->idx = i;
        p_client->proto_type = 0;
        p_client->security = FALSE;
        coap_client[i] = p_client;
    }

    return 0;
}

int32_t coap_client_node_free(uint32_t idx, qbool_t complete)
{
    coap_demo_client_t *p_client = NULL;


    if (idx >= COAP_CLIENT_CONTEXT_MAX){
        return -1;
    }
    
    p_client = coap_client[idx];
    if (NULL == p_client){
        return -1;
    }

    /*Reset it now since it's released 
    in qapi_Net_Coap_Client_Free_Context or qapi_Net_Coap_Client_Stop*/
    p_client->ctx = NULL; 
    
    if (QAPI_NET_SSL_INVALID_HANDLE != p_client->sslCtx){
        qapi_Net_SSL_Obj_Free(p_client->sslCtx);
        p_client->sslCtx = QAPI_NET_SSL_INVALID_HANDLE;
    }
    if (NULL != p_client->sslCfg){
        free(p_client->sslCfg);
        p_client->sslCfg = NULL;
    }

    if (complete){
        free(p_client);
        coap_client[idx] = NULL;
    }
    
    return 0;
}

int32_t coap_client_list_deinit(void)
{
    int i;
    
    for (i = 0; i < COAP_CLIENT_CONTEXT_MAX; i++){
        coap_client_node_free(i, TRUE);
    }
    
    return 0;
}

coap_demo_client_t *coap_client_node_get_by_idx(uint32_t idx)
{
    if (idx >= COAP_CLIENT_CONTEXT_MAX){
        return NULL;
    }
    return coap_client[idx];
}

coap_demo_client_t *coap_client_node_get_free(void)
{
    int i;

    for (i = 0; i < COAP_CLIENT_CONTEXT_MAX; i++){
        if (NULL == coap_client[i]->ctx){
            return coap_client[i];
        }
    }
    
    return NULL;
}

unsigned char coap_client_get_content_code(char *media_type)
{
    int i;
    char *local_type = NULL;
    static content_type_t content_types[] = {
        {  0, "plain" },
        {  0, "text/plain" },
        { 40, "link" },
        { 40, "link-format" },
        { 40, "application/link-format" },
        { 41, "xml" },
        { 41, "application/xml" },
        { 42, "binary" },
        { 42, "octet-stream" },
        { 42, "application/octet-stream" },
        { 47, "exi" },
        { 47, "application/exi" },
        { 50, "json" },
        { 50, "application/json" },
        { 60, "cbor" },
        { 60, "application/cbor" },
        { 255, NULL }
    };


    if (NULL == media_type){
        return 0xFF;
    }
    
    for (i = 0; NULL != content_types[i].media_type; i++){
        local_type = content_types[i].media_type;
        if (0 == strncmp(local_type, media_type, strlen(local_type))){
            return content_types[i].code;
        }
    }
    
    return 0xFF;
}
/*
 *              [0]  [1] [2] [3] [4] [5]   
 *  net coap  client  1  udp -m  get coap://192.168.1.103 
 *  net coap  client  1  -m  get /time?ticks 
 *  net coap  client  start
 *  net coap  client  stop
 *  net coap  client  1 stop
 *  net coap  client  1 sslconfig protocol DTLS1.2 cipher TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8
 */
QCLI_Command_Status_t
coap_client_test(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List) 
{
    int i= 2, index =-1; 
    coap_demo_client_t *pCoapClient = NULL;
    int tid;

    char server[40];   
    unsigned int port;    
    unsigned char security;    
    char query[40];    
    int server_len, query_len;    
    unsigned int block_num = 0;
    unsigned int block_size = 0;
    unsigned char token[QAPI_COAP_TOKEN_MAX_LEN] = {0};
    unsigned char block_is_set=0;
    unsigned char token_is_set=0;
    unsigned char content_type_code = 0;
    unsigned char content_type_is_set = 0;
    
    unsigned int wait_ms=0;
    unsigned int obs_seconds=0; 
    unsigned char * payload=NULL;
    unsigned int payload_len=0;
    qapi_Net_Coap_Request_Method method = QAPI_COAP_REQUEST_GET;
    qapi_Net_Coap_Msg_Type msgtype = QAPI_COAP_MESSAGE_CON;
    qapi_Net_Coap_Protocol_Type protocol_type = QAPI_COAP_PROTOCOL_UDP;

    
    if (Parameter_Count < 2){
        coap_client_help();
        return QCLI_STATUS_ERROR_E;
    }

    /*net coap client start*/
    if ((Parameter_Count == 2) 
        && (strcmp(Parameter_List[1].String_Value, "start")== 0)){
        if (client_demo_started){
            COAP_PRINTF("coap client already started\n");
            return QCLI_STATUS_ERROR_E;
        }
        
        if(qapi_Net_Coap_Client_Start() != QCLI_STATUS_SUCCESS_E){
            COAP_PRINTF("coap client start error!\r\n");
            return QCLI_STATUS_ERROR_E;
        }
        
        if (0 != coap_client_list_init()){
            COAP_PRINTF("coap client list init error!\r\n");
            return QCLI_STATUS_ERROR_E;
        }

        client_demo_started = TRUE;
        return QCLI_STATUS_SUCCESS_E;
    } 
    
    /*net coap client stop*/
    if ((Parameter_Count == 2) 
        && (strcmp(Parameter_List[1].String_Value, "stop")== 0)){
        if (!client_demo_started){
            COAP_PRINTF("coap client not started\n");
            return QCLI_STATUS_ERROR_E;
        }
        if(qapi_Net_Coap_Client_Stop() != QCLI_STATUS_SUCCESS_E){
            COAP_PRINTF("coap client stop error!\r\n");
            return QCLI_STATUS_ERROR_E;
        }

        if (0 != coap_client_list_deinit()){
            COAP_PRINTF("coap client list deinit error!\r\n");
            return QCLI_STATUS_ERROR_E;
        }

        client_demo_started = FALSE;
        COAP_PRINTF("all coap client stop! you need to coap client start again.\r\n");        
        
        return QCLI_STATUS_SUCCESS_E;   
    } 


    if (!client_demo_started){
        COAP_PRINTF("coap client not started\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    /*Get client index*/
    if (Parameter_List[1].Integer_Is_Valid){
        index = atoi(Parameter_List[1].String_Value);
        if (index < 1 || index > COAP_CLIENT_CONTEXT_MAX){
            COAP_PRINTF("Client index should be in range from 1 to %d\n", COAP_CLIENT_CONTEXT_MAX);
            return QCLI_STATUS_ERROR_E;
        }
    }
    else{
        COAP_PRINTF("Client index is invalid\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count < 3){
        coap_client_help();
        return QCLI_STATUS_ERROR_E;
    }
    
    /*net coap client {1-4} stop*/
    if (strcmp(Parameter_List[2].String_Value, "stop")== 0){        
        pCoapClient = coap_client_node_get_by_idx(index - 1);
        if (NULL == pCoapClient){
            COAP_PRINTF("This COAP client %d doesn't exist!", index);
            return QCLI_STATUS_ERROR_E;
        }

        if (NULL != pCoapClient->ctx){
            qapi_Net_Coap_Client_Free_Context(pCoapClient->ctx);
        }
        coap_client_node_free(pCoapClient->idx, FALSE);
        COAP_PRINTF("coap client %d stop!\r\n", index);
        return QCLI_STATUS_SUCCESS_E;
    }

    /*           [0]   [1]     [2]      [3] */
    /*net coap client {0-4} sslconfig option*/
    if(strncmp(Parameter_List[2].String_Value, "sslconfig", 3) == 0){
        QCLI_Command_Status_t status;

        pCoapClient = coap_client_node_get_by_idx(index - 1);
        if (NULL == pCoapClient){
            COAP_PRINTF("This COAP client %d doesn't exist!", index);
            return QCLI_STATUS_ERROR_E;
        }
        
        if (Parameter_Count < 4)
        {
            COAP_PRINTF("What are SSL parameters?\n");
            sslconfig_help("coap client index sslconfig");
            return QCLI_STATUS_SUCCESS_E;
        }

        if (pCoapClient->sslCfg == NULL)
        {
            pCoapClient->sslCfg = malloc(sizeof(qapi_Net_SSL_Config_t));
            if (pCoapClient->sslCfg == NULL)
            {
                COAP_PRINTF("Allocation ssl config failure\n");
                return QCLI_STATUS_ERROR_E;
            }
            memset(pCoapClient->sslCfg, 0, sizeof(qapi_Net_SSL_Config_t));
        }
        else
        {
            /* free previous ssl parameters */
            ssl_free_config_parameters(pCoapClient->sslCfg);
        }

        /* Parse SSL config parameters from command line */
        status = ssl_parse_config_parameters(
                        Parameter_Count-3,
                        &Parameter_List[3],
                        pCoapClient->sslCfg,
                        0,
                        FALSE);
        if (status == QCLI_STATUS_SUCCESS_E){
            COAP_PRINTF("SSL configuration of coap client %d changed\n", pCoapClient->idx + 1);
        }
        else
        {   
            COAP_PRINTF("ssl configuration failure\n");
            ssl_free_config_parameters(pCoapClient->sslCfg);
            free(pCoapClient->sslCfg);
            pCoapClient->sslCfg = NULL;
            return QCLI_STATUS_ERROR_E;
        }
        
        return status;
    }

    
    /*net coap client index {udp|tcp} option }*/
    pCoapClient = coap_client_node_get_by_idx(index - 1);
    if (NULL == pCoapClient){
        COAP_PRINTF("COAP client %d doesn't exist!", index);
        return QCLI_STATUS_ERROR_E;
    }

    #if 0
    if (NULL != pCoapClient->ctx){
        COAP_PRINTF("Please stop coap client %d before starting it again.\n", pCoapClient->idx + 1);
        return QCLI_STATUS_ERROR_E;
    }
    #endif
    
    i = 2;
    if(strcmp(Parameter_List[i].String_Value, "udp") == 0)
    {   
        if (pCoapClient->ctx &&
            QAPI_COAP_PROTOCOL_UDP != pCoapClient->proto_type){
            COAP_PRINTF("One client allows only one protocol (TCP or UDP)\n");
            goto COAP_CLIENT_ERROR;
        }
        protocol_type = QAPI_COAP_PROTOCOL_UDP;
        i++;
    }
    else if(strcmp(Parameter_List[i].String_Value, "tcp") == 0)
    {
        if (pCoapClient->ctx &&
            QAPI_COAP_PROTOCOL_TCP != pCoapClient->proto_type){
            COAP_PRINTF("One client allows only one protocol (TCP or UDP)\n");
            goto COAP_CLIENT_ERROR;
        }
        protocol_type = QAPI_COAP_PROTOCOL_TCP;
        i++;
    }
    else
    {
        COAP_PRINTF("unknown protocol, udp or tcp");
        goto COAP_CLIENT_ERROR;
    }
    pCoapClient->proto_type = protocol_type; /*Store protocol type*/
    wait_ms = QAPI_COAP_DEFAULT_MAX_WAIT_MS;
    obs_seconds = 0;
    msgtype = QAPI_COAP_MESSAGE_CON;

    COAP_PRINTF("Start coap client %d\n", pCoapClient->idx + 1);
    COAP_PRINTF("  PROTO : %s\n", (QAPI_COAP_PROTOCOL_UDP == protocol_type)?"UDP":"TCP");
    while ((Parameter_Count > 2) 
            && (i<Parameter_Count) 
            && (strlen(Parameter_List[i].String_Value) == 2)) {
        char cli_option = *(Parameter_List[i].String_Value+1); 
        if ((1 == coap_is_cli_option_need_parameter(cli_option))
            && (Parameter_List[++i].String_Value == NULL))
        {
          COAP_PRINTF("Missing parameter after -%c", cli_option);
          goto COAP_CLIENT_ERROR;
        }

        /* note that "i" now point to the value of the option */
        switch (cli_option) {
            case 'b' :
                demo_cmdline_blocksize(Parameter_List[i].String_Value, &block_num, &block_size);
                block_is_set = 1;
                break;
            case 'B' :
                wait_ms= atoi(Parameter_List[i].String_Value)*1000;
                COAP_PRINTF("  wait_ms: %u\n", wait_ms);
                break;
            case 'e' :
                payload_len = strlen(Parameter_List[i].String_Value);
                payload = (unsigned char *)malloc(payload_len + 1);
                if (payload == NULL){
                  COAP_PRINTF("Coap client payload memory alloc fail!");
                  goto COAP_CLIENT_ERROR;
                }
                strncpy((char*)payload, Parameter_List[i].String_Value, payload_len); 
                COAP_PRINTF("  payload: %s\n", payload);
                break;    
            case 'm' :
                method = cmdline_method(Parameter_List[i].String_Value);   
                COAP_PRINTF("  method: %s\n",  (1 == method)?"get"
                                                :(2 == method)?"post"
                                                :(3 == method)?"put"
                                                :(4 == method)?"delete":"Invalid"
                                                );
                break;
            case 'N' :
                msgtype = QAPI_COAP_MESSAGE_NON;
                COAP_PRINTF("  msgtype: Non_conn\n");
                break;
            case 's' :
                obs_seconds = atoi(Parameter_List[i].String_Value);
                COAP_PRINTF("  method: %u\n", obs_seconds);
                break;
            case 't' :
                COAP_PRINTF("content type: %s\n", Parameter_List[i].String_Value);
                content_type_code = coap_client_get_content_code(Parameter_List[i].String_Value);
                if (0xFF == content_type_code){
                    COAP_PRINTF("Unsupport content type: %s!\n", Parameter_List[i].String_Value);
                    goto COAP_CLIENT_ERROR;
                }
                content_type_is_set = 1;
                break;
            case 'T' :
                strncpy((char *)token, Parameter_List[i].String_Value, min(QAPI_COAP_TOKEN_MAX_LEN, strlen(Parameter_List[i].String_Value)));
                token_is_set = 1;
                break;
            default:
                COAP_PRINTF("Unsupport option -%c!", cli_option);
                goto COAP_CLIENT_ERROR;
        }
        i++;    
    }

    /*parse URI*/
    if (i < Parameter_Count && i>3) {
        if(demo_coap_split_uri((unsigned char*)Parameter_List[i].String_Value, strlen(Parameter_List[i].String_Value),&port, server, &server_len, &security, query, &query_len)!= QCLI_STATUS_SUCCESS_E){
            COAP_PRINTF("URI parese error!\n");
            goto COAP_CLIENT_ERROR;
        }
        COAP_PRINTF("  Server: %s[%u] security %s\n", server, port, security?"on":"off");
        COAP_PRINTF("  query : %s\n", query);
        if( security == TRUE){
            //Previous connection of this client is non-secure
            if (pCoapClient->ctx && !pCoapClient->security){
                COAP_PRINTF("One client allows only one security mode\n");
                goto COAP_CLIENT_ERROR;
            }
            
#ifdef CONFIG_NET_SSL_DEMO
            COAP_PRINTF("SSL context!\r\n");
            if (0 == pCoapClient->sslCtx){
                pCoapClient->sslCtx = qapi_Net_SSL_Obj_New(QAPI_NET_SSL_CLIENT_E);
                if (pCoapClient->sslCtx == QAPI_NET_SSL_INVALID_HANDLE)
                {
                    COAP_PRINTF("ERROR: Unable to create SSL context\n");
                    goto COAP_CLIENT_ERROR;
                }
            }
#else
            COAP_PRINTF("ERROR: SSL not supported\n");
            goto COAP_CLIENT_ERROR;
#endif
        }else{
            //Previous connection of this client is secure
            if (pCoapClient->ctx && pCoapClient->security){
                COAP_PRINTF("One client allows only one security mode\n");
                goto COAP_CLIENT_ERROR;
            }
            pCoapClient->sslCtx = 0;
        }
        pCoapClient->security = security; /*Store security mode*/

        if (NULL == pCoapClient->ctx){
            //Create coap client instance and connect to coap server.
            pCoapClient->ctx = qapi_Net_Coap_Client_New_Context(protocol_type, pCoapClient->sslCtx, demo_coap_client_cb_test, (void *)pCoapClient);
            if(pCoapClient->ctx == NULL){
                COAP_PRINTF("qapi_Net_Coap_Client_New_Context Error!\n");
                goto COAP_CLIENT_ERROR;
            }
            
            if(pCoapClient->security && pCoapClient->sslCfg != NULL){
                COAP_PRINTF("Configure ssl context\n");
                if (qapi_Net_Coap_Client_SSL_Config(pCoapClient->ctx, pCoapClient->sslCfg) != QCLI_STATUS_SUCCESS_E){
                    goto COAP_CLIENT_ERROR;
                }
            }
            
            COAP_PRINTF("connect server=%s, port=%d\n",server, port);
            if (qapi_Net_Coap_Client_Connect(pCoapClient->ctx, server, port) != QCLI_STATUS_SUCCESS_E){
                goto COAP_CLIENT_ERROR;
            }
            COAP_PRINTF("coap client %d connect Success\n",pCoapClient->idx + 1);
        }
    } else {
        COAP_PRINTF("Error Command!");
        goto COAP_CLIENT_ERROR;
    }


    if(token_is_set){
        token_is_set = 0;
        if((qapi_Net_Coap_Client_Add_Parameter(pCoapClient->ctx,QAPI_COAP_PARAMETER_FLAG_TOKEN, QAPI_COAP_PARAMETER_TYPE_TOKEN_GENERIC,token,strlen((char *)token))) != QCLI_STATUS_SUCCESS_E){
            COAP_PRINTF("set parameter token error \n");
        }
        
    }else{
        if((qapi_Net_Coap_Client_Add_Parameter(pCoapClient->ctx,QAPI_COAP_PARAMETER_FLAG_TOKEN, QAPI_COAP_PARAMETER_TYPE_TOKEN_GENERIC,NULL,0)) != QCLI_STATUS_SUCCESS_E){
            COAP_PRINTF("set parameter token clear error \n");
        }
    }

    if(block_is_set){
        block_is_set = 0;
        if((qapi_Net_Coap_Client_Add_Parameter(pCoapClient->ctx,QAPI_COAP_PARAMETER_FLAG_BLOCK, QAPI_COAP_PARAMETER_TYPE_BLOCK_GENERIC,(unsigned char *)&block_num,block_size)) != QCLI_STATUS_SUCCESS_E){
            COAP_PRINTF("set parameter  QAPI_COAP_PARAMETER_TYPE_BLOCK_GENERIC error \n");
        }

    }

    if(obs_seconds != 0){
        if((qapi_Net_Coap_Client_Add_Parameter(pCoapClient->ctx,QAPI_COAP_PARAMETER_FLAG_TIMEOUT, QAPI_COAP_PARAMETER_TYPE_TIMEOUT_OBSERVER,(unsigned char*)&obs_seconds,0)) != QCLI_STATUS_SUCCESS_E){
            COAP_PRINTF("set parameter QAPI_COAP_PARAMETER_TYPE_TIMEOUT_OBSERVER error \n");
        }
    }
    
    if(wait_ms != QAPI_COAP_DEFAULT_MAX_WAIT_MS){
        if((qapi_Net_Coap_Client_Add_Parameter(pCoapClient->ctx,QAPI_COAP_PARAMETER_FLAG_TIMEOUT, QAPI_COAP_PARAMETER_TYPE_TIMEOUT_SEND,(unsigned char*)&wait_ms,0)) != QCLI_STATUS_SUCCESS_E){
            COAP_PRINTF("set parameter  QAPI_COAP_PARAMETER_TYPE_TIMEOUT_SEND error \n");
        }
    }

    if (content_type_is_set){
        if(qapi_Net_Coap_Client_Add_Parameter(
            pCoapClient->ctx, 
            QAPI_COAP_PARAMETER_FLAG_OPTION, 
            QAPI_COAP_OPTION_CONTENT_TYPE, 
            (unsigned char*)&content_type_code, 
            0) != 0){
            COAP_PRINTF("Set COAP_OPTION_CONTENT_TYPE error\n");
        }
    }
    
    tid = qapi_Net_Coap_Client_Send_Msg(pCoapClient->ctx, query, payload, payload_len, method, msgtype);
    if (tid == QAPI_COAP_INVALID_TID){
        goto COAP_CLIENT_ERROR;
    } 

    if(payload != NULL){
        free(payload);
        payload = NULL;
    }
    COAP_PRINTF("coap client %d start successfully!\n",pCoapClient->idx + 1);        
    return QCLI_STATUS_SUCCESS_E;

COAP_CLIENT_ERROR:
    COAP_PRINTF("coap client %d start failed!\n",pCoapClient->idx + 1);
    if(payload != NULL){
        free(payload);
        payload = NULL;
    }
    qapi_Net_Coap_Client_Free_Context(pCoapClient->ctx);
    
    coap_client_node_free(pCoapClient->idx, FALSE);

    return QCLI_STATUS_ERROR_E;
}


