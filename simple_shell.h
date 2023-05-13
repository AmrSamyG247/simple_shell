#ifndef _AMR_MERIEM_A
#define _AMR_MERIEM_A
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <sys/stat.h>

/**
 * struct exit_status - Struct built
 *
 * @message: The exit message
 * @code: The exit code
 * @exit: 1 if should exit shell, 0 if not.
 */
typedef struct exit_status
{
	char *message;
	int code;
	int exit;
} exit_t;

/**
 * struct built - Struct built
 *
 * @cmd: The command
 * @f: The function associated
 */
typedef struct built
{
	char *cmd;
	int (*f)(char **arraytoken);
} built_t;

/* Declaration of global variables */
extern char **environ;

/* Integral functions */
exit_t *proc(char *input, char *ipname, exit_t *estat);
exit_t *change_status(exit_t *estat, char *msg, int cd, int flag);
int niproc(char *av[]);
char *_getenv(const char *name);
ssize_t _getline(char **lineptr);
int check_builtins(char *token, char *inputcpy2, char **arraytoken);
exit_t *child_proc(exit_t *estat, char **arraytoken, char *cpy2, char *ipname);
exit_t *pipex(char **argv);

/* Builtin functions */
int (*get_cmd_func(char *s))(char **arraytoken);
int simshell_cd(char **arraytoken);
int simshell_env(char **arraytoken);
int simshell_exit(char **arraytoken);
int simshell_setenv(char **arraytoken);
