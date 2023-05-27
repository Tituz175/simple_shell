#include "main.h"

/**
 * error_info ->this function calls the error function depending on
 * the following permission, syntax or builtin
 * @s_datas: shell data structure that contains arguments needed
 * @error_num: error value number
 * Return: error value number
 */
int error_info(st_shell *s_datas, int error_num)
{
	char *error;

	switch (error_num)
	{
	case -1:
		error = error_env(s_datas);
		break;
	case 126:
		error = error_path_126(s_datas);
		break;
	case 127:
		error = error_not_found(s_datas);
		break;
	case 2:
		if (_strcmp("exit", s_datas->args[0]) == 0)
			error = error_exit_shell(s_datas);
		else if (_strcmp("cd", s_datas->args[0]) == 0)
			error = error_get_cd(s_datas);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	s_datas->status = error_num;
	return (error_num);
}

/**
 * error_not_found -> this function generate generic error message
 * for command not found
 * @s_datas: shell data structure that contains arguments
 * Return: error message
 */
char *error_not_found(st_shell *s_datas)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(s_datas->counter);
	length = _strlen(s_datas->argv[0]) + _strlen(ver_str);
	length += _strlen(s_datas->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, s_datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, s_datas->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell -> this function generate a generic
 * error message for exit
 * @s_datas: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_exit_shell(st_shell *s_datas)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(s_datas->counter);
	length = _strlen(s_datas->argv[0]) + _strlen(ver_str);
	length += _strlen(s_datas->args[0]) + _strlen(s_datas->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, s_datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, s_datas->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, s_datas->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}

/**
 * error_env -> this function generates an error message
 * for env in get_env.
 * @s_datas: shell data structure relevant to the error message.
 * Return: error message.
 */
char *error_env(st_shell *s_datas)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(s_datas->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(s_datas->argv[0]) + _strlen(ver_str);
	length += _strlen(s_datas->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, s_datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, s_datas->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_126 -> this function generates an error message for
 * path and failure denied permission
 * @s_datas: data relevant to the error message (counter, arguments)
 * Return: error string.
 */
char *error_path_126(st_shell *s_datas)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(s_datas->counter);
	length = _strlen(s_datas->argv[0]) + _strlen(ver_str);
	length += _strlen(s_datas->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, s_datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, s_datas->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
