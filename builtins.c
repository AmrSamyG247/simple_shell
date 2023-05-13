#include "simple_shell.h"

/**
 * simshell_cd - Changes the user's current directory.
 * @arraytoken: the directory to be changed to
 * Return: 0 on success, 1 on failure.
 */
int simshell_cd(char **arraytoken)
{
	(void)arraytoken;
	return (0);
}

/**
 * simshell_env - Prints the user's global environment variable.
 * @arraytoken: An unused string.
 * Return: 0 on success, 1 on failure.
 */
int simshell_env(char **arraytoken)
{
	int i, len;

	(void)arraytoken;
	for (i = 0; environ[i]; i++)
	{
		len = _strlen(environ[i]);
		write(1, environ[i], len);
		write(1, "\n", 1);
	}
	return (0);
}

/**
 * simshell_exit - Exits the user's shell.
 * @arraytoken: An unused string.
 * Return: 0 on success, 1 on failure.
 */
int simshell_exit(char **arraytoken)
{
	(void)arraytoken;
	return (1);
}
