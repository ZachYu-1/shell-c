# shell-c

## Description
Built a shell on a Linux environment using the C language.

## Files

| Name | Description |
| ------------------------------ | -------------------------------------------- |
| shell.h | Header file, macros and prototypes |
| main.c | Main function, run the shell in a loop |
| read_line.c | Read a command from user input |
| split_line.c | Split a string of command into tokens |
| execute_args.c | Go through command and execute |
| new_procees.c | Create a child process to execute command |
| builtin_cd.c | Builtin function, change the working directory |
| builtin_exit.c | Builtin function, exit with a given state |

## Compile
gcc -std=c11 *.c -o [name]

## Run
Type command after prompt symbol $ and press enter