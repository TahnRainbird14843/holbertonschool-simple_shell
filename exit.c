#include "shell.h"

/**
 * check_exit - handles exit builtin
 * @args: array of cmd arguments
 * @run: pointer to shell loop flag
 *
 */

int check_exit(char **args, int *run, int *status, char *pgm)
{
	int exit_status;
	int exit_fail;

	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1])
		{
			exit_status = _atoi(args[1], &exit_fail);
			if (exit_fail == 1)
			{
				*status = 2;
				fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", pgm, args[1]);
				return (-1);
			}

			*status = exit_status;
		}
		else if (isatty(STDIN_FILENO))
			*status = 0;

		*run = 0;

		return (1);
	}

	return (0);
}

/**
 * _atoi - convert string to int
 * @str: input str
 *
 * Return: int corresponding to string
 */
int _atoi(char *str, int *fail)
{
	int i = 0;
	int out = 0;

	*fail = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			out = 10 * out + (str[i] - '0');
		else
			*fail = 1;
		i++;
	}

	return (out);
}
