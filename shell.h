#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void run_shell(void);
void print_prompt(const char *message);
void execute_command(char *command, char **args, char **path_list);
char *find_command_path(char *command, char **path_list);
char *build_full_path(char *directory, char *command);
char **get_path_directories(void);
void free_path_list(char **path_list);
void env_builtin(void);
void print_simple_shell_prompt(void);
char *custom_getline(void);
void unsetenv_builtin(char **args);
void setenv_builtin(char **args);
#endif /* SHELL_H */
