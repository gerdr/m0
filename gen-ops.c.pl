use strict;
use warnings;

sub m0_ops {
	open my $fh, '<', $ENV{M0_OPS};
	while(<$fh>) {
		next unless /^\w/;
		chomp;
		my $op = 'M0_'.uc;
		my $func = 'op_'.$_;
		print <<EOS
		case $op:
		$func();
		continue;

EOS
	}
	close $fh;
}

do 'gen.pl';
