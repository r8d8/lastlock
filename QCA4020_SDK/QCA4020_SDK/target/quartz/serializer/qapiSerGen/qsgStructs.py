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

def CreateStructCode(xmlFile, component, root):
   manual_c_file = None
   # Find out if we need to create a manually written code file for functions in this module
   manualStructFileNeeded = False
   for structElement in root.findall('structure'):
      if structElement.get('name') in qsgCommon.manualStructList:
         manualStructFileNeeded = True
         if qsgCommon.generateManual:
            try:
                manual_c_file = CreateStructManualCommonFiles(xmlFile, component, root)
            except IOError as e:
                print '#warning# ' + structElement.get('name') + ' already defined'

   auto_c_file = CreateStructAutoCommonFiles(xmlFile, component, root, manualStructFileNeeded)

   # Generate the structure size calculation functions.
   for structElement in root.findall('structure'):
      if structElement.get('name') in qsgCommon.manualStructList:
         if qsgCommon.generateManual and manual_c_file:
            GeneratePackStructureSizes(structElement, manual_c_file, True)
         GeneratePackStructureSizeStub(structElement, auto_c_file)
      else:
         GeneratePackStructureSizes(structElement, auto_c_file, False)

   # Generate the structure packing functions
   for structElement in root.findall('structure'):
      if structElement.get('name') in qsgCommon.manualStructList:
         if qsgCommon.generateManual and manual_c_file:
            GeneratePackStructures(structElement, manual_c_file, True)
         GeneratePackStructureStub(structElement, auto_c_file)
      else:
         GeneratePackStructures(structElement, auto_c_file, False)

   # Generate the structure unpacking functions
   for structElement in root.findall('structure'):
      if structElement.get('name') in qsgCommon.manualStructList:
         if qsgCommon.generateManual and manual_c_file:
            GenerateUnpackStructures(structElement, manual_c_file, True)
         GenerateUnpackStructureStub(structElement, auto_c_file)
      else:
         GenerateUnpackStructures(structElement, auto_c_file, False)

   if manual_c_file is not None:
      manual_c_file.close()
   auto_c_file.close()

def CreateStructManualCommonFiles(xmlFile, component, root):
   # Open a new Quartz H file for creation
   manual_h_file = open(os.path.join(qsgCommon.manualDir, 'common', 'include', xmlFile.replace('.xml', '') + '_common_mnl.h'), 'w+')
   CreateStructHeaders(xmlFile, manual_h_file, component, root, True)
   manual_h_file.close()

   # Open a new Quartz C file for creation
   manual_c_file = open(os.path.join(qsgCommon.manualDir, 'common', xmlFile.replace('.xml', '') + '_common_mnl.c'), 'w+')
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
   manual_c_file.write('#include "qapi_' + component + '.h"\n')
   manual_c_file.write('#include "qsCommon.h"\n')
   manual_c_file.write('#include "qsPack.h"\n')
   manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n')
   manual_c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common_mnl.h"\n')
   for includeElement in root.findall('include'):
      if 'qapi_' in includeElement.get('name') and not 'qapi_status' in includeElement.get('name') and not 'qapi_types' in includeElement.get('name'):
         manual_c_file.write('#include "' + includeElement.get('name').replace('.h', '').replace('.','').replace('qapi/','').replace('/','') + '_common.h"\n')

   return manual_c_file

def CreateStructAutoCommonFiles(xmlFile, component, root, manualStructFileNeeded):
   # Open a new Quartz H file for creation
   c_file = open(os.path.join(qsgCommon.qapiDir, 'common', 'include', xmlFile.replace('.xml', '') + '_common.h'), 'w+')
   CreateStructHeaders(xmlFile, c_file, component, root, False)
   c_file.close()

   # Open a new Quartz C file for creation
   c_file = open(os.path.join(qsgCommon.qapiDir, 'common', xmlFile.replace('.xml', '') + '_common.c'), 'w+')
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
   c_file.write('#include "qapi_' + component + '.h"\n')
   c_file.write('#include "qsCommon.h"\n')
   c_file.write('#include "qsPack.h"\n')
   c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common.h"\n')
   if manualStructFileNeeded:
      c_file.write('#include "' + xmlFile.replace('.xml', '') + '_common_mnl.h"\n')
   for includeElement in root.findall('include'):
      if 'qapi_' in includeElement.get('name') and not 'qapi_status' in includeElement.get('name') and not 'qapi_types' in includeElement.get('name'):
         c_file.write('#include "' + includeElement.get('name').replace('.h', '').replace('.','').replace('qapi/','').replace('/','') + '_common.h"\n')

   return c_file

def CreateStructHeaders(xmlFile, c_file, component, root, isManualCode):
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
   c_file.write('#ifndef __')
   if isManualCode:
      c_file.write('MNL_')
   c_file.write((xmlFile.replace('.xml', '') + '_common_h__').upper() + '\n')
   c_file.write('#define __')
   if isManualCode:
      c_file.write('MNL_')
   c_file.write((xmlFile.replace('.xml', '') + '_common_h__').upper() + '\n')
   c_file.write('#include "qsCommon.h"\n')
   c_file.write('#include "qapi_' + component + '.h"\n')
   # Override includes for btb and base BLE types.
   if 'qapi_ble_btbtypes' in xmlFile:
      c_file.write('#include "qapi_ble_bttypes_common.h"\n')
   elif 'qapi_ble_basetypes' in xmlFile:
      c_file.write('#include "qapi_ble_bttypes_common.h"\n')
   else:
      c_file.write('#include "' + xmlFile.replace('.xml', '.h') + '"\n')
   for includeElement in root.findall('include'):
      if 'qapi_' in includeElement.get('name') and not 'qapi_status' in includeElement.get('name') and not 'qapi_types' in includeElement.get('name'):
         c_file.write('#include "' + includeElement.get('name').replace('.h', '').replace('.','').replace('qapi/','').replace('/','') + '_common.h"\n')

   # Generate the structure size definitions
   if len(root.findall('structure')) > 0:
      if not isManualCode:
         c_file.write('\n/* Packed structure minimum size macros. */\n')
         for structElement in root.findall('structure'):
            GenerateMinPackStructureMacros(structElement, c_file)

      c_file.write('\n/* Packed structure size definitions. */\n')
      for structElement in root.findall('structure'):
         if isManualCode and structElement.get('name') in qsgCommon.manualStructList:
            c_file.write('uint32_t Mnl_CalcPackedSize_' + structElement.get('name') + '(' + structElement.get('name') + ' *Structure);\n')
         if not isManualCode:
            c_file.write('uint32_t CalcPackedSize_' + structElement.get('name') + '(' + structElement.get('name') + ' *Structure);\n')

      # Generate the structure packing functions
      c_file.write('\n/* Pack structure function definitions. */\n')
      for structElement in root.findall('structure'):
         if isManualCode and structElement.get('name') in qsgCommon.manualStructList:
            c_file.write('SerStatus_t Mnl_PackedWrite_' + structElement.get('name') + '(PackedBuffer_t *Buffer, ' + structElement.get('name') + ' *Structure);\n')
         if not isManualCode:
            c_file.write('SerStatus_t PackedWrite_' + structElement.get('name') + '(PackedBuffer_t *Buffer, ' + structElement.get('name') + ' *Structure);\n')

      # Generate the structure unpacking functions
      c_file.write('\n/* Unpack structure function definitions. */\n')
      for structElement in root.findall('structure'):
         if isManualCode and structElement.get('name') in qsgCommon.manualStructList:
            c_file.write('SerStatus_t Mnl_PackedRead_' + structElement.get('name') + '(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, ' + structElement.get('name') + ' *Structure);\n')
         if not isManualCode:
            c_file.write('SerStatus_t PackedRead_' + structElement.get('name') + '(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, ' + structElement.get('name') + ' *Structure);\n')

   if isManualCode:
      c_file.write('\n#endif // __MNL_' + (xmlFile.replace('.xml', '') + '_common_h__').upper() + '\n')
   else:
      c_file.write('\n#endif // __' + (xmlFile.replace('.xml', '') + '_common_h__').upper() + '\n')

# Generates a stub in auto-generated code to call a manually written version.
def GeneratePackStructureStub(structElement, c_file):
   # Generate function name.
   c_file.write('\nSerStatus_t PackedWrite_' + structElement.get('name') + '(PackedBuffer_t *Buffer, ' + structElement.get('name') + ' *Structure)\n')
   c_file.write('{\n')
   c_file.write('    return(Mnl_PackedWrite_' + structElement.get('name') + '(Buffer, Structure));\n')
   c_file.write('}\n')

# Generates functions for packed writing of structures.
def GeneratePackStructures(structElement, c_file, isManualCode):
   # Generate function name.
   if isManualCode:
      c_file.write('\nSerStatus_t Mnl_PackedWrite_' + structElement.get('name') + '(PackedBuffer_t *Buffer, ' + structElement.get('name') + ' *Structure)\n')
   else:
      c_file.write('\nSerStatus_t PackedWrite_' + structElement.get('name') + '(PackedBuffer_t *Buffer, ' + structElement.get('name') + ' *Structure)\n')
   c_file.write('{\n')
   if isManualCode:
      c_file.write('\n#error Must complete this code manually.\n\n')
   c_file.write('    SerStatus_t qsResult = ssSuccess;\n')

   # Check if the index variable is needed.
   if (ParamsNeedIndex(structElement.findall('member'), ['in']) == True):
      c_file.write('    uint32_t    qsIndex;\n')

   c_file.write('\n')
   c_file.write('    if(Buffer->Remaining >= CalcPackedSize_' + structElement.get('name') + '(Structure))\n')
   c_file.write('    {\n')
   c_file.write('        if(Structure != NULL)\n')
   c_file.write('        {\n')

   # Packed write all the structure members.
   c_file.write(MakePackedWriteParametersString(structElement, structElement.findall('member'), True, ['in'], '         ', 'Buffer', 'Structure->'))

   # End of function
   c_file.write('        }\n')
   c_file.write('    }\n')
   c_file.write('    else\n')
   c_file.write('    {\n')
   c_file.write('        qsResult = ssInvalidLength;\n')
   c_file.write('    }\n')
   c_file.write('\n')
   c_file.write('    return(qsResult);\n')
   c_file.write('}\n')

# Generates a stub in auto-generated code to call a manually written version.
def GenerateUnpackStructureStub(structElement, c_file):
   # Generate function name.
   c_file.write('\nSerStatus_t PackedRead_' + structElement.get('name') + '(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, ' + structElement.get('name') + ' *Structure)\n')
   c_file.write('{\n')
   c_file.write('    return(Mnl_PackedRead_' + structElement.get('name') + '(Buffer, BufferList, Structure));\n')
   c_file.write('}\n')

# Generates functions for unpacking functions.
def GenerateUnpackStructures(structElement, c_file, isManualCode):
   # Generate function name.
   if isManualCode:
      c_file.write('\nSerStatus_t Mnl_PackedRead_' + structElement.get('name') + '(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, ' + structElement.get('name') + ' *Structure)\n')
   else:
      c_file.write('\nSerStatus_t PackedRead_' + structElement.get('name') + '(PackedBuffer_t *Buffer, BufferListEntry_t **BufferList, ' + structElement.get('name') + ' *Structure)\n')
   c_file.write('{\n')
   if isManualCode:
      c_file.write('\n#error Must complete this code manually.\n\n')
   c_file.write('    SerStatus_t qsResult = ssSuccess;\n')
   c_file.write('    Boolean_t   qsPointerValid = FALSE;\n')

   # Check if the index variable is needed.
   if (ParamsNeedIndex(structElement.findall('member'), ['in']) == True):
      c_file.write('    uint32_t    qsIndex = 0;\n')

   c_file.write('\n    UNUSED(qsPointerValid);\n')

   c_file.write('\n    if(Buffer->Remaining >= ' + structElement.get('name').upper() + '_MIN_PACKED_SIZE)\n')
   c_file.write('    {\n')

   # Packed write all the structure members.
   c_file.write(MakePackedReadParametersString(structElement, structElement.findall('member'), True, ['in'], '        ', 'Buffer', 'BufferList', 'Structure->', True))

   # End of function
   c_file.write('    }\n')
   c_file.write('    else\n')
   c_file.write('    {\n')
   c_file.write('        qsResult = ssInvalidLength;\n')
   c_file.write('    }\n\n')
   c_file.write('    return(qsResult);\n')
   c_file.write('}\n')

# Generates macros for minimum packed structure sizes.
def GenerateMinPackStructureMacros(structElement, c_file):
   decSize = 0
   numPointerHeaders = 0
   fixedSizeStr = ''
   varSizeStr = ''
   unionSizeStr = ''

   # Get the size of all fixed values, including enums, callbacks, primitives, and pointers to primitives of length '1'
   # Output stored in 'decSize'
   for memberElement in structElement.findall('member'):
      if 'value' in memberElement.get('attributes'):
         # Handle value members.
         if memberElement.get('type') in qsgCommon.enumList:
            decSize = decSize + GetPrimitiveSize('int')
         elif memberElement.get('type') in qsgCommon.callbackList:
            decSize = decSize + 4
         elif IsPrimitive(memberElement.get('type')):
            decSize = decSize + GetPrimitiveSize(memberElement.get('type'))

   # Get the number of pointer headers required.
   for memberElement in structElement.findall('member'):
      if 'ptr' in memberElement.get('attributes'):
         if 'bracketArray' in memberElement.get('attributes'):
            if (not unicode(memberElement.get('lengthParam')).isnumeric() or (unicode(memberElement.get('lengthParam')).isnumeric() and int(memberElement.get('lengthParam')) > 1)):
               if IsPrimitive(memberElement.get('type')):
                  varSizeStr = varSizeStr + '(' + str(GetPrimitiveSize((memberElement.get('type')))) + '*' + memberElement.get('lengthParam') + ') + '
               else:
                  varSizeStr = varSizeStr + '(sizeof(' + memberElement.get('type') + ')*' + memberElement.get('lengthParam') + ') + '
         else:
            numPointerHeaders = numPointerHeaders + 1
      elif memberElement.get('attributes') == 'union':
         if len(memberElement.findall('member')) > 0:
            if not 'value' in memberElement.findall('member')[0].get('attributes'):
               numPointerHeaders = numPointerHeaders + 1

   # Write the macro.
   c_file.write('#define ' + structElement.get('name').upper() + '_MIN_PACKED_SIZE ')
   # Pad spaces
   for index in range(len(structElement.get('name')), 79):
      c_file.write(' ')
   if decSize == 0 and numPointerHeaders == 0:
      c_file.write('(0)\n')
   if decSize == 0 and numPointerHeaders <> 0:
      c_file.write('((QS_POINTER_HEADER_SIZE) * (' + str(numPointerHeaders) + '))\n')
   if decSize <> 0 and numPointerHeaders == 0:
      c_file.write('(' + str(decSize) + ')\n')
   if decSize <> 0 and numPointerHeaders <> 0:
      c_file.write('((' + str(decSize) + ') + (QS_POINTER_HEADER_SIZE) * (' + str(numPointerHeaders) + '))\n')

# Creates a stub in auto-generated code that calls the manually written version
def GeneratePackStructureSizeStub(structElement, c_file):
   # Write the function.
   c_file.write('\n')
   c_file.write('uint32_t CalcPackedSize_' + structElement.get('name') + '(' + structElement.get('name') + ' *Structure)\n')
   c_file.write('{\n')
   c_file.write('    return(Mnl_CalcPackedSize_' + structElement.get('name') + '(Structure));\n')
   c_file.write('}\n')

# Generates functions for packed structure sizes.
def GeneratePackStructureSizes(structElement, c_file, isManualCode):
   fixedSizeStr = ''
   varSizeStr = ''
   unionSizeStr = ''
   foundMember = False

   # Add the size of all pointers to primitives of variable length.
   # Output stored in 'fixedSizeStr'
   for memberElement in structElement.findall('member'):
      foundMember = False
      if (memberElement.get('attributes') == 'ptr' or memberElement.get('attributes') == 'ptr,const'):
         if IsPrimitive(memberElement.get('type')):
            # Handle single pointers to primitive types
            if GetPrimitiveSize(memberElement.get('type')) == 1:
               # Handle strings
               if memberElement.get('lengthParam') == '__strlen__':
                  fixedSizeStr = fixedSizeStr + '\n        if(Structure->' + memberElement.get('name') + ' != NULL)\n'
                  fixedSizeStr = fixedSizeStr + '        {\n'
                  fixedSizeStr = fixedSizeStr + '            qsResult += (strlen((const char *)Structure->' + memberElement.get('name') + ')+1);\n'
                  fixedSizeStr = fixedSizeStr + '        }\n'
               else:
                  # Find the length parameter and check if it is a pointer or value
                  for otherMember in structElement.findall('member'):
                     if otherMember.get('name') == memberElement.get('lengthParam'):
                        if 'value' in otherMember.get('attributes'):
                           fixedSizeStr = fixedSizeStr + '\n        if(Structure->' + memberElement.get('name') + ' != NULL)\n'
                           fixedSizeStr = fixedSizeStr + '        {\n'
                           fixedSizeStr = fixedSizeStr + '            qsResult += (Structure->' + memberElement.get('lengthParam') + ');\n'
                           fixedSizeStr = fixedSizeStr + '        }\n'
                        else:
                           fixedSizeStr = fixedSizeStr + '\n        if(Structure->' + memberElement.get('name') + ' != NULL)\n'
                           fixedSizeStr = fixedSizeStr + '        {\n'
                           fixedSizeStr = fixedSizeStr + '            qsResult += *(Structure->' + memberElement.get('lengthParam') + ');\n'
                           fixedSizeStr = fixedSizeStr + '        }\n'
                        foundMember = True
                        break
                  if not foundMember and memberElement.get('type') <> 'void':
                     fixedSizeStr = fixedSizeStr + '\n        if(Structure->' + memberElement.get('name') + ' != NULL)\n'
                     fixedSizeStr = fixedSizeStr + '        {\n'
                     fixedSizeStr = fixedSizeStr + '            qsResult += ' + str(GetPrimitiveSize(memberElement.get('type'))) + ';\n'
                     fixedSizeStr = fixedSizeStr + '        }\n'
            # Handle variable length pointers
            else:
               # Find the length parameter and check if it is a pointer or value
               for otherMember in structElement.findall('member'):
                  if otherMember.get('name') == memberElement.get('lengthParam'):
                     if 'value' in otherMember.get('attributes'):
                        fixedSizeStr = fixedSizeStr + '\n        if(Structure->' + memberElement.get('name') + ' != NULL)\n'
                        fixedSizeStr = fixedSizeStr + '        {\n'
                        fixedSizeStr = fixedSizeStr + '            qsResult += ((Structure->' + memberElement.get('lengthParam') + ') * (' + str(GetPrimitiveSize(memberElement.get('type'))) + '));\n'
                        fixedSizeStr = fixedSizeStr + '        }\n'
                     else:
                        fixedSizeStr = fixedSizeStr + '\n        if(Structure->' + memberElement.get('name') + ' != NULL)\n'
                        fixedSizeStr = fixedSizeStr + '        {\n'
                        fixedSizeStr = fixedSizeStr + '            qsResult += (*(Structure->' + memberElement.get('lengthParam') + ') * (' + str(GetPrimitiveSize(memberElement.get('type'))) + '));\n'
                        fixedSizeStr = fixedSizeStr + '        }\n'
                     foundMember = True
                     break
               if not foundMember and memberElement.get('type') <> 'void':
                  fixedSizeStr = fixedSizeStr + '\n        if(Structure->' + memberElement.get('name') + ' != NULL)\n'
                  fixedSizeStr = fixedSizeStr + '        {\n'
                  fixedSizeStr = fixedSizeStr + '            qsResult += ' + str(GetPrimitiveSize(memberElement.get('type'))) + ';\n'
                  fixedSizeStr = fixedSizeStr + '        }\n'
         else:
            # Handle single pointers to structures
            if memberElement.get('lengthParam') == '1':
               fixedSizeStr = fixedSizeStr + '\n        qsResult += ' + GetCalcPackedSizeFunctionName(memberElement.get('type')) + '(' + GetCastStr(memberElement.get('type')) + '&Structure->' + memberElement.get('name') + ');\n'

            # # Handle variable length structures arrays
            else:
               # Find the length parameter and check if it is a pointer or value
               for otherMember in structElement.findall('member'):
                  if otherMember.get('name') == memberElement.get('lengthParam'):
                     if 'value' in otherMember.get('attributes'):
                        varSizeStr = varSizeStr + '\n        if(Structure->' + memberElement.get('name') + ' != NULL)\n'
                        varSizeStr = varSizeStr + '        {\n'
                        varSizeStr = varSizeStr + '            for (qsIndex = 0; qsIndex < Structure->'  + memberElement.get('lengthParam') + '; qsIndex++)\n'
                        varSizeStr = varSizeStr + '                qsResult += ' + GetCalcPackedSizeFunctionName(memberElement.get('type')) + '(&(' + GetCastStr(memberElement.get('type')) + 'Structure->' + memberElement.get('name') + ')[qsIndex]);\n'
                        varSizeStr = varSizeStr + '        }\n'
                     else:
                        varSizeStr = varSizeStr + '\n        if(Structure->' + memberElement.get('name') + ' != NULL)\n'
                        varSizeStr = varSizeStr + '        {\n'
                        varSizeStr = varSizeStr + '            for (qsIndex = 0; qsIndex < *Structure->'  + memberElement.get('lengthParam') + '; qsIndex++)\n'
                        varSizeStr = varSizeStr + '                qsResult += ' + GetCalcPackedSizeFunctionName(memberElement.get('type')) + '(' + GetCastStr(memberElement.get('type')) + '&Structure->' + memberElement.get('name') + '[qsIndex]);\n'
                        varSizeStr = varSizeStr + '        }\n'
                     break
      elif memberElement.get('attributes') == 'union':
         if len(memberElement.findall('unionMap')) > 0:
            unionMap = memberElement.findall('unionMap')[-1]
            if unionMap.get('name') is not None:
               unionSizeStr = unionSizeStr + '\n        switch(Structure->' + unionMap.get('name') + ')\n'
               unionSizeStr = unionSizeStr + '        {\n'
               for mapEntry in unionMap.findall('mapEntry'):
                  unionMember = memberElement.findall('member')[0]
                  for members in memberElement.findall('member'):
                     if members.get('name') == mapEntry.get('member'):
                        unionMember = members
                  unionSizeStr = unionSizeStr + '            case ' + mapEntry.get('value') + ':\n'
                  if unionMember.get('attributes') == 'value':
                     unionSizeStr = unionSizeStr + '                qsResult += ' + GetCalcPackedSizeFunctionName(mapEntry.get('type')) + '(' + GetCastStr(mapEntry.get('type')) + '&Structure->' + memberElement.get('name') + '.' + unionMember.get('name') + ');\n'
                  elif unionMember.get('attributes') == 'ptr,bracketArray':
                     unionSizeStr = unionSizeStr + '                qsResult += (' + GetSizeOfStr(mapEntry.get('type')) + '*(' + unionMember.get('lengthParam') + '));\n'
                  else:
                     unionSizeStr = unionSizeStr + '                if(Structure->' + memberElement.get('name') + '.' + unionMember.get('name') + ' != NULL)\n'
                     unionSizeStr = unionSizeStr + '                    qsResult += ' + GetCalcPackedSizeFunctionName(mapEntry.get('type')) + '(' + GetCastStr(mapEntry.get('type')) + 'Structure->' + memberElement.get('name') + '.' + unionMember.get('name') + ');\n'
                  unionSizeStr = unionSizeStr + '                break;\n'
               unionSizeStr = unionSizeStr + '            default:\n'
               unionSizeStr = unionSizeStr + '                break;\n'
               unionSizeStr = unionSizeStr + '        }\n'
      elif 'bracketArray' in memberElement.get('attributes'):
            fixedSizeStr = fixedSizeStr + '\n        qsResult += (' + GetSizeOfStr(memberElement.get('type')) + '*(' + memberElement.get('lengthParam') + '));\n'
      else:
         if memberElement.get('type') in qsgCommon.structList:
            fixedSizeStr = fixedSizeStr + '\n        qsResult += ' + GetCalcPackedSizeFunctionName(memberElement.get('type')) + '(' + GetCastStr(memberElement.get('type')) + '&Structure->' + memberElement.get('name') + ');\n'

   # Write the function.
   c_file.write('\n')
   if isManualCode:
      c_file.write('uint32_t Mnl_CalcPackedSize_' + structElement.get('name') + '(' + structElement.get('name') + ' *Structure)\n')
   else:
      c_file.write('uint32_t CalcPackedSize_' + structElement.get('name') + '(' + structElement.get('name') + ' *Structure)\n')
   c_file.write('{\n')
   if isManualCode:
      c_file.write('\n#error Must complete this code manually.\n\n')
   if varSizeStr <> '':
      c_file.write('    uint32_t qsIndex;\n')
   c_file.write('    uint32_t qsResult;\n\n')
   c_file.write('    if(Structure == NULL)\n')
   c_file.write('    {\n')
   c_file.write('        qsResult = 0;\n')
   c_file.write('    }\n')
   c_file.write('    else\n')
   c_file.write('    {\n')
   c_file.write('        qsResult = ' + structElement.get('name').upper() + '_MIN_PACKED_SIZE;\n')
   c_file.write(fixedSizeStr)
   c_file.write(varSizeStr)
   c_file.write(unionSizeStr)
   c_file.write('    }\n\n')
   c_file.write('    return(qsResult);\n')
   c_file.write('}\n')

