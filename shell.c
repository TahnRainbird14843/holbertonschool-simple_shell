#include "shell.h"

/**
 * main - entry point
 * argc: argument count
 * argv: list of args
 * env: list of env args
 *
 * Return: 0 always
 */
int main(int argc, char *argv[], char *env[])
{
	pid_t curr_pid;
	pid_t child_pid;
	char *input;
	char **in_argv;
	int run = 1;
	int status;

	while (run == 1)
	{
		prompt();

		input = input_read();

		in_argv = get_tokens(input);

		if (strcmp("exit", in_argv[0]) == 0)
		{
			run = 0;
			break;
		}

		child_pid = fork();
		curr_pid = getpid();
		if (child_pid == 0)
		{
			execve(in_argv[0], in_argv, env);
		}
		else
		{
			wait(&status);
			printf("Success!\n");
		}
	}
	
	return (0);
}
