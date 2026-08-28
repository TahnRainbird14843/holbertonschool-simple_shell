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
	void (*builtin)(char **, char **);

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

		builtin = get_builtin(args[0]);

		if (builtin);
		else
			execute(args, env);
		free(input);
		free(args);
	}

	return (0);
}
