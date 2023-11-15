#include "shell.h"

/**
 * exit_shell - a function that exits shell
 * @info: Structure that contains potential arguments
 *  Return: exits with this exit status
 *         (0) for info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int checkexit;

	if (info->argv[1])  /* find an exit arguement */
	{
		checkexit = strint(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			error_message(info, "Illegal number: ");
			print_string_std_error(info->argv[1]);
			write_char('\n');
			return (1);
		}
		info->err_num = strint(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * chngdir - a funct that changes the current dir
 * @info: Structure that contains potential arguments.
 *  Return: Should be 0
 */
int chngdir(info_t *info)
{
	char *g, *d, buffer[1024];
	int chndir;

	g = getcwd(buffer, 1024);
	if (!g)
		print_stri("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		d = get_env_var(info, "HOME=");
		if (!d)
			chndir = /* what should this be? */
				chdir((d = get_env_var(info, "PWD=")) ? d : "/");
		else
			chndir = chdir(d);
	}
	else if (comp_string(info->argv[1], "-") == 0)
	{
		if (!get_env_var(info, "OLDPWD="))
		{
			print_stri(g);
			write_char('\n');
			return (1);
		}
		print_stri(get_env_var(info, "OLDPWD=")), write_char('\n');
		chndir = /* should this */
			chdir((d = get_env_var(info, "OLDPWD=")) ? d : "/");
	}
	else
		chndir = chdir(info->argv[1]);
	if (chndir == -1)
	{
		error_message(info, "can't cd to ");
		print_string_std_error(info->argv[1]), write_char('\n');
	}
	else
	{
		set_environ(info, "OLDPWD", get_env_var(info, "PWD="));
		set_environ(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help1 - a function that  changes the current dir
 * @info: Structure that contain potential arguments
 *  Return: should be 0
 */
int help1(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	print_stri("help call works. Function not yet implemented \n");
	if (0)
		print_stri(*arg_array); /* workaround */
	return (0);
}
