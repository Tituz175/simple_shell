#include "main.h"

/**
 * char_switch - Switches the characters '|' and '&' in the input string
 *               to non-printed characters (ASCII 16 and 12 respectively).
 * @input: The input line string to be processed.
 * @flag: The type of switch operation to perform.
 *        If flag == 0, it converts '|' and '&' to non-printed characters.
 *        If flag == 1, it converts non-printed characters back to '|' and '&'.
 * Return: The modified input string.
 */
char *char_switch(char *input, int flag)
{
    int i;

    if (flag == 0) // Convert '|' and '&' to non-printed characters
    {
        for (i = 0; input[i]; i++)
        {
            if (input[i] == '|')
            {
                if (input[i + 1] != '|') // Check for double pipe '||'
                    input[i] = 16; // Convert to non-printed character
                else
                    i++; // Skip the next character
            }

            if (input[i] == '&')
            {
                if (input[i + 1] != '&') // Check for double ampersand '&&'
                    input[i] = 12; // Convert to non-printed character
                else
                    i++; // Skip the next character
            }
        }
    }
    else // Convert non-printed characters back to '|' and '&'
    {
        for (i = 0; input[i]; i++)
        {
            input[i] = (input[i] == 16 ? '|' : input[i]); // Convert back to '|'
            input[i] = (input[i] == 12 ? '&' : input[i]); // Convert back to '&'
        }
    }
    return (input);
}

/**
 * join_nodes - Adds command line strings and separators to the
 *              st_separtor_list and sh_command_line lists.
 * @head_s: Pointer to the head of the separator list (st_separtor_list).
 * @head_l: Pointer to the head of the command line list (sh_command_line).
 * @input: The input line string containing commands.
 */
void join_nodes(st_separtor_list **head_s, sh_command_line **head_l, char *input)
{
    int i;
    char *line;
    char *sep = ";|&"; // Define separators

    input = char_switch(input, 0); // Convert '|' and '&' to non-printed characters

    for (i = 0; input[i]; i++)
    {
        if (strchr(sep, input[i])) // Check if current character is a separator
            add_sep_end(head_s, input[i]); // Add separator to list

        if (input[i] == '|' || input[i] == '&') // Handle special cases for '|' and '&'
        {
            add_sep_end(head_s, input[i]);
            i++; // Skip the next character
        }
    }

    line = strtok(input, sep); // Split input string using separators
    do {
        line = char_switch(line, 1); // Convert non-printed characters back to '|' and '&'
        add_line_end(head_l, line); // Add command line to list
        line = strtok(NULL, sep); // Get next token
    } while (line != NULL);
}

/**
 * next_command - Moves to the next command line based on the status
 *                of the previous command execution.
 * @list_s: Pointer to the current separator list (st_separtor_list).
 * @list_l: Pointer to the current command line list (sh_command_line).
 * @s_datas: Pointer to the shell data structure containing command execution status.
 */
void next_command(st_separtor_list **list_s, sh_command_line **list_l, st_shell *s_datas)
{
    st_separtor_list *ls_s = *list_s;
    sh_command_line *ls_l = *list_l;

    while (ls_s != NULL) // Traverse the separator list
    {
        if (s_datas->status == 0) // If the last command succeeded
        {
            if (ls_s->separator == '&' || ls_s->separator == ';')
                break; // Proceed to next command
            else if (ls_s->separator == '|') // If '|' and last command failed
                ls_l = ls_l->next; // Move to the next command
        }
        else // If the last command failed
        {
            if (ls_s->separator == '|' || ls_s->separator == ';')
                break; // Proceed to next command
            else if (ls_s->separator == '&') // If '&' and last command succeeded
                ls_l = ls_l->next; // Move to the next command
        }

        ls_s = ls_s->next; // Move to the next separator
    }

    *list_s = ls_s; // Update the list of separators
    *list_l = ls_l; // Update the list of command lines
}

/**
 * tokenize_commands - Splits command lines using separators and executes them.
 * @s_datas: Pointer to the shell data structure.
 * @input: The input line string containing commands.
 * Return: 1 if continue processing, 0 if exit.
 */
int tokenize_commands(st_shell *s_datas, char *input)
{
    st_separtor_list *head_s, *list_s;
    sh_command_line *head_l, *list_l;
    int loop;

    head_s = NULL; // Initialize head of separator list
    head_l = NULL; // Initialize head of command line list

    join_nodes(&head_s, &head_l, input); // Populate the lists with commands and separators

    list_s = head_s; // Set current separator list
    list_l = head_l; // Set current command line list

    while (list_l != NULL) // Process each command line
    {
        s_datas->input = list_l->line; // Get current command line
        s_datas->args = tokenize_input(s_datas->input); // Tokenize the command line
        loop = locate_command(s_datas); // Execute the command
        free(s_datas->args); // Free allocated memory for arguments

        if (loop == 0) // If command execution failed
            break;

        next_command(&list_s, &list_l, s_datas); // Move to the next command

        if (list_l != NULL)
            list_l = list_l->next; // Proceed to the next command line
    }

    free_st_separtor_list(&head_s); // Free the separator list
    free_sh_command_line(&head_l); // Free the command line list

    return (loop == 0 ? 0 : 1); // Return 0 for exit, 1 to continue
}

/**
 * tokenize_input - Tokenizes the input line string into an array of tokens.
 * @input: The input line string to be tokenized.
 * Return: An array of tokens.
 */
char **tokenize_input(char *input)
{
    size_t buffersize = TOKEN_BUFFERSIZE, i = 0; // Initial buffer size
    char **tokens = malloc(buffersize * sizeof(char *)); // Allocate memory for tokens
    char *token;

    if (tokens == NULL) // Check for successful memory allocation
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = _strtok(input, TOKEN_DELIM); // Tokenize input using delimiters
    tokens[0] = token; // Store first token

    for (i = 1; token != NULL; i++)
    {
        if (i == buffersize) // If token array is full
        {
            buffersize += TOKEN_BUFFERSIZE; // Increase buffer size
            tokens = _reallocdp(tokens, i, sizeof(char *) * buffersize); // Reallocate memory for tokens
            if (tokens == NULL) // Check for successful memory allocation
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
        }
        token = _strtok(NULL, TOKEN_DELIM); // Get next token
        tokens[i] = token; // Store token
    }

    return (tokens); // Return the array of tokens
}
