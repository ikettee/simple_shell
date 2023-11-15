#include "shell.h"

/**
 * reset_info - function that initializes info_t structure
 * @infostruct: the structure address
 */
void reset_info(info_t *infostruct)
{
	infostruct->arg = NULL;
	infostruct->argv = NULL;
	infostruct->path = NULL;
	infostruct->argc = 0;
}

/**
 * ini_info - a function that  initializes info_t structure
 * @infostruct: the structure address
 * @avec: argument vector
 */
void ini_info(info_t *infostruct, char **avec)
{
	int g = 0;

	infostruct->fname = avec[0];
	if (infostruct->arg)
	{
		infostruct->argv = split_stri(infostruct->arg, " \t");
		if (!infostruct->argv)
		{

			infostruct->argv = malloc(sizeof(char *) * 2);
			if (infostruct->argv)
			{
				infostruct->argv[0] = dupli_string(infostruct->arg);
				infostruct->argv[1] = NULL;
			}
		}
		for (g = 0; infostruct->argv && infostruct->argv[g]; g++)
			;
		infostruct->argc = g;

		replace_alias_stri(infostruct);
		var_replace(infostruct);
	}
}

/**
 * loose_info - a function that frees info_t structure
 * @infostruct: structure address
 * @maj: should be true free
 */
void loose_info(info_t *infostruct, int maj)
{
	free_array(infostruct->argv);
	infostruct->argv = NULL;
	infostruct->path = NULL;
	if (maj)
	{
		if (!infostruct->cmd_buf)
			free(infostruct->arg);
		if (infostruct->env)
			f_list(&(infostruct->env));
		if (infostruct->history)
			f_list(&(infostruct->history));
		if (infostruct->alias)
			f_list(&(infostruct->alias));
		free_array(infostruct->environ);
			infostruct->environ = NULL;
		set_free((void **)infostruct->cmd_buf);
		if (infostruct->readfd > 2)
			close(infostruct->readfd);
		write_char(BUF_FLUSH);
	}
}
