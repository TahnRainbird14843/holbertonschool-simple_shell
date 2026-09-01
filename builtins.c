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

	struct stat path_stat;
	char *cwd = malloc(128);

	(void)env; /*unused*/

	getcwd(cwd, 128);

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

	while (env[i] != NULL)
		printf("%s\n", env[i++]);

	return (0);
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
	char *var;
	char *out = malloc(sizeof(args[1]) + sizeof(args[2]) + 1);
	int i = 0;

	memset(out, 0, sizeof(args[1]) + sizeof(args[2]) + 1);

	while (env[i] != NULL)
	{
		var = strdup(env[i]);
		if (strcmp(args[1], strtok(var, "=")) == 0)
		{
			out = strcat(strcat(strcat(out, args[1]), "="), args[2]);
			env[i] = out;
			return (1);
		}
		i++;
	}

	if (!env[i])
	{
		env = realloc(env, sizeof(char *) * (i + 2));
		out = strcat(strcat(strcat(out, args[1]), "="), args[2]);
		env[i] = out;
		env[i + 1] = NULL;
		return (1);
	}

	return (0);
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
	char *var;
	int i = 0;
	int found = 0;

	while (env[i] != NULL)
	{
		var = strdup(env[i]);
		if (found == 1)
		{
			env[i] = env[i + 1];
			i++;
		}
		else if (strcmp(args[1], strtok(var, "=")) == 0)
		{
			found = 1;
			env[i] = env[i + 1];
			return (1);
		}
		i++;
	}

	if (found == 1)
	{
		env = realloc(env, sizeof(char *) * i);
		return (1);
	}

	return (0);
}
