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

            if (check_syntax_error(datash, clean_input) == 1)
            {
                datash->status = 2;
                free(clean_input);
                free(input);
                continue;
            }

            // Print raw input for inspection
            // printf("Raw Input: %s\n", input);

            /* Check if the word "alias" is present in the input */
            if (strstr(clean_input, "alias") != NULL)
            {

	                /* Handle the case where "alias" is present */
	                printf("Alias command detected: %s\n", clean_input);
	
	                // If the user types "alias," display the aliases
	                if (strncmp(clean_input, "alias", 5) == 0 && strlen(clean_input) == 5)
	                {
	                    printf("Display aliases:\n");
	                    // Display aliases logic here
	                    free(clean_input);
	                    continue;
	                }
	
	                // If we have "alias" in the command line
	                if (strncmp(clean_input, "alias ", 6) == 0 && strlen(clean_input) > 6)
	                {
	                    char **alias_names, **alias_values;
			            char *alias_value = get_alias(datash, clean_input);
			
			            if (alias_value != NULL)
			            {
			                // If the command is an alias, replace it with the alias value
			                free(clean_input);
			                input = strdup(alias_value);
			                continue;
			            }
	                    // Parse alias command to get alias_names and alias_values
	                    if (parse_alias_command(clean_input, &alias_names, &alias_values) == 0)
	                    {
	                        // Print values for debugging
	                        printf("Parsed alias: name='%s', value='%s'\n", alias_names[0], alias_values[0]);
	
	                        // Add the alias to your data structure
	                        if (alias_names[0] != NULL && alias_values[0] != NULL)
	                        {
	                            add_alias(datash, alias_names[0], alias_values[0]);
	                            printf("Alias added: %s='%s'\n", alias_names[0], alias_values[0]);
	                        }
	
	                        // Free memory
	                        free(alias_names[0]);
	                        free(alias_values[0]);
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
	                    continue;
	                }
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
