#include "shell.h"

/**
 * get_path - directory search in PATH for command
 * @command: name
 * @env: environment
 *
 * Return: string with full path otherwise NULL
 */

char *get_path(char *command, char **env)
{
	char full_path[1024];
	char *p_copy, *dire;
	char *path = fetch_env("PATH", env);

	if (access(command, X_OK) == 0 && (command[0] == '/' || command[0] == '.'))
		return (_strdup(command));

	if (!path || path[0] == '\0')
		return (NULL);

	p_copy = _strdup(path);
	if (!p_copy)
		return (NULL);

	dire = _strtok(p_copy, ":");

	while (dire)
	{
		full_path[0] = '\0';
		strcpy(full_path, dire);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(p_copy);
			return (_strdup(full_path));
		}
		dire = _strtok(NULL, ":");
	}

	free(p_copy);

	return (NULL);
}
