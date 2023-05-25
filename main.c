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
