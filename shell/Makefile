# DIRECTORIES
BIN_DIR := ../bin
INCLUDE_DIR := ../include

# COMPILER CONFIGURATION
CC := gcc
CFLAGS := -I$(INCLUDE_DIR) -Wall

# TARGET BINARY
TARGET := $(BIN_DIR)/osh

# COMPILE SHELL BINARY
$(TARGET): shell.c $(INCLUDE_DIR)/shell.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Default target to build the shell
all: $(TARGET)

# CLEAN TARGET
clean:
	rm -f $(TARGET)
