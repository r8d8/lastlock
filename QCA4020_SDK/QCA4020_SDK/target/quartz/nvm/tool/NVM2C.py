# =============================================================================
# Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
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
# =============================================================================
import re
import os
import argparse

COPYRIGHT_YEARS='2016-2018'

def ParseNVMFile(Input):
   '''
   Parses an NVM file and returns a list of Tags.

   Input is the name of the NVM file to parse.

   Returns a list of Tags in the format [[TagNum, TagLength, TagValue],...].
      Note that TagValue is an array of bytes and all values are integers.
   '''

   # Initialize the list variables. TagList will store the actual tag
   # information and TagNumList is used for duplicate tag detection.
   TagList    = []
   TagNumList = []

   #Parse the NVM input
   with open(Input, 'r') as InputFile:
      State = 'TagNum';

      TagNum = 0
      TagLength = 0

      # Read the NVM file tags/lengths/value and write them to the output array.
      for LineNum, Line in enumerate(InputFile, 1):
         Line = Line.strip()

         # Determine what data the line holds. Ignore any lines that don't
         # start with 'TagNum', 'TagLength', or 'TagValue'
         if Line.startswith('TagNum'):
            if State == 'TagNum':
               # Read the tag number from the line
               Match = re.match(r'TagNum\s*\=\s*(\d+)', Line, re.I)
               if Match:
                  TagNum = int(Match.group(1))

                  # Verify this tag number is unique.
                  if TagNum in TagNumList:
                     raise Exception('Line {0}: Duplicate TagNum {1}.'.format(LineNum, TagNum))

                  TagNumList.append(TagNum)
                  State = 'TagLength';
               else:
                  raise Exception('Line {0}: Error parsing line'.format(LineNum))
            else:
               raise Exception('Line {0}: "TagNum" unexpected at this time.'.format(LineNum))

         elif Line.startswith('TagLength'):
            if State == 'TagLength':
               # Read the tag length from the line
               Match = re.match(r'TagLength\s*\=\s*(\d+)', Line, re.I)
               if Match:
                  TagLength = int(Match.group(1))

                  # Verify the tag length is non-zero.
                  if TagLength == 0:
                     raise Exception('Line {1}: Zero length tag.')

                  State = 'TagValue';
               else:
                  raise Exception('Line {0}: Error parsing line'.format(LineNum))
            else:
               raise Exception('Line {0}: "TagLength" unexpected at this time.'.format(LineNum))

         elif Line.startswith('TagValue'):
            if State == 'TagValue':
               # Read the tag value from the line
               Match = re.match(r'TagValue\s*\=\s*(([0-9a-f][0-9a-f]\s*)*)', Line, re.I)
               if Match:
                  TagValue = [int(Tag, 16) for Tag in Match.group(1).split()]

                  # Verify the length of the tag value matches the tag length.
                  if int(TagLength) != len(TagValue):
                     raise Exception('Line {0}: Length mismatch for tag {1}.'.format(LineNum, TagNum))

                  # Add the tag's information to the tag list.
                  TagList.append([TagNum, TagLength, TagValue])

                  State = 'TagNum';
               else:
                  raise Exception('Line {0}: Error parsing line'.format(LineNum))
            else:
               raise Exception('Line {0}: "TagValue" unexpected at this time.'.format(LineNum))

      # Make sure the end of the file wasn't encountered while processing a tag.
      if State != 'TagNum':
         raise Exception('Unexpected EOF: Expected "{0}".'.format(State))

   # Return the sorted tag list.
   return sorted(TagList, key=lambda Tag: Tag[0])

def WriteEDLFile(TagList, Source, Header=None, Symbol='UsrEDLFileData'):
   '''
   Writes a tag list as an array to a c file.

   TagList Tag information to be written. The format should be the same as what
           is returned by ParseNVMFile().
   Output  Name of the C file to write the tag information to or a handle to an
           already open file (this allows for multiple tag lists to be written
           to the same file).
   Header  Optional name of the C header file to write or a handle to an already
           open file.
   Symbol  Optional name of the a Array that the tag information will be placed
           into. This also determines the name of the variable that stores the
           length of the array (i.e., '<Symbol>Length').
   '''
   # Calculate the overall length of the tag data. Note that each tag contains
   # 12 bytes in addition to the value.
   TotalLength = 0;
   for Tag in TagList:
      TotalLength += 12 + Tag[1]

   if isinstance(Source, str):
      # treat the parameter as a Filename
      SourceFile = open(Source, 'w')
   else:
      # Treat the parameter as a File object.
      SourceFile = Source

   # write a COPYRIGHT to the files if this is the first line
   if SourceFile.tell() == 0:
      # Write the file header
      SourceFile.write('')
      SourceFile.write('/*\n')
      SourceFile.write(' * Copyright (c) {0} Qualcomm Technologies, Inc.\n'.format(COPYRIGHT_YEARS))
      SourceFile.write(' * All Rights Reserved.\n')
      SourceFile.write(' */\n')

   SourceFile.write('\n')

   # Write the start of the EDL buffer.
   SourceFile.write('unsigned char {0}[] = {{\n'.format(Symbol))
   SourceFile.write('   0x02, 0x{0:02X}, 0x{1:02X}, 0x00'.format(TotalLength % 256, TotalLength // 256))

   # Write the tags to the file.
   for Tag in TagList:
      SourceFile.write(',\n')
      SourceFile.write('   0x{0:02X}, 0x00, 0x{1:02X}, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00'.format(Tag[0], Tag[1]))

      for Byte in Tag[2]:
         SourceFile.write(', 0x{0:02X}'.format(Byte))

   # Write the file footer.
   SourceFile.write('\n')
   SourceFile.write('};\n')
   SourceFile.write('\n')
   SourceFile.write('unsigned int {0}Length = sizeof({0});\n'.format(Symbol))
   SourceFile.write('\n')

   # Close the files if they were opened by this function
   if isinstance(Source, str):
      SourceFile.close()

   if Header:
      # Write the header file.
      if isinstance(Header, str):
         # treat the parameter as a Filename
         HeaderFile = open(Header, 'w')
      else:
         # Treat the parameter as a File object.
         HeaderFile = Header

      # write a copyright to the files if this is the first line
      if HeaderFile.tell() == 0:
         # Write the file header
         HeaderFile.write('')
         HeaderFile.write('/*\n')
         HeaderFile.write(' * Copyright (c) {0} Qualcomm Technologies, Inc.\n'.format(COPYRIGHT_YEARS))
         HeaderFile.write(' * All Rights Reserved.\n')
         HeaderFile.write(' */\n')
         HeaderFile.write('\n')

      # Write the symbols to the header file.
      HeaderFile.write('extern unsigned char {0}[];\n'.format(Symbol))
      HeaderFile.write('extern unsigned int {0}Length;\n'.format(Symbol))
      HeaderFile.write('\n')

      if isinstance(Header, str):
         HeaderFile.close()

if __name__ == '__main__':
   Parser = argparse.ArgumentParser(description='Converts an NVM file into a C file.')
   Parser.add_argument('-o', '--output', dest='Output', required=True,                         help='Output C file to generate.')
   Parser.add_argument('-i', '--input',  dest='Input',  required=True,              nargs='+', help='Input NVM file(s) to parse')
   Parser.add_argument('-s', '--symbol', dest='Symbol', default=['UsrEDLFileData'], nargs='+', help='Name of the C symbol(s) for the NVM data. If the number of symbols specified is less than the number of input files, a number will be appended to the last symbol for all remaining files.')
   Parser.add_argument('-H', '--header', dest='Header', action='store_true',                   help='Flag to also generate a C header file. The header file will use the same name as the output file.')
   Arguments = Parser.parse_args()

   SymbolList = Arguments.Symbol
   if len(SymbolList) < len(Arguments.Input):
      # Fill in the remainder of the symbol list based on the name of the last
      # symbol specified.
      Name = SymbolList[-1]
      for Num in range(1, len(Arguments.Input) - len(SymbolList) + 1):
         SymbolList.append('{0}_{1}'.format(Name, Num))

   # Form a list of taglists from the input files specified.
   TagListList = []
   for Input in Arguments.Input:
      TagListList.append(ParseNVMFile(Input))

   # Make sure the output folder exists.
   OutputPath = os.path.dirname(Arguments.Output)
   if not OutputPath:
      OutputPath = '.'
   if not os.path.exists(OutputPath):
      os.makedirs(OutputPath)

   # Write the tags to the output file
   with open(Arguments.Output, 'w') as SourceFile:
      if Arguments.Header:
         HeaderFile = open(Arguments.Output.rsplit('.', 1)[0] + '.h', 'w')
      else:
         HeaderFile = None;

      for TagList, Symbol in zip(TagListList, SymbolList):
         WriteEDLFile(TagList, SourceFile, HeaderFile, Symbol)

      if HeaderFile:
         HeaderFile.close()

