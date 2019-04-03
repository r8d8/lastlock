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

class ArgStr:
   def __init__(self):
      self.decSize          = 0
      self.numPtrs          = 0
      self.structSizeStr    = ''
      self.varStructSizeStr = ''


   def CalcSizeForVariableLengthData(self, functionElement, argElement):
      # Loop through variable length data.
      for otherArg in functionElement.findall('argument'):
         if otherArg.get('name') == argElement.get('lengthParam'):
            if 'yes' == argElement.get('lengthFirst'):
               self.GenerateQAPIFunctionArguments(functionElement, otherArg)

            self.numPtrs = self.numPtrs + 1
            if 'value' in otherArg.get('attributes'):
               if IsPrimitive(argElement.get('type')):
                  self.varStructSizeStr = self.varStructSizeStr + '    qsSize = qsSize + ((' + argElement.get('lengthParam') + ')*(' + str(GetPrimitiveSize(argElement.get('type'))) + '));\n'
               else:
                  self.varStructSizeStr = self.varStructSizeStr + '    for (qsIndex = 0; qsIndex < ' + argElement.get('lengthParam') + '; qsIndex++)\n'
                  self.varStructSizeStr = self.varStructSizeStr + '    {\n'
                  self.varStructSizeStr = self.varStructSizeStr + '        qsSize = qsSize + ' + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + '&' + argElement.get('name') + '[qsIndex]);\n'
                  self.varStructSizeStr = self.varStructSizeStr + '    }\n'
            else:
               if IsPrimitive(argElement.get('type')):
                  self.varStructSizeStr = self.varStructSizeStr + '    qsSize = qsSize + ((*' + argElement.get('lengthParam') + ')*(' + str(GetPrimitiveSize(argElement.get('type'))) + '));\n'
               else:
                  self.varStructSizeStr = self.varStructSizeStr + '    for (qsIndex = 0; qsIndex < *' + argElement.get('lengthParam') + '; qsIndex++)\n'
                  self.varStructSizeStr = self.varStructSizeStr + '    {\n'
                  self.varStructSizeStr = self.varStructSizeStr + '        qsSize = qsSize + ' + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + '&' + argElement.get('name') + '[qsIndex]);\n'
                  self.varStructSizeStr = self.varStructSizeStr + '    }\n'


   def GenerateQAPIFunctionArguments(self, functionElement, argElement):
      # Generate packing code for each argument
      if argElement.get('type') in qsgCommon.callbackList:
         self.structSizeStr = self.structSizeStr
      elif 'value' in argElement.get('attributes'):
         if IsPrimitive(argElement.get('type')):
            self.decSize = self.decSize + GetPrimitiveSize(argElement.get('type'))
         else:
            self.structSizeStr = self.structSizeStr + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + '&' + argElement.get('name') + ') + '
      elif (argElement.get('attributes') == 'ptr' or argElement.get('attributes') == 'ptr,const'):
         if (argElement.get('iotype') is not None and 'in' in argElement.get('iotype')):
            if argElement.get('lengthParam') == '1':
               self.numPtrs = self.numPtrs + 1
               self.structSizeStr = self.structSizeStr + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + argElement.get('name') + ') + '
            elif argElement.get('lengthParam') == '__strlen__':
               self.numPtrs = self.numPtrs + 1
               self.structSizeStr = self.structSizeStr + '((' + argElement.get('name') + ' != NULL) ? (strlen((const char *)' + argElement.get('name') + ')+1) : 0) + '
            elif isParamLengthInt(argElement.get('lengthParam')) == True:
                self.numPtrs = self.numPtrs + 1
                self.structSizeStr = self.structSizeStr + argElement.get('lengthParam') + ' + '
            else:
               self.CalcSizeForVariableLengthData(functionElement, argElement)

         else:
            self.numPtrs = self.numPtrs + 1

      return


# Creates auto generated QAPI functions and also manual function code if needed
def CreateHostQAPICode(xmlFile, component, root):
   # Find out if we need to create a manually written code file for functions in this module
   fileName = xmlFile.replace('.xml', '')
   c_file = None
   h_file = None
   manual_c_file = None
   manual_h_file = None
   manualFuncFileNeeded = False
   for functionElement in root.findall('function'):
      if functionElement.get('name') in qsgCommon.manualFuncList:
         manualFuncFileNeeded = True
         if qsgCommon.generateManual:
            manual_c_file, manual_h_file = CreateManualFiles(xmlFile, component, root)

   h_file = open(os.path.join(qsgCommon.qapiDir, 'host', 'include', fileName + '_host.h'), 'w+')
   h_file.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')
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
   h_file.write('#include "' + fileName + '.h"\n')

   c_file = open(os.path.join(qsgCommon.qapiDir, 'host', fileName + '_host.c'), 'w+')
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

   c_file.write('#include <stdint.h>\n')
   c_file.write('#include <string.h>\n')
   c_file.write('#include "qsCommon.h"\n')
   c_file.write('#include "qsHost.h"\n')
   c_file.write('#include "qsCallback.h"\n')
   c_file.write('#include "idlist.h"\n')
   c_file.write('#include "qapi_' + component + '.h"\n')
   if manualFuncFileNeeded:
      c_file.write('#include "' + fileName + '_host_mnl.h"\n')
   c_file.write('#include "' + fileName + '_common.h"\n')
   if len(root.findall('callback')) > 0:
      c_file.write('#include "' + fileName + '_host_cb.h"\n')
   for includeElement in root.findall('include'):
      if 'qapi_' in includeElement.get('name') and not 'qapi_status' in includeElement.get('name') and not 'qapi_types' in includeElement.get('name'):
         c_file.write('#include "' + includeElement.get('name').replace('.h', '').replace('.','').replace('qapi/','').replace('/','') + '_common.h"\n')

   # Generate the function packing functions
   for functionElement in root.findall('function'):
      GenerateQAPIFunctionDeclaration(root, functionElement, h_file)
      if functionElement.get('name') in qsgCommon.manualFuncList:
         # Create the stub function that calls the manual function
         GenerateQAPIManualFunctionStubs(root, functionElement, c_file)
         c_file.write(GenerateQAPIWrapperFunctionStubs(root, functionElement))
         if qsgCommon.generateManual:
            # Create the manual function declarations
            GenerateQAPIManualFunctionDeclaration(root, functionElement, manual_h_file)
            # Go ahead and generate the code in the manual file, but flag it for manual writing
            GenerateQAPIFunctions(component, fileName, root, functionElement, manual_c_file, True)
      else:
         GenerateQAPIFunctions(component, fileName, root, functionElement, c_file, False)

   # Close the files
   if manual_c_file is not None:
      manual_c_file.close()
   if manual_h_file is not None:
      manual_h_file.close()
   h_file.close()
   c_file.close()

def CreateManualFiles(xmlFile, component, root):
   manual_h_file = open(os.path.join(qsgCommon.manualDir, 'host', 'include', xmlFile.replace('.xml', '') + '_host_mnl.h'), 'w+')
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

   manual_c_file = open(os.path.join(qsgCommon.manualDir, 'host', xmlFile.replace('.xml', '') + '_host_mnl.c'), 'w+')
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
   manual_c_file.write('#include <stdint.h>\n')
   manual_c_file.write('#include <string.h>\n')
   manual_c_file.write('#include "idlist.h"\n')
   manual_c_file.write('#include "qsCommon.h"\n')
   manual_c_file.write('#include "qsHost.h"\n')
   manual_c_file.write('#include "qsCallback.h"\n')
   manual_c_file.write('#include "qapi_' + component + '.h"\n')
   manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n')
   manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_host_mnl.h"\n')

   if len(root.findall('callback')) > 0:
      manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_host_cb.h"\n')
   for includeElement in root.findall('include'):
      if 'qapi_' in includeElement.get('name') and not 'qapi_status' in includeElement.get('name') and not 'qapi_types' in includeElement.get('name'):
         manual_c_file.write('#include "' + includeElement.get('name').replace('.h', '').replace('.','').replace('qapi/','').replace('/','') + '_common.h"\n')
         manual_h_file.write('#include "' + includeElement.get('name').replace('.h', '').replace('.','').replace('qapi/','').replace('/','') + '_common.h"\n')

   return manual_c_file, manual_h_file

# Generates stubs for calling manually written pack functions.
def GenerateQAPIManualFunctionStubs(headerElement, functionElement, c_file):
   wrapper_func = ''
   # Handle return value
   retElement = functionElement.findall('return')[0]

   # Write the return value.
   if 'const' in retElement.get('attributes'):
      c_file.write('const')
   c_file.write('\n' + retElement.get('type') + ' ')
   if 'ptr' in retElement.get('attributes'):
      c_file.write('*')
   if 'doubleptr' in retElement.get('attributes'):
      c_file.write('*')

   # Write function name and arguments
   c_file.write('_' + functionElement.get('name') + '(uint8_t TargetID, ')
   if len(functionElement.findall('argument')) > 0:
      for argElement in functionElement.findall('argument'):
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
            print '#warning# Unhandled argument type ' + argElement.get('name') + ' in ' + functionElement.get('name')
   c_file.seek(-2,1)
   c_file.write(')\n{\n')

   if 'void' in retElement.get('type') and retElement.get('attributes') == 'value':
      c_file.write('    Mnl_' + functionElement.get('name') + '(TargetID, ')
      for argElement in functionElement.findall('argument'):
         c_file.write(argElement.get('name') + ', ')
      c_file.seek(-2,1)
      c_file.write(');\n}\n')
   else:
      c_file.write('    return(Mnl_' + functionElement.get('name') + '(TargetID, ')
      if len(functionElement.findall('argument')) > 0:
         for argElement in functionElement.findall('argument'):
            c_file.write(argElement.get('name') + ', ')
      c_file.seek(-2,1)
      c_file.write('));\n}\n')


def GenerateQAPIManualFunctionDeclaration(root, functionElement, manual_h_file):
   # Handle return value
   retElement = functionElement.findall('return')[0]

   # Write the return value.
   if 'const' in retElement.get('attributes'):
      manual_h_file.write('const')
   manual_h_file.write('\n' + retElement.get('type') + ' ')
   if 'ptr' in retElement.get('attributes'):
      manual_h_file.write('*')
   if 'doubleptr' in retElement.get('attributes'):
      manual_h_file.write('*')

   # Write function name and arguments
   manual_h_file.write('Mnl_' + functionElement.get('name') + '(uint8_t TargetID, ')
   if len(functionElement.findall('argument')) > 0:
      for argElement in functionElement.findall('argument'):
         if 'value' in argElement.get('attributes'):
            if 'const' in argElement.get('attributes'):
               manual_h_file.write('const ')
            manual_h_file.write(argElement.get('type') + ' ' + argElement.get('name') + ', ')
         elif argElement.get('attributes') == 'ptr':
            manual_h_file.write(argElement.get('type') + ' *' + argElement.get('name') + ', ')
         elif argElement.get('attributes') == 'ptr,const':
            manual_h_file.write('const ' + argElement.get('type') + ' *' + argElement.get('name') + ', ')
         elif argElement.get('attributes') == 'doubleptr':
            manual_h_file.write(argElement.get('type') + ' **' + argElement.get('name') + ', ')
         elif argElement.get('attributes') == 'doubleptr,const':
            manual_h_file.write('const ' + argElement.get('type') + ' **' + argElement.get('name') + ', ')
         else:
            print '#warning# Unhandled argument type ' + argElement.get('name') + ' in ' + functionElement.get('name')
   manual_h_file.seek(-2,1)
   manual_h_file.write(');\n')


# Generates stubs for calling manually written pack functions.
def GenerateQAPIWrapperFunctionStubs(headerElement, functionElement):
   wrapper_func = ''

   # Handle return value
   retElement = functionElement.findall('return')[0]

   # Write the return value.
   if 'const' in retElement.get('attributes'):
      wrapper_func += 'const'
   wrapper_func = wrapper_func + '\n' + retElement.get('type') + ' '
   if 'ptr' in retElement.get('attributes'):
      wrapper_func += '*'
   if 'doubleptr' in retElement.get('attributes'):
      wrapper_func += '*'

   # Write function name and arguments
   wrapper_func = wrapper_func + functionElement.get('name') + '('
   if len(functionElement.findall('argument')) > 0:
      for argElement in functionElement.findall('argument'):
         if 'value' in argElement.get('attributes'):
            if 'const' in argElement.get('attributes'):
               wrapper_func += 'const '
            wrapper_func = wrapper_func + argElement.get('type') + ' ' + argElement.get('name') + ', '
         elif argElement.get('attributes') == 'ptr':
            wrapper_func = wrapper_func + argElement.get('type') + ' *' + argElement.get('name') + ', '
         elif argElement.get('attributes') == 'ptr,const':
            wrapper_func = wrapper_func + 'const ' + argElement.get('type') + ' *' + argElement.get('name') + ', '
         elif argElement.get('attributes') == 'doubleptr':
            wrapper_func = wrapper_func + argElement.get('type') + ' **' + argElement.get('name') + ', '
         elif argElement.get('attributes') == 'doubleptr,const':
            wrapper_func = wrapper_func + 'const ' + argElement.get('type') + ' **' + argElement.get('name') + ', '
         else:
            print '#warning# Unhandled argument type ' + argElement.get('name') + ' in ' + functionElement.get('name')
      wrapper_func = wrapper_func[:-2]
   wrapper_func += ')\n{\n'

   if 'void' in retElement.get('type') and retElement.get('attributes') == 'value':
      wrapper_func = wrapper_func + '   _' + functionElement.get('name') + '(qsTargetId, '
      for argElement in functionElement.findall('argument'):
         wrapper_func = wrapper_func + argElement.get('name') + ', '
      wrapper_func = wrapper_func[:-2]
      wrapper_func += ');\n}\n'

   else:
      wrapper_func = wrapper_func + '   return _' + functionElement.get('name') + '(qsTargetId, '
      if len(functionElement.findall('argument')) > 0:
         for argElement in functionElement.findall('argument'):
             wrapper_func = wrapper_func + argElement.get('name') + ', '
      wrapper_func = wrapper_func[:-2]
      wrapper_func += ');\n}\n'

   return wrapper_func

def GenerateQAPIFunctionDeclaration(root, functionElement, h_file):
   # Handle return value
   retElement = functionElement.findall('return')[0]
   # Write the return value.
   if 'const' in retElement.get('attributes'):
      h_file.write('const')
   h_file.write('\n' + retElement.get('type') + ' ')
   if 'ptr' in retElement.get('attributes'):
      h_file.write('*')
   if 'doubleptr' in retElement.get('attributes'):
      h_file.write('*')

   # Write function name and arguments
   h_file.write('_' + functionElement.get('name') + '(uint8_t TargetID, ')
   if len(functionElement.findall('argument')) > 0:
      for argElement in functionElement.findall('argument'):
         if 'value' in argElement.get('attributes'):
            if 'const' in argElement.get('attributes'):
               h_file.write('const ')
            h_file.write(argElement.get('type') + ' ' + argElement.get('name') + ', ')

         elif argElement.get('attributes') == 'ptr':
            h_file.write(argElement.get('type') + ' *' + argElement.get('name') + ', ')

         elif argElement.get('attributes') == 'ptr,const':
            h_file.write('const ' + argElement.get('type') + ' *' + argElement.get('name') + ', ')

         elif argElement.get('attributes') == 'doubleptr':
            h_file.write(argElement.get('type') + ' **' + argElement.get('name') + ', ')

         elif argElement.get('attributes') == 'doubleptr,const':
            h_file.write('const ' + argElement.get('type') + ' **' + argElement.get('name') + ', ')

         else:
            print '#warning# Unhandled argument type ' + argElement.get('name') + ' in ' + functionElement.get('name')

   h_file.seek(-2,1)
   h_file.write(');\n')


# Generates functions for packing functions (qapi pack functions).
def GenerateQAPIFunctions(component, fileName, headerElement, functionElement, c_file, isManualCode):
   ArgStrings = ArgStr()
   errGenericStr    = ''
   errMemoryStr     = ''
   successLogicStr  = ''
   wrapper_func     = ''

   # Handle return value
   retElement = functionElement.findall('return')[0]

   # Write the return value.
   if 'const' in retElement.get('attributes'):
      c_file.write('const')
   c_file.write('\n' + retElement.get('type') + ' ')
   if 'ptr' in retElement.get('attributes'):
      c_file.write('*')
   if 'doubleptr' in retElement.get('attributes'):
      c_file.write('*')

   if 'ptr' in retElement.get('attributes'):
      errGenericStr   = 'qsRetVal = NULL;\n'
      errMemoryStr    = 'qsRetVal = NULL;\n'
      successLogicStr = 'qsRetVal != NULL'
   elif retElement.get('type') == 'qapi_Status_t':
      errGenericStr = 'qsRetVal = QAPI_ERROR;\n'
      errMemoryStr  = 'qsRetVal = QAPI_ERR_NO_MEMORY;\n'
      successLogicStr = 'qsRetVal == QAPI_OK'
   elif retElement.get('type') == 'int8_t':
      if 'qapi_prof' in functionElement.get('name').lower():
         errGenericStr   = 'qsRetVal = QAPI_WLAN_ERROR;\n'
         errMemoryStr    = 'qsRetVal = QAPI_WLAN_ERR_NO_MEMORY;\n'
         successLogicStr = 'qsRetVal == QAPI_WLAN_OK'
      else:
         errGenericStr   = '#error Unhandled return type.\n'
         errMemoryStr    = '#error Unhandled return type.\n'
         successLogicStr = '#error Unhandled return type.\n'
         print '#warning# Unhandled return type, ', retElement.get('type'), functionElement.get('name')
   elif retElement.get('type') == 'int' or retElement.get('type') == 'int32_t':
      if 'qapi_ble' in functionElement.get('name').lower():
         errGenericStr   = 'qsRetVal = QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR;\n'
         errMemoryStr    = 'qsRetVal = QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR;\n'
         successLogicStr = 'qsRetVal >= 0'
      else:
         errGenericStr   = '#error Unhandled return type.\n'
         errMemoryStr    = '#error Unhandled return type.\n'
         successLogicStr = '#error Unhandled return type.\n'
         print '#warning# Unhandled return type, ', retElement.get('type'), functionElement.get('name')
   elif 'unsigned' in retElement.get('type') or 'uint' in retElement.get('type'):
      errGenericStr   = 'qsRetVal = 0;\n'
      errMemoryStr    = 'qsRetVal = 0;\n'
      successLogicStr = 'qsRetVal > 0'
   elif 'bool' in retElement.get('type').lower():
      errGenericStr   = 'qsRetVal = FALSE;\n'
      errMemoryStr    = 'qsRetVal = FALSE;\n'
      successLogicStr = 'qsRetVal == TRUE'
   elif 'void' in retElement.get('type') and retElement.get('attributes') == 'value':
      errGenericStr   = '// Return type is void, no need to set any variables.\n'
      errMemoryStr    = '// Return type is void, no need to set any variables.\n'
      successLogicStr = ''
   elif 'qapi_fw_upgrade' in functionElement.get('name').lower() and 'qapi_Fw_Upgrade_Status_Code_t' in retElement.get('type'):
         errGenericStr   = 'qsRetVal = QAPI_FW_UPGRADE_ERROR_E;\n'
         errMemoryStr    = 'qsRetVal = QAPI_FW_UPGRADE_ERR_INSUFFICIENT_MEMORY_E;\n'
         successLogicStr = 'qsRetVal == QAPI_FW_UPGRADE_OK_E'
   elif 'qapi_fw_upgrade' in functionElement.get('name').lower() and 'qapi_Fw_Upgrade_State_t' in retElement.get('type'):
         errGenericStr   = 'qsRetVal = QAPI_FW_UPGRADE_STATE_NOT_START_E;\n'
         errMemoryStr    = 'qsRetVal = QAPI_FW_UPGRADE_STATE_NOT_START_E;\n'
         successLogicStr = 'qsRetVal == TRUE'
   elif 'qapi_GPIO_Value_t' in retElement.get('type'):
         errGenericStr   = 'qsRetVal = QAPI_GPIO_INVALID_VALUE_E;\n'
         errMemoryStr    = 'qsRetVal = QAPI_GPIO_INVALID_VALUE_E;\n'
         successLogicStr = 'qsRetVal != QAPI_GPIO_INVALID_VALUE_E'
   else:
      errGenericStr   = '#error Unhandled return type.\n'
      errMemoryStr    = '#error Unhandled return type.\n'
      successLogicStr = '#error Unhandled return type.\n'
      print '#warning# Unhandled return type, ', retElement.get('type'), functionElement.get('name')

   # Prefix the function name if this is supposed to be manual code
   if isManualCode:
      c_file.write('Mnl_')
   else:
      c_file.write('_')

   # Write function name and arguments
   c_file.write(functionElement.get('name') + '(uint8_t TargetID, ')

   if len(functionElement.findall('argument')) > 0:
      for argElement in functionElement.findall('argument'):
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
            print '#warning# Unhandled argument type ' + argElement.get('name') + ' in ' + functionElement.get('name')
   c_file.seek(-2, 1)
   c_file.write(')\n{\n')

   # Generate an error if this is supposed to be manual code
   if isManualCode:
      c_file.write('\n#error Must complete this code manually.\n\n')

   # Create local variables.
   c_file.write('    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };\n')
   c_file.write('    PackedBuffer_t     qsOutputBuffer = { NULL, 0, 0, 0, NULL, NULL };\n')
   c_file.write('    BufferListEntry_t *qsBufferList = NULL;\n')
   c_file.write('    SerStatus_t        qsResult = ssSuccess;\n')
   c_file.write('    uint32_t           qsIndex = 0;\n')
   c_file.write('    uint16_t           qsSize = 0;\n')
   c_file.write('    Boolean_t          qsPointerValid = FALSE;\n\n')

   # Find and store any variable-length arguments whose size we need to keep track of with a temporary variable.
   # The original length argument may be changed by the qapi function.
   for argElement in functionElement.findall('argument'):
       if ('ptr' in argElement.get('attributes') and argElement.get('iotype') is not None and
           'out' in argElement.get('iotype') and argElement.get('lengthParam') is not None and
           argElement.get('lengthParam') <> '1' and argElement.get('lengthFirst') is None):
           for arg2 in functionElement.findall('argument'):
               if 'ptr' in arg2.get('attributes') and arg2.get('iotype') is not None and 'in' in arg2.get('iotype') and 'out' in arg2.get('iotype') and arg2.get('name') == argElement.get('lengthParam'):
                   c_file.write('    /* Create a temporary variable for the length of ' + argElement.get('name') + '. */\n')
                   c_file.write('    uint32_t qsTmp_' + arg2.get('name') + ' = 0;\n')
                   c_file.write('    if (' + arg2.get('name') + ' != NULL)\n')
                   c_file.write('        qsTmp_' + arg2.get('name') + ' = *' + arg2.get('name') + ';\n\n')
                   argElement.set('TempLength', 'qsTmp_' + arg2.get('name'))
                   break

   c_file.write('    UNUSED(qsIndex);\n')
   c_file.write('    UNUSED(qsPointerValid);\n\n')

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
         print '#warning# Unhandled return type ' + retElement.get('type') + ' in ' + functionElement.get('name')

   # Generate the callback registration code if necessary.
   GenerateCallbackRegister(fileName, headerElement, functionElement, c_file)

   # Calculate output buffer size.
   c_file.write('    /* Calculate size of packed function arguments. */\n')
   for argElement in functionElement.findall('argument'):
      ArgStrings.GenerateQAPIFunctionArguments(functionElement, argElement)


   if ArgStrings.numPtrs > 0:
      ArgStrings.structSizeStr = ArgStrings.structSizeStr + '(QS_POINTER_HEADER_SIZE * ' + str(ArgStrings.numPtrs) + ') + '

   if ArgStrings.decSize == 0 and ArgStrings.structSizeStr == '':
      c_file.write('    qsSize = 0')
   if ArgStrings.decSize <> 0 and ArgStrings.structSizeStr == '':
      c_file.write('    qsSize = ' + str(ArgStrings.decSize))
   if ArgStrings.decSize <> 0 and ArgStrings.structSizeStr <> '':
      c_file.write('    qsSize = ('  + str(ArgStrings.decSize) + ' + ' + ArgStrings.structSizeStr)
      c_file.seek(-3,1)
      c_file.write(')')
   if ArgStrings.decSize == 0 and ArgStrings.structSizeStr <> '':
      c_file.write('    qsSize = (' + ArgStrings.structSizeStr)
      c_file.seek(-3,1)
      c_file.write(')')
   c_file.write(';\n\n')

   if ArgStrings.varStructSizeStr <> '':
      c_file.write(ArgStrings.varStructSizeStr);
      c_file.write('\n');

   # Allocate packed buffer
   c_file.write('    if(AllocatePackedBuffer(TargetID, QS_PACKET_E, MODULE_' + component.upper() + ', ' + fileName.upper() + '_FILE_ID, ' + functionElement.get('name').upper() + '_FUNCTION_ID, &qsInputBuffer, qsSize))\n')
   c_file.write('    {\n')

   # Write each element to the buffer.
   if len(functionElement.findall('argument')) > 0:
      c_file.write('        /* Write arguments packed. */\n')
      # Write the packed parameters.
      c_file.write(MakePackedWriteParametersString(functionElement, functionElement.findall('argument'), True, ['in','in,out'], '        ', '&qsInputBuffer', '', 1))

   # Send command and get response.
   c_file.write('        if(qsResult == ssSuccess)\n')
   c_file.write('        {\n')
   c_file.write('            /* Send the command. */\n')
   
   if retElement.get('noResp') is not None and retElement.get('noResp') == 'true':
       c_file.write('            /* Host does not require a response for this API hence last parameter is set to FALSE. */\n')
       c_file.write('            if(_SendCommand(&qsInputBuffer, &qsOutputBuffer, FALSE) != ssSuccess)\n')

   else:
       c_file.write('            if(SendCommand(&qsInputBuffer, &qsOutputBuffer) == ssSuccess)\n')
       c_file.write('            {\n')
       c_file.write('                if(qsOutputBuffer.Start != NULL)\n')
       c_file.write('                {\n')

       # Handle reading the output values.
       if NeedsOutputRead(functionElement):
          # Unpack the return type from the response.
          if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void') or len(functionElement.findall('argument')) > 0:
             c_file.write('                    /* Unpack returned values. */\n')
          if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void'):
             if 'value' in retElement.get('attributes'):
                c_file.write('                    if(qsResult == ssSuccess)\n')
                c_file.write('                        qsResult = ' + GetPackedReadFunctionName(retElement.get('type')) + '(&qsOutputBuffer, &qsBufferList, ' + GetCastStr(retElement.get('type')) + '&qsRetVal);\n\n')
             if retElement.get('attributes') == 'ptr' or retElement.get('attributes') == 'ptr,const':
                c_file.write('                    if(qsResult == ssSuccess)\n')
                c_file.write('                        qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);\n')
                c_file.write('                    if((qsResult == ssSuccess) && (qsPointerValid))\n')
                c_file.write('                    {\n')
                c_file.write('                        qsRetVal = AllocateBufferListEntry(&qsBufferList, ' + GetSizeOfStr(retElement.get('type')) + ');\n')
                c_file.write('                        if(qsRetVal != NULL)\n')
                c_file.write('                            qsResult = ' + GetPackedReadFunctionName(retElement.get('type')) + '(&qsOutputBuffer, &qsBufferList, ' + GetCastStr(retElement.get('type')) + 'qsRetVal);\n')
                c_file.write('                        else\n')
                c_file.write('                            qsResult = ssAllocationError;\n')
                c_file.write('                    }\n')
                c_file.write('                    else\n')
                c_file.write('                        qsRetVal = NULL;\n\n')
             if retElement.get('attributes') == 'doubleptr' or retElement.get('attributes') == 'doubleptr,const':
                c_file.write('                    if(qsResult == ssSuccess)\n')
                c_file.write('                        qsResult = PackedRead_PointerHeader(&qsOutputBuffer, &qsBufferList, &qsPointerValid);\n')
                c_file.write('                    if((qsResult == ssSuccess) && (qsPointerValid))\n')
                c_file.write('                    {\n')
                c_file.write('                        qsRetVal = AllocateBufferListEntry(BufferList, ' + GetSizeOfStr(retElement.get('type')) + ');\n')
                c_file.write('                        if(qsRetVal != NULL)\n')
                c_file.write('                            qsResult = ' + GetPackedReadFunctionName(retElement.get('type')) + '(&qsOutputBuffer, &qsBufferList, ' + GetCastStr(retElement.get('type')) + 'qsRetVal);\n')
                c_file.write('                        else\n')
                c_file.write('                            qsResult = ssAllocationError;\n')
                c_file.write('                    }\n')
                c_file.write('                    else\n')
                c_file.write('                        qsRetVal = NULL;\n\n')

          # Unpack any output pointers from the response.
          c_file.write(MakePackedReadParametersString(functionElement, functionElement.findall('argument'), False, ['out','in,out'], '                    ', '&qsOutputBuffer', '&qsBufferList', '', False))

          # Generate code for updating the callback ID with the returned value.
          GenerateCallbackUpdate(headerElement, functionElement, c_file, successLogicStr)

          # Generate code for un-registering the callback.
          GenerateCallbackUnRegister(component, fileName, headerElement, functionElement, c_file, successLogicStr)

          # Function cleanup and return.
          if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void'):
             c_file.write('                    /* Set the return value to error if necessary. */\n')
             c_file.write('                    if(qsResult != ssSuccess)\n')
             c_file.write('                    {\n')
             c_file.write('                        ' + errGenericStr)
             c_file.write('                    }\n')

       c_file.write('                }\n')
       c_file.write('                else\n')
       c_file.write('                {\n')
       c_file.write('                    ' + errGenericStr)
       c_file.write('                }\n\n')
       c_file.write('                /* Free the output buffer. */\n')
       c_file.write('                FreePackedBuffer(&qsOutputBuffer);\n')
       c_file.write('            }\n')
       c_file.write('            else\n')

   # Common code irrespective of whether response is required.
   c_file.write('            {\n')
   c_file.write('                ' + errGenericStr)
   c_file.write('            }\n')
   c_file.write('        }\n')
   c_file.write('        else\n')
   c_file.write('        {\n')
   c_file.write('            ' + errGenericStr)
   c_file.write('        }\n\n')
   c_file.write('        /* Free the input buffer. */\n')
   c_file.write('        FreePackedBuffer(&qsInputBuffer);\n')
   c_file.write('    }\n')
   c_file.write('    else\n')
   c_file.write('    {\n')
   c_file.write('        ' + errMemoryStr)
   c_file.write('    }\n\n')
   c_file.write('    FreeBufferList(&qsBufferList);\n\n')
   if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void'):
      c_file.write('    return(qsRetVal);\n')
   c_file.write('}\n')

   # Write stubs for wrapper functions
   if not isManualCode:
      c_file.write(GenerateQAPIWrapperFunctionStubs(headerElement, functionElement))

# Generates function definitions for packing structures.
def GenerateHostCallbackHandlerFunctions(callbackElement, c_file):
   decSize = 0
   numPtrs = 0
   structSizeStr = ""
   varStructSizeStr = ""

   # Write the function name
   c_file.write('void Host_' + callbackElement.get('name') + '_Handler(uint32_t CallbackID, CallbackInfo_t *Info, uint16_t BufferLength, uint8_t *Buffer)\n')
   c_file.write('{\n')
   c_file.write('    SerStatus_t        qsResult = ssSuccess;\n')
   c_file.write('    BufferListEntry_t *qsBufferList = NULL;\n')
   c_file.write('    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };\n')
   c_file.write('    CallbackInfo_t     qsCallbackInfo = { 0, 0, 0, 0, 0, NULL, 0 };\n')
   if (ParamsNeedIndex(callbackElement.findall('argument'), ['out']) == True):
      c_file.write('    uint32_t           qsIndex = 0;\n')
   c_file.write('    Boolean_t          qsPointerValid = FALSE;\n')
   c_file.write('\n')
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
            c_file.write('    ' + argElement.get('type') + ' ' + argElement.get('name') + ';\n')
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
   c_file.write('    }\n')
   c_file.write('}\n')

