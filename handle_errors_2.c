#include "main.h"


/**
 * error_get_cd -> this function generates an error
 * message for the cd command in get_cd function
 * @s_datas: data relevant to the error (directory, counter, arguments)
 * Return: error message
 */
char *error_get_cd(st_shell *s_datas)
{
	int length;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(s_datas->counter);
	if (s_datas->args[1][0] == '-')
		msg = "Illegal option ";
	else
	{
		msg = "No such file or directory: ";
	}

	length = _strlen(s_datas->argv[0]) + _strlen(s_datas->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + _strlen(s_datas->args[1]) + 4;
	error = malloc(sizeof(char) * (length + 1));

	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, s_datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, msg);
	_strcat(error, s_datas->args[1]);
	_strcat(error, "\n");
	free(ver_str);

	return (error);
}


/**
 * verify_cmd_error -> this function verifies if user has permissions to access
 * @dir: user's destination directory
 * @s_datas: pointer to shell data structure
 * Return: 1 on failure else 0
 */
int verify_cmd_error(char *dir, st_shell *s_datas)
{
	if (dir == NULL)
	{
		error_info(s_datas, 127);
		return (1);
	}

	if (_strcmp(s_datas->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			error_info(s_datas, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(s_datas->args[0], X_OK) == -1)
		{
			error_info(s_datas, 126);
			return (1);
		}
	}

	return (0);
}


/**
 * display_syn_error -> this function prints a syntax error message
 * for a shell command
 * @s_datas: pointer to shell data structure
 * @input: string containing the user input
 * @i: index in the input string where the error occurred
 * @flag: boolean value indicating whether the error occurred before or after i
 */
void display_syn_error(st_shell *s_datas, const char *input, int i, int flag)
{
	const char *msg = NULL, *msg2 = ": Syntax error: \"",
	*msg3 = "\" unexpected\n";
	char *error, *ct_str = NULL;
	int length;

	if (input[i] == ';')
		msg = (input[i + 1] == ';' ? ";;" : ";");
	else if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");
	else if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	ct_str = aux_itoa(s_datas->counter);
	if (ct_str == NULL)
		return;

	length = _strlen(s_datas->argv[0]) + _strlen(ct_str) + _strlen(msg) +
			_strlen(msg2) + _strlen(msg3) + 2;
	error = malloc(length + 1);
	if (error == NULL)
	{
		free(ct_str);
		return;
	}
	_strcpy(error, s_datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ct_str);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");
	if (flag)
		i--;
	error[i + _strlen(s_datas->argv[0]) + _strlen(ct_str) + _strlen(msg2)] = '^';

	write(STDERR_FILENO, error, length);
	free(error);
	free(ct_str);
}



/**
 * syntax_error -> this is function to detect
 * a syntax error
 * @s_datas: shell data structure
 * @input: input line of command
 * Return: 1 for error and 0 for no error
 */
int syntax_error(st_shell *s_datas, char *input)
{
	int first_char_index, op_index, starting_point = 0, index = 0;

	first_char_index = find_first_non_whitespace(input, &starting_point);
	if (first_char_index == -1)
	{
		display_syn_error(s_datas, input, starting_point, 0);
		return (1);
	}

	op_index = find_next_operator_index(input + starting_point, &index);
	if (op_index != -1)
	{
		display_syn_error(s_datas, input, starting_point + op_index, 1);
		return (1);
	}

	return (0);
}

/**
 * find_first_non_whitespace -> this function finds index of the
 * first non-whitespace character
 * @input: input string
 * @index: index where to start looking
 * Return: index of the first non-whitespace char, -1 if not found
 */
int find_first_non_whitespace(char *input, int *index)
{
	while (*(input + *index))
	{
		if (*(input + *index) != ' ' && *(input + *index) != '\t')
			return (*index);
		(*index)++;
	}

	return (-1);
}
