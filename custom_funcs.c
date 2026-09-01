#include "shell.h"

/**
 * _getline - getline implementation using read()
 * @input: pointer to buffer for data store
 * @size: size buffer
 * @stream: input stream to read
 *
 * Return: Pointer to buffer otherwise NULL
 */

ssize_t _getline(char **input, size_t *size, FILE *stream)
{
	ssize_t chars;

	if (!input)
		return (-1);

	if (!(*input))
		*input = malloc(64);

	chars = read(fileno(stream), *input, 64);

	return (chars);
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
	if (copy == NULL || tok == NULL)
		return (NULL);

	while (copy[i] != '\0' && copy[i] != sep[0])
	{
		tok[i] = copy[i];
		i++;
	}
	tok[i] = '\0';

	if (copy[i] == '\0')
	{
		copy = NULL;
		return (tok);
	}

	copy = copy + i + 1;
	return (tok);
}

/* getenv function*/

/**
 * _getenv - gets value of environment variable
 * @var: name of environment var
 *
 * Return: pointer to val of env var otherwise NULL
 */

char *_getenv(const char *var)
{
	int i = 0;
	size_t l = strlen(var);

	while (environ[i])
	{
		if (strncmp(environ[i], var, l) == 0 &&
				environ[i][l] == '=')
		{
			return environ[i] + l + 1;
		}
		i++;
	}

	return (NULL);
}
