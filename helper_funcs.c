#include "shell.h"

/**
 * _strdup - implemented strdup from string.h
 * @str: input str
 *
 * Return: pointer to duplicated string
 */
char *_strdup(char *str)
{
	char *out;
	int size;
	int i = 0;

	size = _strlen(str);
	out = malloc(size + 1);
	while (str[i] != '\0')
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';

	return (out);
}

/**
 * _strncmp - implemented strncmp from string.h
 * @str1: input string 1
 * @str2: input string 2
 * @n: number of chars to compare
 *
 * Return: difference between first different character
 */
int _strncmp(char *str1, char *str2, int n)
{
	int i = 0;

	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}

	if (i < n)
		return (str1[i] - str2[i]);

	return (0);
}

/**
 * _strcmp - implement strcmp from string.h
 * @str1: input string 1
 * @str2: input string 2
 *
 * Return: difference between first different character
 */
int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}

	return (str1[i] - str2[i]);
}

/**
 * _strlen - implement strlen from string.h
 * @str: input string
 *
 * Return: length of string
 */
int _strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	return (i);
}

/**
 * _realloc - implement realloc from stdlib.h
 * @input: input pointer
 * @size: size to reallocate
 *
 * Return: pointer to newly allocated memory of new size
 */
void *_realloc(void *input, size_t size)
{
	char *out = malloc(size);
	char *in = (char *)input;
	int i = 0;
	int s = size > sizeof(input) ? sizeof(input) : size;

	while (i < s)
	{
		out[i] = in[i];
		i++;
	}
	free(input);

	return ((void *)out);
}
