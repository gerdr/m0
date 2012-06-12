#include "m0.h"

#undef NDEBUG
#include <assert.h>
#include <limits.h>

int main(void)
{
	m0_interp interp = M0_INTERP;
	m0_callframe *cf = m0_interp_alloc_cf(&interp, 42);

	assert(cf != NULL);
	assert(m0_reg_cf(cf) == cf);
	assert(m0_reg_interp(cf) == &interp);

	return 0;
}
