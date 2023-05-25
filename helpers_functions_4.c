#include "simple_shell.h"
/**
* _strtok - Our strtok.
* @base: String .
* @delims: Delimiters.
* Return:  next token.
*/
char *_strtok(char *base, char *delims)
{
	static char *copy;
	static int i;
	int j = 0, word_found = -1, blanks = 0;
	char *ret_str;

	if (base)
	{
		i = 0;
		copy = base;
	}
	while (copy[i])
	{
		while (delims[j])
		{
			if (copy[i] == delims[j])
			{
				blanks = 1;
				if (word_found >= 0)
				{
					copy[i++] = '\0';
					ret_str = copy + word_found;
					return (ret_str);
				}
			}
			j++;
		}
		j = 0;
		if (word_found == -1 && !blanks)
		{
			word_found = i;
		}
		blanks = 0;
		i++;
	}
	if (word_found == -1)
		return (0);
	ret_str = copy + word_found;
	return (ret_str);
}
/**
* _strncmp - Compares  bytes .
* @s1: First string.
* @s2: Second string.
* @n: bytes to  compare.
* Return: 0 if equal, difference if not.
*/
short _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while (i < n && *(s1 + i) && *(s2 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			return (*(s1 + i) - *(s2 + i));
		i++;
	}
	if (i < n && *(s1 + i) != *(s2 + i))
		return (*(s1 + i) - *(s2 + i));
	return (0);
}
/**
 * _strlen -  length of a string
 * @s: pointer to  string
 * Return:  chars in the string
 */
int _strlen(char *s)
{
	int n = 0;

	if (s)
		for (n = 0; *s; s++)
			n++;
	return (n);
}
/**
 * _strcpy - copies string
 * @dest: pointer to  copy
 * @src:  char array
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	if (dest && src)
		while ((*dest++ = *src++))
			;
	return (dest);
}
/**
 * _strcmp - compares the ascii sum of characters in two strings
 * @dest: pointer
 * @src: pointer
 * Return: integer. positive if the first string is bigger
 */
int _strcmp(char *dest, char *src)
{
	int i = 0, k = 0;

	while (dest[i] != '\0')
	{
		if (dest[i] > src[i])
		{
			k = dest[i] - src[i];
			break;
		}
		else if (dest[i] < src[i])
		{
			k = dest[i] - src[i];
			break;
		}
	i++;
	}
	if (src[i] != '\0' && k == 0)
	k = -src[i];
	return (k);
}

