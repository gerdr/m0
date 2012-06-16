#define M0_SOURCE
#include "m0.h"

#include <string.h>

struct loader
{
	m0_interp *interp;
	const char *name;
	FILE *err;
	void *mapping;
	size_t size;
	uint32_t *cursor;
	size_t remaining;
};

static const m0_mobheader HEADER = {
	{ 'M', 0, 'B' },
	{ M0_VERSION },
	{ M0_ENDIANNESS, M0_OPSZ, M0_INTSZ, M0_NUMSZ },
	0
};

#define cry(LOADER, FORMAT, ...) do { \
	struct loader *loader_ =  LOADER; \
	if(!loader_->err) break; \
	fprintf(loader_->err, "m0: " FORMAT "\n", __VA_ARGS__); \
	int status_ = fflush(loader_->err); assert(status_ == 0); \
} while(0)

static inline void *read(struct loader *loader, size_t size)
{
	assert(size % sizeof *loader->cursor == 0);
	if(loader->remaining < size)
	{
		cry(loader, "premature end of file <%s>", loader->name);
		return NULL;
	}

	void *mark = loader->cursor;
	loader->remaining -= size;
	loader->cursor += size / sizeof *loader->cursor;
	return mark;
}

static bool mmap_file(struct loader *loader)
{
	size_t size;
	void *mapping = m0_platform_mmap_file_private(loader->name, &size);
	if(!mapping)
	{
		cry(loader, "failed to mmap file <%s>", loader->name);
		return 0;
	}

	loader->mapping = mapping;
	loader->size = size;
	loader->cursor = (uint32_t *)loader->mapping;
	loader->remaining = size;

	return 1;
}

static bool verify_header(struct loader *loader)
{
	const m0_mobheader *header = (m0_mobheader *)read(loader, sizeof *header);
	if(!header) return 0;

	if(memcmp(header->magic, HEADER.magic, sizeof HEADER.magic))
	{
		cry(loader, "file <%s> has wrong magic number", loader->name);
		return 0;
	}

	if(memcmp(header->version, HEADER.version, sizeof HEADER.version))
	{
		cry(loader, "file <%s> has wrong version", loader->name);
		return 0;
	}

	if(memcmp(header->config, HEADER.config, sizeof HEADER.config))
	{
		cry(loader, "file <%s> has wrong type configuration", loader->name);
		return 0;
	}

	if(header->size != loader->size)
	{
		cry(loader, "file <%s> has incorrect size", loader->name);
		return 0;
	}

	return 1;
}

static bool load_chunks(struct loader *loader)
{
	const m0_segment *dir = (m0_segment *)read(loader, sizeof *dir);
	if(!dir) return 0;

	// TODO: verify id - need to come up with a general scheme

	if(!m0_interp_reserve_chunks(loader->interp, dir->entry_count) ||
		!m0_interp_reserve_chunk_map_slots(loader->interp, dir->entry_count))
	{
		cry(loader, "failed to reserve %u chunks for file <%s>",
			(unsigned)dir->entry_count, loader->name);

		return 0;
	}

	for(size_t i = 0; i < dir->entry_count; ++i)
	{
		const m0_direntry *entry = (m0_direntry *)read(loader, sizeof *entry);
		if(!entry) return 0;
			// no need to rollback reserved chunks:
			// the worst that can happen are superfluous realloc() calls

		uint32_t *blocks = (uint32_t *)loader->mapping;

		if(entry->const_offset % sizeof *blocks ||
			entry->meta_offset % sizeof *blocks ||
			entry->code_offset % sizeof *blocks)
		{
			cry(loader, "illegal offsets in file <%s>", loader->name);
			return 0;
		}

		const m0_chunk chunk = {
			(m0_string *)loader->cursor,
			(m0_segment *)(blocks + entry->const_offset / sizeof *blocks),
			(m0_segment *)(blocks + entry->meta_offset / sizeof *blocks),
			(m0_segment *)(blocks + entry->code_offset / sizeof *blocks)
		};

		size_t chunk_id = m0_interp_push_reserved_chunk(
			loader->interp, &chunk);

		if(!m0_interp_register_reserved_chunk(
			loader->interp, chunk.name, chunk_id))
		{
			cry(loader, "allocation failure while loading file <%s>",
				loader->name);

			return 0;
		}

		// TODO: skip name bytes

		assert(!&"TODO");
	}

	return 1;
}

static bool verify_chunks(struct loader *loader)
{
	// TODO: verify segements (walk through chunks)
	(void)loader;
	return 0;
}

bool m0_mob_load(m0_interp *interp, const char *name, FILE *err)
{
	struct loader loader = { interp, name, err, NULL, 0, NULL, 0 };

	if(!mmap_file(&loader))
		goto FAIL;

	if(!verify_header(&loader))
		goto FAIL;

	if(!load_chunks(&loader))
		goto FAIL;

	if(!verify_chunks(&loader))
		goto FAIL;

	return 1;

FAIL:
	if(loader.mapping)
	{
		bool status = m0_platform_munmap(loader.mapping, loader.size);
		assert(status == 1);
	}

	return 0;
}
