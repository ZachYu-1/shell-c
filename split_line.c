#include "shell.h"

parsed_args *split_line(char *line)
{
    int bufsize = 64;
    int i = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;
    parsed_args *result; // struct parsed_args for storing args and number of args

    if (!tokens)
    {
        fprintf(stderr, "allocation error in split_line");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM); // defined delimiters in shell.h
    while (token != NULL)
    {
        tokens[i] = token;
        i++;
        if (i >= bufsize)
        {
            bufsize += bufsize;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "allocation error in split_line");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[i] = NULL; // add NULL as last arg

    result = malloc(sizeof(parsed_args));
    result->argc = i;
    result->args = tokens;
    return (result);
}