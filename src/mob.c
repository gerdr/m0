#define M0_SOURCE
#include "m0.h"

#include <string.h>

#define cry(FORMAT, ...) do if(err) { \
	fprintf(err, "m0: " FORMAT "\n", __VA_ARGS__); \
	int status_ = fflush(err); assert(status_ == 0); \
} while(0)

static const m0_mobheader HEADER = {
	{ 'M', 0, 'B' },
	{ M0_VERSION },
	{ M0_ENDIANNESS, M0_OPSZ, M0_INTSZ, M0_NUMSZ },
	0
};

bool m0_mob_load(const char *name, FILE *err)
{
	void *bc = NULL;
	size_t size = 0;
	const m0_mobheader *header = NULL;

	bc = m0_platform_mmap_file_private(name, &size);
	if(!bc)
	{
		cry("failed to mmap file %s", name);
		goto FAIL;
	}

	if(size < sizeof (m0_mobheader) + sizeof (m0_segment))
	{
		cry("file %s is too small to be a bytecode file", name);
		goto FAIL;
	}

	header = (m0_mobheader *)bc;

	if(memcmp(header->magic, HEADER.magic, sizeof HEADER.magic))
	{
		cry("file %s has wrong magic number", name);
		goto FAIL;
	}

	if(memcmp(header->version, HEADER.version, sizeof HEADER.version))
	{
		cry("file %s has wrong version - expected %X, got %X",
			name, *HEADER.version, *header->version);
		goto FAIL;
	}

	if(memcmp(header->config, HEADER.config, sizeof HEADER.config))
	{
		cry("file %s has wrong type configuration", name);
		goto FAIL;
	}

	if(size != header->size)
	{
		cry("file <%s> has incorrect size", name);
		goto FAIL;
	}

	// TODO

	return 1;

FAIL:
	if(bc)
	{
		bool status = m0_platform_munmap(bc, size);
		assert(status == 1);
	}

	return 0;
}
