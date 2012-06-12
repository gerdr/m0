#define M0_SOURCE
#include "m0.h"

#undef NDEBUG
#include <assert.h>

int main(void)
{
	{
		assert(CHAR_BIT == 8);

		assert(M0_OPSZ == 4);
		assert(
			M0_INTSZ == 2 || M0_INTSZ == 4 || M0_INTSZ == 8 || M0_INTSZ == 16);
		assert(M0_NUMSZ == 4 || M0_NUMSZ == 8 || M0_NUMSZ == 16);
	}

	{
		static const m0_value VALUE = { 0 };

		assert(sizeof VALUE == sizeof VALUE.bits);
		assert(sizeof VALUE == sizeof VALUE.bytes);

		assert(sizeof VALUE.as_int == sizeof VALUE.as_uint);
		assert(sizeof VALUE.as_word == sizeof VALUE.as_uword);

		assert(VALUE.as_ptr == NULL);
	}

	{
		assert(is_pow2z(0) == 1);
		assert(is_pow2z(1) == 1);
		assert(is_pow2z(2) == 1);
		assert(is_pow2z(3) == 0);
		assert(is_pow2z(4) == 1);
		assert(is_pow2z(5) == 0);
		assert(is_pow2z(1023) == 0);
		assert(is_pow2z(1024) == 1);
		assert(is_pow2z((size_t)-1 / 2 + 1) == 1);
		assert(is_pow2z((size_t)-1) == 0);
	}

	{
		assert(next_greater_pow2(0) == 1);
		assert(next_greater_pow2(1) == 2);
		assert(next_greater_pow2(2) == 4);
		assert(next_greater_pow2(3) == 4);
		assert(next_greater_pow2(4) == 8);
		assert(next_greater_pow2(5) == 8);
		assert(next_greater_pow2(1023) == 1024);
		assert(next_greater_pow2(1024) == 2048);
		assert(next_greater_pow2((size_t)-1 / 2) == (size_t)-1 / 2 + 1);
		assert(next_greater_pow2((size_t)-1 / 2 + 1) == 0);
	}

	return 0;
}
