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

/*
 * Amazon FreeRTOS V1.2.6
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////

/* SDK Included Files */
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"

#include "portmacro.h"
/* Amazon FreeRTOS Demo Includes */
//#include "aws_clientcredential.h"
#include "aws_logging_task.h"
#include "aws_system_init.h"
#include "aws_demo_runner.h"
#include "aws_dev_mode_key_provisioning.h"
#include "aws_wifi.h"
#include "aws_clientcredential.h"
#include "qcom_code/pal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define mainLOGGING_TASK_PRIORITY       (tskIDLE_PRIORITY)
#define mainLOGGING_TASK_STACK_SIZE     (configMINIMAL_STACK_SIZE * 4)
#define mainLOGGING_QUEUE_LENGTH        (16)
#define mainLOGGING_MESSAGE_QUEUE_LENGTH    ( 32 )
/* Unit test defines. */
#define mainTEST_RUNNER_TASK_STACK_SIZE     ( configMINIMAL_STACK_SIZE * 16 )

/* The task delay for allowing the lower priority logging task to print out Wi-Fi 
 * failure status before blocking indefinitely. */
#define mainLOGGING_WIFI_STATUS_DELAY   pdMS_TO_TICKS( 1000 )

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void prvWifiConnect( void );
extern void app_init_func(uint32_t ColdBoot);
extern void app_start_func(uint32_t ColdBoot);


extern void * qcli_test_group;
extern bool g_sleepAllowLowPowerModes;


/*******************************************************************************
 * Code
 ******************************************************************************/
#if 0
int main(void)
{
	/* Perform any hardware initialization that does not require the RTOS to be
	 * running.  */
	prvMiscInitialization();
		/* Create tasks that are not dependent on the WiFi being initialized. */
	xLoggingTaskInitialize( mainLOGGING_TASK_STACK_SIZE,
							tskIDLE_PRIORITY + 5,
							mainLOGGING_MESSAGE_QUEUE_LENGTH );
	FreeRTOS_IPInit( ucIPAddress,
			ucNetMask,
			ucGatewayAddress,
			ucDNSServerAddress,
			ucMACAddress );

	/* Start the scheduler.  Initialization that requires the OS to be running,
	 * including the WiFi initialization, is performed in the RTOS daemon task
	 * startup hook. */
	// Following is taken care by initialization code in ESP IDF
	// vTaskStartScheduler();

	return 0;
}
#endif
/*-----------------------------------------------------------*/
/**
 * @brief Initializes the board.
 */
static void prvMiscInitialization( void );


/**
   @brief Function call to initialize the application.
*/
void app_init(uint32_t ColdBoot)
{
#if 0
/* Perform any hardware initialization that does not require the RTOS to be
	 * running.  */
	prvMiscInitialization();
		/* Create tasks that are not dependent on the WiFi being initialized. */
	xLoggingTaskInitialize( mainLOGGING_TASK_STACK_SIZE,
							tskIDLE_PRIORITY + 5,
							mainLOGGING_MESSAGE_QUEUE_LENGTH );
#else		
	g_sleepAllowLowPowerModes = 0;

	app_init_func(ColdBoot);

	prvMiscInitialization();
	xLoggingTaskInitialize( mainLOGGING_TASK_STACK_SIZE,
							tskIDLE_PRIORITY + 5,
							mainLOGGING_MESSAGE_QUEUE_LENGTH );

	//vTaskStartScheduler();


#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
//test code
#endif

#endif   
}

/**
   @brief Main entry point of the application.
*/

void app_start(uint32_t ColdBoot)
{
	//app_start_func(ColdBoot);
	//if( SYSTEM_Init() == pdPASS )
    {
        prvWifiConnect();

        //DEMO_RUNNER_RunDemos();

#if 0
		
		/* Create the task to run unit tests. */
		xTaskCreate( TEST_RUNNER_RunTests_task,
					 "RunTests_task",
					 mainTEST_RUNNER_TASK_STACK_SIZE,
					 NULL,
					 tskIDLE_PRIORITY,
					 NULL );
#endif /* if 0 */
    }
}

static void prvMiscInitialization( void )
{
}

void vApplicationDaemonTaskStartupHook( void )
{
    /* A simple example to demonstrate key and certificate provisioning in
     * microcontroller flash using PKCS#11 interface. This should be replaced
     * by production ready key provisioning mechanism. */
    vDevModeKeyProvisioning();
  
    if( SYSTEM_Init() == pdPASS )
    {
        prvWifiConnect();

        DEMO_RUNNER_RunDemos();

#if 0
		
		/* Create the task to run unit tests. */
		xTaskCreate( TEST_RUNNER_RunTests_task,
					 "RunTests_task",
					 4096/*mainTEST_RUNNER_TASK_STACK_SIZE*/,
					 NULL,
					 tskIDLE_PRIORITY,
					 NULL );
#endif /* if 0 */
    }
}

/*-----------------------------------------------------------*/
uint8_t ucTempIp[4];

static void prvWifiConnect( void )
{
	WIFINetworkParams_t xNetworkParams;
	WIFIReturnCode_t xWifiStatus;
	WIFIScanResult_t *xWifiScanResults;
	uint32_t scanNum=12;

	/* Setup WiFi parameters to connect to access point. */
	xNetworkParams.pcSSID = clientcredentialWIFI_SSID;
	xNetworkParams.ucSSIDLength = sizeof( clientcredentialWIFI_SSID );
	xNetworkParams.pcPassword = clientcredentialWIFI_PASSWORD;
	xNetworkParams.ucPasswordLength = sizeof( clientcredentialWIFI_PASSWORD )-1;
	xNetworkParams.xSecurity = clientcredentialWIFI_SECURITY;
	xNetworkParams.cChannel = 0;
	vTaskDelay( mainLOGGING_WIFI_STATUS_DELAY );
	configPRINTF( ( "Starting Wi-Fi...\r\n" ) );

	xWifiStatus = WIFI_On();
	if( xWifiStatus == eWiFiSuccess )
	{
		configPRINTF( ("Wi-Fi module initialized. Connecting to AP... %s\r\n", xNetworkParams.pcSSID) );
	}
	else
	{
		configPRINTF( ( "Wi-Fi module failed to initialize.\r\n" ) );
		
		/* Delay to allow the lower priority logging task to print the above status. */
		vTaskDelay( mainLOGGING_WIFI_STATUS_DELAY );

		while( 1 )
		{
		}
	}
#if 1
	int ii=0;
	char securityMode[8] = {0};
	xWifiScanResults = malloc((sizeof(WIFIScanResult_t) * scanNum));
	WIFI_Scan(xWifiScanResults, scanNum);

	configPRINTF( ("configPrint : scanNum = %d\r\n", scanNum) );
	for (ii=0;ii<scanNum;ii++)
	{
		configPRINTF( ("===========%d============\r\n", ii) );
		configPRINTF( (" ssid = %s\r\n", (xWifiScanResults+ii)->cSSID) );
		configPRINTF( (" bssid = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\r\n", 
			(xWifiScanResults+ii)->ucBSSID[0], (xWifiScanResults+ii)->ucBSSID[1],
			(xWifiScanResults+ii)->ucBSSID[2], (xWifiScanResults+ii)->ucBSSID[3],
			(xWifiScanResults+ii)->ucBSSID[4], (xWifiScanResults+ii)->ucBSSID[5]) );
		configPRINTF( (" channel = %d\r\n", (xWifiScanResults+ii)->cChannel) );
		if((xWifiScanResults+ii)->xSecurity == eWiFiSecurityOpen)
			strncpy(securityMode, "open", sizeof(securityMode)-1);
		else if((xWifiScanResults+ii)->xSecurity == eWiFiSecurityWEP)
			strncpy(securityMode, "WEP", sizeof(securityMode)-1);
		else if((xWifiScanResults+ii)->xSecurity == eWiFiSecurityWPA)
			strncpy(securityMode, "WPA", sizeof(securityMode)-1);
		else if((xWifiScanResults+ii)->xSecurity == eWiFiSecurityWPA2)
			strncpy(securityMode, "WPA2", sizeof(securityMode)-1);
		
		configPRINTF( (" Security = %s\r\n", securityMode) );
		memset( securityMode, 0, sizeof( securityMode ) );
	}
	configPRINTF( ("======SCAN end==============\r\n") );
#endif

	xWifiStatus = WIFI_ConnectAP( &xNetworkParams );
	if( xWifiStatus == eWiFiSuccess )
	{
		configPRINTF( ( "Wi-Fi connected to AP %s.\r\n", xNetworkParams.pcSSID ) );

		xWifiStatus = WIFI_GetIP( ucTempIp );
		if ( eWiFiSuccess == xWifiStatus ) 
		{
			configPRINTF( ("IP Address acquired %d.%d.%d.%d\r\n",
							ucTempIp[ 0 ], ucTempIp[ 1 ], ucTempIp[ 2 ], ucTempIp[ 3 ])  );
		}
	}
	else
	{
		/* Connection failed, configure SoftAP. */
		configPRINTF( ("Wi-Fi failed to connect to AP %s.\r\n", xNetworkParams.pcSSID) );

		/*xNetworkParams.pcSSID = wificonfigACCESS_POINT_SSID_PREFIX;
		xNetworkParams.pcPassword = wificonfigACCESS_POINT_PASSKEY;
		xNetworkParams.xSecurity = wificonfigACCESS_POINT_SECURITY;
		xNetworkParams.cChannel = wificonfigACCESS_POINT_CHANNEL;*/

		configPRINTF( ( "Connect to SoftAP %s using password %s. \r\n",
						xNetworkParams.pcSSID, xNetworkParams.pcPassword ) );
/*
		while( WIFI_ConfigureAP( &xNetworkParams ) != eWiFiSuccess )
		{
			configPRINTF( ( "Connect to SoftAP %s using password %s and configure Wi-Fi. \r\n",
							xNetworkParams.pcSSID, xNetworkParams.pcPassword ) );
		}
*/
		configPRINTF( ( " Wi-Fi configuration successful. \r\n" ) );
	}
	
}


/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    /* If the buffers to be provided to the Idle task are declared inside this
     * function then they must be declared static - otherwise they will be allocated on
     * the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle
     * task's state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
 * application must provide an implementation of vApplicationGetTimerTaskMemory()
 * to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize)
{
    /* If the buffers to be provided to the Timer task are declared inside this
     * function then they must be declared static - otherwise they will be allocated on
     * the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
     * task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/*-----------------------------------------------------------*/

/**
 * @brief Warn user if pvPortMalloc fails.
 *
 * Called if a call to pvPortMalloc() fails because there is insufficient
 * free memory available in the FreeRTOS heap.  pvPortMalloc() is called
 * internally by FreeRTOS API functions that create tasks, queues, software
 * timers, and semaphores.  The size of the FreeRTOS heap is set by the
 * configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h.
 *
 */
void vApplicationMallocFailedHook()
{
    taskDISABLE_INTERRUPTS();
    for( ;; );
}

/*-----------------------------------------------------------*/

/**
 * @brief Loop forever if stack overflow is detected.
 *
 * If configCHECK_FOR_STACK_OVERFLOW is set to 1,
 * this hook provides a location for applications to
 * define a response to a stack overflow.
 *
 * Use this hook to help identify that a stack overflow
 * has occurred.
 *
 */
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char * pcTaskName )
{
    portDISABLE_INTERRUPTS();

    /* Loop forever */
    for( ; ; );
}

/*-----------------------------------------------------------*/

void *pvPortCalloc( size_t xSize )
{
    void *pvReturn;

    pvReturn = pvPortMalloc( xSize );
    if( pvReturn != NULL )
    {
      memset( pvReturn, 0x00, xSize );
    }

    return pvReturn;
}
