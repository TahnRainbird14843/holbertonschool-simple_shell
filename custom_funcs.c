#include "shell.h"

/**
 * _getline - getline implementation using read()
 * @input: pointer to buffer for data store
 * @size: size buffer
 * @stream: input stream to read
 *
 * Return: Pointer to buffer otherwise NULL
 */

ssize_t _getline(char **input,__attribute__ ((unused)) size_t *size,__attribute__ ((unused)) FILE *stream)
{
	static char buffer[1024];
	static ssize_t buff_len = 0, buff = 0;

	ssize_t count = 0;
	char c;

	if (!input)
		return (-1);

	if (!(*input))
	{
		*input = malloc(1024);
		if (!*input)
			return (-1);
	}

	while (1)
	{
		if (buff >= buff_len)
		{
			buff_len = read(0, buffer, 1024);
			buff = 0;

			if (buff_len <= 0)
				return (count > 0 ? count : -1);
		}

		c = buffer[buff++];
		(*input)[count++] = c;

		if (c == '\n')
			break;
	}
	(*input)[count] = '\0';
	return (count);
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
	static char *copy;
	static int j = 0;
	static int tok = 0;


	if (input != NULL)
	{
		copy = input;
		j = 0;
	}
	tok = j;

	if (copy[j] == '\0')
		return (NULL);

	while (copy[j] != '\0' && copy[j] != sep[0])
		j++;

	if (copy[j] == sep[0])
	{
		copy[j] = '\0';
		j++;
		return (copy + tok);
	}

	return (copy + tok);
}

/**
 * Fetch_env - gets value of environment variable
 * @var: name of environment var
 *
 * Return: pointer to val of env var otherwise NULL
 */

char *fetch_env(char *var, char **env)
{
	int i = 0;
	int l = _strlen(var);

	while (env[i])
	{
		if (_strncmp(env[i], var, l) == 0 &&
				env[i][l] == '=')
		{
			return (env[i] + l + 1);
		}
		i++;
	}

	return (NULL);
}
