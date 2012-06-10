use strict;
use warnings;

while(<STDIN>) {
	print, next unless /__(M0_\w+)__/;
	my $var = $1;
	&{$::{lc $var}}, next if exists $::{lc $var};
	s/__${var}__/$ENV{$var}/g;
	print;
}
