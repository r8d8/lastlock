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

from qapiSerGen import qsg

def loadConfiguration():
   xml_dir = ''
   c_dir = ''
   manual_dir = ''
   fileId_dir = ''
   modules       = []
   manualFuncs   = []
   manualStructs = []
   manualCbs     = []
   gen_manual = False
   gen_code = True

   # Determine whether or not to generate
   if len(sys.argv) > 1 and sys.argv[1].lower() == 'generatemanual':
      gen_manual = True
   if len(sys.argv) > 1 and sys.argv[1].lower() == 'help':
      print '"qapi_Generate_Serial.py generatemanual" will overwrite files in manual directory with stubs.'
      gen_code = False

   retVal = False
   current_dir = os.path.dirname(os.path.abspath(__file__))

   # Parse the input XML
   if gen_code:
      if os.path.isfile('generator_config.xml'):
         tree = parse('generator_config.xml')
         root = tree.getroot()

         # Get the XML directory configuration
         xml_dir = root.get('xmldir')
         if xml_dir is not None:
            if xml_dir[0] == '/' or xml_dir[0] == '\\':
               xml_dir = xml_dir[1:]
            xml_dir = os.path.join(current_dir, xml_dir)

            c_dir = root.get('cdir')
            if c_dir is not None:
               if c_dir[0] == '/' or c_dir[0] == '\\':
                  c_dir = c_dir[1:]
               c_dir = os.path.join(current_dir, c_dir)

            manual_dir = root.get('manualdir')
            if manual_dir is not None:
               if manual_dir[0] == '/' or manual_dir[0] == '\\':
                  manual_dir = manual_dir[1:]
               manual_dir = os.path.join(current_dir, manual_dir)


               fileId_dir = root.get('fileiddir')
               if manual_dir is not None:
                  if fileId_dir[0] == '/' or fileId_dir[0] == '\\':
                     fileId_dir = fileId_dir[1:]
                  fileId_dir = os.path.join(current_dir, fileId_dir)

                  # Add all the modules
                  for module in root.findall('module'):
                    modules.append(module.get('name'))

                  # Add all the manual functions
                  for manualFunction in root.findall('manualFunction'):
                    manualFuncs.append(manualFunction.get('name'))

                  # Add all the manual structures
                  for manualStructure in root.findall('manualStructure'):
                    manualStructs.append(manualStructure.get('name'))

                  # Add all the manual callbacks
                  for manualCallback in root.findall('manualCallback'):
                    manualCbs.append(manualCallback.get('name'))

                  retVal = True
               else:
                  print 'Error, no file ID directory configured.'
            else:
               print 'Error, no manual code directory configured.'
         else:
            print 'Error, no XML directory configured.'
      else:
         print 'Error, configuration file does not exist.'

   return retVal, xml_dir, c_dir, manual_dir, fileId_dir, modules, manualFuncs, manualStructs, manualCbs, gen_manual

def main():
   retVal, xml_dir, c_dir, manual_dir, fileId_dir, modules, manualFuncs, manualStructs, manualCbs, gen_manual = loadConfiguration()

   if retVal:
      qsg.Initialize(xml_dir, c_dir, manual_dir, fileId_dir, modules, manualFuncs, manualStructs, manualCbs, gen_manual)
      qsg.GenerateCode()

main()

