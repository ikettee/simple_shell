#include "shell.h"

/**
 * history_list - a function that display the history list
 * @info: Structure that contains potential argument
 *  Return: Should be 0
 */
int history_list(info_t *info)
{
	show_list(info->history);
	return (0);
}

/**
 * un_alias - a function that sets alias to a string
 * @info: the parameter structure
 * @str: alias for the string
 *
 * Return: Should be 0 on success, or 1 for error
 */
int un_alias(info_t *info, char *str)
{
	char *g, k;
	int retu;

	g = locate_char(str, '=');
	if (!g)
		return (1);
	k = *g;
	*g = 0;
	retu = del_node(&(info->alias),
		fetch_node_indx(info->alias, nd_start(info->alias, str, -1)));
	*g = k;

	return (retu);
}

/**
 * s_alias - a function that sets alias to a string
 * @info: the parameter structure
 * @str: alias for the string
 *
 * Return: Should be 0 on success, or 1 for error
 */
int s_alias(info_t *info, char *str)
{
	char *g;

	g = locate_char(str, '=');
	if (!g)
		return (1);
	if (!*++g)
		return (un_alias(info, str));

	un_alias(info, str);
	return (end_node(&(info->alias), str, 0) == NULL);
}

/**
 * prt_alias - a function that prints string alias
 * @node: the node for the alias
 *
 * Return: Should be 0 on success, or 1 for error
 */
int prt_alias(list_t *node)
{
	char *g = NULL, *a = NULL;

	if (node)
	{
		g = locate_char(node->str, '=');
		for (a = node->str; a <= g; a++)
			write_char(*a);
		write_char('\'');
		print_stri(g + 1);
		print_stri("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_builtin - a function that mimics the builtin alias
 * @info: Structure that contains the potential arguments
 *  Return: Should be 0
 */
int alias_builtin(info_t *info)
{
	int g = 0;
	char *k = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			prt_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (g = 1; info->argv[g]; g++)
	{
		k = locate_char(info->argv[g], '=');
		if (k)
			s_alias(info, info->argv[g]);
		else
			prt_alias(nd_start(info->alias, info->argv[g], '='));
	}

	return (0);
}
