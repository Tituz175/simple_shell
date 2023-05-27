#include "main.h"

/**
 * locate_command -> this function finds the
 * shell builtins and normal commands.
 * @s_datas: shell data structure needed for this function
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
 * @s_datas: shell data structure needed for this function
 * Return: always return 0 on success.
 */
int exit_command(st_shell *s_datas)
{
	unsigned int exit_status;
	int isdigit;
	int string_length;
	int max_number;

	if (s_datas->args[1] != NULL)
	{
		exit_status = _atoi(s_datas->args[1]);
		isdigit = _isdigit(s_datas->args[1]);
		string_length = _strlen(s_datas->args[1]);
		max_number = exit_status > (unsigned int)INT_MAX;
		if (!isdigit || string_length > 10 || max_number)
		{
			error_info(s_datas, 2);
			s_datas->status = 2;
			return (1);
		}
		s_datas->status = (exit_status % 256);
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
