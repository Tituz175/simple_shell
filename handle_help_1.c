#include "main.h"

/**
 * get_help - Retrieves help messages for built-in shell commands.
 * @s_datas: A pointer to a struct containing shell command data.
 *
 * This function checks which built-in command help message to display,
 * based on the first argument (s_datas->args[1]). If no argument is 
 * provided, it displays general help information.
 *
 * Return: Always returns 1.
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
 * help - Displays general help information for the shell.
 *
 * This function provides an overview of available shell built-in commands,
 * their usage, and some general information on how to use the shell. 
 * It includes commands such as `cd`, `alias`, `help`, `env`, `setenv`, 
 * `unsetenv`, and `exit`. Also provides information about options.
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
 * help_alias - Displays help information for the `alias` builtin command.
 *
 * This function provides a detailed explanation of the `alias` command,
 * its usage, and options. It explains how to define or display command aliases.
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
 * help_cd - Displays help information for the `cd` (change directory) command.
 *
 * This function explains the usage of the `cd` command, which changes the
 * current working directory of the shell. It also describes the available
 * options such as `-L` (follow symbolic links) and `-P` (do not follow 
 * symbolic links).
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
