#include "main.h"

/**
 * _atoi - Convert a string to an integer.
 * @s: The pointer to convert
 *
 * Return: A integer
 */

int _atoi(char *s)
{
	int c = 0;
	unsigned int ni = 0;
	int min = 1;
	int isi = 0;

	while (s[c])
	{
		if (s[c] == 45)
		{
			min *= -1;
		}

		while (s[c] >= 48 && s[c] <= 57)
		{
			isi = 1;
			ni = (ni * 10) + (s[c] - '0');
			c++;
		}

		if (isi == 1)
		{
			break;
		}

		c++;
	}

	ni *= min;
	return (ni);
}


/**
 * aux_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int i, length = num_len(n);
	char *buffer = malloc(sizeof(char) * (length + 1));

	if (buffer == NULL)
		return (NULL);

	buffer[length] = '\0';

	if (n < 0)
	{
		n1 = -n;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	for (i = length - 1; i >= 0; i--)
	{
		buffer[i] = (n1 % 10) + '0';
		n1 /= 10;
	}

	return (buffer);
}


/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @variableue: variableue (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *variableue)
{
	char *new;
	int len_name, len_variableue, len;

	len_name = _strlen(name);
	len_variableue = _strlen(variableue);
	len = len_name + len_variableue + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, variableue);
	_strcat(new, "\0");

	return (new);
}

/**
 * _strncpy -> copy a certain number of string
 * @dest: destination of the copied string
 * @src: source of the string
 * @n: total number of character to be copied.
 */

void _strncpy(char *dest, char *src, size_t n)
{
	while (*src && n > 0)
	{
		*dest++ = *src++;
		n--;
	}

	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}

}

/**
 * string_slice -> slice a given string
 * @str: string to be slice
 * @start: start position of the slice
 * @end: end position of the slice
 * @result: the result string of the slice.
 */

void string_slice(char *str, int start, int end, char *result)
{
	int length = _strlen(str);
	int slice_length = end - start;

	if (start < 0 || end > length || start > end)
	{
		result[0] = '\0';
		return;
	}

	_strncpy(result, str + start, slice_length);
	result[slice_length] = '\0';
}
