# DIRECTORIES
BIN_DIR := ../bin
INCLUDE_DIR := ../include

# COMPILER CONFIGURATION
CC := gcc
CFLAGS := -I$(INCLUDE_DIR) -Wall

# TARGET BINARY
TARGET := $(BIN_DIR)/osh

# SOURCE FILES
SOURCES := shell.c builtin.c

# COMPILE SHELL BINARY
$(TARGET): $(SOURCES) $(INCLUDE_DIR)/shell.h $(INCLUDE_DIR)/builtin.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

# DEFAULT TARGET
all: $(TARGET)

# CLEAN TARGET
clean:
	rm -f $(TARGET)
