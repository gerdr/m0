CC := clang
CFLAGS := -std=c99 -Werror -Weverything
RM := rm -f
PERL := perl
ECHO := echo
SHELL := sh

SOURCES := interp.c mob.c ops.c platform.c
OBJECTS := $(SOURCES:%.c=%.o)
GEN_FILES := m0.h ops.c
TESTS := sanity
TEST_BINARIES := $(TESTS:%=t-%)
TEST_SCRIPT := test.sh
CHECKS := $(TESTS:%=%-check)
TARGETS := build test clean realclean gen genclean regen $(CHECKS) help
FILES_TO_CLEAN := $(OBJECTS) $(TEST_BINARIES)
FILES_TO_REALCLEAN := $(GEN_FILES)

include CONFIG

.PHONY : $(TARGETS)

build : $(OBJECTS)

gen : $(GEN_FILES)

regen : genclean gen

genclean :
	$(RM) $(GEN_FILES)

test : $(TEST_SCRIPT) $(TEST_BINARIES)
	@$(SHELL) $^

clean :
	$(RM) $(FILES_TO_CLEAN)

realclean : FILES_TO_CLEAN += $(FILES_TO_REALCLEAN)
realclean : clean

help :
	@$(ECHO) $(TARGETS)

$(CHECKS) : %-check : t-%
	./$<

$(TEST_BINARIES) : % : %.c $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(GEN_FILES) : % : gen-%.pl src-% gen.pl CONFIG m0.ops m0.ipd m0.reg m0.cfg
	$(PERL) gen-$@.pl <src-$@ >$@

$(OBJECTS) : %.o : %.c m0.h
	$(CC) $(CFLAGS) -c -o $@ $<
