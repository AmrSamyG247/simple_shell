#include "simple_shell.h"
/**
 * _strcat - concatenates string
 * @dest: first string
 * @src: second string
 * Return: concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int n, i = 0;

	char *new;

	for (n = 0; dest[n] != '\0'; n++)
		;
		while (src[i] != '\0')
		{
			dest[n++] = src[i++];
		}
	if (src[i] == '\0')
		dest[n] = src[i];

	new = dest;
	return (new);
}
/**
 * print_number - prints an integer
 * @n:number
 * Return: void
 */
void print_number(int n)
{
	unsigned int k;
	char letter[1];

	k = n;
	if (k / 10)
	{
		print_number(k / 10);
	}
	letter[0] = k % 10 + '0';
	write(STDIN_FILENO, letter, 1);
}
/**
 * _atoi -  string to  integer
 * @s:  array of characters
 * Return: integer if there is a number or (0) if not
 */
int _atoi(char *s)
{
	int i = 0, j = 0;

	unsigned int n = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			j++;
		if (s[i] >= '0' && s[i] <= '9')
			n = n * 10 + s[i] - '0';
		else if (n > 0)
			break;
		i++;
	}
	if (i == 0)
		return (0);
	if (j % 2 != 0)
		n = (int) -n;
	return (n);
}

