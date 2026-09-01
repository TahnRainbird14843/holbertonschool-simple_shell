#include "shell.h"

/**
 * input_read - reads line of input (stdin)
 *
 * Return: pointer to input string otherwise NULL
 */

char *input_read(void)
{
	char *input = NULL;
	char a;
	size_t size = 0;
	ssize_t l;

	/*signal(SIGINT, SIG_IGN);*/
	l = _getline(&input, &size, stdin);
	if (l == -1)
	{
		free(input);
		return (NULL);
	}

	if (input[l - 1] == '\n')
	{
		input[l - 1] = '\0';
	}
	if (l > 1 && (a = getchar()) == EOF)
	{
		strcat(input, input_read());
	}
	else if (a == EOF)
	{
		return ("");
	}

	return (input);
}
