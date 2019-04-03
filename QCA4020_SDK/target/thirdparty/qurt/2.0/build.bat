@ECHO OFF
REM #/***************************************************************************************
REM #    Copyright (c) 2017 Linux Foundation.
REM #    All rights reserved.
REM #
REM #    Redistribution and use in source and binary forms, with or without modification,
REM #    are permitted (subject to the limitations in the disclaimer below)provided that
REM #    the following conditions are met:
REM #
REM #    1.Redistributions of source code must retain the above copyright notice, this list
REM #      of conditions and the following disclaimer.
REM #
REM #    2.Redistributions in binary form must reproduce the above copyright notice, this list
REM #      of conditions and the following disclaimer in the documentation and/or other
REM #      materials provided with the distribution.
REM #
REM #    3.Neither the name of [Owner Organization] nor the names of its contributors may be
REM #      used to endorse or promote products derived from this software without specific
REM #      prior written permission.
REM #
REM #    NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
REM #    LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
REM #    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
REM #    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR APARTICULAR PURPOSE ARE
REM #    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER ORCONTRIBUTORS BE LIABLEFOR ANY
REM #    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIALDAMAGES (INCLUDING,
REM #    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
REM #    OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
REM #    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE  OR OTHERWISE)
REM #    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
REM #    OF SUCH DAMAGE.
REM #
REM #****************************************************************************************/
REM #
REM #****************************************************************************************/
REM #
REM #    Build script to build QuRT library with GCC, GNU tool chain.
REM #
REM #    Please use this as reference file for building QuRT Library.
REM #
REM #    In order to build QuRT library following dependencies has to be met -
REM #    1. Update to INCLUDES PATH with location of QuRT header files and
REM #       other header files supplied by SDK.
REM #    2. Update to INCLUDES PATH with location of FreeRTOS header files.
REM #
REM #****************************************************************************************/

SET OBJDIR=obj
SET OUTDIR=output
SET CC=arm-none-eabi-gcc
SET AR=arm-none-eabi-ar

REM Specify COPT FLAGS
SET COPTS=-c -g -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mfloat-abi=hard -fno-inline-functions -Os -O3 -fno-zero-initialized-in-bss -std=c99 -fno-short-enums -mapcs-frame -gdwarf-3 

REM Specify preprocessor flag/feature defines
SET DEFINES=-D FEATURE_MUTEX_PI_RECURSIVE -D QURT_THREAD_MAX_PRIORITIES=32

SET ROOT=..\..\..
SET AWSROOT=..\..\aws_freertos
SET AWSCOMM=%AWSROOT%\demos\qcom\qca402x\common

REM Specify Include paths here
SET INCLUDES=-I.
SET INCLUDES=%INCLUDES% -I"%AWSCOMM%\application_code\qcom_code"
SET INCLUDES=%INCLUDES% -I"%AWSCOMM%\config_files"
SET INCLUDES=%INCLUDES% -I"%AWSROOT%\lib\include"
SET INCLUDES=%INCLUDES% -I"%AWSROOT%\lib\include\private"
SET INCLUDES=%INCLUDES% -I"%ROOT%\include\bsp"
  
RMDIR /s/q "%OUTDIR%" >NUL 2>&1
TIMEOUT /t 1          >NUL 2>&1

RMDIR /s/q "%OBJDIR%" >NUL 2>&1
TIMEOUT /t 1          >NUL 2>&1

MKDIR %OUTDIR%
MKDIR %OBJDIR%

REM Set CFLAGS
SET CFLAGS=%COPTS% %DEFINES% %INCLUDES%

SET CSRCS=qurt_init.c
SET CSRCS=%CSRCS% qurt_pimutex.c
SET CSRCS=%CSRCS% qurt_pipe.c
SET CSRCS=%CSRCS% qurt_rmutex.c
SET CSRCS=%CSRCS% qurt_signal.c
SET CSRCS=%CSRCS% qurt_system.c
SET CSRCS=%CSRCS% qurt_thread.c
SET CSRCS=%CSRCS% qurt_timer.c

SET SRCS_SOM=qurt_interrupt.c
SET SRCS_SOM=%SRCS_SOM% qurt_interrupt_asm.S

echo %CFLAGS%

REM Compile the source
FOR %%F IN (%CSRCS%) DO (
   ECHO Building %%F
   ECHO "%CC%" %CFLAGS% -o"%OBJDIR%\%%~nF.o" "%SrcDir%\%%F"
   "%CC%" %CFLAGS% -o"%OBJDIR%\%%~nF.o" "%%F"

   "%AR%" -r "%OUTDIR%\qurt.lib" "%OBJDIR%\%%~nF.o"
)

SET SRC_SOM_OBJS=""
FOR %%F IN (%SRCS_SOM%) DO (
   ECHO Building %%F
   "%CC%" %CFLAGS% -o"%OBJDIR%\%%~nF.o" "%%F"

   "%AR%" -r "%OUTDIR%\qurt_shared.lib" "%OBJDIR%\%%~nF.o"
)

