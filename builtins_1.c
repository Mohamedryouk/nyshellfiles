#include "main.h"
void shell_exit(char **args)
{
	exit(0);
}
void cd(char **args)
{
	char cwd[1024], *home, *currentdir, *backslash, *oldpwd;
	char *home_error = "Error: home not found";
	oldpwd = getenv("PWD");

	if (args[1] == NULL)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			if (chdir(home) != 0)
			{
				perror("shell: cd:");
			}
		}
		else
		{
			write(STDERR_FILENO, home_error, strlen(home_error));
		}
	}
	else if (strcmp(args[1], "..") == 0)
	{
		currentdir = getcwd(NULL, 0);
		backslash = strrchr(currentdir, '/');
		if (backslash != NULL)
		{
			backslash ='\0';
			if (chdir(currentdir) != 0)
			{
				perror("Shell: cd:");
			}
		}
		free(currentdir);
	}
	else
	{
		if (chdir(args[0]) != 0)
		{
			perror("shell: cd:");
		}

	
		if (oldpwd != NULL)
		{
			setenv("OLDPWD", oldpwd, 1);
		}
		if(getcwd(cwd, sizeof(cwd)) != NULL)
		{
			setenv("PWD", cwd, 1);
		}else{
			perror("shell: cd:");
		}
	}
}
void help(char **args)
{
	char *helptext =
		" shell - the alx shell.\n"
		" the following commands are available:\n"
		" cd	change the working directory.\n"
		" exit	Exit the shell.\n"
		" help	print this help text.\n";
	write(STDOUT_FILENO, helptext, strlen(helptext));
}
struct builtin builtins[] = {
	{"help", help},
	{"exit", shell_exit},
	{"cd", cd},
};
int num_builtins()
{
	return (sizeof(builtins) / sizeof(struct builtin));
}
