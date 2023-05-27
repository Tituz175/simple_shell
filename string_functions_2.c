#include "main.h"

/**
 * _strlen ->this function returns the lenght of a string.
 * @str: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *str)
{
	unsigned int index = 0;

	if (!str)
		return (0);

	while (*str++)
		index++;
	return (index);
}



/**
 * _strtok -> this function splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char *str, char *delim)
{
	static char *last_token_end = '\0';
	char *token_start = NULL;

	if (str != NULL)
		last_token_end = str;

	else
		str = last_token_end;

	while (*str && _strchr(delim, *str))
		str++;

	if (*str)
	{
		token_start = str;

		while (*str && !(_strchr(delim, *str)))
			str++;

		if (*str)
		{
			*str = '\0';
			last_token_end = str + 1;
		}
		else
			last_token_end = str;
	}

	return (token_start);
}

/**
 * _isdigit -> this function defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *s)
{
	for (; *s != '\0'; s++)
	{
		if (*s < '0' || *s > '9')
			return (0);
	}
	return (1);
}

/**
 * rev_string -> this function reverses a string.
 * @s: input string.
 */

void rev_string(char *s)
{
	char tmp;
	int i, length1, length2;

	length1 = 0;
	length2 = 0;

	while (s[length1] != '\0')
		length1++;

	length2 = length1 - 1;
	for (i = 0; i < length1 / 2; i++)
	{
		tmp = s[i];
		s[i] = s[length2];
		s[length2] = tmp;
		length2 -= 1;
	}
}

/**
 * num_len -> this function calculates
 * the lenght of a given number.
 * @n: given number.
 * Return: Lenght of the number.
 */
int num_len(int n)
{
	unsigned int n1;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}
