#include "shell.h"

/**
 * exec_cmd - a func that determines if a file is an executable command
 * @inform: the information structure
 * @fpath: file path
 *
 * Return: 1 if true, 0 otherwise
 */
int exec_cmd(info_t *inform, char *fpath)
{
	struct stat st;

	(void)inform;
	if (!fpath || stat(fpath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupli_chara - a func that duplicates chars
 * @origstr: the path of original string
 * @startindx: the start index
 * @end: the end index
 * Return: pointer to buffer
 */
char *dupli_chara(char *origstr, int startindx, int end)
{
	static char buff[1024];
	int g = 0, a = 0;

	for (a = 0, g = startindx; g < end; g++)
		if (origstr[g] != ':')
			buff[a++] = origstr[g];
	buff[a] = 0;
	return (buff);
}

/**
 * find_cmd_path - finds this cmd in the PATH string
 * @inform: the info struct
 * @origstr: the PATH string
 * @execcommand: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *find_cmd_path(info_t *inform, char *origstr, char *execcommand)
{
	int g = 0, curr_position = 0;
	char *pathresult;

	if (!origstr)
		return (NULL);
	if ((leng_string(execcommand) > 2) && start_sub_string(execcommand, "./"))
	{
		if (exec_cmd(inform, execcommand))
			return (execcommand);
	}
	while (1)
	{
		if (!origstr[g] || origstr[g] == ':')
		{
			pathresult = dupli_chara(origstr, curr_position, g);
			if (!*pathresult)
				conc_2_stri(pathresult, execcommand);
			else
			{
				conc_2_stri(pathresult, "/");
				conc_2_stri(pathresult, execcommand);
			}
			if (exec_cmd(inform, pathresult))
				return (pathresult);
			if (!origstr[g])
				break;
			curr_position = g;
		}
		g++;
	}
	return (NULL);
}
