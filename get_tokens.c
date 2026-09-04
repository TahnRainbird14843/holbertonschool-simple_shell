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

	t = _strtok(input, " \t\n");
	while (t)
	{
		if (t[0] != '\0')
			tokens[i++] = t;

		if (i >= buffsize)
		{
			buffsize *= 2;
			tokens = _realloc(tokens, sizeof(char *) * buffsize);

			if (!tokens)
				return (NULL);
		}

		t = _strtok(NULL, " \t\n");
	}

	tokens[i] = NULL;
	return (tokens);
}
