#include "shell.h"

/**
 * print_prompt - Prints the shell prompt with a new line.
 */
void print_prompt(void);

/**
 * run_shell - Runs the simple shell program.
 */
void run_shell(void);

/**
 * execute_command - Executes a command in a child process.
 * @command: The command to be executed.
 * @args: Array of arguments for the command.
 * @path_list: List of directories in the PATH environment variable.
 */
void execute_command(char *command, char **args, char **path_list);

/**
 * find_command_path - Finds the full path of a command in the PATH directories.
 * @command: The command to be found.
 * @path_list: List of directories in the PATH environment variable.
 * @return: Full path of the command if found, NULL otherwise.
 */
char *find_command_path(char *command, char **path_list);

/**
 * build_full_path - Builds the full path of a command.
 * @directory: The directory containing the command.
 * @command: The command to be appended to the directory.
 * @return: Full path of the command.
 */
char *build_full_path(char *directory, char *command);
