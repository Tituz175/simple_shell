#include "main.h"

/**
 * without_comment -> this function removes comments
 * from a given input string
 *
 * @in: input string
 * Return: a pointer to the modified input string
 */
char *without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop -> this function continuously reads user
 * input from stdin, processes it and executes any valid commands
 * @s_datas: a struct containing relevant data.
 *
 * Return: void.
 */
void shell_loop(st_shell *s_datas)
{
	int loop_status, eof;
	char *input;

	loop_status = 1;
	while (loop_status == 1)
	{
		write(STDIN_FILENO, "($) ", 4);
		input = read_line(&eof);
		if (eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(s_datas, input) == 1)
			{
				s_datas->status = 2;
				free(input);
				continue;
			}
			input = swap_variable(input, s_datas);
			loop_status = tokenize_commands(s_datas, input);
			s_datas->counter += 1;
			free(input);
		}
		else
		{
			loop_status = 0;
			free(input);
		}
	}
}
