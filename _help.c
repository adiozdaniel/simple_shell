#include "main.h"
/**
 * _help_env - Help information
 */
void _help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	_print(help);
	help = "Print the enviroment of the shell.\n";
	_print(help);

}
/**
 * _help_setenv - Help information
 */
void _help_setenv(void)
{
	char *help = "setenv: setenv (const char *name, const char *value,";

	_print(help);
	help = "int replace)\n\t";
	_print(help);
	help = "Add a new definition to the environment\n";
	_print(help);
}
/**
 * _help_unsetenv - Help information
 */
void _help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	_print(help);
	help = "Remove an entry completely from the environment\n";
	_print(help);
}

/**
 * _help_general - Entry point for help information
 */
void _help_general(void)
{
	char *help = "Happy&Daniel-shell bash, version 1.0-release. Copyright 2023\n";

	_print(help);
	help = "These commands are defined internally.Type 'help' to see the list";
	_print(help);
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	_print(help);
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	_print(help);
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	_print(help);
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	_print(help);
	help = "unsetenv [variable]\n";
	_print(help);
}
/**
 * _help_exit - Help information fot the builint exit
 */
void _help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	_print(help);
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	_print(help);
	help = "status is that of the last command executed\n";
	_print(help);
}

