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
		cry(loader, "file <%s> has wrong version - expected %u, got %u",
			loader->name, *HEADER.version, *header->version);
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

bool m0_mob_load(m0_interp *interp, const char *name, FILE *err)
{
	struct loader loader = { interp, name, err, NULL, 0, NULL, 0 };

	if(!mmap_file(&loader))
		goto FAIL;

	if(!verify_header(&loader))
		goto FAIL;

	// TODO

	return 1;

FAIL:
	if(loader.mapping)
	{
		bool status = m0_platform_munmap(loader.mapping, loader.size);
		assert(status == 1);
	}

	return 0;
}
