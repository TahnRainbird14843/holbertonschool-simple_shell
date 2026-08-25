#include "shell.h"

void check_exit(char **args, int *run)
{
	int exit_code;

	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1])
			exit(atoi(args[1]));
		else
			*run = 0;
	}
}
