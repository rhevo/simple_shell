#include "shell.h"

/**
 * env_builtin - Prints the current environment.
 */
void env_builtin(void)
{
	extern char **environ;
	char **env_ptr = environ;

	while (*env_ptr != NULL)
	{
		print_prompt(*env_ptr);
		print_prompt("\n");
		env_ptr++;
	}
}
