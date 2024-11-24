# osh 
## operating systems shell
This project implements a simple shell program written in C. The shell supports interactive mode, external command execution, built-in commands, and history navigation using arrow keys.

## features
- External Command Execution: Supports commands like `cat`, `grep`,`wc`, etc., by directly executing binaries from the shell's bin path.
- Built-in Commands: Implements built-ins like `cd`, `exit`, `status`, and `help` for faster execution with less overhead compared to external commands.
- Command History: Saves previously entered commands for easy navigation using the up/down arrow keys.
### adding new commands 
New commands can be added by placing their source files (`*.c`) in the `/command` folder; the Makefile automatically detects and compiles them.

## usage
to compile and run the shell, use
```bash
make run
```
![make](https://github.com/user-attachments/assets/7f265491-4cdf-47ce-8657-31a342ba6a1b)

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

![bi](https://github.com/user-attachments/assets/3cfc85e4-6f23-4beb-8d0f-b48a144940e3)

## commands
### clear
- clear the terminal screen

### wc [OPTIONS]... [FILE]...
- print newline, word, and character count for each file
- [OPTIONS]:
    - -m,-c: print the character counts
    - l : print the newline counts
    - w : print the word counts

 ![nuaim](https://github.com/user-attachments/assets/9ecca62f-4418-4cc4-9995-2290f12035af)
  
