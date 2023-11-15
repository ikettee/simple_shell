#include "shell.h"

/**
 * hsh - the function for  main shell loop
 * @info: the parameter & inform structur
 * @av: argum vector from the  main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t readsta = 0;
	int bin_result = 0;

	while (readsta != -1 && bin_result != -2)
	{
		reset_info(info);
		if (interactv(info))
			print_stri("$ ");
		write_char(BUF_FLUSH);
		readsta = retv_input(info);
		if (readsta != -1)
		{
			ini_info(info, av);
			bin_result = find_builtin(info);
			if (bin_result == -1)
				find_comm(info);
		}
		else if (interactv(info))
			write_char('\n');
		loose_info(info, 0);
	}
	create_history(info);
	loose_info(info, 1);
	if (!interactv(info) && info->status)
		exit(info->status);
	if (bin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (bin_result);
}

/**
 * find_builtin - a function that find builtin command
 * @info: the parameter info struct
 * Return: -1 if builtin not found,
 *			0 if builtin is executed successfully,
 *			1 if builtin found but not successfully exec,
 *			-2 for builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int g, built_in_result = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"help", help1},
		{"history", history_list},
		{"setenv", set_env_var},
		{"unsetenv", unset_env_var},
		{"cd", chngdir},
		{"alias", alias_builtin},
		{NULL, NULL}
	};

	for (g = 0; builtintbl[g].type; g++)
		if (comp_string(info->argv[0], builtintbl[g].type) == 0)
		{
			info->line_count++;
			built_in_result = builtintbl[g].func(info);
			break;
		}
	return (built_in_result);
}

/**
 * find_comm - a function that find command in PATH
 * @inform: the parame & info structur
 * Return: void
 */
void find_comm(info_t *inform)
{
	char *comm_path = NULL;
	int g, a;

	inform->path = inform->argv[0];
	if (inform->linecount_flag == 1)
	{
		inform->line_count++;
		inform->linecount_flag = 0;
	}
	for (g = 0, a = 0; inform->arg[g]; g++)
		if (!mydelim(inform->arg[g], " \t\n"))
			a++;
	if (!a)
		return;

	comm_path = find_cmd_path(inform, get_env_var(inform, "PATH="),
			inform->argv[0]);
	if (comm_path)
	{
		inform->path = comm_path;
		fork_comm(inform);
	}
	else
	{
		if ((interactv(inform) || get_env_var(inform, "PATH=")
			|| inform->argv[0][0] == '/') && exec_cmd(inform, inform->argv[0]))
			fork_comm(inform);
		else if (*(inform->arg) != '\n')
		{
			inform->status = 127;
			error_message(inform, "not found\n");
		}
	}
}

/**
 * fork_comm - a function tha fork exec thread to run cmd
 * @inform: parame & info struct
 * Return: void
 */
void fork_comm(info_t *inform)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inform->path, inform->argv, retv_envi(inform)) == -1)
		{
			loose_info(inform, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inform->status));
		if (WIFEXITED(inform->status))
		{
			inform->status = WEXITSTATUS(inform->status);
			if (inform->status == 126)
				error_message(inform, "Permission denied\n");
		}
	}
}
