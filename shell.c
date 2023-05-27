#include "main.h"

/**
 * main -> Shell program entry point
 *
 * @ac: argument count
 * @argv: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char *argv[])
{
	st_shell s_datas;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&s_datas, argv);
	shell_loop(&s_datas);
	free_data(&s_datas);
	if (s_datas.status < 0)
		return (255);
	return (s_datas.status);
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
			input = filter_out_comment(input);
			if (input == NULL)
				continue;

			if (syntax_error(s_datas, input) == 1)
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
