#include "../include/builtin.h"


/*TODO: cannot change dir 
    to a path with spaces.
    fix this asap. (getc)

*/
int bi_cd(char **args){
    if(args[2] != NULL){
        printf("usage: cd <path>\n");
        return BUILTIN_SUCCESS;
    }
    char *path = args[1];
    if (path == NULL) {
        path = getenv("HOME");  
    }
    if (chdir(path) != 0) {
        perror("cd failed");
        return BUILTIN_SUCCESS;  // Print error if directory change fails
    }
    return BUILTIN_SUCCESS;
}

/*TODO: exit is broken.
    please fix it asap, it has some issue
    where i have to exit multiple times to 
    actually exit the shell. 
    (some stdin issue) 
    (try .1 recursive shells .2 invalid exit args)
*/
int bi_exit(char **args){
    int status = 0;

    if(args[2] != NULL){
        printf("usage: exit [NULL]/<status>\n");
        return BUILTIN_SUCCESS;
    }

    if(args[1] != NULL && (strcmp(args[1],"0") != 0)){
        status = atoi(args[1]);
        if(status == 0){
            printf("exit: status must be numeric.\n");
            return BUILTIN_SUCCESS;
        }
    }

    printf("(%d) : goodbye\n",status);
    exit(status);

}

int bi_help(char **args) {
    printf("Utility commands:\n");
    printf("  cd         Change directory to <path>.\n");
    printf("  exit       Exit the shell.            \n");
    printf("  help       List basic osh commands.   \n");
    printf("  cat        Concatenate file contents. \n");
    printf("  cp         Copy file.                 \n"); 
    printf("  del        Delete file.               \n");
    printf("  grep       Search <pattern> in a file.\n");
    printf("  ls         List directory contents.   \n");
    printf("  mv         Move file to <path>.       \n");
    printf("  wc         Print word count of file.  \n");
    printf("  status     Display last exit status.  \n");
    return BUILTIN_SUCCESS;
}

int bi_status(char **args) {
    if(args[1] != NULL){
        printf("usage: status\n");
        return BUILTIN_SUCCESS;
    }
    printf("last exit status: %d\n", last_exit_status);
    return BUILTIN_SUCCESS;
}