#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <qcli.h>
#include <qcli_api.h>
#include <qapi_wlan.h>

#include "lastlock_demo.h"

extern QCLI_Group_Handle_t qcli_peripherals_group;
QCLI_Group_Handle_t qcli_lastlock_group;

QCLI_Command_Status_t lastlock_test(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t adc_cmd_list[] = {
   // cmd_function        start_thread          cmd_string               usage_string                   description
   { lastlock_test,            false,                  "read",                     "",                           "read"   },
};

const QCLI_Command_Group_t lastlock_cmd_group = {
    "LASTLOCK",
    0,
    NULL
};

void Initialize_Lastlock_Demo(void) {
    qcli_lastlock_group = QCLI_Register_Command_Group(qcli_peripherals_group, &lastlock_cmd_group);

    if(qcli_lastlock_group != NULL) {
        QCLI_Printf(qcli_lastlock_group, "LASTLOCK Registered\n");
    }
}

QCLI_Command_Status_t lastlock_test(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List) {
    
}