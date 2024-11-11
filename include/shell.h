#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


// shell constants
#define MAX_BUFFER_LEN 1024                         // Maximum length of a command
#define MAX_ARG_COUNT 64                            // Maximum number of arguments per command
#define INTERACTIVE 1                               // Interactive mode

// shell return codes
#define RUN_SUCCESS 1                               // Command run successfully
#define RUN_DO_NOTHING 0                            // Do nothing
#define RUN_FAILURE -1                              // unexpected failure
#define RUN_CMD_NOTFOUND -2                         // Command not found
#define RUN_FILE_NOTFOUND -3                        // File not found

// shell members
extern int is_interactive;                          // Flag to indicate whether the shell is in interactive mode
extern int last_exit_status;                        // Holds exit status of the last executed file
extern char *SH_PATH;                               // Hold path to the shell executable
extern char *builtins[];                            // Built-in command names
extern int (*builtins_fn[])(char **);               // Function pointers to built-in commands

//formatting
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define ORANGE "\033[38;5;208m"

// MAIN SHELL FUNCTIONS
/*
run_shell_loop
    Main interactive shell loop,
    which displays the shell prompt and reads input from the user.
    then runs the command.
*/
void run_shell_loop(void);                          // Main interactive shell loop

/*
prompt
    Display the shell prompt (e.g., osh>)
    todo: add the current working directory to the prompt
*/
void prompt(void);                      // Display the shell prompt (e.g., osh>

// THE SHELL UTILS

/*
read_line
    Read a line of input from the user.
    The line is stored in the buffer.
    Returns 0 if the user enters an empty line.(ie. whitespace)
    else returns 1.
*/
int read_line(char *);               

/*
run_line
    Run a command.
    The command is passed as a string.
    The command is parsed and executed.
    returns the exit status of the command,
    or -1 if the command is not valid.
*/           
int run_line(char *);  

/*
parse_input
    Parse the input line.
    tokenizes the input line into arguments.
    returns the number of arguments.
    TODO: checks for redirection, piping, and multiple commands.
*/                        
int parse_line(char *, char **);        

/*
get_builtin
    Check if the command is a built-in command.
    returns the index of the built-in command.
    returns -1 if the command is not a built-in command.
*/
int get_builtin(char *);    

/*
get_shell_dir
    helper function,
    returns the directory path of the shell executable.
*/
char *get_shell_dir(void);

/*
exec_fn_builtin
    Execute a built-in command,
    which is a function pointer,,
    with index bi_index.
    The command is passed as a string.
    returns the exit status of the command.
*/
int exec_fn_builtin(int, char **); 

/*
exec_cmd_ext
    Execute an external command.
    The command is passed as a string.
    if absolute path is not provided,
     the command is searched in the PATH.
    else the absolute path is executed.
    returns the exit status of the command.
*/
int exec_cmd_ext(char **);

#endif // SHELL_H
