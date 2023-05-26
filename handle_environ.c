#include "main.h"

/**
 * _mygetenv -> this function look throughout the environment variable
 * for whatever name given to it
 * @name: the name to be look for in the environment variable
 * @_environ: the process environment variable.
 *
 * Return: a pointer to the name value else, NULL.
 */

char *_mygetenv(const char *name, char **_environ)
{
	char *ptr_env = NULL;
	int i, mov;

	/* Compare all environment variables */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			/* Set ptr_env to point to the value of the variable */
			ptr_env = _environ[i] + mov;
			break;
		}
	}

	return (ptr_env);
}

/**
 * _myenv -> Prints the environment variables to standard output.
 *
 * @s_datas: a pointer to a structure containing the relevant data.
 * Return: 1 on success, 0 otherwise.
 */

int _myenv(st_shell *s_datas)
{
	int i, j;
	char stop[8];

	for (i = 0; s_datas->_environ[i]; i++)
	{
		j = _strlen(s_datas->_environ[i]);

		if (write(STDOUT_FILENO, s_datas->_environ[i], j) == -1 ||
			write(STDOUT_FILENO, "\n", 1) == -1)
			return (0);
		string_slice(s_datas->_environ[i], 0, 7, stop);
		if (_strcmp(stop, "DISPLAY") == 0)
			break;
	}

	s_datas->status = 0;

	return (1);
}


/**
 * set_myenv -> this function sets an environment variable
 *
 * @name: the given name of the environment variable
 * @value: the given value of the environment variable
 * @s_datas: shell data structure
 * Return: no return, void function
 */
void set_myenv(char *name, char *value, st_shell *s_datas)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; s_datas->_environ[i] != NULL; i++)
	{
		var_env = _strdup(s_datas->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(var_env);
			free(s_datas->_environ[i]);
			s_datas->_environ[i] = copy_info(name, value);
			return;
		}
		free(var_env);
	}

	s_datas->_environ = _reallocdp(s_datas->_environ, i + 1, sizeof(char *));
	s_datas->_environ[i] = copy_info(name, value);
	s_datas->_environ[i + 1] = NULL;
}

/**
 * set_myenv_wrapper -> compares env variables names
 * with the name passed.
 * @s_datas: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int set_myenv_wrapper(st_shell *s_datas)
{

	if (s_datas->args[1] == NULL || s_datas->args[2] == NULL)
	{
		get_error(s_datas, -1);
		return (1);
	}

	set_myenv(s_datas->args[1], s_datas->args[2], s_datas);

	return (1);
}

/**
 * find_next_operator_index - finds index of next operator
 *
 * @input: input string
 * @index: pointer to index where to start looking
 * Return: index of the next operator, -1 if not found
 */
int find_next_operator_index(char *input, int *index)
{
	int i = 0;

	while (*(input + i))
	{
		if (*(input + i) == ';' || *(input + i) == '|' || *(input + i) == '&')
		{
			if (i == 0)
				return (i);
			if (i > 0 && *(input + i - 1) != '\\')
			{
				*index = *index + i;
				return (i);
			}
		}
		i++;
	}

	return (-1);
}
