#include "simple_shell.h"
/**
* getenvtok - Get env vars as tokens.
* @envp: Env.
* @var: Variable.
* @token: Array s.
* Return: String to free
*/
char *getenvtok(char *envp[], char *var, char *token[])
{
	short i = 0;
	char *path_str = NULL;

	while (_strncmp(envp[i], var, _strlen(var)))
		i++;
	path_str = malloc(_strlen(envp[i]) + 1);
	if (!path_str)
		exit(-1);
	_strcpy(path_str, envp[i]);
	if (*(path_str + 5) == ':')
		*(path_str + 4) = '.', *(path_str + 3) = '=';
	i = 0;
	_strtok(path_str, "=");
	while ((token[i++] = _strtok(NULL, ":")))
		;
	return (path_str);
}
/**
* set_var - handles the setenv.
* @arg1: Name .
* @arg2: Value .
* @new_envs: New env
*/
void set_var(char *arg1, char *arg2, char *new_envs[])
{
	char *new_var, var_to_set[ARG_MAX];
	short i = 0, j = 0;

	if (!arg1 || !arg2)
	{
		write(STDERR_FILENO, "setenv: parameters not found\n", 29);
		return;
	}

	_strcpy(var_to_set, arg1);
	_strcat(var_to_set, "=");

	while (environ[i] && _strncmp(environ[i], var_to_set, _strlen(var_to_set)))
		i++;

	_strcat(var_to_set, arg2);
	if (environ[i])
		_strcpy(environ[i], var_to_set);
	else
	{
		new_var = malloc(100);
		_strcpy(new_var, var_to_set);
		while (new_envs[j])
			j++;
		new_envs[j] = new_var;
		new_envs[j + 1] = NULL;
		environ[i++] = new_var;
		environ[i] = NULL;
	}
}

/**
 * unset_var - unsets an env var
 * @var_name: var to unset
 * @new_envs: New env.
 * Return: void
 */

void unset_var(char *var_name, char *new_envs[])
{
	short i = 0, j = 0;
	char var_to_rm[ARG_MAX];

	if (!var_name)
	{
		write(STDERR_FILENO, "unsetenv: parameter not found\n", 30);
		return;
	}

	_strcpy(var_to_rm, var_name);
	_strcat(var_to_rm, "=");

	while (environ[i] && _strncmp(environ[i], var_to_rm, _strlen(var_to_rm)))
		i++;
	for (j = 0; new_envs[j]; j++)
		if (!_strcmp(new_envs[j], environ[i]))
			break;
	if (!environ[i])
	{
		write(STDERR_FILENO, "unsetenv: Variable not found\n", 29);
		return;
	}
	else
	{
		free(environ[i]);
	}
	while (environ[i])
	{
		environ[i] = environ[i + 1];
		new_envs[j] = new_envs[j + 1];
		i++;
		j++;
	}
}

