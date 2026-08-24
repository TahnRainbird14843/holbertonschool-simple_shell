#include "shell.h"

char *get_tokens(char *input)
{
	char **tokens = malloc(sizeof(char *) * 64);
	int i = 0;

	for (char *token = strtok(input, " "); token; token = strtok(NULL, " "))
		tokens[i++] = token;

	token[i] = NULL;
	return tokens;
}
