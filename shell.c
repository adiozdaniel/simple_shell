#include "main.h"

/**
 * shell - Loop of shell
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
            {
                free(input);
                continue;
            }

            switch (get_command_type(datash, clean_input))
            {
                case CMD_ALIAS:
                {
                    handle_alias_command(datash, clean_input);
                    break;
                }

                case CMD_ALIAS_EXEC:
                {
                    int alias_index = is_alias_exec_command(datash, clean_input);

                    char *searched = datash->alias_names[alias_index];
                    _print("we gladly received: ");
                    _print(searched);
                    _print("\n");

                    if (alias_index != -1)
                    {
                        char *alias_value = alias_cmd(datash->alias_values[alias_index]);
                        _print("found alias\n");
                        _print(alias_value);
                        // Do something with alias_value
                        free(alias_value);
                    }
                    break;
                }

                case CMD_UNKNOWN:
                default:
                    if (check_syntax_error(datash, clean_input) == 1)
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
                    break;
            }
            free(clean_input);
        }
        else
        {
            loop = 0;

            for (i = 0; datash->alias_names[i] != NULL; i++)
            {
                free(datash->alias_names[i]);
                datash->alias_names[i] = NULL;

                free(datash->alias_values[i]);
                datash->alias_values[i] = NULL;
            }

            free(input);
        }
    }
}
