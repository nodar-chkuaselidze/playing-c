# Compiler and linker configs.
WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
			-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
			-Wredundant-decls -Wnested-externs -Winline \
			-Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS := -O3 -std=c99 -D_GNU_SOURCE $(WARNINGS) $(CFLAGS)
LDFLAGS := $(LDFLAGS)

SRC_DIR = .
BUILD_DIR = ./build
BUILD_OBJ_DIR = $(BUILD_DIR)/obj

TARGET_NAMES = stack_arrint_test stack_llint_test stack_arrint_bench stack_llint_bench
TARGETS = $(TARGET_NAMES:%=$(BUILD_DIR)/%)

SRCS = $(wildcard *.c)
OBJECTS = $(SRCS:%.c=$(BUILD_OBJ_DIR)/%.o)
DEPS = $(wildcard $(OBJECTS:%=%.d))

all: $(TARGETS)

.PHONY: clean

$(BUILD_DIR)/stack_%_test: $(BUILD_OBJ_DIR)/stack_%.o $(BUILD_OBJ_DIR)/stack_%_test.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/stack_%_bench: $(BUILD_OBJ_DIR)/stack_%.o $(BUILD_OBJ_DIR)/hrtime.o $(BUILD_OBJ_DIR)/stack_%_bench.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_OBJ_DIR):
	mkdir -pv $(BUILD_OBJ_DIR)

$(BUILD_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_OBJ_DIR)
	$(CC) $(CFLAGS) -MD -MP -MF "$@.d" -c $< -o $@ $(LDFLAGS)

include $(DEPS)

clean:
	- rm $(TARGETS) $(wildcard OBJECTS) $(DEPS)
