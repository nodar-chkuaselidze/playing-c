WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
			-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
			-Wredundant-decls -Wnested-externs -Winline \
			-Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS := -O0 -std=c11 $(WARNINGS) $(CFLAGS)
LDFLAGS := $(LDFLAGS)

# One File - One Target projects.

BUILDDIR = ./build

SRCS = $(wildcard *.c)
TARGETS = $(SRCS:%.c=$(BUILDDIR)/%)

.PHONE: all clean 

all: $(TARGETS)

$(BUILDDIR)/%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)


clean:
	- rm $(wildcard $(TARGETS))
