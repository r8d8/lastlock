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

import qsgCommon
import qsgTest
import qsgFilelist
import qsgQuartz
import qsgQuartz_Cb
import qsgHost
import qsgHost_Cb
import qsgStructs
import qsgUtils

def GenerateCFromXML(xmlFile, component):
   # Parse the XML input and get the root
   tree = parse(qsgCommon.xmlDir + xmlFile)
   root = tree.getroot()

   qsgFilelist.AddGeneratedCode(xmlFile, component)

   # Set the Function Index for all function in this file
   for funcIndex, functionElement in enumerate(root.findall('function')):
      SubElement(functionElement,'FunctionIndex').set('Value', funcIndex)

   # Set the callback index for each callback.
   for callbackIndex, callbackElement in enumerate(root.findall('callback')):
      callbackElement.set('CallbackIndex', str(callbackIndex))

   # Create host callback header and C file if a function exists
   if len(root.findall('function')) != 0:
      # Create the host QAPI API functions.
      qsgHost.CreateHostQAPICode(xmlFile, component, root)

      # Create the Quartz QAPI API functions.
      qsgQuartz.CreateQzQAPICode(xmlFile, component, root)

      # Create the test code and headers
      qsgTest.CreateTestCode(xmlFile, component, root)

      # Create the function list file
      qsgFilelist.CreateFunctionListFile(xmlFile, component, root)

   # Create host callback header and C file if a callback exists
   if len(root.findall('callback')) != 0:
      # Create the host QAPI callback functions.
      qsgHost_Cb.CreateHostCallbackCode(xmlFile, component, root)

      # Create the Quartz QAPI callback functions.
      qsgQuartz_Cb.CreateQuartzCallbackCode(xmlFile, component, root)

   # Create the common struct pack/unpack/size code
   qsgStructs.CreateStructCode(xmlFile, component, root)

   return

def GenerateCode():

   # Make all the needed directories
   MakeDirectories()

   # Begin writing of the test and filelist components
   qsgTest.Begin()
   qsgFilelist.Begin()

   qsgCommon.ReadTypesToGlobalsFromXML()

   # Generate the C Files for all of the XMLs
   for component in qsgCommon.qapiComponents:
      print 'Generating component ' + component
      xml_list = qsgUtils.getComponentXMLFiles(component)
      # Generate C packing files
      for xml_file in xml_list:
         print '   Generating code for header ' + xml_file.replace('.xml','')
         # Call function to generate the code
         GenerateCFromXML(xml_file, component)

   # End writing of the test and filelist components
   qsgTest.End()
   qsgFilelist.End()

   print 'Code generation complete.'

def MakeDirectories():
   # Make directories for the generated code
   if not os.path.exists(os.path.join(qsgCommon.qapiDir , 'host')):
      os.makedirs(os.path.join(qsgCommon.qapiDir , 'host'))
   if not os.path.exists(os.path.join(qsgCommon.qapiDir , 'host', 'include')):
      os.makedirs(os.path.join(qsgCommon.qapiDir , 'host', 'include'))
   if not os.path.exists(os.path.join(qsgCommon.qapiDir , 'qz')):
      os.makedirs(os.path.join(qsgCommon.qapiDir , 'qz'))
   if not os.path.exists(os.path.join(qsgCommon.qapiDir , 'qz', 'include')):
      os.makedirs(os.path.join(qsgCommon.qapiDir , 'qz', 'include'))
   if not os.path.exists(os.path.join(qsgCommon.qapiDir , 'common')):
      os.makedirs(os.path.join(qsgCommon.qapiDir , 'common'))
   if not os.path.exists(os.path.join(qsgCommon.qapiDir , 'common', 'include')):
      os.makedirs(os.path.join(qsgCommon.qapiDir , 'common', 'include'))
   if not os.path.exists(os.path.join(qsgCommon.qapiDir , 'test')):
      os.makedirs(os.path.join(qsgCommon.qapiDir , 'test'))
   if not os.path.exists(os.path.join(qsgCommon.qapiDir , 'test', 'include')):
         os.makedirs(os.path.join(qsgCommon.qapiDir , 'test', 'include'))

   # Make directories for the manual code
   if not os.path.exists(os.path.join(qsgCommon.manualDir , 'host')):
      os.makedirs(os.path.join(qsgCommon.manualDir , 'host'))
   if not os.path.exists(os.path.join(qsgCommon.manualDir , 'host', 'include')):
      os.makedirs(os.path.join(qsgCommon.manualDir , 'host', 'include'))
   if not os.path.exists(os.path.join(qsgCommon.manualDir , 'qz')):
      os.makedirs(os.path.join(qsgCommon.manualDir , 'qz'))
   if not os.path.exists(os.path.join(qsgCommon.manualDir , 'qz', 'include')):
      os.makedirs(os.path.join(qsgCommon.manualDir , 'qz', 'include'))
   if not os.path.exists(os.path.join(qsgCommon.manualDir , 'common')):
      os.makedirs(os.path.join(qsgCommon.manualDir , 'common'))
   if not os.path.exists(os.path.join(qsgCommon.manualDir , 'common', 'include')):
      os.makedirs(os.path.join(qsgCommon.manualDir , 'common', 'include'))
   if not os.path.exists(os.path.join(qsgCommon.manualDir , 'test')):
      os.makedirs(os.path.join(qsgCommon.manualDir , 'test'))
   if not os.path.exists(os.path.join(qsgCommon.manualDir , 'test', 'include')):
      os.makedirs(os.path.join(qsgCommon.manualDir , 'test', 'include'))

def Initialize(xml_dir, c_dir, manual_dir, fileId_dir, modules, manualFuncs, manualStructs, manualCbs, gen_manual):
   qsgCommon.init(xml_dir, c_dir, manual_dir, fileId_dir, modules, manualFuncs, manualStructs, manualCbs, gen_manual)

