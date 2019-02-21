#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qcli.h"
#include "qcli_api.h"
#include "ble_demo.h"


#include "lastlock_demo.h"

extern QCLI_Group_Handle_t qcli_peripherals_group;
QCLI_Group_Handle_t qcli_lastlock_group;

const uint16_t LASTLOCK_CYCLE_COUNT = 2000;


typedef enum state {
    SLEEP, 
    ACTIVE,
    LOCKED,
    UNLOCKED,
} lock_state;

static lock_state ll_state = NULL;


QCLI_Command_Status_t lastlock_demo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t lastlock_cmd_list[] = {
   // cmd_function        start_thread          cmd_string               usage_string                   description
   { lastlock_demo,            false,                  "read",                     "",                           "read"   },
};

const QCLI_Command_Group_t lastlock_cmd_group = {
    "LASTLOCK",
    0,
    NULL
};

void 
lastlock_init(qbool_t IsColdBoot)
{
    Initialize_BLE_Demo(IsColdBoot)
    qcli_lastlock_group = QCLI_Register_Command_Group(qcli_peripherals_group, &lastlock_cmd_group);

    if (qcli_lastlock_group != NULL)
    {
        QCLI_Printf(qcli_lastlock_group, "LASTLOCK Registered\n");
    }
}


QCLI_Command_Status_t 
lastlock_demo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List) 
{
    for (int i = 0; i <= LASTLOCK_CYCLE_COUNT; i++)
    {
        switch (ll_state) 
        {
            case SLEEP:
                //
                ll_state = ACTIVE;
            break;

            case ACTIVE:
                //
                ll_state = LOCKED;
            break;

            case LOCKED:
                //
                ll_state = UNLOCKED;
            break;

            case UNLOCKED:
                //
                ll_state = SLEEP;
            break;
        }
    }    
}    


int32_t 
Start_onboard_via_ble()
{
    int32_t res = AdvertiseLE(1);
    
    if (res != SUCCESS)
    {
        LOG_ERROR("BLE: error AdvertiseLE()\n");
    }

    return (res);
}