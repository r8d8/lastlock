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
#include "qapi_ble.h"
#include "qsCommon.h"
#include "qsPack.h"
#include "qapi_ble_common.h"
#include "qapi_ble_bttypes_common.h"
#include "qapi_ble_btapityp_common.h"
#include "qapi_ble_hcicommt_common.h"
#include "qapi_ble_hcitypes_common.h"
#include "qapi_ble_hciusbt_common.h"
#include "qapi_ble_errors_common.h"
#include "qapi_ble_bsc_common.h"
#include "qapi_ble_hci_common.h"
#include "qapi_ble_l2cap_common.h"
#include "qapi_ble_gap_common.h"
#include "qapi_ble_gatt_common.h"
#include "qapi_ble_gatttype_common.h"
#include "qapi_ble_atttypes_common.h"
#include "qapi_ble_aios_common.h"
#include "qapi_ble_aiostypes_common.h"
#include "qapi_ble_ancs_common.h"
#include "qapi_ble_ancstypes_common.h"
#include "qapi_ble_ans_common.h"
#include "qapi_ble_anstypes_common.h"
#include "qapi_ble_bas_common.h"
#include "qapi_ble_bastypes_common.h"
#include "qapi_ble_bcs_common.h"
#include "qapi_ble_bcstypes_common.h"
#include "qapi_ble_bls_common.h"
#include "qapi_ble_blstypes_common.h"
#include "qapi_ble_bms_common.h"
#include "qapi_ble_bmstypes_common.h"
#include "qapi_ble_cgms_common.h"
#include "qapi_ble_cgmstypes_common.h"
#include "qapi_ble_cps_common.h"
#include "qapi_ble_cpstypes_common.h"
#include "qapi_ble_cscs_common.h"
#include "qapi_ble_cscstypes_common.h"
#include "qapi_ble_cts_common.h"
#include "qapi_ble_ctstypes_common.h"
#include "qapi_ble_dis_common.h"
#include "qapi_ble_distypes_common.h"
#include "qapi_ble_ess_common.h"
#include "qapi_ble_esstypes_common.h"
#include "qapi_ble_gaps_common.h"
#include "qapi_ble_gapstypes_common.h"
#include "qapi_ble_gls_common.h"
#include "qapi_ble_glstypes_common.h"
#include "qapi_ble_hids_common.h"
#include "qapi_ble_hidstypes_common.h"
#include "qapi_ble_hps_common.h"
#include "qapi_ble_hpstypes_common.h"
#include "qapi_ble_hrs_common.h"
#include "qapi_ble_hrstypes_common.h"
#include "qapi_ble_hts_common.h"
#include "qapi_ble_htstypes_common.h"
#include "qapi_ble_ias_common.h"
#include "qapi_ble_iastypes_common.h"
#include "qapi_ble_ips_common.h"
#include "qapi_ble_ipstypes_common.h"
#include "qapi_ble_ipsp_common.h"
#include "qapi_ble_ipsptypes_common.h"
#include "qapi_ble_lls_common.h"
#include "qapi_ble_llstypes_common.h"
#include "qapi_ble_lns_common.h"
#include "qapi_ble_lnstypes_common.h"
#include "qapi_ble_ots_common.h"
#include "qapi_ble_otstypes_common.h"
#include "qapi_ble_plxs_common.h"
#include "qapi_ble_plxstypes_common.h"
#include "qapi_ble_ndcs_common.h"
#include "qapi_ble_ndcstypes_common.h"
#include "qapi_ble_pass_common.h"
#include "qapi_ble_passtypes_common.h"
#include "qapi_ble_rscs_common.h"
#include "qapi_ble_rscstypes_common.h"
#include "qapi_ble_rtus_common.h"
#include "qapi_ble_rtustypes_common.h"
#include "qapi_ble_scps_common.h"
#include "qapi_ble_scpstypes_common.h"
#include "qapi_ble_slowp_common.h"
#include "qapi_ble_tps_common.h"
#include "qapi_ble_tpstypes_common.h"
#include "qapi_ble_trds_common.h"
#include "qapi_ble_trdstypes_common.h"
#include "qapi_ble_uds_common.h"
#include "qapi_ble_udstypes_common.h"
#include "qapi_ble_wss_common.h"
#include "qapi_ble_wsstypes_common.h"
