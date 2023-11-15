#include "shell.h"

/**
 * history_path - a function that gets the history file path
 * @inform: the para structure for information
 *
 * Return: contains the history path
 */

char *history_path(info_t *inform)
{
	char *buff, *dir;

	dir = get_env_var(inform, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (leng_string(dir) + leng_string(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	cpy_string(buff, dir);
	conc_2_stri(buff, "/");
	conc_2_stri(buff, HIST_FILE);
	return (buff);
}

/**
 * create_history - a function that creates a file history
 * @inform: the para structure
 *
 * Return: 1 for success, or -1
 */
int create_history(info_t *inform)
{
	ssize_t filed;
	char *filename = history_path(inform);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	filed = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filed == -1)
		return (-1);
	for (node = inform->history; node; node = node->next)
	{
		print_descript(node->str, filed);
		char_descript('\n', filed);
	}
	char_descript(BUF_FLUSH, filed);
	close(filed);
	return (1);
}

/**
 * fetch_history - a function that reads history from file
 * @inform: para structure
 *
 * Return: history count on success, 0 if not
 */
int fetch_history(info_t *inform)
{
	int g, end = 0, line_read = 0;
	ssize_t filed, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = history_path(inform);

	if (!filename)
		return (0);

	filed = open(filename, O_RDONLY);
	free(filename);
	if (filed == -1)
		return (0);
	if (!fstat(filed, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(filed, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(filed);
	for (g = 0; g < fsize; g++)
		if (buff[g] == '\n')
		{
			buff[g] = 0;
			add_history_list(inform, buff + end, line_read++);
			end = g + 1;
		}
	if (end != g)
		add_history_list(inform, buff + end, line_read++);
	free(buff);
	inform->histcount = line_read;
	while (inform->histcount-- >= HIST_MAX)
		del_node(&(inform->history), 0);
	history_renumb(inform);
	return (inform->histcount);
}

/**
 * add_history_list - a funct adds entry to a history list
 * @inform: Structure that contains potential arguments
 * @buff: the buffer
 * @line_read: the history line count
 *
 * Return: Always 0
 */
int add_history_list(info_t *inform, char *buff, int line_read)
{
	list_t *node = NULL;

	if (inform->history)
		node = inform->history;
	end_node(&node, buff, line_read);

	if (!inform->history)
		inform->history = node;
	return (0);
}

/**
 * history_renumb -a funct that re-numbers the history linked
 * @inform: Structure contains potential arguments
 *
 * Return: the new history count
 */
int history_renumb(info_t *inform)
{
	list_t *node = inform->history;
	int g = 0;

	while (node)
	{
		node->num = g++;
		node = node->next;
	}
	return (inform->histcount = g);
}
