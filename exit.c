#include "shell.h"

/**
 * check_exit - handles exit builtin
 * @args: array of cmd arguments
 * @run: pointer to shell loop flag
 *
 */

void check_exit(char **args, int *run, int *status)
{
	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1])
			*status = atoi(args[1]);
		else
			*status = 2;

		*run = 0;
	}
}
