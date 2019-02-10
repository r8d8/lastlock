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

#include <stdio.h>
#include <unistd.h>
#include <string.h>

size_t iotd_strlcpy(char *Destination, const char *Source, size_t Length)
{
   char       *dest  = Destination;
   const char *src       = Source;
   size_t      len       = Length;

   /* Copy all bytes that can fit */
   if (len != 0)
   {
      while (--len != 0)
      {
         if ((*dest++ = *src++) == '\0')
         {
            break;
         }
      }
   }

   /* Not enough room in dest, add NULL and traverse rest of source */
   if (len == 0)
   {
      if (Length != 0)
      {
         *dest = '\0';        /* NULL-terminate dest */
      }

      while (*src++)
         ;
   }

   return(src - Source - 1);    /* count does not include NULL */
}


size_t iotd_strlcat(char *Destination, const char *Source, size_t Length)
{
    size_t  len = 0;
    size_t  slen;
    char    *dest  = Destination;
    const char *src = Source;

    slen = strlen(Source);
    while (*dest && Length > 0){
        dest++;
        len++;
        Length--;
    }

    while (*src && Length-- > 1){
        *dest++ = *src++;
    }

    if (Length == 1 || *src == 0)
        *dest = '\0';

    return (slen + len);
}
