![image](https://github.com/user-attachments/assets/943cb3de-1f4f-45ab-94c2-a653e93e7e74)# osh 
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


 ## cp (Copy)
- **cp**: Copy files or directories.
- **Usage**: `cp [options] <source> <destination>`
- **Options**:
  - `-r, --recursive`: Copy directories recursively.
  - `-f, --force`: Force overwrite of existing files.
  - `-v, --verbose`: Enable verbose output.
    
![image](https://github.com/user-attachments/assets/0e3b7542-42f2-4723-bb06-f4bb9c1c856b)
![image](https://github.com/user-attachments/assets/50c0312b-92bf-46cd-b6c3-6719879a45ef)
![image](https://github.com/user-attachments/assets/870616fb-cb5a-4906-ac56-d5c3c38edf0e)
![image](https://github.com/user-attachments/assets/62e619c6-978e-4fe9-829a-7998e7ec2bcb)


## del (Delete)
- **del**: Delete files or directories.
- **Usage**: `del [options] <path>`
- **Options**:
  - `-v, --verbose`: Enable verbose output.
![image](https://github.com/user-attachments/assets/2f56cff9-41cd-4915-9267-07d1baef96bc)
-before
![image](https://github.com/user-attachments/assets/b0bd2488-9f93-4f5a-9e3a-0b251b601e40)
-after
![image](https://github.com/user-attachments/assets/1cca1cb2-527a-4f8b-8f50-70359f9f2097)
![image](https://github.com/user-attachments/assets/e489632d-a004-4feb-8561-e151ab647093)

## mv (Move)
- **mv**: Move files or directories.
- **Usage**: `mv [options] <source> <destination>`
- **Options**:
  - `-r, --recursive`: Move directories recursively.
  - `-f, --force`: Force overwrite of existing files.
  - `-v, --verbose`: Enable verbose output.

  ![image](https://github.com/user-attachments/assets/6e65b4f5-50b1-4017-b2da-fbbf064bf3ba)
  ![image](https://github.com/user-attachments/assets/a00a66d7-f179-4015-a643-6d7c6fa7d228)
  ![image](https://github.com/user-attachments/assets/d6a78754-f9dd-44ef-88ec-a85272642b63)

## cat [FILE]...
- print the file content(s)
- concatentates the file content if multiple files provided

![image](https://github.com/user-attachments/assets/bccf3c8b-b3c1-4b86-a59c-840e84c3f86e)
![image](https://github.com/user-attachments/assets/0f07b43b-cdd3-4795-9eed-8ecf7103370c)

## ls [OPTIONS]... [PATH]
- list the contents of the current working directory
- [OPTIONS]:
    - -a: include hidden files/directories
    - -l: output in form of a list

![image](https://github.com/user-attachments/assets/69fbb9b4-868c-4d7a-aa9d-85f7da36b71a)


## grep [OPTIONS]... [PATTERN] [FILE]
- list the contents of the current working directory
- [OPTIONS]:
    - -i: ignore case in search
- [PATTERN]: the pattern to be searched in the given file(s)

![image](https://github.com/user-attachments/assets/200a15ba-f353-43a6-b9b5-00bc48b539f1)
![image](https://github.com/user-attachments/assets/d4139713-0758-4edb-a391-fd305abe9e02)



