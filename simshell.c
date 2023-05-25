#include "simple_shell.h"
/**
* get_input - prompt and iput.
* @av: Argument.
* @command: String of input.
* @args: Argument .
* Return: Result of the getline funcion.
*/
short get_input(char *av[], char **command, int *args)
{
	short getl_res = 0, write_err = 0;
	int size = ARG_MAX, File_Des;

	if (*args == 1)
	{
		if (isatty(STDIN_FILENO))
			write_err = write(STDOUT_FILENO, "$ ", 2);
		if (write_err == -1)
		{
			perror(av[0]);
			free(command);
			exit(-1);
		}

		getl_res = _getline(command, &size, STDIN_FILENO);
		if (isatty(STDIN_FILENO) && getl_res == EOF)
			write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		File_Des = open(av[1], O_RDONLY);
		getl_res = _getline(command, &size, File_Des);
		close(File_Des);
		*args = 0;
	}
	return (getl_res);
}
/**
* tokenize - convert input to token.
* @command: Command
* @av: pointers to tokens
* @status: Staatus.
* @alias: array of aliases.
* @filename: file
* @new_envs: New env.
* Return: 1 in case of exit signal, 0 otherwise.
*/
short tokenize(char *command, char *av[], char *alias[], char *filename,
int *status, char *new_envs[])
{
	char *token;
	short i = 0, builtin = 0, j = 0;

	token = _strtok(command, " ");
	av[i] = malloc(_strlen(token) + 1);
	if (!av[i])
		exit(-1);
	_strcpy(av[i++], token);
	while ((token = _strtok(NULL, " ")))
	{
		av[i] = malloc(_strlen(token) + 1);
		if (!av[i])
		{
			free(command);
			for (--i; i >= 0; i--)
				free(av[i]);
			exit(-1);
		}
		_strcpy(av[i++], token);
	}
	av[i] = NULL;
	i = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] == '\'')
				av[i][j] = ' ';
			j++;
		}
		i++;
		j = 0;
	}
	expand_vars(av, status);
	alias_expansion(av, alias);
	builtin = check_builtins(av, alias, filename, new_envs, *status);
	if (builtin)
		return (builtin);
	return (0);
}
/**
* exec_command - Executes
* @filename: file name.
* @av: token.
* @prog_name: program name
* @envp: Env
* @status: status
*/
void exec_command(char *filename, char *av[], char *prog_name, char *envp[],
int *status)
{
	pid_t child;
	short i = 0;
	char *token[100], *full_comm = NULL, *path_str = NULL;

	path_str = getenvtok(envp, "PATH", token);
	child = fork();
	if (!child)
	{
		do {
			full_comm = malloc(_strlen(token[i]) + _strlen(av[0]) + 2);
			if (!full_comm)
				exit(-1);
			_strcpy(full_comm, token[i]);
			_strcat(full_comm, "/");
			execve(_strcat(full_comm, av[0]), av, envp);
			free(full_comm);
			i++;
		} while (token[i]);
		execve(av[0], av, envp);
		perror(prog_name);
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(path_str);
		free(filename);
		_exit(127);
	}
	else
	{
		wait(status);
		*status >>= 8;
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(full_comm), free(path_str);
	}
}
/**
* sig_handler -handle signals.
* @signum: Numbn.
*/
void sig_handler(int signum)
{
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n$ ", 3);
}
/**
* main - Entry point .
* @argc: counter.
* @argv: Argumen.
* @envp: Env
* Return: 0 on success.
*/
int main(int argc, char *argv[], char *envp[])
{
	char *command, *alias[1000], *filename, *new_envs[100];
	short getl_res = 0, i, history_res = 1, file_res = 0;
	int status = 0;

	alias[0] = NULL, signal(SIGINT, sig_handler);
	new_envs[0] = NULL;
	command = NULL;
	while (1)
	{
		command = malloc(ARG_MAX);
		if (!command)
			return (-1);
		if (argc == 0)
			break;
		getl_res = get_input(argv, &command, &argc);
		if (getl_res == EOF)
			break;
		if (remove_spaces(command))
			continue;
		if (!file_res)
			file_res = get_filename(&filename, envp);
		if (file_res)
		{
			history_res = create_write_file(filename, command);
			if (history_res != 1)
				free(command), exit(-1);
		}
		prepare_command(command, argv, envp, alias, filename, new_envs, &status);
	}
	free(command);
	for (i = 0; alias[i]; i++)
		free(alias[i]);
	if (file_res)
		free(filename);
	for (i = 0; new_envs[i]; i++)
		free(new_envs[i]);
	return (status);
}

