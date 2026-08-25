#include "shell.h"

extern char **environ;

/**
 * execute - command run from forking & calling execve
 * @args: array tokens
 *
 * Return: 1 - shell running otherwise 0 - exit
 */

int execute(char **args)
{
	char *full_path;
	pid_t pid;

	if (!args[0])
		return 1;

	if (strcmp(args[0], "exit") == 0)
		return 0;

	if (strcmp(args[0], "env") == 0)
	{
		for (char **e = environ; *e; e++)
			printf("%s\n", *e);
		return 1;
	}

	full_path = get_path(args[0]);

	pid = fork();

	if (pid == 0)
	{
		if (full_path)
			execve(full_path, args, environ);

		printf("%s: path not found\n", args[0]);
		exit(1);
	}

	wait(NULL);
	free(full_path);
	return 1;
}
