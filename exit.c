#include "shell.h"

/**
 * check_exit - handles exit builtin
 * @args: array of cmd arguments
 * @run: pointer to shell loop flag
 *
 */

void check_exit(char **args, int last_status)
{
	int exit_code;

	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1])
		{
			exit_code = atoi(args[1]);
			exit(exit_code);
		}

		else
		{
			exit(last_status);
		}
	}
}
