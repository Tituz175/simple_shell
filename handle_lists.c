#include "main.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a st_separtor_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
st_separtor_list *add_sep_node_end(st_separtor_list **head, char sep)
{
	st_separtor_list *new, *temp;

	new = malloc(sizeof(st_separtor_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
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
 * free_st_separtor_list - frees a st_separtor_list
 * @head: head of the linked list.
 * Return: no return.
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
 * add_line_node_end - adds a command line at the end
 * of a sh_command_line.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
sh_command_line *add_line_node_end(sh_command_line **head, char *line)
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
 * free_sh_command_line - frees a sh_command_line
 * @head: head of the linked list.
 * Return: no return.
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
 * add_rvar_node - adds a variable at the end
 * of a sh_variable_list list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
sh_variable_list *add_rvar_node(sh_variable_list **head,
int lvar, char *val, int lval)
{
	sh_variable_list *new, *temp;

	new = malloc(sizeof(sh_variable_list));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

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
