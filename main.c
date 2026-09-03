#include "shell.h"

/**
 * main - entry point dimple shell
 * @argv: argument vector
 * @env: environment
 * @argc: argument count
 *
 * Return: 0
 */

int main(__attribute__ ((unused)) int argc,
		char *argv[],
		char *env[])
{
	char *input, **args;
	int size = get_env_size(env);
	char **envir = malloc(sizeof(char *) * size);
	int i = 0;
	int run = 1;
	int status = 0;
	int ex;

	while (env[i])
	{
		envir[i] = strdup(env[i]);
		i++;
	}
	envir[i] = NULL;

	while (run)
	{
		if (isatty(STDIN_FILENO))
			prompt();

		input = input_read();
		if (!input)
		{
			break;
		}

		args = get_tokens(input);

		if (args && args[0])
		{
			ex = check_exit(args, &run, &status, argv[0]);
			if (ex == 0)
				execute(args, argv[0], envir, &status);
		}

		free(input);
		free(args);
		input = NULL;
		args = NULL;
	}
	i = 0;
	while (envir[i])
	{
		free(envir[i]);
		i++;
	}
	free(envir);

	if (status)
		exit(status);

	return (0);
}

/**
 * get_env_size - count environment variables
 * @env: environment variable array
 *
 * Return: num of entried in env including NULL
 */

int get_env_size(char **env)
{
	int i = 0;

	while (env[i] != NULL)
		i++;

	return (i + 1);
}
