#include "shell.h"

ssize_t _getline(char **input, size_t *size, FILE *stream)
{
	ssize_t chars;

	if (!*input)
		return (-1);

	chars = read(fileno(stream), *input, *size);

	if (chars == -1)
		return (-1);

	if (*input[chars - 1] == '\n')
		*input[chars - 1] = '\0';

	return (chars);
}

char *_strtok(char *input, char *sep)
{
	int i = 0;
	char *tok = malloc(64);
	static char *copy;

	if (input)
		copy = strdup(input);
	if (copy == NULL)
		return (NULL);

	while (copy[i] != '\0' && copy[i] != sep[0])
	{
		tok[i] = copy[i];
		i++;
	}

	if (copy[i] == '\0')
	{
		copy = NULL;
		return (tok);
	}
	
	copy = copy + i + 1;
	return (tok);
}
