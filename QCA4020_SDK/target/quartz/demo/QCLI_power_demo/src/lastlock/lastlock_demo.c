#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_omtm.h"
#include "qapi/qapi_om_smem.h"
#include "qapi/qapi_mom.h"
#include "qapi_types.h"
#include "qurt_error.h"
#include "qurt_thread.h"
#include "qurt_signal.h"
#include "qurt_timer.h"

#include "pal.h"
#include "qcli.h"
#include "ble_demo.h"
#include "hmi_demo.h"
#include "coex_demo.h"
#include "lastlock_demo.h"


//
const uint16_t LASTLOCK_CYCLE_COUNT = 2000;

//
typedef enum state
{
    START,
    SLEEP, 
    ACTIVE,
    LOCKED,
    UNLOCKED,
    STOP
} Lock_State_t;

//
typedef struct Lastlock_Transition_Data_s 
{
    Lock_State_t state;
    uint32_t operatimg_mode;
    uint32_t cycle_count;
    QCLI_Group_Handle_t qcli_handle
} Lastlock_Transition_Data_t;

static Lastlock_Transition_Data_t lastlock_context;

const QCLI_Command_t lastlock_cmd_list[] = {
// cmd_function, start_thread, cmd_string, usage_string, description
{ lastlock_demo, false, "run", "", "Run lastlock demo cycles"}
};

const QCLI_Command_Group_t lastlock_cmd_group = {
    "LASTLOCK",
    (sizeof(lastlock_cmd_list) / sizeof(QCLI_Command_t)),
    lastlock_cmd_list
};

void 
lastlock_init(qbool_t IsColdBoot)
{
    if (IsColdBoot)
    {
        lastlock_context.state = START;
        lastlock_context.operatimg_mode = OPERATING_MODE_FOM_E;
    }
    else // restore context from mode switch
    {
        qapi_Status_t res;
        uint16_t data_size;
        Lastlock_Transition_Data_t *transition_data;

        res = qapi_OMSM_Retrieve(QAPI_OMSM_DEFAULT_AON_POOL, 
        OMSM_CLIENT_ID_LASTLOCK_E, &data_size, (void **)&transition_data);

        if ((res == QAPI_OK) 
            && (transition_data != NULL) 
            && (data_size == sizeof(Lastlock_Transition_Data_t)))
        {
            memset(&lastlock_context, 0, sizeof(lastlock_context));
            lastlock_context.state = transition_data->state;
            lastlock_context.operatimg_mode = transition_data->operatimg_mode;
            lastlock_context.cycle_count = transition_data->cycle_count;
            lastlock_context.qcli_handle = transition_data->qcli_handle;
        }
    }

    lastlock_context.qcli_handle = QCLI_Register_Command_Group(NULL, &lastlock_cmd_group);
    if (lastlock_context.qcli_handle != NULL)
    {
        QCLI_Printf(lastlock_context.qcli_handle, "LASTLOCK Registered\n");
    }

}

//
QCLI_Command_Status_t
lastlock_receive_ble()
{
    //
    return (QCLI_STATUS_SUCCESS_E);
}

//
QCLI_Command_Status_t
lastlock_lock()
{
    //
    return (QCLI_STATUS_SUCCESS_E);
}

//
QCLI_Command_Status_t
lastlock_unlock()
{
    //
    return (QCLI_STATUS_SUCCESS_E);
}

//
QCLI_Command_Status_t 
lastlock_switch_mode(uint32_t mode_id) 
{
    qapi_Status_t res = qapi_OMTM_Switch_Operating_Mode(mode_id, QAPI_OMTM_SWITCH_NOW_E);

    if(res == QAPI_OK)
    {
        lastlock_context.operatimg_mode = mode_id;
    }
    else
    {
        /* Sleep the Thread for a short period then try again. */
        // PAL_Context.Transition_Attempts ++;

        // if(PAL_Context.Transition_Attempts >= PAL_MODE_TRANSITION_ATTEMPTS)
        // {
        //     QCLI_Printf(lastlock_context.qcli_handle, "Mode transition failed.");
        //     QCLI_Printf(lastlock_context.qcli_handle, PAL_OUTPUT_END_OF_LINE_STRING);
        //     PAL_Context.Switch_Mode = (uint32_t)OPERATING_MODE_FOM_E;
        // }
        qurt_time_t dt = qurt_timer_convert_time_to_ticks(
            (qurt_time_t)PAL_MODE_TRANSITION_WAIT_MS, QURT_TIME_MSEC);
        qurt_thread_sleep(dt);
    }
    

    return (res);
}

//
static QCLI_Command_Status_t  
run() {
    QCLI_Command_Status_t res; 

    while (lastlock_context.state != STOP) {
        switch (lastlock_context.state) 
        {
            case START:
                lastlock_context.state = SLEEP;
                QCLI_Printf(lastlock_context.qcli_handle, "state SLEEP\n");
            break;

            case SLEEP:
                res = lastlock_switch_mode(OPERATING_MODE_FOM_E);
                if (res != QCLI_STATUS_SUCCESS_E) 
                {
                    break;
                }
                lastlock_context.state = ACTIVE;
                QCLI_Printf(lastlock_context.qcli_handle, "state ACTIVE\n");
            break;

            case ACTIVE:
                res = lastlock_receive_ble();
                if (res != QCLI_STATUS_SUCCESS_E) 
                {
                    break;
                }

                res = lastlock_lock();
                if (res != QCLI_STATUS_SUCCESS_E) 
                {
                    break;
                }
                lastlock_context.state = LOCKED;
                QCLI_Printf(lastlock_context.qcli_handle, "state LOCKED\n");
            break;

            case LOCKED:
                res = lastlock_unlock();
                if (res != QCLI_STATUS_SUCCESS_E) 
                {
                    break;
                }
                lastlock_context.state = UNLOCKED;
                QCLI_Printf(lastlock_context.qcli_handle, "state UNLOCKED\n");
            break;

            case UNLOCKED:
                res = lastlock_switch_mode(OPERATING_MODE_SOM_E);
                if (res != QCLI_STATUS_SUCCESS_E) 
                {
                    break;
                }
                lastlock_context.state = STOP;
                QCLI_Printf(lastlock_context.qcli_handle, "state SLEEP\n");
            break;
        }

        if (res != QCLI_STATUS_SUCCESS_E)
        {   
            break;
        }

    }

    return (res);
}

//
QCLI_Command_Status_t 
lastlock_demo() 
{
    QCLI_Command_Status_t res;
    for (; lastlock_context.cycle_count <= LASTLOCK_CYCLE_COUNT;)
    {
        lastlock_context.state = START;
        res = run() ;
        if (res != QCLI_STATUS_SUCCESS_E) 
        {
            char str[50];
            int n = sprintf(str, "Failed to process cycle %d\n", 
                lastlock_context.cycle_count);
            QCLI_Printf(lastlock_context.qcli_handle, str);
            break;
        }
        lastlock_context.cycle_count += 1;
    }

    return (res);    
}

//
qbool_t 
Lastlock_Prepare_Mode_Switch(Operating_Mode_t Next_Mode) 
{
    void *buf;
    qbool_t is_prepared = false;
    qapi_Status_t res = qapi_OMSM_Alloc(QAPI_OMSM_DEFAULT_AON_POOL,
        OMSM_CLIENT_ID_LASTLOCK_E, 
        sizeof(Lastlock_Transition_Data_t), 
        &buf);
    
    if ((res == QAPI_OK) && (buf != NULL))
    {
        res = qapi_OMSM_Commit(QAPI_OMSM_DEFAULT_AON_POOL, OMSM_CLIENT_ID_LASTLOCK_E);
        if (res == QAPI_OK)
        {
            is_prepared = true;
        }
        else
        {
            qapi_OMSM_Free(QAPI_OMSM_DEFAULT_AON_POOL, OMSM_CLIENT_ID_LASTLOCK_E);
            Display_Function_Error(lastlock_context.qcli_handle, "qapi_OMSM_Commit", res);
        }
    }

    return (is_prepared);
}

void 
Lastlock_Cancel_Mode_Switch(void)
{
    if (lastlock_context.qcli_handle != NULL)
    {
        qapi_OMSM_Free(QAPI_OMSM_DEFAULT_AON_POOL, OMSM_CLIENT_ID_LASTLOCK_E);
    }
}

void 
Lastlock_Exit_Mode(Operating_Mode_t Next_Mode) 
{
    uint16_t                    data_size;
    unsigned int                Index;
    qapi_Status_t               res;
    Lastlock_Transition_Data_t *transition_data;

    if (lastlock_context.qcli_handle != NULL)
    {
        res = qapi_OMSM_Retrieve(QAPI_OMSM_DEFAULT_AON_POOL,
            OMSM_CLIENT_ID_LASTLOCK_E, 
            &data_size, (void **)&transition_data);

        if ((res == QAPI_OK) && (transition_data != NULL))
        {
            if (data_size == sizeof(Lastlock_Transition_Data_t))
            {
                transition_data->state = lastlock_context.state;
                transition_data->cycle_count = lastlock_context.cycle_count;
                transition_data->operatimg_mode = lastlock_context.operatimg_mode;
                transition_data->qcli_handle = lastlock_context.qcli_handle;

                res = qapi_OMSM_Commit(QAPI_OMSM_DEFAULT_AON_POOL, 
                    OMSM_CLIENT_ID_LASTLOCK_E);
            }
            else
            {
                qapi_OMSM_Free(QAPI_OMSM_DEFAULT_AON_POOL, OMSM_CLIENT_ID_BLE_E);
            }
        }
    }
}