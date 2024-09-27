#include "main.h"

/**
 * _atoi - Converts a string to an integer.
 *
 * This function parses the input string and converts it to an integer,
 * handling optional leading whitespace and a negative sign.
 *
 * @string: Pointer to the string to be converted.
 *
 * Return: The integer value of the string.
 */
int _atoi(char *string)
{
	int c = 0;
	unsigned int ni = 0;
	int min = 1;
	int isi = 0;

	while (string[c])
	{
		if (string[c] == 45) // ASCII code for '-'
		{
			min *= -1; // Toggle sign
		}

		while (string[c] >= 48 && string[c] <= 57) // ASCII codes for '0'-'9'
		{
			isi = 1;
			ni = (ni * 10) + (string[c] - '0');
			c++;
		}

		if (isi == 1) // If at least one digit was found
		{
			break;
		}

		c++;
	}

	ni *= min; // Apply sign if negative
	return (ni);
}

/**
 * aux_itoa - Converts an integer to a string.
 *
 * This function takes an integer and converts it to its string representation.
 *
 * @number: The integer to convert.
 *
 * Return: A pointer to the string representation of the integer.
 *         Returns NULL if memory allocation fails.
 */
char *aux_itoa(int number)
{
	unsigned int n1;
	int i, length = num_len(number);
	char *buffer = malloc(sizeof(char) * (length + 1));

	if (buffer == NULL)
		return (NULL); // Memory allocation failure

	buffer[length] = '\0'; // Null-terminate the string

	if (number < 0)
	{
		n1 = -number; // Work with positive equivalent for conversion
		buffer[0] = '-';
	}
	else
	{
		n1 = number; // Positive number
	}

	for (i = length - 1; i >= 0; i--) // Fill buffer with digits
	{
		buffer[i] = (n1 % 10) + '0'; // Convert digit to character
		n1 /= 10; // Remove last digit
	}

	return (buffer);
}

/**
 * copy_info - Copies information to create a new environment variable or alias.
 *
 * This function combines a name and a variable into a new string in the 
 * format "name=variable".
 *
 * @name: The name of the environment variable or alias.
 * @variable: The value of the environment variable or alias.
 *
 * Return: A pointer to the newly created environment or alias string.
 *         Returns NULL if memory allocation fails.
 */
char *copy_info(char *name, char *variable)
{
	char *new;
	int len_name, len_variable, len;

	len_name = _strlen(name);
	len_variable = _strlen(variable);
	len = len_name + len_variable + 2; // Additional space for '=' and '\0'
	new = malloc(sizeof(char) * (len));
	if (new == NULL)
		return (NULL); // Memory allocation failure

	_strcpy(new, name); // Copy the name
	_strcat(new, "="); // Append '='
	_strcat(new, variable); // Append variable
	_strcat(new, "\0"); // Ensure null termination

	return (new);
}

/**
 * _strncpy - Copies a specified number of characters from one string to another.
 *
 * This function copies at most n characters from the source string to
 * the destination string. If the source string is shorter than n, the
 * remaining characters in the destination are filled with null bytes.
 *
 * @dest: The destination string where the copied characters will be stored.
 * @src: The source string to copy characters from.
 * @n: The maximum number of characters to copy.
 */
void _strncpy(char *dest, char *src, size_t n)
{
	while (*src && n > 0) // Copy while characters remain and n is positive
	{
		*dest++ = *src++;
		n--;
	}

	while (n > 0) // Fill remaining space with null characters
	{
		*dest++ = '\0';
		n--;
	}
}

/**
 * string_slice - Slices a substring from a given string.
 *
 * This function extracts a substring from the input string starting 
 * from the 'start' index to the 'end' index (exclusive).
 *
 * @str: The input string to slice from.
 * @start: The starting index of the slice.
 * @end: The ending index of the slice (exclusive).
 * @result: The buffer where the result substring will be stored.
 */
void string_slice(char *str, int start, int end, char *result)
{
	int length = _strlen(str);
	int slice_length = end - start;

	if (start < 0 || end > length || start > end) // Validate indices
	{
		result[0] = '\0'; // Return an empty string if indices are invalid
		return;
	}

	_strncpy(result, str + start, slice_length); // Copy the slice to result
	result[slice_length] = '\0'; // Null-terminate the result string
}
