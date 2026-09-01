#include "shell.h"

/**
 * get_tokens - command line split into aarray of tokens
 * @input: string to token
 *
 * Return: pointer to array of token string otherwise NULL
 */

char **get_tokens(char *input)
{
	int i = 0, buffsize = 10;
	char **tokens, *t;

	tokens = malloc(sizeof(char *) * buffsize);

	if (!tokens)
		return (NULL);

	t = _strtok(input, " \t\r\n");
	while (t)
	{
		tokens[i++] = t;

		if (i >= buffsize)
		{
			buffsize *= 2;
			tokens = realloc(tokens, sizeof(char *) * buffsize);

			if (!tokens)
				return (NULL);
		}

		t = _strtok(NULL, " \t\r\n");
	}

	tokens[i] = NULL;
	return (tokens);
}
