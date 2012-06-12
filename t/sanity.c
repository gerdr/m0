#include "m0.h"

#undef NDEBUG
#include <assert.h>
#include <limits.h>

int main(void)
{
	static const m0_value VALUE = { 0 };

	assert(CHAR_BIT == 8);

	assert(M0_OPSZ == 4);
	assert(M0_INTSZ == 2 || M0_INTSZ == 4 || M0_INTSZ == 8 || M0_INTSZ == 16);
	assert(M0_NUMSZ == 4 || M0_NUMSZ == 8 || M0_NUMSZ == 16);

	assert(sizeof VALUE == sizeof VALUE.bits);
	assert(sizeof VALUE == sizeof VALUE.bytes);

	assert(sizeof VALUE.as_int == sizeof VALUE.as_uint);
	assert(sizeof VALUE.as_word == sizeof VALUE.as_uword);

	assert(VALUE.as_ptr == NULL);

	return 0;
}
