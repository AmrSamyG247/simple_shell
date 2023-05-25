#include "simple_shell.h"
/**
* prepare_command - Parses and check commands
* @command: input from user
* @argv: Argument .
* @envp: Env.
* @alias: Alias .
* @filename: Name of file.
* @new_envs: New env.
* @status: status
*/
void prepare_command(char *command, char *argv[], char *envp[], char *alias[],
char *filename, char *new_envs[], int *status)
{
	short i = 0, j = 0, quote_flag = 0, idx = 0, checks = -1, tok_res;
	char *exec_comm, new_command[ARG_MAX], *av[100];

	while (command[i])
	{
		if (command[i + 1] && (command[i] == '\n' || command[i] == ';'))
		{
			new_command[j++] = ' ', new_command[j++] = '\n';
			new_command[j++] = ' ', i++;
			continue;
		}
		else if (command[i] == '\'' || command[i] == '"')
		{
			quote_flag = ~quote_flag;
			i++;
			continue;
		}
		else if (command[i] == ' ' && quote_flag)
		{
			new_command[j++] = '\'';
			i++;
			continue;
		}
		new_command[j] = command[i], i++, j++;
	}
	free(command), new_command[j] = '\0';
	new_command[_strlen(new_command) - 1] = '\0', exec_comm = new_command;
	do {
		exec_comm += idx;
		checks = check_newlines(exec_comm, &idx);
		tok_res = tokenize(exec_comm, av, alias, filename, status, new_envs);
		if (tok_res)
		{
			for (i = 0; av[i]; i++)
				free(av[i]);
			continue;
		}
		exec_command(filename, av, argv[0], envp, status);
	} while (!checks || (checks == 1 && !*status) || (checks == 2 && *status));
}

/**
* check_newlines - Checks for newlines.
* @av: args.
* @idx: pointer to index.
* Return: 0 if \n or ; 1 if &&, 2 if ||, and 3 if #.
*/
short check_newlines(char *av, short *idx)
{
	short i = 0, retv = -1;

	while (av[i])
	{
		if (av[i] == '\n' || av[i] == ';' || (av[i] == '&' && av[i + 1] == '&') ||
			(av[i] == '|' && av[i + 1] == '|') || av[i] == '#')
		{
			switch (av[i])
			{
				case '&':
					retv = 1;
					av[i] = '\0';
					i++;
					break;
				case '|':
					retv = 2;
					av[i] = '\0';
					i++;
					break;
				case '#':
					retv = 3;
					break;
				default:
					retv = 0;
					break;
			}
			av[i] = '\0';
			*idx = ++i;
			break;
		}
		i++;
	}
	return (retv);
}
/**
 * my_exit - exits the program
 * @av: args
 * @alias: aliases
 * @filename: used memory.
 * @new_envs: New env.
 * @status: status
 * Return: void
 */

void my_exit(char *av[], char *alias[], char *filename, char *new_envs[],
int status)
{
	unsigned char exit_st;
	int i = 0, j = 0;

	if (av[1])
	{
		exit_st = (unsigned char) _atoi(av[1]);
		if (i < 0 || *av[1] < 49 || *av[1] > 57)
		{
			write(STDERR_FILENO, "hsh: 1: exit: Illegal number:\n", 30);
			if (!isatty(STDIN_FILENO))
				exit(2);
		}
		else
		{
			while (alias[j])
				free(alias[j++]);
			j = 0;
			while (new_envs[j])
				free(new_envs[j++]);
			j = 0;
			while (av[j])
				free(av[j++]);
			free(filename);
			exit(exit_st);
		}
	}
	else
	{
		while (alias[i])
			free(alias[i++]);
		i = 0;
		while (new_envs[i])
			free(new_envs[i++]);
		while (av[j])
			free(av[j++]);
		free(filename);
		exit(status);
	}
}

