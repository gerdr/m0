#include "m0.h"

#undef NDEBUG
#include <assert.h>

#define assert_msg(ERR, MSG) do { \
	FILE *err_ = (ERR), *msg_ = (MSG); \
	assert(fseek(err_, 0, SEEK_SET) == 0); \
	while(!feof(err_)) assert(fgetc(msg_) == fgetc(err_)); \
	assert(!ferror(err_)); \
	assert(!ferror(msg_)); \
} while(0)

int main(void)
{
	m0_interp interp = M0_INTERP;

	FILE *msg = fopen("t/mob/messages", "rb");
	assert(msg != NULL);

	FILE *err = tmpfile();
	assert(err != NULL);

	assert(m0_mob_load(&interp, "t/mob/too-small.m0b", err) == 0);
	assert_msg(err, msg);

	return 0;
}
