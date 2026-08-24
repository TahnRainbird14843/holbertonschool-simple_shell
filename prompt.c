#include <stdio.h>
#include <unistd.h>

/**
 * prompt - prints shell prompt
 *
 * Return: void
 */

void prompt(void) /* Interactive mode prompt */
{
	if (isatty(STDIN_FILENO)) /* Checks standard input is from terminal */
	{
		printf("#Shell$ ");
		fflush(stdout);
	}
}
