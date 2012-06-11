#include "m0.h"

#undef NDEBUG
#include <assert.h>
#include <limits.h>

int main(void)
{
	assert(CHAR_BIT == 8);

	assert(M0_OPSZ == 4);
	assert(M0_INTSZ == 2 || M0_INTSZ == 4 || M0_INTSZ == 8 || M0_INTSZ == 16);
	assert(M0_NUMSZ == 4 || M0_NUMSZ == 8 || M0_NUMSZ == 16);

	static m0_value value;
	assert(sizeof value == sizeof value.bits);
	assert(sizeof value.as_int == sizeof value.as_uint);
	assert(sizeof value.as_word == sizeof value.as_uword);

	return 0;
}
