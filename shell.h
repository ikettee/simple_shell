#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* the read or write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* cmd chain */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* to convert number */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - a function that singly link list
 * @num: field number
 * @str: string
 * @next: a pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function
 * @arg: a string generated from getline contain argu
 * @argv: an array of strings generat from arg
 * @path: a string path for the curr command
 * @argc: the arg count
 * @line_count: error count
 * @err_num: error code for exit
 * @linecount_flag: if on count this line of input
 * @fname: program filename
 * @env: linked list local copy of envt
 * @environ: custom modified copy of envt from LL env
 * @history: the history node
 * @alias: alias node
 * @env_changed: on if envt was changed
 * @status: return status of the last exec'd command
 * @cmd_buf: address of point to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for mem mgt */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related funct
 *@type: builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shell_loop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_comm(info_t *);
void fork_comm(info_t *);

/* pars.c */
int exec_cmd(info_t *, char *);
char *dupli_chara(char *, int, int);
char *find_cmd_path(info_t *, char *, char *);

/* loop.c */
int loophsh(char **);

/* stderr.c */
void print_string_std_error(char *);
int ewrite_char(char);
int char_descript(char c, int filed);
int print_descript(char *str, int filed);

/* stri.c */
int leng_string(char *);
int comp_string(char *, char *);
char *start_sub_string(const char *, const char *);
char *conc_2_stri(char *, char *);

/* stri1.c */
char *cpy_string(char *, char *);
char *dupli_string(const char *);
void print_stri(char *);
int write_char(char);

/* sys_exit.c */
char *my_strncpy(char *, char *, int);
char *stringcat(char *, char *, int);
char *locate_char(char *, char);

/* token.c */
char **split_stri(char *, char *);
char **split_stri2(char *, char);

/* alloc.c */
char *set_memory(char *, char, unsigned int);
void free_array(char **);
void *alloc_mem(void *, unsigned int, unsigned int);

/* mem.c */
int set_free(void **);

/* conv_2_int.c */
int interactv(info_t *);
int mydelim(char, char *);
int myisalpha(int);
int conv_stri_int(char *);

/* stderr1.c */
int strint(char *);
void error_message(info_t *, char *);
int print_deci(int, int);
char *conv_num_string(long int, int, int);
void replace_comment(char *);

/* built.c */
int exit_shell(info_t *);
int chngdir(info_t *);
int help1(info_t *);

/* built1.c */
int history_list(info_t *);
int alias_builtin(info_t *);

/* line.c */
ssize_t retv_input(info_t *);
int next_line(info_t *, char **, size_t *);
void sig_numb_Handle(int);

/* info.c */
void reset_info(info_t *);
void ini_info(info_t *, char **);
void loose_info(info_t *, int);

/* env_var.c */
char *get_env_var(info_t *, const char *);
int print_env(info_t *);
int set_env_var(info_t *);
int unset_env_var(info_t *);
int env_linked_list(info_t *);

/* envt.c */
char **retv_envi(info_t *);
int un_env(info_t *, char *);
int set_environ(info_t *, char *, char *);

/* histo.c */
char *history_path(info_t *inform);
int create_history(info_t *inform);
int fetch_history(info_t *inform);
int add_history_list(info_t *inform, char *buff, int line_read);
int history_renumb(info_t *inform);

/* list.c */
list_t *add_new_node(list_t **, const char *, int);
list_t *end_node(list_t **, const char *, int);
size_t show_list_string(const list_t *);
int del_node(list_t **, unsigned int);
void f_list(list_t **);

/* list1.c */
size_t numb_list(const list_t *);
char **list_2_str(list_t *);
size_t show_list(const list_t *);
list_t *nd_start(list_t *, char *, char);
ssize_t fetch_node_indx(list_t *, list_t *);

/* varia.c */
int curr_char_chain_deli(info_t *, char *, size_t *);
void check_chain_deli(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_stri(info_t *);
int var_replace(info_t *);
int stri_replace(char **, char *);

#endif
