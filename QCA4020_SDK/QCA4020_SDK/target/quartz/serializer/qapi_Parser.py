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

GLOBAL_ENUM_LIST = []

def IsDecimal(type):
   RetVal = False

   if 'int8' in type:
      RetVal = True
   elif 'int16' in type:
      RetVal = True
   elif 'int32' in type:
      RetVal = True
   elif 'int64' in type:
      RetVal = True
   elif type == 'int' or type == 'unsigned int' or type == 'signed int':
      RetVal = True
   elif type == 'char' or type == 'unsigned char' or type == 'signed char':
      RetVal = True
   elif type == 'long' or type == 'unsigned long' or type == 'signed long':
      RetVal = True
   elif type == 'qapi_BLE_NonAlignedByte_t' or type == 'qapi_BLE_NonAlignedSByte_t':
      RetVal = True
   elif type == 'qapi_BLE_NonAlignedWord_t' or type == 'qapi_BLE_NonAlignedSWord_t':
      RetVal = True
   elif type == 'qapi_BLE_NonAlignedDWord_t' or type == 'qapi_BLE_NonAlignedSDWord_t':
      RetVal = True
   elif type == 'qapi_BLE_NonAlignedQWord_t' or type == 'qapi_BLE_NonAlignedSQWord_t':
      RetVal = True

   return RetVal

class Parser_Configuration:
   def __init__(self, QAPI_dir):
      self.QAPI_dir = QAPI_dir
      self.modules = []
      self.excludedHeaderList = []
      self.excludedFunctionList = []
      self.excludedStructureList = []
      self.xml_dir = ''
      self.fileID_dir = ''
      self.c_dir = ''

   def headerDir(self):
      return self.QAPI_dir

   def setXMLdir(self, xml_dir):
      self.xml_dir = xml_dir

   def getXMLdir(self):
      return self.xml_dir

   def setFileIDdir(self, fileID_dir):
      self.fileID_dir = fileID_dir

   def getFileIDdir(self):
      return self.fileID_dir

   def setCdir(self, c_dir):
      self.c_dir = c_dir

   def getCdir(self):
      return self.c_dir

   def addModule(self, module):
      self.modules.append(module)

   def addExcludedHeader(self, header):
      self.excludedHeaderList.append(header)

   def addExcludedFunction(self, function):
      self.excludedFunctionList.append(function)

   def addExcludedStructure(self, structure):
      self.excludedStructureList.append(structure)

   def getModules(self):
      return self.modules

   def isHeaderAllowed(self, header):
      retVal = True

      if header in self.excludedHeaderList:
         retVal = False

      return retVal

   def isFunctionAllowed(self, function):
      retVal = True

      if function in self.excludedFunctionList:
         retVal = False

      return retVal

   def isStructureAllowed(self, structure):
      retVal = True

      if structure in self.excludedStructureList:
         retVal = False

      return retVal

class QAPI_Header:

   def __init__(self, file_name):
      self.file_name = file_name
      self.xml_name = file_name.replace('.h', '.xml')

   # Removes BLE API definitions
   # Also removes multiple spaces which simplifies parsing later
   def stripAPIDefs(self, text):
      # Remove BLE API declarations.
      re_replace_comments = re.compile('QAPI_BLE_DECLARATION')
      text = re_replace_comments.sub('', text)
      re_replace_comments = re.compile('QAPI_BLE_BTPSAPI')
      text = re_replace_comments.sub('', text)
      re_replace_comments = re.compile('__QAPI_BLE_PACKED_STRUCT_BEGIN__')
      text = re_replace_comments.sub('', text)
      re_replace_comments = re.compile('__QAPI_BLE_PACKED_STRUCT_END__')
      text = re_replace_comments.sub('', text)
      re_replace_comments = re.compile('[^\S\n]+')
      text = re_replace_comments.sub(' ', text)
      return text

   # Removes inline and multiline comments
   # Also removes multiple spaces which simplifies parsing later
   def stripComments(self, text):
      re_replace_comments = re.compile('/\*.*?\*/', flags = re.DOTALL)
      text = re_replace_comments.sub('', text)
      re_replace_comments = re.compile('//.*')
      text = re_replace_comments.sub('', text)
      re_replace_comments = re.compile('[^\S\n]+')
      text = re_replace_comments.sub(' ', text)
      return text

   # Removes newlines and multiple spaces
   def stripNewLines(self, text):
      re_replace_comments = re.compile('\r\n', flags = re.DOTALL)
      text = re_replace_comments.sub(' ', text)
      re_replace_comments = re.compile('\n', flags = re.DOTALL)
      text = re_replace_comments.sub(' ', text)
      re_replace_comments = re.compile('\s+')
      text = re_replace_comments.sub(' ', text)
      return text

   # Adds each argument to the parent function element, giving the argument
   # element a name, type, and any attributes (pointer, const)
   def parseFunctionArguments(self, contents, parentElement):
      contents = contents.strip()
      # No processing needed for void functions
      if contents <> 'void':
         argStrs = contents.split(',')
         # Walk through each argument
         for argStr in argStrs:
            argStr = argStr.strip()
            if '**' in argStr:
               if 'const ' in argStr:
                  # Handle const double pointers
                  argStr = argStr.split('const ')[1]
                  argElement = SubElement(parentElement, 'argument',
                     {'name':argStr.split('**')[-1],
                      'type':argStr.replace(' **' + argStr.split('**')[-1],''),
                      'attributes':'doubleptr,const',
                     })
               else:
                  # Handle double pointers
                  argElement = SubElement(parentElement, 'argument',
                     {'name':argStr.split('**')[-1],
                      'type':argStr.replace(' **' + argStr.split('**')[-1],''),
                      'attributes':'doubleptr',
                     })
            elif '*' in argStr:
               if 'const ' in argStr:
                  # Handle const pointers
                  argStr = argStr.split('const ')[1]
                  argElement = SubElement(parentElement, 'argument',
                     {'name':argStr.split('*')[-1],
                      'type':argStr.replace(' *' + argStr.split('*')[-1],''),
                      'attributes':'ptr,const',
                     })
               else:
                  # Handle pointers
                  argElement = SubElement(parentElement, 'argument',
                     {'name':argStr.split('*')[-1],
                      'type':argStr.replace(' *' + argStr.split('*')[-1],''),
                      'attributes':'ptr',
                     })
            elif "[]" in argStr:
               # Handle arrays
               argStr = argStr.replace('[]','')
               argStr = SubElement(parentElement, 'argument',
                  {'name':argStr.split(' ')[-1],
                   'type':argStr.replace(' ' + argStr.split(' ')[-1],''),
                   'attributes':'ptr',
                  })
            else:
               if 'const ' in argStr:
                  # Handle const value
                  argStr = argStr.split('const ')[1]
                  argElement = SubElement(parentElement, 'argument',
                     {'name':argStr.split(' ')[-1],
                      'type':argStr.replace(' ' + argStr.split(' ')[-1],''),
                      'attributes':'value,const',
                     })
               else:
                  # Handle values
                  argElement = SubElement(parentElement, 'argument',
                     {'name':argStr.split(' ')[-1],
                      'type':argStr.replace(' ' + argStr.split(' ')[-1],''),
                      'attributes':'value',
                     })

   # Adds the return value to the parent function element
   def parseFunctionRetval(self, contents, parentElement):
      contents = contents.strip()
      if '**' in contents:
         if 'const ' in contents:
            # Handle const double pointers
            contents = contents.split('const ')[1]
            contents = contents.replace(' ', '')
            retValElement = SubElement(parentElement, 'return',
               {'type':contents.split('**')[0],
                'attributes':'doubleptr,const',
               })
         else:
            # Handle double pointers
            contents = contents.replace(' ', '')
            retValElement = SubElement(parentElement, 'return',
               {'type':contents.split('**')[0],
                'attributes':'doubleptr',
               })
      elif '*' in contents:
         if 'const ' in contents:
            # Handle const pointers
            contents = contents.split('const ')[1]
            contents = contents.replace(' ', '')
            retValElement = SubElement(parentElement, 'return',
               {'type':contents.split('*')[0],
                'attributes':'ptr,const',
               })
         else:
            # Handle pointers
            contents = contents.replace(' ', '')
            retValElement = SubElement(parentElement, 'return',
               {'type':contents.split('*')[0],
                'attributes':'ptr',
               })
      else:
         # Handle values
         retValElement = SubElement(parentElement, 'return',
            {'type':contents,
             'attributes':'value',
            })

   # Guesses the argument for pointer size within a function.
   # Uses weighting based on potential size arg name, pointer arg name,
   # and arg proximity to determine the best fit parameter.
   def guessFunctionArgumentSizes(self, functionElement):
      for childIndex, child in enumerate(functionElement):
         if child.tag == 'argument' and 'ptr' in child.get('attributes'):
            maxConfidence = 0
            bestFitName = ''
            if 'char' in child.get('type'):
               # If this is a char ptr, start with a low-scoring assumption it is a string
               maxConfidence = 2
               bestFitName = '__strlen__'
            for otherChildIndex, otherChild in enumerate(functionElement):
               # Check that the other parameter is unique and a decimal
               if child <> otherChild and otherChild.tag == 'argument' and otherChild.get('type') is not None and IsDecimal(otherChild.get('type')):
                  currentConfidence = 0
                  if 'size' in otherChild.get('name').lower():
                     currentConfidence = currentConfidence + 1
                  if 'len' in otherChild.get('name').lower():
                     currentConfidence = currentConfidence + 1
                  if 'num' in otherChild.get('name').lower():
                     currentConfidence = currentConfidence + 1
                  if 'count' in otherChild.get('name').lower():
                     currentConfidence = currentConfidence + 1
                  if child.get('name') in otherChild.get('name') and currentConfidence > 0:
                     currentConfidence = currentConfidence + 2
                  if abs(otherChildIndex - childIndex) == 1 and currentConfidence > 0:
                     currentConfidence = currentConfidence + 1
                  if 'value' in otherChild.get('attributes') and currentConfidence > 0:
                     currentConfidence = currentConfidence + 1

                  if currentConfidence > maxConfidence:
                     maxConfidence = currentConfidence
                     bestFitName = otherChild.get('name')

            if len(bestFitName) > 0:
               useLengthParam = True
               for otherChild in functionElement:
                  if child <> otherChild and otherChild.get('lengthParam') == bestFitName:
                     if int(otherChild.get('lengthConfidence')) > maxConfidence:
                        useLengthParam = False
                     if int(otherChild.get('lengthConfidence')) < maxConfidence:
                        otherChild.set('lengthParam', '1')
                        otherChild.set('lengthVerified', 'no')
                        otherChild.set('lengthConfidence', 'NA')
               if useLengthParam:
                  child.set('lengthParam', bestFitName)
                  child.set('lengthVerified', 'no')
                  child.set('lengthConfidence', str(maxConfidence))
               else:
                  child.set('lengthParam', '1')
                  child.set('lengthVerified', 'no')
                  child.set('lengthConfidence', 'NA')
            else:
               child.set('lengthParam', '1')
               child.set('lengthVerified', 'no')
               child.set('lengthConfidence', 'NA')
      for child in functionElement:
         # Remove the length confidence parameters from final output.
         if child.get('lengthConfidence') is not None:
            del child.attrib['lengthConfidence']

   # Guesses register/unregister functions and parameters for a callback type.
   def guessCallbackInformation(self, headerElement, callbackElement, module):
      # Find init functions.
      for function in headerElement.findall('function'):
         initFunc = False
         ID = '__return__'
         cbParam = ''
         funcSuccess = ''
         moduleParam = ''
         # Init function will include the callback type as a parameter.
         for arg in function.findall('argument'):
            if arg.get('type') == callbackElement.get('name'):
               initFunc = True
         if initFunc:
            # Get the return type and guess the success value by type`.
            if len(function.findall('return')) > 0:
               retVal = function.findall('return')[0]
               if retVal.get('type') == 'int':
                  funcSuccess = '0'
               elif retVal.get('type') == 'qapi_Status_t':
                  funcSuccess = 'QAPI_OK'
            if module == 'ble':
               for arg in function.findall('argument'):
                  # Find BLE callback IDs and callback params
                  if ('CallbackID' in arg.get('name') or 'ServiceID' in arg.get('name') or 'InstanceID' in arg.get('name')) and not 'Bluetooth' in arg.get('name'):
                     ID = arg.get('name')
                  if 'param' in arg.get('name').lower():
                     cbParam = arg.get('name')
                  if 'BluetoothStackID' == arg.get('name'):
                     moduleParam = arg.get('name')
                  if ID <> '' and ID <> '__return__' and cbParam <> '':
                     break
            elif module == 'zb':
               # Find Zigbee callback IDs and callback params
               for arg in function.findall('argument'):
                  if arg.get('name') == 'Cluster':
                     ID = arg.get('name')
                  if 'param' in arg.get('name').lower():
                     cbParam = arg.get('name')
                  if ID <> '' and ID <> '__return__'  and cbParam <> '':
                     break
            else:
               # Find all other callback IDs and callback params
               for arg in function.findall('argument'):
                  if ('ID' in arg.get('name') and not 'Bluetooth' in arg.get('name')) or arg.get('name') == 'Cluster':
                     ID = arg.get('name')
                  if 'param' in arg.get('name').lower():
                     cbParam = arg.get('name')
                  if ID <> '' and ID <> '__return__'  and cbParam <> '':
                     break
            # If the callback ID was not found, it is likely that it is the return value,
            # use that as the return and make the function success parameter be a positive integer.
            if ID == '__return__':
               funcSuccess = '__positive__'
            # Write the function and parameters to XML.
            createFunction = SubElement(callbackElement, 'createFunction',
               {'name'       :function.get('name'),
                'ID'         :ID,
                'param'      :cbParam,
                'moduleParam':moduleParam,
                'funcSuccess':funcSuccess,
               })
      # Find deinit functions.
      for function in headerElement.findall('function'):
         deInitFunc = False
         funcSuccess = ''
         # Look for common cleanup/deinit function names.
         if 'cleanup' in function.get('name').lower() or ('deinit') in function.get('name').lower() or ('unregister') in function.get('name').lower() or ('un_register') in function.get('name').lower():
            # Guess the success value by return type.
            if len(function.findall('return')) > 0:
               retVal = function.findall('return')[0]
               if retVal.get('type') == 'int':
                  funcSuccess = '0'
               elif retVal.get('type') == 'qapi_Status_t':
                  funcSuccess = 'QAPI_OK'
            # Loop through the arguments and find one that might match
            # a callback ID.
            for arg in function.findall('argument'):
               # Just look for the string 'ID' within the arguments.
               if 'ID' in arg.get('name') and not 'Bluetooth' in arg.get('name'):
                  contentsElement = SubElement(callbackElement, 'destroyFunction',
                     {'name'       :function.get('name'),
                      'ID'         :arg.get('name'),
                      'funcSuccess':funcSuccess,
                     })
                  break
      # Add module-specific shutdowns that will remove all callbacks
      # for the module or unregister functions not specific to the current header.
      if module == 'ble':
         contentsElement = SubElement(callbackElement, 'destroyFunction',
            {'name':'BSC_Shutdown',
             'ID'  :'BluetoothStackID',
            })
      elif module == 'zb':
         contentsElement = SubElement(callbackElement, 'destroyFunction',
            {'name'       :'qapi_ZB_CL_Destroy_Cluster',
             'ID'         :'Cluster',
             'funcSuccess':'QAPI_OK',
            })

   # Adds each member to the parent structure element, giving the member
   # element a name, type, and any attributes (pointer, const)
   def parseEnumMembers(self, contents, parentElement):
      GLOBAL_ENUM_LIST.append(parentElement)

   # Adds each member to the parent structure element, giving the member
   # element a name, type, and any attributes (pointer, const)
   def parseStructMembers(self, contents, parentElement):
      contents = contents.strip()
      unionStr = ''
      if contents.endswith(';'):
         members = contents[:-1].replace('; ',';').split(';')
         union = False
         for member in members:
            if 'union {' in member or union:
               # Handle unions. Once a union is found to have been declared,
               # must continue adding each member to the union until the end is found.
               # Then we recursively call with the union contents to parse those members.
               union = True
               if 'union {' in member:
                  unionStr = member[len('union {'):] + ';'
               elif '}' in member:
                  unionElement = SubElement(parentElement, 'member',
                     {'name':member.replace(' ','').split('}')[1],
                      'attributes':'union',
                     })
                  self.parseStructMembers(unionStr + '', unionElement)
                  union = False
               else:
                  unionStr = unionStr + member + ';'
            else:
               if '**' in member:
                  if 'const ' in member:
                     # Handle const double pointers
                     member = member.split('const ')[1]
                     memberElement = SubElement(parentElement, 'member',
                        {'name':member.split('**')[-1],
                         'type':member.replace(' **' + member.split('**')[-1],''),
                         'attributes':'doubleptr,const',
                        })
                  else:
                     # Handle double pointers
                     memberElement = SubElement(parentElement, 'member',
                        {'name':member.split('**')[-1],
                         'type':member.replace(' **' + member.split('**')[-1],''),
                         'attributes':'doubleptr',
                        })
               elif '*' in member:
                  if 'const ' in member:
                     # Handle const pointers
                     member = member.split('const ')[1]
                     memberElement = SubElement(parentElement, 'member',
                        {'name':member.split('*')[-1],
                         'type':member.replace(' *' + member.split('*')[-1],''),
                         'attributes':'ptr,const',
                        })
                  else:
                     # Handle pointers
                     memberElement = SubElement(parentElement, 'member',
                        {'name':member.split('*')[-1],
                         'type':member.replace(' *' + member.split('*')[-1],''),
                         'attributes':'ptr',
                        })
               elif '[' in member:
                  # Handle arrays
                  if '[]' in member in member:
                     member = member.replace('[]','')
                     if 'const ' in member:
                        # Handle const arrays with unspecified length
                        member = member.split('const ')[1]
                        memberElement = SubElement(parentElement, 'member',
                           {'name':member.split(' ')[-1],
                            'type':member.replace(' ' + member.split(' ')[-1],''),
                            'attributes':'ptr,const,bracketArray',
                            'fixedLength':'false',
                           })
                     else:
                        # Handle arrays with unspecified length
                        memberElement = SubElement(parentElement, 'member',
                           {'name':member.split(' ')[-1],
                            'type':member.replace(' ' + member.split(' ')[-1],''),
                            'attributes':'ptr,bracketArray',
                            'fixedLength':'false',
                           })
                  else:
                     arraySize = re.findall('\[([^\[\]]+)\]', member, re.DOTALL)
                     if len(arraySize) == 1:
                        member = member.replace('[' + arraySize[0] + ']','')
                        arraySize[0] = arraySize[0].replace(' ','')
                        if 'const ' in member:
                           # Handle const arrays with fixed length
                           member = member.split('const ')[1]
                           memberElement = SubElement(parentElement, 'member',
                              {'name':member.split(' ')[-1],
                               'type':member.replace(' ' + member.split(' ')[-1],''),
                               'attributes':'ptr,const,bracketArray',
                               'fixedLength':'true',
                               'lengthParam':arraySize[0],
                              })
                        else:
                           # Handle arrays with fixed length
                           memberElement = SubElement(parentElement, 'member',
                              {'name':member.split(' ')[-1],
                               'type':member.replace(' ' + member.split(' ')[-1],''),
                               'attributes':'ptr,bracketArray',
                               'fixedLength':'true',
                               'lengthParam':arraySize[0],
                              })
                     else:
                        print 'Unhandled structure member ' + member + ' in ' + parentElement.get('name')
               else:
                  if 'const ' in member:
                     # Handle const values
                     member = member.split('const ')[1]
                     memberElement = SubElement(parentElement, 'member',
                        {'name':member.split(' ')[-1],
                         'type':member.replace(' ' + member.split('*')[-1],''),
                         'attributes':'value,const',
                        })
                  else:
                     # Handle values
                     memberElement = SubElement(parentElement, 'member',
                        {'name':member.split(' ')[-1],
                         'type':member.replace(' ' + member.split(' ')[-1],''),
                         'attributes':'value',
                        })

   # Guesses the member for pointer size within a structure.
   # Uses weighting based on potential size member name, pointer member name,
   # and member proximity to determine the best fit parameter.
   def guessStructureMemberSizes(self, structElement):
      for childIndex, child in enumerate(structElement):
         if child.tag == 'member' and 'ptr' in child.get('attributes') and (child.get('fixedLength') is None or child.get('fixedLength') == 'false'):
            maxConfidence = 0
            bestFitName = ''
            if 'char' in child.get('type'):
               # If this is a char ptr, start with a low-scoring assumption it is a string
               maxConfidence = 2
               bestFitName = '__strlen__'
            for otherChildIndex, otherChild in enumerate(structElement):
               # Check that the other parameter is unique and a decimal
               if child <> otherChild and otherChild.tag == 'member' and otherChild.get('type') is not None and IsDecimal(otherChild.get('type')):
                  currentConfidence = 0
                  if 'size' in otherChild.get('name').lower():
                     currentConfidence = currentConfidence + 1
                  if 'len' in otherChild.get('name').lower():
                     currentConfidence = currentConfidence + 1
                  if 'num' in otherChild.get('name').lower():
                     currentConfidence = currentConfidence + 1
                  if 'count' in otherChild.get('name').lower():
                     currentConfidence = currentConfidence + 1
                  if child.get('name') in otherChild.get('name') and currentConfidence > 0:
                     currentConfidence = currentConfidence + 2
                  if abs(otherChildIndex - childIndex) == 1 and currentConfidence > 0:
                     currentConfidence = currentConfidence + 1
                  if 'value' in otherChild.get('attributes') and currentConfidence > 0:
                     currentConfidence = currentConfidence + 1

                  if currentConfidence > maxConfidence:
                     maxConfidence = currentConfidence
                     bestFitName = otherChild.get('name')

            if len(bestFitName) > 0:
               useLengthParam = True
               for otherChild in structElement:
                  if child <> otherChild and otherChild.get('lengthParam') == bestFitName:
                     if int(otherChild.get('lengthConfidence')) > maxConfidence:
                        useLengthParam = False
                     if int(otherChild.get('lengthConfidence')) < maxConfidence:
                        otherChild.set('lengthParam', '1')
                        otherChild.set('lengthVerified', 'no')
                        otherChild.set('lengthConfidence', 'NA')
               if useLengthParam:
                  child.set('lengthParam', bestFitName)
                  child.set('lengthVerified', 'no')
                  child.set('lengthConfidence', str(maxConfidence))
               else:
                  child.set('lengthParam', '1')
                  child.set('lengthVerified', 'no')
                  child.set('lengthConfidence', 'NA')
            else:
               child.set('lengthParam', '1')
               child.set('lengthVerified', 'no')
               child.set('lengthConfidence', 'NA')
      for child in structElement:
         # Remove the length confidence parameters from final output.
         if child.get('lengthConfidence') is not None:
            del child.attrib['lengthConfidence']

   # Guesses mapping of structure unions. Finds an enum with at least as many
   # members as the union within the structure and creates a mapping if it
   # exists.
   def guessStructureUnionMapping(self, headerElement, structElement):
      for childIndex, child in enumerate(structElement):
         if child.tag == 'member' and 'union' in child.get('attributes'):
            foundMapping = False
            for otherChildIndex, otherChild in enumerate(structElement):
               # Check that the other parameter is unique
               if child <> otherChild and otherChild.tag == 'member':
                  for enum in headerElement.findall('.//enum'):
                     # Search local enum types first.
                     if enum.get('name') == otherChild.get('type'):
                        if len(enum) >= len(child):
                           mappingElement = SubElement(child, 'unionMap',
                              {'type':otherChild.get('type'),
                               'name':otherChild.get('name'),
                               'mapVerified':'no',
                              })
                           if child.get('type') == 'qapi_ZB_Addr_t' and enum.get('name') == 'qapi_ZB_Addr_Mode_t':
                              # Handle Zigbee addresses directly
                              mapElement = SubElement(mappingElement, 'mapEntry',
                                 {'value':'QAPI_ZB_ADDRESS_MODE_GROUP_ADDRESS_E',
                                  'member':child[0].get('name'),
                                  'type':child[0].get('type'),
                                 })
                              mapElement = SubElement(mappingElement, 'mapEntry',
                                 {'value':'QAPI_ZB_ADDRESS_MODE_SHORT_ADDRESS_E',
                                  'member':child[0].get('name'),
                                  'type':child[0].get('type'),
                                 })
                              mapElement = SubElement(mappingElement, 'mapEntry',
                                 {'value':'QAPI_ZB_ADDRESS_MODE_EXTENDED_ADDRESS_E',
                                  'member':child[1].get('name'),
                                  'type':child[1].get('type'),
                                 })
                           else:
                              for index in range(0, len(child)-1):
                                 mapElement = SubElement(mappingElement, 'mapEntry',
                                    {'value':enum[index].get('name'),
                                     'member':child[index].get('name'),
                                     'type':child[index].get('type'),
                                    })
                           foundMapping = True
                           break
                  for enum in GLOBAL_ENUM_LIST:
                     # Search the global enum types if a local match was not found.
                     if not foundMapping and enum.get('name') == otherChild.get('type'):
                        if len(enum) >= len(child):
                           mappingElement = SubElement(child, 'unionMap',
                              {'type':otherChild.get('type'),
                               'name':otherChild.get('name'),
                               'mapVerified':'no',
                              })
                           if child.get('type') == 'qapi_ZB_Addr_t' and enum.get('name') == 'qapi_ZB_Addr_Mode_t':
                              # Handle Zigbee addresses directly
                              mapElement = SubElement(mappingElement, 'mapEntry',
                                 {'value':'QAPI_ZB_ADDRESS_MODE_GROUP_ADDRESS_E',
                                  'member':child[0].get('name'),
                                  'type':child[0].get('type'),
                                 })
                              mapElement = SubElement(mappingElement, 'mapEntry',
                                 {'value':'QAPI_ZB_ADDRESS_MODE_SHORT_ADDRESS_E',
                                  'member':child[0].get('name'),
                                  'type':child[0].get('type'),
                                 })
                              mapElement = SubElement(mappingElement, 'mapEntry',
                                 {'value':'QAPI_ZB_ADDRESS_MODE_EXTENDED_ADDRESS_E',
                                  'member':child[1].get('name'),
                                  'type':child[1].get('type'),
                                 })
                           else:
                              for index in range(0, len(child)-1):
                                 mapElement = SubElement(mappingElement, 'mapEntry',
                                    {'value':enum[index].get('name'),
                                     'member':child[index].get('name'),
                                     'type':child[index].get('type'),
                                    })
                           foundMapping = True
                           break
               if foundMapping:
                  break
            # If a mapping could not be found, insert an empty map with the union members
            # and their types.
            if not foundMapping:
               mappingElement = SubElement(child, 'unionMap',
                  {'mapVerified':'no',
                  })
               for index in range(0, len(child)-1):
                  mapElement = SubElement(mappingElement, 'mapEntry',
                     {'value':'',
                      'member':child[index].get('name'),
                      'type':child[index].get('type'),
                     })

   def parseHeader(self, config, module, fileElement):
      # Open the header file and create an output
      header_file = open(os.path.join(config.headerDir(), self.file_name), 'r')
      xml_file = open(os.path.join(config.getXMLdir(), self.xml_name), 'w+')

      # Create the header element
      headerElement = Element('header')

      # Read in the file and remove comments before parsing the contents
      hdr = header_file.read()

      # Remove BLE API definitions and keep a copy of this for comment parsing
      commentedHdr = self.stripAPIDefs(hdr)

      # Remove comments for simpler parsing when comments are not needed
      hdr = self.stripComments(commentedHdr)
      commentedHdr = self.stripNewLines(commentedHdr)

      # Get all includes and walk through them
      includeMatch = re.findall('#include\s*([^\s]+)', hdr, re.DOTALL)
      for fileName in includeMatch:
         fileName = fileName.replace('"','')
         # Add a new element for this header and parse the include
         includeElement = SubElement(headerElement, 'include',
            {'name':fileName
            })


      # Get all macros and walk through them
      macroMatch = re.findall('(?:(?:#define\s+(?P<name0>[^\s]+)(?P<params0>(?:\([^\)]+\)))\s*(?P<value0>(?:[^\r\n\\\\]+)|(?:(?:\\\\[\s\r\n]+[^\r\n\\\\]+)*)))|(?:#define\s+(?P<name1>[^\s]+)\s*(?P<value1>(?:[^\r\n\\\\]+)|(?:(?:\\\\[\s\r\n]+[^\r\n\\\\]+)*))))', hdr)
      for name0, params0, value0, name1, value1 in macroMatch:
         if (len(name0) > 0) and ('_H__' not in name0) and (len(params0) > 0) and (len(value0) > 0):
            # Add a new element for this header and parse the macro
            macroElement = SubElement(headerElement, 'macro',
               {'name':name0,
                'params':params0,
                'value':value0
            })
         if (len(name1) > 0) and ('_H__' not in name1) and (len(value1) > 0):
            # Add a new element for this header and parse the macro
            macroElement = SubElement(headerElement, 'macro',
               {'name':name1,
                'value':value1
            })

      # Strip all the new lines since we no longer need them after parsing macros
      hdr = self.stripNewLines(hdr)

      # Get all enums and walk through them
      enumMatch = re.findall('typedef\s*enum\s*[^\{;]*\s*\{(.*?)\}\s*([qapi_|QAPI_][^;]+);', hdr, re.DOTALL)
      for contents, name in enumMatch:
         # Add a new element for this header and parse the enum
         enumElement = SubElement(headerElement, 'enum',
            {'name':name
            })
         self.parseEnumMembers(contents, enumElement)

      # Get all structures and walk through them
      structMatch = re.findall('typedef\s*struct\s*[^\{;]*\s*\{(.*?)\}\s*(qapi[^;]+);', hdr, re.DOTALL)
      for contents, name in structMatch:
         if config.isStructureAllowed(name):
            # Add a new element for this header and parse the struct
            structureElement = SubElement(headerElement, 'structure',
               {'name':name
               })
            self.parseStructMembers(contents, structureElement)

            # Flag each pointer in the callback type as an output pointer.
            for childIndex, child in enumerate(structureElement):
               if child.tag == 'member' and child.get('type') == 'qapi_ZB_Addr_t':
                  child.attrib['attributes'] = 'union'
                  unionMember = SubElement(child, 'member',
                     {'name':'ShortAddress',
                      'attributes':'value',
                      'type':'uint16_t',
                     })
                  unionMember = SubElement(child, 'member',
                     {'name':'ExtendedAddress',
                      'attributes':'value',
                      'type':'uint64_t',
                     })
               if child.tag == 'member' and 'ptr' in child.get('attributes'):
                  child.set('iotype', 'in')
               if child.tag == 'member' and 'union' in child.get('attributes'):
                  for unionChild in child:
                     if unionChild.tag == 'member' and 'ptr' in unionChild.get('attributes'):
                        unionChild.set('iotype', 'in')

            # Guess at which structure members indicate pointer sizes
            self.guessStructureMemberSizes(structureElement)

            # Guess at union mapping
            self.guessStructureUnionMapping(headerElement, structureElement)
         else:
            print 'Excluding structure ' + name + '...'

      # Get all unions and walk through them
      unionMatch = re.findall('typedef\s*union\s*[^\{;]*\s*\{(.*?)\}\s*(qapi[^;]+);', hdr, re.DOTALL)
      for contents, name in unionMatch:
         # Add a new element for this header and parse the union
         unionElement = SubElement(headerElement, 'union',
            {'name':name
            })
         self.parseStructMembers(contents, unionElement)

      # Get all functions and walk through them
      funcMatch = re.findall('(((?:const\s*)*(?:unsigned\s*|signed\s*)*[^\s;]+\s*\**\s*)(qapi_[^\s]*)\s*\(([^;]+)\)\s*;)', hdr, re.DOTALL)
      for funcStr, retVal, name, contents in funcMatch:
         # Add a new element for this header and parse the function
         if not ')' in name:
            # Add to the function ID list.
            funcListElement = SubElement(fileElement, 'function',
               {'name':name,
                'id':str(len(fileElement.findall('function'))),
               })

            if config.isFunctionAllowed(name):
               functionElement = SubElement(headerElement, 'function',
                  {'name':name
                  })
               self.parseFunctionRetval(retVal, functionElement)
               self.parseFunctionArguments(contents, functionElement)

               for childIndex, child in enumerate(functionElement):
                  if child.tag == 'argument' and 'ptr' in child.get('attributes'):
                     if funcStr in commentedHdr:
                        commentMatches = re.findall('/\*.*?\*/', commentedHdr[0:commentedHdr.index(funcStr)], re.DOTALL)
                        if len(commentMatches) > 0:
                           funcComment = commentMatches[-1]
                           inoutStr = re.findall('param\[(in|out|in,out)\]\s*' + child.get('name') + '\s+', funcComment, re.DOTALL)
                           for match in inoutStr:
                              child.set('iotype', match)
                        else:
                           print 'Error, could not parse comment for', funcStr
                     else:
                        print 'Error, could not parse comment for', funcStr

               # Guess at which function arguments indicate pointer sizes
               self.guessFunctionArgumentSizes(functionElement)

            else:
               print 'Excluding function ' + name + '...'

      # Get all callbacks and walk through them
      callbackMatch = re.findall('typedef\s+([^\s;]+\s*\**\s*)\(\s*\**\s*([^\s]+)\s*\)\s*\(([^;]+)\)\s*;', hdr, re.DOTALL)
      for retVal, name, contents in callbackMatch:
         # Add a new element for this header and parse the callback
         if not ')' in name:
            # Add to the function ID list.
            cbListElement = SubElement(fileElement, 'callback',
               {'name':name,
                'id':str(len(fileElement.findall('callback'))),
               })

            callbackElement = SubElement(headerElement, 'callback',
               {'name':name
               })
            # Callback prototypes can be parsed the same as function declarations
            self.parseFunctionRetval(retVal, callbackElement)
            self.parseFunctionArguments(contents, callbackElement)

            # Flag each pointer in the callback type as an output pointer.
            for childIndex, child in enumerate(callbackElement):
               if child.tag == 'argument' and 'ptr' in child.get('attributes'):
                  child.set('iotype', 'out')

            # Guess at which function arguments indicate pointer sizes
            self.guessFunctionArgumentSizes(callbackElement)

            # Guess at callback init/deinit functions and callback parameters.
            self.guessCallbackInformation(headerElement, callbackElement, module)

      # Write the XML output to disk after prettifying it
      xml_file.write(minidom.parseString(tostring(headerElement)).toprettyxml(indent='   '))

      header_file.close()
      xml_file.close()
      return 0

def loadConfiguration(QAPI_dir):
   retVal = False
   current_dir = os.path.dirname(os.path.abspath(__file__))
   config = Parser_Configuration(QAPI_dir)

   # Parse the input XML
   if os.path.isfile('parser_config.xml'):
      tree = parse('parser_config.xml')
      root = tree.getroot()

      # Get the XML directory configuration
      xml_dir = root.get('xmldir')
      if xml_dir is not None:
         if xml_dir[0] == '/' or xml_dir[0] == '\\':
            xml_dir = xml_dir[1:]
         xml_dir = os.path.join(current_dir, xml_dir)
         if not os.path.exists(xml_dir):
            os.makedirs(xml_dir)
         if not os.path.exists(os.path.join(current_dir, 'fileID')):
            os.makedirs(os.path.join(current_dir, 'fileID'))

         # Get the C directory configuration
         c_dir = root.get('cdir')
         if c_dir is not None:
            if c_dir[0] == '/' or c_dir[0] == '\\':
               c_dir = c_dir[1:]
            c_dir = os.path.join(current_dir, c_dir)
            # if not os.path.exists(c_dir):
               # os.makedirs(c_dir)

            fileid_dir = root.get('fileiddir')
            if fileid_dir is not None:
               if fileid_dir[0] == '/' or fileid_dir[0] == '\\':
                  fileid_dir = fileid_dir[1:]
               fileid_dir = os.path.join(current_dir, fileid_dir)
               if not os.path.exists(fileid_dir):
                  os.makedirs(fileid_dir)

               # Set the configuration directories
               config.setXMLdir(xml_dir)
               config.setFileIDdir(fileid_dir)
               config.setCdir(c_dir)

               # Add all the modules
               for module in root.findall('module'):
                 config.addModule(module.get('name'))

               # Add all the header exclusions
               for excludedHeader in root.findall('excludeHeader'):
                 config.addExcludedHeader(excludedHeader.get('name'))

               # Add all the function exclusions
               for excludedFunction in root.findall('excludeFunction'):
                 config.addExcludedFunction(excludedFunction.get('name'))

               # Add all the structure exclusions
               for excludedStructure in root.findall('excludeStructure'):
                 config.addExcludedStructure(excludedStructure.get('name'))

               retVal = True
            else:
               print 'Error, no file ID directory configured.'
         else:
            print 'Error, no C directory configured.'
      else:
         print 'Error, no XML directory configured.'
   else:
      print 'Error, configuration file does not exist.'

   return retVal, config

def getComponentHeaderFiles(config, module):
   qapi_headers = os.listdir(config.headerDir())
   header_list = []

   # Walk the list of files and components to get the header files
   for header_file in qapi_headers:
     # Match qapi_COMPONENT and .h to the file name
     if (header_file[:(len(module)+len('qapi_'))] == 'qapi_' + module) and (header_file[-2:] == '.h'):
        header_list.append(header_file)

   return header_list

def main():
   current_dir = os.path.dirname(os.path.abspath(__file__))
   QAPI_dir = ''
   FileID = 0

   if len(sys.argv) > 1:
      if os.path.exists(os.path.join(current_dir, sys.argv[1])):
         QAPI_dir = os.path.join(current_dir, sys.argv[1])

         # Load the parser configuration
         loadSuccess, config = loadConfiguration(QAPI_dir)
         if loadSuccess:
            # Create an XML file for the file list (list of all modules/functions/callbacks).
            functionListXML = open(os.path.join(config.getFileIDdir(), 'qapiIdList.xml'), 'w+')
            idList = Element('IDList')

            # Parse each module
            for module in config.getModules():
               print 'Parsing module ' + module + '...'

               # Get all the headers for the configured components
               header_list = getComponentHeaderFiles(config, module)

               # Create an element in the ID file for this module
               moduleElement = SubElement(idList, 'module',
                  {'name':module,
                   'id':str(len(idList.findall('module'))),
                  })

               # Parse each header
               for header in header_list:
                  # Create an element in the ID file for this file
                  fileElement = SubElement(moduleElement, 'file',
                     {'name':header.replace('.h',''),
                      'id':str(FileID),
                     })

                  FileID += 1

                  # Parse the header if allowed by configuration
                  if config.isHeaderAllowed(header):
                     qapiHeader = QAPI_Header(header)
                     qapiHeader.parseHeader(config, module, fileElement)
                  else:
                     print 'Excluding header ' + header + '...'

            # Write out the function list XML.
            functionListXML.write(minidom.parseString(tostring(idList)).toprettyxml(indent='   '))
            functionListXML.close()

            print 'Done.'
      else:
         print 'Error, QAPI header path does not exist'

   else:
      print 'Error, must specify the QAPI directory as an argument.'

main()
