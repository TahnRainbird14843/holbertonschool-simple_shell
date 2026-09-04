#include "shell.h"

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

int _strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	return (i);
}

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
