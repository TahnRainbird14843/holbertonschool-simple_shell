#include "shell.h"

/**
 * get_builtin - returns handler func for given command
 * @cmd: command string
 *
 * Return: pointer to function executes command otherwise NULL
 */

int (*get_builtin(char *cmd))(char **, char ***, char *)
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

int _cd(char **args, char ***env_addr, char *pgm)
{
	char **env = *env_addr;
	struct stat st;
	char *tar = NULL;
	char old_pwd[1024];
	char pwd[1024];
	char *new_args[3];

	if (!args[1])
		tar = fetch_env("HOME", env);

	else if (strcmp(args[1], "-") == 0)
		tar = fetch_env("OLDPWD", env);

	else
		tar = args[1];

	if (!tar)
		return (0);

	if (stat(tar, &st) == 0 && S_ISDIR(st.st_mode))
	{
		getcwd(old_pwd, 1024);
		if (chdir(tar) == 0)
		{
			new_args[0] = "setenv";
			new_args[1] = "PWD";
			getcwd(pwd, 1024);
			new_args[2] = pwd;
			_setenv(new_args, env_addr);
			new_args[1] = "OLDPWD";
			new_args[2] = old_pwd;
			_setenv(new_args, env_addr);
			return (1);
		}
		fprintf(stderr, "%s: 1: cd: can't cd to %s\n", pgm, tar);
		return (0);
	}

	return (0);
}

/**
 * _env - prints environment variables
 * @args: argument array
 * @env: environment variables
 *
 * Return: 1
 */

int _env(char **args, char ***env_addr, __attribute__ ((unused)) char *pgm)
{
	char **env = *env_addr;
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

int _setenv(char **args, char ***env_addr, __attribute__ ((unused)) char *pgm)
{
	char *name = args[1];
	char *val = args[2];
	char *new;
	char **new_env;
	char **env = *env_addr;
	int i = 0;

	if (!name)
		return (0);
	if (!val)
		return (0);

	new = malloc(strlen(name) + strlen(val) + 2);
	if (!new)
		return (0);
	sprintf(new, "%s=%s", name, val);

	while (env[i])
	{
		if (strncmp(env[i], name, strlen(name)) == 0 &&
			env[i][strlen(name)] == '=')
		{
			free(env[i]);
			env[i] = new;
			return (1);
		}
		i++;
	}

	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = new;
	new_env[i + 1] = NULL;
	free(env);
	*env_addr = new_env;

	return (0);
}

/**
 * _unsetenv - removes environment variables
 * @args: arguments
 * @env: environment variables
 *
 * Return: 1 - success otherwise 0.
 */

int _unsetenv(char **args, char ***env_addr, __attribute__ ((unused)) char *pgm)
{
	char *name;
	char **env = *env_addr;
	int i = 0, j;

	if (!args[1])
		return (0);

	name = args[1];

	while (env[i])
	{
		if (strncmp(env[i], name, strlen(name)) == 0 &&
			env[i][strlen(name)] == '=')
		{

			free(env[i]);
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
