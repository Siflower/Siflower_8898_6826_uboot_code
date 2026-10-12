#ifndef _SF_NPU_TABLE_
#define _SF_NPU_TABLE_

#include "se/se_common.h"
#include "se/l2_se.h"
#include "se/l3_se.h"
#include "se/arp_se.h"
#include "se/nat_se.h"
#include "se/ivlan_se.h"
#include "se/evlan_se.h"
#include "se/spl_se.h"


void nat_test(int rule_index, int oport, int vid, int dnat_flag, Sekey* key, Sersp* rsp);

#endif // end _SF_NPU_TABLE_
