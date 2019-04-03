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
 * Copyright 2010-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 *
 * This example takes the parameters from the aws_iot_config.h file and establishes
 * a connection to the AWS IoT MQTT Platform. It performs several operations to
 * demonstrate the basic capabilities of the AWS IoT Jobs platform.
 *
 * If all the certs are correct, you should see the list of pending Job Executions
 * printed out by the iot_get_pending_callback_handler. If there are any existing pending
 * job executions each will be processed one at a time in the iot_next_job_callback_handler.
 * After all of the pending jobs have been processed the program will wait for
 * notifications for new pending jobs and process them one at a time as they come in.
 *
 * In the main body you can see how each callback is registered for each corresponding
 * Jobs topic.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "aws_iot_json_utils.h"
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"
#include "aws_iot_jobs_interface.h"
#include "jobs_sample.h"

#include "netutils.h"
#include "qapi/qurt_thread.h"
#include "qapi/qurt_types.h"
#include "qapi/qurt_error.h"
#include "qapi/qurt_signal.h"
#include "qapi/qurt_mutex.h"
#include "qapi_fs.h"
#include "qapi_crypto.h"

#include "qcli_api.h"
#include "qapi_ssl.h"
#include "qapi_socket.h"
#include "qapi_ns_utils.h"
#include "qapi_netbuf.h"

#undef A_OK
#define A_OK                    QAPI_OK

#undef A_ERROR
#define A_ERROR                 -1

#undef IOT_INFO
#undef IOT_ERROR

#define IOT_INFO(...) QCLI_Printf(qcli_ecosystem_handle, __VA_ARGS__)
#define IOT_ERROR(...) QCLI_Printf(qcli_ecosystem_handle, __VA_ARGS__)

#define JOBS_TASK_PRIORITY    20
#define JOBS_TASK_STACK_SIZE  4096

extern QCLI_Group_Handle_t qcli_ecosystem_handle; /* Handle for ecosystem Command Group. */

bool stop_jobs;
struct jobs_params *g_jobs_data = NULL;
qurt_thread_t jobs_thread;

/**
 * @brief Default cert location
 */

static jsmn_parser jsonParser;
static jsmntok_t jsonTokenStruct[MAX_JSON_TOKEN_EXPECTED];
static int32_t tokenCount;

void iot_get_pending_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
									IoT_Publish_Message_Params *params, void *pData) {
	IOT_UNUSED(pData);
	IOT_UNUSED(pClient);
	IOT_INFO("\nJOB_GET_PENDING_TOPIC callback\n");
	IOT_INFO("topic: %.*s\n", topicNameLen, topicName);
	IOT_INFO("payload: %.*s\n", (int) params->payloadLen, (char *)params->payload);

	jsmn_init(&jsonParser);

	tokenCount = jsmn_parse(&jsonParser, params->payload, (int) params->payloadLen, jsonTokenStruct, MAX_JSON_TOKEN_EXPECTED);

	if(tokenCount < 0) {
		IOT_WARN("Failed to parse JSON: %d\n", tokenCount);
		return;
	}

	/* Assume the top-level element is an object */
	if(tokenCount < 1 || jsonTokenStruct[0].type != JSMN_OBJECT) {
		IOT_WARN("Top Level is not an object\n");
		return;
	}

	jsmntok_t *jobs;

	jobs = findToken("inProgressJobs", params->payload, jsonTokenStruct);

	if (jobs) {
		IOT_INFO("inProgressJobs: %.*s\n", jobs->end - jobs->start, (char *)params->payload + jobs->start);
	}

	jobs = findToken("queuedJobs", params->payload, jsonTokenStruct);

	if (jobs) {
		IOT_INFO("queuedJobs: %.*s\n", jobs->end - jobs->start, (char *)params->payload + jobs->start);
	}
}

void iot_next_job_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
									IoT_Publish_Message_Params *params, void *pData) {
	char topicToPublishUpdate[MAX_JOB_TOPIC_LENGTH_BYTES];
	char messageBuffer[200];

	IOT_UNUSED(pData);
	IOT_UNUSED(pClient);
	IOT_INFO("\nJOB_NOTIFY_NEXT_TOPIC / JOB_DESCRIBE_TOPIC($next) callback\n");
	IOT_INFO("topic: %.*s\n", topicNameLen, topicName);
	IOT_INFO("payload: %.*s\n", (int) params->payloadLen, (char *)params->payload);

	jsmn_init(&jsonParser);

	tokenCount = jsmn_parse(&jsonParser, params->payload, (int) params->payloadLen, jsonTokenStruct, MAX_JSON_TOKEN_EXPECTED);

	if(tokenCount < 0) {
		IOT_WARN("Failed to parse JSON: %d\n", tokenCount);
		return;
	}

	/* Assume the top-level element is an object */
	if(tokenCount < 1 || jsonTokenStruct[0].type != JSMN_OBJECT) {
		IOT_WARN("Top Level is not an object\n");
		return;
	}

	jsmntok_t *tokExecution;

	tokExecution = findToken("execution", params->payload, jsonTokenStruct);

	if (tokExecution) {
		IOT_INFO("execution: %.*s\n", tokExecution->end - tokExecution->start, (char *)params->payload + tokExecution->start);

		jsmntok_t *tok;

		tok = findToken("jobId", params->payload, tokExecution);

		if (tok) {
			IoT_Error_t rc;
			char jobId[MAX_SIZE_OF_JOB_ID + 1];
			AwsIotJobExecutionUpdateRequest updateRequest;

			rc = parseStringValue(jobId, MAX_SIZE_OF_JOB_ID + 1, params->payload, tok);

			if(SUCCESS != rc) {
				IOT_ERROR("parseStringValue returned error : %d\n", rc);
				return;
			}

			IOT_INFO("jobId: %s\n", jobId);

			tok = findToken("jobDocument", params->payload, tokExecution);

			/*
			 * Do your job processing here.
			 */

			if (tok) {
				IOT_INFO("jobDocument: %.*s\n", tok->end - tok->start, (char *)params->payload + tok->start);
				/* Alternatively if the job still has more steps the status can be set to JOB_EXECUTION_IN_PROGRESS instead */
				updateRequest.status = JOB_EXECUTION_SUCCEEDED;
				updateRequest.statusDetails = "{\"exampleDetail\":\"a value appropriate for your successful job\"}";
			} else {
				updateRequest.status = JOB_EXECUTION_FAILED;
				updateRequest.statusDetails = "{\"failureDetail\":\"Unable to process job document\"}";
			}

			updateRequest.expectedVersion = 0;
			updateRequest.executionNumber = 0;
			updateRequest.includeJobExecutionState = false;
			updateRequest.includeJobDocument = false;
			updateRequest.clientToken = NULL;

			rc = aws_iot_jobs_send_update(pClient, QOS0, g_jobs_data->thing_name, jobId, &updateRequest,
					topicToPublishUpdate, sizeof(topicToPublishUpdate), messageBuffer, sizeof(messageBuffer));
		}
	} else {
		IOT_INFO("execution property not found, nothing to do\n");
	}
}

void iot_update_accepted_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
									IoT_Publish_Message_Params *params, void *pData) {
	IOT_UNUSED(pData);
	IOT_UNUSED(pClient);
	IOT_INFO("\nJOB_UPDATE_TOPIC / accepted callback\n");
	IOT_INFO("topic: %.*s\n", topicNameLen, topicName);
	IOT_INFO("payload: %.*s\n", (int) params->payloadLen, (char *)params->payload);
}

void iot_update_rejected_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
									IoT_Publish_Message_Params *params, void *pData) {
	IOT_UNUSED(pData);
	IOT_UNUSED(pClient);
	IOT_INFO("\nJOB_UPDATE_TOPIC / rejected callback\n");
	IOT_INFO("topic: %.*s\n", topicNameLen, topicName);
	IOT_INFO("payload: %.*s\n", (int) params->payloadLen, (char *)params->payload);

	/* Do error handling here for when the update was rejected */
}

void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data) {
	IOT_WARN("MQTT Disconnect\n");
	IoT_Error_t rc = FAILURE;

	if(NULL == pClient) {
		return;
	}

	IOT_UNUSED(data);

	if(aws_iot_is_autoreconnect_enabled(pClient)) {
		IOT_INFO("Auto Reconnect is enabled, Reconnecting attempt will start now\n");
	} else {
		IOT_WARN("Auto Reconnect not enabled. Starting manual reconnect...\n");
		rc = aws_iot_mqtt_attempt_reconnect(pClient);
		if(NETWORK_RECONNECTED == rc) {
			IOT_WARN("Manual Reconnect Successful\n");
		} else {
			IOT_WARN("Manual Reconnect Failed - %d\n", rc);
		}
	}
}

void jobs_sample_cleanup()
{
    if( g_jobs_data == NULL )
        return;

    if(g_jobs_data->host_name != NULL)
        free(g_jobs_data->host_name);

    if(g_jobs_data->thing_name != NULL)
        free(g_jobs_data->thing_name);

    if(g_jobs_data->root_ca != NULL)
        free(g_jobs_data->root_ca);

    if(g_jobs_data->client_crt != NULL)
        free(g_jobs_data->client_crt);

    free(g_jobs_data);
    g_jobs_data = NULL;
}

/*
 * 
 */
void jobs_sample() 
{
	IoT_Error_t rc = FAILURE;
    AWS_IoT_Client client;
	IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
	IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;
    char key_stub[] = "this is a stub key";
    
	//IoT_Publish_Message_Params paramsQOS0;

    if( g_jobs_data == NULL)
    {
		IOT_ERROR("jobs parameters are not set\n");
        goto jobs_end;
    }
    
    stop_jobs = FALSE;
	IOT_DEBUG("rootCA: %s\n", g_jobs_data->root_ca);
	IOT_DEBUG("clientCRT: %s\n", g_jobs_data->client_crt);
    
	mqttInitParams.enableAutoReconnect = false; // We enable this later below
	mqttInitParams.pHostURL = g_jobs_data->host_name;
	mqttInitParams.port = AWS_IOT_MQTT_PORT;
	mqttInitParams.pRootCALocation = g_jobs_data->root_ca;
	mqttInitParams.pDeviceCertLocation = g_jobs_data->client_crt;
	mqttInitParams.pDevicePrivateKeyLocation = key_stub;
	mqttInitParams.mqttCommandTimeout_ms = 20000;
	mqttInitParams.tlsHandshakeTimeout_ms = 5000;
	mqttInitParams.isSSLHostnameVerify = true;
	mqttInitParams.disconnectHandler = disconnectCallbackHandler;
	mqttInitParams.disconnectHandlerData = NULL;

	rc = aws_iot_mqtt_init(&client, &mqttInitParams);
	if(SUCCESS != rc) {
		IOT_ERROR("aws_iot_mqtt_init returned error : %d\n", rc);
        goto jobs_end;
	}

	connectParams.keepAliveIntervalInSec = 600;
	connectParams.isCleanSession = true;
	connectParams.MQTTVersion = MQTT_3_1_1;
	connectParams.pClientID = AWS_IOT_MQTT_CLIENT_ID;
	connectParams.clientIDLen = (uint16_t) strlen(AWS_IOT_MQTT_CLIENT_ID);
	connectParams.isWillMsgPresent = false;
	connectParams.pPassword = NULL;
	connectParams.pUsername = NULL;
   
    IOT_INFO("Connecting...\n");
	rc = aws_iot_mqtt_connect(&client, &connectParams);
	if(SUCCESS != rc) {
		IOT_ERROR("Error(%d) connecting to %s:%d\n", rc, mqttInitParams.pHostURL, mqttInitParams.port);
        goto jobs_end;
	}
	/*
	 * Enable Auto Reconnect functionality. Minimum and Maximum time of Exponential backoff are set in aws_iot_config.h
	 *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
	 *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
	 */
	rc = aws_iot_mqtt_autoreconnect_set_status(&client, true);
	if(SUCCESS != rc) {
		IOT_ERROR("Unable to set Auto Reconnect to true - %d\n", rc);
        goto jobs_end;
	}

	char topicToSubscribeGetPending[MAX_JOB_TOPIC_LENGTH_BYTES];
	char topicToSubscribeNotifyNext[MAX_JOB_TOPIC_LENGTH_BYTES];
	char topicToSubscribeGetNext[MAX_JOB_TOPIC_LENGTH_BYTES];
	char topicToSubscribeUpdateAccepted[MAX_JOB_TOPIC_LENGTH_BYTES];
	char topicToSubscribeUpdateRejected[MAX_JOB_TOPIC_LENGTH_BYTES];

	char topicToPublishGetPending[MAX_JOB_TOPIC_LENGTH_BYTES];
	char topicToPublishGetNext[MAX_JOB_TOPIC_LENGTH_BYTES];

	rc = aws_iot_jobs_subscribe_to_job_messages(
		&client, QOS0, g_jobs_data->thing_name, NULL, JOB_GET_PENDING_TOPIC, JOB_WILDCARD_REPLY_TYPE,
		iot_get_pending_callback_handler, NULL, topicToSubscribeGetPending, sizeof(topicToSubscribeGetPending));

	if(SUCCESS != rc) {
		IOT_ERROR("Error subscribing JOB_GET_PENDING_TOPIC: %d\n", rc);
        goto jobs_end;
	}

	rc = aws_iot_jobs_subscribe_to_job_messages(
		&client, QOS0, g_jobs_data->thing_name, NULL, JOB_NOTIFY_NEXT_TOPIC, JOB_REQUEST_TYPE,
		iot_next_job_callback_handler, NULL, topicToSubscribeNotifyNext, sizeof(topicToSubscribeNotifyNext));

	if(SUCCESS != rc) {
		IOT_ERROR("Error subscribing JOB_NOTIFY_NEXT_TOPIC: %d\n", rc);
        goto jobs_end;
	}

	rc = aws_iot_jobs_subscribe_to_job_messages(
		&client, QOS0, g_jobs_data->thing_name, JOB_ID_NEXT, JOB_DESCRIBE_TOPIC, JOB_WILDCARD_REPLY_TYPE,
		iot_next_job_callback_handler, NULL, topicToSubscribeGetNext, sizeof(topicToSubscribeGetNext));

	if(SUCCESS != rc) {
		IOT_ERROR("Error subscribing JOB_DESCRIBE_TOPIC ($next): %d\n", rc);
        goto jobs_end;
	}

	rc = aws_iot_jobs_subscribe_to_job_messages(
		&client, QOS0, g_jobs_data->thing_name, JOB_ID_WILDCARD, JOB_UPDATE_TOPIC, JOB_ACCEPTED_REPLY_TYPE,
		iot_update_accepted_callback_handler, NULL, topicToSubscribeUpdateAccepted, sizeof(topicToSubscribeUpdateAccepted));

	if(SUCCESS != rc) {
		IOT_ERROR("Error subscribing JOB_UPDATE_TOPIC/accepted: %d\n", rc);
        goto jobs_end;
	}

	rc = aws_iot_jobs_subscribe_to_job_messages(
		&client, QOS0, g_jobs_data->thing_name, JOB_ID_WILDCARD, JOB_UPDATE_TOPIC, JOB_REJECTED_REPLY_TYPE,
		iot_update_rejected_callback_handler, NULL, topicToSubscribeUpdateRejected, sizeof(topicToSubscribeUpdateRejected));

	if(SUCCESS != rc) {
		IOT_ERROR("Error subscribing JOB_UPDATE_TOPIC/rejected: %d\n", rc);
        goto jobs_end;
	}

	//paramsQOS0.qos = QOS0;
	//paramsQOS0.payload = (void *) cPayload;
	//paramsQOS0.isRetained = 0;
	//paramsQOS0.payloadLen = strlen(cPayload);

	rc = aws_iot_jobs_send_query(&client, QOS0, g_jobs_data->thing_name, NULL, NULL, topicToPublishGetPending, sizeof(topicToPublishGetPending), NULL, 0, JOB_GET_PENDING_TOPIC);

	AwsIotDescribeJobExecutionRequest describeRequest;
	describeRequest.executionNumber = 0;
	describeRequest.includeJobDocument = true;
	describeRequest.clientToken = NULL;

	rc = aws_iot_jobs_describe(&client, QOS0, g_jobs_data->thing_name, JOB_ID_NEXT, &describeRequest, topicToPublishGetNext, sizeof(topicToPublishGetNext), NULL, 0);

	while((SUCCESS == rc) && (stop_jobs == FALSE)) {
		//Max time the yield function will wait for read messages
		rc = aws_iot_mqtt_yield(&client, 5000);
	}

    aws_iot_mqtt_autoreconnect_set_status(&client, false);
    aws_iot_mqtt_disconnect(&client);
    
    IOT_INFO("jobs_demo is terminated\n");
    
    /* clean up the thread */
jobs_end:
    jobs_sample_cleanup();
    qurt_thread_stop();
    return;
}


QCLI_Command_Status_t jobs_sample_run(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List) 
{
    unsigned long task_priority = JOBS_TASK_PRIORITY;
    int stack_size = JOBS_TASK_STACK_SIZE;

    if( g_jobs_data != NULL)
    {
        IOT_ERROR("ERROR: jobs_demo is running....\n");
        return QCLI_STATUS_SUCCESS_E;
    }
    
    if(Parameter_Count != 4) {
        IOT_ERROR("Please provide Host_Name, Thing_Name, RootCA_name, Dev_Cert\n");
        IOT_ERROR("Usage: jobs_run [Host_Name] [Thing_Name] [RootCA_name] [Dev_cert]\n");
        goto cleanup;
    }

    /* flag to know if main loop is running */
    stop_jobs = TRUE;

    g_jobs_data = malloc(sizeof(struct jobs_params));

    if(g_jobs_data == NULL)
    {
        IOT_ERROR("ERROR: malloc failed\n");
        goto cleanup;
    }

    memset(g_jobs_data, 0, sizeof(struct jobs_params));
    
    g_jobs_data->host_name = (char *)malloc(JOBS_MAX_HOST_NAME_SIZE);
    if(g_jobs_data->host_name == NULL)
    {
        IOT_ERROR("ERROR: malloc failed\n");
        goto cleanup;
    }

    g_jobs_data->thing_name = (char *)malloc(JOBS_MAX_THING_NAME_SIZE);
    if(g_jobs_data->thing_name == NULL)
    {
        IOT_ERROR("ERROR: malloc failed\n");
        goto cleanup;
    }

    g_jobs_data->root_ca = (char *)malloc(JOBS_MAX_ROOTCA_NAME_SIZE);
    if(g_jobs_data->root_ca == NULL)
    {
        IOT_ERROR("ERROR: malloc failed\n");
        goto cleanup;
    }

    g_jobs_data->client_crt = (char *)malloc(JOBS_MAX_CERT_NAME_SIZE);
    if(g_jobs_data->client_crt == NULL)
    {
        IOT_ERROR("ERROR: malloc failed\n");
        goto cleanup;
    }
    
	snprintf(g_jobs_data->host_name, JOBS_MAX_HOST_NAME_SIZE, "%s", Parameter_List[0].String_Value);
	snprintf(g_jobs_data->thing_name, JOBS_MAX_THING_NAME_SIZE, "%s", Parameter_List[1].String_Value);
	snprintf(g_jobs_data->root_ca, JOBS_MAX_ROOTCA_NAME_SIZE, "%s", Parameter_List[2].String_Value);
	snprintf(g_jobs_data->client_crt, JOBS_MAX_CERT_NAME_SIZE, "%s", Parameter_List[3].String_Value);
    
    //create a thread
    qurt_thread_attr_t attr;
    //qurt_thread_t handle;
    qurt_thread_attr_init (&attr);
    qurt_thread_attr_set_name (&attr, "jobs_sample");
    qurt_thread_attr_set_priority (&attr, task_priority);
    qurt_thread_attr_set_stack_size (&attr, stack_size);

    if(qurt_thread_create(&jobs_thread, &attr, (void *)jobs_sample, NULL) != QURT_EOK)
        IOT_ERROR("failed to create aws thread\n");

    return QCLI_STATUS_SUCCESS_E;
cleanup:
    jobs_sample_cleanup();
    return QCLI_STATUS_SUCCESS_E;
}


QCLI_Command_Status_t jobs_sample_destroy(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List) 
{
    //Stop the shadow sample demo, this clean up everything if sample is running
    stop_jobs = TRUE;
    return TRUE;
}
