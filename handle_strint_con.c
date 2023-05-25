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
	int lenght = num_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	lenght--;
	do {
		*(buffer + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	}
	while (n1 > 0)
		;
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
