#define M0_SOURCE
#include "m0.h"

const m0_value M0_CONFIG[M0_CONFIGSZ_] = {
	[M0_CFG_REGSZ] = { sizeof (m0_value) },
	[M0_CFG_IREGSZ] = { sizeof (m0_int) },
	[M0_CFG_NREGSZ] = { sizeof (m0_num) },
	[M0_CFG_OPCODESZ] = { sizeof (m0_opcode) },
	[M0_CFG_PTRSZ] = { sizeof (void *) }
};
