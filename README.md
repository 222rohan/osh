# osh 
## operating systems shell
This project implements a simple shell program written in C. The shell supports interactive mode, external command execution, built-in commands, and history navigation using arrow keys.

## features
- External Command Execution: Supports commands like `cat`, `grep`,`wc`, etc., by directly executing binaries from the shell's bin path.
- Built-in Commands: Implements built-ins like `cd`, `exit`, `status`, and `help` for faster execution with less overhead compared to external commands.
- Command History: Saves previously entered commands for easy navigation using the up/down arrow keys.

## usage
to compile and run the shell, use
```bash
make run
```
### Makefile
The project uses a recursive Makefile structure where source and header files (from `/shell`, `/command` and `/include`) are compiled into `/bin`.

## shell functions and builtins
### functions
- `get_shell_dir()` : returns the shell binary directory to simulate environment path variables for command resolution.
### builtins
- `cd <PATH>` : change directory to specified path.
- `exit or exit <code>` :  exits the shell with an optional status. 0 is the default status code.
- `help` : lists all the available commands.
- `status` : prints the exit status of the last command/program.