CC := clang
CFLAGS := -std=c99 -Werror -Weverything

I_FLAG := -I
C_FLAG := -c
OBJ_FLAG := -o
EXE_FLAG := -o

SEPARATOR := /
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
TEST_SOURCES := $(TESTS:%=t/t-%.c)
TEST_BINARIES := $(TESTS:%=t-%$(EXESUFFIX))
BINARY := m0$(EXESUFFIX)

shellpath = $(subst /,$(SEPARATOR),$(1))

include Config

.PHONY : build exe test clean realclean cppcheck gen list

build : $(OBJECTS)

exe : $(BINARY)

gen : $(GEN_FILES)

list :
	@$(ECHO) $(SOURCES)

test : $(TEST_BINARIES)
	$(call shellpath,$(foreach TEST,$^,./$(TEST);))

clean :
	$(RM) $(call shellpath,$(OBJECTS) $(TEST_BINARIES))

realclean : clean
	$(RM) $(call shellpath,$(GEN_FILES) $(BINARY))

cppcheck : $(GEN_FILES)
	$(CPPCHECK) $(call shellpath,$(SOURCES) $(TEST_SOURCES))

$(GEN_FILES) : Config $(SPECS)
chunk$(OBJSUFFIX) : src/murmur3.h

$(filter %.h,$(GEN_FILES)) : %.h : %~.h gen/%.h.pl
	$(PERL) $(call shellpath,gen/$@.pl <$< >$@)

$(filter %.c,$(GEN_FILES)) : %.c : %~.c gen/%.c.pl
	$(PERL) $(call shellpath,gen/$@.pl <$< >$@)

$(OBJECTS) : %$(OBJSUFFIX) : src/%.c m0.h
	$(CC) $(C_FLAG) $(OBJ_FLAG)$(call shellpath,$@) $(I_FLAG). $(CFLAGS) $(call shellpath,$<)

$(BINARY) : $(OBJECTS)
	$(CC) $(EXE_FLAG)$(call shellpath,$@) $(call shellpath,$^)

$(TEST_BINARIES) : OBJECTS := $(filter-out main$(OBJSUFFIX),$(OBJECTS))
$(TEST_BINARIES) : %$(EXESUFFIX) : t/%.c $(OBJECTS)
	$(CC) $(EXE_FLAG)$(call shellpath,$@) $(I_FLAG). $(OBJECTS) $(CFLAGS) $(call shellpath,$<)
