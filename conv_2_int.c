#include "shell.h"

/**
 * interactv - a func that  returns true if the shell is in interactive mode
 * @info: the structure address
 *
 * Return: should be 1 for interactive mode or 0 if not
 */
int interactv(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * mydelim -a funct that  checks if a char is a delimeter
 * @c: character to check for
 * @delim: string delim
 * Return: should be 1 if true, or 0 if false
 */
int mydelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * myisalpha - a funct that checks for alphabet char
 * @c: input char
 * Return: should be 1 if c is alphabet, or 0 if not
 */

int myisalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * conv_stri_int - a function that converts a string to an integer
 * @stri: string converted
 * Return: 0 if no numbers in the string, otherwise the conv int
 */

int conv_stri_int(char *stri)
{
	int indx, sign = 1, flag = 0, result;
	unsigned int convresult = 0;

	for (indx = 0;  stri[indx] != '\0' && flag != 2; indx++)
	{
		if (stri[indx] == '-')
			sign *= -1;

		if (stri[indx] >= '0' && stri[indx] <= '9')
		{
			flag = 1;
			convresult *= 10;
			convresult += (stri[indx] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -convresult;
	else
		result = convresult;

	return (result);
}
