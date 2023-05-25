#include "simple_shell.h"
/**
* _change_dir -  cd builtin.
* @path: Path .
* @new_envs: New env.
*/
void _change_dir(char *path, char *new_envs[])
{
	int chdir_res = 0, i = 0, j = 0;
	char ptr_dir[ARG_MAX], home_ptr[ARG_MAX], old_ptr[ARG_MAX];

	while (environ[i] && (_strncmp(environ[i], "HOME=", 5)))
		i++;

	while (environ[j] && (_strncmp(environ[j], "OLDPWD=", 7)))
		j++;

	_strcpy(old_ptr, environ[j] + 7);
	_strcpy(home_ptr, environ[i] + 5);
	getcwd(ptr_dir, ARG_MAX);
	if (!path)
		chdir_res = chdir(home_ptr);
	else if (!_strcmp("-", path))
		chdir_res = chdir(old_ptr);
	else
		chdir_res = chdir(path);
	if (chdir_res)
	{
		perror("cd");
		return;
	}
	set_var("OLDPWD", ptr_dir, new_envs);
	getcwd(ptr_dir, ARG_MAX);
	set_var("PWD", ptr_dir, new_envs);
}
/**
* remove_spaces - Remove spaces.
* @command: Command.
* Return: 1 if skip necessary, 0 otherwise.
*/
short remove_spaces(char *command)
{
	short i, sp = 0;

	for (i = 0; command[i]; i++)
		if (command[i] == ' ' || command[i] == '\n')
			sp++;
		else
			break;
	if (!*(command + sp) || !_strcmp(command + sp, "\n"))
	{
		free(command);
		return (1);
	}
	_strcpy(command, command + sp);
	return (0);
}

