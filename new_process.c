#include "shell.h"

int new_process(char **args, int input_fd, int output_fd, int is_background, int print_pid)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) // child process
    {
        if (input_fd != STDIN_FILENO) // redirect stdin to input_fd
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO) // redirect stdout to output_fd
        {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        if (is_background) // backgroud child does not receive keyboard interrupts
        {
            setpgid(0, 0);
        }

        if (execvp(args[0], args) == -1) // error executing
        {
            if (errno == ENOENT)
                fprintf(stderr, "%s: Command not found\n", args[0]);

            else
                perror("Error executing command");
        }

        exit(EXIT_FAILURE);
    }

    else if (pid < 0)
    {
        perror("error in new_process: forking");
    }

    else // parent process
    {
        if (input_fd != STDIN_FILENO) // close redirected input and output in parent
            close(input_fd);
        if (output_fd != STDOUT_FILENO)
            close(output_fd);

        if (!is_background) // not background process, wait for exit or interrupted
        {
            do
            {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        else if (print_pid) // print the pid of background process
            printf("[%d]\n", pid);
    }
    return (-1);
}