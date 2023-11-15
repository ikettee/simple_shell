#include "shell.h"

/**
 * numb_list - a function that determines the # nodes linked list
 * @curr: point to the first node
 *
 * Return: the size of the linked list
 */
size_t numb_list(const list_t *curr)
{
	size_t g = 0;

	while (curr)
	{
		curr = curr->next;
		g++;
	}
	return (g);
}

/**
 * list_2_str - a function an array of strings of the list
 * @hd: the pointer to first node
 * Return: array of strings
 */
char **list_2_str(list_t *hd)
{
	list_t *node = hd;
	size_t g = numb_list(hd), k;
	char **strs;
	char *str;

	if (!hd || !g)
		return (NULL);
	strs = malloc(sizeof(char *) * (g + 1));
	if (!strs)
		return (NULL);
	for (g = 0; node; node = node->next, g++)
	{
		str = malloc(leng_string(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < g; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = cpy_string(str, node->str);
		strs[g] = str;
	}
	strs[g] = NULL;
	return (strs);
}


/**
 * show_list - a func prints all elements of a link list
 * @curr: the point to first node
 *
 * Return: size of list
 */
size_t show_list(const list_t *curr)
{
	size_t g = 0;

	while (curr)
	{
		print_stri(conv_num_string(curr->num, 10, 0));
		write_char(':');
		write_char(' ');
		print_stri(curr->str ? curr->str : "(nil)");
		print_stri("\n");
		curr = curr->next;
		g++;
	}
	return (g);
}

/**
 * nd_start - a func returns node for wh string start with prefix
 * @curr: the  point to list head
 * @match: the string
 * @nxtchar: the next character
 *
 * Return: the match node or null
 */
list_t *nd_start(list_t *curr, char *match, char nxtchar)
{
	char *matchstr = NULL;

	while (curr)
	{
		matchstr = start_sub_string(curr->str, match);
		if (matchstr && ((nxtchar == -1) || (*matchstr == nxtchar)))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * fetch_node_indx - func gets the index of a node
 * @hd: the point to list head
 * @curr: the point to the node
 * Return: index of node or -1
 */
ssize_t fetch_node_indx(list_t *hd, list_t *curr)
{
	size_t g = 0;

	while (hd)
	{
		if (hd == curr)
			return (g);
		hd = hd->next;
		g++;
	}
	return (-1);
}
