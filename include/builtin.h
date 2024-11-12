#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUILTIN_SUCCESS 1
#define BUILTIN_FAILURE -1

extern int last_exit_status;

/*
bi_cd
    Change the current working directory.
    args[1] is the directory to change to.
    args[2] is NULL.
    returns BUILTIN_SUCCESS on success.
    returns BUILTIN_FAILURE on unexpected error.
*/
int bi_cd(char **args);

/*
bi_exit
    Exit the shell.
    args[1] is NULL.
    returns BUILTIN_SUCCESS on success.
*/
int bi_exit(char **args);

/*
bi_help
    Display help information.
    args[1] is NULL.
    returns BUILTIN_SUCCESS.
*/
int bi_help(char **args);

/*
bi_status
    Display the exit status of the last executed file.
    args[1] is NULL.
    returns BUILTIN_SUCCESS on sucess.
*/
int bi_status(char **args);

#endif  //BUILTIN_H