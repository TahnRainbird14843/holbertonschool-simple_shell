#include "shell.h"

char **get_tokens(char *input)
{
	char **tokens = malloc(sizeof(char *) * 64);
	int i = 0;
	char *token;

	for (token = _strtok(input, " "); token; token = _strtok(NULL, " "))
		tokens[i++] = token;

	tokens[i] = NULL;
	return tokens;
}
