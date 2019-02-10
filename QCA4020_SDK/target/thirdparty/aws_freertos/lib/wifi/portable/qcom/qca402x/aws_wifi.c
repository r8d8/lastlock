/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
 * All Rights Reserved.
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
 *
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/**
 * @file aws_WIFI.c
 * @brief Wi-Fi Interface.
 */

/* Amazon FreeRTOS include. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "aws_wifi.h"
#include "aws_secure_sockets.h"

/* QCOM Driver includes. */
//#include "wifi_common.h"
#include "qapi_wlan.h"
#include "qapi_wlan_base.h"
#include "semphr.h"
#include "qapi_ns_gen_v4.h"
#include "qapi_netservices.h"
#include "qapi_dnsc.h"
#include "qapi_fs.h"
#include "event_groups.h"

//#include "atheros_wifi.h"

#ifndef WLAN_NUM_OF_DEVICES
    #define WLAN_NUM_OF_DEVICES 2
#endif

#define AWS_WLAN_CONNECT_EVENT		0x1
#define AWS_WLAN_DHCP_EVENT			0x2
#define AWS_WLAN_DISCONNECT_EVENT	0x4
#define AWS_WLAN_HANDSHAKE_EVENT	0x8

static EventGroupHandle_t AWS_Wlan_Event = NULL;


/* Protect API */
static SemaphoreHandle_t g_wifi_semaph=NULL;
/* scan result*/
qapi_WLAN_BSS_Scan_Info_t scan_result[__QAPI_MAX_SCAN_RESULT_ENTRY] = {0};
qapi_WLAN_Scan_List_t scan_results;
volatile uint8_t wifi_state[2] = {0};
uint8_t g_bssid[2][__QAPI_WLAN_MAC_LEN] ={{0},{0}};


int active_device = 0, wlan_enabled = 0;
uint32_t deviceId = 1; /* Device ID 1 is specifically tied to station mode */
#define WLAN_INTERFACE 	"wlan1"
#define MSEC_TO_TICK(msec) ((1000L + ((uint32_t)configTICK_RATE_HZ * (uint32_t)(msec - 1U))) / 1000L)

static void ip_to_pxIPAddr(uint32_t ip, uint8_t *pxIPAddr)
{
    pxIPAddr[3] = (uint8_t)(ip >> 24);
    pxIPAddr[2] = (uint8_t)(ip >> 16);
    pxIPAddr[1] = (uint8_t)(ip >> 8);
    pxIPAddr[0] = (uint8_t)(ip);
}

static void pxIPAddr_to_ip(uint8_t *pxIPAddr, uint32_t *ip32)
{
    *ip32 = (((pxIPAddr[3]) & 0xFF) << 24) | \
            (((pxIPAddr[2]) & 0xFF) << 16) | \
            (((pxIPAddr[1]) & 0xFF) << 8) | \
            (((pxIPAddr[0]) & 0xFF));
}
/*
 * kpi_ipconfig_dhcpc_success_cb - A callback regsitered
 * with qapi dhcp api. This callback is called on a
 * successful dhcp completion for a client.
 */
static uint32_t wifi_dhcpc_ipaddr=0;
static int32_t wifi_dhcpc_success_cb(uint32_t addr, uint32_t mask, uint32_t gw)
{
	wifi_dhcpc_ipaddr = addr;
	xEventGroupSetBits( AWS_Wlan_Event, AWS_WLAN_DHCP_EVENT);
 
    return 0;
}

static WIFIReturnCode_t dhcp_GetIP()
{
    WIFIReturnCode_t status = eWiFiFailure;
	char *interface_name = WLAN_INTERFACE;
	uint32_t if_is_up = false;

	/* get dhcp IP address */
	if (qapi_Net_Interface_Exist(interface_name, &if_is_up) == false ||
			if_is_up == false)
	{
		qapi_Net_DHCPv4c_Release(interface_name);
	}
	do 
	{
		qapi_Net_DHCPv4c_Register_Success_Callback(interface_name, wifi_dhcpc_success_cb);

		qapi_Net_IPv4_Config(interface_name, QAPI_NET_IPV4CFG_DHCP_IP_E, NULL, NULL, NULL);

		/* Wait for callback, that is invoked from 'driver_task' context */
		status = eWiFiSuccess;
	} while(0);

    return status;
}

/* Invoked from 'driver_task', on SUCCESS post semaphore */
//qapi_WLAN_Connect_Cb_Info_t *cxnInfo;

static void aws_wlan_cb_handler(uint8_t devId, uint32_t cbId, void *pApplicationContext, void *payload, uint32_t payload_Length)
{
	uint8_t temp_bss[__QAPI_WLAN_MAC_LEN] ={0};

    switch(cbId)
	{

     /* indicates connection notification from the driver */
     case QAPI_WLAN_CONNECT_CB_E:  
     {
		 qapi_WLAN_Connect_Cb_Info_t *cxnInfo  = (qapi_WLAN_Connect_Cb_Info_t *)(payload);

         /* Implies the connection notification is for station mode */
         if((deviceId == devId) && (cxnInfo->value == 1)) {
		 	wifi_state[deviceId] = true;
			memcpy(g_bssid[deviceId],cxnInfo->mac_Addr,__QAPI_WLAN_MAC_LEN);
			/*configPRINTF(("connect event, bssconn=%d, mac %02x:%02x:%02x:%02x:%02x:%02x\n", 
				cxnInfo->bss_Connection_Status, cxnInfo->mac_Addr[0],cxnInfo->mac_Addr[1],
				cxnInfo->mac_Addr[2],cxnInfo->mac_Addr[3],cxnInfo->mac_Addr[4],cxnInfo->mac_Addr[5]));*/
			xEventGroupSetBits( AWS_Wlan_Event, AWS_WLAN_CONNECT_EVENT );
         }
		 else if(cxnInfo->value ==QAPI_WLAN_INVALID_PROFILE_E)
	 	 {
			wifi_state[deviceId] = false;
			/* some issue here: device is connected but the handshake failed */
			if (0 == qapi_WLAN_Disconnect(deviceId))
			{
				//In some scenaro print nothing.
				;//qcom_printf("disconnect error \n");
			}
			xEventGroupSetBits( AWS_Wlan_Event, AWS_WLAN_HANDSHAKE_EVENT);
	 	 }
		 else if(cxnInfo->value ==0x10)
	 	 {
			xEventGroupSetBits( AWS_Wlan_Event, AWS_WLAN_HANDSHAKE_EVENT);
	 	 }
		 else if(cxnInfo->value == 0)//disconnect event
	 	 {
			if (cxnInfo->bss_Connection_Status )
			{
				if((memcmp(cxnInfo->mac_Addr,temp_bss,__QAPI_WLAN_MAC_LEN) == 0) && (memcmp(g_bssid[devId],temp_bss,__QAPI_WLAN_MAC_LEN) != 0))
				{
				    wifi_state[deviceId] = false;;
				}
				else if((memcmp(g_bssid[devId],cxnInfo->mac_Addr,__QAPI_WLAN_MAC_LEN) == 0) 
					&& (memcmp(cxnInfo->mac_Addr,temp_bss,__QAPI_WLAN_MAC_LEN) != 0))
				{
					xEventGroupSetBits( AWS_Wlan_Event, AWS_WLAN_DISCONNECT_EVENT);
					wifi_state[deviceId] = false;
				}

			}
			
			memcpy(g_bssid[devId],temp_bss,__QAPI_WLAN_MAC_LEN);
	   
	 	 }
     }
     break;

	 case QAPI_WLAN_SCAN_COMPLETE_CB_E:
     {
        //qapi_WLAN_Scan_List_t scan_results;
        int32_t error = 0;
		qapi_WLAN_Scan_Status_t *pScanModeStatus = (qapi_WLAN_Scan_Status_t*)payload;
        uint16_t scan_Mode = pScanModeStatus->scan_Mode;
        
        if(scan_Mode == QAPI_WLAN_NO_BUFFERING_E)
        {
            return;
        }
        scan_results.num_Scan_Entries = __QAPI_MAX_SCAN_RESULT_ENTRY;
        error = qapi_WLAN_Get_Scan_Results(deviceId, (qapi_WLAN_BSS_Scan_Info_t *)(scan_results.scan_List), (int16_t *)&(scan_results.num_Scan_Entries));
        if (0 != error){
			return;
        }
        
		xEventGroupSetBits( AWS_Wlan_Event, AWS_WLAN_CONNECT_EVENT );
        return;
     }
	 //EVENT result print
	 case QAPI_WLAN_BSS_INFO_CB_E:
		break;      
     default:
         break;
    }

	return;
}
/* change between rec and perf modes */
uint32_t set_wlan_power_mode(uint32_t pwr_mode, uint8_t pwr_module)
{
    qapi_WLAN_Power_Mode_Params_t pwrMode;
    qapi_Status_t status;
    pwrMode.power_Mode = pwr_mode;
    pwrMode.power_Module = pwr_module;

    status = qapi_WLAN_Set_Param(0,
                               __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                               __QAPI_WLAN_PARAM_GROUP_WIRELESS_POWER_MODE_PARAMS,
                               (void *) &pwrMode,
                               sizeof(pwrMode),
                               false);

   if(status != QAPI_OK)
       return status;

   status = qapi_WLAN_Set_Param(deviceId,
                               __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                               __QAPI_WLAN_PARAM_GROUP_WIRELESS_POWER_MODE_PARAMS,
                               (void *) &pwrMode,
                               sizeof(pwrMode),
                               false);

   return status;
}

/**
 * @brief Initializes the Wi-Fi module.
 *
 * This function must be called exactly once before any other
 * Wi-Fi functions (including socket functions) can be used.
 *
 * @return eWiFiSuccess if everything succeeds, eWiFiFailure otherwise.
 */
 
WIFIReturnCode_t WIFI_On( void )
{
	if (wlan_enabled) {
		return 0;
	}

	if (0 == qapi_WLAN_Enable(QAPI_WLAN_ENABLE_E))
	{
		int i;
	
		/* Due to bugs in Iniche stack, the second device is created statically in
		 * MCC or SCC is enabled
		 */
		for(i=0;i < WLAN_NUM_OF_DEVICES;i++)
		{
			qapi_WLAN_Add_Device(i);
		}

		//set_callback(NULL);
		wlan_enabled = 1;

	}
	else 
		return eWiFiFailure;
	/* Create a on_connect semaphore, */
	if(g_wifi_semaph==NULL)
    	g_wifi_semaph = xSemaphoreCreateBinary();
    if (NULL == g_wifi_semaph)
        return eWiFiFailure;
    xSemaphoreGive(g_wifi_semaph);

	if(AWS_Wlan_Event==NULL)
		AWS_Wlan_Event = xEventGroupCreate();
	if (NULL == AWS_Wlan_Event)
	{
		configPRINTF(("AWS_Wlan_Event fail\n"));
		return eWiFiFailure;
	}
	
	return 0;
}


WIFIReturnCode_t WIFI_Off( void )
{
	int i;

	if (0 == wlan_enabled) {
		return 0;
	}

	/* Remove the WLAN device from network interface before disabling WLAN */
	for(i=0;i < WLAN_NUM_OF_DEVICES;i++)
	{
		qapi_WLAN_Remove_Device(i);
	}

	if (0 == qapi_WLAN_Enable(QAPI_WLAN_DISABLE_E))
	{
		wlan_enabled = 0;
		wifi_state[0] = 0;
		wifi_state[1] = 0;
		return 0;
	}
	return eWiFiSuccess;
}



/**
 * @brief Connects to Access Point.
 *
 * @param[in] pxNetworkParams Configuration to join AP.
 *
 * @return eWiFiSuccess if connection is successful, eWiFiFailure otherwise.
 */
WIFIReturnCode_t WIFI_ConnectAP( const WIFINetworkParams_t * const pxNetworkParams )
{
    WIFIReturnCode_t status = eWiFiFailure;
    const TickType_t xTimeout = pdMS_TO_TICKS( 20000UL );
	int32_t error;
	qapi_WLAN_Crypt_Type_e cipher;
	qapi_WLAN_Auth_Mode_e wpa_ver;
	EventBits_t uxBits=0;

    /* Check params */
    if((NULL==pxNetworkParams) || (NULL==pxNetworkParams->pcSSID))
	{
        return eWiFiFailure;
	}
	if((pxNetworkParams->xSecurity!=eWiFiSecurityOpen) && (NULL==pxNetworkParams->pcPassword))
	{
        return eWiFiFailure;
	}
	if(pxNetworkParams->pcSSID && (sizeof(pxNetworkParams->pcSSID)>wificonfigMAX_SSID_LEN))
	{
        return eWiFiFailure;
	}
	if(pxNetworkParams->pcPassword && (sizeof(pxNetworkParams->pcPassword)>wificonfigMAX_PASSPHRASE_LEN))
	{
        return eWiFiFailure;
	}

    /* Acquire semaphore */
    if (xSemaphoreTake(g_wifi_semaph, xTimeout) == pdTRUE)
    {
		/* Set connect_callback */
		//configPRINTF(("connect ap %s pwd=%s\n",pxNetworkParams->pcSSID, pxNetworkParams->pcPassword?pxNetworkParams->pcPassword:"none" ));
        do {
            /* Set Wi-Fi to device mode */
            qapi_WLAN_Dev_Mode_e opMode, wifimode;
            uint32_t dataLen;
            qapi_WLAN_Get_Param (deviceId, 
                                 __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                                 __QAPI_WLAN_PARAM_GROUP_WIRELESS_OPERATION_MODE,
                                 &wifimode,
                                 &dataLen);
			
  			if(wifi_state[deviceId])
			{
				xEventGroupClearBits(AWS_Wlan_Event, 0xf);
				/* Workaround: in aws_test_wifi.c, there's 2s delay in prvConnectionTask
                 * if thread 1 does connection, and after 2 sec it checks wifi_isconnected.
                 * And thread 2 does connection with AP2 and disconnects firstly. It may
                 * cause confilicts when thread 2 is in disconnect and wait connect event.
                 * Adds delay to let thread 1 runs status check completely.
				 */
				vTaskDelay(MSEC_TO_TICK(2000)); 
				qapi_WLAN_Disconnect(deviceId);
				uxBits = xEventGroupWaitBits(AWS_Wlan_Event, AWS_WLAN_DISCONNECT_EVENT, pdTRUE, pdFALSE, xTimeout);
				if(!(uxBits&AWS_WLAN_DISCONNECT_EVENT))
				{
				    break;
				}
				uxBits = 0;
            }
			qapi_WLAN_Set_Callback(deviceId, (qapi_WLAN_Callback_t)aws_wlan_cb_handler, NULL);
			
            opMode = QAPI_WLAN_DEV_MODE_STATION_E;
			if(wifimode!=opMode)
			{
				error = qapi_WLAN_Set_Param(deviceId, 
	                                __QAPI_WLAN_PARAM_GROUP_WIRELESS,
	                                __QAPI_WLAN_PARAM_GROUP_WIRELESS_OPERATION_MODE,
	                                &opMode,
	                                sizeof(qapi_WLAN_Dev_Mode_e),
	                                false);
				if (error != 0)
	    		{
			        break;
	    		}
        	}
            /* Set SSID, must be done before auth, cipher and passphrase */
			error = qapi_WLAN_Set_Param (deviceId,
                                 __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                                 __QAPI_WLAN_PARAM_GROUP_WIRELESS_SSID,
                                 (void *) pxNetworkParams->pcSSID,
                                 pxNetworkParams->ucSSIDLength,
                                 false);
			if (error != 0)
    		{
		        break;
    		}

			uint8_t bssidToConnect[__QAPI_WLAN_MAC_LEN] = {0};
			error = qapi_WLAN_Set_Param (deviceId,
                             __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                             __QAPI_WLAN_PARAM_GROUP_WIRELESS_BSSID,
                             bssidToConnect,
                             __QAPI_WLAN_MAC_LEN,
                             false);
			if (error != 0)
    		{
		        break;
    		}

			
			if (pxNetworkParams->xSecurity == eWiFiSecurityWEP) 
			{
				cipher = QAPI_WLAN_CRYPT_WEP_CRYPT_E;
				if ( 0 != qapi_WLAN_Set_Param(deviceId,
				                                 __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
				                                 __QAPI_WLAN_PARAM_GROUP_SECURITY_ENCRYPTION_TYPE,
				                                 &cipher,
				                                 sizeof(qapi_WLAN_Crypt_Type_e),
				                                 false))

				{
			        break;
				}
			} 
			else if(pxNetworkParams->xSecurity == eWiFiSecurityWPA || pxNetworkParams->xSecurity == eWiFiSecurityWPA2)
			{
				uint32_t passphraseLen = 0;
				cipher = QAPI_WLAN_CRYPT_AES_CRYPT_E; // QAPI_WLAN_CRYPT_TKIP_CRYPT_E

				if(0 != qapi_WLAN_Set_Param(deviceId,
				                               __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
				                               __QAPI_WLAN_PARAM_GROUP_SECURITY_ENCRYPTION_TYPE,
				                               (void *) &cipher, //cipher is set in set_wpa
				                               sizeof(qapi_WLAN_Crypt_Type_e), 
				                               false))
				{
					break;
				}

				if(pxNetworkParams->xSecurity == eWiFiSecurityWPA)
			    {
			       wpa_ver = QAPI_WLAN_AUTH_WPA_PSK_E;
			    }
			    else if(pxNetworkParams->xSecurity == eWiFiSecurityWPA2)
			    {
			       wpa_ver = QAPI_WLAN_AUTH_WPA2_PSK_E;
			    }

				if( 0 != qapi_WLAN_Set_Param (deviceId,
				                                __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
				                                __QAPI_WLAN_PARAM_GROUP_SECURITY_AUTH_MODE,
				                                (void *) &wpa_ver,
				                                sizeof(qapi_WLAN_Auth_Mode_e),
				                                false))
				{
					break;
				}
				passphraseLen  = pxNetworkParams->ucPasswordLength;
				if((passphraseLen >= 8) && (passphraseLen <= 63))
				{
				    if (0 != qapi_WLAN_Set_Param(deviceId,
				                                    __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
				                                    __QAPI_WLAN_PARAM_GROUP_SECURITY_PASSPHRASE,
				                                    pxNetworkParams->pcPassword,
				                                     passphraseLen,
				                                     false))
					{
					    break;
					}
				}
				else if(passphraseLen == 64)
				{
					if (0 != qapi_WLAN_Set_Param(deviceId,
					                                    __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
					                                    __QAPI_WLAN_PARAM_GROUP_SECURITY_PMK,
					                                    pxNetworkParams->pcPassword,
					                                    passphraseLen,
					                                    false))
					{
					    break;
					}
				}
				else
				{
					break;
				}
				
			}

            /* Commit settings to Wi-Fi module */
			error = qapi_WLAN_Commit(deviceId);
		    if(error != 0)
		    { 
		        break;
		    }
			
			if(pxNetworkParams->xSecurity == eWiFiSecurityOpen)
			{
				uxBits = xEventGroupWaitBits(AWS_Wlan_Event, AWS_WLAN_CONNECT_EVENT, pdTRUE, pdTRUE, xTimeout);
				if(!(uxBits&AWS_WLAN_CONNECT_EVENT))
	            {
					wifi_state[deviceId] = false;
	                break;
	        	}
			}
			else
			{
				uxBits = xEventGroupWaitBits(AWS_Wlan_Event, AWS_WLAN_CONNECT_EVENT|AWS_WLAN_HANDSHAKE_EVENT, pdTRUE, pdTRUE, xTimeout);
				if(!(uxBits&AWS_WLAN_CONNECT_EVENT))
				{
					break;
				}
				if(!(uxBits&AWS_WLAN_HANDSHAKE_EVENT))
				{
				    wifi_state[deviceId] = false;
					break;
				}
			}

            /* Remove callback ?? */
            /*
            if (A_OK != qcom_set_connect_callback(g_devid, NULL))
                break;
            */
            if(wifi_state[deviceId] == true) //connected event
        	{
	        	/* Everything is OK */
	        	status = eWiFiSuccess;
        	}
        } while (0);
		if(dhcp_GetIP()==eWiFiFailure)
		{
			//twice DHCP get IP to improve it
			dhcp_GetIP();
		}
		/* Wait for callback, that is invoked from 'driver_task' context */
		/* DHCP time may be more than 4 seconds */
		uxBits = xEventGroupWaitBits(AWS_Wlan_Event, AWS_WLAN_DHCP_EVENT, pdTRUE, pdFALSE, pdMS_TO_TICKS( 2500UL ));
		if(!(uxBits&AWS_WLAN_DHCP_EVENT))
		{
			//TODO: if no DHCP event, one more WAIT here!
    	}

        /* Release semaphore */
        xSemaphoreGive(g_wifi_semaph);
    }

    return status;
}

/**
 * @brief Retrieves the Wi-Fi interface's IP address.
 *
 * @param[in] IP Address buffer.
 *
 * @return eWiFiSuccess if everything succeeds, failure code otherwise.
 */
WIFIReturnCode_t WIFI_GetIP( uint8_t * pxIPAddr )
{
	const TickType_t xTimeout = pdMS_TO_TICKS( 10000UL );

    /* Check params */
    if (NULL == pxIPAddr)
	{
        return eWiFiFailure;
	}
	if (xSemaphoreTake(g_wifi_semaph, xTimeout) == pdTRUE)
	{
		dhcp_GetIP();

		/* Release semaphore */
        xSemaphoreGive(g_wifi_semaph);
	}
	ip_to_pxIPAddr(wifi_dhcpc_ipaddr, pxIPAddr);
	
    return eWiFiSuccess;
}

/**
 * @brief Retrieves the Wi-Fi interface's MAC address.
 *
 * @param[in] MAC Address buffer.
 *
 * @return eWiFiSuccess if everything succeeds, failure code otherwise.
 */
WIFIReturnCode_t WIFI_GetMAC( uint8_t * pxMac )
{
    WIFIReturnCode_t status = eWiFiFailure;
	char data[32+1] = {'\0'};
	uint32_t dataLen = 0;

    /* Check params */
    if (NULL == pxMac)
        return eWiFiFailure;

    /* Acquire semaphore */
    if (xSemaphoreTake(g_wifi_semaph, portMAX_DELAY) == pdTRUE)
    {
        do {
			if (0 != qapi_WLAN_Get_Param (deviceId, 
                         __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                         __QAPI_WLAN_PARAM_GROUP_WIRELESS_MAC_ADDRESS,
                         &data,
                         &dataLen))
                break;
            memcpy(pxMac, data, __QAPI_WLAN_MAC_LEN);
            status = eWiFiSuccess;
        } while (0);
        /* Release semaphore */
        xSemaphoreGive(g_wifi_semaph);
    }
    return status;
}

/**
 * @brief Disconnects from Access Point.
 *
 * @param[in] None.
 *
 * @return eWiFiSuccess if everything succeeds, failure code otherwise.
 */
WIFIReturnCode_t WIFI_Disconnect( void )
{
    WIFIReturnCode_t status = eWiFiFailure;
	EventBits_t uxBits=0;
	const TickType_t xTimeout = pdMS_TO_TICKS( 2000UL );

	if(wifi_state[deviceId] == false)
		return eWiFiSuccess;
	
    /* Acquire semaphore */
    if (xSemaphoreTake(g_wifi_semaph, pdMS_TO_TICKS(20000UL)) == pdTRUE)
    {
    	if(wifi_state[deviceId] == true)
		{
			qapi_WLAN_Set_Callback(deviceId, (qapi_WLAN_Callback_t)aws_wlan_cb_handler, NULL);
	        if (0 == qapi_WLAN_Disconnect(deviceId))
	    	{
	    		uxBits = xEventGroupWaitBits(AWS_Wlan_Event, AWS_WLAN_DISCONNECT_EVENT, pdTRUE, pdFALSE, xTimeout);
				if(!(uxBits&AWS_WLAN_DISCONNECT_EVENT))
				{
					if(wifi_state[deviceId] == false) //multi-thread only one disconnection EVENT
					{
						status = eWiFiSuccess;
					}
					else
					{
				    	status = eWiFiFailure;
					}
				}
				else
	            	status = eWiFiSuccess;
		        /* Release semaphore */
				wifi_state[deviceId] = false;
	    	}
		}
		else
		{
			status = eWiFiSuccess; //state is set by another thread
		}
        xSemaphoreGive(g_wifi_semaph);
    }
    return status;
}

int32_t wmi_set_scan(uint32_t dev_num, void *start_scan, qapi_WLAN_Store_Scan_Results_e store_scan_results)
{
    int32_t error = 0;
    
	qapi_WLAN_Set_Callback(deviceId, (qapi_WLAN_Callback_t)aws_wlan_cb_handler, NULL);
    {
        qapi_WLAN_Store_Scan_Results_e storeScanResults = (qapi_WLAN_Store_Scan_Results_e) store_scan_results; //QAPI_WLAN_BUFFER_SCAN_RESULTS_BLOCKING_E;
        error = qapi_WLAN_Start_Scan(dev_num, (qapi_WLAN_Start_Scan_Params_t *) start_scan, storeScanResults); 
        if (0 != error)
        {
            return error;
        }

        if((store_scan_results == QAPI_WLAN_BUFFER_SCAN_RESULTS_NON_BLOCKING_E) || (store_scan_results == QAPI_WLAN_NO_BUFFERING_E))
            return error;
		scan_results.scan_List = scan_result;
		scan_results.num_Scan_Entries = __QAPI_MAX_SCAN_RESULT_ENTRY;
        error = qapi_WLAN_Get_Scan_Results(deviceId, (qapi_WLAN_BSS_Scan_Info_t *)(scan_results.scan_List), (int16_t *)&(scan_results.num_Scan_Entries));

		if (0 != error)
        {
			return error;
        }

    } 
	xEventGroupSetBits( AWS_Wlan_Event, AWS_WLAN_CONNECT_EVENT);
    return error;
}

/**
 * @brief Perform WiF Scan
 *
 * @param[in] pxBuffer - Buffer for scan results.
 * @param[in] uxNumNetworks - Number of networks in scan result.
 *
 * @return eWiFiSuccess if everything succeeds, failure code otherwise.
 */
WIFIReturnCode_t WIFI_Scan( WIFIScanResult_t * pxBuffer,
                                       uint8_t uxNumNetworks )
{
    WIFIReturnCode_t status = eWiFiFailure;
    int16_t scan_result_num = __QAPI_MAX_SCAN_RESULT_ENTRY;
	int32_t error = 0;
	char *ssid = "";
	const TickType_t xTimeout = pdMS_TO_TICKS( 10000UL );
	EventBits_t uxBits=0;

    /* Check params */
    if ((NULL == pxBuffer) || (0 == uxNumNetworks))
        return eWiFiFailure;

    /* Acquire semaphore */
    if (xSemaphoreTake(g_wifi_semaph, portMAX_DELAY) == pdTRUE)
    {
        do {
			/* TODO: check if SSID should be store/revert if sta connected AP */
	        error = qapi_WLAN_Set_Param (deviceId,
	                                     __QAPI_WLAN_PARAM_GROUP_WIRELESS,
	                                     __QAPI_WLAN_PARAM_GROUP_WIRELESS_SSID,
	                                     (void *) ssid,
	                                     strlen(ssid),
	                                     false);
			if(error != 0)
				return status;

			/*Do the actual scan*/
			/* scan_mode=0 means BLOCKING in driver*/
    		wmi_set_scan(deviceId, NULL, QAPI_WLAN_BUFFER_SCAN_RESULTS_BLOCKING_E);

			uxBits = xEventGroupWaitBits(AWS_Wlan_Event, AWS_WLAN_CONNECT_EVENT, pdTRUE, pdFALSE, xTimeout);
			if(!(uxBits&AWS_WLAN_CONNECT_EVENT))
			{
				xSemaphoreGive(g_wifi_semaph);
		        return eWiFiFailure;
	    	}
		
            /* Get MIN(scan_result_num, uxNumNetworks) */
            if (scan_result_num > (int16_t)uxNumNetworks)
                scan_result_num = (int16_t)uxNumNetworks;
            for (int16_t i  = 0 ; i < scan_result_num; i++)
            {
                strncpy((char*)pxBuffer->cSSID, (char const*)scan_result[i].ssid, wificonfigMAX_SSID_LEN);
                strncpy((char*)pxBuffer->ucBSSID, (char const*)scan_result[i].bssid, wificonfigMAX_BSSID_LEN);
                pxBuffer->cRSSI = scan_result[i].rssi;
                pxBuffer->cChannel = scan_result[i].channel;
                pxBuffer->ucHidden = 0;
                if (!scan_result[i].security_Enabled)
                {
                    pxBuffer->xSecurity = eWiFiSecurityOpen;
                }
                else
            	{
					if ((0 == scan_result[i].rsn_Cipher) ||
                    (__QAPI_WLAN_CIPHER_TYPE_WEP & scan_result[i].rsn_Cipher))
	                {
	                    pxBuffer->xSecurity = eWiFiSecurityWEP;
	                }
	                else if (__QAPI_WLAN_CIPHER_TYPE_CCMP & scan_result[i].rsn_Cipher)
	                {
	                    pxBuffer->xSecurity = eWiFiSecurityWPA2;
	                }
	                else
	                {
	                    /* TODO: Expect WPA */
	                    pxBuffer->xSecurity = eWiFiSecurityWPA;
	                }
            	}
#if 0
                PRINTF("-----------------------\r\n");
                PRINTF("channel: %d \r\n", scan_result[i].channel);
                PRINTF("ssid_len: %d \r\n", scan_result[i].ssid_len);
                PRINTF("rssi: %d \r\n", scan_result[i].rssi);
                PRINTF("security_enabled: %d \r\n", scan_result[i].security_enabled);
                PRINTF("beacon_period: %d \r\n", scan_result[i].beacon_period);
                PRINTF("preamble: %d \r\n", scan_result[i].preamble);
                PRINTF("bss_type: %d \r\n", scan_result[i].bss_type);
                PRINTF("bssid: %x%x%x%x%x%x \r\n",
                    scan_result[i].bssid[0],
                    scan_result[i].bssid[1],
                    scan_result[i].bssid[2],
                    scan_result[i].bssid[3],
                    scan_result[i].bssid[4],
                    scan_result[i].bssid[5]
                );
                PRINTF("ssid: %s \r\n", scan_result[i].ssid);
                PRINTF("rsn_cipher: %d \r\n", scan_result[i].rsn_cipher);
                PRINTF("rsn_auth: %d \r\n", scan_result[i].rsn_auth);
                PRINTF("wpa_cipher: %d \r\n", scan_result[i].wpa_cipher);
                PRINTF("wpa_auth: %d \r\n", scan_result[i].wpa_auth);
#endif

                pxBuffer += 1;
            }
            status = eWiFiSuccess;
        } while (0);
        /* Release semaphore */
        xSemaphoreGive(g_wifi_semaph);
    }
    return status;
}

/**
 * @brief Retrieves host IP address from URL using DNS
 *
 * @param[in] pxHost - Host URL.
 * @param[in] pxIPAddr - IP Address buffer.
 *
 * @return eWiFiSuccess if everything succeeds, failure code otherwise.
 */

WIFIReturnCode_t WIFI_GetHostIP( char * pxHost,
                                            uint8_t * pxIPAddr )
{
    WIFIReturnCode_t status = eWiFiFailure;
    char ip_str[20];

    /* Check params */
    if ((NULL == pxIPAddr) || (NULL == pxHost))
        return eWiFiFailure;

    /* Acquire semaphore */
    if (xSemaphoreTake(g_wifi_semaph, portMAX_DELAY) == pdTRUE)
    {
        do {
            struct qapi_hostent_s * he;
            //Start DNS
            qapi_Net_DNSc_Command(QAPI_NET_DNS_START_E);


            he = qapi_Net_DNSc_Get_Host_By_Name(pxHost);
            if(he == NULL){
                xSemaphoreGive(g_wifi_semaph);
                qapi_Net_DNSc_Command(QAPI_NET_DNS_STOP_E);
                return eWiFiFailure;
            }
            else
            {
                while (*(he->h_addr_list) != NULL)
                {
                    inet_ntop(AF_INET, *(he->h_addr_list), ip_str, sizeof(ip_str));
                    ++(he->h_addr_list);
                }
                inet_pton(AF_INET, ip_str, pxIPAddr);
				
                status = eWiFiSuccess;
            }

        } while(0);
        /* Release semaphore */
        xSemaphoreGive(g_wifi_semaph);
        qapi_Net_DNSc_Command(QAPI_NET_DNS_STOP_E);
    }

    return status;
}

BaseType_t WIFI_IsConnected( void )
{
    BaseType_t xIsConnected = pdFALSE;
    xIsConnected = wifi_state[deviceId];
	
    return xIsConnected;
}

/**
 * @brief Configure SoftAP
 *
 * @param[in] pxNetworkParams - Network params to configure AP.
 *
 * @return eWiFiSuccess if everything succeeds, failure code otherwise.
 */
WIFIReturnCode_t WIFI_ConfigureAP(const WIFINetworkParams_t * const pxNetworkParams )
{
    WIFIReturnCode_t status = eWiFiFailure;
    const TickType_t xTimeout = pdMS_TO_TICKS( 10000UL );
	int32_t error;
	qapi_WLAN_Crypt_Type_e cipher;
	qapi_WLAN_Auth_Mode_e wpa_ver;
	EventBits_t uxBits=0;

    /* Check params */
    if (NULL == pxNetworkParams || NULL == pxNetworkParams->pcSSID)
        return eWiFiFailure;

    /* Acquire semaphore */
    if (xSemaphoreTake(g_wifi_semaph, portMAX_DELAY) == pdTRUE)
    {
        do {
            /* Set Wi-Fi to device mode */
            {
                qapi_WLAN_Dev_Mode_e opMode, wifimode;
                uint32_t dataLen;
                qapi_WLAN_Get_Param (deviceId, 
                                     __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                                     __QAPI_WLAN_PARAM_GROUP_WIRELESS_OPERATION_MODE,
                                     &wifimode,
                                     &dataLen);
                if (wifimode == QAPI_WLAN_DEV_MODE_AP_E) /*check previous mode*/
                {
                   qapi_WLAN_Disconnect(deviceId);
                    /* AP Mode is always set to maxper; if we are switching mode and prev mode is QAPI_WLAN_POWER_MODE_REC_POWER_E then
                       retain the power mode for STA */
                    
                   set_wlan_power_mode( QAPI_WLAN_POWER_MODE_REC_POWER_E, QAPI_WLAN_POWER_MODULE_SOFTAP_E);
                }
                opMode = QAPI_WLAN_DEV_MODE_AP_E;
                if (0 == qapi_WLAN_Set_Param(deviceId, 
                                    __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                                    __QAPI_WLAN_PARAM_GROUP_WIRELESS_OPERATION_MODE,
                                    &opMode,
                                    sizeof(qapi_WLAN_Dev_Mode_e),
                                    false))
                //TODO: ditinguish succeed/fail event.
                   ;
                else
                    ;
            }
			//if(pxNetworkParams->xSecurity == eWiFiSecurityOpen)
			{
	            /* Set SSID, must be done before auth, cipher and passphrase */
				error = qapi_WLAN_Set_Param (deviceId,
	                                 __QAPI_WLAN_PARAM_GROUP_WIRELESS,
	                                 __QAPI_WLAN_PARAM_GROUP_WIRELESS_SSID,
	                                 (void *) pxNetworkParams->pcSSID,
	                                 pxNetworkParams->ucSSIDLength,
	                                 false);
				if (error != 0)
	    		{
			        break;
	    		}
			}
			if (pxNetworkParams->xSecurity == eWiFiSecurityWEP) 
			{
				cipher = QAPI_WLAN_CRYPT_WEP_CRYPT_E;
				if ( 0 != qapi_WLAN_Set_Param(deviceId,
				                                 __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
				                                 __QAPI_WLAN_PARAM_GROUP_SECURITY_ENCRYPTION_TYPE,
				                                 &cipher,
				                                 sizeof(qapi_WLAN_Crypt_Type_e),
				                                 false))

				{
			        break;
				}
			} 
			else if(pxNetworkParams->xSecurity == eWiFiSecurityWPA || pxNetworkParams->xSecurity == eWiFiSecurityWPA2)
			{
				uint32_t passphraseLen = 0;
				cipher = QAPI_WLAN_CRYPT_AES_CRYPT_E; //QAPI_WLAN_CRYPT_TKIP_CRYPT_E is for TKIP, QAPI_WLAN_CRYPT_AES_CRYPT_E is for CCMP

				if(0 != qapi_WLAN_Set_Param(deviceId,
				                               __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
				                               __QAPI_WLAN_PARAM_GROUP_SECURITY_ENCRYPTION_TYPE,
				                               (void *) &cipher, //cipher is set in set_wpa
				                               sizeof(qapi_WLAN_Crypt_Type_e), 
				                               false))
				{
					break;
				}

				if(pxNetworkParams->xSecurity == eWiFiSecurityWPA)
			    {
			       wpa_ver = QAPI_WLAN_AUTH_WPA_PSK_E;
			    }
			    else if(pxNetworkParams->xSecurity == eWiFiSecurityWPA2)
			    {
			       wpa_ver = QAPI_WLAN_AUTH_WPA2_PSK_E;
			    }

				if( 0 != qapi_WLAN_Set_Param (deviceId,
				                                __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
				                                __QAPI_WLAN_PARAM_GROUP_SECURITY_AUTH_MODE,
				                                (void *) &wpa_ver,
				                                sizeof(qapi_WLAN_Auth_Mode_e),
				                                false))
				{
					break;
				}
				passphraseLen  = pxNetworkParams->ucPasswordLength;
				if((passphraseLen >= 8) && (passphraseLen <= 63))
				{
				    if (0 != qapi_WLAN_Set_Param(deviceId,
				                                    __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
				                                    __QAPI_WLAN_PARAM_GROUP_SECURITY_PASSPHRASE,
				                                    pxNetworkParams->pcPassword,
				                                     passphraseLen,
				                                     false))
				{
				    break;
				}
				//pmk_flag[deviceId] = 1;
				}
				else if(passphraseLen == 64)
				{
				if (0 != qapi_WLAN_Set_Param(deviceId,
				                                    __QAPI_WLAN_PARAM_GROUP_WIRELESS_SECURITY,
				                                    __QAPI_WLAN_PARAM_GROUP_SECURITY_PMK,
				                                    pxNetworkParams->pcPassword,
				                                    passphraseLen,
				                                    false))
				{
				    //QCLI_Printf(qcli_wlan_group, "Unable to set pmk\r\n");
				    break;
				}
				//pmk_flag[deviceId] = 1;
				}
				else
				{
					//QCLI_Printf(qcli_wlan_group, "invalid password\r\n");
					break;
				}
				
			}
            /* Set connect_callback */
            qapi_WLAN_Set_Callback(deviceId, (qapi_WLAN_Callback_t)aws_wlan_cb_handler, NULL);

            /* Commit settings to Wi-Fi module */
			error = qapi_WLAN_Commit(deviceId);
		    if(error != 0)
		    { 
		        break;
		    }

            /* Wait for callback, that is invoked from 'driver_task' context */
			uxBits = xEventGroupWaitBits(AWS_Wlan_Event, AWS_WLAN_CONNECT_EVENT, pdTRUE, pdFALSE, xTimeout);
			if(!(uxBits&AWS_WLAN_CONNECT_EVENT))
			{
                break;
            }

            /* Remove callback ?? */
            /*
            if (A_OK != qcom_set_connect_callback(g_devid, NULL))
                break;
            */
            /* Everything is OK */
            status = eWiFiSuccess;
        } while (0);

        /* Release semaphore */
        xSemaphoreGive(g_wifi_semaph);
		//xSemaphoreGive(g_connect_semaph);
    }
    return status;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_Reset( void )
{
        WIFIReturnCode_t ret;
	
        WIFI_Off();
        ret = WIFI_On();
	
        return ret;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_SetMode( WIFIDeviceMode_t xDeviceMode )
{
	qapi_WLAN_Dev_Mode_e opMode;

	if(xDeviceMode == eWiFiModeAP)
		opMode = QAPI_WLAN_DEV_MODE_AP_E;
	else if (xDeviceMode == eWiFiModeStation)
		opMode = QAPI_WLAN_DEV_MODE_STATION_E;
	else if (xDeviceMode == eWiFiModeP2P)
		opMode = QAPI_WLAN_DEV_MODE_STATION_E; //TODO :
	else
		return eWiFiFailure; //wrong mode
                    
    if (0 != qapi_WLAN_Set_Param(deviceId, 
                        __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                        __QAPI_WLAN_PARAM_GROUP_WIRELESS_OPERATION_MODE,
                        &opMode,
                        sizeof(qapi_WLAN_Dev_Mode_e),
                        false))
    {
        return eWiFiNotSupported;
    }
				
    return eWiFiSuccess;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetMode( WIFIDeviceMode_t * pxDeviceMode )
{
	uint32_t mode = 0, dataLen = 0;

	if(!pxDeviceMode)
	{
		return eWiFiFailure;
	}

    if (0 != qapi_WLAN_Get_Param (deviceId, 
                         __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                         __QAPI_WLAN_PARAM_GROUP_WIRELESS_OPERATION_MODE,
                         &mode,
                         &dataLen))
    {
        return eWiFiNotSupported;
    }
	
	*pxDeviceMode = mode;
    return eWiFiSuccess;
}

#define WLAN_NETWORK_FILE                "/spinor/amz_network.txt"
#define NETWORK_PROFILE_SIZE			128
#define PROFILE_LABEL					0x5a5a
typedef struct {
	short index;
	short label;
	uint8_t data[NETWORK_PROFILE_SIZE];
}wifiNetworkFile_t;
wifiNetworkFile_t fileData = {0};
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_NetworkAdd( const WIFINetworkProfile_t * const pxNetworkProfile,
                                  uint16_t * pusIndex )
{
	int ret=0;
	int fd=0;
	int32_t unused;
	uint32_t bytes_written=0, bytes_read=0;
	int offset=0;
	int status = eWiFiSuccess;
	
	if((NULL == pxNetworkProfile) || (NULL == pusIndex))
		return eWiFiFailure;

	ret = qapi_Fs_Open(WLAN_NETWORK_FILE, QAPI_FS_O_RDWR | QAPI_FS_O_CREAT, &fd);
	if (ret != QAPI_OK)
    {
        return eWiFiFailure;
    }

	while(1)
	{
		ret = qapi_Fs_Read(fd, (uint8_t *)(&fileData), sizeof(wifiNetworkFile_t), &bytes_read);
		if(ret!= QAPI_OK)
		{
	        break;
	    }
		offset += sizeof(wifiNetworkFile_t);

		if(bytes_read==0) //end of file
			break;

		if(fileData.index == (*pusIndex) && fileData.label == PROFILE_LABEL)
		{
			break;
		}
	}

	if(fileData.index == (*pusIndex) && fileData.label == PROFILE_LABEL)
	{
		/* if find index in exist file data, we need re-locate the FD offset*/
		ret = qapi_Fs_Lseek(fd, offset-sizeof(wifiNetworkFile_t), QAPI_FS_SEEK_SET, &unused);
	}
	
	fileData.index = (*pusIndex);
	fileData.label = PROFILE_LABEL;
	memcpy(fileData.data, pxNetworkProfile, sizeof(WIFINetworkProfile_t));
	ret = qapi_Fs_Write(fd, (uint8_t *)(&fileData), sizeof(wifiNetworkFile_t), &bytes_written);
	if(ret!= QAPI_OK || (bytes_written != sizeof(wifiNetworkFile_t)))
	{
		status = eWiFiFailure;
	}
	else
	{
		status = eWiFiSuccess;
	}
	
	qapi_Fs_Close(fd);
    return status;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_NetworkGet( WIFINetworkProfile_t * pxNetworkProfile,
                                  uint16_t usIndex )
{
	int ret=0;
	int fd=0;
	uint32_t bytes_read=0;
	int status = eWiFiSuccess;

	if(pxNetworkProfile == NULL)
		return eWiFiFailure;
	if(usIndex>100) //sync with testwifiMAX_NETWORK_SAVE_NUMBER
		return eWiFiFailure;

	ret = qapi_Fs_Open(WLAN_NETWORK_FILE, QAPI_FS_O_RDONLY, &fd);
	if (ret != QAPI_OK)
	{
		return eWiFiFailure;
	}
	memset(fileData.data, 0, sizeof(wifiNetworkFile_t));

	while(1)
	{
		ret = qapi_Fs_Read(fd, (uint8_t *)(&fileData), sizeof(wifiNetworkFile_t), &bytes_read);
		if(ret!= QAPI_OK)
		{
	        break;
	    }
		
		if(bytes_read==0) //end of file
			break;

		if((fileData.index == usIndex) && (fileData.label == PROFILE_LABEL))
		{
			break;
		}
		
	}
	
	if((fileData.index == usIndex) && (fileData.label == PROFILE_LABEL))
	{
		memcpy(pxNetworkProfile, fileData.data, sizeof(WIFINetworkProfile_t));
	}
	else
	{
		status = eWiFiFailure;
	}
	
	qapi_Fs_Close(fd);
	
    return status;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_NetworkDelete( uint16_t usIndex )
{
	int ret=0;
	int fd=0;
	int32_t unused;
	uint32_t bytes_written=0;
	uint32_t bytes_read=0;
	uint32_t offset=0;	
	int status = eWiFiSuccess;

	ret = qapi_Fs_Open(WLAN_NETWORK_FILE, QAPI_FS_O_RDWR, &fd);
	if (ret != QAPI_OK)
	{
		return eWiFiSuccess; //no such file
	}

	while(1)
	{
		ret = qapi_Fs_Read(fd, (uint8_t *)(&fileData), sizeof(wifiNetworkFile_t), &bytes_read);
		if(ret!= QAPI_OK)
		{
	        break;
	    }
		offset += sizeof(wifiNetworkFile_t);
		
		if(bytes_read==0) //end of file
			break;

		if((fileData.index == usIndex) && (fileData.label == PROFILE_LABEL))
		{
			break;
		}
	}
	if((fileData.index == usIndex) && (fileData.label == PROFILE_LABEL))
	{
		memset(fileData.data, 0, sizeof(WIFINetworkProfile_t));
		fileData.index = 0;
		fileData.label = 0;

		ret = qapi_Fs_Lseek(fd, offset-sizeof(wifiNetworkFile_t), QAPI_FS_SEEK_SET, &unused);
		
		ret = qapi_Fs_Write(fd, (uint8_t *)(&fileData), sizeof(wifiNetworkFile_t), &bytes_written);
		if(ret!= QAPI_OK || (bytes_written != sizeof(wifiNetworkFile_t)))
		{
			status = eWiFiFailure;
		}
	}
	else
	{
		status = eWiFiSuccess;
	}
	qapi_Fs_Close(fd);
	
	return status;
}
/*-----------------------------------------------------------*/
WIFIReturnCode_t WIFI_Ping( uint8_t * pucIPAddr,
                            uint16_t usCount,
                            uint32_t ulIntervalMS )
{
    int e;
	int failed_cnt = 0;
	uint32_t ip4_addr = 0;

	if(WIFI_IsConnected()==false)
	{
		/*If wifi is not connected we mark it as not supported. test case should do connection */
		return eWiFiNotSupported;
	}
		
	if(NULL == pucIPAddr)
		return eWiFiFailure;

	pxIPAddr_to_ip(pucIPAddr, &ip4_addr);
	for(int i=0; i<usCount; i++)
	{
		e = qapi_Net_Ping(ip4_addr, 64); //size should <1576
		if(e == 0)
		{
			vTaskDelay(MSEC_TO_TICK(500)); //TODO check ulIntervalMS
		}
		else
			failed_cnt++;
	}
	return failed_cnt == usCount ? eWiFiFailure : eWiFiSuccess;
}
/*-----------------------------------------------------------*/
/*Amazon power mode has 3 states, we made some temp value to restore it for qualification program*/
static int wifi_pwrmode=0;
WIFIReturnCode_t WIFI_SetPMMode( WIFIPMMode_t xPMModeType,
                                 const void * pvOptionValue )
{
	qapi_WLAN_Power_Mode_Params_t pwrMode;

	if(NULL == pvOptionValue)
		return eWiFiFailure;
	if(xPMModeType == eWiFiPMNotSupported)
		return eWiFiFailure;
	if((xPMModeType == eWiFiPMNormal) || (xPMModeType == eWiFiPMAlwaysOn))
	{
		wifi_pwrmode = xPMModeType;
		pwrMode.power_Mode = QAPI_WLAN_POWER_MODE_MAX_PERF_E;
	}
	else
		pwrMode.power_Mode = QAPI_WLAN_POWER_MODE_REC_POWER_E;

    pwrMode.power_Module = QAPI_WLAN_POWER_MODULE_USER_E;
    return qapi_WLAN_Set_Param (deviceId,
                               __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                               __QAPI_WLAN_PARAM_GROUP_WIRELESS_POWER_MODE_PARAMS,
                               (void *) &pwrMode,
                               sizeof(pwrMode),
                               false);
    return eWiFiSuccess;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetPMMode( WIFIPMMode_t * pxPMModeType,
                                 void * pvOptionValue )
{
	uint32_t mode = 0, dataLen = 0;

	if((NULL == pxPMModeType) || (NULL == pvOptionValue))
		return eWiFiFailure;
	if (0 != qapi_WLAN_Get_Param (deviceId, 
                         __QAPI_WLAN_PARAM_GROUP_WIRELESS,
                         __QAPI_WLAN_PARAM_GROUP_WIRELESS_POWER_MODE_PARAMS,
                         &mode,
                         &dataLen))
    {
        return eWiFiFailure;
	}
	if(mode == QAPI_WLAN_POWER_MODE_MAX_PERF_E)
	{
		/*The test should run WIFI_SetPMMode firstly to store value in wifi_pwrmode, Or we return eWiFiPMNormal*/
		if(wifi_pwrmode==eWiFiPMNormal || wifi_pwrmode==eWiFiPMAlwaysOn)
			*pxPMModeType = wifi_pwrmode;
		else
			*pxPMModeType = eWiFiPMNormal;
	}
	else
	{
		*pxPMModeType = eWiFiPMLowPower;
	}
    return eWiFiSuccess;
}
/*-----------------------------------------------------------*/


