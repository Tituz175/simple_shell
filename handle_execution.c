#include "main.h"

/**
 * runable -> this function checks if a
 * command is an executable
 * @s_datas: shell data structure
 * Return: 0 not an executable, 1 an executable,
 * and -1 an error
 */
int runable(st_shell *s_datas)
{
	struct stat buffer;
	int index;
	char *input;

	input = s_datas->args[0];
	for (index = 0; input[index]; index++)
	{
		if (input[index] == '.')
		{
			if (input[index + 1] == '.')
				return (0);
			if (input[index + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[index] == '/' && index != 0)
		{
			if (input[index + 1] == '.')
				continue;
			index++;
			break;
		}
		else
			break;
	}
	if (index == 0)
		return (0);

	if (stat(input + index, &buffer) == 0)
	{
		return (index);
	}
	error_info(s_datas, 127);
	return (-1);
}

/**
 * get_location -> this function locate command executable
 * @command: the command name to search for.
 * @_environ: the environment variable.
 * Return: a pointer to a string representing the path of the
 * command if found, NULL otherwise.
 */
char *get_location(char *command, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int dir_length, command_length, i;
	struct stat buffer;

	path = _mygetenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		command_length = _strlen(command);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (current_location(path, &i))
				if (stat(command, &buffer) == 0)
					return (command);
			dir_length = _strlen(token_path);
			dir = malloc(dir_length + command_length + 2);
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
 * run_command -> this function executes a command line
 * @s_datas: the needed shell shell data structure for
 * the run function.
 * Return: 1 if successful.
 */
int run_command(st_shell *s_datas)
{
	pid_t child_pd, wait_pd;
	int command_state, executable;
	char *dir;
	(void) wait_pd;

	executable = runable(s_datas);
	if (executable == -1)
		return (1);
	if (executable == 0)
	{
		dir = get_location(s_datas->args[0], s_datas->_environ);
		if (verify_cmd_error(dir, s_datas) == 1)
			return (1);
	}

	child_pd = fork();
	if (child_pd == 0)
	{
		if (executable == 0)
			dir = get_location(s_datas->args[0], s_datas->_environ);
		else
			dir = s_datas->args[0];
		execve(dir + executable, s_datas->args, s_datas->_environ);
	}
	else if (child_pd < 0)
	{
		perror(s_datas->argv[0]);
		return (1);
	}
	else
	{
		do {
			wait_pd = waitpid(child_pd, &command_state, WUNTRACED);
		} while (!WIFEXITED(command_state) && !WIFSIGNALED(command_state));
	}
	s_datas->status = command_state / 256;
	return (1);
}

/**
 * filter_out_comment -> this function removes comments
 * from a given input line of string
 * @input: input line string
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
