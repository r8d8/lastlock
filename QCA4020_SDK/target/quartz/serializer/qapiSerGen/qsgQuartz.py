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

class ArgStr:
   def __init__(self):
      self.numPtrs          = 0
      self.structSizeStr    = ''
      self.varStructSizeStr = ''

      
   # Calculate required buffer size
   def CalcPackedSize(self, functionElement, argElement):
      if not argElement.get('type') in qsgCommon.callbackList and (argElement.get('attributes') == 'ptr' or argElement.get('attributes') == 'ptr,const'):
          if (argElement.get('iotype') is not None and 'out' in argElement.get('iotype')):
              if argElement.get('lengthParam') == '1':
                  self.numPtrs = self.numPtrs + 1
                  if IsPrimitive(argElement.get('type')):
                      self.structSizeStr = self.structSizeStr + '(' + argElement.get('name') + ' == NULL ? 0 : ' + str(GetPrimitiveSize(argElement.get('type'))) + ') + '
                  else:
                      self.structSizeStr = self.structSizeStr + '(' + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + argElement.get('name') + ')) + '
      
              elif isParamLengthInt(argElement.get('lengthParam')) == True:
                  self.numPtrs = self.numPtrs + 1
                  self.structSizeStr = self.structSizeStr + argElement.get('lengthParam') + ' + '
      
              else:
        # Loop through variable length data.
                  for otherArg in functionElement.findall('argument'):
                      if otherArg.get('name') == argElement.get('lengthParam'):
                          if 'yes' == argElement.get('lengthFirst'):
                              self.CalcPackedSize(functionElement, otherArg)
      
                          self.numPtrs = self.numPtrs + 1
                          if 'value' in otherArg.get('attributes'):
                              if IsPrimitive(argElement.get('type')):
                                  self.varStructSizeStr = self.varStructSizeStr + '      if(' + argElement.get('name') + ' != NULL)\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '         qsOutputLength = qsOutputLength + ((' + argElement.get('lengthParam') + ')*(' + str(GetPrimitiveSize(argElement.get('type'))) + '));\n'
                              else:
                                  self.varStructSizeStr = self.varStructSizeStr + '      if(' + argElement.get('name') + ' != NULL)\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '      {\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '         for (qsIndex = 0; qsIndex < ' + argElement.get('lengthParam') + '; qsIndex++)\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '         {\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '            qsOutputLength = qsOutputLength + ' + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + '&' + argElement.get('name') + '[qsIndex]);\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '         }\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '      }\n'
      
      
      
                          else:
                              if IsPrimitive(argElement.get('type')):
                                  self.varStructSizeStr = self.varStructSizeStr + '      if((' + argElement.get('lengthParam') + ' != NULL) && (' + argElement.get('name') + ' != NULL))\n'
                                  if argElement.get('TempLength') is not None:
                                      self.varStructSizeStr = self.varStructSizeStr + '      {\n'
                                      self.varStructSizeStr = self.varStructSizeStr + '         if(' + argElement.get('TempLength') + ' > *' + argElement.get('lengthParam') + ')\n'
                                      self.varStructSizeStr = self.varStructSizeStr + '            ' + argElement.get('TempLength') + ' = *' + argElement.get('lengthParam') + ';\n'
                                      self.varStructSizeStr = self.varStructSizeStr + '         qsOutputLength = qsOutputLength + ((' + argElement.get('TempLength') + ')*(' + str(GetPrimitiveSize(argElement.get('type'))) + '));\n'
                                      self.varStructSizeStr = self.varStructSizeStr + '      }\n'
                                  else:
                                      self.varStructSizeStr = self.varStructSizeStr + '         qsOutputLength = qsOutputLength + ((*' + argElement.get('lengthParam') + ')*(' + str(GetPrimitiveSize(argElement.get('type'))) + '));\n'
                              else:
                                  self.varStructSizeStr = self.varStructSizeStr + '      if((' + argElement.get('lengthParam') + ' != NULL) && (' + argElement.get('name') + ' != NULL))\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '      {\n'
                                  if argElement.get('TempLength') is not None:
                                      self.varStructSizeStr = self.varStructSizeStr + '         if(' + argElement.get('TempLength') + ' > *' + argElement.get('lengthParam') + ')\n'
                                      self.varStructSizeStr = self.varStructSizeStr + '            ' + argElement.get('TempLength') + ' = *' + argElement.get('lengthParam') + ';\n'
                                      self.varStructSizeStr = self.varStructSizeStr + '         for (qsIndex = 0; qsIndex < ' + argElement.get('TempLength') + '; qsIndex++)\n'
                                  else:
                                      self.varStructSizeStr = self.varStructSizeStr + '         for (qsIndex = 0; qsIndex < *' + argElement.get('lengthParam') + '; qsIndex++)\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '         {\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '            qsOutputLength = qsOutputLength + ' + GetCalcPackedSizeFunctionName(argElement.get('type')) + '(' + GetCastStr(argElement.get('type')) + '&' + argElement.get('name') + '[qsIndex]);\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '         }\n'
                                  self.varStructSizeStr = self.varStructSizeStr + '      }\n'
         
      
      


# Create the Quartz QAPI handler code.
def CreateQzQAPICode(xmlFile, component, root):
    fileName = xmlFile.replace('.xml', '')
    manual_c_file = None
    # Find out if we need to create a manually written code file for functions in this module
    manualFuncFileNeeded = False
    for functionElement in root.findall('function'):
        if functionElement.get('name') in qsgCommon.manualFuncList:
            manualFuncFileNeeded = True
            if qsgCommon.generateManual:
                manual_c_file = CreateQzManualQAPIHandlerFiles(xmlFile, component, root)

    # Create the auto-gen code
    auto_c_file = CreateQzAutoQAPIHandlerFiles(xmlFile, component, root, manualFuncFileNeeded)

    # Generate the function unpacking functions
    for functionElement in root.findall('function'):
        if functionElement.get('name') in qsgCommon.manualFuncList:
            CreateQzManualQAPIHandlerStubs(functionElement, auto_c_file)
            if qsgCommon.generateManual:
                CreateQzQAPIHandlerFunctions(component, fileName, functionElement, manual_c_file, True)
        else:
            CreateQzQAPIHandlerFunctions(component, fileName, functionElement, auto_c_file, False)

    auto_c_file.close()
    if manual_c_file is not None:
        manual_c_file.close()

# Creates the C file for automatically generated code. The header for this file
# is created in the Filelist module.
def CreateQzAutoQAPIHandlerFiles(xmlFile, component, root, manualFuncFileNeeded):
    c_file = open(os.path.join(qsgCommon.qapiDir, 'qz', xmlFile.replace('.xml', '') + '_qz.c'), 'w+')

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
    c_file.write('#include "idlist.h"\n')
    c_file.write('#include "qsCommon.h"\n')
    c_file.write('#include "qsQuartz.h"\n')
    c_file.write('#include "qsPack.h"\n')
    c_file.write('#include "qapi_' + component + '.h"\n')
    if manualFuncFileNeeded:
        c_file.write('#include "' + xmlFile.replace('.xml', '') + '_qz_mnl.h"\n')
    c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n')
    if len(root.findall('callback')) > 0:
        c_file.write('#include "' + xmlFile.replace('.xml', '') + '_qz_cb.h"\n')

    return c_file

# Creates the header and C files for manual Quartz function handlers
def CreateQzManualQAPIHandlerFiles(xmlFile, component, root):
    manual_h_file = open(os.path.join(qsgCommon.manualDir, 'qz', 'include', xmlFile.replace('.xml', '') + '_qz_mnl.h'), 'w+')
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

    manual_c_file = open(os.path.join(qsgCommon.manualDir, 'qz', xmlFile.replace('.xml', '') + '_qz_mnl.c'), 'w+')
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
    manual_h_file.write('#include "qsCommon.h"\n')
    manual_h_file.write('#include "qapi_' + component + '.h"\n')
    manual_c_file.write('#include "qapi_' + component + '.h"\n')
    manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n')
    manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_qz_mnl.h"\n')
    if len(root.findall('callback')) > 0:
        manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_qz_cb.h"\n')

    for functionElement in root.findall('function'):
        if functionElement.get('name') in qsgCommon.manualFuncList:
            manual_h_file.write('\nSerStatus_t Mnl_Handle_' + functionElement.get('name') + '(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);\n')

    manual_h_file.close()

    return manual_c_file

# Creates calls in auto generated code to manual functions.
def CreateQzManualQAPIHandlerStubs(functionElement, c_file):
    c_file.write('\nSerStatus_t Handle_' + functionElement.get('name') + '(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)\n')
    c_file.write('{\n')
    c_file.write('    return(Mnl_Handle_' + functionElement.get('name') + '(qsBuffer, qsLength, qsOutputBuffer, uId));\n')
    c_file.write('}\n')

# Creates auto generated code for QAPI handler functions.
def CreateQzQAPIHandlerFunctions(component, fileName, functionElement, c_file, isManualCode):
    ArgStrings = ArgStr()
    decSize          = 0

    # Declare the return value.
    retElement = functionElement.findall('return')[0]

    # Write function handler name and local variables.
    if isManualCode:
        c_file.write('\nSerStatus_t Mnl_Handle_' + functionElement.get('name') + '(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)\n')
    else:
        c_file.write('\nSerStatus_t Handle_' + functionElement.get('name') + '(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)\n')
    c_file.write('{\n')
    if isManualCode:
        c_file.write('\n#error Must complete this code manually.\n\n')
    c_file.write('    SerStatus_t        qsResult = ssSuccess;\n')
    c_file.write('    BufferListEntry_t *qsBufferList = NULL;\n')
    c_file.write('    PackedBuffer_t     qsInputBuffer = { NULL, 0, 0, 0, NULL, NULL };\n')
    if not (retElement.get('noResp') is not None and retElement.get('noResp') == 'true'):
        c_file.write('    uint32_t           qsOutputLength = 0;\n')
    c_file.write('    uint32_t           qsIndex = 0;\n')
    c_file.write('    Boolean_t          qsPointerValid = FALSE;\n')
    c_file.write('\n')

    # Find any variable-length arguments whose size we need to keep track of with a temporary variable.
    # The original length argument may be changed by the qapi function, losing the original length of variable-length arguments  otherwise.
    for argElement in functionElement.findall('argument'):
        if ('ptr' in argElement.get('attributes') and argElement.get('iotype') is not None and 
            'out' in argElement.get('iotype') and argElement.get('lengthParam') is not None and 
            argElement.get('lengthParam') <> '1' and argElement.get('lengthFirst') is None):
            for arg2 in functionElement.findall('argument'):
                if 'ptr' in arg2.get('attributes') and arg2.get('iotype') is not None and 'in' in arg2.get('iotype') and 'out' in arg2.get('iotype') and arg2.get('name') == argElement.get('lengthParam'):
                    c_file.write('    /* Create a temporary variable for the length of ' + argElement.get('name') + '. */\n')
                    c_file.write('    uint32_t qsTmp_' + arg2.get('name') + ' = 0;\n')
                    break

    c_file.write('    UNUSED(qsPointerValid);\n')
    c_file.write('    UNUSED(qsIndex);\n\n')

    if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void'):
        if not (retElement.get('noResp') is not None and retElement.get('noResp') == 'true'):
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

    # Declare function argument variables.
    if len(functionElement.findall('argument')) > 0:
        c_file.write('    /* Function parameters. */\n')
        for argElement in functionElement.findall('argument'):
            if argElement.get('type') not in qsgCommon.callbackList:
                if 'value' in argElement.get('attributes'):
                    c_file.write('    ' + argElement.get('type') + ' ' + argElement.get('name') + ';\n')
                if (argElement.get('attributes') == 'ptr' or argElement.get('attributes') == 'ptr,const'):
                    c_file.write('    ' + argElement.get('type') + ' *' + argElement.get('name') + ' = NULL;\n')
        c_file.write('\n')
    c_file.write('    InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);\n')
    c_file.write('\n')
    c_file.write('    /* Read function parameters. */\n')

    # Write argument variables from the packed buffer.
    c_file.write(MakePackedReadParametersString(functionElement, functionElement.findall('argument'), True, ['in','in,out'], '    ', '&qsInputBuffer', '&qsBufferList', '', True, 1))

    # Find any variable-length arguments whose size we need to keep track of with a temporary variable and update its size.
    for argElement in functionElement.findall('argument'):
        if ('ptr' in argElement.get('attributes') and argElement.get('iotype') is not None and 
            'out' in argElement.get('iotype') and argElement.get('lengthParam') is not None and 
            argElement.get('lengthParam') <> '1' and argElement.get('lengthFirst') is None):
            for arg2 in functionElement.findall('argument'):
                if 'ptr' in arg2.get('attributes') and arg2.get('iotype') is not None and 'in' in arg2.get('iotype') and 'out' in arg2.get('iotype') and arg2.get('name') == argElement.get('lengthParam'):
                    c_file.write('    if(' + arg2.get('name') + ' != NULL)\n')
                    c_file.write('      qsTmp_' + arg2.get('name') + ' = *' + arg2.get('name') + ';\n\n')
                    argElement.set('TempLength', 'qsTmp_' + arg2.get('name'))
                    break

    # Write the function call.
    c_file.write('    /* Call the QAPI function and handle the response. */\n')
    c_file.write('    if(qsResult == ssSuccess)\n')
    c_file.write('    {\n')
    if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void'):
        if retElement.get('noResp') is not None and retElement.get('noResp') == 'true':
            c_file.write('        /* Host does not require a response for this API. */\n')
            c_file.write('        (void)' + functionElement.get('name') + '(')
        else:
            c_file.write('        qsRetVal = ' + functionElement.get('name') + '(')
    else:
        c_file.write('        ' + functionElement.get('name') + '(')

    # Write the function parameters.
    for argElement in functionElement.findall('argument'):
        if argElement.get('type') in qsgCommon.callbackList:
            # Write Quartz function handler names.
            c_file.write('QZ_' + argElement.get('type') + '_Handler, ')
        else:
            c_file.write(argElement.get('name') + ', ')
    if len(functionElement.findall('argument')) > 0:
        c_file.seek(-2, 1)

    if retElement.get('noResp') is not None and retElement.get('noResp') == 'true':
        c_file.write(');\n')
    else:
        c_file.write(');\n\n')

    if not (retElement.get('noResp') is not None and retElement.get('noResp') == 'true'):
        # Calculate return value packed size.
        if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void'):
            if 'value' in retElement.get('attributes'):
                decSize = decSize + GetPrimitiveSize(retElement.get('type'))
            else:
                ArgStrings.numPtrs = ArgStrings.numPtrs + 1
                if IsPrimitive(retElement.get('type')):
                    decSize = decSize + GetPrimitiveSize(retElement.get('type'))
                else:
                    ArgStrings.structSizeStr = ArgStrings.structSizeStr + GetCalcPackedSizeFunctionName(retElement.get('type')) + '(' + GetCastStr(retElement.get('type')) + 'qsRetVal) + '

        # Calculate packed sizes of any output arguments. Only pointers need to be examined.
        for argElement in functionElement.findall('argument'):
           ArgStrings.CalcPackedSize(functionElement, argElement)

        # Add the number of pointer headers to the output buffer size.
        if ArgStrings.numPtrs > 0:
            ArgStrings.structSizeStr = ArgStrings.structSizeStr + '(QS_POINTER_HEADER_SIZE * ' + str(ArgStrings.numPtrs) + ') + '

        # Write the output length variable.
        if decSize == 0 and ArgStrings.structSizeStr == '':
            c_file.write('    qsOutputLength = 0')
        if decSize <> 0 and ArgStrings.structSizeStr == '':
            c_file.write('        qsOutputLength = ' + str(decSize))
        if decSize <> 0 and ArgStrings.structSizeStr <> '':
            c_file.write('        qsOutputLength = (' + str(decSize) + ' + ' + ArgStrings.structSizeStr)
            c_file.seek(-3, 1)
            c_file.write(')')
        if decSize == 0 and ArgStrings.structSizeStr <> '':
            c_file.write('        qsOutputLength = (' + ArgStrings.structSizeStr)
            c_file.seek(-3, 1)
            c_file.write(')')
        c_file.write(';\n\n')

        if ArgStrings.varStructSizeStr <> '':
            c_file.write(ArgStrings.varStructSizeStr);
            c_file.write('\n');

        # Allocate the output buffer and packed write all the outputs.
        c_file.write('        if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_' + component.upper() + ', ' + fileName.upper() + '_FILE_ID, ' + functionElement.get('name').upper() + '_FUNCTION_ID, qsOutputBuffer, qsOutputLength))\n')
        c_file.write('        {\n')
        c_file.write('            /* Write return value and/or output parameters packed. */\n')
        if not (retElement.get('attributes') == 'value' and retElement.get('type') == 'void'):
            if 'value' in retElement.get('attributes'):
                # Handle value return types.
                c_file.write('             if(qsResult == ssSuccess)\n')
                c_file.write('                qsResult = ' + GetPackedWriteFunctionName(retElement.get('type')) + '(qsOutputBuffer, ' + GetCastStr(retElement.get('type')) + '&qsRetVal);\n')
                c_file.write('\n')
            else:
                # Handle pointer return types.
                c_file.write('            if(qsResult == ssSuccess)\n')
                c_file.write('                qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)qsRetVal);\n')
                c_file.write('            if(qsResult == ssSuccess)\n')
                c_file.write('                qsResult = ' + GetPackedWriteFunctionName(retElement.get('type')) + '(qsOutputBuffer, ' + GetCastStr(retElement.get('type')) + 'qsRetVal);\n')
                c_file.write('\n')

        # Write the packed parameters.
        c_file.write(MakePackedWriteParametersString(functionElement, functionElement.findall('argument'), False, ['in,out','out'], '         ', 'qsOutputBuffer', ''))

        c_file.write('        }\n')
        c_file.write('        else\n')
        c_file.write('        {\n')
        c_file.write('            qsResult = ssAllocationError;\n')
        c_file.write('        }\n')
    # End of output parameters and creation of return packet

    c_file.write('    }\n\n')
    c_file.write('    FreeBufferList(&qsBufferList);\n\n')
    c_file.write('    return(qsResult);\n')
    c_file.write('}\n')

