#include "main.h"

/**
 * environ_var_check -> this function verify maybe the variable
 * is an environment variable
 * @head: the head of sh_variable_list linked list
 * @input: input line string
 * @data: shell data structure
 */
void environ_var_check(sh_variable_list **head, char *input, st_shell *data)
{
	char **_envr = data->_environ;
	int i, j = 0;

	while (_envr[j] != NULL)
	{
		char *env_var = _envr[j];
		int k = 0;

		while (input[k] == env_var[k] && env_var[k] != '=')
			k++;

		if (env_var[k] == '=')
		{
			int len = _strlen(env_var + k + 1);

			add_var_end(head, k, env_var + k + 1, len);
			return;
		}

		j++;
	}

	i = 0;

	while (input[i] != ' ' && input[i] != '\t' && input[i] !=
	';' && input[i] != '\n' && input[i] != '\0')
		i++;

	add_var_end(head, i, NULL, 0);
}

/**
 * verify_variable ->this function verify maybe the variable is $$ or $?
 * @head: head of the sh_variable_list linked list
 * @input: input line string
 * @s_last: shell last status
 * @data: shell data structure
 * Return: int
 */
int verify_variable(sh_variable_list **head, char *input,
	char *s_last, st_shell *data)
{
	int i = 0, lst = _strlen(s_last), lpd = _strlen(data->pid);

	while (input[i])
	{
		switch (input[i])
		{
			case '$':
				switch (input[++i])
				{
					case '?':
						add_var_end(head, 2, s_last, lst);
						break;
					case '$':
						add_var_end(head, 2, data->pid, lpd);
						break;
					case '\n':
					case '\0':
					case ' ':
					case '\t':
					case ';':
						add_var_end(head, 0, NULL, 0);
						break;
					default:
						environ_var_check(head, input + i, data);
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
 * @head: head of the sh_variable_list linked list.
 * @input: the give input line string.
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
 * swap_variable -> this function to replace string to
 * variable.
 * @s_datas: shell data structure
 * @input: input line string
 * Return: string
 */
char *swap_variable(char *input, st_shell *s_datas)
{
	sh_variable_list *head, *index;
	char *status, *new_input;
	int old_len, new_len;

	status = aux_itoa(s_datas->status);
	head = NULL;

	old_len = verify_variable(&head, input, status, s_datas);

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
	free_var_list(&head);
	return (new_input);
}


/**
 * count_char -> this function counts the number of
 * recusive the of a character
 * @input: input line string
 * @index: index
 * Return: total number of repetitions
 */
int count_char(char *input, int index)
{
	if (*(input - 1) == *input)
		return (count_char(input - 1, index + 1));

	return (index);
}
