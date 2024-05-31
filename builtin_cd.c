#include "shell.h"

int builtin_cd(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "expected dir to \"cd\"\n");

	else
	{
		if (chdir(args[1]) != 0)
			perror("error changing dir\n");
	}
	return (-1);
}