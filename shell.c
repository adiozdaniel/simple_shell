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
                if (check_alias_syntax(clean_input)) // Corrected function name
                {
                    putchar(check_alias_syntax(clean_input));
                    _print("the alias is fine\n");
                    free(clean_input);
                }
                else
                {
                    _print("the alias failed!\n");
                    free(clean_input);
                    continue;
                }
                // printf("%i", alias);
                // free(alias);
            }

            else
            {
                if (check_syntax_error(datash, clean_input) == 1)
                {
                    datash->status = 2;
                    free(clean_input);
                    continue;
                }
                else
                {
                    input = rep_var(clean_input, datash);

                    loop = split_commands(datash, input);
                    datash->counter += 1;
                }
                free(clean_input); // Free the cleaned input
            }
        }
        else
        {
            loop = 0;
            free(input);
        }
    }
}
