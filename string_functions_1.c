#include "main.h"

/**
 * _strcat -> This function concatenates two strings.
 * @dest: A pointer to the destination string, where the source string will be appended.
 * @src: A constant pointer to the source string to be appended to the destination.
 * Return: A pointer to the destination string.
 *
 * This function appends the contents of the source string (src) to the end of the
 * destination string (dest). It updates the destination string to include the
 * concatenated result and returns the destination pointer.
 */
char *_strcat(char *dest, const char *src)
{
	int len = 0, i;

	// Calculate the length of the destination string
	while (dest[len])
		len++;

	// Append each character from the source string to the destination
	for (i = 0; src[i] != 0; i++)
	{
		dest[len] = src[i];
		len += 1;
	}
	dest[len] = '\0'; // Null-terminate the concatenated string
	return (dest); // Return the destination string
}

/**
 * _strcpy -> This function copies a string from source to destination.
 * @dest: A pointer to the destination string where the source string will be copied.
 * @src: A pointer to the source string to be copied.
 * Return: A pointer to the destination string.
 *
 * This function copies the string pointed to by src to the buffer pointed to by
 * dest, including the null terminator. It returns a pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	// Copy characters from source to destination
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i++] = '\0'; // Null-terminate the destination string

	return (dest); // Return the destination string
}

/**
 * _strcmp -> This function compares two strings.
 * @s1: A pointer to the first string to be compared.
 * @s2: A pointer to the second string to be compared.
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 *         respectively, to be less than, to match, or be greater than s2.
 *
 * This function compares two strings character by character. It returns:
 * - 0 if both strings are equal,
 * - A negative value if the first non-matching character in s1 is less than that in s2,
 * - A positive value if the first non-matching character in s1 is greater than that in s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2) // Loop until either string ends
	{
		if (*s1 != *s2) // If characters do not match
			return (*s1 - *s2); // Return the difference
		s1++; // Move to the next character
		s2++;
	}
	if (*s1 == *s2) // If both strings end together
		return (0); // They are equal
	else
		return (*s1 < *s2 ? -1 : 1); // Determine which string is "greater"
}

/**
 * _strchr -> This function locates a character in a string.
 * @str: A pointer to the string to be searched.
 * @ch: The character to be located in the string.
 * Return: A pointer to the first occurrence of the character ch in the string str,
 *         or NULL if the character is not found.
 *
 * This function searches for the first occurrence of a specified character (ch)
 * in the given string (str). If found, it returns a pointer to that character;
 * otherwise, it returns NULL.
 */
char *_strchr(char *str, char ch)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++) // Loop through the string
		if (str[i] == ch) // If character matches
			return (&str[i]); // Return pointer to the matching character
	if (str[i] == ch) // Check the null terminator
		return (&str[i]); // Return pointer to the null terminator if it matches
	return ('\0'); // Return NULL if character not found
}


/**
 * _strdup -> This function duplicates a string.
 * @str: A pointer to the string to be duplicated.
 * Return: A pointer to the newly allocated duplicate string,
 *         or NULL if memory allocation fails.
 *
 * This function allocates memory for a new string and copies the content of
 * the original string (str) into it. It returns a pointer to the newly allocated
 * string or NULL if memory allocation fails.
 */
char *_strdup(const char *str)
{
	char *ret; // Pointer for the duplicated string
	size_t length = _strlen(str) + 1; // Calculate string length plus null terminator

	ret = malloc(sizeof(char) * (length)); // Allocate memory for the duplicate
	if (!ret) // Check for allocation failure
		return (NULL); // Return NULL if allocation failed
	_memcpy(ret, str, length); // Copy the string to the new location

	return (ret); // Return the duplicated string
}

