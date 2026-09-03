#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stddef.h>
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
	int (*func)(char **, char **);
} cmd_t;

extern char **environ;
void prompt(void);
char *input_read(void);
char **get_tokens(char *input);
char *get_path(char *command, char **env);
ssize_t _getline(char **buffer, size_t *size, FILE *stream);
char *_strtok(char *input, char *sep);
char *get_path(char *command, char **env);
int execute(char **args, char *pgm, char **env, int *status);
int (*get_builtin(char *cmd))(char **, char **);
int check_exit(char **args, int *run, int *status);
void sig_handle(int);
int _cd(char **args, char **env);
int _env(char **args, char **env);
int _setenv(char **args, char **env);
int _unsetenv(char **args, char **env);
int get_env_size(char **env);
char *get_home(char **env);
char *fetch_env(char *var, char **env);
int _atoi(char *str);

#endif
