#define M0_SOURCE
#include "m0.h"

#include <string.h>

// TODO: support big-endian architectures
static const uint8_t FORMAT[8] = {
	'M', '0', 'B',
	'L', 'E',
	'0' + sizeof (m0_opcode),
	'0' + sizeof (m0_int),
	'0' + sizeof (m0_num)
};

bool m0_mob_verify_header(const m0_mob_header *header)
{
	return memcmp(header->format, FORMAT, sizeof FORMAT);
}
