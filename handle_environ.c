#include "main.h"

/**
 * _mygetenv -> Looks for the specified environment variable in the environment.
 * @name: The name of the environment variable to search for.
 * @_environ: The array containing the environment variables.
 * 
 * Return: A pointer to the value of the environment variable if found,
 * otherwise, NULL.
 * 
 * This function loops through the environment variables and compares 
 * each variable's name with the provided name. If a match is found, 
 * it returns a pointer to the variable's value.
 */
char *_mygetenv(const char *name, char **_environ)
{
    char *ptr_env = NULL;
    int i, mov;

    /* Compare all environment variables */
    for (i = 0; _environ[i]; i++)
    {
        /* If name and env are equal */
        mov = cmp_env_name(_environ[i], name);
        if (mov)
        {
            /* Set ptr_env to point to the value of the variable */
            ptr_env = _environ[i] + mov;
            break;
        }
    }

    return (ptr_env);
}

/**
 * _myenv -> Prints all environment variables to standard output.
 * @s_datas: Pointer to a structure containing the shell data, including the environment.
 * 
 * Return: 1 on success, 0 otherwise.
 * 
 * This function loops through the environment array and prints each 
 * variable to the standard output. It also stops printing when it 
 * encounters the "DISPLAY" variable.
 */
int _myenv(st_shell *s_datas)
{
    int i, j;
    char stop[8];

    for (i = 0; s_datas->_environ[i]; i++)
    {
        j = _strlen(s_datas->_environ[i]);

        if (write(STDOUT_FILENO, s_datas->_environ[i], j) == -1 ||
            write(STDOUT_FILENO, "\n", 1) == -1)
            return (0);
        
        /* Stop printing at the "DISPLAY" environment variable */
        string_slice(s_datas->_environ[i], 0, 7, stop);
        if (_strcmp(stop, "DISPLAY") == 0)
            break;
    }

    s_datas->status = 0;

    return (1);
}

/**
 * set_myenv -> Sets or updates an environment variable.
 * @name: The name of the environment variable to set.
 * @value: The value of the environment variable to set.
 * @s_datas: Pointer to the shell data structure.
 * 
 * This function checks if the environment variable already exists 
 * and updates it if it does. If the variable does not exist, it 
 * creates a new entry in the environment array.
 */
void set_myenv(char *name, char *value, st_shell *s_datas)
{
    int i;
    char *var_env, *name_env;

    for (i = 0; s_datas->_environ[i] != NULL; i++)
    {
        var_env = _strdup(s_datas->_environ[i]);
        name_env = _strtok(var_env, "=");
        if (_strcmp(name_env, name) == 0)
        {
            free(var_env);
            free(s_datas->_environ[i]);
            s_datas->_environ[i] = copy_info(name, value);
            return;
        }
        free(var_env);
    }

    s_datas->_environ = _reallocdp(s_datas->_environ, i + 1, sizeof(char *));
    s_datas->_environ[i] = copy_info(name, value);
    s_datas->_environ[i + 1] = NULL;
}

/**
 * set_myenv_wrapper -> Wrapper function for setting environment variables.
 * @s_datas: Shell data structure containing the environment and arguments.
 * 
 * Return: 1 on success, or 1 if any arguments are missing.
 * 
 * This function checks if both a name and a value are provided before
 * calling the `set_myenv` function to update or create the environment variable.
 */
int set_myenv_wrapper(st_shell *s_datas)
{
    if (s_datas->args[1] == NULL || s_datas->args[2] == NULL)
    {
        error_info(s_datas, -1);
        return (1);
    }

    set_myenv(s_datas->args[1], s_datas->args[2], s_datas);

    return (1);
}

/**
 * find_next_operator_index -> Finds the index of the next operator in a command.
 * @input: The input string containing the command.
 * @index: Pointer to the index to start searching from.
 * 
 * Return: The index of the next operator, or -1 if no operator is found.
 * 
 * This function searches the input string for shell operators such as `;`, `|`,
 * and `&`. It returns the index of the next operator found or -1 if no operator
 * is present. The function ignores operators escaped by a backslash (`\`).
 */
int find_next_operator_index(char *input, int *index)
{
    int i = 0;

    while (*(input + i))
    {
        if (*(input + i) == ';' || *(input + i) == '|' || *(input + i) == '&')
        {
            if (i == 0)
                return (i);
            if (i > 0 && *(input + i - 1) != '\\')
            {
                *index = *index + i;
                return (i);
            }
        }
        i++;
    }

    return (-1);
}
