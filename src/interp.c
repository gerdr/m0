#define M0_SOURCE
#include "m0.h"
#include "murmur3.h"

#include <stdlib.h>

struct bucket
{
	uint32_t hash;
	uint32_t chunk_id;
};

struct map
{
	uint8_t *index;
	uint32_t mask;
	uint32_t seed;
	union { struct bucket as_single, *as_multiple; } buckets[];
};

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

size_t m0_interp_push_reserved_chunk(m0_interp *interp, const m0_chunk *chunk)
{
	size_t count = m0_interp_chunk_count(interp);
	m0_chunk *chunks = m0_interp_chunks(interp);

	chunks[count] = *chunk;
	m0_interp_set_chunk_count(interp, count + 1);

	return count;
}

bool m0_interp_push_chunk(m0_interp *interp, const m0_chunk *chunk)
{
	size_t count = m0_interp_chunk_count(interp);
	m0_chunk *chunks = m0_interp_chunks(interp);

	if(is_pow2z(count + 1))
	{
		chunks = (m0_chunk *)realloc(chunks, (count + 1) * 2 * sizeof *chunks);
		if(!chunks) return 0;

		m0_interp_set_chunks(interp, chunks);
	}

	chunks[count] = *chunk;
	m0_interp_set_chunk_count(interp, count + 1);

	return 1;
}

bool m0_interp_init_chunk_map(m0_interp *interp, size_t size, uint32_t seed)
{
	assert(m0_interp_chunk_map(interp) == NULL);
	assert(size > 0);
	assert(is_pow2z(size));

	uint32_t mask = (uint32_t)(size - 1);
	assert(mask == size - 1);

	struct map *map = (struct map *)malloc(
		sizeof *map + size * sizeof *map->buckets);

	uint8_t *index = (uint8_t *)calloc(size, sizeof *index);

	if(!map || !index)
		goto FAIL;

	map->index = index;
	map->mask = mask;
	map->seed = seed;

	m0_interp_set_chunk_map(interp, map);

	return 1;

FAIL:
	free(index);
	free(map);

	return 0;
}

size_t m0_interp_chunk_map_size(const m0_interp *interp)
{
	const struct map *map = (struct map *)m0_interp_chunk_map(interp);
	return map->mask + 1;
}

static uint32_t hash_string(const m0_string *string, uint32_t seed)
{
	return murmur3_32(string->bytes, string->byte_size - sizeof *string, seed);
}

static bool register_chunk(struct map *map, uint32_t hash, uint32_t chunk_id)
{
	uint32_t slot = hash & map->mask;

	size_t fill_count = map->index[slot];
	assert(fill_count < (uint8_t)-1);

	if(fill_count == 0)
	{
		map->buckets[slot].as_single.hash = hash;
		map->buckets[slot].as_single.chunk_id = chunk_id;
		map->index[slot] = 1;
		return 1;
	}

	if(fill_count == 1)
	{
		struct bucket *buckets = (struct bucket *)malloc(2 * sizeof *buckets);
		if(!buckets) return 0;

		buckets[0] = map->buckets[slot].as_single;
		buckets[1].hash = hash;
		buckets[1].chunk_id = chunk_id;

		map->buckets[slot].as_multiple = buckets;
		map->index[slot] = 2;

		return 1;
	}

	struct bucket *buckets = (struct bucket *)realloc(
		map->buckets[slot].as_multiple, (fill_count + 1) * sizeof *buckets);

	if(!buckets) return 0;

	buckets[fill_count].hash = hash;
	buckets[fill_count].chunk_id = (uint32_t)chunk_id;

	map->buckets[slot].as_multiple = buckets;
	map->index[slot] = (uint8_t)(fill_count + 1);

	return 1;
}

bool m0_interp_register_reserved_chunk(
	m0_interp *interp, const m0_string *name, size_t chunk_id)
{
	assert(chunk_id <= (uint32_t)-1);

	struct map *map = (struct map *)m0_interp_chunk_map(interp);
	uint32_t hash = hash_string(name, map->seed);

	return register_chunk(map, hash, (uint32_t)chunk_id);
}

static inline size_t preferred_map_size(size_t load)
{
	// roughly corresponds to a load factor of 0.72,
	// the value recommended by Microsoft
	return next_greater_pow2((load * 11) / 8);
}

bool m0_interp_reserve_chunk_map_slots(m0_interp *interp, size_t count)
{
	struct map *map = (struct map *)m0_interp_chunk_map(interp);
	size_t current_size = map->mask + 1;

	size_t new_load = m0_interp_chunk_count(interp) + count;
	size_t new_size = preferred_map_size(new_load);

	if(current_size == new_size)
		return 1;

	uint32_t new_mask = (uint32_t)(new_size - 1);
	assert(new_mask == new_size - 1);

	struct map *new_map = (struct map *)malloc(
		sizeof *new_map + new_size * sizeof *new_map->buckets);

	uint8_t *new_index = (uint8_t *)calloc(new_size, sizeof *new_index);

	if(!new_map || !new_index)
		goto FAIL;

	new_map->index = new_index;
	new_map->mask = new_mask;
	new_map->seed = map->seed;

	for(size_t i = 0; i < current_size; ++i)
	{
		size_t fill_count = map->index[i];
		if(!fill_count) continue;

		if(fill_count == 1)
		{
			struct bucket *bucket = &map->buckets[i].as_single;
			if(!register_chunk(new_map, bucket->hash, bucket->chunk_id))
				goto DESTROY_AND_FAIL;

			continue;
		}

		for(size_t j = 0; j < fill_count; ++j)
		{
			struct bucket *bucket = &map->buckets[i].as_multiple[j];
			if(!register_chunk(new_map, bucket->hash, bucket->chunk_id))
				goto DESTROY_AND_FAIL;

			continue;
		}
	}

	m0_interp_set_chunk_map(interp, new_map);

	return 1;

DESTROY_AND_FAIL:

	for(size_t i = 0; i < new_size; ++i)
	{
		if(new_index[i] > 1)
			free(new_map->buckets[i].as_multiple);
	}

FAIL:

	free(new_index);
	free(new_map);

	return 0;
}
