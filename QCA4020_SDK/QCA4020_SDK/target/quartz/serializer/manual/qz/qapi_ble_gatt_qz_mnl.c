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

#include <stdlib.h>
#include <string.h>
#include "idlist.h"
#include "qsCommon.h"
#include "qsQuartz.h"
#include "qsPack.h"
#include "qsPersist.h"
#include "qapi_ble.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_gatt_qz_mnl.h"
#include "qapi_ble_gatt_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_BLE_GATT_Register_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t                              qsResult = ssSuccess;
   BufferListEntry_t                       *qsBufferList = NULL;
   PackedBuffer_t                           qsInputBuffer;
   uint32_t                                 qsOutputLength;
   uint32_t                                 qsIndex;
   Boolean_t                                qsPointerValid = FALSE;
   PersistInfo_t                            PersistInfo;
   uint32_t                                 PersistHandle;
   qapi_BLE_GATT_Service_Attribute_Entry_t *PersistServiceTable = NULL;

   /* Return value.                                                     */
   int qsRetVal;

   /* Function parameters.                                              */
   uint32_t BluetoothStackID;
   uint8_t ServiceFlags;
   uint32_t NumberOfServiceAttributeEntries;
   qapi_BLE_GATT_Service_Attribute_Entry_t *ServiceTable = NULL;
   qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleGroupResult = NULL;
   uint32_t CallbackParameter;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&ServiceFlags);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&NumberOfServiceAttributeEntries);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&CallbackParameter);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      ServiceTable = AllocateBufferListEntry(&qsBufferList, (sizeof(qapi_BLE_GATT_Service_Attribute_Entry_t)*(NumberOfServiceAttributeEntries)));

      if(ServiceTable == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         for (qsIndex = 0; (qsResult == ssSuccess) && (qsIndex < NumberOfServiceAttributeEntries); qsIndex++)
         {
            qsResult = PackedRead_qapi_BLE_GATT_Service_Attribute_Entry_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GATT_Service_Attribute_Entry_t*)&ServiceTable[qsIndex]);
         }
      }
   }
   else
      ServiceTable = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      ServiceHandleGroupResult = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

      if(ServiceHandleGroupResult == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_GATT_Attribute_Handle_Group_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_GATT_Attribute_Handle_Group_t*)ServiceHandleGroupResult);
      }
   }
   else
      ServiceHandleGroupResult = NULL;

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      /* Alloctate memory to hold the service table since it needs to   */
      /* persist.                                                       */
      /* * NOTE * The buffer list will be freed when this function      */
      /*          returns.                                              */
      if((PersistServiceTable = QSOSAL_AllocateMemory((sizeof(qapi_BLE_GATT_Service_Attribute_Entry_t) * NumberOfServiceAttributeEntries))) != NULL)
      {
         /* Allocate memory for all sub structures.                     */
         for (qsIndex = 0; (qsResult == ssSuccess) && (qsIndex < NumberOfServiceAttributeEntries); qsIndex++)
         {
            PersistServiceTable[qsIndex].Attribute_Flags      = ServiceTable[qsIndex].Attribute_Flags;
            PersistServiceTable[qsIndex].Attribute_Entry_Type = ServiceTable[qsIndex].Attribute_Entry_Type;

            /* Use the attribute entry type to determine how to allocate*/
            /* memory for the attribute value.                          */
            switch(ServiceTable[qsIndex].Attribute_Entry_Type)
            {
               case QAPI_BLE_AET_PRIMARY_SERVICE_16_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Primary_Service_16_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Primary_Service_16_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Primary_Service_16_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_PRIMARY_SERVICE_128_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Primary_Service_128_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Primary_Service_128_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Primary_Service_128_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_SECONDARY_SERVICE_16_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Secondary_Service_16_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Secondary_Service_16_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Secondary_Service_16_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_SECONDARY_SERVICE_128_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Secondary_Service_128_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Secondary_Service_128_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Secondary_Service_128_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_INCLUDE_DEFINITION_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Include_Definition_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Include_Definition_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Include_Definition_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_16_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Characteristic_Declaration_16_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Characteristic_Declaration_16_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Characteristic_Declaration_16_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_128_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Characteristic_Declaration_128_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Characteristic_Declaration_128_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Characteristic_Declaration_128_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_CHARACTERISTIC_VALUE_16_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Characteristic_Value_16_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     /* * NOTE * This is a shallow copy.                */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Characteristic_Value_16_Entry_t));

                     /* Check if the characteristic value is valid.     */
                     if((((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value))
                     {
                        /* Allocate memory for the characteristic value.*/
                        if((((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value = QSOSAL_AllocateMemory(((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length)) != NULL)
                        {
                           /* Format the characteristic value.          */
                           QSOSAL_MemCopy(((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value,
                                          ((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value,
                                          ((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length);
                        }
                        else
                           qsResult = ssAllocationError;
                     }
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_CHARACTERISTIC_VALUE_128_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Characteristic_Value_128_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     /* * NOTE * This is a shallow copy.                */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Characteristic_Value_128_Entry_t));

                     /* Check if the characteristic value is valid.     */
                     if((((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value))
                     {
                        /* Allocate memory for the characteristic value.*/
                        if((((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value = QSOSAL_AllocateMemory(((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length)) != NULL)
                        {
                           /* Format the characteristic value.          */
                           QSOSAL_MemCopy(((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value,
                                          ((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value,
                                          ((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length);
                        }
                        else
                           qsResult = ssAllocationError;
                     }
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_16_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     /* * NOTE * This is a shallow copy.                */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t));

                     /* Check if the characteristic descriptor value is */
                     /* valid.                                          */
                     if((((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor))
                     {
                        /* Allocate memory for the characteristic value.*/
                        if((((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor = QSOSAL_AllocateMemory(((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length)) != NULL)
                        {
                           /* Format the characteristic value.          */
                           QSOSAL_MemCopy(((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor,
                                          ((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor,
                                          ((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length);
                        }
                        else
                           qsResult = ssAllocationError;
                     }
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_128_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     /* * NOTE * This is a shallow copy.                */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t));

                     /* Check if the characteristic descriptor value is */
                     /* valid.                                          */
                     if((((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor))
                     {
                        /* Allocate memory for the characteristic value.*/
                        if((((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor = QSOSAL_AllocateMemory(((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length)) != NULL)
                        {
                           /* Format the characteristic value.          */
                           QSOSAL_MemCopy(((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor,
                                          ((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor,
                                          ((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length);
                        }
                        else
                           qsResult = ssAllocationError;
                     }
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_PRIMARY_SERVICE_32_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Primary_Service_32_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Primary_Service_32_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Primary_Service_32_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_SECONDARY_SERVICE_32_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Secondary_Service_32_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Secondary_Service_32_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Secondary_Service_32_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_32_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Characteristic_Declaration_32_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Characteristic_Declaration_32_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Characteristic_Declaration_32_Entry_t));
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_CHARACTERISTIC_VALUE_32_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Characteristic_Value_32_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     /* * NOTE * This is a shallow copy.                */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Characteristic_Value_32_Entry_t));

                     /* Check if the characteristic value is valid.     */
                     if((((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value))
                     {
                        /* Allocate memory for the characteristic value.*/
                        if((((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value = QSOSAL_AllocateMemory(((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length)) != NULL)
                        {
                           /* Format the characteristic value.          */
                           QSOSAL_MemCopy(((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value,
                                          ((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value,
                                          ((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length);
                        }
                        else
                           qsResult = ssAllocationError;
                     }
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
               case QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_32_E:
                  /* Allocate memory for the attribute value.           */
                  if((PersistServiceTable[qsIndex].Attribute_Value = (qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)QSOSAL_AllocateMemory(sizeof(qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t))) != NULL)
                  {
                     /* Format the attribute value.                     */
                     /* * NOTE * This is a shallow copy.                */
                     QSOSAL_MemCopy(PersistServiceTable[qsIndex].Attribute_Value, ServiceTable[qsIndex].Attribute_Value, sizeof(qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t));

                     /* Check if the characteristic descriptor value is */
                     /* valid.                                          */
                     if((((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor))
                     {
                        /* Allocate memory for the characteristic value.*/
                        if((((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor = QSOSAL_AllocateMemory(((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length)) != NULL)
                        {
                           /* Format the characteristic value.          */
                           QSOSAL_MemCopy(((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor,
                                          ((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor,
                                          ((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)PersistServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length);
                        }
                        else
                           qsResult = ssAllocationError;
                     }
                  }
                  else
                     qsResult = ssAllocationError;
                  break;
            }
         }
      }

      if(qsResult == ssSuccess)
      {
         qsRetVal = qapi_BLE_GATT_Register_Service(BluetoothStackID, ServiceFlags, NumberOfServiceAttributeEntries, PersistServiceTable, ServiceHandleGroupResult, QZ_qapi_BLE_GATT_Server_Event_Callback_t_Handler, CallbackParameter);

         if(qsRetVal > 0)
         {
            /* NOTE * We do not need this, but it is returned by the    */
            /*          Persist_Register() function.                    */
            PersistHandle = 0;

            /* Format the persist info.                                 */
            /* * NOTE * We won't store the actual length of the service */
            /*          table since we only need to know the number of  */
            /*          attribute entries to free the service table.    */
            PersistInfo.ModuleID      = QS_MODULE_BLE;
            PersistInfo.FileID        = QAPI_BLE_GATT_FILE_ID;
            PersistInfo.FunctionID    = QAPI_BLE_GATT_REGISTER_SERVICE_FUNCTION_ID;
            PersistInfo.PersistKey    = (uint32_t)qsRetVal;
            PersistInfo.AppDataLength = NumberOfServiceAttributeEntries;
            PersistInfo.AppData       = PersistServiceTable;

            qsResult = Persist_Register(&PersistHandle, &PersistInfo);
         }

         if(qsResult == ssSuccess)
         {
            qsOutputLength = (4 + (CalcPackedSize_qapi_BLE_GATT_Attribute_Handle_Group_t((qapi_BLE_GATT_Attribute_Handle_Group_t *)ServiceHandleGroupResult)) + (QS_POINTER_HEADER_SIZE * 1));

            if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GATT_FILE_ID, QAPI_BLE_GATT_REGISTER_SERVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
            {
               /* Write return value and/or output parameters packed.   */
               if(qsResult == ssSuccess)
                  qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

               if(qsResult == ssSuccess)
                  qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)ServiceHandleGroupResult);

               if(qsResult == ssSuccess)
               {
                  qsResult = PackedWrite_qapi_BLE_GATT_Attribute_Handle_Group_t(qsOutputBuffer, (qapi_BLE_GATT_Attribute_Handle_Group_t*)ServiceHandleGroupResult);
               }

            }
            else
            {
               qsResult = ssAllocationError;
            }
         }
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}

SerStatus_t Mnl_Handle_qapi_BLE_GATT_Un_Register_Service(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t                              qsResult = ssSuccess;
   BufferListEntry_t                       *qsBufferList = NULL;
   PackedBuffer_t                           qsInputBuffer;
   uint32_t                                 qsOutputLength;
   PersistInfo_t                            PersistInfo;
   uint32_t                                 qsIndex;
   qapi_BLE_GATT_Service_Attribute_Entry_t *ServiceTable = NULL;

   /* Function parameters.                                              */
   uint32_t BluetoothStackID;
   uint32_t ServiceID;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters.                                         */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&ServiceID);

   /* Call the QAPI function and handle the response.                   */
   if(qsResult == ssSuccess)
   {
      qapi_BLE_GATT_Un_Register_Service(BluetoothStackID, ServiceID);

      /* Initialize the persist info. */
      memset(&PersistInfo, 0, sizeof(PersistInfo));

      /* Cleanup persistent memory for service table.                   */
      /* * NOTE * This function should NOT fail so we will assume       */
      /*          success.                                              */
      qsResult = Persist_RetrieveByKey(QS_MODULE_BLE, QAPI_BLE_GATT_FILE_ID, QAPI_BLE_GATT_REGISTER_SERVICE_FUNCTION_ID, ServiceID, &PersistInfo);
      if(qsResult == ssSuccess)
      {
         if(PersistInfo.AppData)
         {
            /* Store a pointer to the service table.                    */
            ServiceTable = (qapi_BLE_GATT_Service_Attribute_Entry_t *)(PersistInfo.AppData);

            /* Free all the memory for attribute entries.               */
            for (qsIndex = 0; (qsResult == ssSuccess) && (qsIndex < PersistInfo.AppDataLength); qsIndex++)
            {
               /* Use the attribute entry type to determine how to      */
               /* allocate memory for the attribute value.              */
               switch(ServiceTable[qsIndex].Attribute_Entry_Type)
               {
                  case QAPI_BLE_AET_PRIMARY_SERVICE_16_E:
                  case QAPI_BLE_AET_PRIMARY_SERVICE_32_E:
                  case QAPI_BLE_AET_PRIMARY_SERVICE_128_E:
                  case QAPI_BLE_AET_SECONDARY_SERVICE_16_E:
                  case QAPI_BLE_AET_SECONDARY_SERVICE_32_E:
                  case QAPI_BLE_AET_SECONDARY_SERVICE_128_E:
                  case QAPI_BLE_AET_INCLUDE_DEFINITION_E:
                  case QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_16_E:
                  case QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_32_E:
                  case QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_128_E:
                     /* Intentional fall-through since only the         */
                     /* attribute value needs to be freed.              */
                     QSOSAL_FreeMemory(ServiceTable[qsIndex].Attribute_Value);
                     break;
                  case QAPI_BLE_AET_CHARACTERISTIC_VALUE_16_E:
                     /* Check if the characteristic value is valid.     */
                     if((((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value))
                     {
                        /* Free the characteristic value.               */
                        QSOSAL_FreeMemory(((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value);
                     }

                     /* Free the attribute value.                       */
                     QSOSAL_FreeMemory(ServiceTable[qsIndex].Attribute_Value);
                     break;
                  case QAPI_BLE_AET_CHARACTERISTIC_VALUE_128_E:
                     /* Check if the characteristic value is valid.     */
                     if((((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value))
                     {
                        /* Free the characteristic value.               */
                        QSOSAL_FreeMemory(((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value);
                     }

                     /* Free the attribute value.                       */
                     QSOSAL_FreeMemory(ServiceTable[qsIndex].Attribute_Value);
                     break;
                  case QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_16_E:
                     /* Check if the characteristic value is valid.     */
                     if((((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor))
                     {
                        /* Free the characteristic value.               */
                        QSOSAL_FreeMemory(((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor);
                     }

                     /* Free the attribute value.                       */
                     QSOSAL_FreeMemory(ServiceTable[qsIndex].Attribute_Value);
                     break;
                  case QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_128_E:
                     /* Check if the characteristic value is valid.     */
                     if((((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor))
                     {
                        /* Free the characteristic value.               */
                        QSOSAL_FreeMemory(((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor);
                     }

                     /* Free the attribute value.                       */
                     QSOSAL_FreeMemory(ServiceTable[qsIndex].Attribute_Value);
                     break;
                  case QAPI_BLE_AET_CHARACTERISTIC_VALUE_32_E:
                     /* Check if the characteristic value is valid.     */
                     if((((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value))
                     {
                        /* Free the characteristic value.               */
                        QSOSAL_FreeMemory(((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Value);
                     }

                     /* Free the attribute value.                       */
                     QSOSAL_FreeMemory(ServiceTable[qsIndex].Attribute_Value);
                     break;
                  case QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_32_E:
                     /* Check if the characteristic value is valid.     */
                     if((((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor_Length) &&
                        (((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor))
                     {
                        /* Free the characteristic value.               */
                        QSOSAL_FreeMemory(((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)ServiceTable[qsIndex].Attribute_Value)->Characteristic_Descriptor);
                     }

                     /* Free the attribute value.                       */
                     QSOSAL_FreeMemory(ServiceTable[qsIndex].Attribute_Value);
                     break;
               }
            }

            /* Free the service table.                                  */
            QSOSAL_FreeMemory(ServiceTable);
         }

         Persist_UnregisterByKey(QS_MODULE_BLE, QAPI_BLE_GATT_FILE_ID, QAPI_BLE_GATT_REGISTER_SERVICE_FUNCTION_ID, ServiceID);
      }

      qsOutputLength = 0;

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_GATT_FILE_ID, QAPI_BLE_GATT_UN_REGISTER_SERVICE_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed.         */
      }
      else
      {
         qsResult = ssAllocationError;
      }
   }

   FreeBufferList(&qsBufferList);

   return(qsResult);
}
