#include <stdio.h>

#include "qapi_types.h"

#include "pal.h"
#include "qcli.h"

#include "qurt_error.h"
#include "qurt_thread.h"
#include "qurt_signal.h"
#include "qurt_timer.h"

#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_uart.h"
#include "qapi/qapi_omtm.h"
#include "qapi/qapi_om_smem.h"
#include "qapi/qapi_mom.h"

#include "ble_demo.h"
#include "hmi_demo.h"
#include "coex_demo.h"
#include "lastlock_demo.h"



// #define QCLI_Printf(qcli_lastlock_group, __String__)  do { PAL_Console_Write(sizeof(__String__) - 1, (__String__)); } while(0)

const uint16_t LASTLOCK_CYCLE_COUNT = 2000;

typedef enum state {
    START,
    SLEEP, 
    ACTIVE,
    LOCKED,
    UNLOCKED,
} lock_state;

static QCLI_Group_Handle_t qcli_lastlock_group;
static lock_state ll_state = START;
static QCLI_Group_Handle_t qcli_lastlock_group;

const QCLI_Command_t lastlock_cmd_list[] = {
   // cmd_function        start_thread          cmd_string               usage_string                   description
   { lastlock_demo,            false,                  "run",                     "",                    "Run lastlock demo cycles"   },
};

const QCLI_Command_Group_t lastlock_cmd_group = {
    "LASTLOCK",
    0,
    NULL
};

void 
lastlock_init(qbool_t IsColdBoot)
{
    qcli_lastlock_group = QCLI_Register_Command_Group(NULL, &lastlock_cmd_group);

    if (qcli_lastlock_group != NULL)
    {
        QCLI_Printf(qcli_lastlock_group, "LASTLOCK Registered\n");
    }

    ll_state = START;
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
        /* Set the switch mode back so that the thread can go idle again. */
        // PAL_Context.Switch_Mode = (uint32_t)OPERATING_MODE_FOM_E;
    }
    else
    {
        /* Sleep the Thread for a short period then try again. */
        // PAL_Context.Transition_Attempts ++;

        // if(PAL_Context.Transition_Attempts >= PAL_MODE_TRANSITION_ATTEMPTS)
        // {
        //     QCLI_Printf(qcli_lastlock_group, "Mode transition failed.");
        //     QCLI_Printf(qcli_lastlock_group, PAL_OUTPUT_END_OF_LINE_STRING);
        //     QCLI_Printf(qcli_lastlock_group, PAL_OUTPUT_END_OF_LINE_STRING);

        //     PAL_Context.Switch_Mode = (uint32_t)OPERATING_MODE_FOM_E;
        // }
        qurt_time_t dt = qurt_timer_convert_time_to_ticks((qurt_time_t)PAL_MODE_TRANSITION_WAIT_MS, QURT_TIME_MSEC);
        qurt_thread_sleep(dt);
    }
    

    return (res);
}

//
QCLI_Command_Status_t 
lastlock_demo() 
{
    qapi_Status_t res;
    for (int i = 0; i <= LASTLOCK_CYCLE_COUNT; i++)
    {
        switch (ll_state) 
        {
            case START:
                ll_state = SLEEP;
                QCLI_Printf(qcli_lastlock_group, "state SLEEP\n");
            break;

            case SLEEP:
                res = lastlock_switch_mode(OPERATING_MODE_FOM_E);
                if (res != QCLI_STATUS_SUCCESS_E) 
                {
                    break;
                }
                ll_state = ACTIVE;
                QCLI_Printf(qcli_lastlock_group, "state ACTIVE");
            break;

            case ACTIVE:
                res = lastlock_receive_ble();
                if (res != QCLI_STATUS_SUCCESS_E) 
                {
                    break;
                }
                ll_state = LOCKED;
                QCLI_Printf(qcli_lastlock_group, "state LOCKED");
            break;

            case LOCKED:
                res = lastlock_unlock();
                if (res != QCLI_STATUS_SUCCESS_E) 
                {
                    break;
                }
                ll_state = UNLOCKED;
                QCLI_Printf(qcli_lastlock_group, "state UNLOCKED");
            break;

            case UNLOCKED:
                res = lastlock_switch_mode(OPERATING_MODE_SOM_E);
                if (res != QCLI_STATUS_SUCCESS_E) 
                {
                    break;
                }
                ll_state = SLEEP;
                QCLI_Printf(qcli_lastlock_group, "state SLEEP");
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
void
Initialize_Lastlock_Demo()
{
}
    //