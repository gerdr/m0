CC := clang
CFLAGS := -std=c99 -Werror -Weverything

CXX := clang++
CXXNOWARN := global-constructors variadic-macros
CXXFLAGS := -std=c++98 -Weverything $(CXXNOWARN:%=-Wno-%)

RM := rm -f
PERL := perl

SPECS := $(wildcard spec/*)
GEN_FILES := $(patsubst gen/%.pl,%,$(wildcard gen/*.pl gen/src/*.pl))
SOURCES := $(subst ~,,$(filter-out $(GEN_FILES),$(wildcard src/*.c)))
OBJECTS := $(SOURCES:%.c=%.o)
TESTS := sanity mob ops
TEST_BINARIES := $(TESTS:%=t/%.exe)

include Config

.PHONY : build test clean realclean cppcheck

build : $(OBJECTS)

test : $(TEST_BINARIES)
	$(foreach TEST,$^,$(TEST);)

clean :
	$(RM) $(OBJECTS) $(TEST_BINARIES)

realclean : clean
	$(RM) $(GEN_FILES)

cppcheck :
	$(CXX) -fsyntax-only -I. $(CXXFLAGS) -xc++ $(SOURCES)

$(GEN_FILES) : Config $(SPECS)

$(filter-out src/%,$(GEN_FILES)) : % : gen/%.pl ~%
	$(PERL) $< <~$@ >$@

$(filter src/%,$(GEN_FILES)) : src/% : gen/src/%.pl src/~%
	$(PERL) $< <src/~$(notdir $@) >$@

$(OBJECTS) : %.o : %.c m0.h
	$(CC) -c -o $@ -I. $(CFLAGS) $<

$(TEST_BINARIES) : %.exe : %.c $(OBJECTS)
	$(CC) -o $@ -I. $(OBJECTS) $(CFLAGS) $<
