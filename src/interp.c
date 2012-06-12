#define M0_SOURCE
#include "m0.h"

#include <stdlib.h>

static const m0_config CONFIG;
const m0_interp M0_INTERP;

#ifndef __cplusplus

static const m0_config CONFIG = { {
	[M0_CFG_M0V].as_quad = M0_VERSION,
	[M0_CFG_REGSZ].as_uword = M0_REGSZ,
	[M0_CFG_CFMAXSZ].as_uword = M0_CFMAXSZ,
	[M0_CFG_INTSZ].as_uword = M0_INTSZ,
	[M0_CFG_NUMSZ].as_uword = M0_NUMSZ,
	[M0_CFG_OPSZ].as_uword = M0_OPSZ,
	[M0_CFG_PTRSZ].as_uword = M0_PTRSZ,
	[M0_CFG_ENDIANNESS].as_uint = M0_ENDIANNESS
} };

const m0_interp M0_INTERP = { {
	[M0_IPD_OP_FUNCS].as_cptr = M0_OP_FUNCS,
	[M0_IPD_CONFIG].as_cptr = CONFIG.data,
} };

#else

m0_interp_::m0_interp_() {
	data[M0_IPD_OP_FUNCS].as_cptr = M0_OP_FUNCS;
	data[M0_IPD_CONFIG].as_cptr = CONFIG.data;
}

m0_config_::m0_config_() {
	data[M0_CFG_M0V].as_quad = M0_VERSION;
	data[M0_CFG_REGSZ].as_uword = M0_REGSZ;
	data[M0_CFG_CFMAXSZ].as_uword = M0_CFMAXSZ;
	data[M0_CFG_INTSZ].as_uword = M0_INTSZ;
	data[M0_CFG_NUMSZ].as_uword = M0_NUMSZ;
	data[M0_CFG_OPSZ].as_uword = M0_OPSZ;
	data[M0_CFG_PTRSZ].as_uword = M0_PTRSZ;
	data[M0_CFG_ENDIANNESS].as_uint = M0_ENDIANNESS;
}

#endif

m0_callframe *m0_interp_alloc_cf(m0_interp *interp, size_t size)
{
	assert(size >= M0_REGCOUNT);

	m0_callframe *cf = (m0_callframe *)calloc(size, M0_REGSZ);
	if(!cf) return NULL;

	m0_reg_set_cf(cf, cf);
	m0_reg_set_interp(cf, interp);

	return cf;
}
