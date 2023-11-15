#include "shell.h"

/**
 * leng_string - a function that return length of a string
 * @stri: the string
 * Return: length of string int
 */
int leng_string(char *stri)
{
	int g = 0;

	if (!stri)
		return (0);

	while (*stri++)
		g++;
	return (g);
}

/**
 * comp_string - a funct that  performs lexicogarphic comparison of two strgs
 * @stri1: 1st strg
 * @stri2: 2nd strg
 * Return: negatv if s1 < s2, positv if s1 > s2, or zero if s1 == s2
 */
int comp_string(char *stri1, char *stri2)
{
	while (*stri1 && *stri2)
	{
		if (*stri1 != *stri2)
			return (*stri1 - *stri2);
		stri1++;
		stri2++;
	}
	if (*stri1 == *stri2)
		return (0);
	else
		return (*stri1 < *stri2 ? -1 : 1);
}

/**
 * start_sub_string - a func that check if needle starts with haystack
 * @haystack: the stri to search
 * @needle: the sub_string to find
 * Return: the address of next charac of haystack or NULL
 */
char *start_sub_string(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * conc_2_stri - a function that concatenates two strings
 * @des: the destinatn buff
 * @sour: the source buff
 * Return: pointer to destinatn buff
 */
char *conc_2_stri(char *des, char *sour)
{
	char *ret = des;

	while (*des)
		des++;
	while (*sour)
		*des++ = *sour++;
	*des = *sour;
	return (ret);
}
