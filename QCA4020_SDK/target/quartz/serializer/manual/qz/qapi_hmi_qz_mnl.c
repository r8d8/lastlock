/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 */
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

#include <string.h>
#include "idlist.h"
#include "qsCommon.h"
#include "qsQuartz.h"
#include "qsPack.h"
#include "qapi_hmi.h"
#include "qapi_hmi_common.h"
#include "qapi_hmi_qz_mnl.h"
#include "qapi_hmi_qz_cb.h"

#define HMI_MLME_GET_MAX_ATTRIBUTE_LENGTH (128)

SerStatus_t Mnl_Handle_qapi_HMI_MLME_Get_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   uint32_t           qsIndex;
   Boolean_t          qsPointerValid = FALSE;

   /* Create a temporary variable for the length of PIBAttributeValue. */
   uint32_t qsTmp_PIBAttributeLength = 0;
   UNUSED(qsPointerValid);
   UNUSED(qsIndex);

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   uint32_t Interface_ID;
   uint8_t PIBAttribute;
   uint8_t PIBAttributeIndex;
   uint8_t *PIBAttributeLength = NULL;
   uint8_t *PIBAttributeValue = NULL;
   uint8_t *Status = NULL;

   /* Pointers to the packed data packet. */
   HMI_Key_Descriptor_t            *HMI_Key_Descriptor;
   HMI_Device_Descriptor_t         *HMI_Device_Descriptor;
   HMI_Security_Level_Descriptor_t *HMI_Security_Level_Descriptor;

   /* Pointers to buffer holds the returned unpacked attribute value.
   */
   qapi_HMI_KeyDescriptor_t           *KeyDescriptor;
   qapi_HMI_DeviceDescriptor_t        *DeviceDescriptor;
   qapi_HMI_SecurityLevelDescriptor_t *SecuriyLevelDescriptor;

   uint8_t PackedAttributeValue[HMI_MLME_GET_MAX_ATTRIBUTE_LENGTH];

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   QSOSAL_MemInitialize(PackedAttributeValue, 0 , sizeof(PackedAttributeValue));

   /* Data from host is packed, unpack them before sending to M0. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Interface_ID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&PIBAttribute);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&PIBAttributeIndex);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      PIBAttributeLength = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

      if(PIBAttributeLength == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         /* *PIBAttributeLength represents the length of an unpacked structure.
         */
         qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)PIBAttributeLength);
      }
   }
   else
      PIBAttributeLength = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE) && (PIBAttributeLength != NULL))
   {
      /* Buffer to hold the unpacked attribute value is allocated. */
      PIBAttributeValue = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(*PIBAttributeLength)));

      if(PIBAttributeValue == NULL)
         qsResult = ssAllocationError;
   }
   else
      PIBAttributeValue= NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Status = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

      if(Status == NULL)
         qsResult = ssAllocationError;
   }
   else
      Status= NULL;

   if (PIBAttributeLength != NULL)
      qsTmp_PIBAttributeLength = *PIBAttributeLength;

   /* Call the QAPI function and handle the response. */
   if((qsResult == ssSuccess) && (Status != NULL))
   {
      /* Get the requested attrbiute with the buffer size specified by user. */
      qsRetVal = qapi_HMI_MLME_Get_Request(Interface_ID, PIBAttribute, PIBAttributeIndex, PIBAttributeLength, PIBAttributeValue, Status);

      /* The basic output buffer length. The output buffer will contain
         the length of packed attribue and the value of the packed attribute.
      */
      qsOutputLength = (4 + (PIBAttributeLength == NULL ? 0 : 1) + (Status == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 3));

      if((PIBAttributeLength != NULL) && (PIBAttributeValue != NULL))
      {
         if(((qsRetVal == QAPI_OK) && (*Status == QAPI_HMI_STATUS_CODE_SUCCESS)) || (qsRetVal == QAPI_ERR_BOUNDS))
         {
            /* The *PIBAttributeLength contains the actual length of unpacked
               attribute which will be updated to the length of the packed
               attribute. */
            switch(PIBAttribute)
            {
               case QAPI_HMI_PIB_MAC_KEY_TABLE:
                  if(*PIBAttributeLength == sizeof(qapi_HMI_KeyDescriptor_t))
                  {
                     *PIBAttributeLength = HMI_KEY_DESCRIPTOR_SIZE;
                  }
                  else
                  {
                     qsRetVal = QAPI_ERROR;
                  }
                  break;

               case QAPI_HMI_PIB_MAC_DEVICE_TABLE:
                  if(*PIBAttributeLength == sizeof(qapi_HMI_DeviceDescriptor_t))
                  {
                     *PIBAttributeLength = HMI_DEVICE_DESCRIPTOR_SIZE;
                  }
                  else
                  {
                     qsRetVal = QAPI_ERROR;
                  }
                  break;

               case QAPI_HMI_PIB_MAC_SECURITY_LEVEL_TABLE:
                  if(*PIBAttributeLength == sizeof(qapi_HMI_SecurityLevelDescriptor_t))
                  {
                     *PIBAttributeLength = HMI_SECURITY_LEVEL_DESCRIPTOR_SIZE;
                  }
                  else
                  {
                     qsRetVal = QAPI_ERROR;
                  }
                  break;

               default:
                  /* For none structured attribute there is no need to adjust
                     *PIBAttributeLength. */
                  break;
            }

            if((qsRetVal == QAPI_OK) && (*Status == QAPI_HMI_STATUS_CODE_SUCCESS))
            {
               /* Adjust the qsTmp_PIBAttributeLength. */
               qsTmp_PIBAttributeLength = *PIBAttributeLength;
            }
         }

         qsOutputLength = qsOutputLength + ((qsTmp_PIBAttributeLength)*(1));
      }

      /* Allocate the output buffer which will contain the packed data being
         sent to host side. */
      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_HMI, QAPI_HMI_FILE_ID, QAPI_HMI_MLME_GET_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Pack the data into output buffer. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)PIBAttributeLength);

         if((qsResult == ssSuccess) && (PIBAttributeLength != NULL))
         {
            qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)PIBAttributeLength);
         }

         if((qsResult == ssSuccess) && (PIBAttributeValue != NULL) && (PIBAttributeLength != NULL) && (qsRetVal == QAPI_OK) && (*Status == QAPI_HMI_STATUS_CODE_SUCCESS))
         {
            if(qsResult == ssSuccess)
               qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)PackedAttributeValue);

            if(qsResult == ssSuccess)
            {
               /* Pack the data in PIBAttributeValue into PIBAttributeValue. */
               switch(PIBAttribute)
               {
                  case QAPI_HMI_PIB_MAC_KEY_TABLE:
                     if(qsOutputLength > HMI_KEY_DESCRIPTOR_SIZE)
                     {
                        KeyDescriptor = (qapi_HMI_KeyDescriptor_t *)(PIBAttributeValue);
                        HMI_Key_Descriptor = (HMI_Key_Descriptor_t *)(PackedAttributeValue);

                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT64(&(HMI_Key_Descriptor->Source), KeyDescriptor->Source);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8(&(HMI_Key_Descriptor->IdMode), KeyDescriptor->IdMode);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8(&(HMI_Key_Descriptor->Index), KeyDescriptor->Index);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Key_Descriptor->FrameUsage), KeyDescriptor->FrameUsage);
                        QSOSAL_MemCopy_S(HMI_Key_Descriptor->Key, sizeof(HMI_Key_Descriptor->Key), KeyDescriptor->Key, sizeof(KeyDescriptor->Key));
                     }
                     else
                     {
                        qsResult = ssInvalidLength;
                     }
                     break;

                  case QAPI_HMI_PIB_MAC_DEVICE_TABLE:
                     if(qsOutputLength > HMI_DEVICE_DESCRIPTOR_SIZE)
                     {
                        DeviceDescriptor = (qapi_HMI_DeviceDescriptor_t *)(PIBAttributeValue);
                        HMI_Device_Descriptor = (HMI_Device_Descriptor_t *)(PackedAttributeValue);

                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT64(&(HMI_Device_Descriptor->ExtAddress), DeviceDescriptor->ExtAddress);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Device_Descriptor->ShortAddress), DeviceDescriptor->ShortAddress);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Device_Descriptor->PanId), DeviceDescriptor->PanId);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT32(&(HMI_Device_Descriptor->FrameCounter), DeviceDescriptor->FrameCounter);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8(&(HMI_Device_Descriptor->Flags), DeviceDescriptor->Flags);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8(&(HMI_Device_Descriptor->KeyTableIndex), DeviceDescriptor->KeyTableIndex);
                     }
                     else
                     {
                        qsResult = ssInvalidLength;
                     }
                     break;

                  case QAPI_HMI_PIB_MAC_SECURITY_LEVEL_TABLE:
                     if(qsOutputLength > HMI_SECURITY_LEVEL_DESCRIPTOR_SIZE)
                     {
                        SecuriyLevelDescriptor   = (qapi_HMI_SecurityLevelDescriptor_t *)(PIBAttributeValue);
                        HMI_Security_Level_Descriptor = (HMI_Security_Level_Descriptor_t *)(PackedAttributeValue);

                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Security_Level_Descriptor->FrameUsage), SecuriyLevelDescriptor->FrameUsage);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Security_Level_Descriptor->OverrideMask), SecuriyLevelDescriptor->OverrideMask);
                        WRITE_UNALIGNED_LITTLE_ENDIAN_UINT8(&(HMI_Security_Level_Descriptor->SecurityMinimum), SecuriyLevelDescriptor->SecurityMinimum);
                     }
                     else
                     {
                        qsResult = ssInvalidLength;
                     }
                     break;

                  default:
                     if(qsOutputLength > *PIBAttributeLength)
                     {
                        /* Just copy over the data for non strucutured attribute. */
                        QSOSAL_MemCopy_S((void *)PackedAttributeValue, *PIBAttributeLength, PIBAttributeValue, *PIBAttributeLength);
                     }
                     else
                     {
                        qsResult = ssInvalidLength;
                     }
                     break;
               }

               if(qsResult == ssSuccess)
               {
                  /* Write the PackedAttributeValue into the output buffer. */
                  qsResult = PackedWrite_Array(qsOutputBuffer, (void *)PackedAttributeValue, sizeof(uint8_t), qsTmp_PIBAttributeLength);
               }
            }
         }
         else
         {
            if(qsResult == ssSuccess)
            {
               qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)PIBAttributeValue);
            }

            if(qsResult == ssSuccess)
            {
               /* Write the PackedAttributeValue back to the output buffer. */
               qsResult = PackedWrite_Array(qsOutputBuffer, (void *)PIBAttributeValue, sizeof(uint8_t), qsTmp_PIBAttributeLength);
            }
         }

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Status);

         if((qsResult == ssSuccess) && (Status != NULL))
         {
            qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Status);
         }
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_HMI_MLME_Set_Request(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   uint32_t           qsIndex;
   Boolean_t          qsPointerValid = FALSE;

   UNUSED(qsPointerValid);
   UNUSED(qsIndex);

   /* Return value. */
   qapi_Status_t qsRetVal;

   /* Function parameters. */
   uint32_t Interface_ID;
   uint8_t PIBAttribute;
   uint8_t PIBAttributeIndex;
   uint8_t PIBAttributeLength;
   void *PIBAttributeValue = NULL;
   uint8_t *Status = NULL;

   HMI_Key_Descriptor_t            *HMI_Key_Descriptor;
   HMI_Device_Descriptor_t         *HMI_Device_Descriptor;
   HMI_Security_Level_Descriptor_t *HMI_Security_Level_Descriptor;

   union
   {
      void                               *Generic;
      qapi_HMI_KeyDescriptor_t           *KeyDescriptor;
      qapi_HMI_DeviceDescriptor_t        *DeviceDescriptor;
      qapi_HMI_SecurityLevelDescriptor_t *SecuriyLevelDescriptor;
   }QapiAttriValue;

   uint8_t UnpackedPIBAttributeLength;
   void    *UnpackedPIBValue = NULL;

   QapiAttriValue.Generic = NULL;
   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&Interface_ID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&PIBAttribute);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&PIBAttributeIndex);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&PIBAttributeLength);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      PIBAttributeValue = AllocateBufferListEntry(&qsBufferList, (1*(PIBAttributeLength)));

      if(PIBAttributeValue == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)PIBAttributeValue, 1, PIBAttributeLength);
      }
   }
   else
      PIBAttributeValue = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Status = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

      if(Status == NULL)
         qsResult = ssAllocationError;
   }
   else
      Status= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      /* Attribute ID, attribute index, attribute length and attribute data
         info had all been read out from the buffer at this point. But the
         attribute data may contain packed structed PIB data which should be
         unpacked before sending the set request. */
      switch(PIBAttribute)
      {
         case QAPI_HMI_PIB_MAC_KEY_TABLE:
            if(PIBAttributeLength == HMI_KEY_DESCRIPTOR_SIZE)
            {
               UnpackedPIBAttributeLength  = sizeof(qapi_HMI_KeyDescriptor_t);
               QapiAttriValue.KeyDescriptor = (qapi_HMI_KeyDescriptor_t *)QSOSAL_AllocateMemory(UnpackedPIBAttributeLength);
               if(QapiAttriValue.KeyDescriptor != NULL)
               {
                  HMI_Key_Descriptor = (HMI_Key_Descriptor_t *)(PIBAttributeValue);

                  QapiAttriValue.KeyDescriptor->Source     = READ_UNALIGNED_LITTLE_ENDIAN_UINT64(&(HMI_Key_Descriptor->Source));
                  QapiAttriValue.KeyDescriptor->IdMode     = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(&(HMI_Key_Descriptor->IdMode));
                  QapiAttriValue.KeyDescriptor->Index      = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(&(HMI_Key_Descriptor->Index));
                  QapiAttriValue.KeyDescriptor->FrameUsage = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Key_Descriptor->FrameUsage));
                  QSOSAL_MemCopy_S(QapiAttriValue.KeyDescriptor->Key, sizeof(QapiAttriValue.KeyDescriptor->Key), HMI_Key_Descriptor->Key, sizeof(HMI_Key_Descriptor->Key));

                  UnpackedPIBValue = (void *)(QapiAttriValue.KeyDescriptor);
               }
               else
               {
                  qsResult = ssFailure;
               }
            }
            else
            {
               qsResult = ssInvalidLength;
            }
            break;

         case QAPI_HMI_PIB_MAC_DEVICE_TABLE:
            if(PIBAttributeLength == HMI_DEVICE_DESCRIPTOR_SIZE)
            {
               UnpackedPIBAttributeLength     = sizeof(qapi_HMI_DeviceDescriptor_t);
               QapiAttriValue.DeviceDescriptor = (qapi_HMI_DeviceDescriptor_t *)QSOSAL_AllocateMemory(UnpackedPIBAttributeLength);
               if(QapiAttriValue.DeviceDescriptor != NULL)
               {
                  HMI_Device_Descriptor = (HMI_Device_Descriptor_t *)(PIBAttributeValue);

                  QapiAttriValue.DeviceDescriptor->ExtAddress    = READ_UNALIGNED_LITTLE_ENDIAN_UINT64(&(HMI_Device_Descriptor->ExtAddress));
                  QapiAttriValue.DeviceDescriptor->ShortAddress  = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Device_Descriptor->ShortAddress));
                  QapiAttriValue.DeviceDescriptor->PanId         = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Device_Descriptor->PanId));
                  QapiAttriValue.DeviceDescriptor->FrameCounter  = READ_UNALIGNED_LITTLE_ENDIAN_UINT32(&(HMI_Device_Descriptor->FrameCounter));
                  QapiAttriValue.DeviceDescriptor->Flags         = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Device_Descriptor->Flags));
                  QapiAttriValue.DeviceDescriptor->KeyTableIndex = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(&(HMI_Device_Descriptor->KeyTableIndex));

                  UnpackedPIBValue = (void *)(QapiAttriValue.DeviceDescriptor);
               }
               else
               {
                  qsResult = ssFailure;
               }
            }
            else
            {
               qsResult = ssInvalidLength;
            }
            break;

         case QAPI_HMI_PIB_MAC_SECURITY_LEVEL_TABLE:
            if(PIBAttributeLength == HMI_SECURITY_LEVEL_DESCRIPTOR_SIZE)
            {
               UnpackedPIBAttributeLength           = sizeof(qapi_HMI_SecurityLevelDescriptor_t);
               QapiAttriValue.SecuriyLevelDescriptor = (qapi_HMI_SecurityLevelDescriptor_t *)QSOSAL_AllocateMemory(UnpackedPIBAttributeLength);
               if(QapiAttriValue.SecuriyLevelDescriptor != NULL)
               {
                  HMI_Security_Level_Descriptor = (HMI_Security_Level_Descriptor_t *)(PIBAttributeValue);

                  QapiAttriValue.SecuriyLevelDescriptor->FrameUsage      = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Security_Level_Descriptor->FrameUsage));
                  QapiAttriValue.SecuriyLevelDescriptor->OverrideMask    = READ_UNALIGNED_LITTLE_ENDIAN_UINT16(&(HMI_Security_Level_Descriptor->OverrideMask));
                  QapiAttriValue.SecuriyLevelDescriptor->SecurityMinimum = READ_UNALIGNED_LITTLE_ENDIAN_UINT8(&(HMI_Security_Level_Descriptor->SecurityMinimum));

                  UnpackedPIBValue = (void *)(QapiAttriValue.SecuriyLevelDescriptor);
               }
               else
               {
                  qsResult = ssFailure;
               }
            }
            else
            {
               qsResult = ssInvalidLength;
            }
            break;

         default:
            /* No need to unpack the data with integer types. */
            UnpackedPIBValue           = PIBAttributeValue;
            UnpackedPIBAttributeLength = PIBAttributeLength;
            break;
      }

      if(qsResult == ssSuccess)
      {
         qsRetVal = qapi_HMI_MLME_Set_Request(Interface_ID, PIBAttribute, PIBAttributeIndex, UnpackedPIBAttributeLength, UnpackedPIBValue, Status);

         qsOutputLength = (4 + (Status == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

         if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_HMI, QAPI_HMI_FILE_ID, QAPI_HMI_MLME_SET_REQUEST_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
         {
            /* Write return value and/or output parameters packed. */
            if(qsResult == ssSuccess)
               qsResult = PackedWrite_32(qsOutputBuffer, (uint32_t *)&qsRetVal);

            if(qsResult == ssSuccess)
               qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)Status);

            if((qsResult == ssSuccess) && (Status != NULL))
            {
               qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)Status);
            }
         }
         else
         {
            qsResult = ssAllocationError;
         }
      }
   }

   if(QapiAttriValue.Generic != NULL)
   {
      QSOSAL_FreeMemory(QapiAttriValue.Generic);
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

