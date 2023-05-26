#include "main.h"

/**
 * get_help - retrieves help messages for built-in commands
 * @s_datas: pointer to a struct containing command data
 *
 * Return: Always returns 1
 */
int get_help(st_shell *s_datas)
{
	char *command = s_datas->args[1];

	if (s_datas->args[1] == 0)
		help_general();
	else if (_strcmp(command, "setenv") == 0)
		help_setenv();
	else if (_strcmp(command, "env") == 0)
		help_env();
	else if (_strcmp(command, "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(command, "help") == 0)
		help();
	else if (_strcmp(command, "exit") == 0)
		help_exit();
	else if (_strcmp(command, "cd") == 0)
		help_cd();
	else if (_strcmp(command, "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, s_datas->args[0],
		      _strlen(s_datas->args[0]));

	s_datas->status = 0;
	return (1);
}

/**
 * help - Display help information for the shell.
 *
 * This function displays help information for the shell, including
 * summaries of builtin commands and general usage information.
 *
 * Return: void
 */
void help(void)
{
	char *help_msg =
		"Usage: shell [OPTIONS] [COMMANDS]\n"
		"\n"
		"A simple shell implementation that supports running external commands\n"
		"and executing shell builtins. The following shell builtins are available:\n"
		"\n"
		"  cd [DIRECTORY]       Change the current working directory.\n"
		"  alias [NAME[=VALUE]] Define or display command aliases.\n"
		"  help [COMMAND]       Display help information for shell commands.\n"
		"  env                  Display the environment variables.\n";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg =
		"  setenv [NAME[=VALUE] Set or modify the environment variables.\n"
		"  unsetenv NAME        Remove an environment variable.\n"
		"  exit [STATUS]        Exit the shell.\n"
		"\n"
		"OPTIONS:\n"
		"  -h, --help           Display this help message and exit.\n"
		"\n"
		"Report bugs to: some_email@example.com\n"
		"Author: John Doe <john@example.com>\n";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
 * help_alias - Displays help information for the `alias` builtin.
 */
void help_alias(void)
{
	const char *help =
		"alias: alias [-p] [name[=value] ...]\n"
		"\tDefine or display aliases.\n\n"
		"\tWithout arguments, `alias' prints the list of aliases in a reusable\n"
		"\tform `alias NAME=value' on standard output.\n\n"
		"\tOtherwise, an alias is defined for each NAME whose value is given.\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help =
		"\tA trailing space in value causes the next word to be checked for\n"
		"\talias substitution when the alias is expanded.\n\n"
		"\tOptions:\n"
		"\t  -p  print all defined aliases in a reusable format\n\n"
		"\tExit Status:\n"
		"\talias returns true unless a NAME is supplied for which no alias has\n"
		"\tbeen defined.\n";

	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_cd - Display help information for the `cd` command
 */
void help_cd(void)
{
	char *help = "cd: cd [-L|-P] [dir]\n"
				"\tChange the current working directory.\n\n"
				"\tOptions:\n"
				"\t  -L\tfollow symbolic links (default)\n"
				"\t  -P\tdo not follow symbolic links\n\n"
				"\tIf no directory is given, the home directory is used.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
