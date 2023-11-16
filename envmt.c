#include "shell.h"
/**
 * get_environ - Returns the string array copy of our environment.
 * @info: Structure containing potential arguments.
 * Return: Pointer to the environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
/**
 * shell_unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The string representing the environment variable to remove.
 * Return: returns 1 if the variable was removed, 0 otherwise.
 */
int shell_unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = custom_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env),
					index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}

	return (info->env_changed);
}

/**
 * shell_setenv - Initialize a new environment variable or
 * modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The string representing the environment variable to set.
 * @value: The string representing the value to set for the
 * environment variable.
 * Return: returns 0 on success, 1 on failure.
 */
int shell_setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(custom_strlen(var) + custom_strlen(value) + 2);
	if (!buf)
		return (1);
	custom_strcpy(buf, var);
	custom_strcat(buf, "=");
	custom_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = custom_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
