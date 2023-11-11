#include "main.h"
/**
 * _help - Help information for the builtin help
 */
void _help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	_print(help);
	help = "\tDisplay information about builtin commands.\n ";
	_print(help);
	help = "Displays brief summaries of builtin commands.\n";
	_print(help);
}
/**
 * _help_alias - Help information for the builtin alias
 */
void _help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	_print(help);
	help = "\tDefine or display aliases.\n ";
	_print(help);
}
/**
 * _help_cd - Help information for the builtin alias
 */
void _help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	_print(help);
	help = "\tChange the shell working directory.\n ";
	_print(help);
}
