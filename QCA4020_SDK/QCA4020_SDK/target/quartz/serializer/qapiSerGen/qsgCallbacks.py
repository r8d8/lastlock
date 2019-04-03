# =============================================================================
# Copyright (c) 2018 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Copyright (c) 2018 Qualcomm Technologies, Inc.
# All rights reserved.
# Redistribution and use in source and binary forms, with or without modification, are permitted (subject to the limitations in the disclaimer below)
# provided that the following conditions are met:
# Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
# Neither the name of Qualcomm Technologies, Inc. nor the names of its contributors may be used to endorse or promote products derived
# from this software without specific prior written permission.
# NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
# BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
# OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import os
import sys
import re
from optparse import OptionParser
from xml.etree.ElementTree import Element, ElementTree, SubElement, Comment, tostring, parse
from xml.dom import minidom

from qsgUtils import *
import qsgCommon

# Generates the call to the application callback handler.
def GenerateAppCallbackFunctionCall(callbackElement):
   RetVal = ''
   CbParamName = ''

   # Get the callback parameter name.
   for argElement in callbackElement.findall('argument'):
      for createFunctionElement in callbackElement.findall('createFunction'):
         if argElement.get('name') == createFunctionElement.get('param'):
            CbParamName = argElement.get('name')
            break

   if CbParamName <> '':
      # Retrieve the the callback info and start the function call.
      RetVal = RetVal + '        qsResult = Callback_Retrieve(' + CbParamName + ', &qsCallbackInfo);\n\n'
      RetVal = RetVal + '        if((qsResult == ssSuccess) && (qsCallbackInfo.AppFunction != NULL))\n'
      RetVal = RetVal + '            (*(' + callbackElement.get('name') + ')qsCallbackInfo.AppFunction)('

      # Write all the function arguments, make sure to override the callback parameter with what
      # the application intended to register and cast to its type.
      for argElement in callbackElement.findall('argument'):
         if argElement.get('name') == CbParamName:
            if 'value' in argElement.get('attributes'):
               RetVal = RetVal + '(' + argElement.get('type') + ')qsCallbackInfo.AppParam, '
            else:
               RetVal = RetVal + '(' + argElement.get('type') + ' *)qsCallbackInfo.AppParam, '
         else:
            RetVal = RetVal + argElement.get('name') + ', '

      # Remove the last ', ' from the string
      RetVal = RetVal[0:-2]

      RetVal = RetVal + ');\n'
   else:
      RetVal = '        # TODO, handle unknown callpack parameter.\n'
      print '#warning# Unable to find callback parameter for type ' + callbackElement.get('name')

   return RetVal

# Generates code for registering callbacks from a list of function arguments.
def GenerateCallbackRegister(fileName, headerElement, functionElement, c_file):
   for arg in functionElement.findall('argument'):
      if arg.get('type') in qsgCommon.callbackList:
         if len(headerElement.findall('callback')) > 0:
            callback = None
            for cb in headerElement.findall('callback'):
               if cb.get('name') == arg.get('type'):
                  callback = cb
            if callback is not None:
               for cFunc in callback.findall('createFunction'):
                  if cFunc.get('name') == functionElement.get('name'):
                     c_file.write('    /* Handle event callback registration. */\n')
                     c_file.write('    uint32_t qsCbParam = 0;\n')
                     c_file.write('    CallbackInfo_t CallbackInfo;\n')
                     c_file.write('    CallbackInfo.TargetID = TargetID;\n')
                     if 'qapi_ble' in cFunc.get('name').lower():
                        c_file.write('    CallbackInfo.ModuleID = QS_MODULE_BLE;\n')
                     elif 'qapi_hmi' in cFunc.get('name').lower():
                        c_file.write('    CallbackInfo.ModuleID = QS_MODULE_HMI;\n')
                     elif 'qapi_twn' in cFunc.get('name').lower():
                        c_file.write('    CallbackInfo.ModuleID = QS_MODULE_THREAD;\n')
                     elif 'qapi_zb' in cFunc.get('name').lower():
                        c_file.write('    CallbackInfo.ModuleID = QS_MODULE_ZIGBEE;\n')
                     else:
                        print '#warning# Unhandled callback module for ' + callback.get('name') + ' in ' + cFunc.get('name')

                     # Set the callback info data.
                     c_file.write('    CallbackInfo.FileID = ' + fileName.upper() + '_FILE_ID;\n')
                     c_file.write('    CallbackInfo.CallbackID = ' + callback.get('name').upper() + '_CALLBACK_ID;\n')
                     c_file.write('    CallbackInfo.CallbackKey = 0;\n')
                     c_file.write('    CallbackInfo.AppFunction = ' + arg.get('name') + ';\n')
                     if cFunc.get('param') is not None and cFunc.get('param') <> '':
                        c_file.write('    CallbackInfo.AppParam = (uint32_t)' + cFunc.get('param') + ';\n')
                     else:
                        c_file.write('    CallbackInfo.AppParam = 0;\n')

                     # Register the callback.
                     c_file.write('    qsResult = Callback_Register(&qsCbParam, Host_' + callback.get('name') + '_Handler, &CallbackInfo);\n\n')
                     if cFunc.get('param') is not None:
                        c_file.write('    /* Override the callback parameter with the new one. */\n')
                        # Find the callback parameter type and cast the qsCbParam to it if necessary.
                        for arg in functionElement.findall('argument'):
                           if arg.get('name') == cFunc.get('param'):
                              if 'value' in arg.get('attributes'):
                                 if not 'uint32' in arg.get('type'):
                                    c_file.write('    ' + arg.get('name') + ' = (' + arg.get('type') + ')qsCbParam;\n\n')
                                 else:
                                    c_file.write('    ' + arg.get('name') + ' = qsCbParam;\n\n')
                              elif arg.get('attributes') == 'ptr':
                                 c_file.write('    ' + arg.get('name') + ' = (' + arg.get('type') + ' *)qsCbParam;\n\n')

# Generates code for registering callbacks from a list of function arguments.
def GenerateCallbackUnRegister(component, fileName, headerElement, functionElement, c_file, successLogicStr):
   if successLogicStr <> '':
      if len(headerElement.findall('callback')) > 0:
         for cb in headerElement.findall('callback'):
            for dFunc in cb.findall('destroyFunction'):
               if dFunc.get('name') == functionElement.get('name'):
                  c_file.write('                    /* Un-register the callback. */\n')
                  if dFunc.get('funcSuccess'):
                     c_file.write('                    if(' + successLogicStr + ')\n')
                     c_file.write('                        Callback_UnregisterByKey(MODULE_' + component.upper() + ', ' + fileName.upper() + '_FILE_ID, ' + cb.get('name').upper() + '_CALLBACK_ID, (uintptr_t)'
                                  + dFunc.get('ID')
                                  + ');\n\n')
                  else:
                     c_file.write('                    Callback_UnregisterByKey(MODULE_' + component.upper() + ', ' + fileName.upper() + '_FILE_ID, ' + cb.get('name').upper() + '_CALLBACK_ID, (uintptr_t)'
                                  + dFunc.get('ID')
                                  + ');\n\n')

# Generates code for registering callbacks from a list of function arguments.
def GenerateCallbackUpdate(headerElement, functionElement, c_file, successLogicStr):
   if successLogicStr <> '':
      if len(headerElement.findall('callback')) > 0:
         for cb in headerElement.findall('callback'):
            for cFunc in cb.findall('createFunction'):
               if cFunc.get('name') == functionElement.get('name'):
                  if cFunc.get('ID') != '0':
                     c_file.write('                    /* Update the event callback ID. */\n')
                     c_file.write('                    if(' + successLogicStr + ')\n')
                     c_file.write('                        qsResult = Callback_UpdateKey(qsCbParam, (uintptr_t)' + cFunc.get('ID') + ');\n')
                     c_file.write('                    else\n')
                     c_file.write('                        Callback_UnregisterByHandle(qsCbParam);\n\n')


