#include "shell.h"

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

void exec_ls(char **args, char **env)
{
	args[0] = "/bin/ls";
	execve(args[0], args, env);
}

void exec_env(char **args, char **env)
{
	args[0] = "/bin/env";
	execve(args[0], args, env);
}
