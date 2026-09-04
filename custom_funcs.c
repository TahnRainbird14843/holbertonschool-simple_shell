#include "shell.h"

/**
 * _getline - getline implementation using read()
 * @input: pointer to buffer for data store
 * @size: size buffer
 * @stream: input stream to read
 *
 * Return: Pointer to buffer otherwise NULL
 */

ssize_t _getline(char **input, __attribute__ ((unused)) size_t *size,
		__attribute__ ((unused)) FILE * stream)
{
	static char buffer[1024];
	static ssize_t buff_len = 0, buff = 0, input_size = 1024;
	ssize_t count = 0;
	char c;

	if (!input)
		return (-1);
	if (!(*input))
	{
		*input = malloc(input_size);
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
			{
				if (count > 0)
					break;
				return (-1);
			}
		}

		c = buffer[buff++];
		(*input)[count++] = c;

		if (c == '\n')
			break;
		else if (count == input_size)
		{
			input_size *= 2;
			*input = _realloc(*input, input_size, input_size * 2);
			if (!*input)
				return (-1);
		}
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
	static int j;
	int i;
	int tok;


	if (input != NULL)
	{
		copy = input;
		j = 0;
	}

	if (!copy)
		return (NULL);

	while (copy[j] != '\0')
	{
		i = 0;
		while (sep[i] != '\0' && copy[j] != sep[i])
			i++;

		if (sep[i] == '\0')
			break;
		j++;
	}

	if (copy[j] == '\0')
		return (NULL);

	tok = j;

	while (copy[j] != '\0')
	{
		i = 0;
		while (sep[i] != '\0' && copy[j] != sep[i])
			i++;

		if (sep[i] != '\0')
			break;

		j++;
	}
	if (copy[j] != '\0')
	{
		copy[j] = '\0';
		j++;
	}

	return (copy + tok);
}
/**
 * fetch_env - gets value of environment variable
 * @var: name of environment var
 * @env: environment
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
