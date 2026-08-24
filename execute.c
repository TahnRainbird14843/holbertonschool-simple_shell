#include "shell.h"

int execute(char **args)
{
	char *path;
	pid_t pid;

	if (!args[0])
		return 1;

	
