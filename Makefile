##
# Nod is kinda learning C..

FILES=$(wildcard test*/*.c)
BINS=$(patsubst %.c,%.o,$(FILES))

SUP_WARNINGS=-Wno-incompatible-pointer-types \
						-Wno-sizeof-array-argument
CFLAGS := -g -O0 -std=c11 $(SUP_WARNINGS) $(CFLAGS)


all: $(BINS)
	@echo "NOTE: WARNINGS are suppressed with make command."
	@echo "Build finished."

clean:
	@$(RM) $(BINS)
	@$(RM) $(wildcard test*/a.out)

%.o: %.c Makefile
	@$(CC) $(CFLAGS) $< -o $@

.PHONY: all clean

# vim:ft=make
