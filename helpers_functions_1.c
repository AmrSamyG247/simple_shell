#include "simple_shell.h"

/**
 * count_tokens - counts the number of tokens to be copied
 * @input: the input string to analyze for tokens
 * @delim: the delimeter string to base tokenization on
 * Return: the number of tokens in the input string
 */
int count_tokens(char *input, const char *delim)
{
	int count;
	char *token;

	token = strtok(input, delim);

	for (count = 0; token; count++)
		token = strtok(NULL, delim);

	return (count);
}

/**
 * create_arraytoken - create array of pointers to tokens of the input string
 * @input: a string to tokenize and have the pointers point to those tokens
 * @arraytoken: the pointer array to have point to tokens
 * Return: a poiinter array to the tokens of the input string
 */
char **create_arraytoken(char *input, char **arraytoken)
{
	int i;
	char *token;

	arraytoken[0] = NULL;
	if (input == NULL)
		return (arraytoken);
	token = strtok(input, " ");
	if (token == NULL)
		arraytoken[0] = token;
	for (i = 0; token; i++)
	{
		arraytoken[i] = token;
		token = strtok(NULL, " ");
	}
	if (i > 0)
		arraytoken[i] = NULL;
	return (arraytoken);
}

/**
 * get_input - gets input from command line or standard input
 * @input: a pointer to a pointer to the input
 * @estat: the struct that tracks exit codes
 * Return: No value
 */
void get_input(char **input, exit_t *estat)
{
	int i;

	i = _getline(input);
	if (*input == NULL)
		return;
	if (i < 0)
	{
		write(1, "\n", 1);
		free(*input);
		exit(estat->code);
	}
	for (i = 0; (*input)[i]; i++)
		;
	if ((*input)[i - 1] == '\n')
		(*input)[i - 1] = '\0';
}

/**
 * _strtok - tokenizes a string according to a certain delimiter
 * @str: the string to be tokenized
 * @delim: the delimiter to separate tokens
 * @saveptr: a pointer to keep track of the beginning of the token
 * Return: a character pointer to the current delimited token
 */
char *_strtok(char *str, const char *delim, char **saveptr)
{
	int i, j;

	if (str)
		*saveptr = str;
	for (i = 0; delim[i]; i++)
	{
		if (delim[i] == *saveptr[0])
		{
			*saveptr[0] = '\0';
			(*saveptr)++;
			continue;
		}
	}
	for (i = 0; *saveptr[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (delim[j] == *saveptr[i])
			{
				*saveptr[i] = '\0';
				*saveptr += (j + 1);
				return (*saveptr);
			}
		}
	}
	return (*saveptr);
}

/**
 * tokenize_cmds - tokenizes the input string into a pointer array of commands
 * @input: a character pointer to the input string in memory
 * @cmdtok: a pointer array that points to different sets of commands and args
 * Return: a pointer array for the commands
 */
char **tokenize_cmds(char *input, char **cmdtok)
{
	int i;
	char *token, *inputcpy;

	i = _strlen(input), mem_init(2, &inputcpy, i);
	inputcpy = _strcpy(input, inputcpy);
	i = count_tokens(inputcpy, "\n;");
	minit2(2, &cmdtok, i);
	_free(1, inputcpy);
	token = strtok(input, "\n;");
	for (i = 0; token; i++)
	{
		cmdtok[i] = token;
		token = strtok(NULL, "\n;");
	}
	cmdtok[i] = NULL;
	return (cmdtok);
}
