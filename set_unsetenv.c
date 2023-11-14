#include "shell.h"
/**
 * setenv_builtin - setenv
 * @args : ..
 */
void setenv_builtin(char **args)
{
	/* Check if the correct number of arguments is provided */
	if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
	{
		print_prompt();
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 30);
		return;
	}
	/* Set or modify the environment variable */
	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
	}
}

/**
 * unsetenv_builtin - unsetenv
 * @args : ...
 */
void unsetenv_builtin(char **args)
{
	/* Check if the correct number of arguments is provided */
	if (args[1] == NULL || args[2] != NULL)
	{
		print_prompt();
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 26);
		return;
	}
	/* Remove the environment variable */
	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
	}
}
