#include "shell.h"

/**
 * execute - command run from forking & calling execve
 * @args: array tokens
 * @env: environment
 *
 * Return: 1 - shell running otherwise 0 - exit
 */

int execute(char **args, char **env)
{
	char *full_path;
	pid_t pid;
	int status;
	int (*builtin)(char **, char **);

	if (!args[0])
		return (0);

	full_path = get_path(args[0], env);
	builtin = get_builtin(args[0]);

	if (full_path && !builtin)
	{
		pid = fork();

		if (pid == 0)
		{
			execve(full_path, args, env);
			free(full_path);
			exit(127);
		}

		wait(&status);
		free(full_path);

		return WEXITSTATUS(status);
	}
	else if (builtin)
	{
		free(full_path);
		return (builtin(args, env));
	}
	else
	{
		printf("%s: path not found\n", args[0]);
		free(full_path);
		return (127);
	}
}
