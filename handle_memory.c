#include "main.h"

/**
 * _realloc -> this function reallocates a memory using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int copy_size;
	void *result;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	result = malloc(new_size);
	if (result == NULL)
		return (NULL);

	if (ptr != NULL)
	{
		copy_size = (old_size < new_size) ? old_size : new_size;
		_memcpy(result, ptr, copy_size);
		free(ptr);
	}

	return (result);
}

/**
 * _memcpy -> this function copies data from one memory
 * location to another.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source of data to be copied.
 * @n: Number of bytes to copy.
 */
void _memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned int i;
	char *char_dest = (char *)dest;
	char *char_src = (char *)src;

	for (i = 0; i < n; i++)
		char_dest[i] = char_src[i];
}

/**
 * _reallocdp -> this function reallocates a memory for a
 * double pointer using malloc and free.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}

/**
 * free_var_list -> this function frees a sh_variable_list list
 * @head: head of the sh_variable_list linked list.
 */
void free_var_list(sh_variable_list **head)
{
	sh_variable_list *temp;
	sh_variable_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
