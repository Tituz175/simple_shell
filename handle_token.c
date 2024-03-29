#include "main.h"

/**
 * char_switch -> this function switch these char | and &
 * to non-printed characters
 * @input: input line string
 * @flag: type of switch
 * Return: switched string
 */
char *char_switch(char *input, int flag)
{
	int i;

	if (flag == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}


/**
 * join_nodes -> this function add separators and command
 * lines to the st_separtor_list and sh_command_line
 * @head_s: head of st_separtor_list
 * @head_l: head of sh_command_line list
 * @input: input line string
 */
void join_nodes(st_separtor_list **head_s, sh_command_line **head_l,
	char *input)
{
	int i;
	char *line;
	char *sep = ";|&";

	input = char_switch(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (strchr(sep, input[i]))
			add_sep_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_end(head_s, input[i]);
			i++;
		}
	}

	line = strtok(input, sep);
	do {
		line = char_switch(line, 1);
		add_line_end(head_l, line);
		line = strtok(NULL, sep);
	} while (line != NULL);

}

/**
 * next_command -> this function moves to
 * the next command line in storage
 * @list_s: the needed separator list (st_separtor_list)
 * @list_l: the needed command line list (sh_command_line)
 * @s_datas: shell data structure
 */
void next_command(st_separtor_list **list_s, sh_command_line **list_l,
	st_shell *s_datas)
{
	st_separtor_list *ls_s = *list_s;
	sh_command_line *ls_l = *list_l;

	while (ls_s != NULL)
	{
		if (s_datas->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				break;
			else if (ls_s->separator == '|')
				ls_l = ls_l->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				break;
			else if (ls_s->separator == '&')
				ls_l = ls_l->next;
		}

		ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * tokenize_commands -> this function splits command lines according using
 * separators and executes them
 * @s_datas: shell data structure
 * @input: input line string
 * Return: 1 - continue while 0 - exit,
 */
int tokenize_commands(st_shell *s_datas, char *input)
{

	st_separtor_list *head_s, *list_s;
	sh_command_line *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	join_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		s_datas->input = list_l->line;
		s_datas->args = tokenize_input(s_datas->input);
		loop = locate_command(s_datas);
		free(s_datas->args);

		if (loop == 0)
			break;

		next_command(&list_s, &list_l, s_datas);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_st_separtor_list(&head_s);
	free_sh_command_line(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * tokenize_input -> this function tokenizes
 * given input line string
 * @input: input line string.
 * Return: array of tokens.
 */
char **tokenize_input(char *input)
{
	size_t buffersize = TOKEN_BUFFERSIZE, i = 0;
	char **tokens = malloc(buffersize * sizeof(char *));
	char *token;

	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOKEN_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == buffersize)
		{
			buffersize += TOKEN_BUFFERSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * buffersize);
			if (tokens == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKEN_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
