#include "shell.h"

/**
 * _getline - getline implementation using read()
 * @input: pointer to buffer for data store
 * @size: size buffer
 * @stream: input stream to read
 *
 * Return: Pointer to buffer otherwise NULL
 */

char *_getline(char **input, size_t *size, FILE *stream)
{
	char *str = *input;
	ssize_t chars;

	if (!str)
		return (NULL);

	chars = read(fileno(stream), str, *size);

	if (chars == -1)
		return (NULL);

	if (str[chars - 1] == '\n')
		str[chars - 1] = '\0';

	return (str);
}

/**
 * _strtok - string token using static buffer
 * @input: string to token
 * @sep: seperator string 1st char
 *
 * Return: Pointer to allocated token otherwise NULL
 */

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
