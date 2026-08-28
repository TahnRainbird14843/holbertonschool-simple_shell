#include "shell.h"

/**
 * command_func - returns handler func for given command
 * @cmd: command string
 *
 * Return: pointer to function executes command otherwise NULL
 */

void (*get_builtin(char *cmd))(char **, char **)
{
	cmd_t cmds[] = {
		{"exit", NULL},
		{"cd", NULL},
		{"setenv", NULL},
		{"unsetenv", NULL},
		{"alias", NULL},
		{"help", NULL},
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
