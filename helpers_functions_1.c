#include "simple_shell.h"
/**
 * create_write_file -creates  history file
 * @filename: name of the file
 * @content_to_wr: command to be stored
 * Return: 1 on success
 */
short create_write_file(const char *filename, char *content_to_wr)
{
	int fd, len, write_chars;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0600);

	if (fd < 0)
		return (-1);

	if (content_to_wr && content_to_wr[0] != '\0')
	{
		for (len = 0; content_to_wr[len]; len++)
			;
		write_chars = write(fd, content_to_wr, len);
		close(fd);
		if (write_chars < 0 || write_chars != len)
			return (-1);
	}
	close(fd);
	return (1);
}
/**
 * get_filename -  gets the path of the history file
 * @filename: pointer to the filename
 * @envp: envs array
 * Return: returns 1 on success
 */
short get_filename(char **filename, char *envp[])
{
	char *token;
	short i = 0;

	while (_strncmp(envp[i], "HOME=", 5))
		i++;
	if (!envp[i])
		return (0);

	*filename = malloc(1024); /* ojo */
	if (!*filename)
		exit(-1);
	_strcpy(*filename, envp[i]);
	token = _strtok(*filename, "=");
	token = _strtok(NULL, ":");

	_strcpy(*filename, token);
	_strcat(*filename, "/");
	_strcat(*filename, "simple_shell_history");
	return (1);
}
/**
 * print_history -displays the history
 * @filename: name of the file
 * Return: void
 */
void print_history(char *filename)
{
	int fd_h = 0, read_char = 1, close_res, i = 0, flag = 0, j;
	char buffer[1000000];
	int flag_hist;
	int line_count;

	if (!filename)
		return;
	fd_h = open(filename, O_RDONLY);
	if (fd_h < 0)
		exit(-1);

	while (read_char > 0)
	{
		read_char = read(fd_h, buffer, 999999);
		if (read_char < 0)
			exit(-1);
		buffer[read_char] = '\0';
		if (read_char)
		{
			for (j = 0; buffer[j]; j++)
				if (buffer[j] == '\n' && !flag_hist)
					line_count += 1;
			if (!flag_hist)
				line_count %= 4096;
			flag_hist = line_count;
			print_loop_his(buffer, &i, &line_count, &flag);
			flag++;
		}
	}
	close_res = close(fd_h);
	if (close_res != 0)
		exit(-1);
}
/**
 * print_loop_his - loop for history printing
 * @buffer: read data string
 * @i: index
 * @line_count: line coun
 * @flag: flag
 * Return: void
 */
void print_loop_his(char *buffer, int *i, int *line_count, int *flag)
{
	int temp;

	temp = *line_count;
	while (buffer[*i])
	{
		if (buffer[*i] == '\n' && buffer[*i + 1])
		{
			write(STDIN_FILENO, buffer + *i, 1), (*i)++;
			write(STDIN_FILENO, " ", 1);
			print_number(*line_count), (*line_count)++;
			write(STDIN_FILENO, "  ", 2);
		}
		else if (*i == 0 && buffer[*i + 1] && !*flag)
		{
			write(STDIN_FILENO, " ", 1);
			print_number(*line_count), (*line_count)++;
			write(STDIN_FILENO, "  ", 2);
			write(STDIN_FILENO, buffer + *i, 1), (*i)++;
		}
		else
			write(STDIN_FILENO, buffer + *i, 1), (*i)++;
	}
	*line_count = temp;
}

