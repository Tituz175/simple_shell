#include "main.h"

/**
 * add_sep_end -> this function adds a separator found at the end
 * of a st_separtor_list.
 * @head: head of the st_separtor_list linked list.
 * @seperator: separator found (; | &).
 * Return: address of the st_separtor_list head.
 */
st_separtor_list *add_sep_end(st_separtor_list **head, char seperator)
{
	st_separtor_list *new, *temp;

	new = malloc(sizeof(st_separtor_list));
	if (new == NULL)
		return (NULL);

	new->separator = seperator;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_st_separtor_list -> this function frees a st_separtor_list
 * @head: head of the st_separtor_list linked list.
 */
void free_st_separtor_list(st_separtor_list **head)
{
	st_separtor_list *temp;
	st_separtor_list *curr;

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

/**
 * add_line_end -> this function adds a command line at the tail
 * of a sh_command_line.
 * @head: head of the sh_command_line linked list.
 * @line: given command line.
 * Return: address of the sh_command_line head.
 */
sh_command_line *add_line_end(sh_command_line **head, char *line)
{
	sh_command_line *new, *temp;

	new = malloc(sizeof(sh_command_line));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_sh_command_line -> this function frees a sh_command_line
 * @head: sh_command_line head of the linked list.
 */
void free_sh_command_line(sh_command_line **head)
{
	sh_command_line *temp;
	sh_command_line *curr;

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

/**
 * add_var_end -> this function adds a variable at the end
 * of a sh_variable_list list.
 * @head: head of the linked sh_variable_list list.
 * @length_var: length of the given variable.
 * @val: given variable value.
 * @length_val: given variable length.
 * Return: address of the sh_variable_list head.
 */
sh_variable_list *add_var_end(sh_variable_list **head,
int length_var, char *val, int length_val)
{
	sh_variable_list *new, *temp;

	new = malloc(sizeof(sh_variable_list));
	if (new == NULL)
		return (NULL);

	new->len_var = length_var;
	new->val = val;
	new->len_val = length_val;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
