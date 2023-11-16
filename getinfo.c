#include "shell.h"

/**
 * clear_info - Initializes an info_t struct.
 * @info: Pointer to the struct to be cleared.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes an info_t struct with the provided arguments.
 * @info: Pointer to the struct to be initialized.
 * @av: Argument vector.
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_string(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = custom_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_aliases(info);
		replace_variables(info);
	}
}

/**
 * free_info - Frees fields of an info_t struct.
 * @info: Pointer to the struct to be freed.
 * @all: Flag indicating whether to free all fields.
 */
void free_info(info_t *info, int all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_string_array(info->environ);
		info->environ = NULL;
		free_and_null((void **)info->cmd_buf);

		if (info->readfd > STDERR_FILENO)
			close(info->readfd);
		custom_putchar(BUF_FLUSH);
	}
}
