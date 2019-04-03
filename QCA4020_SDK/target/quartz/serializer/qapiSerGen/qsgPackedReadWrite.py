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

# Makes the packed read code for pointer function arguments and structure members
# Also handles fixed length arrays within structures since the handling is similar
def MakePackedReadPointerParamString(param, parent, includeValue, ioTypeList, leadingSpace, bufferName, bufferListName, prefix, makeAllocs, target_side=0):
    RetVal = ''

    if ('bracketArray' in param.get('attributes') or param.get('attributes') == 'ptr' or param.get('attributes') == 'ptr,const'):
        # Copy the prefix and parameter name
        paramNameStr = prefix + param.get('name')

        for ioType in ioTypeList:
            # Set values for how to handle this type
            isRealPointer = (not 'bracketArray' in param.get('attributes'))
            useReadArray = (IsFixedSize(param.get('type')) and param.get('lengthParam') <> '1')
            useForLoop = (not IsFixedSize(param.get('type')) and param.get('lengthParam') <> '1' and param.get('lengthParam') <> '__strlen__')
            addlLeadingSpace = ''

            # Set up strings for length parameters ahead of time.
            lengthValueStr = ''
            sizeStr = ''
            lengthParamIsValue = False
            lengthParamNameStr = ''
            readArrayLenStr = ''

            if makeAllocs and isRealPointer:
                addlLeadingSpace = '    '

            # Determine whether this is part of a structure, which contains 'members',
            # or a function, which contains 'arguments'.
            paramName = ''
            if len(parent.findall('argument')) > len(parent.findall('member')):
                paramName = 'argument'
            if len(parent.findall('member')) > len(parent.findall('argument')):
                paramName = 'member'

            # Get the length parameter information
            if 'bracketArray' in param.get('attributes'):
                lengthValueStr = param.get('lengthParam')
                lengthParamIsValue = True
                sizeStr = '(' + GetSizeOfStr(param.get('type')) + '*(' + param.get('lengthParam') + '))'
                if useReadArray:
                    readArrayLenStr = '' + GetSizeOfStr(param.get('type')) + ', ' + param.get('lengthParam')
            elif param.get('lengthParam') == '1':
                lengthParamIsValue = True
                sizeStr = '' + GetSizeOfStr(param.get('type')) + ''
            elif param.get('lengthParam') == '__strlen__':
                lengthParamIsValue = True
                sizeStr = '(strlen((const char *)(' + bufferName + ')->CurrentPos)+1)'
                if useReadArray:
                    readArrayLenStr = '1, (strlen((const char *)(' + bufferName + ')->CurrentPos)+1)'
            elif isParamLengthInt(param.get('lengthParam')) == True:
                sizeStr = param.get('lengthParam')
                lengthParamIsValue = True
                if useReadArray:
                    readArrayLenStr = '1, ' + param.get('lengthParam')
            else:
                for lengthParam in parent.findall(paramName):
                    if lengthParam.get('name') == param.get('lengthParam'):
                        #Some functions/structures have the variable data field before the actual length parameter.
                        #For such cases, add the length field before the data to notify the other side. This means
                        #the packet with have 2 length fields, one before and one after the variable field data.
                        if 'yes' == param.get('lengthFirst') and param.get('iotype') is not None and ioType == param.get('iotype'):
                            parameterList = []
                            parameterList.append(lengthParam)
                            TmpRetVal = MakePackedReadParametersString(parent, parameterList, includeValue, ioTypeList, leadingSpace, bufferName, bufferListName, prefix, makeAllocs)
                            RetVal = RetVal + TmpRetVal

                        lengthParamNameStr = prefix + param.get('lengthParam')
                        if 'value' in lengthParam.get('attributes'):
                            lengthParamIsValue = True
                            lengthValueStr = prefix + param.get('lengthParam')
                            sizeStr = '(' + GetSizeOfStr(param.get('type')) + '*(' + lengthParamNameStr + '))'
                            if useReadArray:
                                if param.get('type') == 'void':
                                    readArrayLenStr = '1, ' + lengthParamNameStr
                                else:
                                    readArrayLenStr = '' + GetSizeOfStr(param.get('type')) + ', ' + lengthParamNameStr
                        else:
                            lengthParamIsValue = False
                            lengthValueStr = '*' + prefix + param.get('lengthParam')
                            sizeStr = '(' + GetSizeOfStr(param.get('type')) + '*(*' + lengthParamNameStr + '))'
                            if useReadArray:
                                if param.get('type') == 'void':
                                    readArrayLenStr = '1, *' + lengthParamNameStr
                                else:
                                    readArrayLenStr = '' + GetSizeOfStr(param.get('type')) + ', *' + lengthParamNameStr
                        break

                if lengthParamNameStr == '':
                    print '#warning# Could not find length parameter ' + param.get('lengthParam') + ' in ' + parent.get('name') + ' for ' + paramNameStr

            if (param.get('iotype') is not None and ioType == param.get('iotype')):
                # Write the initial parameter checks and pointer header reads

                # Length parameter must be non-zero for some cases
                if 'yes' == param.get('lengthFirst') and target_side == 1:
                    if lengthParamIsValue:
                        RetVal = RetVal + leadingSpace + 'if(0 == ' + lengthParamNameStr + ')\n'
                    else:
                        RetVal = RetVal + leadingSpace + 'if(!' + lengthParamNameStr + ' || !(*' + lengthParamNameStr + '))\n'
                    #end-if

                    RetVal = RetVal + leadingSpace + '{\n'
                    RetVal = RetVal + leadingSpace + '    qsResult = ssInvalidParameter;\n'
                    RetVal = RetVal + leadingSpace + '}\n'
                #end-if


                RetVal = RetVal + leadingSpace + 'if(qsResult == ssSuccess)\n'
                if isRealPointer:
                    RetVal = RetVal + leadingSpace + '    qsResult = PackedRead_PointerHeader(' + bufferName + ', ' + bufferListName + ', &qsPointerValid);\n\n'
                    if lengthParamIsValue:
                        RetVal = RetVal + leadingSpace + 'if((qsResult == ssSuccess) && (qsPointerValid == TRUE))\n'
                    else:
                        RetVal = RetVal + leadingSpace + 'if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (' + lengthParamNameStr + ' != NULL))\n'
                RetVal = RetVal + leadingSpace + '{\n'

                # Make the allocation if needed
                if makeAllocs and isRealPointer:
                    RetVal = RetVal + leadingSpace + '    ' + paramNameStr + ' = AllocateBufferListEntry(' + bufferListName + ', ' + sizeStr + ');\n\n'
                    RetVal = RetVal + leadingSpace + '    if(' + paramNameStr + ' == NULL)\n'
                    RetVal = RetVal + leadingSpace + '    {\n'
                    RetVal = RetVal + leadingSpace + '        qsResult = ssAllocationError;\n'
                    RetVal = RetVal + leadingSpace + '    }\n'
                    RetVal = RetVal + leadingSpace + '    else\n'
                    RetVal = RetVal + leadingSpace + '    {\n'

                # Read packed via the array function, for loop for structure arrays, or a single struct array read
                if useReadArray:
                    if param.get('TempLength') is not None and target_side <> 1:
                        RetVal = RetVal + leadingSpace + addlLeadingSpace + '    if(' + param.get('TempLength') + ' > ' + readArrayLenStr.split(',')[1].strip(' ') + ')\n'
                        RetVal = RetVal + leadingSpace + addlLeadingSpace + '        ' + param.get('TempLength') + ' = ' + readArrayLenStr.split(',')[1].strip(' ') + ';\n'
                        RetVal = RetVal + leadingSpace + addlLeadingSpace + '    qsResult = PackedRead_Array(' + bufferName + ', ' + bufferListName + ', (void *)' + paramNameStr + ', ' + readArrayLenStr.split(',')[0].strip(' ') + ', ' + param.get('TempLength') + ');\n'
                    else:
                        RetVal = RetVal + leadingSpace + addlLeadingSpace + '    qsResult = PackedRead_Array(' + bufferName + ', ' + bufferListName + ', (void *)' + paramNameStr + ', ' + readArrayLenStr + ');\n'
                elif useForLoop:
                    if param.get('TempLength') is not None and target_side <> 1:
                        RetVal = RetVal + leadingSpace + addlLeadingSpace + '    if(' + param.get('TempLength') + ' > ' + lengthValueStr + ')\n'
                        RetVal = RetVal + leadingSpace + addlLeadingSpace + '        ' + param.get('TempLength') + ' = ' + lengthValueStr + ';\n'
                        RetVal = RetVal + leadingSpace + addlLeadingSpace + '    for (qsIndex = 0; qsIndex < ' + param.get('TempLength') + '; qsIndex++)\n'
                    else:
                        RetVal = RetVal + leadingSpace + addlLeadingSpace + '    for (qsIndex = 0; qsIndex < ' + lengthValueStr + '; qsIndex++)\n'
                    RetVal = RetVal + leadingSpace + addlLeadingSpace + '    {\n'
                    RetVal = RetVal + leadingSpace + addlLeadingSpace + '        if(qsResult == ssSuccess)\n'
                    RetVal = RetVal + leadingSpace + addlLeadingSpace + '            qsResult = ' + GetPackedReadFunctionName(param.get('type')) + '(' + bufferName + ', ' + bufferListName + ', &(' + GetCastStr(param.get('type')) + paramNameStr + ')[qsIndex]);\n'
                    RetVal = RetVal + leadingSpace + addlLeadingSpace + '    }\n'
                else:
                    if not makeAllocs and IsHandle(param.get('type')):
                        RetVal = RetVal + leadingSpace + addlLeadingSpace + '    *' + paramNameStr + ' = NULL;\n'
                    RetVal = RetVal + leadingSpace + addlLeadingSpace + '    qsResult = ' + GetPackedReadFunctionName(param.get('type')) + '(' + bufferName + ', ' + bufferListName + ', ' + GetCastStr(param.get('type')) + paramNameStr + ');\n'

                # Add the closing braces and NULL set if necessary
                if makeAllocs and isRealPointer:
                    RetVal = RetVal + leadingSpace + '    }\n'
                RetVal = RetVal + leadingSpace + '}\n'
                if isRealPointer and makeAllocs:
                    RetVal = RetVal + leadingSpace + 'else\n'
                    RetVal = RetVal + leadingSpace + '    ' + paramNameStr + ' = NULL;\n'
                RetVal = RetVal + '\n'
            else:
                # Write pointer headers for output buffers if we are looking for 'in' parameters and 'out' is not in the ioTypeList.
                # In this case we are in a function handler and will need output buffers but do not need to read them from the packet.
                if (isRealPointer and param.get('iotype') is not None and ioType == 'in' and param.get('iotype') == 'out' and (len(ioTypeList) == 1 or (len(ioTypeList) == 2 and 'in,out' in ioTypeList))):

                    # Write the initial parameter checks and pointer header reads
                    RetVal = RetVal + leadingSpace + 'if(qsResult == ssSuccess)\n'
                    if isRealPointer:
                        RetVal = RetVal + leadingSpace + '    qsResult = PackedRead_PointerHeader(' + bufferName + ', ' + bufferListName + ', &qsPointerValid);\n\n'
                        if lengthParamIsValue:
                            RetVal = RetVal + leadingSpace + 'if((qsResult == ssSuccess) && (qsPointerValid == TRUE))\n'
                        else:
                            RetVal = RetVal + leadingSpace + 'if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (' + lengthParamNameStr + ' != NULL))\n'

                    # Allocate the output buffer or set it to NULL if the pointer header was NULL.
                    RetVal = RetVal + leadingSpace + '{\n'
                    RetVal = RetVal + leadingSpace + '    ' + paramNameStr + ' = AllocateBufferListEntry(' + bufferListName + ', ' + sizeStr + ');\n\n'
                    RetVal = RetVal + leadingSpace + '    if(' + paramNameStr + ' == NULL)\n'
                    RetVal = RetVal + leadingSpace + '        qsResult = ssAllocationError;\n'
                    RetVal = RetVal + leadingSpace + '}\n'
                    RetVal = RetVal + leadingSpace + 'else\n'
                    RetVal = RetVal + leadingSpace + '    ' + paramNameStr + '= NULL;\n\n'
    return RetVal

# Makes the packed read code for a list of parameters, regardless of type
# (value, pointer, union, etc.)
def MakePackedReadParametersString(parent, parameterList, includeValue, ioTypeList, leadingSpace, bufferName, bufferListName, prefix, makeAllocs, target_side=0):
    RetVal = ''

    for param in parameterList:
        if not param.get('type') in qsgCommon.callbackList:
            if 'value' in param.get('attributes') and includeValue:
                # Read function arguments packed as value.
                RetVal = RetVal + leadingSpace + 'if(qsResult == ssSuccess)\n'
                RetVal = RetVal + leadingSpace + '    qsResult = ' + GetPackedReadFunctionName(param.get('type')) + '(' + bufferName + ', ' + bufferListName + ', ' + GetCastStr(param.get('type')) + '&' + prefix + param.get('name') + ');\n\n'

    for param in parameterList:
        if not param.get('type') in qsgCommon.structList:
            # Write the non-struct pointers.
            TmpRetVal = MakePackedReadPointerParamString(param, parent, includeValue, ioTypeList, leadingSpace, bufferName, bufferListName, prefix, makeAllocs, target_side);
            RetVal = RetVal + TmpRetVal
    for param in parameterList:
        if param.get('type') in qsgCommon.structList:
            # Write the struct pointers.
            TmpRetVal = MakePackedReadPointerParamString(param, parent, includeValue, ioTypeList, leadingSpace, bufferName, bufferListName, prefix, makeAllocs, target_side);
            RetVal = RetVal + TmpRetVal
    for param in parameterList:
        if param.get('attributes') == 'union':
            if len(param.findall('unionMap')) > 0:
                unionMap = param.findall('unionMap')[-1]
                if unionMap.get('name') is not None:
                    RetVal = RetVal + leadingSpace + 'if(qsResult == ssSuccess)\n'
                    RetVal = RetVal + leadingSpace + '{\n'
                    RetVal = RetVal + leadingSpace + '    switch(' + prefix + unionMap.get('name') + ')\n'
                    RetVal = RetVal + leadingSpace + '    {\n'
                    for mapEntry in unionMap.findall('mapEntry'):
                        unionMember = param.findall('member')[0]
                        for members in param.findall('member'):
                            if members.get('name') == mapEntry.get('member'):
                                unionMember = members
                        RetVal = RetVal + leadingSpace + '        case ' + mapEntry.get('value') + ':\n'
                        if 'value' in unionMember.get('attributes'):
                            RetVal = RetVal + leadingSpace + '            qsResult = ' + GetPackedReadFunctionName(mapEntry.get('type')) + '(' + bufferName + ', ' + bufferListName + ', ' + GetCastStr(unionMember.get('type')) + '&' + prefix + param.get('name') + '.' + unionMember.get('name') + ');\n'
                        else:
                            if 'bracketArray' in unionMember.get('attributes') and unionMember.get('lengthParam') is not None:
                                if param.get('TempLength') is not None and target_side <> 1:
                                    RetVal = RetVal + leadingSpace + '            if(' + param.get('TempLength') + ' > ' + unionMember.get('lengthParam') + ')\n'
                                    RetVal = RetVal + leadingSpace + '                ' + param.get('TempLength') + ' = ' + unionMember.get('lengthParam') + ';\n'
                                    RetVal = RetVal + leadingSpace + '            qsResult = PackedRead_Array(' + bufferName + ', ' + bufferListName + ', (void *)&(' + prefix + param.get('name') + '.' + unionMember.get('name') + '), ' + GetSizeOfStr(unionMember.get('type')) + ', ' + unionMember.get('TempLength') + ');\n'
                                else:
                                    RetVal = RetVal + leadingSpace + '            qsResult = PackedRead_Array(' + bufferName + ', ' + bufferListName + ', (void *)&(' + prefix + param.get('name') + '.' + unionMember.get('name') + '), ' + GetSizeOfStr(unionMember.get('type')) + ', ' + unionMember.get('lengthParam') + ');\n'
                            else:
                                RetVal = RetVal + leadingSpace + '            ' + prefix + param.get('name') + '.' + unionMember.get('name') + ' = AllocateBufferListEntry(' + bufferListName + ', sizeof(' + unionMember.get('type') + '));\n\n'
                                RetVal = RetVal + leadingSpace + '            if(' + prefix + param.get('name') + '.' + unionMember.get('name') + ' == NULL)\n'
                                RetVal = RetVal + leadingSpace + '            {\n'
                                RetVal = RetVal + leadingSpace + '                qsResult = ssAllocationError;\n'
                                RetVal = RetVal + leadingSpace + '            }\n'
                                RetVal = RetVal + leadingSpace + '            else\n'
                                RetVal = RetVal + leadingSpace + '            {\n'
                                RetVal = RetVal + leadingSpace + '                qsResult = ' + GetPackedReadFunctionName(mapEntry.get('type')) + '(' + bufferName + ', ' + bufferListName + ', ' + GetCastStr(unionMember.get('type')) + prefix + param.get('name') + '.' + unionMember.get('name') + ');\n'
                                RetVal = RetVal + leadingSpace + '            }\n'
                        RetVal = RetVal + leadingSpace + '            break;\n'
                    RetVal = RetVal + leadingSpace + '        default:\n'
                    RetVal = RetVal + leadingSpace + '            break;\n'
                    RetVal = RetVal + leadingSpace + '    }\n'
                    RetVal = RetVal + leadingSpace + '}\n\n'
    return RetVal

# Makes the packed write code for pointer function arguments and structure members
# Also handles fixed length arrays within structures since the handling is similar
def MakePackedWritePointerParamString(param, parent, includeValue, ioTypeList, leadingSpace, bufferName, prefix, host_side=0):
    RetVal = ''

    if ('bracketArray' in param.get('attributes') or param.get('attributes') == 'ptr' or param.get('attributes') == 'ptr,const'):
        # Copy the prefix and parameter name
        paramNameStr = prefix + param.get('name')

        # Set values for how to handle this type
        isRealPointer = (not 'bracketArray' in param.get('attributes'))
        useWriteArray = (IsFixedSize(param.get('type')) and param.get('lengthParam') <> '1')
        useForLoop = (not IsFixedSize(param.get('type')) and param.get('lengthParam') <> '1' and param.get('lengthParam') <> '__strlen__')
        addlLeadingSpace = ''

        # Set up strings for length parameters ahead of time.
        lengthValueStr = ''
        sizeStr = ''
        lengthParamIsValue = False
        lengthParamNameStr = ''
        writeArrayLenStr = ''

        # Determine whether this is part of a structure, which contains 'members',
        # or a function, which contains 'arguments'.
        paramName = ''
        if len(parent.findall('argument')) > len(parent.findall('member')):
            paramName = 'argument'
        if len(parent.findall('member')) > len(parent.findall('argument')):
            paramName = 'member'

        # Get the length parameter information
        if 'bracketArray' in param.get('attributes'):
            lengthValueStr = param.get('lengthParam')
            lengthParamIsValue = True
            sizeStr = '(' + GetSizeOfStr(param.get('type')) + '*(' + param.get('lengthParam') + '))'
            if useWriteArray:
                writeArrayLenStr = '' + GetSizeOfStr(param.get('type')) + ', ' + param.get('lengthParam')
        elif param.get('lengthParam') == '1':
            lengthParamIsValue = True
            sizeStr = '' + GetSizeOfStr(param.get('type')) + ''
        elif param.get('lengthParam') == '__strlen__':
            lengthParamIsValue = True
            sizeStr = '(strlen((const char *)(' + paramNameStr + '))+1)'
            if useWriteArray:
                writeArrayLenStr = '1, (strlen((const char *)(' + paramNameStr + '))+1)'
        elif isParamLengthInt(param.get('lengthParam')) == True:
            if useWriteArray:
                writeArrayLenStr = '1, ' + param.get('lengthParam')
                lengthParamIsValue = True
        else:
            for lengthParam in parent.findall(paramName):
                if lengthParam.get('name') == param.get('lengthParam'):
                    lengthParamNameStr = prefix + param.get('lengthParam')
                    if 'value' in lengthParam.get('attributes'):
                        lengthParamIsValue = True
                        lengthValueStr = prefix + param.get('lengthParam')
                        sizeStr = '(' + GetSizeOfStr(param.get('type')) + '*(' + lengthParamNameStr + '))'
                        if useWriteArray:
                            if param.get('type') == 'void':
                                writeArrayLenStr = '1, ' + lengthParamNameStr
                            else:
                                writeArrayLenStr = '' + GetSizeOfStr(param.get('type')) + ', ' + lengthParamNameStr
                    else:
                        lengthParamIsValue = False
                        lengthValueStr = '*' + prefix + param.get('lengthParam')
                        sizeStr = '(' + GetSizeOfStr(param.get('type')) + '*(*' + lengthParamNameStr + '))'
                        if useWriteArray:
                            if param.get('type') == 'void':
                                writeArrayLenStr = '1, *' + lengthParamNameStr
                            else:
                                writeArrayLenStr = '' + GetSizeOfStr(param.get('type')) + ', *' + lengthParamNameStr
                    break

            if lengthParamNameStr == '':
                print '#warning# Could not find length parameter ' + param.get('lengthParam') + ' in ' + parent.get('name') + ' for ' + paramNameStr

        for ioType in ioTypeList:
            if (param.get('iotype') is not None and ioType == param.get('iotype')):

                #Some functions/structures have the variable data field before the actual length parameter.
                #For such cases, add the length field before the data to notify the other side. This means
                #the packet with have 2 length fields, one before and oe after the variable field data.
                if 'yes' == param.get('lengthFirst'):
                    if host_side == 1:
                        if lengthParamIsValue:
                            RetVal = RetVal + leadingSpace + 'if(0 == ' + lengthParam.get('name') + ')\n'
                        else:
                            RetVal = RetVal + leadingSpace + 'if(!' + lengthParam.get('name') + ' || !(*' + lengthParam.get('name') + '))\n'
                        RetVal = RetVal + leadingSpace + '{\n'
                        RetVal = RetVal + leadingSpace + '    qsResult = ssInvalidParameter;\n'
                        RetVal = RetVal + leadingSpace + '}\n'
                        #end-if
                    parameterList = []
                    parameterList.append(lengthParam)
                    TmpRetVal = MakePackedWriteParametersString(parent, parameterList, includeValue, ioTypeList, leadingSpace, bufferName, prefix)
                    RetVal = RetVal + TmpRetVal
                #end-if

                # Write the initial parameter checks and pointer header writes
                RetVal = RetVal + leadingSpace + 'if(qsResult == ssSuccess)\n'
                if isRealPointer:
                    RetVal = RetVal + leadingSpace + '    qsResult = PackedWrite_PointerHeader(' + bufferName + ', (void *)' + paramNameStr + ');\n\n'
                    if lengthParamIsValue:
                        RetVal = RetVal + leadingSpace + 'if((qsResult == ssSuccess) && (' + paramNameStr + ' != NULL))\n'
                    else:
                        RetVal = RetVal + leadingSpace + 'if((qsResult == ssSuccess) && (' + paramNameStr + ' != NULL) && (' + lengthParamNameStr + ' != NULL))\n'
                RetVal = RetVal + leadingSpace + '{\n'

                # Write packed via the array function, for loop for structure arrays, or a single struct array write
                if useWriteArray:
                    if param.get('TempLength') is not None:
                        RetVal = RetVal + leadingSpace + '    qsResult = PackedWrite_Array(' + bufferName + ', (void *)' + paramNameStr + ', ' + writeArrayLenStr.split(',')[0].strip(' ') + ', ' + param.get('TempLength') + ');\n'
                    else:
                        RetVal = RetVal + leadingSpace + '    qsResult = PackedWrite_Array(' + bufferName + ', (void *)' + paramNameStr + ', ' + writeArrayLenStr + ');\n'
                elif useForLoop:
                    if param.get('TempLength') is not None:
                        RetVal = RetVal + leadingSpace + '    for (qsIndex = 0; qsIndex < ' + param.get('TempLength') + '; qsIndex++)\n'
                    else:
                        RetVal = RetVal + leadingSpace + '    for (qsIndex = 0; qsIndex < ' + lengthValueStr + '; qsIndex++)\n'
                    RetVal = RetVal + leadingSpace + '    {\n'
                    RetVal = RetVal + leadingSpace + '        if(qsResult == ssSuccess)\n'
                    RetVal = RetVal + leadingSpace + '            qsResult = ' + GetPackedWriteFunctionName(param.get('type')) + '(' + bufferName + ', &(' + GetCastStr(param.get('type')) + paramNameStr + ')[qsIndex]);\n'
                    RetVal = RetVal + leadingSpace + '    }\n'
                else:
                    RetVal = RetVal + leadingSpace + '    qsResult = ' + GetPackedWriteFunctionName(param.get('type')) + '(' + bufferName + ', ' + GetCastStr(param.get('type')) + paramNameStr + ');\n'

                # Add the closing brace
                RetVal = RetVal + leadingSpace + '}\n\n'
            else:
                # Write pointer headers for output buffers if we are looking for 'in' parameters and 'out' is not in the ioTypeList.
                if (isRealPointer and param.get('iotype') is not None and ioType == 'in' and param.get('iotype') == 'out' and (len(ioTypeList) == 1 or (len(ioTypeList) == 2 and 'in,out' in ioTypeList))):
                    RetVal = RetVal + leadingSpace + 'if(qsResult == ssSuccess)\n'
                    RetVal = RetVal + leadingSpace + '    qsResult = PackedWrite_PointerHeader(' + bufferName + ', (void *)' + paramNameStr + ');\n\n'
    return RetVal

# Makes the packed write code for a list of parameters, regardless of type
# (value, pointer, union, etc.)
def MakePackedWriteParametersString(parent, parameterList, includeValue, ioTypeList, leadingSpace, bufferName, prefix, host_side=0):
    RetVal = ''

    # Write each element to the buffer.
    for param in parameterList:
        if not param.get('type') in qsgCommon.callbackList:
            if 'value' in param.get('attributes') and includeValue:
                RetVal = RetVal + leadingSpace + 'if(qsResult == ssSuccess)\n'
                RetVal = RetVal + leadingSpace + '    qsResult = ' + GetPackedWriteFunctionName(param.get('type')) + '(' + bufferName + ', ' + GetCastStr(param.get('type')) + '&' + prefix + param.get('name') + ');\n\n'
    for param in parameterList:
        if not param.get('type') in qsgCommon.structList:
            # Write the non-struct pointers.
            TmpRetVal = MakePackedWritePointerParamString(param, parent, includeValue, ioTypeList, leadingSpace, bufferName, prefix, host_side);
            RetVal = RetVal + TmpRetVal
    for param in parameterList:
        if param.get('type') in qsgCommon.structList:
            # Write the struct pointers.
            TmpRetVal = MakePackedWritePointerParamString(param, parent, includeValue, ioTypeList, leadingSpace, bufferName, prefix, host_side);
            RetVal = RetVal + TmpRetVal
    for param in parameterList:
        if param.get('attributes') == 'union':
            if len(param.findall('unionMap')) > 0:
                unionMap = param.findall('unionMap')[-1]
                if unionMap.get('name') is not None:
                    RetVal = RetVal + leadingSpace + 'if(qsResult == ssSuccess)\n'
                    RetVal = RetVal + leadingSpace + '{\n'
                    RetVal = RetVal + leadingSpace + '    switch(' + prefix + unionMap.get('name') + ')\n'
                    RetVal = RetVal + leadingSpace + '    {\n'
                    for mapEntry in unionMap.findall('mapEntry'):
                        unionMember = param.findall('member')[0]
                        for members in param.findall('member'):
                            if members.get('name') == mapEntry.get('member'):
                                unionMember = members
                        RetVal = RetVal + leadingSpace + '        case ' + mapEntry.get('value') + ':\n'
                        if 'value' in unionMember.get('attributes'):
                            RetVal = RetVal + leadingSpace + '         qsResult = ' + GetPackedWriteFunctionName(mapEntry.get('type')) + '(' + bufferName + ', ' + GetCastStr(unionMember.get('type')) + '&' + prefix + param.get('name') + '.' + unionMember.get('name') + ');\n'
                        else:
                            if 'bracketArray' in unionMember.get('attributes') and unionMember.get('lengthParam') is not None:
                                if param.get('TempLength') is not None:
                                    RetVal = RetVal + leadingSpace + '            if(' + param.get('TempLength') + ' > ' + unionMember.get('lengthParam') + ')\n'
                                    RetVal = RetVal + leadingSpace + '               ' + param.get('TempLength') + ' = ' + unionMember.get('lengthParam') + ';\n'
                                    RetVal = RetVal + leadingSpace + '            qsResult = PackedWrite_Array(' + bufferName + ', (void *)&(' + prefix + param.get('name') + '.' + unionMember.get('name') + '), ' + GetSizeOfStr(unionMember.get('type')) + ', ' + unionMember.get('TempLength') + ');\n'
                                else:
                                    RetVal = RetVal + leadingSpace + '            qsResult = PackedWrite_Array(' + bufferName + ', (void *)&(' + prefix + param.get('name') + '.' + unionMember.get('name') + '), ' + GetSizeOfStr(unionMember.get('type')) + ', ' + unionMember.get('lengthParam') + ');\n'
                            else:
                                RetVal = RetVal + leadingSpace + '            qsResult = ' + GetPackedWriteFunctionName(mapEntry.get('type')) + '(' + bufferName + ', ' + GetCastStr(unionMember.get('type')) + prefix + param.get('name') + '.' + unionMember.get('name') + ');\n'
                        RetVal = RetVal + leadingSpace + '            break;\n'
                    RetVal = RetVal + leadingSpace + '        default:\n'
                    RetVal = RetVal + leadingSpace + '            break;\n'
                    RetVal = RetVal + leadingSpace + '    }\n'
                    RetVal = RetVal + leadingSpace + '}\n\n'
                else:
                    print '#warning# Incomplete union map for ' + param.get('name') + ' in ' + parent.get('name')
            else:
                print '#warning# No union map exists for ' + param.get('name') + ' in ' + parent.get('name')

    return RetVal

