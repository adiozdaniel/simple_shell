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
            {
                free(input);
                continue;
            }

            if (strncmp(clean_input, "alias", 5) == 0)
            {
                if (check_alias_syntax(clean_input))
                {
                    _print("the alias is fine\n");

                    char **alias_names = NULL, **alias_values = NULL;

                    if (parse_alias_command(clean_input, &alias_names, &alias_values) == 0)
                    {
                        /* process and use the aliases */
                    
                        // Free memory for alias_names and alias_values
                        for (int i = 0; alias_names[i] != NULL; i++)
                        {
                            free(alias_names[i]);
                            free(alias_values[i]);
                        }
                        free(alias_names);
                        free(alias_values);
                    
                        // continue;
                    }
                     free(clean_input);  // Free clean_input in both success and error cases
                    continue;

                }
                else
                {
                    // Print all stored aliases
                    printf("Stored aliases:\n");
                
                    for (int i = 0; datash->alias_names[i] != NULL; i++)
                    {
                        char *alias_name = datash->alias_names[i];
                        char *alias_value = get_alias(datash, alias_name);
                
                        if (alias_value != NULL)
                        {
                            printf("%s='%s'\n", alias_name, alias_value);
                            free(alias_value);
                        }
                        else
                        {
                            printf("%s=NULL\n", alias_name);
                        }
                    }
                }

                free(clean_input);
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
