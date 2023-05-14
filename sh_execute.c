#include "simple_shell.h"

/**
 * change_status - changes the status of error message struct
 * @estat: the struct containing the status
 * @msg: the error messsage
 * @cd: the code
 * @flag: should we exit the shell, 1 is yes, 0 is no
 * Return: Struct.
 */
exit_t *change_status(exit_t *estat, char *msg, int cd, int flag)
{
	if (msg)
		estat->message = msg;
	if (flag == 1 || flag == 0)
		estat->exit = flag;
	estat->code = cd;
	return (estat);
}

/**
 * check_builtins - checks for built-in commands
 * @token: the string to check if matches known built-ins
 * @cpy2: the buffer to be freed if exit is triggered
 * @arraytoken: the array of strings to be freed if exit is triggered
 * Return: an integer to indicate success (0) or failure (1)
 */
int check_builtins(char *token, char *cpy2, char **arraytoken)
{
	if (get_cmd_func(token))
	{
		if (get_cmd_func(token)(arraytoken))
		{
			_free(3, token, cpy2, arraytoken);
			return (1);
		}
		_free(3, token, cpy2, arraytoken);
		return (0);
	}
	return (-1);
}

/**
 * proc - a function to execute processes and tokenize a string input
 * @input: the input string to be tokenized and executed
 * @ipname: the name of the program being run
 * @estat: the struct containing exit information
 * Return: an integer to indicate success (1) or failure (0)
 */
exit_t *proc(char *input, char *ipname, exit_t *estat)
{
	pid_t child_pid;
	int status, i, builtin;
	char **arraytoken, *inputcpy, *cpy2;


	i = _strlen(input), mem_init(4, &inputcpy, i, &cpy2, i);
	inputcpy = _strcpy(input, inputcpy), cpy2 = _strcpy(inputcpy, cpy2);
	i = count_tokens(inputcpy, " "), _free(1, inputcpy), minit2(2, &arraytoken, i);
	arraytoken = create_arraytoken(cpy2, arraytoken), arraytoken[0] = transform_tok(arraytoken[0]);
	builtin = check_builtins(arraytoken[0], cpy2, arraytoken);
	if (builtin == 1)
	{
		estat = change_status(estat, "Exit", estat->code, 1);
		return (estat);
	}
	else if (builtin == 0)
	{
		estat = change_status(estat, NULL, 0, 0);
		return (estat);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		_free(3, arraytoken[0], cpy2, arraytoken), perror("Error:");
		return (estat);
	}
	else if (child_pid == 0)
	{
		return (child_proc(estat, arraytoken, cpy2, ipname));
	}
	else if (child_pid != 0)
	{
		wait(&status), _free(3, arraytoken[0], cpy2, arraytoken);
		estat = change_status(estat, NULL, WEXITSTATUS(status), estat->exit);
	}
	return (estat);
}

/**
 * niproc - handles execution of commands in non-interactive mode
 * @av: the commands passed into non-interactive shell
 * Return: An integer to indicate success (1) or failure (0).
 */
int niproc(char *av[])
{
	pid_t child_pid;
	char *prname = av[0];
	int status;

	av++;
	if (get_cmd_func(av[0]))
	{
		if (get_cmd_func(av[0])(av))
			return (1);
	}
	else
	{
		av[0] = transform_tok(av[0]);
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Fork Error");
			return (0);
		}
		else if (child_pid == 0)
		{
			if (execve(av[0], av, NULL) == -1)
			{
				perror(prname);
				return (0);
			}
		}
		else if (child_pid != 0)
			wait(&status);
		return (1);
	}
	return (0);
}
