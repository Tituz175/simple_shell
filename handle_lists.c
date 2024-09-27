#include "main.h"

/**
 * add_sep_end - Adds a separator at the end of a st_separtor_list.
 *
 * This function creates a new node with the specified separator 
 * and appends it to the end of the linked list. If the list is empty,
 * the new node becomes the head of the list.
 *
 * @head: A pointer to the head of the st_separtor_list linked list.
 * @seperator: The separator character to be added (e.g., ';', '|', '&').
 *
 * Return: A pointer to the head of the st_separtor_list linked list.
 *         Returns NULL if memory allocation fails.
 */
st_separtor_list *add_sep_end(st_separtor_list **head, char seperator)
{
	st_separtor_list *new, *temp;

	new = malloc(sizeof(st_separtor_list));
	if (new == NULL)
		return (NULL);  // Return NULL if memory allocation fails

	new->separator = seperator;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)  // If the list is empty
	{
		*head = new;  // Set the new node as the head
	}
	else
	{
		while (temp->next != NULL)  // Traverse to the end of the list
			temp = temp->next;
		temp->next = new;  // Link the new node at the end
	}

	return (*head);  // Return the head of the list
}

/**
 * free_st_separtor_list - Frees the memory allocated for a st_separtor_list.
 *
 * This function traverses the st_separtor_list linked list and frees
 * each node to avoid memory leaks. After freeing, it sets the head 
 * pointer to NULL.
 *
 * @head: A pointer to the head of the st_separtor_list linked list.
 */
void free_st_separtor_list(st_separtor_list **head)
{
	st_separtor_list *temp;
	st_separtor_list *curr;

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

/**
 * add_line_end - Adds a command line at the end of a sh_command_line list.
 *
 * This function creates a new node containing the specified command line 
 * and appends it to the end of the linked list. If the list is empty,
 * the new node becomes the head of the list.
 *
 * @head: A pointer to the head of the sh_command_line linked list.
 * @line: The command line string to be added.
 *
 * Return: A pointer to the head of the sh_command_line linked list.
 *         Returns NULL if memory allocation fails.
 */
sh_command_line *add_line_end(sh_command_line **head, char *line)
{
	sh_command_line *new, *temp;

	new = malloc(sizeof(sh_command_line));
	if (new == NULL)
		return (NULL);  // Return NULL if memory allocation fails

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)  // If the list is empty
	{
		*head = new;  // Set the new node as the head
	}
	else
	{
		while (temp->next != NULL)  // Traverse to the end of the list
			temp = temp->next;
		temp->next = new;  // Link the new node at the end
	}

	return (*head);  // Return the head of the list
}

/**
 * free_sh_command_line - Frees the memory allocated for a sh_command_line list.
 *
 * This function traverses the sh_command_line linked list and frees
 * each node to avoid memory leaks. After freeing, it sets the head 
 * pointer to NULL.
 *
 * @head: A pointer to the head of the sh_command_line linked list.
 */
void free_sh_command_line(sh_command_line **head)
{
	sh_command_line *temp;
	sh_command_line *curr;

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

/**
 * add_var_end - Adds a variable at the end of a sh_variable_list list.
 *
 * This function creates a new node containing the variable's name and
 * value and appends it to the end of the linked list. If the list is empty,
 * the new node becomes the head of the list.
 *
 * @head: A pointer to the head of the sh_variable_list linked list.
 * @length_var: The length of the given variable name.
 * @val: The value of the variable to be added.
 * @length_val: The length of the given variable value.
 *
 * Return: A pointer to the head of the sh_variable_list linked list.
 *         Returns NULL if memory allocation fails.
 */
sh_variable_list *add_var_end(sh_variable_list **head,
int length_var, char *val, int length_val)
{
	sh_variable_list *new, *temp;

	new = malloc(sizeof(sh_variable_list));
	if (new == NULL)
		return (NULL);  // Return NULL if memory allocation fails

	new->len_var = length_var;
	new->val = val;
	new->len_val = length_val;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)  // If the list is empty
	{
		*head = new;  // Set the new node as the head
	}
	else
	{
		while (temp->next != NULL)  // Traverse to the end of the list
			temp = temp->next;
		temp->next = new;  // Link the new node at the end
	}

	return (*head);  // Return the head of the list
}
