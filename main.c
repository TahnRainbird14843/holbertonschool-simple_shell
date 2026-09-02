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
			check_exit(args, &run);
			if (run == 1)
				execute(args, argv[0], envir);
		}
		free(input);
		i = 0;
		while(args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
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
