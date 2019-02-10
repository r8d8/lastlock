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
import qsgUtils

def CreateIDListHeader():
   global IDListRoot
   IDListFile = open(os.path.join(qsgCommon.fileIdDir, 'idlist.h'), 'w+')
   IDListFile.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')
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

   IDListTree = parse(os.path.join(qsgCommon.fileIdDir, 'qapiIdList.xml'))
   IDListRoot = IDListTree.getroot()

   IDListFile.write('#ifndef __IDLIST_H__\n')
   IDListFile.write('#define __IDLIST_H__\n')
   IDListFile.write('\n')

   for module in IDListRoot.findall('module'):
      # Write the module ID
      IDListFile.write('/* ID for ' + module.get('name') + ' component. */\n')
      IDListFile.write('#define MODULE_' + module.get('name') .upper())
      # Pad spaces
      for index in range(len(module.get('name') ), 84):
         IDListFile.write(' ')
      IDListFile.write(' (' + module.get('id') + ')\n\n')

      for file in module.findall('file'):
         # Write the file ID
         IDListFile.write('#define ' + file.get('name').upper() + '_FILE_ID')
         # Pad spaces
         for index in range(len(file.get('name').upper()), 83):
            IDListFile.write(' ')
         IDListFile.write(' (' + file.get('id') + ')\n\n')

         for function in file.findall('function'):
            # Write the function ID
            IDListFile.write('#define ' + function.get('name').upper() + '_FUNCTION_ID')
            # Pad spaces
            for index in range(len(function.get('name').upper()), 79):
               IDListFile.write(' ')
            IDListFile.write(' (' + function.get('id') + ')\n')

         for callback in file.findall('callback'):
            # Write the callback ID
            IDListFile.write('#define ' + callback.get('name').upper() + '_CALLBACK_ID')
            # Pad spaces
            for index in range(len(callback.get('name').upper()), 79):
               IDListFile.write(' ')
            IDListFile.write(' (' + callback.get('id') + ')\n')

         if len(file.findall('function')) <> 0 and len(file.findall('callback')) <> 0:
            IDListFile.write('\n')

   IDListFile.write('#endif /* __IDLIST_H__ */\n')
   IDListFile.close()

def AddGeneratedCode(xmlFile, component):
   # Get the XML file root.
   fileTree = parse(qsgCommon.xmlDir + xmlFile)
   fileRoot = fileTree.getroot()

   # Loop through the xmlFile and ID list XML ot find
   # which functions in the ID list XML are actually used
   for module in IDListRoot.findall('module'):
      if component == module.get('name'):
         for file in module.findall('file'):
            if xmlFile.replace('.xml','') == file.get('name'):
               for fileFunction in fileRoot.findall('function'):
                  for function in file.findall('function'):
                     if fileFunction.get('name') == function.get('name'):
                        # Set the function to 'used' in the ID list XML.
                        function.set('used', 'true')
                        file.set('used', 'true')
                        break
               break
         break

def Begin():
   global FileListFile
   global CurrentComponent
   CurrentComponent = ''
   # Make the filelist.h file to hold all of the
   # function arrays
   FileListFile = open(os.path.join(qsgCommon.fileIdDir, 'filelist.h'), 'w+')
   FileListFile.write('/*\n * Copyright (c) 2018 Qualcomm Technologies, Inc.\n * All Rights Reserved.\n')
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
   
   CreateIDListHeader()

   WriteFileListHeader()

   # Add Includes to FileList array for all components
   for component in qsgCommon.qapiComponents:
      xml_list = getComponentXMLFiles(component)
      FileListFile.write('#ifdef ENABLE_MODULE_' + component.upper() + '\n')
      # Add includes to file list
      for xml_file in xml_list:
         GenerateFileListIncludes(xml_file)
      FileListFile.write('#endif // ENABLE_MODULE_' + component.upper() + '\n')

   WriteFileListArrayHeader()

def End():


   for module in IDListRoot.findall('module'):
      FileListFile.write('#ifdef ENABLE_MODULE_' + module.get('name').upper() + '\n')
      for file in module.findall('file'):
         if file.get('used') is not None and file.get('used') == 'true':
            FileListFile.write('   { ' + file.get('name') + '_funclist, ' + file.get('name').upper() + '_FUNC_LIST_SIZE, 0 },')
            FileListFile.write(' /* File list for file ID ' + file.get('id') + ' */\n')
         else:
            FileListFile.write('   { NULL, 0, 0 },')
            FileListFile.write(' /* File list for file ID ' + file.get('id') + ' */\n')
         file.set('used', 'true')
      FileListFile.write('#else\n')
      for file in module.findall('file'):
         FileListFile.write('   { NULL, 0, 0 },')
         FileListFile.write(' /* File list for file ID ' + file.get('id') + ' */\n')
         file.set('used', 'true')
      FileListFile.write('#endif // ENABLE_MODULE_' + module.get('name').upper() + '\n')

   # Add this array to the FileList file

   WriteFileListFooter()
   FileListFile.close()

def CreateFunctionListFile(xmlFile, component, fileRoot):
   FuncListListFileName = xmlFile.replace('.xml', '') + '_func'
   FuncListFile = FuncListListFileName + '.h'

   c_file = open(os.path.join(qsgCommon.qapiDir, 'qz', 'include', FuncListFile), 'w+')
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
   
   c_file.write('#ifndef __' + (FuncListListFileName + '_h__').upper() + '\n')
   c_file.write('#define __' + (FuncListListFileName + '_h__').upper() + '\n')

   c_file.write('\n#include <stdint.h>\n')
   c_file.write('#include "qsCommon.h"\n\n')
   # Add extern prototypes for all the functions
   for module in IDListRoot.findall('module'):
      if component == module.get('name'):
         for file in module.findall('file'):
            if xmlFile.replace('.xml','') == file.get('name'):
               # Write the function prototype
               for fileFunction in fileRoot.findall('function'):
                  for function in file.findall('function'):
                     if fileFunction.get('name') == function.get('name'):
                        c_file.write('SerStatus_t Handle_' + fileFunction.get('name') + '(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId);\n')
                        break

               c_file.write('\n')

               # Add functions to function list
               FuncListArray = FuncListListFileName + 'list'
               c_file.write('FunctionHandler_t ' + FuncListArray + '[] =\n')
               c_file.write('{\n')

               # Add function table entries
               for function in file.findall('function'):
                  foundFunction = False

                  for fileFunction in fileRoot.findall('function'):
                     if fileFunction.get('name') == function.get('name'):
                        c_file.write('   Handle_' + function.get('name'))
                        c_file.write(', /* Function Index = ' + function.get('id') + ' */\n')
                        foundFunction = True
                        break

                  # Write a NULL entry if the function is blacklisted. */
                  if not foundFunction:
                     c_file.write('   NULL')
                     c_file.write(', /* Function Index = ' + function.get('id') + ' */\n')

               c_file.write('\n};\n\n')

               # Add the list size #define QAPI_BLE_BSC_FUNC_LIST_SIZE    (sizeof(qapi_ble_bsc_FuncList) / sizeof(FunctionHandler_t))
               FuncListArraySize = (FuncListListFileName + '_list_size').upper()
               c_file.write('#define ' + FuncListArraySize + '   (sizeof(' + FuncListArray + ') / sizeof(FunctionHandler_t))\n')

               c_file.write('\n#endif // __' + (FuncListListFileName + '_h__').upper() + '\n')

               c_file.close()
         break

def GenerateFileListIncludes(xmlFile):
   # Parse the XML input and get the root
   tree = parse(os.path.join(qsgCommon.qapiDir, 'xml', xmlFile))
   root = tree.getroot()

   if len(root.findall('function')) != 0:
      IncludeFileName = xmlFile.replace('.xml', '') + '_func.h'
      FileListFile.write('#include "' + IncludeFileName + '"\n')

def WriteFileListHeader():
   FileListFile.write('#ifndef __FILELIST_H__\n')
   FileListFile.write('#define __FILELIST_H__\n')
   FileListFile.write('\n')
   FileListFile.write('#include "qsQuartz.h"\n')

def WriteFileListArrayHeader():
   FileListFile.write('\nFileEntry_t FileList[] =\n')
   FileListFile.write('{\n')

def WriteFileListFooter():
   FileListFile.write('\n};\n\n')
   FileListFile.write('#define FILE_LIST_SIZE   (sizeof(FileList) / sizeof(FileEntry_t))\n\n')
   FileListFile.write('#endif /* __FILELIST_H__ */\n')
