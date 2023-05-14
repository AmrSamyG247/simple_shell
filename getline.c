#include "simple_shell.h"
#define BUFSIZE 64

/**
 * _getline - Retrieves a line of text from standard input.
 * @lineptr: a NULL ptr that will set to the retrieved text.
 *
 * Return: The number of characters read from standard input.
 */
ssize_t _getline(char **lineptr)
{
	int oldsize, bufsize = BUFSIZE;
	char *buffer;
	ssize_t i = 0;
	int position = 0, c = 0;

	*lineptr = NULL;

	if (!lineptr || !*lineptr)
	{
		buffer = malloc(sizeof(char) * bufsize);
		if (!buffer)
			return (0);
		null_init(buffer, bufsize);
		*lineptr = buffer;
	}

	do {
		c = read(STDIN_FILENO, buffer + position, BUFSIZE);
		if (c == -1 || !*buffer)
			return (-1);
		position += c;

		if (c >= BUFSIZE)
		{
			oldsize = bufsize;
			bufsize += BUFSIZE;
			buffer = _realloc(buffer, oldsize, bufsize);
			if (!buffer)
				return (0);
			*lineptr = buffer;
		}
	} while (c >= BUFSIZE);

	i = _strlen(buffer);
	return (i);
}
