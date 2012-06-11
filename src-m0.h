#ifndef M0_H_
#define M0_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define M0_VERSION __M0_VERSION__

enum
{
	M0_OPSZ = sizeof (__M0_OP_TYPE__),
	M0_INTSZ = sizeof (__M0_INT_TYPE__),
	M0_NUMSZ = sizeof (__M0_NUM_TYPE__),
	M0_REGSZ = sizeof (__M0_VALUE_TYPE__),
	M0_PTRSZ = sizeof (void *),
	M0_CFMAXSZ = 256 * M0_REGSZ,
	M0_ENDIANNESS = __M0_ENDIANNESS__
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
	uint32_t as_quad;
};

typedef m0_value m0_interp[M0_INTERPSZ];
typedef m0_value m0_callframe[];

typedef struct m0_mob_header_ m0_mob_header;
struct m0_mob_header_
{
	uint8_t format[8];
	uint32_t version;
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

typedef struct m0_symbol_ m0_symbol;
struct m0_symbol_
{
	uint32_t id;
	uint32_t byte_size;
	uint32_t hash;
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

typedef struct m0_chunk_ m0_chunk;
struct m0_chunk_
{
	const m0_symbol *name;
	const m0_segment *constants_segment;
	const m0_segment *metadata_segment;
	const m0_segment *bytecode_segment;
};

union m0_aliasing_hack_
{
	m0_object as_object;
	m0_segment as_segment;
	m0_string as_string;
	m0_symbol as_symbol;
};

typedef void m0_opfunc(m0_callframe *, uint8_t, uint8_t, uint8_t);

extern const m0_interp M0_INTERP;
extern m0_opfunc *const M0_OP_FUNCS[M0_OPCOUNT];

extern void *m0_platform_mmap_file_private(const char *name, size_t *size);
extern bool m0_platform_munmap(void *block, size_t size);

extern bool m0_mob_verify_header(const m0_mob_header *header);

extern bool m0_ops_run(m0_interp *interp, m0_callframe *cf);

__M0_IPD_FUNCS__
__M0_REG_FUNCS__
#ifdef M0_SOURCE
#include <assert.h>
#endif

#endif
