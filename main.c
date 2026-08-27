#include "shell.h"

/**
 * main - entry point dimple shell
 *
 * Return: 0
 */

int main(void)
{
	char *input, **args;
	int r = 1;

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

		execute(args);
		free(input);
		free(args);
	}

	return (0);
}
