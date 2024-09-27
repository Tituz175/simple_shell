#include "main.h"

/**
 * locate_command - This function finds and executes either shell built-in 
 * commands or normal commands based on the input.
 * @s_datas: A pointer to the shell data structure, which holds information
 * about the current command input and environment.
 *
 * Description:
 *  - If no command is given (i.e., args[0] is NULL), the function immediately
 *    returns 1.
 *  - It checks if the command corresponds to a built-in function. If so, 
 *    it executes the built-in command.
 *  - Otherwise, it proceeds to execute an external command.
 *
 * Return: Always returns 1 on success for built-ins or the result of
 * run_command for external commands.
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
 * exit_command - Executes the exit shell command, terminating the shell.
 * @s_datas: A pointer to the shell data structure, used to retrieve the
 * exit status from user input.
 *
 * Description:
 *  - If an exit status argument is provided by the user, it checks if the 
 *    argument is a valid number.
 *  - Converts the argument to an integer and exits the shell with that 
 *    status code.
 *  - If no argument is provided, the shell exits with a default status code.
 *  - Handles cases where the exit status is too large, not numeric, or exceeds
 *    integer limits, and throws an error in those cases.
 *
 * Return: Always returns 0 on success, 1 if an invalid exit status is provided.
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
 * shell_builtin - Retrieves the appropriate built-in function for the given
 * command input.
 * @command: The command string entered by the user.
 *
 * Description:
 *  - Matches the user input against a list of built-in shell commands.
 *  - If the command matches a built-in, it returns the function pointer
 *    for that built-in command.
 *  - If no match is found, returns NULL.
 *
 * Return: A function pointer to the built-in command, or NULL if not found.
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
