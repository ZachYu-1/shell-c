#include "shell.h"

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1) // getline and if fails
	{
		if (feof(stdin)) // test for eof
		{
			free(line);
			exit(EXIT_SUCCESS); // eof, exit
		}
		else
		{
			free(line);
			perror("error reading from stdin");
			exit(EXIT_FAILURE); // error reading line, exit
		}
	}
	return (line);
}