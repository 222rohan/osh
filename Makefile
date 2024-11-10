# Directories
SHELL_DIR := shell
COMMAND_DIR := command
BIN_DIR := bin

# Default target to build everything
all: $(BIN_DIR)
	$(MAKE) -C $(SHELL_DIR)
	$(MAKE) -C $(COMMAND_DIR)

# Run the shell program
run: all
	./$(BIN_DIR)/osh

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean target to remove binaries in both shell and command directories
clean:
	$(MAKE) -C $(SHELL_DIR) clean
	$(MAKE) -C $(COMMAND_DIR) clean
	rm -rf $(BIN_DIR)
