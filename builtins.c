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
		if (_strcmp(cmds[i].cmd, cmd) == 0)
			return (cmds[i].func);
		i++;
	}

	return (NULL);
}

/**
 * _cd - changes current working direct
 * @args: array of arguments
 * @env_addr: environment variables
 * @pgm: current program being executed
 *
 * Return: 1 - success otherwise 0
 */

int _cd(char **args, char ***env_addr, char *pgm)
{
	char **env = *env_addr;
	struct stat st;
	char *tar = NULL;
	char old_pwd[1024];
	int to_old = 0;
	int success;

	if (!args[1])
		tar = fetch_env("HOME", env);
	else if (_strcmp(args[1], "-") == 0)
	{
		to_old = 1;
		tar = fetch_env("OLDPWD", env);
	}
	else
		tar = args[1];
	getcwd(old_pwd, 1024);
	if (!tar)
	{
		if (to_old)
			printf("%s\n", old_pwd);
		return (0);
	}
	if (stat(tar, &st) == 0 && S_ISDIR(st.st_mode))
	{
		success = change_dir(tar, pgm, env_addr, to_old);
		if (success)
			return (1);

		fprintf(stderr, "%s: 1: cd: can't cd to %s\n", pgm, tar);
		return (0);
	}

	if (to_old)
		printf("%s\n", old_pwd);
	else
		fprintf(stderr, "%s: 1: cd: can't cd to %s\n", pgm, tar);

	return (0);
}

/**
 * change_dir - change directory to a target directory and update env
 * @tar: target directory
 * @pgm: current program being executed
 * @env_addr: current environment
 * @to_old: 1 if "cd -" was called, 0 otherwise
 *
 * Return: 1 on successful change, 0 otherwise
 */
int change_dir(char *tar, char *pgm, char ***env_addr, int to_old)
{
	char old_pwd[1024];
	char pwd[1024];
	char *new_args[3];

	getcwd(old_pwd, 1024);
	if (chdir(tar) == 0)
	{
		new_args[0] = "setenv";
		new_args[1] = "PWD";
		getcwd(pwd, 1024);
		new_args[2] = pwd;
		_setenv(new_args, env_addr, pgm);
		new_args[1] = "OLDPWD";
		new_args[2] = old_pwd;
		_setenv(new_args, env_addr, pgm);
		if (to_old)
			printf("%s\n", pwd);
		return (1);
	}

	return (0);
}

/**
 * _env - prints environment variables
 * @args: argument array
 * @env_addr: environment variables
 * @pgm: current program being run (unused)
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
 * @env_addr: environment variables
 * @pgm: current program being run (unused)
 *
 * Return: 1 - success otherwise 0
 */
int _setenv(char **args, char ***env_addr, __attribute__ ((unused)) char *pgm)
{
	char *name = args[1];
	char *val = args[2];
	char *new;
	char **env = *env_addr;
	char **new_env;
	int i = 0;

	if (!name)
		return (0);
	if (!val)
		return (0);
	new = malloc(_strlen(name) + _strlen(val) + 2);
	if (!new)
		return (0);
	sprintf(new, "%s=%s", name, val);
	while (env[i])
	{
		if (_strncmp(env[i], name, _strlen(name)) == 0 &&
			env[i][_strlen(name)] == '=')
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
 * @env_addr: environment variables
 * @pgm: current program being run
 *
 * Return: 1 - success otherwise 0.
 */
int _unsetenv(char **args, char ***env_addr,
		__attribute__ ((unused)) char *pgm)
{
	char *name;
	char **env = *env_addr;
	int i = 0, j;

	if (!args[1])
		return (0);

	name = args[1];

	while (env[i])
	{
		if (_strncmp(env[i], name, _strlen(name)) == 0 &&
			env[i][_strlen(name)] == '=')
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
