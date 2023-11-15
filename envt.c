#include "shell.h"

/**
 * retv_envi - a fun that returns string array copy of environ
 * @infostruct: Structure that contains argument.
 * Return: Always 0
 */
char **retv_envi(info_t *infostruct)
{
	if (!infostruct->environ || infostruct->env_changed)
	{
		infostruct->environ = list_2_str(infostruct->env);
		infostruct->env_changed = 0;
	}

	return (infostruct->environ);
}

/**
 * un_env - functn that Remove an env't var
 * @infostruct: Structure that contain potential arguments.
 *  Return: 1 on delete, 0 otherwise
 * @varia: the string env't variable property
 */
int un_env(info_t *infostruct, char *varia)
{
	list_t *node = infostruct->env;
	size_t g = 0;
	char *k;

	if (!node || !varia)
		return (0);

	while (node)
	{
		k = start_sub_string(node->str, varia);
		if (k && *k == '=')
		{
			infostruct->env_changed = del_node(&(infostruct->env), g);
			g = 0;
			node = infostruct->env;
			continue;
		}
		node = node->next;
		g++;
	}
	return (infostruct->env_changed);
}

/**
 * set_environ - function Initialize a new env't var, or modify
 * @infostruct: Structure that contain potential arguments
 * @varia: string env't varia property
 * @value: string env't varia value
 *  Return: Always 0
 */
int set_environ(info_t *infostruct, char *varia, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *k;

	if (!varia || !value)
		return (0);

	buf = malloc(leng_string(varia) + leng_string(value) + 2);
	if (!buf)
		return (1);
	cpy_string(buf, varia);
	conc_2_stri(buf, "=");
	conc_2_stri(buf, value);
	node = infostruct->env;
	while (node)
	{
		k = start_sub_string(node->str, varia);
		if (k && *k == '=')
		{
			free(node->str);
			node->str = buf;
			infostruct->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	end_node(&(infostruct->env), buf, 0);
	free(buf);
	infostruct->env_changed = 1;
	return (0);
}
