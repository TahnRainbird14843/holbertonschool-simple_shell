#include "shell.h"

/**
 * main - entry point dimple shell
 *
 * Return: 0
 */

int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char *argv[], char *env[])
{
	char *input, **args;
	int r = 1;
	int size = get_env_size(env);
	char **envir = malloc(sizeof(char *) * size);

	memcpy(envir, env, sizeof(char *) * size);

	while (r)
	{
		prompt();
		input = input_read();
		if (!input)
			break;

		args = get_tokens(input);
		if (!args || !args[0])
		{
			free(input);
			free(args);
			continue;
		}

		check_exit(args, &r);
		if (!r)
		{
			free(input);
			free(args);
			break;
		}

		else
			execute(args, envir);
		free(input);
		free(args);
	}

	return (0);
}

int get_env_size(char **env)
{
	int i = 0;

	while (env[i] != NULL)
		i++;

	return (i + 1);
}
