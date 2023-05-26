#include "main.h"


/**
 * error_get_cd - generates an error message for the cd command in get_cd
 * @s_datas: data relevant to the error (directory, counter, arguments)
 *
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
 * check_error_cmd -> this function verifies if user has permissions to access
 *
 * @dir: user's destination directory
 * @s_datas: data structure
 * Return: 1 on failure else 0
 */
int check_error_cmd(char *dir, st_shell *s_datas)
{
	if (dir == NULL)
	{
		get_error(s_datas, 127);
		return (1);
	}

	if (_strcmp(s_datas->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(s_datas, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(s_datas->args[0], X_OK) == -1)
		{
			get_error(s_datas, 126);
			return (1);
		}
	}

	return (0);
}


/**
 * print_syntax_error -> this function prints a syntax error message
 * for a shell command
 * @s_datas: pointer to shell data struct
 * @input: string containing the user input
 * @i: index in the input string where the error occurred
 * @flag: boolean value indicating whether the error occurred before or after i
 */
void print_syntax_error(st_shell *s_datas, const char *input, int i, int flag)
{
	const char *msg = NULL;
	const char *msg2 = ": Syntax error: \"";
	const char *msg3 = "\" unexpected\n";
	char *error = NULL;
	char *ct_str = NULL;
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
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @s_datas: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(st_shell *s_datas, char *input)
{
	int begin = 0, i = 0;
	int first_char_index, op_index;

	first_char_index = find_first_non_whitespace(input, &begin);
	if (first_char_index == -1)
	{
		print_syntax_error(s_datas, input, begin, 0);
		return (1);
	}

	op_index = find_next_operator_index(input + begin, &i);
	if (op_index != -1)
	{
		print_syntax_error(s_datas, input, begin + op_index, 1);
		return (1);
	}

	return (0);
}

/**
 * find_first_non_whitespace - finds index of the first non-whitespace char
 *
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
