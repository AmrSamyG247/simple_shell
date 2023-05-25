#include "simple_shell.h"
/**
 * print_alias - handles the alias built in
 * @av: arguments
 * @alias: array of aliases
 * Return: continue status = 2
 */
int print_alias(char *av[], char *alias[])
{
	int i = 0, j = 1, len, flag = 0, set_res = 0, eq_len = 0;
	char al_name[ARG_MAX];

	if (!av[j])
	{
		while (alias[i])
		{
			len = _strlen(alias[i]);
			write(STDOUT_FILENO, alias[i++], len);
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	while (av[j])
	{
		while (alias[i])
		{
			_strcpy(al_name, alias[i]);
			_strtok(al_name, "=");
			eq_len = _strlen(al_name);
			if (!_strcmp(al_name, av[j]) && alias[i][eq_len] == '=')
			{
				len = _strlen(alias[i]);
				write(STDOUT_FILENO, alias[i], len);
				write(STDOUT_FILENO, "\n", 1), flag++;
			}
			i++;
		}
		if (!flag)
		{
			set_res = set_alias(av[j], alias);
			if (!set_res)
			{
				len = _strlen(av[j]);
				write(STDOUT_FILENO, av[j], len);
				write(STDOUT_FILENO, ": Not found\n", 12);
			}
		}
		flag = 0, j++, i = 0;
	}
	return (2);
}
/**
 * set_alias - new alias setting
 * @new_alias: storing new aliase
 * @alias: aliases stored
 * Return: 0 on error, or 1 in success
 */
short set_alias(char *new_alias, char *alias[])
{
	int i = 0, len = 0, check_alias;
	char new_alias_cpy[ARG_MAX], *alias_name, *alias_value, al_cpy[ARG_MAX];
	char old_alias_cpy[ARG_MAX];

	check_alias = check_new_alias(new_alias);
	if (!check_alias)
		return (0);

	_strcpy(al_cpy, new_alias);
	alias_name = _strtok(al_cpy, "=");
	alias_value = _strtok(NULL, "=");
	if (!alias_value)
		alias_value = "''";
	_strcpy(new_alias_cpy, alias_name), _strcat(new_alias_cpy, "=");
	if (alias_value[0] != '\'')
		_strcat(new_alias_cpy, "'");
	_strcat(new_alias_cpy, alias_value);

	len = _strlen(alias_value);
	if (alias_value[len - 1] != '\'')
		_strcat(new_alias_cpy, "'");

	i = 0;
	while (alias[i])
	{
		_strcpy(old_alias_cpy, alias[i]);
		_strtok(old_alias_cpy, "=");
		if (!_strcmp(old_alias_cpy, alias_name))
		{
			_strcpy(alias[i], new_alias_cpy);
			return (1);
		}
		i++;
	}
	alias[i] = malloc(ARG_MAX);
	if (!alias[i])
		exit(-1);
	_strcpy(alias[i++], new_alias_cpy);
	alias[i] = NULL;
	return (1);
}
/**
 * check_new_alias - checks argument
 * @new_alias: argument
 * Return: 1 on success or 0 on error
 */
int check_new_alias(char *new_alias)
{
	int i = 0, equals_count = 0;

	while (new_alias[i])
	{
		if (new_alias[i] == '=')
			equals_count++;
		i++;
	}
	if (!equals_count || (equals_count == 1 && new_alias[0] == '='))
		return (0);
	return (1);
}
/**
 * alias_expansion -  alias expansions
 * @av:argumennts to the prog
 * @alias: aliases stored
 * Return: void
 */
void alias_expansion(char *av[], char *alias[])
{
	int i = 0, j = 0, eq_len, len;
	char checker[1000], *token, new_args[1000], *alias_exp[100];

	if (!alias || !alias[0])
		return;
	_strcpy(checker, alias[i]), token = _strtok(checker, "=");
	while (token && alias[i])
	{
		eq_len = _strlen(token);
		if (!_strcmp(token, av[0]) && alias[i][eq_len] == '=')
			break;
		i++;
		if (alias[i])
			_strcpy(checker, alias[i]), token = _strtok(checker, "=");
	}
	if (!alias[i])
		return;
	token = _strtok(NULL, "="), _strcpy(new_args, token);
	token = _strtok(new_args, " ");
	for (i = 0; token; i++)
	{
		eq_len = _strlen(token);
		if (token[0] == '\'' && token[1] != '\'')
			alias_exp[i] = malloc(eq_len), _strcpy(alias_exp[i], token + 1);
		else if (token[0] == '\'' && token[1] == '\'')
			alias_exp[i] = malloc(1), _strcpy(alias_exp[i], "");
		else
			alias_exp[i] = malloc(eq_len + 1), _strcpy(alias_exp[i], token);
		token = _strtok(NULL, " ");
	}
	if (_strcmp(alias_exp[i - 1], ""))
		len = _strlen(alias_exp[i - 1]), alias_exp[i - 1][len - 1] = '\0';

	for (j = 1; av[j]; j++, i++)
	{
		alias_exp[i] = malloc(_strlen(av[j]) + 1);
		 _strcpy(alias_exp[i], av[j]), free(av[j]);
	}
	free(av[0]), alias_exp[i] = NULL, copy_array(av, alias_exp);
	alias_expansion(av, alias);
}

/**
 * copy_array - copy arrays and free old ones
 * @av: dest
 * @alias_exp: array to be copied
 * Return: void
 */
void copy_array(char *av[], char *alias_exp[])
{
	int i;

	for (i = 0; alias_exp[i]; i++)
	{
		av[i] = malloc(_strlen(alias_exp[i]) + 1);
		_strcpy(av[i], alias_exp[i]), free(alias_exp[i]);
	}
	av[i] = NULL;
}

