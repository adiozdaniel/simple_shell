#include "main.h"

/**
 * _print - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, _strlen(string)));
}


/**
 * _printerr - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */

int _printerr(char *string)
{
	return (write(STDERR_FILENO, string, _strlen(string)));
}
