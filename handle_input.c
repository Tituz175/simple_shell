#include "main.h"

/**
 * get_sigint - Handles the SIGINT signal generated by pressing Ctrl+C.
 *
 * This function is a signal handler that is invoked when the user
 * presses Ctrl+C in the shell. It outputs a newline character and 
 * displays a new prompt to allow the user to continue input.
 *
 * @sig: The signal number (not used in this implementation).
 */
void get_sigint(int sig)
{
	(void)sig;  // Suppress unused variable warning
	write(STDOUT_FILENO, "\n($) ", 6);
}

/**
 * read_line - Reads a line of text from the standard input stream.
 *
 * This function uses the getline function to read a line of text
 * from the standard input and returns it as a dynamically allocated
 * string. The function also updates the integer pointed to by `eof`
 * with the return value of getline, which indicates whether the end
 * of the file was reached.
 *
 * @eof: A pointer to an integer that will store the return value 
 *       of the getline function.
 * 
 * Return: A pointer to the input string read from stdin. 
 *         It should be freed by the caller.
 */
char *read_line(int *eof)
{
	char *input = NULL;
	size_t buffersize = 0;

	*eof = getline(&input, &buffersize, stdin);  // Read input
	return (input);
}

/**
 * locate_syntax_error - Locates syntax errors in the input string.
 *
 * This recursive function checks for syntax errors in the input string
 * based on specific shell syntax rules. It identifies common syntax 
 * issues such as unbalanced operators and misplaced semicolons.
 *
 * @input: The input string to check for syntax errors.
 * @last: The last character read in the input string.
 * @index: The current index in the input string being checked.
 * 
 * Return: 0 if no syntax error is found, otherwise returns the index 
 *         of the syntax error in the input string.
 */
int locate_syntax_error(char *input, int index, char last)
{
	int count;

	count = 0;
	if (*input == '\0')  // End of string check
		return (0);

	if (*input == ' ' || *input == '\t')  // Skip whitespace
		return (locate_syntax_error(input + 1, index + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')  // Error if ';' follows another operator
			return (index);

	if (*input == '|')  // Check for pipe operator syntax
	{
		if (last == ';' || last == '&')  // Error if '|' follows these operators
			return (index);

		if (last == '|')  // Check for multiple pipes
		{
			count = count_char(input, 0);
			if (count == 0 || count > 1)  // Error if no pipes or more than one
				return (index);
		}
	}

	if (*input == '&')  // Check for and operator syntax
	{
		if (last == ';' || last == '|')  // Error if '&' follows these operators
			return (index);

		if (last == '&')  // Check for multiple '&'
		{
			count = count_char(input, 0);
			if (count == 0 || count > 1)  // Error if no '&' or more than one
				return (index);
		}
	}

	return (locate_syntax_error(input + 1, index + 1, *input));  // Recursive call
}
