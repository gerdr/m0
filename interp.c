#define M0_SOURCE
#include "m0.h"

static const m0_value CONFIG[M0_CONFIGSZ] = {
	[M0_CFG_M0V].as_quad = M0_VERSION,
	[M0_CFG_REGSZ].as_uword = M0_REGSZ,
	[M0_CFG_CFMAXSZ].as_uword = M0_CFMAXSZ,
	[M0_CFG_INTSZ].as_uword = M0_INTSZ,
	[M0_CFG_NUMSZ].as_uword = M0_NUMSZ,
	[M0_CFG_OPSZ].as_uword = M0_OPSZ,
	[M0_CFG_PTRSZ].as_uword = M0_PTRSZ,
	[M0_CFG_ENDIANNESS].as_uint = M0_ENDIANNESS
};

const m0_interp M0_INTERP = {
	[M0_IPD_OP_FUNCS].as_cptr = M0_OP_FUNCS,
	[M0_IPD_CONFIG].as_cptr = CONFIG,
};
