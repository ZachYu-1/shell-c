#include "shell.h"

void sigchld_handler()
{
	int status;
	waitpid((pid_t)-1, &status, WNOHANG);
}

int main(void)
{
	char *line;
	parsed_args *arg;
	int status = -1;
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigchld_handler; // handles child that run in background
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	do
	{
		printf("$ ");				// print prompt symbol $
		line = read_line();			// read command from stdin
		arg = split_line(line);		// tokenize command
		status = execute_args(arg); // execute command and check status

		free(line);
		free(arg);
		// exit with status
		if (status >= 0)
		{
			exit(status);
		}
	} while (status == -1);

	return (0);
}