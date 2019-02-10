/*======================================================================
   Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
    
   Redistribution and use in source and binary forms, with or without
   modification, are permitted (subject to the limitations in the
   disclaimer below) provided that the following conditions are met:
    
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
    
      * Redistributions in binary form must reproduce the above
        copyright notice, this list of conditions and the following
        disclaimer in the documentation and/or other materials provided
        with the distribution.
    
      * Neither the name of The Linux Foundation nor the names of its
        contributors may be used to endorse or promote products derived
        from this software without specific prior written permission.
    
   NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
   GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
   HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
   IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
                                                      
   qurt_interrupt.c

   GENERAL DESCRIPTION 
      Default interrupt handler.

 ======================================================================*/
#include "qurt_internal.h"
/*======================================================================
                          EXTERNAL
 ======================================================================*/
/*======================================================================
                          MACROS
 ======================================================================*/
/*======================================================================
                          TYPEDEFS
 ======================================================================*/
/*======================================================================
                          GLOBALS
 ======================================================================*/

static qurt_interrupt_handler_func_ptr_t qurt_interrupt_default_irq_handler_gptr;

/*======================================================================
                          FUNCTIONS
=======================================================================*/
void 
qurt_interrupt_register_default_irq( qurt_interrupt_handler_func_ptr_t 
                          qurt_interrupt_default_irq_handler_ptr )
{
    qurt_interrupt_default_irq_handler_gptr = qurt_interrupt_default_irq_handler_ptr;
}

void qurt_interrupt_default_irq_handler (uint32 n_irq)
{
    if(qurt_interrupt_default_irq_handler_gptr)
    {
        qurt_interrupt_default_irq_handler_gptr(n_irq);
    }
}

           