#include "shell.h"

/**
 * execute - command run from forking & calling execve
 * @args: array tokens
 *
 * Return: 1 - shell running otherwise 0 - exit
 */

int execute(char **args, char **env)
{
	char *full_path;
	pid_t pid;
	/*char **e;*/
	int (*builtin)(char **, char **);

	if (!args[0])
		return (1);

	full_path = get_path(args[0]);
	builtin = get_builtin(args[0]);

	if (full_path && !builtin)
	{
		pid = fork();

		if (pid == 0)
		{
			execve(full_path, args, env);
		}
	}
	else if (builtin)
	{
		builtin(args, env);
	}
	else
	{
		printf("%s: path not found\n", args[0]);
	}

	wait(NULL);
	free(full_path);
	return (1);
}
