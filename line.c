#include "shell.h"

/**
 * buff_input - a function that buffer chain command
 * @infostruct: the parameter structure
 * @buff: buffer address
 * @leng: the  address of leng varia
 *
 * Return: bytes read
 */
ssize_t buff_input(info_t *infostruct, char **buff, size_t *leng)
{
	ssize_t g = 0;
	size_t leng_k = 0;

	if (!*leng) /* if it is not left in the buff, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sig_numb_Handle);
#if USE_GETLINE
		g = getline(buff & leng_k, stdin);
#else
		g = next_line(infostruct, buff, &leng_k);
#endif
		if (g > 0)
		{
			if ((*buff)[g - 1] == '\n')
			{
				(*buff)[g - 1] = '\0'; /* remove trail newline */
				g--;
			}
			infostruct->linecount_flag = 1;
			replace_comment(*buff);
			add_history_list(infostruct, *buff, infostruct->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*leng = g;
				infostruct->cmd_buf = buff;
			}
		}
	}
	return (g);
}

/**
 * retv_input - a function that retrieve a line minus the newline
 * @infostruct: the parameter structure
 * Return: bytes read
 */
ssize_t retv_input(info_t *infostruct)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t g, k, leng;
	ssize_t h = 0;
	char **buff_g = &(infostruct->arg), *u;

	write_char(BUF_FLUSH);
	h = buff_input(infostruct, &buff, &leng);
	if (h == -1) /* EOF */
		return (-1);
	if (leng)	/* commands left in the chain buffer */
	{
		k = g; /* init new iterator current buff positn */
		u = buff + g; /* get pointer for return */

		check_chain_deli(infostruct, buff, &k, g, leng);
		while (k < leng) /* iterate to ; or end */
		{
			if (curr_char_chain_deli(infostruct, buff, &k))
				break;
			k++;
		}

		g = k + 1; /* increment past nulled ';'' */
		if (g >= leng) /* reached end of buffer? */
		{
			g = leng = 0; /* reset position and length */
			infostruct->cmd_buf_type = CMD_NORM;
		}

		*buff_g = u; /* pass back point to current command position */
		return (leng_string(u)); /* return leng of current command */
	}

	*buff_g = buff; /* else not a chain, pass back buff from _getline() */
	return (h); /* return length bufr from _getline() */
}

/**
 * my_read_buff - a function that read buffer
 * @infostruct: the  parameter structure
 * @buff:  a buffer
 * @g: for the size
 *
 * Return: h
 */
ssize_t my_read_buff(info_t *infostruct, char *buff, size_t *g)
{
	ssize_t h = 0;

	if (*g)
		return (0);
	h = read(infostruct->readfd, buff, READ_BUF_SIZE);
	if (h >= 0)
		*g = h;
	return (h);
}

/**
 * next_line - a function that get next line of input from stdin
 * @infostruct: the parameter structure
 * @point: address of pointer to buffer
 * @leng: the size of preallocated pointer buffer if not NULL
 *
 * Return: x
 */
int next_line(info_t *infostruct, char **point, size_t *leng)
{
	static char buff[READ_BUF_SIZE];
	static size_t g, le;
	size_t m;
	ssize_t h = 0, x = 0;
	char *u = NULL, *new_g = NULL, *e;

	u = *point;
	if (u && leng)
		x = *leng;
	if (g == le)
		g = le = 0;

	h = my_read_buff(infostruct, buff, &le);
	if (h == -1 || (h == 0 && le == 0))
		return (-1);

	e = locate_char(buff + g, '\n');
	m = e ? 1 + (unsigned int)(e - buff) : le;
	new_g = alloc_mem(u, x, x ? x + m : m + 1);
	if (!new_g) /* If  MALLOC FAILURE! */
		return (u ? free(u), -1 : -1);

	if (x)
		stringcat(new_g, buff + g, m - g);
	else
		my_strncpy(new_g, buff + g, m - g + 1);

	x += m - g;
	g = m;
	u = new_g;

	if (leng)
		*leng = x;
	*point = u;
	return (x);
}

/**
 * sig_numb_Handle - a function that gives blocks ctrl-C
 * @sig_numb: signal #
 * Return: void
 */
void sig_numb_Handle(__attribute__((unused))int sig_numb)
{
	print_stri("\n");
	print_stri("$ ");
	write_char(BUF_FLUSH);
}
