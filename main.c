#include "shell.h"

int main(void)
{
	/* determines if file descriptor is associated with a terminal */
	if (isatty(STDIN_FILENO) == 1)
	{
		shell_interactive();
	}
	else
	{
		shell_no_interactive();
	}
	return (0);
}