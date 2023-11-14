#include "shell.h"

/**
 * execute_command - Executes a command in a child process.
 * @command: The command to be executed.
 * @args: Array of arguments for the command.
 * @path_list: List of directories in the PATH environment variable.
 */
void execute_command(char *command, char **args, char **path_list)
{
    // Check if the command is "cd"
    if (strcmp(command, "cd") == 0)
    {
        cd_builtin(args);
    }
    // Check if the command is "setenv"
    else if (strcmp(command, "setenv") == 0)
    {
        setenv_builtin(args);
    }
    // Check if the command is "unsetenv"
    else if (strcmp(command, "unsetenv") == 0)
    {
        unsetenv_builtin(args);
    }
    // Check if the command is "exit"
    else if (strcmp(command, "exit") == 0)
    {
        // If there is an argument, use it as the exit status
        if (args[1] != NULL)
        {
            int exit_status = atoi(args[1]);
            exit(exit_status);
        }
        else
        {
            // If no argument provided, exit with status 0
            exit(0);
        }
    }
    // Check if the command is a valid external command
    else
    {
        execute_external_command(command, args, path_list);
    }
}

/* Add a new function for executing external commands*/
void execute_command(char *command, char **args, char **path_list)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		/* Child process */
		char *full_path = find_command_path(command, path_list);

		if (full_path != NULL)
		{
			execv(full_path, args);
			perror("Execution failed");
			free(full_path);
		}
		else
		{
			fprintf(stderr, "Command not found: %s\n", command);
		}
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
 * find_command_path - Finds the full path of
 * a command in the PATH directories.
 * @command: The command to be found.
 * @path_list: List of directories in the PATH environment variable.
 * Return: Full path
 */
char *find_command_path(char *command, char **path_list)
{
	while (*path_list != NULL)
	{
		char *full_path = build_full_path(*path_list, command);

		if (access(full_path, F_OK) == 0)
		{
			return (full_path);
		}
		free(full_path);
		path_list++;
	}
	return (NULL);
}

/**
 * build_full_path - Builds the full path of a command.
 * @directory: The directory containing the command.
 * @command: The command to be appended to the directory.
 * Return: Full path of the command.
 */
char *build_full_path(char *directory, char *command)
{
	size_t dir_len = strlen(directory);
	size_t cmd_len = strlen(command);
	/* 1 for '/' and 1 for '\0' */
	char *full_path = (char *)malloc(dir_len + cmd_len + 2);

	if (full_path != NULL)
	{
		strcpy(full_path, directory);
		full_path[dir_len] = '/';
		strcpy(full_path + dir_len + 1, command);
	}
	return (full_path);
}

/**
 * get_path_directories - Retrieves the list of
 * directories from the PATH environment variable.
 * Return: Array of strings representing directories in the PATH.
 */
char **get_path_directories(void)
{
	char **path_list = malloc(sizeof(char *) * 2);

	path_list[0] = strdup("/bin");
	path_list[1] = NULL;

	return (path_list);
}

/**
 * free_path_list - Frees the memory allocated
 * for the list of directories.
 * @path_list: Array of strings representing directories in the PATH.
 */
void free_path_list(char **path_list)
{
	int i;

	for (i = 0; path_list[i] != NULL; i++)
	{
		free(path_list[i]);
	}
	free(path_list);
}
