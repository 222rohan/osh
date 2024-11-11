//main driver for the shell

//contains all definitions for the shell
#include "../include/shell.h"
#include "../include/builtin.h"

//shell constants
int is_interactive = INTERACTIVE;
int last_exit_status = 0;
char *SH_PATH;

//built-in commands
char *builtins[] = {
    "cd",
    "exit",
    "help",
    "status"
    };
    
int (*builtins_fn[])(char **) = {
    &bi_cd, 
    &bi_exit, 
    &bi_help,
    &bi_status
    };

//function definitions

/* checks if arguments are passed to the shell
    if arguments are passed, the shell is not in interactive mode
    and the arguments are executed as commands
    if no arguments are passed, the shell is in interactive mode
    and user enters commands through stdin
*/
int main(int argc, char **argv) {

    SH_PATH = get_shell_dir();

    if(argc > 1) {
        is_interactive = !INTERACTIVE;
        //do this later
    }

    run_shell_loop();
    return 0;
}

//main shell loop
void run_shell_loop(void) {
    char line[MAX_BUFFER_LEN] = {0};
    int run_status = 0;

    while (1) {
        prompt();
        if(read_line(line)) {   
            run_status = run_line(line);

            if(run_status == RUN_CMD_NOTFOUND) {
                printf("%sosh: %scommand not found%s\n", RED, YELLOW, RESET);
            } else if(run_status == RUN_FAILURE) {
                printf("%sosh: %sunexpected error%s\n", RED, YELLOW, RESET);
            } else if(run_status == RUN_FILE_NOTFOUND) {
                printf("%sosh: %sfile not found%s\n", RED, YELLOW, RESET);
            }

        memset(line, 0, MAX_BUFFER_LEN);
        }
    }
}

void prompt(void) {
    if (is_interactive) {
        char current_dir[MAX_BUFFER_LEN];
        getcwd(current_dir, sizeof(current_dir));
        printf("%s(%s):%sosh> %s", ORANGE, current_dir, CYAN ,RESET);
    }
}

int read_line(char *line) {
    if (fgets(line, MAX_BUFFER_LEN, stdin) == NULL) {
        printf("\n");
        return 0;
    }
    int len = strlen(line);
    if (line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
    return 1;
}

int run_line(char *line) {
    char *args[MAX_ARG_COUNT] = {0};
    int arg_count = parse_line(line, args);
    if (arg_count == 0) {
        return RUN_DO_NOTHING;
    }
    int bi_index = get_builtin(args[0]);
    if (bi_index != -1) {
        return exec_fn_builtin(bi_index, args);
    }

    return exec_cmd_ext(args);
}

int parse_line(char *line, char **args) {
    int i = 0;
    args[i] = strtok(line, " ");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
    }
    return i;
}

int get_builtin(char *cmd) {
    for(int i = 0; i < sizeof(builtins) / sizeof(char *); i++) {
        if (strcmp(cmd, builtins[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int exec_fn_builtin(int bi_index, char **args) {
    return builtins_fn[bi_index](args);
}

char *get_shell_dir() {
    static char shell_dir[MAX_BUFFER_LEN];  // Store the shell's directory path
    ssize_t len = readlink("/proc/self/exe", shell_dir, sizeof(shell_dir) - 1);
    if (len == -1) {
        perror("readlink");
        exit(EXIT_FAILURE);
    }
    shell_dir[len] = '\0'; 

    //remove executable name from the path
    char *last_slash = strrchr(shell_dir, '/');
    if (last_slash != NULL) {
        *last_slash = '\0';  
    }
    return shell_dir;
}

int exec_cmd_ext(char **args) {
    char cmd_path[1024];
    int cmd = 1;

//case 1: absolute path is provided
    if (args[0][0] == '/' || args[0][0] == '.') {
        strcpy(cmd_path, args[0]);
        cmd = 0;
//case 2: search in PATH
    } else {
        snprintf(cmd_path, sizeof(cmd_path), "%s/%s", SH_PATH, args[0]);
    }
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(cmd_path, args) == -1) {
            if(cmd) {
                return RUN_CMD_NOTFOUND;
            } else {
                return RUN_FILE_NOTFOUND;
            }
        }
    } else if (pid < 0) {
        perror("fork");
        return RUN_FAILURE;
    } else {
        int status;
        waitpid(pid, &status, 0);
        last_exit_status = WEXITSTATUS(status);
    }

    return RUN_SUCCESS;
}
