#define M0_SOURCE
#include "m0.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		puts("Usage: m0 <FILES>... [-- <ARGS>...]");
		return EXIT_SUCCESS;
	}

	m0_interp interp = M0_INTERP;

	int i = 1;

	for(; i < argc; ++i)
	{
		bool loaded = m0_mob_load(&interp, argv[i], stderr);
		if(!loaded) goto FAIL;

		if(strcmp(argv[i], "--") == 0)
			break;
	}

	for(++i; i < argc; ++i)
	{
		// convert args
	}

	return EXIT_SUCCESS;

FAIL:
	return EXIT_FAILURE;
}
