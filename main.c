#include "main.h"

/**
 * free_data - frees data structure
 * @datash: data structure
 */
void free_data(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
		free(datash->_environ[i]);

	free(datash->_environ);
	free(datash->pid);

	    // Free alias-related memory
    for (i = 0; datash->alias_names[i] != NULL; i++) {
        free(datash->alias_names[i]);
        free(datash->alias_values[i]);
    }

    free(datash->alias_names);
    free(datash->alias_values);
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
    datash->alias_names = malloc(sizeof(char *) * 1);  // Allocate space for one pointer
    datash->alias_values = malloc(sizeof(char *) * 1); // Allocate space for one pointer
    datash->alias_names[0] = NULL;
    datash->alias_values[0] = NULL;
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
