#include "main.h"

/**
 * no_comment - deletes comments from the input
 * @in: input string
 * Return: input without comments
 */
/**
 * no_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *no_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}


int get_command_type(data_shell *datash, const char *input)
{
    if (_alias_strcmp(input, "alias", 5) == 0)
        return CMD_ALIAS;
    else if (is_alias_exec_command(datash, input) != 0)
        return CMD_ALIAS_EXEC;
    else
        return CMD_UNKNOWN;
}


void handle_alias_command(data_shell *datash, const char *clean_input)
{
    char **alias_names = NULL, **alias_values = NULL;

    if (parse_alias_command(clean_input, &alias_names, &alias_values) == 0)
    {
        if (check_alias_syntax(clean_input))
        {
            /* Process and use the aliases */
            for (int i = 0; alias_names[i] != NULL; i++)
                add_alias(datash, alias_names[i], alias_values[i]);

            // Free memory for alias_names and alias_values
            free_string_array(alias_names);
            free_string_array(alias_values);
        }
        else
        {
            for (int i = 0; datash->alias_names[i] != NULL; i++)
            {
                char *alias_name = datash->alias_names[i];
                char *alias_value = datash->alias_values[i];

                _print(alias_name);
                _print(":");
                _print(alias_value);
                free(alias_name);
                free(alias_value);
                alias_name = NULL;
                alias_value = NULL;
            }
        }
    }

    if (alias_names != NULL)
        free_string_array(alias_names);
    if (alias_values != NULL)
        free_string_array(alias_values);

    alias_names = NULL;
    alias_values = NULL;
}

int is_alias_exec_command(data_shell *datash, const char *clean_input)
{
    int i;

    if (datash == NULL || clean_input == NULL)
        return -1; // or another error code

    /* Check if the entered command is an alias */
    for (i = 0; datash->alias_names[i] != NULL; i++)
    {
        printf("\n%d: \n", i);
        if (_alias_strcmp(datash->alias_names[i], clean_input, _strlen(clean_input)) == 0)
            return (i);
    }

    return 0; /* if alias does not exist */
}

/* Define a function to free a string array */
void free_string_array(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
    {
        free(arr[i]);
    }
    free(arr);
}
