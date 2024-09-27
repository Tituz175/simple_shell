#include "main.h"

/**
 * environ_var_check - Checks if the input string matches any
 *                     environment variable and adds it to the linked list.
 * @head: Pointer to the head of the sh_variable_list linked list.
 * @input: The input line string to be checked.
 * @data: Pointer to the shell data structure containing environment variables.
 */
void environ_var_check(sh_variable_list **head, char *input, st_shell *data)
{
    char **_envr = data->_environ; // Pointer to the array of environment variables
    int i, j = 0;

    // Loop through each environment variable
    while (_envr[j] != NULL)
    {
        char *env_var = _envr[j]; // Current environment variable
        int k = 0;

        // Check if the input matches the environment variable name
        while (input[k] == env_var[k] && env_var[k] != '=')
            k++;

        // If the environment variable is found
        if (env_var[k] == '=')
        {
            int len = _strlen(env_var + k + 1); // Length of the variable value
            add_var_end(head, k, env_var + k + 1, len); // Add to the variable list
            return;
        }

        j++;
    }

    // If no environment variable found, add a null variable to the list
    i = 0;
    while (input[i] != ' ' && input[i] != '\t' && input[i] != ';' && input[i] != '\n' && input[i] != '\0')
        i++;

    add_var_end(head, i, NULL, 0);
}

/**
 * verify_variable - Verifies if the variable is $$ (PID) or $? (last status).
 * @head: Pointer to the head of the sh_variable_list linked list.
 * @input: The input line string to be checked.
 * @s_last: String containing the last command status.
 * @data: Pointer to the shell data structure.
 * Return: The number of processed characters in the input.
 */
int verify_variable(sh_variable_list **head, char *input, char *s_last, st_shell *data)
{
    int i = 0, lst = _strlen(s_last), lpd = _strlen(data->pid);

    while (input[i])
    {
        switch (input[i])
        {
            case '$':
                switch (input[++i])
                {
                    case '?':
                        add_var_end(head, 2, s_last, lst); // Add last command status
                        break;
                    case '$':
                        add_var_end(head, 2, data->pid, lpd); // Add PID
                        break;
                    case '\n':
                    case '\0':
                    case ' ':
                    case '\t':
                    case ';':
                        add_var_end(head, 0, NULL, 0); // Add null variable
                        break;
                    default:
                        environ_var_check(head, input + i, data); // Check for environment variables
                        break;
                }
            break;
            default:
                break;
        }
        i++;
    }
    return (i);
}

/**
 * sub_input - Replaces variables in the input string with their values.
 * @head: Pointer to the head of the sh_variable_list linked list.
 * @input: The original input line string.
 * @new_input: The new generated string with variables replaced.
 * @size: The desired length of the new string.
 * Return: The newly generated string with variables replaced.
 */
char *sub_input(sh_variable_list **head, char *input, char *new_input, int size)
{
    int i, k;
    sh_variable_list *indx = *head;
    char *output = new_input;

    for (i = 0; i < size; i++)
    {
        if (input[i] == '$')
        {
            if (!(indx->len_var) && !(indx->len_val)) // If variable and value lengths are zero
            {
                *output++ = input[i++]; // Copy '$' to output
            }
            else if (indx->len_var && !(indx->len_val)) // If variable has length but value is empty
            {
                i += indx->len_var - 1; // Skip the variable length
            }
            else // If variable has a value
            {
                for (k = 0; k < indx->len_val; k++)
                {
                    *output++ = indx->val[k]; // Copy the variable value to output
                }
                i += indx->len_var - 1; // Skip the variable length
            }
            indx = indx->next; // Move to the next variable
        }
        else
        {
            *output++ = input[i]; // Copy other characters directly
        }
    }

    return (new_input); // Return the new input string
}

/**
 * swap_variable - Replaces variables in the input string with their actual values.
 * @input: The input line string containing variables.
 * @s_datas: Pointer to the shell data structure.
 * Return: The modified input string with variables replaced.
 */
char *swap_variable(char *input, st_shell *s_datas)
{
    sh_variable_list *head, *index;
    char *status, *new_input;
    int old_len, new_len;

    status = aux_itoa(s_datas->status); // Convert last status to string
    head = NULL;

    old_len = verify_variable(&head, input, status, s_datas); // Verify and populate variable list

    if (head == NULL)
    {
        free(status); // Free status string
        return (input); // Return original input if no variables found
    }

    index = head;
    new_len = 0;

    while (index != NULL) // Calculate new length after variable replacement
    {
        new_len += (index->len_val - index->len_var); // Adjust for variable length changes
        index = index->next;
    }

    new_len += old_len; // Add length of original input

    new_input = malloc(sizeof(char) * (new_len + 1)); // Allocate memory for new input
    if (new_input == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE); // Exit on memory allocation failure
    }

    new_input[new_len] = '\0'; // Null-terminate the new string
    new_input = sub_input(&head, input, new_input, new_len); // Replace variables in the input string

    free(input); // Free original input
    free(status); // Free status string
    free_var_list(&head); // Free variable list
    return (new_input); // Return modified input string
}

/**
 * count_char - Counts the number of consecutive occurrences of a character in the input string.
 * @input: The input line string to be checked.
 * @index: The current index of the character.
 * Return: The total number of repetitions of the character.
 */
int count_char(char *input, int index)
{
    // Recursive function to count occurrences of the character
    if (*(input - 1) == *input)
        return (count_char(input - 1, index + 1));

    return (index; // Return the count
}
