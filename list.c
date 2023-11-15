#include "shell.h"

/**
 * add_new_node - a func that adds new node to the beginn of list
 * @head: the address of point to head node
 * @str: the str field of new node
 * @num: indxx used by history
 *
 * Return: pointer to new size of list
 */
list_t *add_new_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	set_memory((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = dupli_string(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * end_node - a func that adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: string data field of node
 * @num: the index used by history
 *
 * Return: the size of list
 */
list_t *end_node(list_t **head, const char *str, int num)
{
	list_t *nw_node, *curr_node;

	if (!head)
		return (NULL);

	curr_node = *head;
	nw_node = malloc(sizeof(list_t));
	if (!nw_node)
		return (NULL);
	set_memory((void *)nw_node, 0, sizeof(list_t));
	nw_node->num = num;
	if (str)
	{
		nw_node->str = dupli_string(str);
		if (!nw_node->str)
		{
			free(nw_node);
			return (NULL);
		}
	}
	if (curr_node)
	{
		while (curr_node->next)
			curr_node = curr_node->next;
		curr_node->next = nw_node;
	}
	else
		*head = nw_node;
	return (nw_node);
}

/**
 * show_list_string - funct that prints only the str elem of a linked list
 * @listhd: the  pointer to first node
 * Return: size of list
 */
size_t show_list_string(const list_t *listhd)
{
	size_t g = 0;

	while (listhd)
	{
		print_stri(listhd->str ? listhd->str : "(nil)");
		print_stri("\n");
		listhd = listhd->next;
		g++;
	}
	return (g);
}

/**
 * del_node - a function that deletes node at index
 * @head: the address of pointer to first node
 * @index: the  index delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_node(list_t **head, unsigned int index)
{
	list_t *curr_node, *previ_node;
	unsigned int g = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		curr_node = *head;
		*head = (*head)->next;
		free(curr_node->str);
		free(curr_node);
		return (1);
	}
	curr_node = *head;
	while (curr_node)
	{
		if (g == index)
		{
			previ_node->next = curr_node->next;
			free(curr_node->str);
			free(curr_node);
			return (1);
		}
		g++;
		previ_node = curr_node;
		curr_node = curr_node->next;
	}
	return (0);
}

/**
 * f_list - a funct that frees all nodes of a list
 * @point_hd: the address of point to hd node
 *
 * Return: void
 */
void f_list(list_t **point_hd)
{
	list_t *curr_node, *nxt_node, *head;

	if (!point_hd || !*point_hd)
		return;
	head = *point_hd;
	curr_node = head;
	while (curr_node)
	{
		nxt_node = curr_node->next;
		free(curr_node->str);
		free(curr_node);
		curr_node = nxt_node;
	}
	*point_hd = NULL;
}
