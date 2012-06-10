#include "m0.h"

#undef NDEBUG
#include <assert.h>
#include <limits.h>

int main(void)
{
	assert(CHAR_BIT == 8);

	static m0_value value;
	assert(sizeof value == sizeof value.bits);

	return 0;
}
