#include "main.h"
int print_env()
{
	int i;

	if (environ == NULL	)
	{
		perror("Error: environ is not accessible");
		return (-1);
	}
	for (i = 0; environ[i]; i++)
	{
		if (write(STDOUT_FILENO, environ[i], strlen(environ[i])) == -1)
		{
			perror("write");
			return (-1);
		}
		if (write(STDOUT_FILENO, "\n", 1) == -1)
		{
			perror("write");
			return (-1);
		}
	}
	return (-1);
}
int shell_exit(char **args)
{
	int exitstatus;

	if (args[1] != NULL)
	{
		exitstatus = atoi(args[1]);
		exit(exitstatus);
	}
	else
	{
		exit(0);
	}
}		
int cd(char **args)
{
	int state = -1;
	char cwd[1024];

	if (args[1] == NULL)
		state = chdir(getenv("HOME"));
	else if (strcmp(args[1], "-") == 0)
	{
		state = chdir(getenv("OLDPWD"));
	}
	else
	{
		state = chdir(args[1]);
	}
	if (state == -1)
	{
		perror("shell");
		return (-1);
	}
	else
	{
		getcwd(cwd, sizeof(args));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (1);
}
int help(char **args)
{
	char *helptext =
		" shell - the alx shell.\n"
		" the following commands are available:\n"
		" cd	change the working directory.\n"
		" exit	Exit the shell.\n"
		" env prints current envirnoment"
		" help	print this help text.\n";
	write(STDOUT_FILENO, helptext, strlen(helptext));
	return (1);
}
struct builtin builtins[] = {
	{"help", help},
	{"exit", shell_exit},
	{"-cd", cd},
	{"-env", print_env},
};
int num_builtins()
{
	return (sizeof(builtins) / sizeof(struct builtin));
}
