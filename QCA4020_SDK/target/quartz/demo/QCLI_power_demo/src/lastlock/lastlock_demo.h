#ifndef LASTLOCK_H
#define LASTLOCK_H

#include <qapi_pwm.h>


int32_t 
lastlock(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

/**
    @brief 
    @param
    @return
*/
void 
lastlock_init(qbool_t IsColdBoot);

/**
    @brief This function registers the Lastlock demo  commands with QCLI.
    Demo consists of looped actions: 
        deep sleep -> receive Bluetooth data -> check key -> lock -> unlock -> deep sleep
    @return
*/
QCLI_Command_Status_t 
lastlock_demo();

/**
   @brief
*/
qbool_t 
Lastlock_Prepare_Mode_Switch(Operating_Mode_t Next_Mode);

/**
   @brief
*/
void 
Lastlock_Cancel_Mode_Switch(void);

/**
   @brief
*/
void 
Lastlock_Exit_Mode(Operating_Mode_t Next_Mode);

#endif /* LASTLOCK_H */