#include "main.h"

/**
 * free_data -> this function frees the allocated
 * memory to this structure
 * @s_datas: my shell data
 */
void free_data(st_shell *s_datas)
{
	unsigned int i;

	for (i = 0; s_datas->_environ[i]; i++)
	{
		free(s_datas->_environ[i]);
	}

	free(s_datas->_environ);
	free(s_datas->pid);
}

/**
 * set_data -> this function initializes the s_datas struct
 * with the argv array and allocates memory for the environ
 * in the struct
 * @s_datas: shell data structure
 * @argv: argument vector
 */
void set_data(st_shell *s_datas, char **argv)
{
	unsigned int i;

	s_datas->argv = argv;
	s_datas->input = NULL;
	s_datas->args = NULL;
	s_datas->status = 0;
	s_datas->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	s_datas->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		s_datas->_environ[i] = _strdup(environ[i]);
	}

	s_datas->_environ[i] = NULL;
	s_datas->pid = aux_itoa(getpid());
}

/**
 * cmp_env_name -> this function compares the
 * environment variable name in "nenv" with "name".
 * @nenv: the name of the environment variable
 * @name: the name to compare environment variable with.
 * Return: always 0 if the two parameters are not equal else
 * the length of the matching prefix of "name" in "nenv".
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * delete_env_var -> Deletes an environment variable.
 * @s_datas: shell shell data structure
 * @name: name of the environment variable to be
 * deleted.
 * Return: always 0 on success else 1
 */
int delete_env_var(st_shell *s_datas, char *name)
{
	int i, j = 0, n_vars = 0, index = -1;
	char **new_environ;

	for (i = 0; s_datas->_environ[i]; i++)
	{
		char *var_name = _strtok(s_datas->_environ[i], "=");

		if (_strcmp(var_name, name) == 0)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		error_info(s_datas, -1);
		return (1);
	}
	for (i = 0; s_datas->_environ[i]; i++)
	{
		if (i != index)
			n_vars++;
	}
	new_environ = malloc((n_vars + 1) * sizeof(char *));
	if (!new_environ)
	{
		error_info(s_datas, -1);
		return (1);
	}
	for (i = 0; s_datas->_environ[i]; i++)
	{
		if (i != index)
			new_environ[j++] = s_datas->_environ[i];
		else
			free(s_datas->_environ[i]);
	}
	new_environ[j] = NULL;
	free(s_datas->_environ);
	s_datas->_environ = new_environ;
	return (0);
}

/**
 * _unsetenv -> this function deletes an environment variable.
 * @s_datas: data relevant (env name)
 * Return: 1 on success.
 */
int _unsetenv(st_shell *s_datas)
{
	if (!s_datas->args[1])
	{
		error_info(s_datas, -1);
		return (1);
	}

	return (delete_env_var(s_datas, s_datas->args[1]));
}
