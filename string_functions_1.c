#include "main.h"

/**
 * _strcat -> this function concatenate two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int len = 0, i;

	while (dest[len])
		len++;

	for (i = 0; src[i] != 0; i++)
	{
		dest[len] = src[i];
		len += 1;
	}
	dest[len] = '\0';
	return (dest);
}
/**
 * *_strcpy -> this function copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i++] = '\0';

	return (dest);
}
/**
 * _strcmp -> this function compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * _strchr -> this function locates a character in a string,
 * @str: the given string.
 * @ch: the character looking for.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *str, char ch)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == ch)
			return (&str[i]);
	if (str[i] == ch)
		return (&str[i]);
	return ('\0');
}


/**
 * _strdup -> this function duplicates a string.
 * @str: the given string.
 * Return: the pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	char *ret;
	size_t length = _strlen(str) + 1;

	ret = malloc(sizeof(char) * (length));
	if (!ret)
		return (NULL);
	_memcpy(ret, str, length);

	return (ret);
}
