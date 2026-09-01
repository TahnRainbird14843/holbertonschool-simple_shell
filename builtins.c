#include "shell.h"

/**
 * get_builtin - returns handler func for given command
 * @cmd: command string
 *
 * Return: pointer to function executes command otherwise NULL
 */

int (*get_builtin(char *cmd))(char **, char **)
{
	cmd_t cmds[] = {
		{"cd", _cd},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
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

/**
 * _cd - changes current working direct
 * @args: array of arguments
 * @env: environment variables (unused)
 *
 * Return: 1 - success otherwise 0
 */

int _cd(char **args, char **env)
{

	struct stat st;
	char *tar = NULL;

	if (!args[1] || strcmp(args[1], "-") == 0)
		tar = get_home(env);

	else
		tar = args[1];

	if (!tar)
	{
		printf("HOME\n");
		return (0);
	}

	if (stat(tar, &st) == 0 && S_ISDIR(st.st_mode))
	{
		if (chdir(tar) == 0)
			return (1);
	}
		printf("Path does not exist\n");
		return (0);
}

/**
 * _env - prints environment variables
 * @args: argument array
 * @env: environment variables
 *
 * Return: 1
 */

int _env(char **args, char **env)
{

	int i = 0;

	(void)args; /*unused*/

	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}

	return (1);
}

/**
 * _setenv - set environment variables
 * @args: arguments
 * @env: environment variables
 *
 * Return: 1 - success otherwise 0
 */

int _setenv(char **args, char **env)
{
	char *name = args[1];
	char *val = args[2];
	char *new;
	int i = 0;

	if (!name || !val)
		return (0);

	while (env[i])
	{
		if (strncmp(env[i], name, strlen(name)) == 0 &&
			env[i][strlen(name)] == '=')
		{
			free(env[i]);

			new = malloc(strlen(name) + strlen(val) + 2);
			if (!new)
				return (0);

			sprintf(new, "%s=%s", name, val);
			env[i] = new;
			return (1);
		}
		i++;
	}
	new = malloc(strlen(name) + strlen(val) + 2);
	if (!new)
		return (0);

	sprintf(new, "%s=%s", name, val);

	env[i] = new;
	env[i + 1] = NULL;

	return (1);
}

/**
 * _unsetenv - removes environment variables
 * @args: arguments
 * @env: environment variables
 *
 * Return: 1 - success otherwise 0.
 */

int _unsetenv(char **args, char **env)
{
	char *name;
	int i = 0, j;

	if (!args[1])
		return (0);

	name = args[1];

	while (env[i])
	{
		if (strncmp(env[i], name, strlen(name)) == 0 &&
			env[i][strlen(name)] == '=')
		{
			j = i;

			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}

			return (1);
		}
		i++;
	}
	return (0);
}
