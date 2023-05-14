#include "simple_shell.h"

/**
 * _getrealenv - gets the real environment variable, so we can screw
 * up our system by typing random things into setenv
 * @name: the name of environment variable to be found
 * Return: Environmnet variable.
 */
char *_getrealenv(const char *name)
{
	const char *namecpy;
	int i, j;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j]; j++)
		{
			namecpy = name;
			while (environ[i][j] == *namecpy)
			{
				j++;
				namecpy++;
			}
			if (*namecpy == '\0')
			{
				return (environ[i]);
			}
		}
	}

	return (NULL);
}

/**
 * _unsetenv - deletes an environment variable
 * @name: the name of the environment variable to be deleted
 * Return: 0 on success, and 1 on failure.
 */
int _unsetenv(const char *name)
{
	char *env;

	env = (_getrealenv(name));
	env = NULL;

	if (!env)
		return (0);

	return (1);
}

/**
 * _setenv - sets or creates an environment variable
 * @name: the name of the environment variable to be changed or created
 * @value: the value to be set with name
 * @overwrite: 1 if you want to overwrite set environment variable, 0 if not
 * Return: 0 on success, 1 on failure.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int nlen, vlen;
	char *env = NULL, *buffer = NULL;

	printf("%s\n", getenv("MAIL"));
	env = (_getrealenv(name));
	printf("%s\n", env);
	if (overwrite)
	{
		vlen = _strlen((char *)value);
		nlen = _strlen((char *)name);
		buffer = malloc(sizeof(char) * (vlen + nlen + 2));
		if (!buffer)
			return (1);
	}

	if (overwrite)
	{
		_strcpy((char *)name, buffer);
		*(buffer + nlen) = '=';
		_strcpy((char *)value, buffer + nlen + 1);

		env = buffer;
	}

	if (env)
		return (0);

	return (1);
}

/**
 * simshell_setenv - calls the setenv function with correct parameters
 * @arraytoken: the array of tokens to be passed
 * Return: Always 0.
 */
int simshell_setenv(char **arraytoken)
{
	int i;

	for (i = 0; arraytoken[i]; i++)
		;

	if (i != 3)
	{
		write(1, "Error: Wrong amount of arguments\n", 34);
		return (0);
	}

	_setenv(arraytoken[1], arraytoken[2], 1);

	return (0);
}
