#include "main.h"

/**
 * help_env - Displays help information for the `env` builtin command.
 *
 * This function explains the usage of the `env` command, which prints 
 * the environment variables or allows you to modify the environment 
 * with options and variables. It also details how to run commands with 
 * specific environment variables set.
 */
void help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "\tPrint the environment variables of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_setenv - Displays help information for the `setenv` builtin command.
 *
 * This function explains the usage of the `setenv` command, which adds a new 
 * environment variable or modifies an existing one. It describes the optional 
 * `REPLACE` argument and how it affects existing variables.
 */
void help_setenv(void)
{
	char *help = "setenv: setenv NAME VALUE [REPLACE]\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "\tAdd a new definition to the environment.\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "\tIf REPLACE is given, it will overwrite an existing variable.\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "\tIf REPLACE is not given and the variable already";
	write(STDOUT_FILENO, help, _strlen(help));

	help = " exists, nothing will be done.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_unsetenv - Displays help information for the `unsetenv` builtin command.
 *
 * This function provides details on how to remove environment variables
 * from the shell using the `unsetenv` command.
 */
void help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv NAME\n\t";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "Remove an environment variable from the current shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_general - Displays general help information for the shell's built-in commands.
 *
 * This function provides a list of the shell's built-in commands and 
 * a brief description of their purpose. Users can use `help [command]`
 * for more detailed information about a specific command.
 */
void help_general(void)
{
	char *help = "Shell built-ins:\n\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "alias: Define or display aliases.\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "cd: Change the shell working directory.\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "exit: Exit the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "env: Print or modify the environment.\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "setenv: Add a new definition to the environment.\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "unsetenv: Remove an entry completely from the environment.\n\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "Type `help name' to find out more about the function `name'.\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "For more information about the shell, type `man bash'.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_exit - Displays help information for the `exit` builtin command.
 *
 * This function explains how the `exit` command can be used to close
 * the shell. It also describes the optional `n` argument, which specifies 
 * the exit status to return.
 */
void help_exit(void)
{
	char *help = "exit: exit [n]\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "\tExit the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "\n\tExits the shell with a status of N. If N is not provided, the\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "\texit status is that of the last command executed.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
