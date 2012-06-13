CC := clang
CFLAGS := -std=c99 -Werror -Weverything

I_FLAG := -I
O_FLAG := -o
C_FLAG := -c

EXESUFFIX :=
OBJSUFFIX := .o

NOWARN := global-constructors variadic-macros
CPPCHECK := clang++ -fsyntax-only -I .\
	-std=c++98 -Weverything $(NOWARN:%=-Wno-%) -xc++

RM := rm -f
PERL := perl
ECHO := echo

SPECS := $(wildcard spec/*)
GEN_FILES := $(patsubst gen/%.pl,%,$(wildcard gen/*.pl gen/src/*.pl))
SOURCES := $(subst ~,,$(filter-out $(GEN_FILES),$(wildcard src/*.c)))
OBJECTS := $(SOURCES:src/%.c=%$(OBJSUFFIX))
TESTS := sanity mob ops
TEST_SOURCES := $(TESTS:%=t/%.c)
TEST_BINARIES := $(TESTS:%=t-%)
BINARY := m0$(EXESUFFIX)

include Config

.PHONY : build exe test clean realclean cppcheck gen list

build : $(OBJECTS)

exe : $(BINARY)

gen : $(GEN_FILES)

list :
	@$(ECHO) $(SOURCES)

test : $(TEST_BINARIES)
	$(foreach TEST,$^,./$(TEST);)

clean :
	$(RM) $(OBJECTS) $(TEST_BINARIES)

realclean : clean
	$(RM) $(GEN_FILES) $(BINARY)

cppcheck : $(GEN_FILES)
	$(CPPCHECK) $(SOURCES) $(TEST_SOURCES)

$(BINARY) : $(OBJECTS)
	$(CC) $(O_FLAG) $@ $(I_FLAG) . $^

$(GEN_FILES) : Config $(SPECS)

$(filter %.h,$(GEN_FILES)) : %.h : %~.h gen/%.h.pl
	$(PERL) gen/$@.pl <$< >$@

$(filter %.c,$(GEN_FILES)) : %.c : %~.c gen/%.c.pl
	$(PERL) gen/$@.pl <$< >$@

$(OBJECTS) : %$(OBJSUFFIX) : src/%.c m0.h
	$(CC) $(C_FLAG) $(O_FLAG) $@ $(I_FLAG) . $(CFLAGS) $<

$(TEST_BINARIES) : OBJECTS := $(filter-out main$(OBJSUFFIX),$(OBJECTS))
$(TEST_BINARIES) : t-% : t/%.c $(OBJECTS)
	$(CC) $(O_FLAG) $@ $(I_FLAG) . $(OBJECTS) $(CFLAGS) $<
