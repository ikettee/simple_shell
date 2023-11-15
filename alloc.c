#include "shell.h"

/**
 ** set_memory - a funct that set memory with a constant byte
 * @dest: the points to the memory area
 * @byte: the byte to fill the pointer with
 * @count: amount of bytes
 * Return: a pointer to the memory area
 */
char *set_memory(char *dest, char byte, unsigned int count)
{
	unsigned int g;

	for (g = 0; g < count; g++)
		dest[g] = byte;
	return (dest);
}

/**
 * free_array - a function that frees a string
 * @str_array: the array of  string
 */
void free_array(char **str_array)
{
	char **temparr = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temparr);
}

/**
 * alloc_mem - a function that reallocate a memory
 * @previo: the pointer to previous mem
 * @o_size: the size of previous memory
 * @n_size: the size of new block memory
 * Return: pointer to ol'block
 */
void *alloc_mem(void *previo, unsigned int o_size, unsigned int n_size)
{
	char *n_ptr;

	if (!previo)
		return (malloc(n_size));
	if (!n_size)
		return (free(previo), NULL);
	if (n_size == o_size)
		return (previo);

	n_ptr = malloc(n_size);
	if (!n_ptr)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		n_ptr[o_size] = ((char *)previo)[o_size];
	free(previo);
	return (n_ptr);
}
