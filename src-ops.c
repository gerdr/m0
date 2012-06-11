#define M0_SOURCE
#include "m0.h"

// TODO

m0_opfunc *const M0_OP_FUNCS[M0_OPCOUNT_] = {
	__M0_OPS__
};

bool m0_ops_run(m0_interp *interp, m0_callframe *cf)
{
	assert((*interp)[M0_IPD_OP_FUNCS].as_cptr == M0_OP_FUNCS);

	for(;; cf = (*cf)[M0_REG_CF])
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
