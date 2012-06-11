#define M0_SOURCE
#include "m0.h"

#include <stdio.h>
#include <stdlib.h>

#define close_file(FP) do { \
	FILE *fp_ = FP; if(!fp_) break; \
	int status_ = fclose(fp_); assert(status_ == 0); \
} while(0)

void *m0_platform_mmap_file_private(const char *name, size_t *size)
{
	FILE *file = NULL;
	void *buffer = NULL;
	long pos = -1;

	file = fopen(name, "rb");
	if(!file || fseek(file, 0, SEEK_END))
		goto FAIL;

	pos = ftell(file);
	if(pos < 0)
		goto FAIL;

	buffer = malloc((size_t)pos);
	if(!buffer)
		goto FAIL;

	if(!fread(buffer, (size_t)pos, 1, file))
		goto FAIL;

	close_file(file);
	*size = (size_t)pos;
	return buffer;

FAIL:
	close_file(file);
	free(buffer);
	return NULL;
}

bool m0_platform_munmap(void *block, size_t size)
{
	(void)size;
	free(block);
	return 1;
}
