#include "shell.h"

/**
 * command_func - returns handler func for given command
 * @cmd: command string
 *
 * Return: pointer to function executes command otherwise NULL
 */

void (*command_func(char *cmd))(char **, char **)
{
	cmd_t cmds[3] = {
		{"ls", exec_ls},
		{"env", exec_env},
		{NULL, NULL}
	};
	int i = 0;

	while (cmds[i].cmd)
	{
		if (strcmp(cmds[i].cmd, cmd) == 0)
			return (cmds[i].func);
		i++;
	}

	return (NULL);
}

/**
 * exec_ls - executes ls command (execve())
 * @args: argument vector command
 * @env: environment variables
 */

void exec_ls(char **args, char **env)
{
	args[0] = "/bin/ls";
	execve(args[0], args, env);
}

/**
 * exec_env - executes env using execve()
 * @args: argument vector command
 * @env: environment variables
 */

void exec_env(char **args, char **env)
{
	args[0] = "/bin/env";
	execve(args[0], args, env);
}
