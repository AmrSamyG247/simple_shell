#include "simple_shell.h"
/**
* check_builtins - Checks if a builtin is invoked by user.
* @av: Commands
* @alias:  aliases.
* @filename: file
* @new_envs: New envs
* @status: status
* Return: 0 if no builtin, 1 or 2 otherwise.
*/
short check_builtins(char *av[], char *alias[], char *filename,
char *new_envs[], int status)
{
	int alias_ret;

	if (!_strcmp("history", av[0]))
	{
		print_history(filename);
		return (1);
	}
	if (!_strcmp("exit", av[0]))
	{
		my_exit(av, alias, filename, new_envs, status);
		return (1);
	}
	if (!_strcmp("cd", av[0]))
	{
		_change_dir(av[1], new_envs);
		return (1);
	}
	if (!_strcmp("setenv", av[0]))
	{
		set_var(av[1], av[2], new_envs);
		return (1);
	}
	if (!_strcmp("unsetenv", av[0]))
	{
		unset_var(av[1], new_envs);
		return (1);
	}
	if (!_strcmp("alias", av[0]))
	{
		alias_ret = print_alias(av, alias);
		return (alias_ret);
	}
	return (0);
}

