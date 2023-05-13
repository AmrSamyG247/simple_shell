#include "simple_shell.h"

/***shell_cmd_function***/
/**
 * get_cmd_func - If possible, retrieves the function that corresponds
 * to a built-in command such as 'env' or 'exit'.
 * @s: the string to be compared with list of known built-in commands
 *
 * Return: The corresponding function if one is found, otherwise NULL.
 */
int (*get_cmd_func(char *s))(char **arraytoken)
{
	built_t cmds[] = {
	{"env", simshell_env},
	{"setenv", simshell_setenv},
	{"unsetenv", simshell_setenv},
	{"cd", simshell_cd},
	{"exit", simshell_exit},
	{NULL, NULL}
	};
	int i = 0;

	while (cmds[i].cmd)
	{
		if (_strcmp(s, cmds[i].cmd))
			return (cmds[i].f);
		i++;
	}

	return (cmds[i].f);
}

/***child_process_handeling_shell***/
/**
 * child_proc - processes input if child_pid == 0
 * @estat: the struct handeling exit status
 * @ar: the array of tokens containing input
 * @cpy2: the input stored as a character pointer
 * @ipname: the name of our shell
 * Return: Struct handeling exit codes.
 */
exit_t *child_proc(exit_t *estat, char **ar, char *cpy2, char *ipname)
{
		if (ar[0] == NULL || *(ar[0]) == '\0')
		{
			_free(3, ar[0], cpy2, ar);
			estat = change_status(estat, NULL, estat->code, 1);
			return (estat);
		}
		if (execve(ar[0], ar, environ) == -1)
		{
			_free(3, ar[0], cpy2, ar);
			perror(ipname);
			estat = change_status(estat, NULL, 127, 1);
			return (estat);
		}

	return (estat);
}

