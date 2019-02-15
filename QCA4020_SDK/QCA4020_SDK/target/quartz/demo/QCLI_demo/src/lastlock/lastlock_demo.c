#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <qcli.h>
#include <qcli_api.h>

#include "lastlock_demo.h"


QCLI_Group_Handle_t qcli_lastlock_group;

const QCLI_Command_Group_t peripherals_cmd_group = {
    "Lastlock",
    0,
    NULL
};


void Initialize_Lastlock_Demo(void) {
   qcli_lastlock_group = QCLI_Register_Command_Group(NULL, &peripherals_cmd_group);

   if(qcli_lastlock_group != NULL) {
	   Initialize_Lastlock_Demo();	   
   }
   
   QCLI_Printf(qcli_lastlock_group, "Lastlock registered\n");
}