#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * struct commands - map command name to handler func
 * @cmd: coommand string
 * @func: pointer to function executing command
 */

typedef struct commands
{
	char *cmd;
	void (*func)(char **, char **);
} cmd_t;

extern char **environ;
void prompt(void);
char *input_read(void);
char **get_tokens(char *input);
char *get_path(char *command);
ssize_t _getline(char **buffer, size_t *size, FILE *stream);
char *_strtok(char *input, char *sep);
char *get_path(char *command);
int execute(char **args);
void (*command_func(char *cmd))(char **, char **);
void exec_ls(char **args, char **env);
void exec_env(char **args, char **env);
void check_exit(char **args, int *run);
void sig_handle(int);

#endif
