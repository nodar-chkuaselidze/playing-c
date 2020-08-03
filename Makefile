##
# Nod is kinda learning C..

DIRECTORIES=$(wildcard */)
FILES=$(wildcard */*.c)
BINS=$(patsubst %.c,%.o,$(FILES))

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline \
            -Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS := -g -std=c99 $(WARNINGS)


all: $(BINS)
	@echo "building.."

clean:
	@$(RM) $(BINS)

%.o: %.c Makefile
	@$(CC) $(CFLAGS) $< -o $@

.PHONY: all clean

# vim:ft=make
