HEADERDIR = include

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

INCLUDEPATH = -I$(HEADERDIR)
DEBUG = -g
OPTIM = -O3 -march=native -mtune=native
CFLAGS = $(INCLUDEPATH) $(WARNINGS) $(DEBUG) $(OPTIM) -std=c99 -fPIC -o $@
CC = gcc
OCC = $(CC) -c
LINKOPTS = -L. -lmds
AR = ar
V = @

LIBOBJS = vector/vector.o llist/llist.o dstring/dstring.o

.PHONY : all static dynamic test

all : static dynamic test

static : libmds.a

dynamic : libmds.so

libmds.so : $(LIBOBJS)
	$V printf "Creating dynamic library \033[1m$@\033[0m...\n"
	$V $(CC) $(CFLAGS) -shared $^

libmds.a : $(LIBOBJS)
	$V printf "Creating static library \033[1m$@\033[0m...\n"
	$V $(AR) rcs $@ $^

%.o : %.c
	$V printf "Compiling \033[1m$@\033[0m from $^...\n"
	$V $(OCC) $(CFLAGS) $^

###############################################################################

docs : FORCE
	$V mkdir -p docs/html
	$V naturaldocs2 docs

###############################################################################

test : tests/vector tests/llist tests/dstring tests/vector_huge tests/llist_huge

tests/% : tests/%.c libmds.so
	$V printf "Compiling and linking \033[1m$@\033[0m...\n"
	$V $(CC) $(CFLAGS) $< $(LINKOPTS)

clean : FORCE
	$V rm -f */*.o
	$V (cd tests/; rm -f $$(grep --colour=never -rIL .))

cleanproper : clean FORCE
	$V rm -f *.a *.so

FORCE :

