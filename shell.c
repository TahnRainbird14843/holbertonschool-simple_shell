#include "shell.h"

/**
 * main - entry point
 *
 * Return: 0 always
 */
int main(int argc, char *argv[], char *env[])
{
	pid_t curr_pid;
	pid_t child_pid;
	char *input;
	ssize_t in_len;
	size_t size = 128;
	char *in_argv[10];
	int i = 0;
	FILE *in_stream = stdin;
	int status;
	int run = 1;

	while (run == 1)
	{
		printf("#Shell$ ");

		in_len = getline(&input, &size, in_stream);

		in_argv[i] = strtok(input, " ");
		while (argv[i] != NULL)
		{
			i++;
			in_argv[i] = strtok(NULL, " ");
		}

		if (strcmp("exit", argv[0]) == 0)
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
