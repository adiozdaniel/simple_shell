#include "main.h"

/**
 * add_alias - Adds or updates an alias in the shell data structure
 * @datash: Pointer to the data_shell structure
 * @alias_name: Name of the alias
 * @alias_value: Value of the alias
 */
void add_alias(data_shell *datash, char *alias_name, char *alias_value)
{
    /* Check if the alias already exists */
    for (int i = 0; datash->alias_names[i] != NULL; i++)
    {
        if (_alias_strcmp(datash->alias_names[i], alias_name, _strlen(alias_name)) == 0)
        {
            /* Update the existing alias */
            free(datash->alias_values[i]);
            datash->alias_values[i] = _strdup(alias_value);
            return;
        }
    }

    /* Add a new alias */
    int count = 0;
    while (datash->alias_names[count] != NULL)
    {
        count++;
    }

    datash->alias_names = _realloc(datash->alias_names, count * sizeof(char *), (count + 2) * sizeof(char *));
    datash->alias_values = _realloc(datash->alias_values, count * sizeof(char *), (count + 2) * sizeof(char *));

    datash->alias_names[count] = _strdup(alias_name);
    datash->alias_values[count] = _strdup(alias_value);
    datash->alias_names[count + 1] = NULL;
    datash->alias_values[count + 1] = NULL;

    if (datash->alias_names[count] == NULL || datash->alias_values[count] == NULL)
    {
        /* Handle memory allocation error */
        _printerr("Error allocating memory");
        free(datash->alias_names[count]);
        free(datash->alias_values[count]);
        datash->alias_names[count] = NULL;
        datash->alias_values[count] = NULL;
    }
}

/**
 * get_alias - Retrieves the value of an alias from the shell data structure
 * @datash: Pointer to the data_shell structure
 * @alias_name: Name of the alias to retrieve
 * Return: Value of the alias, or NULL if not found
 */
char *get_alias(data_shell *datash, char *alias_name)
{
    /* Search for the alias */
    for (int i = 0; datash->alias_names[i] != NULL; i++)
    {
        if (datash->alias_names[i] != NULL && datash->alias_values[i] != NULL &&
            _alias_strcmp(datash->alias_names[i], alias_name, _strlen(alias_name)) == 0)
        {
            return datash->alias_values[i];
        }
    }
    return NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parse_alias_command - Parses an alias command and updates alias_names and alias_values
 * @input: Input string containing the alias command
 * @alias_names: Pointer to an array to store alias names
 * @alias_values: Pointer to an array to store alias values
 * Return: 0 on success, 1 on memory allocation error
 */
int parse_alias_command(const char *input, char ***alias_names, char ***alias_values)
{
    /* Skip "alias " part */
    char *alias_cmd = _strdup(input + 6);
    if (alias_cmd == NULL)
    {
        perror("Error allocating memory");
        return 1; /* Memory allocation error */
    }

    /* Initialize arrays to store names and values */
    int count = 0;
    *alias_names = NULL;
    *alias_values = NULL;

    char *token = _strtok(alias_cmd, "=");

    while (token != NULL)
    {
        /* Allocate memory for name and value */
        *alias_names = _realloc(*alias_names, count * sizeof(char *), (count + 1) * sizeof(char *));
        *alias_values = _realloc(*alias_values, count * sizeof(char *), (count + 1) * sizeof(char *));

        if (*alias_names == NULL || *alias_values == NULL)
        {
            perror("Error allocating memory");
            if (alias_cmd != NULL)
                free(alias_cmd);
            return 1; /* Memory allocation error */
        }

        /* Set name */
        (*alias_names)[count] = _strdup(token);

        /* Set value, or set it to NULL if not present */
        token = _strtok(NULL, " ");
        (*alias_values)[count] = (token != NULL) ? _strdup(token) : NULL;

        /* Check for memory allocation errors */
        if ((*alias_names)[count] == NULL && (*alias_values)[count] == NULL)
        {
            perror("Error allocating memory");
            if (alias_cmd != NULL)
                free(alias_cmd);

            return 1; /* Memory allocation error */
        }

        /* Move to the next token */
        count++;
        token = _strtok(NULL, "=");
    }

    /* Null-terminate the arrays */
    *alias_names = _realloc(*alias_names, count * sizeof(char *), (count + 1) * sizeof(char *));
    *alias_values = _realloc(*alias_values, count * sizeof(char *), (count + 1) * sizeof(char *));
    (*alias_names)[count] = NULL;
    (*alias_values)[count] = NULL;

    if (alias_cmd != NULL)
        free(alias_cmd);

    return 0; /* Parsing success */
}
