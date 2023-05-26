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
 * get_location - get the location of a command executable
 * @command: the command name to search for.
 * @_environ: the environment variable.
 * Return: a pointer to a string representing the path of the
 * command if found, NULL otherwise.
 */
char *get_location(char *command, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat buffer;

	path = _mygetenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(command);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (current_location(path, &i))
				if (stat(command, &buffer) == 0)
					return (command);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, command);
			_strcat(dir, "\0");
			if (stat(dir, &buffer) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(command, &buffer) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &buffer) == 0)
			return (command);
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
	return (1);
}

/**
 * filter_out_comment -> this function removes comments
 * from a given input string
 *
 * @input: input string
 * Return: a pointer to the modified input string
 */

char *filter_out_comment(char *input)
{
	int i, limit = 0;
	bool found_comment = false;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
			{
				limit = i;
				found_comment = true;
			}
			else
				break;
		}
	}

	if (found_comment)
	{
		input = _realloc(input, i, limit + 1);
		input[limit] = '\0';
	}

	return (input);
}
