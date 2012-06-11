#define M0_SOURCE
#include "m0.h"

// TODO

m0_opfunc *const M0_OP_FUNCS[M0_OPCOUNT_] = {
	__M0_OPS__
};

bool m0_ops_run(m0_interp *interp, m0_callframe *cf)
{
	assert(m0_interp_op_funcs(interp) == M0_OP_FUNCS);

	for(;; cf = m0_reg_cf(cf))
	{
		const m0_chunk *chunk = m0_interp_chunks(interp) + m0_reg_chunk(cf);
		const m0_op *ops = chunk->bytecode_segment->blocks;
		uint32_t opcount = chunk->bytecode_segment->entry_count;
		m0_uword pc = m0_reg_pc(cf);

		if(pc >= opcount)
			return 0;

		m0_op op = ops[pc];
		// TODO: execute op
	}

}
