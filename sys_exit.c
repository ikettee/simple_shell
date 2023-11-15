#include "shell.h"

/**
 ** my_strncpy - a function that copies a string
 *@destinatn: the string to copy
 *@source: sourace string
 *@mx: the max number of characters to be copied
 *Return: a pointer to the  string
 */
char *my_strncpy(char *destinatn, char *source, int mx)
{
	int g, k;
	char *ss = destinatn;

	g = 0;
	while (source[g] != '\0' && g < mx - 1)
	{
		destinatn[g] = source[g];
		g++;
	}
	if (g < mx)
	{
		k = g;
		while (k < mx)
		{
			destinatn[k] = '\0';
			k++;
		}
	}
	return (ss);
}

/**
 ** stringcat - a funct that concatenates two strings
 * @destinatn: first string
 * @source: the second string
 * @mx: the amount of bytes
 * Return: concatenated string
 */
char *stringcat(char *destinatn, char *source, int mx)
{
	int g, k;
	char *ss = destinatn;

	g = 0;
	k = 0;
	while (destinatn[g] != '\0')
		g++;
	while (source[k] != '\0' && k < mx)
	{
		destinatn[g] = source[k];
		g++;
		k++;
	}
	if (k < mx)
		destinatn[g] = '\0';
	return (ss);
}

/**
 ** locate_char - a funct that locates a character
 * @ss: the string
 * @c: the character
 * Return: (s) a pointer
 */
char *locate_char(char *ss, char c)
{
	do {
		if (*ss == c)
			return (ss);
	} while (*ss++ != '\0');

	return (NULL);
}
