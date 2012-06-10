#ifndef M0_H_
#define M0_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define M0_VERSION __M0_VERSION__

enum
{
	M0_OPCODESZ = sizeof (__M0_OPCODE__),
	M0_INTSZ = sizeof (__M0_INT__),
	M0_NUMSZ = sizeof (__M0_NUM__),
	M0_VALUESZ = sizeof (__M0_VALUE__),
	M0_PTRSZ = sizeof (void *)
};

enum
{
	__M0_OPS__
	M0_OPCOUNT_
};

enum
{
	__M0_IPD__
	M0_INTERPSZ_
};

enum
{
	__M0_CFG__
	M0_CONFIGSZ_
};

enum
{
	__M0_REG__
};

typedef __M0_OPCODE__ m0_opcode;
typedef __M0_INT__ m0_int;
typedef __M0_UINT__ m0_uint;
typedef __M0_NUM__ m0_num;

typedef union m0_value_ m0_value;
union m0_value_
{
	__M0_VALUE__ bits;
	uint8_t bytes[M0_VALUESZ];
	m0_int as_int;
	m0_uint as_uint;
	m0_num as_num;
	void *as_ptr;
	const void *as_cptr;
	intptr_t as_word;
	uintptr_t as_uword;
};

typedef m0_value m0_interp[M0_INTERPSZ_];
typedef m0_value m0_callframe[];

typedef struct m0_string_ m0_string;
struct m0_string_
{
	uint32_t flags;
	uint32_t size;
	uint8_t bytes;
};

typedef struct m0_symbol_ m0_symbol;
struct m0_symbol_
{
	uint32_t flags;
	uint32_t size;
	uint32_t hash;
	uint8_t bytes;
};

#ifdef M0_SOURCE

#include <assert.h>

extern const m0_value M0_CONFIG[M0_CONFIGSZ_];

extern void *m0_platform_mmap_file_private(const char *name);
extern bool m0_platform_munmap(void *block, size_t size);

#endif

#endif
