#include "main.h"

/**
 * _strlen -> This function returns the length of a string.
 * @str: A pointer to the input string whose length is to be calculated.
 * Return: The length of the string as an integer. Returns 0 if the input is NULL.
 *
 * This function iterates through the string until it reaches the null terminator,
 * counting each character to determine the total length. If the input string is
 * NULL, it returns 0.
 */
int _strlen(const char *str)
{
	unsigned int index = 0;

	if (!str) // Check for NULL input
		return (0);

	// Count characters until the null terminator
	while (*str++)
		index++;
	return (index); // Return the length of the string
}



/**
 * _strtok -> This function splits a string by a specified delimiter.
 * @str: The input string to be split.
 * @delim: The delimiter string that determines the split points.
 * Return: A pointer to the next token or NULL if there are no more tokens.
 *
 * This function uses a static variable to keep track of the last token's end
 * position. If str is not NULL, it resets the token search; if it is NULL,
 * it continues from the last position. It returns the starting pointer of the
 * next token found or NULL if there are no more tokens.
 */
char *_strtok(char *str, char *delim)
{
	static char *last_token_end = '\0'; // Static variable to store last token end
	char *token_start = NULL;

	if (str != NULL) // If a new string is provided
		last_token_end = str; // Reset the last token end

	else // If continuing from the last position
		str = last_token_end;

	// Skip any leading delimiters
	while (*str && _strchr(delim, *str))
		str++;

	if (*str) // If there are characters left
	{
		token_start = str; // Start of the token

		// Find the next delimiter
		while (*str && !(_strchr(delim, *str)))
			str++;

		if (*str) // If a delimiter is found
		{
			*str = '\0'; // Null-terminate the token
			last_token_end = str + 1; // Update last token end
		}
		else // If end of string is reached
			last_token_end = str;
	}

	return (token_start); // Return the token start
}


/**
 * _isdigit -> This function checks if the given string represents a valid number.
 * @s: A pointer to the input string to be checked.
 * Return: 1 if the string represents a number; 0 otherwise.
 *
 * This function iterates through each character in the string to check if
 * all characters are digits (0-9). If any character is not a digit, it returns
 * 0; otherwise, it returns 1.
 */
int _isdigit(const char *s)
{
	for (; *s != '\0'; s++) // Loop through each character
	{
		if (*s < '0' || *s > '9') // Check if character is not a digit
			return (0); // Return 0 if not a digit
	}
	return (1); // Return 1 if all characters are digits
}


/**
 * rev_string -> this function reverses a string.
 * @s: input string.
 */

/**
 * rev_string -> This function reverses the characters in a string.
 * @s: A pointer to the input string to be reversed.
 *
 * This function swaps characters in the string from both ends, working towards
 * the center until all characters have been reversed. The original string is
 * modified in place.
 */
void rev_string(char *s)
{
	char tmp; // Temporary variable for swapping
	int i, length1, length2;

	// Calculate the length of the string
	length1 = 0;
	while (s[length1] != '\0')
		length1++;

	length2 = length1 - 1; // Last index of the string
	for (i = 0; i < length1 / 2; i++) // Loop to the halfway point
	{
		tmp = s[i]; // Store the current character
		s[i] = s[length2]; // Swap with the corresponding character from the end
		s[length2] = tmp; // Complete the swap
		length2 -= 1; // Move towards the center
	}
}

/**
 * num_len -> This function calculates the length of a given integer.
 * @n: The integer whose length is to be calculated.
 * Return: The length of the number as an integer.
 *
 * This function counts the number of digits in the integer n. If n is negative,
 * it counts an additional digit for the negative sign. It repeatedly divides the
 * number by 10 to count the total number of digits until n becomes less than 10.
 */
int num_len(int n)
{
	unsigned int n1; // Variable to hold the absolute value of n
	int lenght = 1; // Length of the number (minimum of 1)

	if (n < 0) // If the number is negative
	{
		lenght++; // Increment length for the negative sign
		n1 = n * -1; // Get the absolute value
	}
	else
	{
		n1 = n; // Use the original number if non-negative
	}
	while (n1 > 9) // Count the digits
	{
		lenght++;
		n1 = n1 / 10; // Reduce the number by one digit
	}

	return (lenght); // Return the length of the number
}

