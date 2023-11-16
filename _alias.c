#include "main.h"

// Function to add an alias
void add_alias(data_shell *datash, char *alias_name, char *alias_value)
{
    printf("hi, we are here: %s\n", alias_name);

    // Check if the alias already exists
    for (int i = 0; datash->alias_names[i] != NULL; i++)
    {
        if (strcmp(datash->alias_names[i], alias_name) == 0)
        {
            // Update the existing alias
            free(datash->alias_values[i]);
            datash->alias_values[i] = strdup(alias_value);
            return;
        }
    }

    // Add a new alias
    int count = 0;
    while (datash->alias_names[count] != NULL)
    {
        count++;
    }

    datash->alias_names = realloc(datash->alias_names, (count + 2) * sizeof(char *));
    datash->alias_values = realloc(datash->alias_values, (count + 2) * sizeof(char *));

    datash->alias_names[count] = strdup(alias_name);
    datash->alias_values[count] = strdup(alias_value);
    datash->alias_names[count + 1] = NULL;
    datash->alias_values[count + 1] = NULL;
}

// Function to get an alias value
// Function to get an alias value
char *get_alias(data_shell *datash, char *alias_name)
{
    printf("%s: ", alias_name);

    // Check if datash is NULL
    if (datash == NULL || datash->alias_names == NULL || alias_name == NULL)
    {
        // Add appropriate error handling or return value if necessary
        return NULL;
    }

    // Iterate over alias_names array
    for (int i = 0; datash->alias_names[i] != NULL; i++)
    {
        // Check if alias_names[i] and alias_values[i] are not NULL
        if (datash->alias_names[i] != NULL && datash->alias_values[i] != NULL &&
            strcmp(datash->alias_names[i], alias_name) == 0)
        {
            return datash->alias_values[i];
        }
    }

    return NULL;
}


// Function to parse the alias command
int parse_alias_command(const char *input, char ***alias_names, char ***alias_values)
{
    // Skip "alias " part
    char *alias_cmd = strdup(input + 6);
    if (alias_cmd == NULL)
    {
        perror("Error allocating memory");
        return 1; // Memory allocation error
    }

    char *token = strtok(alias_cmd, " ");

    // Initialize arrays to store names and values
    int count = 0;
    *alias_names = malloc(sizeof(char *));
    *alias_values = malloc(sizeof(char *));
    if (*alias_names == NULL || *alias_values == NULL)
    {
        perror("Error allocating memory");
        free(alias_cmd);
        return 1; // Memory allocation error
    }

    while (token != NULL)
    {
        // Look for equal sign '=' to separate name and value
        char *equal_sign = strchr(token, '=');

        if (equal_sign != NULL)
        {
            *equal_sign = '\0'; // Null-terminate name
            (*alias_names)[count] = strdup(token);
            (*alias_values)[count] = strdup(equal_sign + 1);
        }
        else
        {
            // Handle the case where there's no equal sign
            (*alias_names)[count] = strdup(token);
            (*alias_values)[count] = NULL;
        }

        // Check for memory allocation errors
        if ((*alias_names)[count] == NULL || ((*alias_values)[count] == NULL && equal_sign != NULL))
        {
            perror("Error allocating memory");
            free(alias_cmd);
            // Free memory allocated so far
            for (int i = 0; i < count; i++)
            {
                free((*alias_names)[i]);
                free((*alias_values)[i]);
            }
            free(*alias_names);
            free(*alias_values);
            return 1; // Memory allocation error
        }

        // Resize arrays for the next iteration
        count++;
        *alias_names = realloc(*alias_names, (count + 1) * sizeof(char *));
        *alias_values = realloc(*alias_values, (count + 1) * sizeof(char *));

        // Get the next token
        token = strtok(NULL, " ");
    }

    // Null-terminate the arrays
    (*alias_names)[count] = NULL;
    (*alias_values)[count] = NULL;

    free(alias_cmd);
    return 0; // Parsing success
}
