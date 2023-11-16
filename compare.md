# shell

```C
void shell(data_shell *datash)
{
    int loop, i_eof;
    char *input;
    char *prompt = "Happy&Adioz-Shell: ";

    loop = 1;
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
                clean_input = rep_var(clean_input, datash);

                loop = split_commands(datash, clean_input);
                datash->counter += 1;

                free(clean_input); // Free the cleaned input
            }

            free(input); // Free input in both "if" and "else" blocks
        }
        else
        {
            loop = 0;
            free(input);
        }
    }
}


```
