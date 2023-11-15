#include "shell.h"

/**
 * **split_stri - a func that splits a string into wrds. Rpeat delimi
 * @stri: input the string
 * @deli: the delime string
 * Return: point to an array of strings, or NULL on failure
 */

char **split_stri(char *stri, char *deli)
{
	int g, y, c, n, nword = 0;
	char **resultarr;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	if (!deli)
		deli = " ";
	for (g = 0; stri[g] != '\0'; g++)
		if (!mydelim(stri[g], deli) && (mydelim(stri[g + 1], deli) || !stri[g + 1]))
			nword++;

	if (nword == 0)
		return (NULL);
	resultarr = malloc((1 + nword) * sizeof(char *));
	if (!resultarr)
		return (NULL);
	for (g = 0, y = 0; y < nword; y++)
	{
		while (mydelim(stri[g], deli))
			g++;
		c = 0;
		while (!mydelim(stri[g + c], deli) && stri[g + c])
			c++;
		resultarr[y] = malloc((c + 1) * sizeof(char));
		if (!resultarr[y])
		{
			for (c = 0; c < y; c++)
				free(resultarr[c]);
			free(resultarr);
			return (NULL);
		}
		for (n = 0; n < c; n++)
			resultarr[y][n] = stri[g++];
		resultarr[y][n] = 0;
	}
	resultarr[y] = NULL;
	return (resultarr);
}

/**
 * **split_stri2 - a function that splits a string into words
 * @stri: input string
 * @deli: delimet
 * Return: point to an array of strings, or NULL on failure
 */
char **split_stri2(char *stri, char deli)
{
	int g, y, c, n, nword = 0;
	char **resultarr;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	for (g = 0; stri[g] != '\0'; g++)
		if ((stri[g] != deli && stri[g + 1] == deli) ||
		    (stri[g] != deli && !stri[g + 1]) || stri[g + 1] == deli)
			nword++;
	if (nword == 0)
		return (NULL);
	resultarr = malloc((1 + nword) * sizeof(char *));
	if (!resultarr)
		return (NULL);
	for (g = 0, y = 0; y < nword; y++)
	{
		while (stri[g] == deli && stri[g] != deli)
			g++;
		c = 0;
		while (stri[g + c] != deli && stri[g + c] && stri[g + c] != deli)
			c++;
		resultarr[y] = malloc((c + 1) * sizeof(char));
		if (!resultarr[y])
		{
			for (c = 0; c < y; c++)
				free(resultarr[c]);
			free(resultarr);
			return (NULL);
		}
		for (n = 0; n < c; n++)
			resultarr[y][n] = stri[g++];
		resultarr[y][n] = 0;
	}
	resultarr[y] = NULL;
	return (resultarr);
}
