#include "simple_shell.h"

/****String_helpers_Functions**********/
/**
 * _strlen - Returns the number of characters in a string.
 * @str: the string to find the length of
 *
 * Return: Length of the string.
 */
unsigned int _strlen(char *str)
{
	unsigned int len = 0;

	if (!str)
		return (0);
	while (str[len])
		len++;

	return (len);
}

/**
 * _strcpy - copies string from one pointer to another
 * @src: the pointer to copy from
 * @dest: the pointer to copy to
 * Return: the char pointer of the destination pointer
 */
char *_strcpy(char *src, char *dest)
{
	int i;

	if (src == NULL || dest == NULL)
		return (NULL);
	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = src[i];
	return (dest);
}

/**
 * _strcmp - checks if two strings are equivalent
 * @s1: the first string
 * @s2: the second string
 * Return: 1 if they are equal, else 0.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}

	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

/**
 * _strcat - appends delimeter character and additional string
 * onto the end of destination string
 * @dest: the string to be appended to
 * @src: the additional string to append
 * @delim: a delimeter character that goes between dest and src
 * Return: Nothing..
 */
char *_strcat(char *dest, const char *src, const char *delim)
{
	unsigned int i, len;

	if (!dest || !src)
		return (NULL);

	len = _strlen(dest);

	if (delim)
		dest[len++] = *delim;

	for (i = 0; src[i]; len++, i++)
		dest[len] = src[i];
	dest[len] = src[i];

	return (dest);
}

/**
 * colon_check - checks for doubled or higher tier colon groups in PATH
 * @path: pointer to PATH string to be accessed
 * @command: pointer to command string to be concatenated
 * @buf: a pointer to the pointer of our buffer to hold the concatenated comman
 * @bufstat: a pointer to a pointer to a struct to provide a place for file inf
 * Return: 0 upon failure and 1 upon success
 */
int colon_check(char *path, char *command, char **buf, struct stat **bufstat)
{
	int i, j;

	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':' && path[i + 1] == ':')
		{
			j = _strlen(command);
			mem_init(2, buf, (j + 2));
			*buf = null_init(*buf, (j + 3));
			*buf = _strcat(*buf, ".", NULL);
			*buf = _strcat(*buf, command, "/");
			if (!stat(*buf, *bufstat))
				return (1);
		}
	}
	return (0);
}
