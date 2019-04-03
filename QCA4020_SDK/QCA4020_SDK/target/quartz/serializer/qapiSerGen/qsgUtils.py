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
import random
from optparse import OptionParser
from xml.etree.ElementTree import Element, ElementTree, SubElement, Comment, tostring, parse
from xml.dom import minidom

import qsgCommon

def getComponentXMLFiles(component):
   qapi_xml = os.listdir(os.path.join(qsgCommon.qapiDir, 'xml'))
   xml_list = []

   # Walk the list of files to get the XML files
   for xml_file in qapi_xml:
      # Match qapi_COMPONENT and .xml to the file name
      if (xml_file[:(len(component)+len(qsgCommon.qapiPrefix))] == qsgCommon.qapiPrefix + component) and (xml_file[-4:] == '.xml'):
         xml_list.append(xml_file)

   return xml_list

# Determines whether a function needs to have some output read,
# be it a return value or output pointers.
def NeedsOutputRead(functionElement):
   retVal = False

   if (len(functionElement.findall('return')) > 0 and not (functionElement.findall('return')[0].get('attributes') == 'value' and functionElement.findall('return')[0].get('type') == 'void')):
      retVal = True
   else:
      for arg in functionElement.findall('argument'):
         if 'ptr' in arg.get('attributes'):
            if arg.get('iotype') is not None and 'out' in arg.get('iotype'):
               retVal = True

   return retVal

def SortByFunctionIndex(functionElement):
   FunctionIndexElement = functionElement.findall('FunctionIndex')[0]

   return int(FunctionIndexElement.get('Value'))

def FunctionWithCallbackArgumentOrDoublePtr(functionElement):
   for param in functionElement.findall('argument'):
      if param.get('type') in qsgCommon.callbackList:
         return True
      if 'doubleptr' in param.get('attributes'):
         return True
   return False

def ParamsNeedIndex(parameterList, ioTypeList):
   NeedsIndex = False

   for param in parameterList:
      if 'ptr' in param.get('attributes'):
         for ioType in ioTypeList:
            if (param.get('iotype') is not None and ioType == param.get('iotype')):
               if param.get('lengthParam') <> '1':
                  if not IsPrimitive(param.get('type')) or param.get('type') in qsgCommon.enumList:
                     NeedsIndex = True

   return NeedsIndex

def IsNonStructPrimitive(type):
   RetVal = False

   if 'qapi_Status_t' in type:
      RetVal = True
   elif 'int8' in type:
      RetVal = True
   elif 'int16' in type:
      RetVal = True
   elif 'int32' in type:
      RetVal = True
   elif 'int64' in type:
      RetVal = True
   elif 'bool' in type:
      RetVal = True
   elif type == 'int' or type == 'unsigned int' or type == 'signed int':
      RetVal = True
   elif type == 'char' or type == 'unsigned char' or type == 'signed char':
      RetVal = True
   elif type == 'qapi_BLE_NonAlignedByte_t' or type == 'qapi_BLE_NonAlignedSByte_t':
      RetVal = True
   else:
      RetVal = False

   return RetVal

def IsFixedSize(type):
   RetVal = False

   if type == 'void':
      RetVal = True
   elif 'int8' in type:
      RetVal = True
   elif 'int16' in type:
      RetVal = True
   elif 'int32' in type:
      RetVal = True
   elif 'int64' in type:
      RetVal = True
   elif type == 'char' or type == 'unsigned char' or type == 'signed char':
      RetVal = True
   elif type == 'qapi_BLE_NonAlignedByte_t' or type == 'qapi_BLE_NonAlignedSByte_t':
      RetVal = True
   elif type == 'qapi_BLE_NonAlignedWord_t' or type == 'qapi_BLE_NonAlignedSWord_t':
      RetVal = True
   elif type == 'qapi_BLE_NonAlignedDWord_t' or type == 'qapi_BLE_NonAlignedSDWord_t':
      RetVal = True
   elif type == 'qapi_BLE_NonAlignedQWord_t' or type == 'qapi_BLE_NonAlignedSQWord_t':
      RetVal = True
   else:
      RetVal = False

   return RetVal

def IsPrimitive(type):
   RetVal = False

   if type in qsgCommon.enumList:
      RetVal = True
   elif type == 'void':
      RetVal = True
   elif 'qapi_Status_t' in type:
      RetVal = True
   elif 'int8' in type:
      RetVal = True
   elif 'int16' in type:
      RetVal = True
   elif 'int32' in type:
      RetVal = True
   elif 'int64' in type:
      RetVal = True
   elif 'bool' in type:
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
   elif type == 'qapi_ZB_Handle_t':
      RetVal = True
   elif type == 'qapi_ZB_Cluster_t':
      RetVal = True
   elif type == 'qapi_TWN_Handle_t':
      RetVal = True
   elif type == 'HERH_Handle_t':
      RetVal = True
   elif type == 'qapi_GPIO_ID_t':
      RetVal = True
   else:
      RetVal = False

   return RetVal

def IsHandle(type):
   RetVal = False

   if type == 'qapi_ZB_Handle_t':
      RetVal = True
   elif type == 'qapi_ZB_Cluster_t':
      RetVal = True
   elif type == 'HERH_Handle_t':
      RetVal = True
   else:
      RetVal = False

   return RetVal

def GetCastStr(type):
   RetVal = ''

   if type in qsgCommon.enumList:
      RetVal = '(int *)'
   elif type == 'void':
      RetVal = '(uint8_t *)'
   elif 'qapi_Status_t' in type:
      RetVal = '(uint32_t *)'
   elif 'int8' in type:
      RetVal = '(uint8_t *)'
   elif 'int16' in type:
      RetVal = '(uint16_t *)'
   elif 'int32' in type:
      RetVal = '(uint32_t *)'
   elif 'int64' in type:
      RetVal = '(uint64_t *)'
   elif 'bool' in type:
      RetVal = '(uint32_t *)'
   elif type == 'int' or type == 'unsigned int' or type == 'signed int':
      RetVal = '(int *)'
   elif type == 'char' or type == 'unsigned char' or type == 'signed char':
      RetVal = '(uint8_t *)'
   elif type == 'long' or type == 'unsigned long' or type == 'signed long':
      RetVal = '(uint32_t *)'
   elif type == 'qapi_BLE_NonAlignedByte_t' or type == 'qapi_BLE_NonAlignedSByte_t':
      RetVal = '(uint8_t *)'
   elif type == 'qapi_BLE_NonAlignedWord_t' or type == 'qapi_BLE_NonAlignedSWord_t':
      RetVal = '(uint16_t *)'
   elif type == 'qapi_BLE_NonAlignedDWord_t' or type == 'qapi_BLE_NonAlignedSDWord_t':
      RetVal = '(uint32_t *)'
   elif type == 'qapi_BLE_NonAlignedQWord_t' or type == 'qapi_BLE_NonAlignedSQWord_t':
      RetVal = '(uint64_t *)'
   elif type == 'qapi_ZB_Handle_t':
      RetVal = '(uint32_t *)'
   elif type == 'qapi_ZB_Cluster_t':
      RetVal = '(uint32_t *)'
   elif type == 'qapi_TWN_Handle_t':
      RetVal = '(uint32_t *)'
   elif type == 'HERH_Handle_t':
      RetVal = '(uint32_t *)'
   elif type == 'qapi_GPIO_ID_t':
      RetVal = '(uint16_t *)'
   else:
      RetVal = '(' + type + ' *)'

   return RetVal

def GetCalcPackedSizeFunctionName(type):
   RetVal = ''

   if type in qsgCommon.enumList:
      RetVal = 'CalcPackedSize_int'
   elif type == 'void':
      RetVal = 'CalcPackedSize_8'
   elif 'qapi_Status_t' in type:
      RetVal = 'CalcPackedSize_32'
   elif 'int8' in type:
      RetVal = 'CalcPackedSize_8'
   elif 'int16' in type:
      RetVal = 'CalcPackedSize_16'
   elif 'int32' in type:
      RetVal = 'CalcPackedSize_32'
   elif 'int64' in type:
      RetVal = 'CalcPackedSize_64'
   elif 'bool' in type:
      RetVal = 'CalcPackedSize_32'
   elif type == 'int' or type == 'unsigned int' or type == 'signed int':
      RetVal = 'CalcPackedSize_int'
   elif type == 'char' or type == 'unsigned char' or type == 'signed char':
      RetVal = 'CalcPackedSize_8'
   elif type == 'long' or type == 'unsigned long' or type == 'signed long':
      RetVal = 'CalcPackedSize_int'
   elif type == 'qapi_BLE_NonAlignedByte_t' or type == 'qapi_BLE_NonAlignedSByte_t':
      RetVal = 'CalcPackedSize_8'
   elif type == 'qapi_BLE_NonAlignedWord_t' or type == 'qapi_BLE_NonAlignedSWord_t':
      RetVal = 'CalcPackedSize_16'
   elif type == 'qapi_BLE_NonAlignedDWord_t' or type == 'qapi_BLE_NonAlignedSDWord_t':
      RetVal = 'CalcPackedSize_32'
   elif type == 'qapi_BLE_NonAlignedQWord_t' or type == 'qapi_BLE_NonAlignedSQWord_t':
      RetVal = 'CalcPackedSize_64'
   elif type == 'qapi_ZB_Handle_t':
      RetVal = 'CalcPackedSize_32'
   elif type == 'qapi_ZB_Cluster_t':
      RetVal = 'CalcPackedSize_32'
   elif type == 'qapi_TWN_Handle_t':
      RetVal = 'CalcPackedSize_32'
   elif type == 'HERH_Handle_t':
      RetVal = 'CalcPackedSize_32'
   elif type == 'qapi_GPIO_ID_t':
      RetVal = 'CalcPackedSize_16'
   else:
      RetVal = 'CalcPackedSize_' + type

   return RetVal

def GetPackedWriteFunctionName(type):
   RetVal = ''

   if type in qsgCommon.enumList:
      RetVal = 'PackedWrite_int'
   elif type == 'void':
      RetVal = 'PackedWrite_8'
   elif 'qapi_Status_t' in type:
      RetVal = 'PackedWrite_32'
   elif 'int8' in type:
      RetVal = 'PackedWrite_8'
   elif 'int16' in type:
      RetVal = 'PackedWrite_16'
   elif 'int32' in type:
      RetVal = 'PackedWrite_32'
   elif 'int64' in type:
      RetVal = 'PackedWrite_64'
   elif 'bool' in type:
      RetVal = 'PackedWrite_32'
   elif type == 'int' or type == 'unsigned int' or type == 'signed int':
      RetVal = 'PackedWrite_int'
   elif type == 'char' or type == 'unsigned char' or type == 'signed char':
      RetVal = 'PackedWrite_8'
   elif type == 'long' or type == 'unsigned long' or type == 'signed long':
      RetVal = 'PackedWrite_int'
   elif type == 'qapi_BLE_NonAlignedByte_t' or type == 'qapi_BLE_NonAlignedSByte_t':
      RetVal = 'PackedWrite_8'
   elif type == 'qapi_BLE_NonAlignedWord_t' or type == 'qapi_BLE_NonAlignedSWord_t':
      RetVal = 'PackedWrite_16'
   elif type == 'qapi_BLE_NonAlignedDWord_t' or type == 'qapi_BLE_NonAlignedSDWord_t':
      RetVal = 'PackedWrite_32'
   elif type == 'qapi_BLE_NonAlignedQWord_t' or type == 'qapi_BLE_NonAlignedSQWord_t':
      RetVal = 'PackedWrite_64'
   elif type == 'qapi_ZB_Handle_t':
      RetVal = 'PackedWrite_32'
   elif type == 'qapi_ZB_Cluster_t':
      RetVal = 'PackedWrite_32'
   elif type == 'qapi_TWN_Handle_t':
      RetVal = 'PackedWrite_32'
   elif type == 'HERH_Handle_t':
      RetVal = 'PackedWrite_32'
   elif type == 'qapi_GPIO_ID_t':
      RetVal = 'PackedWrite_16'
   else:
      RetVal = 'PackedWrite_' + type

   return RetVal

def GetPackedReadFunctionName(type):
   RetVal = ''

   if type in qsgCommon.enumList:
      RetVal = 'PackedRead_int'
   elif type == 'void':
      RetVal = 'PackedRead_8'
   elif 'qapi_Status_t' in type:
      RetVal = 'PackedRead_32'
   elif 'int8' in type:
      RetVal = 'PackedRead_8'
   elif 'int16' in type:
      RetVal = 'PackedRead_16'
   elif 'int32' in type:
      RetVal = 'PackedRead_32'
   elif 'int64' in type:
      RetVal = 'PackedRead_64'
   elif 'bool' in type:
      RetVal = 'PackedRead_32'
   elif type == 'int' or type == 'unsigned int' or type == 'signed int':
      RetVal = 'PackedRead_int'
   elif type == 'char' or type == 'unsigned char' or type == 'signed char':
      RetVal = 'PackedRead_8'
   elif type == 'long' or type == 'unsigned long' or type == 'signed long':
      RetVal = 'PackedRead_int'
   elif type == 'qapi_BLE_NonAlignedByte_t' or type == 'qapi_BLE_NonAlignedSByte_t':
      RetVal = 'PackedRead_8'
   elif type == 'qapi_BLE_NonAlignedWord_t' or type == 'qapi_BLE_NonAlignedSWord_t':
      RetVal = 'PackedRead_16'
   elif type == 'qapi_BLE_NonAlignedDWord_t' or type == 'qapi_BLE_NonAlignedSDWord_t':
      RetVal = 'PackedRead_32'
   elif type == 'qapi_BLE_NonAlignedQWord_t' or type == 'qapi_BLE_NonAlignedSQWord_t':
      RetVal = 'PackedRead_64'
   elif type == 'qapi_ZB_Handle_t':
      RetVal = 'PackedRead_32'
   elif type == 'qapi_ZB_Cluster_t':
      RetVal = 'PackedRead_32'
   elif type == 'qapi_TWN_Handle_t':
      RetVal = 'PackedRead_32'
   elif type == 'HERH_Handle_t':
      RetVal = 'PackedRead_32'
   elif type == 'qapi_GPIO_ID_t':
      RetVal = 'PackedRead_16'
   else:
      RetVal = 'PackedRead_' + type

   return RetVal

def GetPrimitiveSize(type):
   size = 0

   if type in qsgCommon.enumList:
      size = 4
   elif 'qapi_Status_t' in type:
      size = 4
   elif type == 'void':
      size = 1
   elif 'int8' in type:
      size = 1
   elif 'int16' in type:
      size = 2
   elif 'int32' in type:
      size = 4
   elif 'int64' in type:
      size = 8
   elif 'bool' in type:
      size = 4
   elif type == 'int' or type == 'unsigned int' or type == 'signed int':
      size = 4
   elif type == 'char' or type == 'unsigned char' or type == 'signed char':
      size = 1
   elif type == 'qapi_BLE_NonAlignedByte_t' or type == 'qapi_BLE_NonAlignedSByte_t':
      size = 1
   elif type == 'qapi_BLE_NonAlignedWord_t' or type == 'qapi_BLE_NonAlignedSWord_t':
      size = 2
   elif type == 'qapi_BLE_NonAlignedDWord_t' or type == 'qapi_BLE_NonAlignedSDWord_t':
      size = 4
   elif type == 'qapi_BLE_NonAlignedQWord_t' or type == 'qapi_BLE_NonAlignedSQWord_t':
      size = 8
   elif type == 'qapi_ZB_Handle_t':
      size = 4
   elif type == 'qapi_ZB_Cluster_t':
      size = 4
   elif type == 'qapi_TWN_Handle_t':
      size = 4
   elif type == 'HERH_Handle_t':
      size = 4
   elif type == 'qapi_GPIO_ID_t':
      size = 2
   else:
      size = 0

   return size

def GetSizeOfStr(type):
   sizeofstr = ''

   if type == 'void':
      sizeofstr = '1'
   else:
      sizeofstr = 'sizeof(' + type + ')'

   return sizeofstr

def GetStructureElement(StructureName):
   # Search global list
   for RootAndStructure in qapi_Common.structRootList:
      if RootAndStructure[1].get('name') == StructureName:
         return RootAndStructure[1]

   return None

def GetEnumElement(EnumName):
   # Search global list
   for RootAndEnum in qapi_Common.enumRootList:
      if RootAndEnum[1].get('name') == EnumName:
         return RootAndEnum[1]

   return None

def isParamLengthInt(paramLength):
   try:
      int(paramLength)
      return True
   except:
      return False

