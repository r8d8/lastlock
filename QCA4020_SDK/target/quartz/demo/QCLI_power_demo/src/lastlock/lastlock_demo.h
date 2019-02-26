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