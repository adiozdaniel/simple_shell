#include "main.h"

/**
 * free_data - frees data structure
 * @datash: data structure
 */
void free_data(data_shell *datash)
{
    unsigned int i;

    // Free environment variables
    if (datash->_environ != NULL)
    {
        for (i = 0; datash->_environ[i] != NULL; i++)
            free(datash->_environ[i]);

        free(datash->_environ);
    }

    // Free process ID string
    if (datash->pid != NULL)
        free(datash->pid);

    // Free alias-related memory
    if (datash->alias_names != NULL)
    {
        for (i = 0; datash->alias_names[i] != NULL; i++)
        {
            free(datash->alias_names[i]);
            free(datash->alias_values[i]);
        }

        free(datash->alias_names);
        free(datash->alias_values);
    }
}

/**
 * set_data - Initialize data structure
 * @datash: data structure
 * @av: argument vector
 */
void set_data(data_shell *datash, char **av)
{
    unsigned int i;

    datash->av = av;
    datash->input = NULL;
    datash->args = NULL;
    datash->status = 0;
    datash->counter = 1;

    for (i = 0; environ[i]; i++)
        ;

    datash->_environ = malloc(sizeof(char *) * (i + 1));

    for (i = 0; environ[i]; i++)
        datash->_environ[i] = _strdup(environ[i]);

    datash->_environ[i] = NULL;
    datash->pid = get_itoa(getpid());

    /* initialise alias table */
    datash->alias_names = malloc(sizeof(char *) * 2);  // Allocate space for two pointers
    datash->alias_values = malloc(sizeof(char *) * 2); // Allocate space for two pointers
    datash->alias_names[0] = NULL;
    datash->alias_values[0] = NULL;
    datash->alias_names[1] = NULL; // Ensure the array ends with a NULL pointer
    datash->alias_values[1] = NULL; // Ensure the array ends with a NULL pointer
}

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	set_data(&datash, av);
	shell(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);

	return (datash.status);
}
