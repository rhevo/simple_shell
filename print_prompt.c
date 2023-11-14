#include "shell.h"

/**
 * print_prompt - Prints the shell prompt.
 */
void print_prompt(const char *message)
{
	write(STDOUT_FILENO, message , strlen(message));
}
