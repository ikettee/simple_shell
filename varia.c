#include "shell.h"

/**
 * curr_char_chain_deli - a funct that check if current char in buffer
 * @inform: the parame structur
 * @buff: the chara buff
 * @pointr: address of current positn in buff
 * Return: 1 if chain delime, 0 otherwise
 */
int curr_char_chain_deli(info_t *inform, char *buff, size_t *pointr)
{
	size_t y = *pointr;

	if (buff[y] == '|' && buff[y + 1] == '|')
	{
		buff[y] = 0;
		y++;
		inform->cmd_buf_type = CMD_OR;
	}
	else if (buff[y] == '&' && buff[y + 1] == '&')
	{
		buff[y] = 0;
		y++;
		inform->cmd_buf_type = CMD_AND;
	}
	else if (buff[y] == ';') /* see end of this command */
	{
		buff[y] = 0; /* replace ; with null */
		inform->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pointr = y;
	return (1);
}

/**
 * check_chain_deli - a funct check to continue chaining based on last status
 * @inf: the parame structur
 * @bu: the chara buff
 * @pntr: address of current positn in buff
 * @g: starting positn in buff
 * @leng: length of buff
 * Return: Void
 */
void check_chain_deli(info_t *inf, char *bu, size_t *pntr,
		size_t g, size_t leng)
{
	size_t y = *pntr;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			bu[g] = 0;
			y = leng;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			bu[g] = 0;
			y = leng;
		}
	}

	*pntr = y;
}

/**
 * replace_alias_stri - a func replaces an aliases in the tokenized stri
 * @inform: the parame structur
 * Return: 1 if replaced, or 0 if not
 */
int replace_alias_stri(info_t *inform)
{
	int g;
	list_t *node;
	char *pointr;

	for (g = 0; g < 10; g++)
	{
		node = nd_start(inform->alias, inform->argv[0], '=');
		if (!node)
			return (0);
		free(inform->argv[0]);
		pointr = locate_char(node->str, '=');
		if (!pointr)
			return (0);
		pointr = dupli_string(pointr + 1);
		if (!pointr)
			return (0);
		inform->argv[0] = pointr;
	}
	return (1);
}

/**
 * var_replace - a funct that replaces vars in the tokenized string
 * @inform: the parame structur
 * Return: should be 1 if replaced, or  0 it not
 */
int var_replace(info_t *inform)
{
	int g = 0;
	list_t *node;

	for (g = 0; inform->argv[g]; g++)
	{
		if (inform->argv[g][0] != '$' || !inform->argv[g][1])
			continue;

		if (!comp_string(inform->argv[g], "$?"))
		{
			stri_replace(&(inform->argv[g]),
				dupli_string(conv_num_string(inform->status, 10, 0)));
			continue;
		}
		if (!comp_string(inform->argv[g], "$$"))
		{
			stri_replace(&(inform->argv[g]),
				dupli_string(conv_num_string(getpid(), 10, 0)));

			continue;
		}
		node = nd_start(inform->env, &inform->argv[g][1], '=');
		if (node)
		{
			stri_replace(&(inform->argv[g]),
				dupli_string(locate_char(node->str, '=') + 1));
			continue;
		}
		stri_replace(&inform->argv[g], dupli_string(""));

	}
	return (0);
}

/**
 * stri_replace - a function that  replaces string
 * @oldstri: the address of the old stri
 * @newstri: the  new stri
 *
 * Return: should be 1 if replaced, or 0 if not
 */
int stri_replace(char **oldstri, char *newstri)
{
	free(*oldstri);
	*oldstri = newstri;
	return (1);
}
