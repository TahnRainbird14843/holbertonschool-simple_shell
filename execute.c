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
	char a;
	int status;
	int (*builtin)(char **, char **);

	if (!args[0] || args[0][0] == '\0')
		return (0);

	full_path = get_path(args[0], env);
	builtin = get_builtin(args[0]);

	if (builtin)
	{
		free(full_path);
		builtin(args, env);
	}
	else if (full_path)
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
	else
	{
		printf("%s: path not found\n", args[0]);
		free(full_path);
		return (127);
	}
}
