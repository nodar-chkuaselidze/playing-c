WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
			-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
			-Wredundant-decls -Wnested-externs -Winline \
			-Wuninitialized -Wconversion -Wstrict-prototypes \
			-Wno-unused-variable
CFLAGS := -O0 -std=c11 $(WARNINGS) $(CFLAGS)
LDFLAGS := $(LDFLAGS)

# One File - One Target projects.

BUILDDIR = ./build

SRCS = $(wildcard *.c)
TARGETS = $(SRCS:%.c=$(BUILDDIR)/%)

.PHONE: all clean 

all: $(TARGETS)

build:
	mkdir -pv build

$(BUILDDIR)/%: %.c | build
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)


clean:
	- rm $(wildcard $(TARGETS))
