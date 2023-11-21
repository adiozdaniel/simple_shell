#include "main.h"

/**
 * no_comment - deletes comments from the input
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

/**
 * shell - Main loop of the shell program
 * @datash: data relevant (av, input, args)
 */
void shell(data_shell *datash)
{
    int loop = 1, i;
    int i_eof;
    char *input;
    char *prompt = "Happy&Adioz-Shell: ";

    while (loop == 1)
    {
        write(STDIN_FILENO, prompt, _strlen(prompt));
        input = read_line(&i_eof);

        if (i_eof != -1)
        {
            char *clean_input = no_comment(input);
            if (clean_input == NULL)
                break; /* free(input);*/

            if (_alias_strcmp(clean_input, "alias", 5) == 0)
            {
                char **alias_names = NULL, **alias_values = NULL;
                if (parse_alias_command(clean_input, &alias_names, &alias_values) == 0)
                {
                    if (check_alias_syntax(clean_input))
                    {
                        /* Process and use the aliases */
                        for (int i = 0; alias_names[i] != NULL; i++)
                            add_alias(datash, alias_names[i], alias_values[i]);
                    }
                    else
                    {
                        for (i = 0; datash->alias_names[i] != NULL; i++)
                        {
                            char *alias_name = datash->alias_names[i];
                            char *alias_value = datash->alias_values[i];

                            /* system(alias_value); */
                            _print(alias_name);
                            _print(":");
                            _print(alias_value);
                        }
                    }
                }
            }
            else
            {
                int alias_index = check_alias(datash, clean_input);
                /* Check if the entered command is an alias */
                if (alias_index != -1)
                {
                    char *alias_value = alias_cmd(datash->alias_values[alias_index]);
                    // system(alias_value);
                    _print("found alias\n");
                    free(alias_value);
                        // break;
                }
                else if (check_syntax_error(datash, clean_input) == 1)
                {
                        datash->status = 2;
                        if (clean_input != NULL)
                            free(clean_input);
                }
                else
                {
                    input = rep_var(clean_input, datash);
                    loop = split_commands(datash, input);
                    datash->counter += 1;
                }
            }
            if (clean_input != NULL)
                free(clean_input);  // Free clean_input outside of the conditional blocks
        }
        else
        {
            loop = 0;

            for (i = 0; datash->alias_names[i] != NULL; i++)
            {
                if (datash->alias_names[i] != NULL)
                    free(datash->alias_names[i]);

                if (datash->alias_values[i] != NULL)
                    free(datash->alias_values[i]);
            }

            if (input != NULL)
                free(input);
        }
    }
}
