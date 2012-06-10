use strict;
use warnings;

sub m0_ops {
	open my $fh, '<', $ENV{M0_OPS};
	while(<$fh>) {
		next unless /^\w/;
		chomp;
		print "\tM0_OP_".uc().",\n"
	}
	close $fh;
}

sub m0_ipd { print for map { "\tM0_IPD_$_,\n" } split(/\s+/, $ENV{M0_IPD}) }
sub m0_cfg { print for map { "\tM0_CFG_$_,\n" } split(/\s+/, $ENV{M0_CFG}) }
sub m0_reg { print for map { "\tM0_REG_$_,\n" } split(/\s+/, $ENV{M0_REG}) }

do 'gen.pl';
