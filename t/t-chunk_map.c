#define M0_SOURCE
#include "m0.h"

#undef NDEBUG
#include <assert.h>

int main(void)
{
	enum { SEED = 42, SIZE = 8 };

	m0_interp interp = M0_INTERP;

	assert(m0_interp_init_chunk_map(&interp, SIZE, SEED) == 1);
	assert(m0_interp_chunk_map_size(&interp) == SIZE);

	assert(m0_interp_reserve_chunk_map_slots(&interp, SIZE / 2) == 1);
	assert(m0_interp_chunk_map_size(&interp) == SIZE);

	assert(m0_interp_reserve_chunk_map_slots(&interp, SIZE) == 1);
	assert(m0_interp_chunk_map_size(&interp) == SIZE * 2);

	return 0;
}
