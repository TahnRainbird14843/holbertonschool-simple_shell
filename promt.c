#include <stdio.h>
#include <unistd.h>

/**
 * prompt - prints shell prompt
 *
 * Return: void
 */

void promt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#Shell$ ");
		fflush(stdout);
	}
}
