#include "shell.h"

/**
 * command_func - returns handler func for given command
 * @cmd: command string
 *
 * Return: pointer to function executes command otherwise NULL
 */

int (*get_builtin(char *cmd))(char **, char **)
{
	cmd_t cmds[] = {
		{"exit", NULL},
		{"cd", _cd},
		{"setenv", _setenv},
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

int _cd(char **args, char **env)
{
	struct stat path_stat;
	char *cwd = malloc(128);
	char *err = getcwd(cwd, 128);

	if (strcmp(args[1], "-") == 0)
	{
		cwd = getenv("HOME");
		chdir(cwd);
		return (1);
	}
	cwd = strcat(strcat(cwd, "/"), args[1]);
	if (stat(cwd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		chdir(cwd);
		return (1);
	}

	printf("Path does not exist\n");
	return (0);
}

int _env(char **args, char **env)
{
	int i = 0;

	while (env[i] != NULL)
		printf("%s\n", env[i++]);

	return (0);
}

int _setenv(char **args, char **env)
{
	char *var;
	char *out = malloc(sizeof(args[1]) + sizeof(args[2]) + 1);
	int i = 0;

	while (env[i] != NULL)
	{
		var = strdup(env[i]);
		if (strcmp(args[1], strtok(var, "=")) == 0)
		{
			out = strcat(strcat(args[1], "="), args[2]);
			env[i] = out;
			return (1);
		}
		i++;
	}

	return (0);
}
