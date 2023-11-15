#include "shell.h"

/**
 * print_string_std_error - a func prints string to standard error stream
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void print_string_std_error(char *string)
{
	int g = 0;

	if (!string)
		return;
	while (string[g] != '\0')
	{
		write_char(string[g]);
		g++;
	}
}

/**
 * ewrite_char - a func that writes char c to stderr
 * @c: char to print
 * Return: should be 1 for success
 * or -1 errno
 */
int ewrite_char(char c)
{
	static int g;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || g >= WRITE_BUF_SIZE)
	{
		write(2, buff, g);
		g = 0;
	}
	if (c != BUF_FLUSH)
		buff[g++] = c;
	return (1);
}

/**
 * char_descript - a function that writes char c to a file descr
 * @c: char to print
 * @filed: file descriptor
 *
 * Return: On success 1.
 * On error, -1
 */
int char_descript(char c, int filed)
{
	static int g;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || g >= WRITE_BUF_SIZE)
	{
		write(filed, buff, g);
		g = 0;
	}
	if (c != BUF_FLUSH)
		buff[g++] = c;
	return (1);
}

/**
 * print_descript - a funct that prints an input string
 * @str: the string
 * @filed: the file descriptor
 *
 * Return: the number of chars put
 */
int print_descript(char *str, int filed)
{
	int g = 0;

	if (!str)
		return (0);
	while (*str)
	{
		g += char_descript(*str++, filed);
	}
	return (g);
}
