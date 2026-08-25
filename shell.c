#include "shell.h"

/**
 * main - entry point
 * argc: argument count
 * argv: list of args
 * env: list of env args
 *
 * Return: 0 always
 */
int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char *argv[], char *env[])
{
	/*pid_t curr_pid;*/
	pid_t child_pid;
	char *input;
	char **in_argv;
	int run = 1;
	int status;
	void (*exec)(char **, char **);

	while (run == 1)
	{
		prompt();

		input = input_read();

		in_argv = get_tokens(input);

		check_exit(in_argv, &run);

		exec = command_func(in_argv[0]);

		if (exec != NULL)
		{
			child_pid = fork();
			/*curr_pid = getpid();*/
			if (child_pid == 0)
			{
				exec(in_argv, env);
			}
			else
			{
				wait(&status);
				printf("Success!\n");
			}
		}
	}
	
	return (0);
}
