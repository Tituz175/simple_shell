#include "main.h"

/**
 * help_env -> this function print builtin environment command help info
 */
void help_env(void)
{
	char *help = "env: env [option] [name=variableue] [command [args]]\n";
	write(STDOUT_FILENO, help, _strlen(help));

	help = "\tPrint the environment variables of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_setenv -> this function print builtin set
 * environment command help info
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
 * help_unsetenv -> this function print builtin unset
 * environment command help info
 */
void help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv name\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an environment variable from the current shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * help_general -> this function display shell built-ins help info
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
 * help_exit -> this function display builtin exit command help info
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

