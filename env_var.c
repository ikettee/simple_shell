#include "shell.h"

/**
 * print_env - a function that prints the current environment
 * @info: Structure that contains potential argument.
 * Return: Should be 0
 */
int print_env(info_t *info)
{
	show_list(info->env);
	return (0);
}

/**
 * get_env_var - a function that gets the value of an environ variable
 * @info: Structure that contains potential arguments.
 * @var: environment var name
 *
 * Return: that value
 */
char *get_env_var(info_t *info, const char *var)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = start_sub_string(node->str, var);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env_var - A function that initializes a new environment variable.
 * @info: Structure that contains potential arguments.
 *  Return: Always 0
 */
int set_env_var(info_t *info)
{
	if (info->argc != 3)
	{
		print_string_std_error("Incorrect number of arguements\n");
		return (1);
	}
	if (set_environ(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env_var -a Function that remove an environment variable
 * @info: Structure containing potential argument.
 *  Return: Always 0
 */
int unset_env_var(info_t *info)
{
	int g;

	if (info->argc == 1)
	{
		print_string_std_error("Too few arguements.\n");
		return (1);
	}
	for (g = 1; g <= info->argc; g++)
		un_env(info, info->argv[g]);

	return (0);
}

/**
 * env_linked_list - a function that  populates env linked list
 * @info: Structure that contains potential arguments.
 * Return: Always 0
 */
int env_linked_list(info_t *info)
{
	list_t *node = NULL;
	size_t g;

	for (g = 0; environ[g]; g++)
		end_node(&node, environ[g], 0);
	info->env = node;
	return (0);
}
