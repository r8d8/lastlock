#ifndef ERRLOG_ARMM_H
#define ERRLOG_ARMM_H
/*===========================================================================

                   L O G  P A C K E T S  F O R  E R R

DESCRIPTION
  This header file contains the definitions of log structure for core dump
 
Copyright (c) 2016 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.ioe/1.0/v2/rom/release/api/debugtools/err/private/errlog_armm.h#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/25/07   tbg     Initial revision (pulled code from rexlog.h)

===========================================================================*/


/************************************************************************
 *                        ARCH_COREDUMP_TYPES
 ************************************************************************/

/****************
 *    ARM
 ****************/

typedef enum
{
  ARM_R0 = 0,
  ARM_R1,
  ARM_R2,
  ARM_R3,
  ARM_R4,
  ARM_R5,
  ARM_R6,
  ARM_R7,
  ARM_R8,
  ARM_R9,
  ARM_R10,
  ARM_R11,
  ARM_R12,
  ARM_SP,
  ARM_LR,
  ARM_PC,
  ARM_PSP,
  ARM_MSP,
  ARM_PSR,
#ifdef ERR_CORTEXM0
  ARM_APSR,
  ARM_IPSR,
  ARM_EPSR,
#endif   
  ARM_PRIMASK,
#ifndef ERR_CORTEXM0
  ARM_FAULTMASK,
  ARM_BASEPRI,
#endif
  ARM_CONTROL,
  ARM_EXCEPTION_R0,
  ARM_EXCEPTION_R1,
  ARM_EXCEPTION_R2,
  ARM_EXCEPTION_R3,
  ARM_EXCEPTION_R12,
  ARM_EXCEPTION_LR,
  ARM_EXCEPTION_PC,
  ARM_EXCEPTION_XPSR,
  SIZEOF_ARCH_COREDUMP_REGISTERS
} arch_coredump_register_type;

#define SIZEOF_SVC_REGS 

typedef struct
{
  uint32 regs[SIZEOF_ARCH_COREDUMP_REGISTERS];
} arch_coredump_array_type;

typedef struct
{
  uint32 regs[13]; /* r0-r12 */
  uint32 sp;
  uint32 lr;
  uint32 pc;
  uint32 psp;
  uint32 msp;
  uint32 psr;
#ifndef ERR_CORTEXM0
  uint32 aspr;
  uint32 ipsr;
  uint32 epsr;
#endif
  uint32 primask; 
#ifndef ERR_CORTEXM0
  uint32 faultmask;
  uint32 basepri;  
#endif
  uint32 control;
  uint32 exception_r0;
  uint32 exception_r1;
  uint32 exception_r2;
  uint32 exception_r3;
  uint32 exception_r12;
  uint32 exception_lr;
  uint32 exception_pc;
  uint32 exception_xpsr;
} arch_coredump_field_type;

union arch_coredump_union
{
  uint32                   array[SIZEOF_ARCH_COREDUMP_REGISTERS];
  arch_coredump_field_type name;
};


#endif /* ERRLOG_ARMM_H */
