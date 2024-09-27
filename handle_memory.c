#include "main.h"

/**
 * _realloc - Reallocates memory for a previously allocated block.
 *
 * This function reallocates a memory block pointed to by ptr,
 * resizing it to new_size. If new_size is greater than old_size,
 * the extra memory will be uninitialized. If new_size is equal to
 * old_size, the same pointer is returned. If new_size is zero, 
 * the function frees the memory and returns NULL.
 *
 * @ptr: A pointer to the previously allocated memory.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: 
 *         - If new_size == old_size, returns ptr.
 *         - If new_size == 0 and ptr is not NULL, returns NULL.
 *         - Otherwise, returns a pointer to the reallocated memory block.
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
 * _memcpy - Copies data from one memory location to another.
 *
 * This function copies n bytes from the source memory area to the 
 * destination memory area. It assumes that the memory areas do not
 * overlap.
 *
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
 * _reallocdp - Reallocates memory for a double pointer (array of strings).
 *
 * This function reallocates memory for a double pointer (an array of 
 * strings) by allocating a new memory block and copying the contents
 * from the old block. If ptr is NULL, it allocates memory for new_size.
 * If new_size is equal to old_size, it returns ptr unchanged.
 *
 * @ptr: Double pointer to the previously allocated memory.
 * @old_size: Size in bytes of the allocated space of ptr.
 * @new_size: New size in bytes of the new memory block.
 *
 * Return: 
 *         - If new_size == old_size, returns ptr.
 *         - If new_size == 0 and ptr is not NULL, returns NULL.
 *         - Otherwise, returns a pointer to the reallocated memory block.
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
 * free_var_list - Frees the memory allocated for a sh_variable_list.
 *
 * This function traverses the sh_variable_list linked list and frees
 * each node to prevent memory leaks. After freeing, it sets the head 
 * pointer to NULL.
 *
 * @head: A pointer to the head of the sh_variable_list linked list.
 */
void free_var_list(sh_variable_list **head)
{
	sh_variable_list *temp;
	sh_variable_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)  // Traverse and free nodes
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;  // Set head to NULL after freeing
	}
}
