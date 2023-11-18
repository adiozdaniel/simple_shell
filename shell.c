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
 * shell - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell(data_shell *datash)
{
    int loop = 1;
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

            if (strncmp(clean_input, "alias", 5) == 0)
            {
                char **alias_names = NULL, **alias_values = NULL;
                if (parse_alias_command(clean_input, &alias_names, &alias_values) == 0)
                {
                    if (check_alias_syntax(clean_input))
                    {
                        /* Process and use the aliases */
                        for (int i = 0; alias_names[i] != NULL; i++)
                        {
                            add_alias(datash, alias_names[i], alias_values[i]);
                                printf("added alias %d\n", (*alias_names[i]));
                        }
                    }
                    else
                    {
                        printf("Alas! %s\n", clean_input);
                        free(clean_input);
                    }
                }
                /* Free memory for alias_names and alias_values*/
                if (alias_names != NULL || alias_values != NULL)
                {
                    for (int i = 0; alias_names[i] != NULL; i++)
                    {
                        if (alias_names[i] != NULL)
                            free(alias_names[i]);
                        if (alias_values[i] != NULL)
                            free(alias_values[i]);
                    }
                    free(alias_names);
                    free(alias_values);
                    continue;
                }
                    continue;
            }
            else
            {
                if (check_syntax_error(datash, clean_input) == 1)
                {
                    datash->status = 2;
                    // free(clean_input);
                    continue;
                }
                else
                {
                    input = rep_var(clean_input, datash);

                    loop = split_commands(datash, input);
                    datash->counter += 1;
                }
                free(clean_input);
            }
        }
        else
        {
            loop = 0;
            free(input);
        }
    }
}
