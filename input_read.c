#include "shell.h"

/**
 * input_read - reads line of input (stdin)
 *
 * Return: pointer to input string otherwise NULL
 */

char *input_read(void)
{
	char *input = NULL;
	size_t size = 0;
	ssize_t l;

	/*signal(SIGINT, sig_handle);*/
	l = getline(&input, &size, stdin);
	if (l == -1)
	{
		free(input);
		return (NULL);
	}

	if (input[l - 1] == '\n')
	{
		input[l - 1] = '\0';
	}

	return (input);
}

void sig_handle(__attribute__ ((unused)) int sig)
{
	printf("\n");
	if (isatty(STDIN_FILENO))
		prompt();
}
