// cd_builtin.c

#include "shell.h"

/**
 * cd_builtin - Changes the current directory of the process.
 * @args: Array of arguments for the cd command.
 */
void cd_builtin(char **args)
{
    char *new_directory;

    // If no argument is given, set new_directory to $HOME
    if (args[1] == NULL)
    {
        new_directory = getenv("HOME");
        if (new_directory == NULL)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    }
    // If the argument is "-", set new_directory to the previous directory
    else if (strcmp(args[1], "-") == 0)
    {
        new_directory = getenv("OLDPWD");
        if (new_directory == NULL)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return;
        }
        printf("%s\n", new_directory);
    }
    // Otherwise, use the provided argument as the new directory
    else
    {
        new_directory = args[1];
    }

    // Save the current directory to OLDPWD
    char *current_directory = getcwd(NULL, 0);
    if (current_directory != NULL)
    {
        setenv("OLDPWD", current_directory, 1);
        free(current_directory);
    }

    // Change the current directory
    if (chdir(new_directory) != 0)
    {
        perror("cd");
    }
    else
    {
        // Update the PWD environment variable
        char *new_pwd = getcwd(NULL, 0);
        if (new_pwd != NULL)
        {
            setenv("PWD", new_pwd, 1);
            free(new_pwd);
        }
    }
}
