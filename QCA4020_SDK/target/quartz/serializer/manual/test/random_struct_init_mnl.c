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

#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "qapi_ble.h"
#include "qapi_zb.h"
#include "qapi_hmi.h"
#include "qapi_coex.h"
#include "qapi_twn.h"
#include "qapi_HERH.h"
#include "random_struct_init.h"

#define TEST_STRING "This is a test string."

void Mnl_GenerateRandom_qapi_BLE_AIOS_Characteristic_Data_t(qapi_BLE_AIOS_Characteristic_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      memset(Ptr, 0, sizeof(qapi_BLE_AIOS_Characteristic_Data_t));
   }
}

void Mnl_GenerateRandom_qapi_BLE_ANCS_App_Attribute_Data_t(qapi_BLE_ANCS_App_Attribute_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_ANCS_App_Attribute_Data_t));

      /* Format the structure fields.                                   */
      Ptr->AttributeID   = (qapi_BLE_ANCS_App_Attribute_ID_t)rand();
      Ptr->AttributeData = (uint8_t *)AllocateBufferListEntry(BufferList, (strlen(TEST_STRING) + 1));

      /* * NOTE * NULL is a valid value for the attribute data.         */
      if(Ptr->AttributeData != NULL)
      {
         /* Store the test string.                                      */
         strcpy_s(Ptr->AttributeData, (strlen(TEST_STRING) + 1), TEST_STRING);
      }
   }
}

void Mnl_GenerateRandom_qapi_BLE_ANCS_Attribute_Data_t(qapi_BLE_ANCS_Attribute_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_ANCS_Attribute_Data_t));

      /* Format the structure fields.                                   */
      /* * NOTE * Union members are both enumerations so we just need to*/
      /*          randomize one of them since they align.               */
      Ptr->Type                       = (qapi_BLE_ANCS_Attribute_Data_Type_t)rand();
      Ptr->AttributeID.AppAttributeID = (qapi_BLE_ANCS_App_Attribute_ID_t)rand();
      Ptr->AttributeData              = (uint8_t *)AllocateBufferListEntry(BufferList, (strlen(TEST_STRING) + 1));

      /* * NOTE * NULL is a valid value for the attribute data.         */
      if(Ptr->AttributeData != NULL)
      {
         /* Store the test string.                                      */
         strcpy_s(Ptr->AttributeData, (strlen(TEST_STRING) + 1), TEST_STRING);
      }
   }
}

void Mnl_GenerateRandom_qapi_BLE_CGMS_RACP_Format_Data_t(qapi_BLE_CGMS_RACP_Format_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_CGMS_RACP_Format_Data_t));

      /* Format the structure fields.                                   */
      /* * NOTE * We will randomize the largest member of the union     */
      /*          (TimeOffsetRange).                                    */
      Ptr->CommandType = (uint8_t)(rand());
      Ptr->OperatorType = (uint8_t)(rand());
      Ptr->FilterType = (uint8_t)(rand());
      Ptr->FilterParameters.TimeOffsetRange.Minimum = (uint16_t)(rand());
      Ptr->FilterParameters.TimeOffsetRange.Maximum = (uint16_t)(rand());
   }
}

void Mnl_GenerateRandom_qapi_BLE_ESS_ES_Trigger_Setting_Data_t(qapi_BLE_ESS_ES_Trigger_Setting_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_ESS_ES_Trigger_Setting_Data_t));

      /* Format the structure fields.                                   */
      /* * NOTE * We will randomize the largest member of the union     */
      /*          (Pressure).                                           */
      Ptr->Condition        = (qapi_BLE_ESS_ES_Trigger_Setting_Condition_t)(rand());
      Ptr->Operand.Pressure = (uint32_t)(rand());
   }
}

void Mnl_GenerateRandom_qapi_BLE_ESS_Characteristic_Data_t(qapi_BLE_ESS_Characteristic_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      memset(Ptr, 0, sizeof(qapi_BLE_ESS_Characteristic_Data_t));
   }
}

void Mnl_GenerateRandom_qapi_BLE_GAP_LE_Authentication_Response_Information_t(qapi_BLE_GAP_LE_Authentication_Response_Information_t *Ptr, BufferListEntry_t **BufferList)
{
   unsigned int Index;

   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_GAP_LE_Authentication_Response_Information_t));

      /* Format the structure fields.                                   */
      Ptr->GAP_LE_Authentication_Type = (qapi_BLE_GAP_LE_Authentication_Response_Type_t)(rand());
      Ptr->Authentication_Data_Length = (uint8_t)(rand());

      for(Index = 0; Index < sizeof(Ptr->Authentication_Data); Index++)
      {
         ((uint8_t *)&(Ptr->Authentication_Data))[Index] = (uint8_t)(rand());
      }
   }
}

void Mnl_GenerateRandom_qapi_BLE_GAP_LE_Authentication_Event_Data_t(qapi_BLE_GAP_LE_Authentication_Event_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   unsigned int Index;

   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_GAP_LE_Authentication_Event_Data_t));

      /* Format the structure fields.                                   */
      Ptr->GAP_LE_Authentication_Event_Type = (qapi_BLE_GAP_LE_Authentication_Event_Type_t)(rand());
      GenerateRandom_qapi_BLE_BD_ADDR_t(&(Ptr->BD_ADDR), BufferList);

      for(Index = 0; Index < sizeof(Ptr->Authentication_Event_Data); Index++)
      {
         ((uint8_t *)&(Ptr->Authentication_Event_Data))[Index] = (uint8_t)(rand());
      }
   }
}

void Mnl_GenerateRandom_qapi_BLE_GATT_Service_Attribute_Entry_t(qapi_BLE_GATT_Service_Attribute_Entry_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_GATT_Service_Attribute_Entry_t));

      /* Format the structure fields.                                   */
      Ptr->Attribute_Flags      = (uint8_t)(rand());
      Ptr->Attribute_Entry_Type = (qapi_BLE_GATT_Service_Attribute_Entry_Type_t)(rand());
      //xxx may not be used
      Ptr->Attribute_Value      = NULL;
   }
}

void Mnl_GenerateRandom_qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t(qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   unsigned int Index;

   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_GLS_Record_Access_Control_Point_Format_Data_t));

      /* Format the structure fields.                                   */
      Ptr->CommandType  = (qapi_BLE_GLS_RACP_Command_Type_t)(rand());
      Ptr->OperatorType = (qapi_BLE_GLS_RACP_Operator_Type_t)(rand());
      Ptr->FilterType   = (qapi_BLE_GLS_RACP_Filter_Type_t)(rand());

      for(Index = 0; Index < sizeof(Ptr->FilterParameters); Index++)
      {
         ((uint8_t *)&(Ptr->FilterParameters))[Index] = (uint8_t)(rand());
      }
   }
}

void Mnl_GenerateRandom_qapi_BLE_OTS_OACP_Response_Data_t(qapi_BLE_OTS_OACP_Response_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   unsigned int Index;

   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_OTS_OACP_Response_Data_t));

      /* Format the structure fields.                                   */
      Ptr->Request_Op_Code = (qapi_BLE_OTS_OACP_Request_Type_t)(rand());
      Ptr->Result_Code     = (qapi_BLE_OTS_OACP_Result_Type_t)(rand());

      for(Index = 0; Index < sizeof(Ptr->Parameter); Index++)
      {
         ((uint8_t *)&(Ptr->Parameter))[Index] = (uint8_t)(rand());
      }
   }
}

void Mnl_GenerateRandom_qapi_BLE_OTS_OLCP_Response_Data_t(qapi_BLE_OTS_OLCP_Response_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   unsigned int Index;

   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_OTS_OLCP_Response_Data_t));

      /* Format the structure fields.                                   */
      Ptr->Request_Op_Code = (qapi_BLE_OTS_OLCP_Request_Type_t)(rand());
      Ptr->Result_Code     = (qapi_BLE_OTS_OLCP_Result_Type_t)(rand());

      for(Index = 0; Index < sizeof(Ptr->Parameter); Index++)
      {
         ((uint8_t *)&(Ptr->Parameter))[Index] = (uint8_t)(rand());
      }
   }
}

void Mnl_GenerateRandom_qapi_BLE_UDS_User_Control_Point_Request_Data_t(qapi_BLE_UDS_User_Control_Point_Request_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   unsigned int Index;

   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_UDS_User_Control_Point_Request_Data_t));

      /* Format the structure fields.                                   */
      Ptr->Op_Code = (qapi_BLE_UDS_User_Control_Point_Request_Type_t)(rand());

      for(Index = 0; Index < sizeof(Ptr->Parameter); Index++)
      {
         ((uint8_t *)&(Ptr->Parameter))[Index] = (uint8_t)(rand());
      }
   }
}

void Mnl_GenerateRandom_qapi_BLE_UDS_User_Control_Point_Response_Data_t(qapi_BLE_UDS_User_Control_Point_Response_Data_t *Ptr, BufferListEntry_t **BufferList)
{
   unsigned int Index;

   if((Ptr != NULL) && (BufferList != NULL))
   {
      /* Initialize the structure.                                      */
      memset(Ptr, 0, sizeof(qapi_BLE_UDS_User_Control_Point_Response_Data_t));

      /* Format the structure fields.                                   */
      Ptr->Request_Op_Code     = (qapi_BLE_UDS_User_Control_Point_Request_Type_t)(rand());
      Ptr->Response_Code_Value = (qapi_BLE_UDS_User_Control_Point_Response_Value_t)(rand());

      for(Index = 0; Index < sizeof(Ptr->Parameter); Index++)
      {
         ((uint8_t *)&(Ptr->Parameter))[Index] = (uint8_t)(rand());
      }
   }
}

void Mnl_GenerateRandom_qapi_BLE_UDS_Characteristic_t(qapi_BLE_UDS_Characteristic_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      memset(Ptr, 0, sizeof(qapi_BLE_UDS_Characteristic_t));
   }
}

void Mnl_GenerateRandom_qapi_ZB_CL_Cluster_Info_t(qapi_ZB_CL_Cluster_Info_t *Ptr, BufferListEntry_t **BufferList)
{
   qapi_ZB_CL_Attribute_t *AttrList;

   if((Ptr != NULL) && (BufferList != NULL))
   {
      memset(Ptr, 0, sizeof(qapi_ZB_CL_Cluster_Info_t));
      Ptr->Endpoint = (uint8_t)(rand());
      Ptr->AttributeCount = (uint8_t)((rand() % 512));
      AttrList = (qapi_ZB_CL_Attribute_t *)AllocateBufferListEntry(BufferList, (sizeof(qapi_ZB_CL_Attribute_t) * Ptr->AttributeCount));
      if(AttrList != NULL)
      {
         for(unsigned int Index=0;Index<(unsigned int)Ptr->AttributeCount;Index++)
         {
            GenerateRandom_qapi_ZB_CL_Attribute_t(&(AttrList[Index]), BufferList);
         }
         Ptr->AttributeList = AttrList;
      }
   }
}

void Mnl_GenerateRandom_qapi_ZB_CL_Read_Attr_Status_Record_t(qapi_ZB_CL_Read_Attr_Status_Record_t *Ptr, BufferListEntry_t **BufferList)
{
   uint8_t *ValueBuffer;
   if((Ptr != NULL) && (BufferList != NULL))
   {
      memset(Ptr, 0, sizeof(qapi_ZB_CL_Read_Attr_Status_Record_t));
      Ptr->Status = (qapi_Status_t)(rand());
      Ptr->AttrId = (uint16_t)(rand());
      memset(&(Ptr->DataType), 0xA5, sizeof(qapi_ZB_CL_Data_Type_t));
      Ptr->AttrLength = (uint16_t)((rand() % 512));
      ValueBuffer = (uint8_t *)AllocateBufferListEntry(BufferList, (sizeof(uint8_t) * Ptr->AttrLength));
      if(ValueBuffer != NULL)
      {
         for(unsigned int Index=0;Index<(unsigned int)Ptr->AttrLength;Index++)
         {
            ValueBuffer[Index] = (uint8_t)(rand());
         }
      }
      Ptr->AttrValue = ValueBuffer;
   }
}

void Mnl_GenerateRandom_qapi_ZB_ZGP_Key_Request_t(qapi_ZB_ZGP_Key_Request_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      memset(Ptr, 0, sizeof(qapi_ZB_ZGP_Key_Request_t));
      Ptr->ApplicationId = (uint8_t)(rand());
      Ptr->GPDId = (uint64_t)(rand());
      Ptr->EndPoint = (uint8_t)(rand());
      Ptr->SecurityLevel = (uint8_t)(rand());
      memset(&(Ptr->KeyType), 0xA5, sizeof(qapi_ZB_ZGP_Security_Key_t));
      Ptr->Key = (uint8_t *)AllocateBufferListEntry(BufferList, QAPI_ZB_KEY_SIZE);
      if(Ptr->Key != NULL)
      {
         for(unsigned int Index=0;Index<QAPI_ZB_KEY_SIZE;Index++)
         {
            Ptr->Key[Index] = (uint8_t)(rand());
         }
      }
   }
}

void Mnl_GenerateRandom_qapi_HMI_PAN_Descriptor_t(qapi_HMI_PAN_Descriptor_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      memset(Ptr, 0, sizeof(qapi_HMI_PAN_Descriptor_t));
      Ptr->CoordAddrMode = (uint8_t)(rand());
      Ptr->CoordPANId = (uint16_t)(rand());
      /*Memset union.*/
      memset(&(Ptr->CoordAddress), 0xA5, sizeof(qapi_HMI_Link_Layer_Address_t));
      Ptr->LogicalChannel = (uint8_t)(rand());
      Ptr->ChannelPage = (uint8_t)(rand());
      Ptr->SuperframeSpec.BeaconOrder = (uint8_t)(rand());
      Ptr->SuperframeSpec.SuperframeOrder = (uint8_t)(rand());
      Ptr->SuperframeSpec.FinalCAPSlot = (uint8_t)(rand());
      Ptr->SuperframeSpec.BatteryLifeExtension = (qbool_t)(rand());
      Ptr->SuperframeSpec.PANCoordinator = (qbool_t)(rand());
      Ptr->SuperframeSpec.AssociationPermit = (qbool_t)(rand());
      Ptr->GTSPermit = (qbool_t)(rand());
      Ptr->LinkQuality = (uint8_t)(rand());
      Ptr->RSSI = (int8_t)(rand());
      Ptr->Timestamp = (uint32_t)(rand());
      Ptr->SecurityFailure = (uint8_t)(rand());
      GenerateRandom_qapi_HMI_Security_t(&(Ptr->Security), BufferList);
   }
}

void Mnl_GenerateRandom_qapi_HMI_MLME_Beacon_Notify_Indication_t(qapi_HMI_MLME_Beacon_Notify_Indication_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      memset(Ptr, 0, sizeof(qapi_HMI_MLME_Beacon_Notify_Indication_t));
      Ptr->BSN = (uint8_t)(rand());
      GenerateRandom_qapi_HMI_PAN_Descriptor_t(&(Ptr->PANDescriptor), BufferList);
      Ptr->NumShortAddr = (uint8_t)(rand());
      Ptr->NumExtendAddr = (uint8_t)((rand() % 512));
      Ptr->SDULength = (uint8_t)((rand() % 512));
     ((qapi_HMI_Link_Layer_Address_t*)(Ptr->AddrList)) = (qapi_HMI_Link_Layer_Address_t *)AllocateBufferListEntry(BufferList, (sizeof(qapi_HMI_Link_Layer_Address_t)* (Ptr->NumShortAddr + Ptr->NumExtendAddr)));
      if(((qapi_HMI_Link_Layer_Address_t*)(Ptr->AddrList)) != NULL)
      {
         for(unsigned int Index=0;Index<(unsigned int)(Ptr->NumExtendAddr + Ptr->NumExtendAddr) ;Index++)
         {
            /*Memset union.*/
            memset(&(((qapi_HMI_Link_Layer_Address_t*)(Ptr->AddrList))[Index]), 0xA5, sizeof(qapi_HMI_Link_Layer_Address_t));
         }
      }
      ((uint8_t*)(Ptr->SDU)) = (uint8_t *)AllocateBufferListEntry(BufferList, (sizeof(uint8_t) * Ptr->SDULength));
      if(((uint8_t*)(Ptr->SDU)) != NULL)
      {
         for(unsigned int Index=0;Index<(unsigned int)Ptr->SDULength;Index++)
         {
            ((uint8_t*)(Ptr->SDU))[Index] = (uint8_t)(rand());
         }
      }
   }
}

void Mnl_GenerateRandom_qapi_TWN_IPv6_Prefix_t(qapi_TWN_IPv6_Prefix_t *Ptr, BufferListEntry_t **BufferList)
{
   if((Ptr != NULL) && (BufferList != NULL))
   {
      memset(Ptr, 0, sizeof(qapi_TWN_IPv6_Prefix_t));
      /*Memset union.*/
      memset(&(Ptr->Address), 0xA5, sizeof(qapi_TWN_IPv6_Address_t));
      Ptr->Length = (uint8_t)(rand());
   }
}

