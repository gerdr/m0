#define M0_SOURCE
#include "m0.h"

#undef NDEBUG
#include <assert.h>

#define assert_msg(ERR, MSG) do { \
	FILE *err_ = (ERR), *msg_ = (MSG); \
	assert(putc(0, err_) != EOF); \
	assert(fseek(err_, 0, SEEK_SET) == 0); \
	int cc; do cc = getc(err_); \
	while(cc && cc != EOF && cc == getc(msg_)); \
	assert(cc == 0); \
	assert(!ferror(err_)); \
	assert(!ferror(msg_)); \
	assert(fseek(err, 0, SEEK_SET) == 0); \
} while(0)

int main(void)
{
	m0_interp interp = M0_INTERP;

	FILE *msg = fopen("t/mob/messages", "rb");
	assert(msg != NULL);

	FILE *err = tmpfile();
	assert(err != NULL);

	assert(m0_mob_load(&interp, "t/mob/invalid/missing.m0b", err) == 0);
	assert_msg(err, msg);

	assert(m0_mob_load(&interp, "t/mob/invalid/too-small.m0b", err) == 0);
	assert_msg(err, msg);

	assert(m0_mob_load(&interp, "t/mob/invalid/no-magic.m0b", err) == 0);
	assert_msg(err, msg);

	assert(m0_mob_load(&interp, "t/mob/invalid/zero-version.m0b", err) == 0);
	assert_msg(err, msg);

	assert(getc(msg) == EOF);
	assert(feof(msg));

	return 0;
}
