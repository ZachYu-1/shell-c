#include "shell.h"

int execute_args(parsed_args *arg)
{
	int argc = arg->argc;
	char **args = arg->args;
	int input_fd = STDIN_FILENO;
	int output_fd = STDOUT_FILENO;
	int pipefd[2];
	int j = 0;
	long unsigned int i = 0;
	int is_background = 0;
	int print_pid = 0;

	char *builtin_func_list[] = {"cd", "exit"}; // builtin function list
	int (*builtin_func[])(char **) = {&builtin_cd, &builtin_exit};

	if (args[0] == NULL) // no input, continue
		return (-1);

	if (argc > 0 && strcmp(args[argc - 1], "&") == 0) // suffix &, run in background
	{
		is_background = 1;
		args[argc - 1] = NULL;
		argc--;
	}

	for (; j < argc; j++)
	{
		if (strcmp(args[j], "<") == 0 && args[j + 1] != NULL) // redirect the standard input
		{
			input_fd = open(args[j + 1], O_RDONLY);
			if (input_fd < 0)
			{
				fprintf(stderr, "%s: File not found\n", args[j + 1]);
				return (-1);
			}
			args[j] = NULL; // set the operator to NULL and skip file name
			j++;
		}

		if (strcmp(args[j], ">") == 0 && args[j + 1] != NULL) // redirect the standard output
		{
			output_fd = open(args[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (output_fd < 0)
			{
				fprintf(stderr, "%s: Cannot create file\n", args[j + 1]);
				return (-1);
			}
			args[j] = NULL; // set the operator to NULL and skip file name
			j++;
		}

		if (strcmp(args[j], "|") == 0 && args[j + 1] != NULL) // create pipes
		{
			int err = pipe(pipefd);
			if (err < 0)
			{
				perror("error in execute_args: pipe");
				return (-1);
			}
			args[j] = NULL; // end command before the pipe

			new_process(args, input_fd, pipefd[1], is_background, print_pid); // execute sub-command
			close(pipefd[1]);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			input_fd = pipefd[0]; // redirect input of next sub-command to read end

			args += j + 1; // adjust args pointer to the next sub-command
			argc -= j + 1;
			j = -1; // reset loop
		}
	}

	for (; i < sizeof(builtin_func_list) / sizeof(char *); i++)
	{
		if (strcmp(args[0], builtin_func_list[i]) == 0) // execute the builtin command
			return ((*builtin_func[i])(args));
	}

	if (is_background) // if run in background, print pid of last sub-command
		print_pid = 1;

	return (new_process(args, input_fd, output_fd, is_background, print_pid));
}