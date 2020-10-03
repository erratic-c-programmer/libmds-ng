WARNINGS += -Wpedantic
WARNINGS += -Wall
WARNINGS += -Wextra
WARNINGS += -Waggregate-return
WARNINGS += -Wbad-function-cast
WARNINGS += -Wcast-align
WARNINGS += -Wcast-qual
WARNINGS += -Wdeclaration-after-statement
WARNINGS += -Wfloat-equal
WARNINGS += -Wformat=2
WARNINGS += -Wmissing-declarations
WARNINGS += -Wmissing-include-dirs
WARNINGS += -Wmissing-prototypes
WARNINGS += -Wnested-externs
WARNINGS += -Wpointer-arith
WARNINGS += -Wredundant-decls
WARNINGS += -Wsequence-point
WARNINGS += -Wshadow
WARNINGS += -Wstrict-prototypes
WARNINGS += -Wswitch
WARNINGS += -Wundef
WARNINGS += -Wunreachable-code
WARNINGS += -Wunused-parameter
WARNINGS += -Wwrite-strings
WARNINGS += -Werror

DEBUG = -g
OPTIM = -O3 -march=native -mtune=native
CFLAGS = $(WARNINGS) $(DEBUG) $(OPTIM) -std=c99 -fPIC -o $@
CC = gcc
OCC = $(CC) -c
LINKOPTS = -L. -lmds
AR = ar
V = @

LIBOBJS = vector/vector.o llist/llist.o

.PHONY : all static dynamic test

all : static test

static : libmds.a

libmds.a : $(LIBOBJS)
	$V printf "Creating static library \033[1m$@\033[0m...\n"
	$V $(AR) rcs $@ $^

%.o : %.c
	$V $(OCC) $(CFLAGS) $^
	$V printf "Compiling \033[1m$@\033[0m from $^...\n"

###############################################################################

test : tests/vector tests/llist

tests/% : tests/%.c libmds.a
	$V $(CC) $(CFLAGS) $< $(LINKOPTS)
	$V printf "Compiling and linking \033[1m$@\033[0m...\n"

clean : FORCE
	rm -f */*.o
	(cd tests/; rm -f `grep --colour=never -r -I -L .`)

cleanproper : clean FORCE
	rm -f *.a *.so

FORCE :

