#include "main.h"

/**
 * environ_var_check - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void environ_var_check(sh_variable_list **h, char *in, st_shell *data)
{
	char **_envr = data->_environ;
	int i, j = 0;

	while (_envr[j] != NULL)
	{
		char *env_var = _envr[j];
		int k = 0;

		while (in[k] == env_var[k] && env_var[k] != '=')
			k++;

		if (env_var[k] == '=')
		{
			int len = _strlen(env_var + k + 1);

			add_rvar_node(h, k, env_var + k + 1, len);
			return;
		}

		j++;
	}

	i = 0;

	while (in[i] != ' ' && in[i] != '\t' && in[i] !=
	';' && in[i] != '\n' && in[i] != '\0')
		i++;

	add_rvar_node(h, i, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(sh_variable_list **h, char *in, char *st, st_shell *data)
{
	int i = 0, lst = _strlen(st), lpd = _strlen(data->pid);

	while (in[i])
	{
		switch (in[i])
		{
			case '$':
				switch (in[++i])
				{
					case '?':
						add_rvar_node(h, 2, st, lst);
						break;
					case '$':
						add_rvar_node(h, 2, data->pid, lpd);
						break;
					case '\n':
					case '\0':
					case ' ':
					case '\t':
					case ';':
						add_rvar_node(h, 0, NULL, 0);
						break;
					default:
						environ_var_check(h, in + i, data);
						break;
				}
			break;
		default:
			break;
		}
		i++;
	}
	return (i);
}


/**
 * sub_input -> this function changes given string into variables
 *
 * @head: head of the linked list.
 * @input: the give input string.
 * @new_input: the new generated input string.
 * @size: the desired length of the new string.
 * Return: the newly generated string input.
 */
char *sub_input(sh_variable_list **head, char *input,
	char *new_input, int size)
{
	int i, k;
	sh_variable_list *indx = *head;
	char *output = new_input;

	for (i = 0; i < size; i++)
	{
		if (input[i] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				*output++ = input[i++];
			}
			else if (indx->len_var && !(indx->len_val))
			{
				i += indx->len_var - 1;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					*output++ = indx->val[k];
				}
				i += indx->len_var - 1;
			}
			indx = indx->next;
		}
		else
		{
			*output++ = input[i];
		}
	}

	return (new_input);
}


/**
 * swap_variable - calls functions to replace string into vars
 *
 * @input: input string
 * @s_datas: data structure
 * Return: replaced string
 */
char *swap_variable(char *input, st_shell *s_datas)
{
	sh_variable_list *head, *index;
	char *status, *new_input;
	int old_len, new_len;

	status = aux_itoa(s_datas->status);
	head = NULL;

	old_len = check_vars(&head, input, status, s_datas);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	new_len = 0;

	while (index != NULL)
	{
		new_len += (index->len_val - index->len_var);
		index = index->next;
	}

	new_len += old_len;

	new_input = malloc(sizeof(char) * (new_len + 1));
	if (new_input == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	new_input[new_len] = '\0';
	new_input = sub_input(&head, input, new_input, new_len);

	free(input);
	free(status);
	free_rvar_list(&head);
	return (new_input);
}


/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}
