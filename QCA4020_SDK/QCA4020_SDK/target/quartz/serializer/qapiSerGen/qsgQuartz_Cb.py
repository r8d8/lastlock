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
import qsgCommon

def CreateQuartzCallbackHeaders(xmlFile, component, root):
   c_file = open(os.path.join(qsgCommon.qapiDir, 'qz', 'include', xmlFile.replace('.xml', '') + '_qz_cb.h'), 'w+')

   # Generate the Quartz headers.
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
   c_file.write('#include "idlist.h"\n')
   c_file.write('#include "qsCommon.h"\n')
   c_file.write('#include "qapi_' + component + '.h"\n')
   c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n\n')

   # Generate the Quartz callback function handler prototypes
   for callbackElement in root.findall('callback'):
      CreateQzCallbackHandlerDeclaration(callbackElement, c_file)

   c_file.close()

# Creates the files for manual callbacks
def CreateManualCbFiles(xmlFile, component):
   # Generate the Quartz C files.
   manual_h_file = open(os.path.join(qsgCommon.manualDir, 'qz', 'include', xmlFile.replace('.xml', '') + '_qz_cb_mnl.h'), 'w+')
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

   manual_c_file = open(os.path.join(qsgCommon.manualDir, 'qz', xmlFile.replace('.xml', '') + '_qz_cb_mnl.c'), 'w+')
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
   manual_c_file.write('#include "idlist.h"\n')
   manual_c_file.write('#include "qsCommon.h"\n')
   manual_c_file.write('#include "qsQuartz.h"\n')
   manual_c_file.write('#include "qsPack.h"\n')
   manual_c_file.write('#include "qapi_' + component + '.h"\n')
   manual_h_file.write('#include "qsCommon.h"\n')
   manual_h_file.write('#include "qapi_' + component + '.h"\n')
   manual_h_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n')
   manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n')
   manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_qz_cb_mnl.h"\n\n')

   return manual_c_file, manual_h_file

def CreateQuartzCallbackCode(xmlFile, component, root):
   # Find out if we need to create a manually written code file for functions in this module
   fileName = xmlFile.replace('.xml', '')
   manual_c_file = None
   manual_h_file = None
   manualCbFileNeeded = False
   for callbackElement in root.findall('callback'):
      if callbackElement.get('name') in qsgCommon.manualCbList:
         manualCbFileNeeded = True
         if qsgCommon.generateManual:
            manual_c_file, manual_h_file = CreateManualCbFiles(xmlFile, component)

   # Generate the Quartz C files.
   c_file = open(os.path.join(qsgCommon.qapiDir, 'qz', fileName + '_qz_cb.c'), 'w+')

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
   c_file.write('#include "qsQuartz.h"\n')
   c_file.write('#include "qapi_' + component + '.h"\n')
   c_file.write('#include "' + fileName + '_common.h"\n')
   if manualCbFileNeeded:
       c_file.write('#include "' + fileName + '_qz_cb_mnl.h"\n')
   c_file.write('#include "' + fileName + '_qz_cb.h"\n\n')

   CreateQuartzCallbackHeaders(xmlFile, component, root)

   # Generate the Quartz callback function handler prototypes
   for callbackElement in root.findall('callback'):
      if callbackElement.get('name') in qsgCommon.manualCbList:
         # Create the stub function that calls the manual callback
         CreateQzManualCallbackHandlerStubs(root, callbackElement, c_file)
         if qsgCommon.generateManual:
            # Create the manual callback declarations
            CreateQzManualCallbackHandlerDeclaration(root, callbackElement, manual_h_file)
            # Go ahead and generate the code in the manual file, but flag it for manual writing
            CreateQzCallbackHandlerFunctions(component, fileName, callbackElement, manual_c_file, True)
      else:
         CreateQzCallbackHandlerFunctions(component, fileName, callbackElement, c_file, False)

   # Close the files
   if manual_c_file is not None:
      manual_c_file.close()
   if manual_h_file is not None:
      manual_h_file.close()

   c_file.close()

def CreateQzManualCallbackHandlerDeclaration(root, callbackElement, c_file):
   # Handle return value
   retElement = callbackElement.findall('return')[0]

   # Write the return value.
   if 'const' in retElement.get('attributes'):
      c_file.write('const')
   c_file.write('\n' + retElement.get('type') + ' ')
   if 'ptr' in retElement.get('attributes'):
      c_file.write('*')
   if 'doubleptr' in retElement.get('attributes'):
      c_file.write('*')

   # Write function name and arguments
   c_file.write('Mnl_QZ_' + callbackElement.get('name') + '_Handler(')
   if len(callbackElement.findall('argument')) > 0:
      for argElement in callbackElement.findall('argument'):
         if 'value' in argElement.get('attributes'):
            if 'const' in argElement.get('attributes'):
               c_file.write('const ')
            c_file.write(argElement.get('type') + ' ' + argElement.get('name') + ', ')
         elif argElement.get('attributes') == 'ptr':
            c_file.write(argElement.get('type') + ' *' + argElement.get('name') + ', ')
         elif argElement.get('attributes') == 'ptr,const':
            c_file.write('const ' + argElement.get('type') + ' *' + argElement.get('name') + ', ')
         elif argElement.get('attributes') == 'doubleptr':
            c_file.write(argElement.get('type') + ' **' + argElement.get('name') + ', ')
         elif argElement.get('attributes') == 'doubleptr,const':
            c_file.write('const ' + argElement.get('type') + ' **' + argElement.get('name') + ', ')
         else:
            print '#warning# Unhandled argument type ' + argElement.get('name') + ' in ' + callbackElement.get('name')
      c_file.seek(-2,1)
      c_file.write(');\n\n')
   else:
      c_file.write('void);\n\n')

# Generates function definitions for packing structures.
def CreateQzCallbackHandlerDeclaration(callbackElement, c_file):
   if (callbackElement.findall('return')) > 0:
      # Write the return value
      retElement = callbackElement.findall('return')[0]
      if 'const' in retElement.get('attributes'):
         c_file.write('const ')
      c_file.write(retElement.get('type') + ' ')
      if 'ptr' in retElement.get('attributes'):
         c_file.write('*')
      if 'doubleptr' in retElement.get('attributes'):
         c_file.write('*')
      # Write the function name
      c_file.write('QZ_' + callbackElement.get('name') + '_Handler(')
      # Write the function arguments
      if len(callbackElement.findall('argument')) > 0:
         for argElement in callbackElement.findall('argument'):
            if 'const' in argElement.get('attributes'):
               c_file.write('const ')
            c_file.write(argElement.get('type') + ' ')
            if 'ptr' in argElement.get('attributes'):
               c_file.write('*')
            if 'doubleptr' in argElement.get('attributes'):
               c_file.write('*')
            c_file.write(argElement.get('name') + ', ')
         c_file.seek(-2,1)
         c_file.write(');\n')
      else:
         # Write void function parameter
         c_file.write('void);\n')

def CreateQzManualCallbackHandlerStubs(root, callbackElement, c_file):
   # Write out the function definition.
   if (callbackElement.findall('return')) > 0:
      # Write the return value
      retElement = callbackElement.findall('return')[0]
      if 'const' in retElement.get('attributes'):
         c_file.write('const ')
      c_file.write(retElement.get('type') + ' ')
      if 'ptr' in retElement.get('attributes'):
         c_file.write('*')
      if 'doubleptr' in retElement.get('attributes'):
         c_file.write('*')
      c_file.write('QZ_' + callbackElement.get('name') + '_Handler(')
      # Write the function arguments
      if len(callbackElement.findall('argument')) > 0:
         for argElement in callbackElement.findall('argument'):
            if 'const' in argElement.get('attributes'):
               c_file.write('const ')
            c_file.write(argElement.get('type') + ' ')
            if 'ptr' in argElement.get('attributes'):
               c_file.write('*')
            if 'doubleptr' in argElement.get('attributes'):
               c_file.write('*')
            c_file.write(argElement.get('name') + ', ')
         c_file.seek(-2,1)
         c_file.write(')\n')
      else:
         # Write void function parameter
         c_file.write('void)\n')
      c_file.write('{\n')

      if 'void' in callbackElement.findall('return')[0].get('type') and callbackElement.findall('return')[0].get('attributes') == 'value':
         c_file.write('    Mnl_QZ_' + callbackElement.get('name') + '_Handler(')
         for argElement in callbackElement.findall('argument'):
            c_file.write(argElement.get('name') + ', ')
         c_file.seek(-2,1)
         c_file.write(');\n}\n')
      else:
         c_file.write('    return(Mnl_' + callbackElement.get('name') + '_Handler(')
         if len(callbackElement.findall('argument')) > 0:
            for argElement in callbackElement.findall('argument'):
               c_file.write(argElement.get('name') + ', ')
            c_file.seek(-2,1)
            c_file.write('));\n}\n')
         else:
            c_file.write('void);\n}\n')

# Generates function definitions for packing structures.
def CreateQzCallbackHandlerFunctions(component, fileName, callbackElement, c_file, isManualCode):
   decSize = 0
   numPtrs = 0
   structSizeStr = ''
   varStructSizeStr = ''

   # Get the packed write parameters string.
   WriteParamString = MakePackedWriteParametersString(callbackElement, callbackElement.findall('argument'), True, ['out'], '      ', '&qsInputBuffer', '')

   # Write out the function definition.
   if (callbackElement.findall('return')) > 0:
      # Write the return value
      retElement = callbackElement.findall('return')[0]
      if 'const' in retElement.get('attributes'):
         c_file.write('const ')
      c_file.write(retElement.get('type') + ' ')
      if 'ptr' in retElement.get('attributes'):
         c_file.write('*')
      if 'doubleptr' in retElement.get('attributes'):
         c_file.write('*')
      # Write the function name
      if isManualCode:
         c_file.write('Mnl_')
      c_file.write('QZ_' + callbackElement.get('name') + '_Handler(')
      # Write the function arguments
      if len(callbackElement.findall('argument')) > 0:
         for argElement in callbackElement.findall('argument'):
            if 'const' in argElement.get('attributes'):
               c_file.write('const ')
            c_file.write(argElement.get('type') + ' ')
            if 'ptr' in argElement.get('attributes'):
               c_file.write('*')
            if 'doubleptr' in argElement.get('attributes'):
               c_file.write('*')
            c_file.write(argElement.get('name') + ', ')
         c_file.seek(-2,1)
         c_file.write(')\n')
      else:
         # Write void function parameter
         c_file.write('void)\n')
      c_file.write('{\n')

   # Generate an error if this is supposed to be manual code
   if isManualCode:
      c_file.write('\n#error Must complete this code manually.\n\n')

   # Create local variables.
   c_file.write('    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };\n')
   c_file.write('    SerStatus_t        qsResult = ssSuccess;\n')
   c_file.write('    uint32_t           qsIndex = 0;\n')
   # c_file.write('    uint32_t           FunctionID = 0;\n')
   c_file.write('    uint16_t           qsSize = 0;\n\n')

   c_file.write('    UNUSED(qsIndex);\n\n')

   if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void'):
      # Create return variable
      c_file.write('    /* Return value. */\n')
      if 'value' in retElement.get('attributes'):
         c_file.write('    ' + retElement.get('type') + ' qsRetVal = 0;\n\n')
      elif retElement.get('attributes') == 'ptr':
         c_file.write('    ' + retElement.get('type') + ' *qsRetVal = NULL;\n\n')
      elif retElement.get('attributes') == 'ptr,const':
         c_file.write('    const ' + retElement.get('type') + ' *qsRetVal = NULL;\n\n')
      elif retElement.get('attributes') == 'doubleptr':
         c_file.write('    ' + retElement.get('type') + ' **qsRetVal = NULL;\n\n')
      elif retElement.get('attributes') == 'doubleptr,const':
         c_file.write('    const ' + retElement.get('type') + ' **qsRetVal = NULL;\n\n')
      else:
         print '#warning# Unhandled return type ' + retElement.get('type') + ' in ' + callbackElement.get('name')

   # Calculate output buffer size.
   c_file.write('    /* Calculate size of packed function arguments. */\n')
   for argElement in callbackElement.findall('argument'):
      if argElement.get('type') in qsgCommon.callbackList:
         structSizeStr = structSizeStr
      elif 'value' in argElement.get('attributes'):
         if IsPrimitive(argElement.get('type')):
            decSize = decSize + GetPrimitiveSize(argElement.get('type'))
         else:
            structSizeStr = structSizeStr + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + argElement.get('name') + ') + '
      elif (argElement.get('attributes') == 'ptr' or argElement.get('attributes') == 'ptr,const'):
         if argElement.get('lengthParam') == '1':
            numPtrs = numPtrs + 1
            structSizeStr = structSizeStr + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + argElement.get('name') + ') + '
         elif isParamLengthInt(argElement.get('lengthParam')) == True:
            numPtrs = numPtrs + 1
            structSizeStr = structSizeStr + argElement.get('lengthParam') + ' + '
         elif argElement.get('lengthParam') == '__strlen__':
            numPtrs = numPtrs + 1
            structSizeStr = structSizeStr + '((' + argElement.get('name') + ' != NULL) ? (strlen((const char *)' + argElement.get('name') + ')+1) : 0) + '
         else:
            # Loop through variable length data.
            for otherArg in callbackElement.findall('argument'):
               if otherArg.get('name') == argElement.get('lengthParam'):
                  numPtrs = numPtrs + 1
                  if 'value' in otherArg.get('attributes'):
                     if IsPrimitive(argElement.get('type')):
                        varStructSizeStr = varStructSizeStr + '    qsSize = qsSize + ((' + argElement.get('lengthParam') + ')*(' + str(GetPrimitiveSize(argElement.get('type'))) + '));\n'
                     else:
                        varStructSizeStr = varStructSizeStr + '    for (qsIndex = 0; qsIndex < ' + argElement.get('lengthParam') + '; qsIndex++)\n'
                        varStructSizeStr = varStructSizeStr + '    {\n'
                        varStructSizeStr = varStructSizeStr + '        qsSize = qsSize + ' + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + '(&' + argElement.get('name') + ')[qsIndex]);\n'
                        varStructSizeStr = varStructSizeStr + '    }\n'
                  else:
                     if IsPrimitive(argElement.get('type')):
                        varStructSizeStr = varStructSizeStr + '    qsSize = qsSize + ((*' + argElement.get('lengthParam') + ')*(' + str(GetPrimitiveSize(argElement.get('type'))) + '));\n'
                     else:
                        varStructSizeStr = varStructSizeStr + '    for (qsIndex = 0; qsIndex < *' + argElement.get('lengthParam') + '; qsIndex++)\n'
                        varStructSizeStr = varStructSizeStr + '    {\n'
                        varStructSizeStr = varStructSizeStr + '        qsSize = qsSize + ' + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + '(&' + argElement.get('name') + ')[qsIndex]);\n'
                        varStructSizeStr = varStructSizeStr + '    }\n'

   if numPtrs > 0:
      structSizeStr = structSizeStr + '(QS_POINTER_HEADER_SIZE * ' + str(numPtrs) + ') + '

   if decSize == 0 and structSizeStr == '':
      c_file.write('    qsSize = 0')
   if decSize <> 0 and structSizeStr == '':
      c_file.write('    qsSize = ' + str(decSize))
   if decSize <> 0 and structSizeStr <> '':
      c_file.write('    qsSize = ('  + str(decSize) + ' + ' + structSizeStr)
      c_file.seek(-3,1)
      c_file.write(')')
   if decSize == 0 and structSizeStr <> '':
      c_file.write('    qsSize = (' + structSizeStr)
      c_file.seek(-3,1)
      c_file.write(')')
   c_file.write(';\n\n')

   if varStructSizeStr <> '':
      c_file.write(varStructSizeStr);
      c_file.write('\n');

   # Allocate packed buffer
   c_file.write('    if(AllocatePackedBuffer(NULL, QS_ASYNC_E, MODULE_' + component.upper() + ', ' + fileName.upper() + '_FILE_ID, ' + callbackElement.get('name').upper() + '_CALLBACK_ID, &qsInputBuffer, qsSize))\n')
   c_file.write('    {\n')

   # Write each element to the buffer.
   if len(callbackElement.findall('argument')) > 0:
      c_file.write('        /* Write arguments packed. */\n')
      c_file.write(WriteParamString)

   # Send command and get response.
   c_file.write('        /* Send the event. */\n')
   c_file.write('        if(qsResult == ssSuccess)\n')
   c_file.write('            qsResult = SendEvent(&qsInputBuffer);\n')
   c_file.write('    }\n')
   c_file.write('    else\n')
   c_file.write('        qsResult = ssAllocationError;\n\n')
   c_file.write('#ifdef ENABLE_DEBUG_CALLBACKS\n')
   c_file.write('    if(qsResult != ssSuccess)\n')
   c_file.write('        SendErrorCallback(MODULE_' + component.upper() + ', ' + fileName.upper() + '_FILE_ID, ' + callbackElement.get('name').upper() + '_CALLBACK_ID);\n')
   c_file.write('#endif // ENABLE_DEBUG_CALLBACKS\n')
   c_file.write('}\n')

