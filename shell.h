#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void execute_command(char *command);
void run_shell(void);
void print_prompt(void);

#endif /* SHELL_H */
