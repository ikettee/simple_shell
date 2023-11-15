#include "shell.h"

/**
 * set_free - a function that  set free a pointer
 * @freeptr: the  address of the pointer that should be free
 * Return: should be 1 if freed, or else 0.
 */
int set_free(void **freeptr)
{
	if (freeptr && *freeptr)
	{
		free(*freeptr);
		*freeptr = NULL;
		return (1);
	}
	return (0);
}
