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
// void shell(data_shell *datash)
// {
//     int loop, i_eof;
//     char *input;
//     char *prompt = "Happy&Adioz-Shell: ";

//     loop = 1;
//     while (loop == 1)
//     {
//         write(STDIN_FILENO, prompt, _strlen(prompt));
//         input = read_line(&i_eof);
//         if (i_eof != -1)
//         {
//             input = no_comment(input);
//             if (input == NULL)
//             {
//                 free(input);
//                 continue;
//             }

//             /* Check if the word "alias" is present in the input */
//             if (strstr(input, "alias") != NULL)
//             {
//                 /* Handle the case where "alias" is present */
//                 printf("Alias command detected: %s\n", input);
//                 /* You can add your alias handling logic here */
//                 /* For example, you might want to parse the alias command and add it to your data structure */
//                 /* Parse the alias command */
//                 char **alias_names;
//                 char **alias_values;
//                 if (parse_alias_command(input, &alias_names, &alias_values) == 0)
//                 {
//                     // Print values for debugging
//                     printf("Parsed alias: name='%s', value='%s'\n", alias_names[0], alias_values[0]);
//                     /* Add the aliases */
//                     for (int i = 0; alias_names[i] != NULL; i++)
//                     {
//                         add_alias(datash, alias_names[i], alias_values[i]);
//                         free(alias_names[i]);
//                         if (alias_values[i] != NULL)
//                             free(alias_values[i]);
//                     }
//                     free(alias_names);
//                     free(alias_values);
//                 }
//                 else
//                 {
//                     // Handle parsing error
//                     printf("There was an error parsing");
//                     free(alias_names);
//                     free(alias_values);
//                     fprintf(stderr, "Error parsing alias command: %s\n", input);
//                 }

//                 free(input); // Free the cleaned input
//             }
//             else
//             {
//                 if (check_syntax_error(datash, input) == 1)
//                 {
//                     datash->status = 2;
//                     free(input);
//                     continue;
//                 }
//                 else
//                 {
// 	                input = rep_var(input, datash);
	
// 	                loop = split_commands(datash, input);
// 	                datash->counter += 1;
	
// 	                free(input); // Free the input
//                 }
//             }

//             free(input); // Free input in both "if" and "else" blocks
//         }
//         else
//         {
//             loop = 0;
//             free(input);
//         }
//     }
// }

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
                // free(input);
                continue;
            }

            // Print raw input for inspection
            printf("Raw Input: %s\n", input);

            /* Check if the word "alias" is present in the input */
            if (strstr(clean_input, "alias") != NULL)
            {
                /* Handle the case where "alias" is present */
                printf("Alias command detected: %s\n", clean_input);

                /* You can add your alias handling logic here */
                /* For example, you might want to parse the alias command and add it to your data structure */
                /* Parse the alias command */
                char **alias_names;
                char **alias_values;

                if (parse_alias_command(clean_input, &alias_names, &alias_values) == 0)
                {
                    // Print values for debugging
                    printf("Parsed alias: name='%s', value='%s'\n", alias_names[0], alias_values[0]);

                    /* Add the aliases */
                    for (int i = 0; alias_names[i] != NULL; i++)
                    {
                        add_alias(datash, alias_names[i], alias_values[i]);
                        free(alias_names[i]);
                        if (alias_values[i] != NULL)
                            free(alias_values[i]);
                    }
                    free(alias_names);
                    free(alias_values);
                }
                else
                {
                    // Handle parsing error
                    printf("There was an error parsing\n");
                    fprintf(stderr, "Error parsing alias command: %s\n", clean_input);
                }

                free(clean_input); // Free the cleaned input
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
            }

            free(clean_input); // Free the cleaned input
        }
        else
        {
            loop = 0;
            free(input);
        }
    }
}
