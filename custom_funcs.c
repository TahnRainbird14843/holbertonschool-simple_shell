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

	if (!*input)
		return (-1);

	chars = read(fileno(stream), *input, *size);

	if (chars == -1)
		return (-1);

	if ((*input)[chars - 1] == '\n')
		(*input)[chars - 1] = '\0';

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
 * Fetch_env - gets value of environment variable
 * @var: name of environment var
 *
 * Return: pointer to val of env var otherwise NULL
 */

char *fetch_env(const char *var)
{
	int i = 0;
	int l = strlen(var);

	while (env[i])
	{
		if (strncmp(env[i], var, l) == 0 &&
				env[i][l] == '=')
		{
			return (env[i] + l + 1);
		}
		i++;
	}

	return (NULL);
}
