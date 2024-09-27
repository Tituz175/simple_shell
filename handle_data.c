#include "main.h"

/**
 * free_data -> Frees the allocated memory to the shell structure.
 * @s_datas: The shell data structure to free memory from.
 * 
 * This function iterates over the `_environ` array, freeing each
 * environment variable stored within it. Finally, it frees the
 * `_environ` array itself and the memory allocated to store the 
 * process ID.
 */
void free_data(st_shell *s_datas)
{
    unsigned int i;

    for (i = 0; s_datas->_environ[i]; i++)
    {
        free(s_datas->_environ[i]);
    }

    free(s_datas->_environ);
    free(s_datas->pid);
}

/**
 * set_data -> Initializes the s_datas struct with the argv array 
 * and allocates memory for the environment in the struct.
 * @s_datas: The shell data structure to initialize.
 * @argv: Argument vector passed to the shell.
 * 
 * This function sets the initial values of the `s_datas` structure,
 * copying the current environment into the `_environ` field of the 
 * structure and storing the process ID.
 */
void set_data(st_shell *s_datas, char **argv)
{
    unsigned int i;

    s_datas->argv = argv;
    s_datas->input = NULL;
    s_datas->args = NULL;
    s_datas->status = 0;
    s_datas->counter = 1;

    for (i = 0; environ[i]; i++)
        ;

    s_datas->_environ = malloc(sizeof(char *) * (i + 1));

    for (i = 0; environ[i]; i++)
    {
        s_datas->_environ[i] = _strdup(environ[i]);
    }

    s_datas->_environ[i] = NULL;
    s_datas->pid = aux_itoa(getpid());
}

/**
 * cmp_env_name -> Compares the environment variable name in `nenv`
 * with `name`.
 * @nenv: The environment variable name to compare.
 * @name: The name to compare it to.
 * 
 * Return: 0 if the names don't match or the length of the name match
 * if the names are equal.
 * 
 * This function loops through both strings and returns the length
 * of the prefix match if the two names match up to the `=` character.
 */
int cmp_env_name(const char *nenv, const char *name)
{
    int i;

    for (i = 0; nenv[i] != '='; i++)
    {
        if (nenv[i] != name[i])
        {
            return (0);
        }
    }

    return (i + 1);
}

/**
 * delete_env_var -> Deletes an environment variable.
 * @s_datas: The shell data structure containing the environment.
 * @name: The name of the environment variable to delete.
 * 
 * Return: 0 on success or 1 if an error occurred.
 * 
 * This function searches for the specified environment variable,
 * removes it from the list, reallocates memory to create a new
 * environment array, and frees the memory of the deleted variable.
 */
int delete_env_var(st_shell *s_datas, char *name)
{
    int i, j = 0, n_vars = 0, index = -1;
    char **new_environ;

    for (i = 0; s_datas->_environ[i]; i++)
    {
        char *var_name = _strtok(s_datas->_environ[i], "=");

        if (_strcmp(var_name, name) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        error_info(s_datas, -1);
        return (1);
    }
    for (i = 0; s_datas->_environ[i]; i++)
    {
        if (i != index)
            n_vars++;
    }
    new_environ = malloc((n_vars + 1) * sizeof(char *));
    if (!new_environ)
    {
        error_info(s_datas, -1);
        return (1);
    }
    for (i = 0; s_datas->_environ[i]; i++)
    {
        if (i != index)
            new_environ[j++] = s_datas->_environ[i];
        else
            free(s_datas->_environ[i]);
    }
    new_environ[j] = NULL;
    free(s_datas->_environ);
    s_datas->_environ = new_environ;
    return (0);
}

/**
 * _unsetenv -> Unsets an environment variable by deleting it.
 * @s_datas: The shell data structure containing the environment.
 * 
 * Return: 1 on success.
 * 
 * This function checks if an environment variable is provided, 
 * and calls `delete_env_var` to remove the variable from the environment.
 * If no variable name is provided, it raises an error.
 */
int _unsetenv(st_shell *s_datas)
{
    if (!s_datas->args[1])
    {
        error_info(s_datas, -1);
        return (1);
    }

    return (delete_env_var(s_datas, s_datas->args[1]));
}
