#include "main.h"

/**
 * current_location -> this function checks if the current directory is
 * in the PATH environment variable.
 * @path: a pointer to a string representing the PATH
 * environment variable.
 * @i: a pointer to an integer representing the current
 * index in the path string.
 * Return: 1 if the current directory is in the PATH, 0 otherwise.
 */
int current_location(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i] != '\0')
		*i += 1;

	if (path[*i] != '\0')
		*i += 1;

	return (0);
}

/**
 * search_in_path - searches for the location of a
 * command executable in the PATH environment variable.
 * @command: the command name to search for.
 * @path: the PATH environment variable.
 * Return: a pointer to a string representing the path of the
 * command if found, NULL otherwise.
 */
char *search_in_path(char *command, char *path)
{
	struct stat buffer;
	char *path_copy = _strdup(path), *path_token = NULL, *file_path = NULL;
	int command_length = _strlen(command), i;

	if (command[0] == '/' && stat(command, &buffer) == 0)
		return (command);
	if (path_copy != NULL && path)
	{
		path_token = _strtok(path_copy, ":");
		while (path_token)
		{
			i = 0;
			if (current_location(path_token, &i))
				file_path = malloc(command_length + 1);
			else
				file_path = malloc(_strlen(path_token) + command_length + 2);
			if (file_path)
			{
				if (current_location(path_token, &i))
					_strcpy(file_path, command);
				else
				{
					_strcpy(file_path, path_token);
					_strcat(file_path, "/");
					_strcat(file_path, command);
				}

				if (stat(file_path, &buffer) == 0)
				{
					free(path_copy);
					return (file_path);
				}
				else
					free(file_path);
			}
			path_token = _strtok(NULL, ":");
		}
		free(path_copy);
	}
	return (NULL);
}



/**
 * get_location - get the location of a command executable
 * @command: the command name to search for.
 * @_environ: the environment variable.
 * Return: a pointer to a string representing the path of the
 * command if found, NULL otherwise.
 */
char *get_location(char *command, char **_environ)
{
	char *path, *file_path;

	path = _mygetenv("PATH", _environ);
	if (path)
	{
		file_path = search_in_path(command, path);
		if (file_path != NULL)
			return (file_path);
	}
	return (NULL);
}




/**
 * runable - determines if is an executable
 *
 * @s_datas: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int runable(st_shell *s_datas)
{
	struct stat buffer;
	int i;
	char *input;

	input = s_datas->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &buffer) == 0)
	{
		return (i);
	}
	get_error(s_datas, 127);
	return (-1);
}



/**
 * run_command - executes command lines
 *
 * @s_datas: the needed shell data structure for
 * the run function.
 * Return: 1 on success.
 */
int run_command(st_shell *s_datas)
{
	pid_t child_pd;
	pid_t wait_pd;
	int state;
	int exec;
	char *dir;
	(void) wait_pd;

	exec = runable(s_datas);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = get_location(s_datas->args[0], s_datas->_environ);
		if (check_error_cmd(dir, s_datas) == 1)
			return (1);
	}

	child_pd = fork();
	if (child_pd == 0)
	{
		if (exec == 0)
			dir = get_location(s_datas->args[0], s_datas->_environ);
		else
			dir = s_datas->args[0];
		execve(dir + exec, s_datas->args, s_datas->_environ);
	}
	else if (child_pd < 0)
	{
		perror(s_datas->argv[0]);
		return (1);
	}
	else
	{
		do {
			wait_pd = waitpid(child_pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	s_datas->status = state / 256;
	free(dir);
	return (1);
}
