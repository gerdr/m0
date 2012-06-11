#define M0_SOURCE
#include "m0.h"

#include <stdio.h>

static inline void op_noop(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_goto(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_goto_if(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_goto_chunk(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_add_i(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_add_n(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_sub_i(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_sub_n(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_mult_i(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_mult_n(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_div_i(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_div_n(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_mod_i(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_mod_n(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_isgt_i(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_isgt_n(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_isge_i(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_isge_n(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_convert_i_n(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_convert_n_i(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_ashr(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_lshr(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_shl(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_and(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_or(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_xor(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_gc_alloc(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_sys_alloc(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_sys_free(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_copy_mem(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_set(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_set_imm(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_deref(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_set_ref(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_set_byte(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_get_byte(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_set_word(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_get_word(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_csym(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_ccall_arg(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_ccall_ret(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_ccall(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_print_s(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_print_i(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_print_n(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}

static inline void op_exit(
	m0_callframe *cf, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
	(void)cf, (void)arg1, (void)arg2, (void)arg3;
	assert(!"NOT IMPLEMENTED");
}


m0_opfunc *const M0_OP_FUNCS[M0_OPCOUNT] = {
	__M0_OPS__
};

bool m0_ops_run(m0_interp *interp, m0_callframe *cf)
{
	assert(m0_interp_op_funcs(interp) == M0_OP_FUNCS);

	for(;; cf = m0_reg_cf(cf))
	{
		const m0_chunk *chunk = m0_interp_chunks(interp) + m0_reg_chunk(cf);
		const m0_op *ops = chunk->bytecode_segment->blocks;
		size_t opcount = chunk->bytecode_segment->entry_count;
		size_t pc = m0_reg_pc(cf);

		if(pc >= opcount)
			return 0;

		m0_op op = ops[pc];
		size_t opcode = op & 0xFF;
		uint8_t arg1 = (uint8_t)(op >>  8);
		uint8_t arg2 = (uint8_t)(op >> 16);
		uint8_t arg3 = (uint8_t)(op >> 24);

		if(opcode >= M0_OPCOUNT)
		{
			fprintf(stderr, "unknown opcode 0x%X", (unsigned)opcode);
			return 0;
		}

		M0_OP_FUNCS[opcode](cf, arg1, arg2, arg3);
	}
}
