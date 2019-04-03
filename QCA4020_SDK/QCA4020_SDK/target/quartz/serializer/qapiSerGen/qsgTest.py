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
import random
from xml.etree.ElementTree import Element, ElementTree, SubElement, Comment, tostring, parse
from xml.dom import minidom

from qsgUtils import *
import qsgCommon

GENERATE_WARNS_ERRORS = False
DATA_STRING  = '1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
TEST_ITERATIONS = 20

def CreateTestCode(xmlFile, component, root):
   try:
      fileName = xmlFile.replace('.xml', '')
      # Find out if we need to create a manually written code file for functions in this module
      manualFuncFileNeeded = False
      manual_c_file = None
      for functionElement in root.findall('function'):
         if functionElement.get('name') in qsgCommon.manualFuncList:
            manualFuncFileNeeded = True
            if qsgCommon.generateManual:
               manual_c_file = CreateManualTestFunctionFiles(fileName, component, root)

      ComponentTestFile = open(CreateTestFileName(component), 'a')

      # Create the auto-gen code
      auto_c_file = CreateAutoTestFunctionFiles(fileName, component, root, manualFuncFileNeeded)

      # Generate the function packing functions
      for functionElement in root.findall('function'):
         # We will not test functions with callback functions
         # or double ptrs as arguments
         if not FunctionWithCallbackArgumentOrDoublePtr(functionElement):
            if functionElement.get('name') in qsgCommon.manualFuncList:
               CreateManualTestFunctionStubs(functionElement, auto_c_file)
               if qsgCommon.generateManual:
                  CreateTestFunctions(component, functionElement, manual_c_file, True)
            else:
               CreateTestFunctions(component, functionElement, auto_c_file, False)

            # Add to component test function
            if ComponentTestFile is not None:
               ComponentTestFile.write('    if(!Test_' + functionElement.get('name') + '())\n')
               ComponentTestFile.write('    {\n')
               ComponentTestFile.write('       FailureCount++;\n')
               ComponentTestFile.write('    }\n\n')

      auto_c_file.close()
      if manual_c_file is not None:
         manual_c_file.close()

   except IOError:
      ComponentTestFile = None;

   #Close the component test file
   if ComponentTestFile is not None:
      ComponentTestFile.close()

def CreateAutoTestFunctionFiles(fileName, component, root, manualFuncFileNeeded):
   # Create a C file.
   auto_c_file = open(os.path.join(qsgCommon.qapiDir, 'test', fileName + '_test.c'), 'w+')

   auto_c_file.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')
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
   auto_c_file.write('#include <string.h>\n')
   auto_c_file.write('#include <stdlib.h>\n')
   auto_c_file.write('#include "qsPack.h"\n')
   auto_c_file.write('#include "qapi_' + component + '.h"\n')
   auto_c_file.write('#include "random_struct_init.h"\n\n')
   auto_c_file.write('#include "qsCommon.h"\n\n')

   auto_c_file.write('/* C files to test. */\n')
   auto_c_file.write('#include "' + fileName + '_common.c' + '"\n')
   if len(root.findall('callback')) > 0:
      auto_c_file.write('#include "' + fileName + '_host_cb.c' + '"\n')
   auto_c_file.write('#include "' + fileName + '_host.c' + '"\n')
   if len(root.findall('callback')) > 0:
      auto_c_file.write('#include "' + fileName + '_qz_cb.c' + '"\n')
   auto_c_file.write('#include "' + fileName + '_qz.c' + '"\n\n')
   if manualFuncFileNeeded:
      auto_c_file.write('#include "' + fileName + '_test_mnl.c' + '"\n\n')

   auto_c_file.write('extern Boolean_t ' + component + '_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);' + '\n')
   auto_c_file.write('extern Boolean_t ' + component + '_SendResponse(PackedBuffer_t *InputBuffer);' + '\n\n')

   auto_c_file.write('#define SendCommand(_a, _b) ' + component + '_SendCommand(_a, _b, __func__)\n')
   auto_c_file.write('#define SendResponse(_a) ' + component + '_SendResponse(_a)\n\n')

   auto_c_file.write('extern Boolean_t  ' + component + '_FirstSendCommandCall;\n')
   auto_c_file.write('extern Boolean_t  ' + component + '_CommandSuccess;\n')
   auto_c_file.write('extern uint32_t   ' + component + '_FirstLength;\n')
   auto_c_file.write('extern uint8_t   *' + component + '_FirstStart;\n')
   auto_c_file.write('extern uint32_t   ' + component + '_CommandIteration;\n')

   # Create a C header.
   h_file = open(os.path.join(qsgCommon.qapiDir, 'test', 'include', fileName + '_test.h'), 'w+')

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

   h_file.write('#ifndef __' + (fileName + '_test' + '_h__').upper() + '\n')
   h_file.write('#define __' + (fileName + '_test' + '_h__').upper() + '\n')

   h_file.write('#include <stdint.h>\n')
   h_file.write('#include "qsCommon.h"\n\n')

   # Define prototypes
   for functionElement in root.findall('function'):
      h_file.write('Boolean_t Test_' + functionElement.get('name') + '(void);\n')

   h_file.write('\n#endif // __' + (fileName + '_test' + '_h__').upper() + '\n')

   # Close the header.
   h_file.close()

   return auto_c_file

def CreateManualTestFunctionFiles(fileName, component, root):
   # Create a C file.
   manual_c_file = open(os.path.join(qsgCommon.manualDir, 'test', fileName + '_test_mnl.c'), 'w+')

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
   manual_c_file.write('#include <stdlib.h>\n')
   manual_c_file.write('#include "qsPack.h"\n')
   manual_c_file.write('#include "qapi_' + component + '.h"\n')
   manual_c_file.write('#include "random_struct_init.h"\n\n')
   manual_c_file.write('#include "qsCommon.h"\n\n')
   manual_c_file.write('#include "' + fileName + '_test_mnl.h"\n\n')

   manual_c_file.write('extern Boolean_t ' + component + '_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function);' + '\n')
   manual_c_file.write('extern Boolean_t ' + component + '_SendResponse(PackedBuffer_t *InputBuffer);' + '\n\n')

   manual_c_file.write('#define SendCommand(_a, _b) ' + component + '_SendCommand(_a, _b, __func__)\n')
   manual_c_file.write('#define SendResponse(_a) ' + component + '_SendResponse(_a)\n\n')

   manual_c_file.write('extern Boolean_t  ' + component + '_FirstSendCommandCall;\n')
   manual_c_file.write('extern Boolean_t  ' + component + '_CommandSuccess;\n')
   manual_c_file.write('extern uint32_t   ' + component + '_FirstLength;\n')
   manual_c_file.write('extern uint8_t   *' + component + '_FirstStart;\n')
   manual_c_file.write('extern uint32_t   ' + component + '_CommandIteration;\n')

   # Create a C header.
   manual_h_file = open(os.path.join(qsgCommon.manualDir, 'test', 'include', fileName + '_test_mnl.h'), 'w+')

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

   manual_h_file.write('#ifndef __MNL_' + (fileName + '_test' + '_h__').upper() + '\n')
   manual_h_file.write('#define __MNL_' + (fileName + '_test' + '_h__').upper() + '\n')

   manual_h_file.write('#include <stdint.h>\n')
   manual_h_file.write('#include "qsCommon.h"\n\n')

   # Define prototypes
   for functionElement in root.findall('function'):
      if functionElement.get('name') in qsgCommon.manualFuncList:
         manual_h_file.write('Boolean_t Mnl_Test_' + functionElement.get('name') + '(void);\n')

   manual_h_file.write('\n#endif // __MNL_' + (fileName + '_test' + '_h__').upper() + '\n')

   # Close the header.
   manual_h_file.close()

   return manual_c_file

def CreateStructureFiles():
   if not os.path.exists(os.path.join(qsgCommon.qapiDir, 'test', 'include')):
      os.makedirs(os.path.join(qsgCommon.qapiDir, 'test', 'include'))

   manual_c_file = None
   manual_h_file = None

   c_file = open(os.path.join(qsgCommon.qapiDir, 'test', 'random_struct_init.c'), 'w+')
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

   h_file = open(os.path.join(qsgCommon.qapiDir, 'test', 'include', 'random_struct_init.h'), 'w+')
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
   if qsgCommon.generateManual:
      manual_c_file = open(os.path.join(qsgCommon.manualDir, 'test', 'random_struct_init_mnl.c'), 'w+')
      manual_c_file.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')
      manual_h_file = open(os.path.join(qsgCommon.manualDir, 'test', 'include', 'random_struct_init_mnl.h'), 'w+')
      manual_h_file.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')

   h_file.write('#ifndef __INITIALIZE_STRUCTURES_H__\n')
   h_file.write('#define __INITIALIZE_STRUCTURES_H__\n')
   h_file.write('\n')
   h_file.write('#include "qsCommon.h"\n')

   c_file.write('#include <time.h>\n')
   c_file.write('#include <stdlib.h>\n')
   c_file.write('#include <string.h>\n')
   c_file.write('#include "random_struct_init_mnl.h"\n')
   c_file.write('\n')

   if qsgCommon.generateManual:
      manual_h_file.write('#ifndef __MNL_INITIALIZE_STRUCTURES_H__\n')
      manual_h_file.write('#define __MNL_INITIALIZE_STRUCTURES_H__\n')
      manual_h_file.write('\n')
      manual_h_file.write('#include "qsCommon.h"\n')

      manual_c_file.write('#include <time.h>\n')
      manual_c_file.write('#include <stdlib.h>\n')
      manual_c_file.write('#include <string.h>\n')
      manual_c_file.write('\n')

   return c_file, h_file, manual_c_file, manual_h_file

def CloseStructureFiles(c_file, h_file, manual_c_file, manual_h_file):
   if qsgCommon.generateManual:
      manual_h_file.write('\n#endif /* __MNL_INITIALIZE_STRUCTURES_H__ */\n')
      manual_h_file.close()
      manual_c_file.close()

   h_file.write('\n#endif /* __INITIALIZE_STRUCTURES_H__ */\n')

   h_file.close()
   c_file.close()

def IsVariableLengthInputPointer(argElement):
   # Make sure this is a pointer
   if (argElement.get('attributes') == 'ptr' or argElement.get('attributes') == 'ptr,const'):
      # Make sure this pointer argument is an input pointer
      if (argElement.get('iotype') is not None and 'in' in argElement.get('iotype')):
         # Make sure the length parameter is not '1' (denoting pointer to single value or structure)
         if (argElement.get('lengthParam') is not None) and (argElement.get('lengthParam') <> '1'):
            return True

   return False

def ParameterIsPtrLengthValue(ArgumentName, parent):
   paramName = ''
   if len(parent.findall('argument')) > len(parent.findall('member')):
      paramName = 'argument'
   if len(parent.findall('member')) > len(parent.findall('argument')):
      paramName = 'member'

   if len(parent.findall(paramName)) > 0:
      for argElement in parent.findall(paramName):
         # Check to see if this is a variable length pointer
         if IsVariableLengthInputPointer(argElement):
            # Check to see if the requested argument is the length parameter
            # for this variable length pointer argument
            if ArgumentName == argElement.get('lengthParam'):
               # Return the variable length pointer arg
               return argElement

   return None

def GenerateProperRangedRandomValue(type):
   Start = 0
   Stop  = 0

   # qapi_status is int32_t
   if 'qapi_Status_t' in type:
      Start = -(2 ** (31))
      Stop  = (2 ** 31) - 1
   elif 'int8' in type:
      if 'uint' in type:
         Start = 0
         Stop  = (2 ** 8) - 1
      else:
         Start = - (2 ** 7)
         Stop  = (2 ** 7) - 1
   elif 'int16' in type:
      if 'uint' in type:
         Start = 0
         Stop  = (2 ** 16) - 1
      else:
         Start = - (2 ** 15)
         Stop  = (2 ** 15) - 1
   elif 'int32' in type or type in qsgCommon.enumList:
      if 'uint' in type or type in qsgCommon.enumList:
         Start = 0
         Stop  = (2 ** 32) - 1
      else:
         Start = - (2 ** 31)
         Stop  = (2 ** 31) - 1
   elif 'int64' in type:
      if 'uint' in type:
         Start = 0
         Stop  = (2 ** 32) - 1
      else:
         Start = - (2 ** 31)
         Stop  = (2 ** 31) - 1
   elif 'bool' in type:
      Start = 0
      Stop  = 1
   elif type == 'int' or type == 'unsigned int' or type == 'signed int' or 'long' in type:
      if 'unsigned' in type:
         Start = 0
         Stop  = (2 ** 32) - 1
      else:
         Start = - (2 ** 31)
         Stop  = (2 ** 31) - 1
   elif type == 'char' or type == 'unsigned char' or type == 'signed char':
      if 'unsigned' in type:
         Start = 0
         Stop  = (2 ** 8) - 1
      else:
         Start = - (2 ** 7)
         Stop  = (2 ** 7) - 1
   elif type == 'qapi_BLE_NonAlignedByte_t' or type == 'qapi_BLE_NonAlignedSByte_t':
      Start = 0
      Stop  = (2 ** 8) - 1
   else:
      print('ERROR : Improper value to GenerateProperRangedRandomValue()\n')

   return random.randrange(Start, Stop)

   # Handles random values
def GeneratePrimitiveRandomValue(Prefix, c_file, PrimitiveType, PrimitiveName, IsVariableLengthParam, UseCRand):
   global DATA_STRING

   if IsNonStructPrimitive(PrimitiveType):
      if UseCRand:
         if IsVariableLengthParam:
            RandStr = '(rand() % 512)'
         else:
            # Check to see if this is a char.  If so make sure the character is a printable char
            if PrimitiveType == 'char' or PrimitiveType == 'unsigned char' or PrimitiveType == 'signed char':
               RandStr = '(rand() % 33) + 65'
            else:
               RandStr = 'rand()'
      else:
         # handle strings a little different
         if PrimitiveType == 'char' or PrimitiveType == 'unsigned char' or PrimitiveType == 'signed char':
            Rand = random.randrange(0, len(DATA_STRING))

            RandStr = "'" + DATA_STRING[Rand] + "'"
         else:
            if IsVariableLengthParam:
               RandStr = str(random.randrange(0, 512))
            else:
               RandStr = str(GenerateProperRangedRandomValue(PrimitiveType))

      c_file.write(Prefix + PrimitiveName + ' = (' + PrimitiveType + ')(' + RandStr + ');\n')
   else:
      c_file.write(Prefix + 'memset(&(' + PrimitiveName + '), 0xA5, ' + GetSizeOfStr(PrimitiveType) + ');\n')

def GenerateRandomArgumentValue(Prefix, c_file, argName, argElement, functionElement, UseCRand):
   if argElement.get('type') is not None:
      if IsPrimitive(argElement.get('type')):
         PrimitiveName = argName

         VarPtrArg = ParameterIsPtrLengthValue(argElement.get('name'), functionElement)
         if VarPtrArg is not None:
            GeneratePrimitiveRandomValue(Prefix, c_file, argElement.get('type'), PrimitiveName, True, UseCRand)
         else:
            GeneratePrimitiveRandomValue(Prefix, c_file, argElement.get('type'), PrimitiveName, False, UseCRand)
      else:
         # Check to see if this is an enum
         if argElement.get('type') in qsgCommon.enumList:
            PrimitiveName = argName

            GenerateEnumRandomValue(Prefix, c_file, argElement.get('type'), PrimitiveName, UseCRand)
         else:
            if argElement.get('type') in qsgCommon.structList:
               PrimitiveName = '&(' + argName + ')'

               SubFunction   = 'GenerateRandom_' + argElement.get('type')
               c_file.write(Prefix + SubFunction + '(' + PrimitiveName + ', &qsBufferList);\n')
            else:
               if not argElement.get('type') in qsgCommon.unionList:
                  c_file.write(Prefix + '#pragma message ("Unrecognized type (not pointer or struct or enum or union or primitive ' + argElement.get('type') + '")\n')
   return

def GenerateRandomStructInitializerStub(c_file, h_file, StructRoot, StructureElement):
   # Verify that we have not processed this structure
   if StructureElement.get('name') not in qsgCommon.processedStructList:
      # Generate the Function Name
      FunctionName = 'GenerateRandom_' + StructureElement.get('name')

      # Add the function prototype to the h file
      h_file.write('void ' + FunctionName + '(' + StructureElement.get('name') + ' *Ptr, BufferListEntry_t **BufferList);\n')

      # Add the function definition to the c file
      c_file.write('void ' + FunctionName + '(' + StructureElement.get('name') + ' *Ptr, BufferListEntry_t **BufferList)\n')
      c_file.write('{\n')
      c_file.write('   Mnl_' + FunctionName + '(Ptr, BufferList);\n')
      c_file.write('}\n\n')

   return

def GenerateRandomStructInitializer(c_file, h_file, StructRoot, StructureElement, isManualCode):
   global GENERATE_WARNS_ERRORS

   # Verify that we have not processed this structure
   if StructureElement.get('name') not in qsgCommon.processedStructList:
      # Add to the list to indicate that this type has been processed
      qsgCommon.processedStructList.append(StructureElement.get('name'))

      # Generate the Function Name
      if isManualCode:
         FunctionName = 'Mnl_GenerateRandom_' + StructureElement.get('name')
      else:
         FunctionName = 'GenerateRandom_' + StructureElement.get('name')

      # Add the function prototype to the h file
      h_file.write('void ' + FunctionName + '(' + StructureElement.get('name') + ' *Ptr, BufferListEntry_t **BufferList);\n')

      # Add the function definition to the c file
      c_file.write('void ' + FunctionName + '(' + StructureElement.get('name') + ' *Ptr, BufferListEntry_t **BufferList)\n')
      c_file.write('{\n')

      if isManualCode:
         c_file.write('#error Must complete this code manually.\n\n')

      Prefix    = '   '

      # Check input parameters
      c_file.write(Prefix + 'if((Ptr != NULL) && (BufferList != NULL))\n')
      c_file.write(Prefix + '{\n')

      # Increase indentation
      Prefix    = Prefix + '   '

      # Clear structure to 0
      c_file.write(Prefix + 'memset(Ptr, 0, sizeof(' + StructureElement.get('name') + '));\n')

      # Process all members (excluding pointers which are processed last)
      for Member in StructureElement.findall('member'):
         # Reset sub prefix
         SubPrefix = Prefix

         # verify that this is not a double pointer argument
         if not ('doubleptr' in Member.get('attributes')):
            if not (Member.get('attributes') == 'ptr' or Member.get('attributes') == 'ptr,const' or 'bracketArray' in Member.get('attributes')):
               # Get the member name
               ModifiedMemberName = Member.get('name')

               # Get if this is an array
               searchObj = re.search( r'\[(.*)\]$', ModifiedMemberName, 0)
               if searchObj:
                  IsArray   = True
                  ArraySize = searchObj.group(1)

                  if len(ArraySize) == 0:
                     ArraySize = '1'

                  # Remove array indices
                  ModifiedMemberName = re.sub(r'\[(.*)\]$', '', ModifiedMemberName)
               else:
                  IsArray   = False
                  ArraySize = ''

               if IsArray and len(ArraySize) > 0:
                  SubPrefix          = SubPrefix + '   '
                  ModifiedMemberName = ModifiedMemberName + '[Index]'
                  c_file.write(Prefix + 'for(unsigned int Index=0;Index<' + ArraySize + ';Index++)\n')
                  c_file.write(Prefix + '{\n')

               if (Member.get('type') is not None) and (Member.get('type') <> 'void'):
                  if IsPrimitive(Member.get('type')):
                     PrimitiveName = 'Ptr->' + ModifiedMemberName

                     VarPtrArg     = ParameterIsPtrLengthValue(Member.get('name'), StructureElement)
                     if VarPtrArg is not None:
                        GeneratePrimitiveRandomValue(SubPrefix, c_file, Member.get('type'), PrimitiveName, True, True)
                     else:
                        GeneratePrimitiveRandomValue(SubPrefix, c_file, Member.get('type'), PrimitiveName, False, True)
                  else:
                     # Check to see if this is an enum
                     if Member.get('type') in qsgCommon.enumList:
                        PrimitiveName = 'Ptr->' + ModifiedMemberName
                        GenerateEnumRandomValue(SubPrefix, c_file, Member.get('type'), PrimitiveName, True)
                     else:
                        if Member.get('type') in qsgCommon.structList:
                           PrimitiveName = '&(Ptr->' + ModifiedMemberName + ')'

                           SubFunction   = 'GenerateRandom_' + Member.get('type')
                           c_file.write(SubPrefix + SubFunction + '(' + PrimitiveName + ', BufferList);\n')
                        else:
                           if Member.get('type') in qsgCommon.unionList:
                              PrimitiveName = '&(Ptr->' + ModifiedMemberName + ')'
                              c_file.write(SubPrefix + '/*Memset union.*/\n')
                              c_file.write(SubPrefix + 'memset(' + PrimitiveName + ', 0xA5, sizeof(' + Member.get('type') + '));\n')
                           else:
                              if GENERATE_WARNS_ERRORS:
                                 c_file.write(SubPrefix + '#error "Unrecognized type (not pointer or struct or enum or union or primitive ' + Member.get('type') + '"\n')
               else:
                  if (Member.get('type') is None) or (Member.get('type') <> 'void'):
                     PrimitiveName = 'Ptr->' + ModifiedMemberName
                     c_file.write(SubPrefix + 'memset(&(' + PrimitiveName + '), 0xA5, sizeof(' + PrimitiveName + '));\n')

               if IsArray and len(ArraySize) > 0:
                  # Index + ArraySize
                  # NULL Terminate strings
                  if Member.get('type') == 'char' or Member.get('type') == 'unsigned char' or Member.get('type') == 'signed char':
                     PrimitiveName = 'Ptr->' + ModifiedMemberName

                     c_file.write(SubPrefix + 'if(Index == (' + ArraySize + ' - 1))\n')
                     c_file.write(SubPrefix + '   ' + PrimitiveName + " = '\\0';\n")

                  c_file.write(Prefix + '}\n')

         else:
            # Set double pointer to NULL
            c_file.write(Prefix + 'Ptr->' + Member.get('name') + ' = NULL;\n')

      for Member in StructureElement.findall('member'):
         # Reset sub prefix
         SubPrefix = Prefix

         # Do not handle double ptrs
         if not ('doubleptr' in Member.get('attributes')):
            if (Member.get('attributes') == 'ptr' or Member.get('attributes') == 'ptr,const'):

               # Get the member name
               ModifiedMemberName = Member.get('name')

               # Get the primitive name
               PtrName = 'Ptr->' + ModifiedMemberName

               # Check to see if this is a void pointer.
               if (Member.get('type') is not None) and (Member.get('type') == 'void'):
                  # Modify the pointer name
                  PtrName = '((uint8_t *)(' + PtrName + '))'

                  # Modify the type
                  Member.set('type', 'uint8_t')

                  # Type Modified
                  TypeModified = True
               else:
                  # If this is a const pointer we need to cast in order to set it
                  if Member.get('attributes') == 'ptr,const':
                     PtrName = '((' + Member.get('type') + '*)(' + PtrName + '))'

                  TypeModified = False

               # Check to see if this is a variable length pointer or not
               if IsVariableLengthInputPointer(Member):
                  if Member.get('lengthParam') == '__strlen__':
                     ArraySize  = str(random.randrange(0, 512))
                     SizeString = '(sizeof(' + Member.get('type') + ') * ' + ArraySize + ')'
                  else:
                     # Bypass length if length is from pointer member
                     PointerLength = False
                     for OtherMember in StructureElement.findall('member'):
                        if OtherMember.get('name') ==  Member.get('lengthParam'):
                           if 'ptr' in OtherMember.get('attributes'):
                              PointerLength = True
                              break

                     LengthParamName = 'Ptr->' + Member.get('lengthParam')

                     if PointerLength:
                        LengthNullCheck = '((' + LengthParamName + ' == NULL) ? 1 : ' + LengthParamName + '[0])'
                        ArraySize       = LengthNullCheck
                        SizeString      = '(sizeof(' + Member.get('type') + ') * ' + LengthNullCheck + ')'
                     else:
                        ArraySize  = LengthParamName
                        SizeString = '(sizeof(' + Member.get('type') + ') * ' + LengthParamName + ')'
               else:
                  ArraySize  = '1'
                  SizeString = '(sizeof(' + Member.get('type') + '))'

               # Allocate the memory void *AllocateBufferListEntry(BufferListEntry_t **BufferList, uint16_t Size);
               c_file.write(SubPrefix + PtrName + ' = (' +  Member.get('type') + ' *)AllocateBufferListEntry(BufferList, ' + SizeString + ');\n')

               c_file.write(SubPrefix + 'if(' + PtrName + ' != NULL)\n')
               c_file.write(SubPrefix + '{\n')

               #Increase the identation
               SubPrefix = SubPrefix + '   '

               if ArraySize <> '1':
                  c_file.write(SubPrefix + 'for(unsigned int Index=0;Index<(unsigned int)' + ArraySize + ';Index++)\n')
                  c_file.write(SubPrefix + '{\n')

                  #Increase the ident
                  SubSubPrefix = SubPrefix + '   '
                  PtrName      = PtrName + '[Index]'
               else:
                  SubSubPrefix = SubPrefix
                  PtrName      = PtrName + '[0]'

               if Member.get('type') is not None:
                  if IsPrimitive(Member.get('type')):
                     PrimitiveName = PtrName

                     VarPtrArg     = ParameterIsPtrLengthValue(Member.get('name'), StructureElement)
                     if VarPtrArg is not None:
                        GeneratePrimitiveRandomValue(SubSubPrefix, c_file, Member.get('type'), PrimitiveName, True, True)
                     else:
                        GeneratePrimitiveRandomValue(SubSubPrefix, c_file, Member.get('type'), PrimitiveName, False, True)
                  else:
                     # Check to see if this is an enum
                     if Member.get('type') in qsgCommon.enumList:
                        PrimitiveName = PtrName
                        GenerateEnumRandomValue(SubSubPrefix, c_file, Member.get('type'), PrimitiveName, True)
                     else:
                        if Member.get('type') in qsgCommon.structList:
                           PrimitiveName = '&(' + PtrName + ')'

                           SubFunction   = 'GenerateRandom_' + Member.get('type')
                           c_file.write(SubSubPrefix + SubFunction + '(' + PrimitiveName + ', BufferList);\n')
                        else:
                           if Member.get('type') in qsgCommon.unionList:
                              PrimitiveName = '&(' + PtrName + ')'
                              c_file.write(SubSubPrefix + '/*Memset union.*/\n')
                              c_file.write(SubSubPrefix + 'memset(' + PrimitiveName + ', 0xA5, sizeof(' + Member.get('type') + '));\n')
                           else:
                              if GENERATE_WARNS_ERRORS:
                                 c_file.write(SubSubPrefix + '#error "Unrecognized type (not pointer or struct or enum or union or primitive ' + Member.get('type') + '"\n')
               else:
                  PrimitiveName = PtrName
                  c_file.write(SubSubPrefix + 'memset(&(' + PrimitiveName + '), 0xA5, sizeof(' + PrimitiveName + '));\n')

               if ArraySize <> '1':
                  if Member.get('type') == 'char' or Member.get('type') == 'unsigned char' or Member.get('type') == 'signed char':
                     PrimitiveName = PtrName
                     c_file.write('\n')
                     c_file.write(SubSubPrefix + '/* always NULL terminate character strings.*/\n')
                     c_file.write(SubSubPrefix + 'if(Index == (' + ArraySize + ' - 1))\n')
                     c_file.write(SubSubPrefix + '   ' + PrimitiveName + " = '\\0';\n")

                  c_file.write(SubPrefix + '}\n')

               # Modify type back if we modified
               if TypeModified:
                  # Modify the type
                  Member.set('type', 'void')

               # Reset sub prefix
               SubPrefix = Prefix
               c_file.write(SubPrefix + '}\n')
            elif 'bracketArray' in Member.get('attributes') and Member.get('fixedLength') is not None and Member.get('fixedLength') == 'true':

               # Get the member name
               ModifiedMemberName = Member.get('name')

               # Get the primitive name
               PtrName = 'Ptr->' + ModifiedMemberName

               c_file.write(SubPrefix + 'for(unsigned int Index=0;Index<(unsigned int)' + Member.get('lengthParam') + ';Index++)\n')
               c_file.write(SubPrefix + '{\n')

               if Member.get('type') in qsgCommon.structList:
                  c_file.write(SubPrefix + '   GenerateRandom_' + Member.get('type') + '(&(' + PtrName + '[Index]), BufferList);\n')
               else:
                  c_file.write(SubPrefix + '   ' + PtrName + '[Index] = (' + Member.get('type') + ')(rand());\n')
               c_file.write(SubPrefix + '}\n')
         else:
            # Set double pointer to NULL
            c_file.write(SubPrefix + 'Ptr->' + Member.get('name') + ' = NULL;\n')

      # Reset indent
      Prefix    = '   '

      # end function
      c_file.write(Prefix + '}\n')
      c_file.write('}\n\n')

   return

   # Generate test function.   Does not accept function with callback function parameters
def CreateManualTestFunctionStubs(functionElement, c_file):
   # Write test function implementation
   c_file.write('\nBoolean_t Test_' + functionElement.get('name') + '(void)\n')
   c_file.write('{\n')
   # Call manual Function
   c_file.write('   return(Mnl_Test_' + functionElement.get('name') + '());\n')
   c_file.write('}\n')

   return

   # Generate test function.   Does not accept function with callback function parameters
def CreateTestFunctions(component, functionElement, c_file, isManualCode):
   global TEST_ITERATIONS
   global GENERATE_WARNS_ERRORS

   # Write test function implementation
   if isManualCode:
      c_file.write('\nBoolean_t Mnl_Test_' + functionElement.get('name') + '(void)\n')
   else:
      c_file.write('\nBoolean_t Test_' + functionElement.get('name') + '(void)\n')

   c_file.write('{\n')
   c_file.write('   Boolean_t Success;\n')
   c_file.write('   BufferListEntry_t *qsBufferList  = NULL;\n')
   c_file.write('   unsigned int Index;\n\n')

   if isManualCode:
      c_file.write('\n#error Must complete this code manually.\n\n')

   # Declare function arguments
   ArgumentString = ''
   FirstLoop = True
   c_file.write('   /* Function arguments.   */\n')

   if len(functionElement.findall('argument')) > 0:
      for argElement in functionElement.findall('argument'):
         c_file.write('   ')
         c_file.write(argElement.get('type') + ' ')

         PtrPrefix = ''
         if 'ptr' in argElement.get('attributes'):
            if (argElement.get('iotype') is not None and 'in' in argElement.get('iotype')):
               if IsVariableLengthInputPointer(argElement) or argElement.get('type') == 'void':
                  c_file.write('*')
               else:
                  PtrPrefix = '&'
                  argElement.set('attributes', 'value')
            else:
               if argElement.get('type') == 'void':
                  c_file.write('*')
               else:
                  PtrPrefix = '&'
                  argElement.set('attributes', 'value')

         if 'ptr' in argElement.get('attributes'):
            c_file.write(argElement.get('name') + ' = NULL;\n')
         else:
            c_file.write(argElement.get('name') + ';\n')

         if not FirstLoop:
            ArgumentString = ArgumentString + ', ' + PtrPrefix + argElement.get('name')
         else:
            ArgumentString = PtrPrefix + argElement.get('name')
            FirstLoop = False

   c_file.write('\n   ' + component + '_CommandIteration = 1;\n\n')

   for x in range(0, TEST_ITERATIONS):
      Prefix = '   '
      c_file.write(Prefix + '/* Iteration = ' + str(x + 1) + '.               */\n')
      c_file.write(Prefix + component + '_FirstSendCommandCall = TRUE;\n')
      c_file.write(Prefix + component + '_CommandSuccess       = FALSE;\n')
      c_file.write(Prefix + component + '_FirstLength          = 0;\n')
      c_file.write(Prefix + component + '_FirstStart           = NULL;\n\n')

      # Generate random values for every argument to the function

      if len(functionElement.findall('argument')) > 0:
         for argElement in functionElement.findall('argument'):
            # Do not process pointers on first loop
            if not (argElement.get('attributes') == 'ptr' or argElement.get('attributes') == 'ptr,const'):

               # Memset to 0 for all unions/structs
               if (argElement.get('type') is None) or (not IsNonStructPrimitive(argElement.get('type'))):
                  c_file.write(Prefix + 'memset(&' + argElement.get('name') + ', 0, sizeof(' + argElement.get('name') + '));\n')

               # Do not process unions (no type).  Unions will not be supported via
               # generated code
               if (argElement.get('type') is not None) and (argElement.get('type') <> 'void'):
                  GenerateRandomArgumentValue(Prefix, c_file, argElement.get('name'), argElement, functionElement, False)

         for argElement in functionElement.findall('argument'):
            # Do not process pointers on first loop
            if (argElement.get('attributes') == 'ptr' or argElement.get('attributes') == 'ptr,const'):
               # Do not process unions (no type) or void types.  Unions will not be supported via
               # generated code
               if (argElement.get('type') is not None):
                  # Check to see if this is a variable length pointer or not
                  if IsVariableLengthInputPointer(argElement) or argElement.get('type') == 'void':
                     if argElement.get('lengthParam') == '__strlen__':
                        ArraySize  = str(random.randrange(0, 512))
                        SizeString = '(' + GetSizeOfStr(argElement.get('type')) + ' * ' + ArraySize + ')'
                     else:
                        ArraySize  = argElement.get('lengthParam')
                        SizeString = '(' + GetSizeOfStr(argElement.get('type')) + ' * ' + argElement.get('lengthParam') + ')'
                  else:
                     ArraySize  = '1'
                     SizeString = '(' + GetSizeOfStr(argElement.get('type')) + ')'

                  # Get the primitive name
                  PtrName = argElement.get('name')

                  # Allocate the memory void *AllocateBufferListEntry(BufferListEntry_t **BufferList, uint16_t Size);
                  c_file.write(Prefix + PtrName + ' = (' +  argElement.get('type') + ' *)AllocateBufferListEntry(&qsBufferList, ' + SizeString + ');\n')
                  c_file.write(Prefix + 'if(' + PtrName + ' != NULL)\n')
                  c_file.write(Prefix + '{\n')

                  SubPrefix = Prefix + '   '

                  if ArraySize <> '1':
                     c_file.write(SubPrefix + 'for(unsigned int Index=0;Index<' + ArraySize + ';Index++)\n')
                     c_file.write(SubPrefix + '{\n')

                     #Increase the ident
                     SubSubPrefix = SubPrefix + '   '
                     if argElement.get('type') == 'void':
                        PtrName      = '((uint8_t *)' + PtrName + ')[Index]'
                     else:
                        PtrName      = PtrName + '[Index]'
                     UseCRand     = True
                  else:
                     SubSubPrefix = SubPrefix
                     if argElement.get('type') == 'void':
                        PtrName      = '((uint8_t *)' + PtrName + ')[0]'
                     else:
                        PtrName      = PtrName + '[0]'
                     UseCRand     = False

                  # Do not generate random values for output arguments
                  GenerateRandomArgumentValue(SubSubPrefix, c_file, PtrName, argElement, functionElement, UseCRand)

                  if ArraySize <> '1':
                     if argElement.get('type') == 'char' or argElement.get('type') == 'unsigned char' or argElement.get('type') == 'signed char':
                        PrimitiveName = PtrName
                        c_file.write('\n')
                        c_file.write(SubSubPrefix + '/* always NULL terminate character strings.*/\n')
                        c_file.write(SubSubPrefix + 'if(Index == (' + ArraySize + ' - 1))\n')
                        c_file.write(SubSubPrefix + '   ' + PtrName + " = '\\0';\n")

                     c_file.write(SubPrefix + '}\n')

                  c_file.write(Prefix + '}\n')

               else:
                  if GENERATE_WARNS_ERRORS:
                     c_file.write(Prefix + '#pragma message ("Pointer without type : ' + argElement.get('name') + ' : code must be generated manually.")\n')


      c_file.write(Prefix + functionElement.get('name') + '(' + ArgumentString + ');\n')

      c_file.write(Prefix + 'if(' + component + '_CommandSuccess)\n')
      c_file.write(Prefix + '{\n')
      c_file.write(Prefix + '   Success = TRUE;\n\n')
      c_file.write(Prefix + '   FreeBufferList(&qsBufferList);\n')
      c_file.write(Prefix + '   qsBufferList = NULL;\n')
      c_file.write(Prefix + '}\n')
      c_file.write(Prefix + 'else\n')
      c_file.write(Prefix + '{\n')
      c_file.write(Prefix + '   OSAL_OutputMessage("%s failed at iteration %u\\n", "' + functionElement.get('name') + '", ' + component + '_CommandIteration);\n')
      c_file.write(Prefix + '   Success = FALSE;\n\n')
      c_file.write(Prefix + '   FreeBufferList(&qsBufferList);\n')
      c_file.write(Prefix + '   qsBufferList = NULL;\n\n')
      c_file.write(Prefix + '   return(Success);\n')
      c_file.write(Prefix + '}\n\n')
      c_file.write(Prefix + component + '_CommandIteration++;\n\n')

      # If this is a void function we only need to test it once
      if len(functionElement.findall('argument'))  == 0:
         break;

   # Close Function
   c_file.write('   return(Success);\n')
   c_file.write('}\n')

   return

def GenerateTestFileIncludes(component, xmlFile, ComponentTestFile):
   if not os.path.exists(os.path.join(qsgCommon.qapiDir, 'test')):
      os.makedirs(os.path.join(qsgCommon.qapiDir, 'test'))

   # Parse the XML input and get the root
   tree = parse(os.path.join(qsgCommon.qapiDir, 'xml', xmlFile))
   root = tree.getroot()

   if len(root.findall('function')) != 0:
      IncludeFileName = xmlFile.replace('.xml', '') + '_test.h'
      ComponentTestFile.write('#include "' + IncludeFileName + '"\n')

def CreateTestFileName(component):
   return os.path.join(qsgCommon.qapiDir, 'test', 'test_all_' + component + '_functions.c')

   # Create a test file to contain implementation calling
   # all test functions and print their success failure status
def CreateTestFile(component):
   if not os.path.exists(os.path.join(qsgCommon.qapiDir, 'test')):
      os.makedirs(os.path.join(qsgCommon.qapiDir, 'test'))

   c_file = open(CreateTestFileName(component), 'w+')

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
   c_file.write('#include "qapi_' + component + '.h"\n')
   c_file.write('#include "OSAL.h"\n')
   c_file.write('#include "qsCommon.h"\n')

   c_file.write('/* Test code glue.*/\n')
   c_file.write('Boolean_t  ' + component + '_FirstSendCommandCall;\n')
   c_file.write('Boolean_t  ' + component + '_CommandSuccess;\n')
   c_file.write('uint32_t   ' + component + '_FirstLength;\n')
   c_file.write('uint8_t   *' + component + '_FirstStart;\n')
   c_file.write('uint32_t   ' + component + '_CommandIteration;\n\n')

   c_file.write('SerStatus_t ' + component + '_SendResponse(PackedBuffer_t *InputBuffer)\n')
   c_file.write('{\n')
   c_file.write('   return(ssSuccess);\n')
   c_file.write('}\n\n')

   c_file.write('Boolean_t ' + component + '_SendCommand(PackedBuffer_t *InputBuffer, PackedBuffer_t *OutputBuffer, const char *Function)\n')
   c_file.write('{\n')
   c_file.write('   uint32_t           FileIndex;\n')
   c_file.write('   uint32_t           FunctionIndex;\n')
   c_file.write('   uint32_t           FunctionID;\n')
   c_file.write('   FileEntry_t       *FileListPtr;\n')
   c_file.write('   unsigned int       NumFileEntries = 0;\n')
   c_file.write('   PackedBuffer_t     InputCommandBuffer;\n')
   c_file.write('   uint16_t           FunctionCount;\n')
   c_file.write('   FunctionHandler_t *FunctionList;\n\n')

   c_file.write('   /* Verify the input command.                                         */\n')
   c_file.write('   if(InputBuffer)\n')
   c_file.write('   {\n')
   c_file.write('      /* Check to see if this is the first command call.  If this is    */\n')
   c_file.write('      /* case we need to un-pack the Function ID and call the write     */\n')
   c_file.write('      /* handler.                                                       */\n')
   c_file.write('      if(' + component + '_FirstSendCommandCall)\n')
   c_file.write('      {\n')
   c_file.write('         /* Flag that this is no longer the first command call.         */\n')
   c_file.write('         ' + component + '_FirstSendCommandCall = FALSE;\n\n')

   c_file.write('         /* Save this input command.                                    */\n')
   c_file.write('         ' + component + '_FirstLength          = InputBuffer->Length;\n')
   c_file.write('         ' + component + '_FirstStart           = InputBuffer->Start;\n\n')

   c_file.write('         /* Initialize the packed buffer.                               */\n')
   c_file.write('         InitializePackedBuffer(&InputCommandBuffer, InputBuffer->Start, InputBuffer->Length);\n\n')

   c_file.write('         /* Un-pack the function ID from the buffer.                    */\n')
   c_file.write('         if(PackedRead_32(&InputCommandBuffer, NULL, &FunctionID) == ssSuccess)\n')
   c_file.write('         {\n')
   c_file.write('            /* Get the file and function index from the function ID.    */\n')
   c_file.write('            FileIndex     = FUNCTION_ID_GET_FILE_INDEX(FunctionID);\n')
   c_file.write('            FunctionIndex = FUNCTION_ID_GET_FUNCTION_INDEX(FunctionID);\n\n')

   c_file.write('            /* Get the function handler list.                           */\n')
   c_file.write('            FileListPtr = GetFileEntryArray(&NumFileEntries);\n')
   c_file.write('            if((FileListPtr) && (NumFileEntries > 0) && (FileIndex < NumFileEntries))\n')
   c_file.write('            {\n')
   c_file.write('               /* Get the function list and count.                      */\n')
   c_file.write('               FunctionList  = FileListPtr[FileIndex].FunctionList;\n')
   c_file.write('               FunctionCount = FileListPtr[FileIndex].FunctionCount;\n\n')

   c_file.write('               /* Call the handler if the Function Index is in bounds.  */\n')
   c_file.write('               if((FunctionList) && (FunctionCount > 0) && (FunctionIndex < FunctionCount))\n')
   c_file.write('                  (*FunctionList[FunctionIndex])(InputCommandBuffer.CurrentPos, InputCommandBuffer.Remaining);\n')
   c_file.write('            }\n')
   c_file.write('         }\n')
   c_file.write('      }\n')
   c_file.write('      else\n')
   c_file.write('      {\n')
   c_file.write('         /* Initialize command success to false.                        */\n')
   c_file.write('         ' + component + '_CommandSuccess = FALSE;\n\n')

   c_file.write('         /* Verify the packed input command against what was originally */\n')
   c_file.write('         /* packed (with memcpy) to verify the packing/un-packing.      */\n')
   c_file.write('         if(InputBuffer->Length == ' + component + '_FirstLength)\n')
   c_file.write('         {\n')
   c_file.write('            /* Do a byte-by-byte comparison.                            */\n')
   c_file.write('            if(!memcmp(InputBuffer->Start, ' + component + '_FirstStart, InputBuffer->Length))\n')
   c_file.write('            {\n')
   c_file.write('               ' + component + '_CommandSuccess = TRUE;\n')
   c_file.write('               OSAL_OutputMessage("%s Success Iteration %u\\n", Function, ' + component + '_CommandIteration);\n')
   c_file.write('            }\n')
   c_file.write('            else\n')
   c_file.write('            {\n')
   c_file.write('               OSAL_OutputMessage("%s Failure Iteration %u: Packed Command Buffers do not match!\\n", Function, ' + component + '_CommandIteration);\n')
   c_file.write('            }\n')
   c_file.write('         }\n')
   c_file.write('         else\n')
   c_file.write('         {\n')
   c_file.write('            OSAL_OutputMessage("%s Failure Iteration %u: Command Lengths do not match!\\n", Function, ' + component + '_CommandIteration);\n')
   c_file.write('         }\n')

   # Function
   c_file.write('      }\n')
   c_file.write('   }\n\n')

   c_file.write('   /* Always return FALSE.                                              */\n')
   c_file.write('   return(FALSE);\n')
   c_file.write('}\n\n')

   c_file.write('#define SendCommand(_a, _b) ' + component + '_SendCommand(_a, _b __func__)\n\n')

   # Add Send Command

   c_file.write('/* C file includes. */\n')

   return c_file

def WriteTestFileHeader(FileHandle, component):
   FileHandle.write('\n')
   FileHandle.write('unsigned int Test' + component.upper() + '(void)\n')
   FileHandle.write('{\n')
   FileHandle.write('    unsigned int FailureCount = 0;\n\n')

def CloseTestFile(c_file):
   c_file.write('    return(FailureCount);\n');
   c_file.write('}\n')
   c_file.close()


def Begin():
   global struct_init_c_file
   global struct_init_h_file
   global struct_init_m_c_file
   global struct_init_m_h_file
   random.seed()

   # Open a utility function for initializing structures
   struct_init_c_file, struct_init_h_file, struct_init_m_c_file, struct_init_m_h_file = CreateStructureFiles()

   # Add Includes to FileList array for all components
   for component in qsgCommon.qapiComponents:
      xml_list = getComponentXMLFiles(component)

      ComponentTestFile = CreateTestFile(component)

      # Skip the Zigbee component header, will be written in the for loop below.
      if component <> 'zb':
         struct_init_h_file.write('#include "qapi_' + component + '.h"\n')
         if qsgCommon.generateManual:
            struct_init_m_h_file.write('#include "qapi_' + component + '.h"\n')

      # Add includes to file list
      for xml_file in xml_list:
         if component == 'zb':
            struct_init_h_file.write('#include "' + xml_file.replace('.xml', '.h') + '"\n')
            if qsgCommon.generateManual:
               struct_init_m_h_file.write('#include "' + xml_file.replace('.xml', '.h') + '"\n')
         GenerateTestFileIncludes(component, xml_file, ComponentTestFile)

      WriteTestFileHeader(ComponentTestFile, component)

      # Close the component file
      ComponentTestFile.close()

      # Add Include after all of the headers in the structure random init file
#     CommonHeader = xml_file.replace('.xml', '') + '_common.h'
#     struct_init_h_file.write('#include "' + CommonHeader + '"\n')

      # Add include to structure file
      struct_init_c_file.write('#include "qapi_' + component + '.h"\n')
      if qsgCommon.generateManual:
         struct_init_m_c_file.write('#include "qapi_' + component + '.h"\n')

   # add new line
   struct_init_h_file.write('\n')
   struct_init_c_file.write('#include "random_struct_init.h"\n')
   struct_init_c_file.write('\n')
   if qsgCommon.generateManual:
      struct_init_m_h_file.write('\n')
      struct_init_m_c_file.write('#include "random_struct_init.h"\n')
      struct_init_m_c_file.write('\n')

def End():
   # Generate structures to get random values per structure
   for RootAndStructure in qsgCommon.structRootList:
      if RootAndStructure[1].get('name') in qsgCommon.manualStructList:
         GenerateRandomStructInitializerStub(struct_init_c_file, struct_init_h_file, RootAndStructure[0], RootAndStructure[1])
         if qsgCommon.generateManual:
            GenerateRandomStructInitializer(struct_init_m_c_file, struct_init_m_h_file, RootAndStructure[0], RootAndStructure[1], True)
      else:
         GenerateRandomStructInitializer(struct_init_c_file, struct_init_h_file, RootAndStructure[0], RootAndStructure[1], False)

   # Close the structure file
   CloseStructureFiles(struct_init_c_file, struct_init_h_file, struct_init_m_c_file, struct_init_m_h_file)

   for component in qsgCommon.qapiComponents:
      ComponentTestFile = open(CreateTestFileName(component), 'a')
      CloseTestFile(ComponentTestFile)

