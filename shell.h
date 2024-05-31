#ifndef SHELL_H
#define SHELL_H

// MACROS
#define TOK_DELIM " \t\r\n\a\""
#define _POSIX_C_SOURCE 200809L

// LIBRARIES
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

// PROTOTYPES
typedef struct
{
    char **args;
    int argc;
} parsed_args;

char *read_line(void);
parsed_args *split_line(char *line);
int execute_args(parsed_args *arg);
int new_process(char **args, int input_fd, int output_fd, int is_background, int print_pid);
int builtin_cd(char **args);
int builtin_exit(char **args);

#endif