use strict;
use warnings;

sub m0_ops {
	open my $fh, '<', $ENV{M0_OPS_FILE};
	while(<$fh>) {
		next unless /^\w/;
		chomp;
		print "\tM0_OP_".uc().",\n"
	}
	close $fh;
}

sub m0_ipd {
	open my $fh, '<', $ENV{M0_IPD_FILE};
	while(<$fh>) {
		next unless /^\w/;
		chomp;
		my ($name) = split /\s+/, $_, 2;
		print "\tM0_IPD_$name,\n"
	}
	close $fh;
}

sub m0_cfg {
	open my $fh, '<', $ENV{M0_CFG_FILE};
	while(<$fh>) {
		next unless /^\w/;
		chomp;
		my ($name) = split /\s+/, $_, 2;
		print "\tM0_CFG_$name,\n"
	}
	close $fh;
}

sub m0_reg {
	open my $fh, '<', $ENV{M0_REG_FILE};
	while(<$fh>) {
		next unless /^\w/;
		chomp;
		my ($name) = split /\s+/, $_, 2;
		print "\tM0_REG_$name,\n"
	}
	close $fh;
}

sub m0_ipd_funcs {
	open my $fh, '<', $ENV{M0_IPD_FILE};
	while(<$fh>) {
		next unless /^\w/;
		chomp;
		my ($name, $member, $type) = split /\s+/, $_, 3;
		next unless defined $member;
		$type .= ' ' unless $type =~ /\*$/;
		my $id = 'M0_IPD_'.uc $name;
		print <<EOS
static inline ${type}m0_interp_$name(const m0_interp *interp)
{
	return (*interp)[$id].as_$member;
}

EOS
	}
	close $fh;
}

sub m0_reg_funcs {
	open my $fh, '<', $ENV{M0_REG_FILE};
	while(<$fh>) {
		next unless /^\w/;
		chomp;
		my ($name, $member, $type) = split /\s+/, $_, 3;
		next unless defined $member;
		$type .= ' ' unless $type =~ /\*$/;
		my $id = "M0_REG_$name";
		$name = lc $name;
		print <<EOS
static inline ${type}m0_reg_$name(const m0_callframe *cf)
{
	return (*cf)[$id].as_$member;
}

EOS
	}
	close $fh;
}

do 'gen.pl';
