#include "main.h"

/**
 * _isspace - Check if a character is a space
 * @c: Character to check
 * Return: 1 if it's a space, otherwise return 0
*/
int _isspace(char c)
{
    return (c == ' ' || c == '\t');
}

/**
 * trim_whitespace - Trim leading and trailing whitespace from a string
 * @str: Input string
 * Return: Pointer to the trimmed string
*/
char *trim_whitespace(char *str)
{
    char *end;

    /* Trim leading whitespace*/
    while (_isspace(*str))
        str++;

    /* If the string is all whitespace*/
    if (*str == '\0')
        return (str);

    /* Trim trailing whitespace*/
    end = str + strlen(str) - 1;
    while (end > str && _isspace(*end))
        end--;

    /* Null-terminate the trimmed string*/
    *(end + 1) = '\0';

    return (str);
}

/**
 * check_alias_syntax - Check the syntax of an alias command
 * @input: Input string to check
 * Return: 1 if the syntax is correct, otherwise return 0
*/
int check_alias_syntax(char *input)
{
    /* Ensure the input is not NULL*/
    if (input == NULL)
        return (0);

    /* Trim leading and trailing whitespace, including newline characters*/
    char *trimmed_input = trim_whitespace(input);

    /* Check if the trimmed input starts with "alias " followed by a space*/
    if (_alias_strcmp(trimmed_input, "alias ", 6) != 0 || _strlen(trimmed_input) <= 6)
        return (0);

    /* Find the position of the equal sign '='*/
    char *equal_sign = _strchr(trimmed_input, '=');

    /* Check if there is an equal sign and it is not at the beginning*/
    if (equal_sign == NULL || equal_sign == trimmed_input + 6)
        return (0);

    /* Check if there is at least one character before the equal sign*/
    if (equal_sign - trimmed_input <= 6)
        return (0);

    /* Check if there is at least one character after the equal sign*/
    if (*(equal_sign + 1) == '\0')
        return (0);

    return (1);/* The syntax is correct*/
}

/**
 * _alias_strcmp - Custom string comparison function
 * @s1: First string
 * @s2: Second string
 * @n: Number of characters to compare
 * Return: 0 if strings are equal, negative if s1 < s2, positive if s1 > s2
 */

int _alias_strcmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i)
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);

    return (0);
}

/**
 * check_alias - if alias exists
 * @input: Input string to check
 * Return: processed str if alias exists, otherwise return NULL
*/
int check_alias(data_shell *datash, char *input)
{
    int i;

     /* Check if the entered command is an alias */
    for (i = 0; datash->alias_names[i] != NULL; i++)
    {
        printf("checking ....%s: against ....%s\n", datash->alias_names[i], input);
        if (_alias_strcmp(datash->alias_names[i], input, _strlen(input) - 1) == 0)
            return (i);
        continue;
    }
    return (-1);/* if elias does not exist */
}
