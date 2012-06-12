use strict;
use warnings;

sub m0_ops {
	open my $fh, '<', $ENV{M0_OPS_FILE};
	while(<$fh>) {
		next unless /^\w/;
		chomp;
		print "\top_$_,\n";
	}
	close $fh;
}

while(<STDIN>) {
	print, next unless /__(M0_\w+)__/;
	my $var = $1;
	&{$::{lc $var}}, next if exists $::{lc $var};
	s/__${var}__/$ENV{$var}/g;
	print;
}

