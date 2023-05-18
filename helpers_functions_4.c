#include "simple_shell.h"

/****Memory_helpers_Functions**********/
/**
 * minit2 - allocates memory with malloc and null checks the memory
 * @num: the number of arguments
 * Return: No Value
 */
void minit2(int num, ...)
{
	va_list v_ls;
	char ***v_arg;

	va_start(v_ls, num);
	for (; num; num -= 2)
	{
		v_arg = va_arg(v_ls, char ***);
		*v_arg = malloc(sizeof(char *) * (va_arg(v_ls, int) + 1));
		if (*v_arg == NULL)
			return;
	}
}

/****Excuting_helpers_Functions**********/
/**
 * _free - function to free as many different things as possible
 * @num: number of inputs put into function
 * Return: No Value
 */
void _free(unsigned int num, ...)
{
	unsigned int i;
	va_list v_ls;
	char *temp;

	va_start(v_ls, num);
	for (i = 0; i < num; i++)
	{
		temp = va_arg(v_ls, char *);
		if (temp)
			free(temp);
	}
	va_end(v_ls);
}

/**
 * _getenv - gets the specified environment variable
 * @name: the name of the environironment variable to be got
 * Return: Pointer to the matching environironment variable,
 * otherwise NULL.
 */
char *_getenv(const char *name)
{
	const char *namecpy = name;
	char *environcpy;
	int i, j, envlen;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j] == namecpy[j]; j++)
			;
		if (namecpy[j] == '\0')
		{
			envlen = _strlen(environ[i] + j);
			environcpy = malloc(sizeof(char) * (envlen + 1));
			_strcpy(environ[i] + j, environcpy);
			return (environcpy);
		}
	}
	return (NULL);
}

/**
 * transform_tok - converts a token to its full path if it can be found in PATH
 * @command: the command token to be transformed to its full path if applicable
 * Return: a char pointer to the command either modified or not
 */
char *transform_tok(char *command)
{
	int i, j, k, col_flag = 0;
	char *buf, *path, *token;
	struct stat *bufstat = NULL;

	path = _getenv("PATH");
	bufstat = malloc(sizeof(struct stat));
	if (bufstat == NULL || command == NULL)
	{
		_free(2, path, bufstat);
		return (NULL);
	}
	col_flag = colon_check(path, command, &buf, &bufstat);
	if (col_flag == 1)
	{
		_free(2, path, bufstat);
		return (buf);
	}
	token = strtok(path, ":");
	while (token)
	{
		i = _strlen(command), j = _strlen(token);
		mem_init(2, &buf, (i + j + 2));
		for (k = 0; k < (i + j); k++)
			buf[k] = '\0';
		buf = _strcat(buf, token, NULL);
		buf = _strcat(buf, command, "/");
		if (stat(buf, bufstat) == 0)
		{
			_free(2, path, bufstat);
			return (buf);
		}
		token = strtok(NULL, ":");
		_free(1, buf);
	}
	mem_init(2, &buf, i);
	buf = _strcpy(command, buf);
	_free(2, path, bufstat);
	return (buf);
}

/**
 * pipex - conducts processing of non-terminal input e.g. pipe
 * @argv: pointer array of pointers to the beginning of arguments fed into func
 * Return: a structure pointer to error struct
 */
exit_t *pipex(char **argv)
{
	int i;
	char **cmdtok = NULL, *input;
	exit_t *estat, estat_real;

	estat = &estat_real;
	estat->message = "Error", estat->code = 0, estat->exit = 0;
	get_input(&input, estat);
	cmdtok = tokenize_cmds(input, cmdtok);
	for (i = 0; cmdtok[i]; i++)
	{
		estat = proc(cmdtok[i], argv[0], estat);
		if (estat->exit == 1)
		{
			_free(2, input, cmdtok);
			return (estat);
		}
	}
	_free(2, input, cmdtok);
	return (estat);
}
