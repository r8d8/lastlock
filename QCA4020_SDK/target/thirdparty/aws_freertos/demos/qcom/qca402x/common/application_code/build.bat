@ECHO OFF
REM Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
REM All Rights Reserved
REM Copyright (c) 2018 Qualcomm Technologies, Inc.
REM All rights reserved.
REM Redistribution and use in source and binary forms, with or without modification, are permitted (subject to the limitations in the disclaimer below)
REM provided that the following conditions are met:
REM Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
REM Redistributions in binary form must reproduce the above copyright notice,
REM this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
REM Neither the name of Qualcomm Technologies, Inc. nor the names of its contributors may be used to endorse or promote products derived
REM from this software without specific prior written permission.
REM NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
REM THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
REM BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
REM IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
REM OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
REM LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
REM WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
REM EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

REM #/***************************************************************************************
REM #    Copyright (c) 2018 Linux Foundation.
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
REM #    Build script to build FreeRTOS library with GCC, GNU tool chain
REM #
REM #    Please use this as reference file for building FreeRTOS Library.
REM #
REM #    In order to build FreeRTOS library following dependencies has to be met -
REM #    1. Update to INCLUDES PATH with location of FreeRTOS header files.
REM #    2. Update to INCLUDES PATH with location of FreeRTOSConfig.h
REM #    3. Update to INCLUDES PATH with location of portmacro.h
REM #    4. Update to SOURCE PATH with location of port.c
REM #
REM #****************************************************************************************/

SET OUTDIR=output
SET CC=arm-none-eabi-gcc
SET AR=arm-none-eabi-ar

REM Specify COPT FLAGS
SET COPTS=-c -g -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mfloat-abi=hard -fno-inline-functions -Os -O3 -fno-zero-initialized-in-bss -std=c99 -fno-short-enums -mapcs-frame -gdwarf-3

REM Specify preprocessor flag/feature defines
SET DEFINES=
SET AWSROOT=..\..\..\..\..

REM Specify Include paths here
SET INCLUDES=-I.\qcom_code
SET INCLUDES=%INCLUDES% -I"..\config_files" -I"%AWSROOT%\lib\include" -I"%AWSROOT%\lib\include\private"

RMDIR /s/q "%OUTDIR%" >NUL 2>&1
TIMEOUT /t 1          >NUL 2>&1

MKDIR %OUTDIR%

REM Set CFLAGS
SET CFLAGS=%COPTS% %DEFINES% %INCLUDES%

SET CSRCS=%AWSROOT%\lib\FreeRTOS\tasks.c
SET CSRCS=%CSRCS%  %AWSROOT%\lib\FreeRTOS\queue.c
SET CSRCS=%CSRCS%  %AWSROOT%\lib\FreeRTOS\stream_buffer.c
SET CSRCS=%CSRCS%  %AWSROOT%\lib\FreeRTOS\event_groups.c
SET CSRCS=%CSRCS%  %AWSROOT%\lib\FreeRTOS\list.c
SET CSRCS=%CSRCS%  %AWSROOT%\lib\FreeRTOS\timers.c
SET CSRCS=%CSRCS%  %AWSROOT%\lib\FreeRTOS\portable\MemMang\heap_4.c
SET CSRCS=%CSRCS% .\qcom_code\port.c


REM Compile the source and generate the lib
FOR %%F IN (%CSRCS%) DO (
   ECHO Building %%F
REM   ECHO "%CC%" %CFLAGS% -o"%OUTDIR%\%%~nF.o" "%SrcDir%\%%F"
   "%CC%" %CFLAGS% -o"%OUTDIR%\%%~nF.o" "%%F"

   "%AR%" -r "%OUTDIR%\free_rtos.lib" "%OUTDIR%\%%~nF.o"
)


