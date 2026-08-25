#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void prompt(void);
char *input_read(void);
char **get_tokens(char *input);
char *_getline(char **buffer, size_t *size, FILE *stream);
char *_strtok(char *input, char *sep);

#endif
