#include "main.h"
void execmd(char **argv)
{
	pid_t child = fork();
	char *token;
	int status;

	if (child == 0)
	{
		if (argv[0][0] == '/')
		{
			execve(argv[0], argv, NULL);
			wait(&status);
		}
		else
		{
			token = getpath(argv[0]);
			execve(token, argv, NULL);
			exit(1);
		}
	}
	else if (child > 0)
	{
		int status;
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
		{
			return;
		}
		else if (WIFSIGNALED(status))
		{
			return;
		}
	}else{
		perror("Error command not found");
	}
}
