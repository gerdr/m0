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

do 'gen.pl';
