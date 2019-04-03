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
#include "qapi_ble.h"
#include "qapi_ble_hci_common.h"
#include "qapi_ble_hci_qz_mnl.h"
#include "qapi_ble_hci_qz_cb.h"

SerStatus_t Mnl_Handle_qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   uint32_t           qsIndex;
   Boolean_t          qsPointerValid = FALSE;
   uint8_t            Scanning_PHYS_Count;

   UNUSED(qsPointerValid);
   UNUSED(qsIndex);

   /* Return value. */
   int qsRetVal;

   /* Function parameters. */
   uint32_t BluetoothStackID;
   uint8_t Own_Address_Type;
   uint8_t Scanning_Filter_Policy;
   uint8_t Scanning_PHYS;
   uint8_t *Scan_Type = NULL;
   uint16_t *Scan_Interval = NULL;
   uint16_t *Scan_Window = NULL;
   uint8_t *StatusResult = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Own_Address_Type);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Scanning_Filter_Policy);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Scanning_PHYS);

   /* Scanning_PHYS is a bit mask so we need to get the actual number of PHYs
      so we correctly calculate the array length.*/
   Scanning_PHYS_Count = 0;
   if(Scanning_PHYS & (uint8_t)QAPI_BLE_HCI_LE_SCANNING_PHYS_1M_PHY)
   {
      Scanning_PHYS_Count++;
   }

   if(Scanning_PHYS & (uint8_t)QAPI_BLE_HCI_LE_SCANNING_PHYS_CODED_PHY)
   {
      Scanning_PHYS_Count++;
   }

   /* Make sure there is at least one PHY specified. */
   if(!Scanning_PHYS_Count)
   {
      qsResult = ssFailure;
   }

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Scan_Type = AllocateBufferListEntry(&qsBufferList, (sizeof(uint8_t)*(Scanning_PHYS_Count)));

      if(Scan_Type == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Type, sizeof(uint8_t), Scanning_PHYS_Count);
      }
   }
   else
      Scan_Type = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Scan_Interval = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Scanning_PHYS_Count)));

      if(Scan_Interval == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Interval, sizeof(uint16_t), Scanning_PHYS_Count);
      }
   }
   else
      Scan_Interval = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Scan_Window = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Scanning_PHYS_Count)));

      if(Scan_Window == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Window, sizeof(uint16_t), Scanning_PHYS_Count);
      }
   }
   else
      Scan_Window = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

      if(StatusResult == NULL)
         qsResult = ssAllocationError;
   }
   else
      StatusResult= NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters(BluetoothStackID, Own_Address_Type, Scanning_Filter_Policy, Scanning_PHYS, Scan_Type, Scan_Interval, Scan_Window, StatusResult);

      qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_SET_EXTENDED_SCAN_PARAMETERS_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
            qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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

SerStatus_t Mnl_Handle_qapi_BLE_HCI_LE_Extended_Create_Connection(uint8_t *qsBuffer, uint16_t qsLength, PackedBuffer_t *qsOutputBuffer, uint8_t *uId)
{
   SerStatus_t        qsResult = ssSuccess;
   BufferListEntry_t *qsBufferList = NULL;
   PackedBuffer_t     qsInputBuffer;
   uint32_t           qsOutputLength;
   uint32_t           qsIndex;
   Boolean_t          qsPointerValid = FALSE;
   uint8_t            Initiating_PHYS_Count;

   UNUSED(qsPointerValid);
   UNUSED(qsIndex);

   /* Return value. */
   int qsRetVal;

   /* Function parameters. */
   uint32_t BluetoothStackID;
   uint8_t Initiating_Filter_Policy;
   uint8_t Own_Address_Type;
   uint8_t Peer_Address_Type;
   qapi_BLE_BD_ADDR_t *Peer_Address = NULL;
   uint8_t Initiating_PHYS;
   uint16_t *Scan_Interval = NULL;
   uint16_t *Scan_Window = NULL;
   uint16_t *Conn_Interval_Min = NULL;
   uint16_t *Conn_Interval_Max = NULL;
   uint16_t *Conn_Latency = NULL;
   uint16_t *Supervision_Timeout = NULL;
   uint16_t *Minimum_CE_Length = NULL;
   uint16_t *Maximum_CE_Length = NULL;
   uint8_t *StatusResult = NULL;

   InitializePackedBuffer(&qsInputBuffer, qsBuffer, qsLength);

   /* Read function parameters. */
   if(qsResult == ssSuccess)
      qsResult = PackedRead_32(&qsInputBuffer, &qsBufferList, (uint32_t *)&BluetoothStackID);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Initiating_Filter_Policy);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Own_Address_Type);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Peer_Address_Type);

   if(qsResult == ssSuccess)
      qsResult = PackedRead_8(&qsInputBuffer, &qsBufferList, (uint8_t *)&Initiating_PHYS);

   /* Initiating_PHYS is a bit mask so we need to get the actual number of PHYs
      so we correctly calculate the array length.*/
   Initiating_PHYS_Count = 0;
   if(Initiating_PHYS & (uint8_t)QAPI_BLE_HCI_LE_INITIATING_PHY_1M_PHY)
   {
      Initiating_PHYS_Count++;
   }

   if(Initiating_PHYS & (uint8_t)QAPI_BLE_HCI_LE_INITIATING_PHY_2M_PHY)
   {
      Initiating_PHYS_Count++;
   }

   if(Initiating_PHYS & (uint8_t)QAPI_BLE_HCI_LE_INITIATING_PHY_CODED_PHY)
   {
      Initiating_PHYS_Count++;
   }

   /* Make sure there is at least one PHY specified. */
   if(!Initiating_PHYS_Count)
   {
      qsResult = ssFailure;
   }

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Scan_Interval = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Initiating_PHYS_Count)));

      if(Scan_Interval == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Interval, sizeof(uint16_t), Initiating_PHYS_Count);
      }
   }
   else
      Scan_Interval = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Scan_Window = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Initiating_PHYS_Count)));

      if(Scan_Window == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Scan_Window, sizeof(uint16_t), Initiating_PHYS_Count);
      }
   }
   else
      Scan_Window = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Conn_Interval_Min = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Initiating_PHYS_Count)));

      if(Conn_Interval_Min == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Conn_Interval_Min, sizeof(uint16_t), Initiating_PHYS_Count);
      }
   }
   else
      Conn_Interval_Min = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Conn_Interval_Max = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Initiating_PHYS_Count)));

      if(Conn_Interval_Max == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Conn_Interval_Max, sizeof(uint16_t), Initiating_PHYS_Count);
      }
   }
   else
      Conn_Interval_Max = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Conn_Latency = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Initiating_PHYS_Count)));

      if(Conn_Latency == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Conn_Latency, sizeof(uint16_t), Initiating_PHYS_Count);
      }
   }
   else
      Conn_Latency = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Supervision_Timeout = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Initiating_PHYS_Count)));

      if(Supervision_Timeout == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Supervision_Timeout, sizeof(uint16_t), Initiating_PHYS_Count);
      }
   }
   else
      Supervision_Timeout = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Minimum_CE_Length = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Initiating_PHYS_Count)));

      if(Minimum_CE_Length == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Minimum_CE_Length, sizeof(uint16_t), Initiating_PHYS_Count);
      }
   }
   else
      Minimum_CE_Length = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Maximum_CE_Length = AllocateBufferListEntry(&qsBufferList, (sizeof(uint16_t)*(Initiating_PHYS_Count)));

      if(Maximum_CE_Length == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_Array(&qsInputBuffer, &qsBufferList, (void *)Maximum_CE_Length, sizeof(uint16_t), Initiating_PHYS_Count);
      }
   }
   else
      Maximum_CE_Length = NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      StatusResult = AllocateBufferListEntry(&qsBufferList, sizeof(uint8_t));

      if(StatusResult == NULL)
         qsResult = ssAllocationError;
   }
   else
      StatusResult= NULL;

   if(qsResult == ssSuccess)
      qsResult = PackedRead_PointerHeader(&qsInputBuffer, &qsBufferList, &qsPointerValid);

   if((qsResult == ssSuccess) && (qsPointerValid == TRUE))
   {
      Peer_Address = AllocateBufferListEntry(&qsBufferList, sizeof(qapi_BLE_BD_ADDR_t));

      if(Peer_Address == NULL)
      {
         qsResult = ssAllocationError;
      }
      else
      {
         qsResult = PackedRead_qapi_BLE_BD_ADDR_t(&qsInputBuffer, &qsBufferList, (qapi_BLE_BD_ADDR_t *)Peer_Address);
      }
   }
   else
      Peer_Address = NULL;

   /* Call the QAPI function and handle the response. */
   if(qsResult == ssSuccess)
   {
      qsRetVal = qapi_BLE_HCI_LE_Extended_Create_Connection(BluetoothStackID, Initiating_Filter_Policy, Own_Address_Type, Peer_Address_Type, Peer_Address, Initiating_PHYS, Scan_Interval, Scan_Window, Conn_Interval_Min, Conn_Interval_Max, Conn_Latency, Supervision_Timeout, Minimum_CE_Length, Maximum_CE_Length, StatusResult);

      qsOutputLength = (4 + (StatusResult == NULL ? 0 : 1) + (QS_POINTER_HEADER_SIZE * 1));

      if(AllocatePackedBuffer(uId, QS_RETURN_E, MODULE_BLE, QAPI_BLE_HCI_FILE_ID, QAPI_BLE_HCI_LE_EXTENDED_CREATE_CONNECTION_FUNCTION_ID, qsOutputBuffer, qsOutputLength))
      {
         /* Write return value and/or output parameters packed. */
         if(qsResult == ssSuccess)
            qsResult = PackedWrite_int(qsOutputBuffer, (int *)&qsRetVal);

         if(qsResult == ssSuccess)
            qsResult = PackedWrite_PointerHeader(qsOutputBuffer, (void *)StatusResult);

         if((qsResult == ssSuccess) && (StatusResult != NULL))
         {
            qsResult = PackedWrite_8(qsOutputBuffer, (uint8_t *)StatusResult);
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
