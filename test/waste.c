// //Add this function to parse the alias command
// void parse_alias_command(const char *input, char **alias_name, char **alias_value)
// {
//     // Assuming the input format is "alias name=value"
//     // You can customize this parsing logic based on your requirements
//     char *alias_cmd = strdup(input + 6);  // Skip "alias " part
//     char *equal_sign = strchr(alias_cmd, '=');

//     if (equal_sign != NULL) {
//         *equal_sign = '\0';  // Null-terminate alias_name
//         *alias_name = strdup(alias_cmd);
//         *alias_value = strdup(equal_sign + 1);
//     } else {
//         // Handle invalid alias command
//         *alias_name = NULL;
//         *alias_value = NULL;
//     }

//     free(alias_cmd);
// }

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
                // free(input);
                continue;
            }

            if (strncmp(clean_input, "alias", 5) == 0)
            {
                if (check_alias_syntax(clean_input))
                {
                    _print("the alias is fine\n");

                    char **alias_names = NULL, **alias_values = NULL;

                    if (parse_alias_command(clean_input, &alias_names, &alias_values) == -1)
                    {

                         /* Process and use the aliases */
                        for (int i = 0; alias_names[i] != NULL; i++)
                        {
                            add_alias(datash, alias_names[i], alias_values[i]);
                                printf("added alias %d\n", (*alias_names[i]));
                        }


                    }
                    //  free(clean_input);  // Free clean_input in both success and error cases
                    continue;

                }
                else
                {
                    int i;
                    for (i = 0; datash->alias_names[i] != NULL; i++)
                    {
                        char *alias_name = datash->alias_names[i];
                        char *alias_value = get_alias(datash, alias_name);
                        char output[1024];  /* Adjust the buffer size as needed */
                    
                        if (alias_value != NULL)
                        {
                            int j;
                            for (j = 0; alias_name[j] != '\0'; j++)
                                output[j] = alias_name[j];
                            output[j++] = '=';
                            for (int k = 0; alias_value[k] != '\0'; k++, j++)
                                output[j] = alias_value[k];
                            output[j++] = '\n';
                    
                            for (int k = 0; output[k] != '\0'; k++)
                                write(STDIN_FILENO, &output[k], 1);
                        }
                        else
                        {
                            for (int k = 0; alias_name[k] != '\0'; k++)
                                write(STDIN_FILENO, &alias_name[k], 1);
                            char null_msg[] = "=NULL\n";
                            for (int k = 0; null_msg[k] != '\0'; k++)
                                write(STDIN_FILENO, &null_msg[k], 1);
                        }
                        free(alias_value);
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
