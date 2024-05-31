#include "shell.h"

int builtin_exit(char **args)
{
	if (args[1])
		return (atoi(args[1])); // exit with status

	else
		exit(0);
}