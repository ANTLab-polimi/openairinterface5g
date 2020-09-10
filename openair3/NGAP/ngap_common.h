/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/** @defgroup _ngap_impl_ NGAP Layer Reference Implementation
 * @ingroup _ref_implementation_
 * @{
 */

#if HAVE_CONFIG_H_
# include "config.h"
#endif

#ifndef NGAP_COMMON_H_
#define NGAP_COMMON_H_


#include "common/utils/LOG/log.h"
/* replace ASN_DEBUG defined in asn_internal.h by oai tracing system
   Would be cleaner to modify asn_internal.h but it seems to come
   from non oai source, with BSD license, so prefer to do that here..
*/
#ifdef ASN_DEBUG
# undef ASN_DEBUG
#endif
#define ASN_DEBUG( x... )  LOG_I(ASN, x)

#include "NGAP_ProtocolIE-Field.h"
#include "NGAP_NGAP-PDU.h"
#include "NGAP_InitiatingMessage.h"
#include "NGAP_SuccessfulOutcome.h"
#include "NGAP_UnsuccessfulOutcome.h"
#include "NGAP_ProtocolIE-Field.h"
#include "NGAP_ProtocolIE-FieldPair.h"
#include "NGAP_ProtocolIE-ContainerPair.h"
#include "NGAP_ProtocolExtensionField.h"
#include "NGAP_ProtocolExtensionContainer.h"
#include "NGAP_asn_constant.h"
#include "NGAP_SupportedTAs-Item.h"
#include "NGAP_ServedGUAMIsItem.h"

/* Checking version of ASN1C compiler */
#if (ASN1C_ENVIRONMENT_VERSION < ASN1C_MINIMUM_VERSION)
# error "You are compiling ngap with the wrong version of ASN1C"
#endif

#ifndef FALSE
# define FALSE (0)
#endif
#ifndef TRUE
# define TRUE  (!FALSE)
#endif

#define NGAP_UE_ID_FMT  "0x%06"PRIX32

extern int asn_debug;
extern int asn1_xer_print;

#if defined(ENB_MODE)
# include "common/utils/LOG/log.h"
# include "ngap_eNB_default_values.h"
# define NGAP_ERROR(x, args...) LOG_E(NGAP, x, ##args)
# define NGAP_WARN(x, args...)  LOG_W(NGAP, x, ##args)
# define NGAP_TRAF(x, args...)  LOG_I(NGAP, x, ##args)
# define NGAP_INFO(x, args...) LOG_I(NGAP, x, ##args)
# define NGAP_DEBUG(x, args...) LOG_I(NGAP, x, ##args)
#else
# include "amf_default_values.h"
# define NGAP_ERROR(x, args...) do { fprintf(stdout, "[NGAP][E]"x, ##args); } while(0)
# define NGAP_WARN(x, args...)  do { fprintf(stdout, "[NGAP][W]"x, ##args); } while(0)
# define NGAP_TRAF(x, args...)  do { fprintf(stdout, "[NGAP][T]"x, ##args); } while(0)
# define NGAP_INFO(x, args...) do { fprintf(stdout, "[NGAP][I]"x, ##args); } while(0)
# define NGAP_DEBUG(x, args...) do { fprintf(stdout, "[NGAP][D]"x, ##args); } while(0)
#endif


#define NGAP_FIND_PROTOCOLIE_BY_ID(IE_TYPE, ie, container, IE_ID, mandatory) \
  do {\
    IE_TYPE **ptr; \
    ie = NULL; \
    for (ptr = container->protocolIEs.list.array; \
         ptr < &container->protocolIEs.list.array[container->protocolIEs.list.count]; \
         ptr++) { \
      if((*ptr)->id == IE_ID) { \
        ie = *ptr; \
        break; \
      } \
    } \
    if (ie == NULL ) { \
      NGAP_ERROR("NGAP_FIND_PROTOCOLIE_BY_ID: %s %d: ie is NULL\n",__FILE__,__LINE__);\
    } \
    if (mandatory)  DevAssert(ie != NULL); \
  } while(0)
/** \brief Function callback prototype.
 **/
typedef int (*ngap_message_decoded_callback)(
    uint32_t         assoc_id,
    uint32_t         stream,
    NGAP_NGAP_PDU_t *pdu
);

/** \brief Handle criticality
 \param criticality Criticality of the IE
 @returns void
 **/
void ngap_handle_criticality(NGAP_Criticality_t criticality);

#endif /* NGAP_COMMON_H_ */