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
from qsgPackedReadWrite import *
from qsgCallbacks import *
import qsgCommon

# Creates auto generated QAPI callbacks and also manual callback code if needed
def CreateHostCallbackCode(xmlFile, component, root):
   manual_c_file = None
   # Find out if we need to create a manually written code file for callbacks in this module
   manualCbFileNeeded = False
   for CbElement in root.findall('callback'):
      if CbElement.get('name') in qsgCommon.manualCbList:
         manualCbFileNeeded = True
         if qsgCommon.generateManual:
            manual_c_file = CreateHostManualCallbackHandlerFiles(xmlFile, component, root)

   # Create the auto-gen code
   auto_c_file = CreateHostAutoCallbackHandlerFiles(xmlFile, component, root, manualCbFileNeeded)

   # Generate the host callback function handler prototypes
   for CbElement in root.findall('callback'):
      if CbElement.get('name') in qsgCommon.manualCbList:
         CreateHostManualCallbackHandlerStubs(CbElement, component, auto_c_file)
         if qsgCommon.generateManual:
            CreateHostCallbackHandlerFunctions(CbElement, component, manual_c_file, True)
      else:
         CreateHostCallbackHandlerFunctions(CbElement, component, auto_c_file, False)

   auto_c_file.close()
   if manual_c_file is not None:
      manual_c_file.close()

# Creates the header and C files for manual host callback handlers
def CreateHostManualCallbackHandlerFiles(xmlFile, component, root):
   manual_c_file = open(os.path.join(qsgCommon.manualDir, 'host', xmlFile.replace('.xml', '') + '_host_cb_mnl.c'), 'w+')
   manual_h_file = open(os.path.join(qsgCommon.manualDir, 'host', 'include', xmlFile.replace('.xml', '') + '_host_cb_mnl.h'), 'w+')

   manual_c_file.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')
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

   manual_c_file.write('#include <string.h>\n')
   manual_c_file.write('#include "qsCommon.h"\n')
   manual_c_file.write('#include "qsHost.h"\n')
   manual_c_file.write('#include "qsCallback.h"\n')
   manual_c_file.write('#include "qapi_' + component + '.h"\n')
   manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n')
   manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_host_cb_mnl.h"\n\n')

   # Generate the host headers.
   manual_h_file.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')
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
   manual_h_file.write('#include "qsCommon.h"\n')
   manual_h_file.write('#include "qapi_' + component + '.h"\n')
   manual_h_file.write('#include "' + xmlFile.replace('.xml', '') + '.h"\n\n')

   # Generate the host callback function handler prototypes
   for CbElement in root.findall('callback'):
      if CbElement.get('name') in qsgCommon.manualCbList:
         manual_h_file.write('void Mnl_Host_' + CbElement.get('name') + '_Handler(')
         if component!='wlan':
            manual_h_file.write('uint32_t CallbackID, CallbackInfo_t *Info, uint16_t BufferLength, uint8_t *Buffer);\n')
         else:
            manual_h_file.write('uint8_t device_ID, uint32_t cb_ID, void *application_Context, void *payload, uint32_t payload_Length);\n')

   manual_h_file.close()

   return manual_c_file

def CreateHostAutoCallbackHandlerFiles(xmlFile, component, root, manualCbFileNeeded):
   # Create the callback headers
   CreateHostCallbackHeaders(xmlFile, component, root)

   # Generate the host C callback code.
   c_file = open(os.path.join(qsgCommon.qapiDir, 'host', xmlFile.replace('.xml', '') + '_host_cb.c'), 'w+')

   c_file.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')
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
   c_file.write('#include <string.h>\n')
   c_file.write('#include "qsCommon.h"\n')
   c_file.write('#include "qsHost.h"\n')
   c_file.write('#include "qsCallback.h"\n')
   c_file.write('#include "qapi_' + component + '.h"\n')
   if manualCbFileNeeded:
      c_file.write('#include "' + xmlFile.replace('.xml', '') + '_host_cb_mnl.h"\n')
   c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n')
   c_file.write('#include "' + xmlFile.replace('.xml', '') + '_host_cb.h"\n\n')

   return c_file

# Creates headers for QAPI callback handlers
def CreateHostCallbackHeaders(xmlFile, component, root):
   c_file = open(os.path.join(qsgCommon.qapiDir, 'host', 'include', xmlFile.replace('.xml', '') + '_host_cb.h'), 'w+')

   # Generate the host headers.
   c_file.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')
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
   c_file.write('#include "qsCommon.h"\n')
   c_file.write('#include "qapi_' + component + '.h"\n')
   c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n\n')

   # Generate the host callback function handler prototypes
   for callbackElement in root.findall('callback'):
      c_file.write('void Host_' + callbackElement.get('name') + '_Handler(')
      if component!='wlan':
         c_file.write('uint32_t CallbackID, CallbackInfo_t *Info, uint16_t BufferLength, uint8_t *Buffer);\n')
      else:
         c_file.write('uint8_t device_ID, uint32_t cb_ID, void *application_Context, void *payload, uint32_t payload_Length);\n')

   c_file.close()

# Create stub function for calling manual callback handlers
def CreateHostManualCallbackHandlerStubs(CbElement, component, c_file):
   # Write the function name and manual handler
   if component!='wlan':
      c_file.write('void Host_' + CbElement.get('name') + '_Handler(uint32_t CallbackID, CallbackInfo_t *Info, uint16_t BufferLength, uint8_t *Buffer)\n')
      c_file.write('{\n')
      c_file.write('    Mnl_Host_' + CbElement.get('name') + '_Handler(CallbackID, Info, BufferLength, Buffer);\n')
      c_file.write('}\n')
   else:
      c_file.write('void Host_' + CbElement.get('name') + '_Handler(uint8_t device_ID, uint32_t cb_ID, void *application_Context, void *payload, uint32_t payload_Length)\n')
      c_file.write('{\n')
      c_file.write('    Mnl_Host_' + CbElement.get('name') + '_Handler(device_ID, cb_ID, application_Context, payload, payload_Length);\n')
      c_file.write('}\n')

# Creates code for handler host callbacks.
def CreateHostCallbackHandlerFunctions(callbackElement, component, c_file, isManualCode):
   if component=='wlan':
      CreateHostWlanCallbackHandlerFunctions(callbackElement, component, c_file, isManualCode)
      return

   decSize = 0
   numPtrs = 0
   structSizeStr = ""
   varStructSizeStr = ""

   # Write the function name
   c_file.write('void ')
   if isManualCode:
      c_file.write('Mnl_')
   c_file.write('Host_' + callbackElement.get('name') + '_Handler(uint32_t CallbackID, CallbackInfo_t *Info, uint16_t BufferLength, uint8_t *Buffer)\n')
   c_file.write('{\n')
   if isManualCode:
      c_file.write('\n#error Must complete this code manually.\n\n')
   c_file.write('    SerStatus_t        qsResult = ssSuccess;\n')
   c_file.write('    BufferListEntry_t *qsBufferList = NULL;\n')
   c_file.write('    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };\n')
   c_file.write('    CallbackInfo_t     qsCallbackInfo;\n')
   if (ParamsNeedIndex(callbackElement.findall('argument'), ['out']) == True):
      c_file.write('    uint32_t           qsIndex = 0;\n')
   c_file.write('    Boolean_t          qsPointerValid = FALSE;\n')
   c_file.write('\n\n')
   c_file.write('    UNUSED(qsPointerValid);\n\n')

   retElement = callbackElement.findall('return')[0]
   if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void'):
      c_file.write('    /* Return value. */\n')
      c_file.write('    ')
      if 'const' in retElement.get('attributes'):
         c_file.write('const')
      c_file.write(retElement.get('type') + ' ')
      if 'value' in retElement.get('attributes'):
         c_file.write('qsRetVal = 0;\n')
      if retElement.get('attributes') == 'ptr' or retElement.get('attributes') == 'ptr,const':
         c_file.write('*qsRetVal = NULL;\n')
      if retElement.get('attributes') == 'doubleptr' or retElement.get('attributes') == 'doubleptr,const':
         c_file.write('**qsRetVal = NULL;\n')
      c_file.write('\n')
   if len(callbackElement.findall('argument')) > 0:
      c_file.write('    /* Function parameters. */\n')
      for argElement in callbackElement.findall('argument'):
         if 'value' in argElement.get('attributes'):
            c_file.write('    ' + argElement.get('type') + ' ' + argElement.get('name'))
            if IsHandle(argElement.get('type')):
               c_file.write(' = NULL;\n')
            else:
               c_file.write(';\n')
         if (argElement.get('attributes') == 'ptr' or argElement.get('attributes') == 'ptr,const'):
            c_file.write('    ' + argElement.get('type') + ' *' + argElement.get('name') + ' = NULL;\n')
      c_file.write('\n')
   c_file.write('    InitializePackedBuffer(&qsInputBuffer, Buffer, BufferLength);\n')
   c_file.write('\n')
   c_file.write('    /* Read function parameters. */\n')

   c_file.write(MakePackedReadParametersString(callbackElement, callbackElement.findall('argument'), True, ['out'], '    ', '&qsInputBuffer', '&qsBufferList', '', True))

   c_file.write('    /* Find the callback and issue it. */\n')
   c_file.write('    if(qsResult == ssSuccess)\n')
   c_file.write('    {\n')
   c_file.write(GenerateAppCallbackFunctionCall(callbackElement));
   c_file.write('    }\n\n')
   c_file.write('    FreeBufferList(&qsBufferList);\n')
   c_file.write('}\n')

# Creates code for handler host callbacks.
def CreateHostWlanCallbackHandlerFunctions(callbackElement, component, c_file, isManualCode):
  decSize = 0
  numPtrs = 0
  structSizeStr = ""
  varStructSizeStr = ""

# Write the function name
  c_file.write('void ')
  if isManualCode:
     c_file.write('Mnl_')
  c_file.write('Host_' + callbackElement.get('name') + '_Handler(uint8_t device_ID, uint32_t cb_ID, void *application_Context, void *payload, uint32_t payload_Length)\n')
  c_file.write('{\n')

  if callbackElement.get('return') is None:
     c_file.write('    return;\n')
  elif callbackElement.get('return') == 'void':
     c_file.write('    return;\n')
  else:
     c_file.write('    return ssSuccess;\n')

  c_file.write('}\n\n')


