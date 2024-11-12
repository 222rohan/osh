# DIRECTORIES
CMD_DIR := ../command
BIN_DIR := ../bin
INCLUDE_DIR := ../include

# COMPILER CONFIGURATION
CC := gcc
CFLAGS := -I$(INCLUDE_DIR) -Wall

# List all command source files and their corresponding binaries in the bin directory
CMD_SRC := $(wildcard $(CMD_DIR)/*.c)
CMD_BIN := $(CMD_SRC:$(CMD_DIR)/%.c=$(BIN_DIR)/%)

# Default target to build all command binaries
all: $(CMD_BIN)

# Compile each command binary in the bin directory
$(BIN_DIR)/%: $(CMD_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Clean target to remove compiled command binaries
clean:
	rm -f $(CMD_BIN)
