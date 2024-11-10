#DIRECTORIES
CMD_DIR := command
BIN_DIR := bin
SHELL_DIR := shell
INCLUDE_DIR := include

#CMD SRC FILES (REMOVE .c)
COMMANDS := ls cat grep  

#COMPILER CONF
CC := gcc
CFLAGS := -I$(INCLUDE_DIR) -Wall

#COMPILE COMMANDS IN BIN DIR
$(BIN_DIR)/%: $(CMD_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

#CREATE BIN
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

#COMPILE SHELL BIN
$(BIN_DIR)/osh: $(SHELL_DIR)/shell.c $(INCLUDE_DIR)/shell.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Target to build all commands and the main shell as osh
all: $(COMMANDS:%=$(BIN_DIR)/%) $(BIN_DIR)/osh

#CLEAN REMOVES ALL BIN
clean:
	rm -rf $(BIN_DIR)
