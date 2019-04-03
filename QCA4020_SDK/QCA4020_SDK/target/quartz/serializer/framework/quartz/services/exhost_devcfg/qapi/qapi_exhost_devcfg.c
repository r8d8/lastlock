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

#include CUST_H
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <DALSysTypes.h>
#include <DALSys.h>
#include <DALDeviceId.h>
#include "qapi/qapi_types.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_exhost_devcfg.h"
#include "qapi/qapi_fatal_err.h"
#include "exhost_dev_dal_id.h"

/*************************************************************************************************/
/*
 * get Exhost Devcfg Scheme Parameter from DEVCFG
 */
qapi_Status_t qapi_Get_Exhost_Devcfg(qapi_Exhost_Devcfg_t *devcfg)
{
    DALSYSPropertyHandle hProps;
    DALSYSPropertyVar var;
    qapi_Status_t rtn = QAPI_ERROR;
    
    if( devcfg == NULL)
        return  rtn;

    /* get exhost handle */
    if( DAL_SUCCESS != DALSYS_GetDALPropertyHandle (DALDEVICEID_EXHOST, hProps)) {
        return  rtn;
    }

    /* get heart beat enable value */ 
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_SYS_SCHEME_HEART_BEAT_ENABLE , &var)) {
        return rtn;
    }
    devcfg->heart_beat_enable = var.Val.dwVal;   

    /* get heart beat interval value */ 
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_SYS_SCHEME_HEART_BEAT_INTERVAL , &var)) {
        return rtn;
    }
    devcfg->heart_beat_interval = var.Val.dwVal;   
    
    /* get uart enable value */ 
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_UART_SCHEME_PROP_ENABLE , &var)) {
        return rtn;
    }
    devcfg->uart_enable = var.Val.dwVal;
    
    /* get uart device id value */ 
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_UART_SCHEME_PROP_DEVICE_ID , &var)) {
        return rtn;
    }
    devcfg->uart_device_id = var.Val.dwVal;
    
    /* get uart port value */ 
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_UART_SCHEME_PROP_UART_PORT, &var)) {
        return rtn;
    }
    devcfg->uart_port = var.Val.dwVal;     
     
    /* get uart baud rate */ 
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_UART_SCHEME_PROP_BAUD_RATE, &var)) {
        return rtn;
    }
    devcfg->uart_baud_rate = var.Val.dwVal; 
   
    /* get uart flow control value */
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_UART_SCHEME_PROP_FLOW_CONTROL_ENABLE, &var)) {
        return rtn;
    }
    devcfg->uart_flowcontrol = var.Val.dwVal; 
   
    /* get num of service queues for uart interface */
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_UART_SCHEME_PROP_NUM_OF_SERVICE_QUEUES, &var)) {
        return rtn;
    }
    devcfg->uart_num_of_sq = var.Val.dwVal; 
   
    /* get servie queues id list for uart interface */
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_UART_SCHEME_PROP_SERVICE_QUEUES, &var)) {
        return rtn;
    }
    if( var.dwLen > MAX_NUM_SERVICE_QUEUE)
        return rtn;

    memcpy((void *)&(devcfg->uart_sq_ids), (void *)(var.Val.pbVal), var.dwLen);
   
    /* get spi enable value */ 
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_SPI_SCHEME_PROP_ENABLE, &var)) {
        return rtn;
    }
    devcfg->spi_enable = var.Val.dwVal;
    
    /* get spi device id value */
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_SPI_SCHEME_PROP_DEVICE_ID, &var)) {
        return rtn;
    }
    devcfg->spi_device_id = var.Val.dwVal;
    
    /* get spi block size value */    
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_SPI_SCHEME_PROP_BLOCK_SIZE, &var)) {
        return rtn;
    }
    devcfg->spi_block_size = var.Val.dwVal;

    /* get num of service queues for spi interface */
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_SPI_SCHEME_PROP_NUM_OF_SERVICE_QUEUES, &var)) {
        return rtn;
    }
    devcfg->spi_num_of_sq = var.Val.dwVal; 

    /* get servie queues id list for spi interface */
    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProps, NULL, EXHOST_SPI_SCHEME_PROP_SERVICE_QUEUES, &var)) {
        return rtn;
    }
    if( var.dwLen > MAX_NUM_SERVICE_QUEUE)
        return rtn;

    memcpy((void *)&(devcfg->spi_sq_ids), (void *)(var.Val.pbVal), var.dwLen);
    
    return QAPI_OK;
}
