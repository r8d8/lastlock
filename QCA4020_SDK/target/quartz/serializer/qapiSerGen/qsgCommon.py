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

from qsgUtils import *

def init(xml_dir, c_dir, manual_dir, fileId_dir, modules, manualFuncs, manualStructs, manualCbs, gen_manual):
   global enumList
   global enumRootList
   global structList
   global structRootList
   global unionList
   global unionRootList
   global callbackList
   global callbackRootList
   global processedStructList
   global manualFuncList
   global manualStructList
   global manualCbList
   global xmlDir
   global manualDir
   global qapiDir
   global qapiComponents
   global qapiPrefix
   global generateManual
   global fileIdDir

   qapiDir = c_dir
   xmlDir = xml_dir
   manualDir = manual_dir
   fileIdDir = fileId_dir
   qapiComponents = modules
   qapiPrefix = 'qapi_'
   generateManual = gen_manual

   enumList = []
   enumRootList = []
   structList = []
   structRootList = []
   unionList = []
   unionRootList = []
   callbackList = []
   callbackRootList = []
   processedStructList = []
   manualFuncList = manualFuncs
   manualStructList = manualStructs
   manualCbList = manualCbs

def ReadTypesToGlobalsFromXML():
   for component in qapiComponents:
      xml_list = getComponentXMLFiles(component)
      for xml_file in xml_list:
         tree = parse(os.path.join(qapiDir, 'xml', xml_file))
         xmlRoot = tree.getroot()

         # Populate the lists with all types.
         for enumElement in xmlRoot.findall('enum'):
            enumList.append(enumElement.get('name'))
            enumRootList.append([xmlRoot, enumElement])
         for structElement in xmlRoot.findall('structure'):
            structList.append(structElement.get('name'))
            structRootList.append([xmlRoot, structElement])
         for cbElement in xmlRoot.findall('callback'):
            callbackList.append(cbElement.get('name'))
            callbackRootList.append([xmlRoot, cbElement])
         for unionElement in xmlRoot.findall('union'):
            unionList.append(unionElement.get('name'))
            unionRootList.append([xmlRoot, unionElement])
