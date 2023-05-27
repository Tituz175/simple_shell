#include "main.h"

/**
 * get_sigint -> this function handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 6);
}


/**
 * read_line -> this function is designed to read a line of text
 * from the standard input stream and return it as a string.
 * @eof: a pointer to an integer that will
 * store the return value of the "getline" function
 * Return: input string
 */
char *read_line(int *eof)
{
	char *input = NULL;
	size_t buffersize = 0;

	/**eof = get_line(&input, &buffersize, stdin);*/
	*eof = getline(&input, &buffersize, stdin);
	return (input);
}


/**
 * locate_syntax_error -> this function locate a syntax errors
 * @input: input string
 * @last: last character read
 * @index: index
 * Return: 0 no error else index of error
 */
int locate_syntax_error(char *input, int index, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (locate_syntax_error(input + 1, index + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (index);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (index);

		if (last == '|')
		{
			count = count_char(input, 0);
			if (count == 0 || count > 1)
				return (index);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (index);

		if (last == '&')
		{
			count = count_char(input, 0);
			if (count == 0 || count > 1)
				return (index);
		}
	}

	return (locate_syntax_error(input + 1, index + 1, *input));
}
