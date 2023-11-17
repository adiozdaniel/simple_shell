#include "main.h"

/**
 * read_line - reads the input string
 * @i_eof: return value of getline function
 * Return: input string
 */
char *read_line(int *i_eof)
{
    char *input = NULL;
    size_t bufsize = 0;

    *i_eof = getline(&input, &bufsize, stdin);

    /* Check for getline failure or end-of-file */
    if (*i_eof == -1 || *i_eof == EOF)
    {
        /* Free the allocated memory */
        free(input);
        /* Set the pointer to NULL to avoid using a dangling pointer */
        input = NULL;
    }

    return input;
}
