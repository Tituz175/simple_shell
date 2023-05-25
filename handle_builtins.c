#include "main.h"

/**
 * locate_command -> this function finds the
 * shell builtins and normal commands.
 *
 * @s_datas: shell datas needed for this function
 * Return: always return 1 on success.
 */
int locate_command(st_shell *s_datas)
{
	int (*builtin)(st_shell *s_datas);

	if (s_datas->args[0] == NULL)
		return (1);

	builtin = shell_builtin(s_datas->args[0]);

	if (builtin != NULL)
		return (builtin(s_datas));

	return (run_command(s_datas));
}

/**
 * exit_command -> This functions execute exits shell command
 *
 * @s_datas: shell datas needed for this function
 * Return: always return 0 on success.
 */
int exit_command(st_shell *s_datas)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (s_datas->args[1] != NULL)
	{
		ustatus = _atoi(s_datas->args[1]);
		is_digit = _isdigit(s_datas->args[1]);
		str_len = _strlen(s_datas->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(s_datas, 2);
			s_datas->status = 2;
			return (1);
		}
		s_datas->status = (ustatus % 256);
	}
	return (0);
}


/**
 * shell_builtin -> this function gets the builtin function base on the user
 * given command.
 * @command: this is the user giver command
 * Return: function pointer of the builtin command
 */
int (*shell_builtin(char *command))(st_shell *)
{
	builtin_function builtin_functions[] = {
		{ "exit", exit_command },
		{ "cd", manage_cd },
		{ "help", get_help },
		{ "env", _myenv },
		{ "setenv", set_myenv_wrapper },
		{ "unsetenv", _unsetenv },
		{ NULL, NULL }
	};
	int index;

	for (index = 0; builtin_functions[index].function_name; index++)
	{
		if (_strcmp(builtin_functions[index].function_name, command) == 0)
			break;
	}

	return (builtin_functions[index].function);
}
