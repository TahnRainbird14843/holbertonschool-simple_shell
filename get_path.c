#include "shell.h"

/**
 * get_path - directory search in PATH for command
 * @command: name
 *
 * Return: string with full path otherwise NULL
 */

char *get_path(char *command)
{
	char full_path[1024];
	char *p_copy, *dire;
	char *path = getenv("PATH");

	if (!path)
		return (NULL);

	p_copy = strdup(path);
	if (!p_copy)
		return (NULL);

	if (access(command, X_OK) == 0)
	{
		free(p_copy);
		return (strdup(command));
	}

	dire = strtok(p_copy, ":");

	while (dire)
	{
		full_path[0] = '\0';
		strcpy(full_path, dire);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(p_copy);
			return (strdup(full_path));
		}

		dire = strtok(NULL, ":");
	}

	free(p_copy);

	return (NULL);
}
