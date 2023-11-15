#include "shell.h"

/**
 * cpy_string - a function that copies a string
 * @des: destination
 * @sour: source
 * Return: pointer to the  destination
 */
char *cpy_string(char *des, char *sour)
{
	int g = 0;

	if (des == sour || sour == 0)
		return (des);
	while (sour[g])
	{
		des[g] = sour[g];
		g++;
	}
	des[g] = 0;
	return (des);
}

/**
 * dupli_string - a function that duplicate a string
 * @stri: the string
 * Return: a pointer to the string
 */
char *dupli_string(const char *stri)
{
	int leng = 0;
	char *dupli;

	if (stri == NULL)
		return (NULL);
	while (*stri++)
		leng++;
	dupli = malloc(sizeof(char) * (leng + 1));
	if (!dupli)
		return (NULL);
	for (leng++; leng--;)
		dupli[leng] = *--stri;
	return (dupli);
}

/**
 * print_stri - a function that print string
 *@stri: the printed string
 * Return: Nothin
 */
void print_stri(char *stri)
{
	int g = 0;

	if (!stri)
		return;
	while (stri[g] != '\0')
	{
		write_char(stri[g]);
		g++;
	}
}

/**
 * write_char - a function that  write charact c to stdout
 * @c: The chara to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_char(char c)
{
	static int g;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || g >= WRITE_BUF_SIZE)
	{
		write(1, buff, g);
		g = 0;
	}
	if (c != BUF_FLUSH)
		buff[g++] = c;
	return (1);
}
