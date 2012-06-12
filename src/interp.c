#define M0_SOURCE
#include "m0.h"

#include <stdlib.h>

static const m0_config CONFIG;
const m0_interp M0_INTERP;

#ifndef __cplusplus

static const m0_config CONFIG = { {
	[M0_CFG_M0V].as_uint = M0_VERSION,
	[M0_CFG_ENDIANNESS].as_uint = M0_ENDIANNESS,
	[M0_CFG_REGSZ].as_uword = M0_REGSZ,
	[M0_CFG_CFMAXSZ].as_uword = M0_CFMAXSZ,
	[M0_CFG_INTSZ].as_uword = M0_INTSZ,
	[M0_CFG_NUMSZ].as_uword = M0_NUMSZ,
	[M0_CFG_OPSZ].as_uword = M0_OPSZ,
	[M0_CFG_PTRSZ].as_uword = M0_PTRSZ,
} };

const m0_interp M0_INTERP = { {
	[M0_IPD_OP_FUNCS].as_cptr = M0_OP_FUNCS,
	[M0_IPD_CONFIG].as_cptr = CONFIG.data,
} };

#else

m0_config_::m0_config_() {
	data[M0_CFG_M0V].as_uint = M0_VERSION;
	data[M0_CFG_ENDIANNESS].as_uint = M0_ENDIANNESS;
	data[M0_CFG_REGSZ].as_uword = M0_REGSZ;
	data[M0_CFG_CFMAXSZ].as_uword = M0_CFMAXSZ;
	data[M0_CFG_INTSZ].as_uword = M0_INTSZ;
	data[M0_CFG_NUMSZ].as_uword = M0_NUMSZ;
	data[M0_CFG_OPSZ].as_uword = M0_OPSZ;
	data[M0_CFG_PTRSZ].as_uword = M0_PTRSZ;
}

m0_interp_::m0_interp_() {
	data[M0_IPD_OP_FUNCS].as_cptr = M0_OP_FUNCS;
	data[M0_IPD_CONFIG].as_cptr = CONFIG.data;
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

bool m0_interp_reserve_chunks(m0_interp *interp, size_t count)
{
	size_t load = m0_interp_chunk_count(interp) + count;
	assert(load >= count);

	size_t size = next_greater_pow2(load);
	assert(size != 0);

	m0_chunk *chunks = m0_interp_chunks(interp);
	chunks = (m0_chunk *)realloc(chunks, size * sizeof *chunks);
	if(!chunks) return 0;

	m0_interp_set_chunks(interp, chunks);

	return 1;
}

void m0_interp_push_reserved_chunk(m0_interp *interp,
	const m0_segment *constants, const m0_segment *metadata,
	const m0_segment *bytecode)
{
	size_t count = m0_interp_chunk_count(interp);
	m0_chunk *chunk = m0_interp_chunks(interp) + count;

	chunk->constants = constants;
	chunk->metadata = metadata;
	chunk->bytecode = bytecode;

	m0_interp_set_chunk_count(interp, count + 1);
}

bool m0_interp_push_chunk(m0_interp *interp,
	const m0_segment *constants, const m0_segment *metadata,
	const m0_segment *bytecode)
{
	size_t count = m0_interp_chunk_count(interp);
	m0_chunk *chunks = m0_interp_chunks(interp);

	if(is_pow2z(count + 1))
	{
		chunks = (m0_chunk *)realloc(chunks, (count + 1) * 2 * sizeof *chunks);
		if(!chunks) return 0;

		m0_interp_set_chunks(interp, chunks);
	}

	chunks[count].constants = constants;
	chunks[count].metadata = metadata;
	chunks[count].bytecode = bytecode;

	m0_interp_set_chunk_count(interp, count + 1);

	return 1;
}
