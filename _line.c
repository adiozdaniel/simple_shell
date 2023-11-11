#include "main.h"

/**
 * exec_line - finds builtins and commands
 * @datash: data relevant
 * Return: 1 on success
 */
int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}

/**
 * get_sigint - Handle the crtl + c call in the prompt
 * @sig: Signal handler
*/

void get_sigint(int sig)
{
	(void)sig;
	_print("\nHappy&Daniel-Shell: ");
}
