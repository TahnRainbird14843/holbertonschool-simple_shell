#include "shell.h"

/**
 * get_home - HOME directory retrieve from environ
 * @env: environment variables
 *
 * Return: pointer to HOME otherwise NULL
 */

char *get_home(char **env)
{
	int i = 0;

	while (env[i])
	{
		if (strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}
