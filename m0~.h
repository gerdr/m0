#ifndef M0_H_
#define M0_H_

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include <stdint.h>
#include <stdio.h>

enum
{
	M0_VERSION = __M0_VERSION__,
	M0_ENDIANNESS = __M0_ENDIANNESS__,
	M0_OPSZ = sizeof (__M0_OP_TYPE__),
	M0_INTSZ = sizeof (__M0_INT_TYPE__),
	M0_NUMSZ = sizeof (__M0_NUM_TYPE__),
	M0_REGSZ = sizeof (__M0_VALUE_TYPE__),
	M0_PTRSZ = sizeof (void *),
	M0_CFMAXSZ = 256 * M0_REGSZ
};

enum
{
	__M0_OPS__
	M0_OPCOUNT
};

enum
{
	__M0_IPD__
	M0_INTERPSZ
};

enum
{
	__M0_CFG__
	M0_CONFIGSZ
};

enum
{
	__M0_REG__
	M0_REGCOUNT
};

typedef __M0_OP_TYPE__ m0_op;
typedef __M0_INT_TYPE__ m0_int;
typedef __M0_UINT_TYPE__ m0_uint;
typedef __M0_NUM_TYPE__ m0_num;

typedef union m0_value_ m0_value;
union m0_value_
{
	__M0_VALUE_TYPE__ bits;
	uint8_t bytes[M0_REGSZ];
	m0_int as_int;
	m0_uint as_uint;
	m0_num as_num;
	void *as_ptr;
	const void *as_cptr;
	ptrdiff_t as_word;
	size_t as_uword;
};

typedef struct m0_interp_ m0_interp;
struct m0_interp_
{
	m0_value data[M0_INTERPSZ];
#ifdef __cplusplus
	m0_interp_();
#endif
};

typedef struct m0_config_ m0_config;
struct m0_config_
{
	m0_value data[M0_CONFIGSZ];
#ifdef __cplusplus
	m0_config_();
#endif
};

typedef m0_value m0_callframe[];

typedef struct m0_mobheader_ m0_mobheader;
struct m0_mobheader_
{
	uint8_t magic[3];
	uint8_t version[1];
	uint8_t config[4];
	uint32_t size;
};

typedef struct m0_object_ m0_object;
struct m0_object_
{
	uint32_t id;
	uint32_t byte_size;
};

typedef struct m0_string_ m0_string;
struct m0_string_
{
	uint32_t id;
	uint32_t byte_size;
	uint8_t bytes[];
};

typedef struct m0_segment_ m0_segment;
struct m0_segment_
{
	uint32_t id;
	uint32_t byte_size;
	uint32_t entry_count;
	uint32_t blocks[];
};

typedef struct m0_direntry_ m0_direntry;
struct m0_direntry_
{
	uint32_t id;
	uint32_t byte_size;
	uint32_t const_offset;
	uint32_t meta_offset;
	uint32_t code_offset;
	uint32_t blocks[];
};

typedef struct m0_chunk_ m0_chunk;
struct m0_chunk_
{
	const m0_string *name;
	const m0_segment *constants;
	const m0_segment *metadata;
	const m0_segment *bytecode;
};

union m0_aliasinghack_
{
	m0_object object_;
	m0_segment segment_;
	m0_string string_;
	m0_direntry direntry_;
};

typedef void m0_opfunc(m0_callframe *, uint8_t, uint8_t, uint8_t);

extern const m0_interp M0_INTERP;
extern m0_opfunc *const M0_OP_FUNCS[M0_OPCOUNT];

#ifdef __cplusplus
extern "C" {
#endif

extern void *m0_platform_mmap_file_private(const char *name, size_t *size);
extern bool m0_platform_munmap(void *block, size_t size);

extern bool m0_mob_load(m0_interp *interp, const char *name, FILE *err);

extern bool m0_ops_run(m0_interp *interp, m0_callframe *cf);

extern m0_callframe *m0_interp_alloc_cf(m0_interp *interp, size_t size);
extern bool m0_interp_init_chunk_map(
	m0_interp *interp, size_t size, uint32_t seed);
extern size_t m0_interp_chunk_map_size(const m0_interp *interp);
extern bool m0_interp_reserve_chunk_map_slots(m0_interp *interp, size_t count);
extern bool m0_interp_reserve_chunks(m0_interp *interp, size_t count);
extern size_t m0_interp_push_reserved_chunk(
	m0_interp *interp, const m0_chunk *chunk);
extern bool m0_interp_register_reserved_chunk(
	m0_interp *interp, const m0_string *name, size_t chunk_id);
extern bool m0_interp_push_chunk(m0_interp *interp, const m0_chunk *chunk);

#ifdef __cplusplus
}
#endif

__M0_IPD_FUNCS__
__M0_REG_FUNCS__
#ifdef M0_SOURCE

#include <assert.h>
#include <limits.h>

static inline size_t is_pow2z(size_t size)
{
	return (size & (size - 1)) == 0;
}

static inline size_t next_greater_pow2(size_t size)
{
	enum { SIZE_BIT = CHAR_BIT * sizeof (size_t) };

	for(unsigned exp = 0; (1 << exp) < SIZE_BIT; ++exp)
		size |= size >> (1 << exp);

	return size + 1;
}

#endif

#endif
