#include "shell.h"

/**
 * execute_command - Executes a command in a child process.
 * @command: The command to be executed.
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		/* Child process */
		char **args = (char **)malloc(2 * sizeof(char *));

		if (args == NULL)
		{
			perror("Memory allocation failed");
			_exit(EXIT_FAILURE);
		}

		args[0] = command;
		args[1] = NULL;

		execve(command, args, NULL);
		perror("Execution failed");
		free(args); /* Free the allocated memory */
		_exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		/* Parent process */
		wait(NULL); /* Wait for the child to finish */
	}
	else
	{
		perror("Fork failed");
	}
}

/**
 * run_shell - Runs the simple shell program.
 */
void run_shell(void)
{
	char input[MAX_INPUT_SIZE];
	char *command;
	char *args[MAX_INPUT_SIZE / 2]; /*Assuming a maximum*/
	/*of MAX_INPUT_SIZE/2 arguments */
	int i;

	while (1)
	{
		/* Print the shell prompt */
		print_prompt();

		/* Read user input */
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			/* Check for end-of-file condition (Ctrl+D) */
			print_prompt(); /* Display prompt on a new line*/
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
		execute_command(input);
	}
}
