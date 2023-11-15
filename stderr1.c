#include "shell.h"

/**
 * strint - a function that converts a string to an integer
 * @str: string to convert
 * Return: should be 0 for string, or
 *       -1 on error
 */
int strint(char *str)
{
	int g = 0;
	unsigned long int output = 0;

	if (*str == '+')
		str++;  /* why does this make return 255? */
	for (g = 0;  str[g] != '\0'; g++)
	{
		if (str[g] >= '0' && str[g] <= '9')
		{
			output *= 10;
			output += (str[g] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * error_message - a func that print error message
 * @info: para and return info structure
 * @errstr: the string
 * Return: should be 0 for string, or
 *        -1 on error
 */
void error_message(info_t *info, char *errstr)
{
	print_string_std_error(info->fname);
	print_string_std_error(": ");
	print_deci(info->line_count, STDERR_FILENO);
	print_string_std_error(": ");
	print_string_std_error(info->argv[0]);
	print_string_std_error(": ");
	print_string_std_error(errstr);
}

/**
 * print_deci - a funct that prints a decimal  number
 * @input: the input to print
 * @fd: the file descriptor to input
 *
 * Return: the num of chars to print
 */
int print_deci(int input, int fd)
{
	int (*__putchar)(char) = write_char;
	int g, counting = 0;
	unsigned int previous, current;

	if (fd == STDERR_FILENO)
		__putchar = write_char;
	if (input < 0)
	{
		previous = -input;
		__putchar('-');
		counting++;
	}
	else
		previous = input;
	current = previous;
	for (g = 1000000000; g > 1; g /= 10)
	{
		if (previous / g)
		{
			__putchar('0' + current / g);
			counting++;
		}
		current %= g;
	}
	__putchar('0' + current);
	counting++;

	return (counting);
}

/**
 * conv_num_string - function that convert a a number to a string
 * @numb: the number
 * @base: the base for the conversion
 * @flags: flags for the conversion
 *
 * Return: should be string
 */
char *conv_num_string(long int numb, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *resultptr;
	unsigned long ln = numb;

	if (!(flags & CONVERT_UNSIGNED) && numb < 0)
	{
		ln = -numb;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	resultptr = &buffer[49];
	*resultptr = '\0';

	do	{
		*--resultptr = array[ln % base];
		ln /= base;
	} while (ln != 0);

	if (sign)
		*--resultptr = sign;
	return (resultptr);
}

/**
 * replace_comment - a  func replaces first instance of '#' with '\0'
 * @buf: the address of the string
 *
 * Return: Always 0;
 */
void replace_comment(char *buf)
{
	int g;

	for (g = 0; buf[g] != '\0'; g++)
		if (buf[g] == '#' && (!g || buf[g - 1] == ' '))
		{
			buf[g] = '\0';
			break;
		}
}
