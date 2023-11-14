#include "shell.h"
/**
 * run_shell - Runs the simple shell program.
 */
void run_shell(void)
{
	char input[MAX_INPUT_SIZE];
	char *command;
	char *args[MAX_INPUT_SIZE / 2]; /*Assuming a maximum*/
	/*of MAX_INPUT_SIZE/2 arguments */
	char **path_list = get_path_directories(); /* Define path_list */
	int i;

	while (1)
	{
		/* Print the shell prompt */
		/* print_prompt("EugeneShell> ");*/
		print_simple_shell_prompt();
		/* Read user input */
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			/* Check for end-of-file condition (Ctrl+D) */
			/*print_prompt();  Display prompt on a new line*/
			print_simple_shell_prompt();
			break;
		}
		/* Remove newline character */
		input[strcspn(input, "\n")] = 0;
		/* Exit if the user inputs "exit" */
		if (strcmp(input, "exit") == 0)
			break;
		/* Parse input into command and arguments */
		command = strtok(input, " ");
		args[0] = command;

		i = 1;

		while ((args[i] = strtok(NULL, " ")) != NULL)
		{
			i++;
		}

		/* Execute the command */
		execute_command(command, args, path_list);
	}

	free_path_list(path_list); /* Free the allocated memory for path_list */
}
