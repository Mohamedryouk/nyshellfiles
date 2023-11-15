#include "main.h"
void execmd(char **argv)
{
	pid_t child = fork();
	char *token, *path;
	int status, exitstatus;
	int signal;
	pid_t wapid;

	if (child == 0)
	{
		if (argv[0][0] == '/')
		{
			execve(argv[0], argv, environ);
			perror("Execve error");
			exit(EXIT_FAILURE);
		}
		else
		{
			token = getpath(argv[0]);
			if (token == NULL)
			{
				perror("Error");
			}
			if (token != NULL)
			{
				execve(token, argv, environ);
				perror("execve error");
				exit(EXIT_FAILURE);
			}
		}
		exit(0);
	}else if (wapid > 0)
	{
		wapid = waitpid(child, &status, 0);
		if (wapid == -1)
		{
			return;
		}
		if (WIFEXITED(status)){
			exitstatus = WEXITSTATUS(status);
			return;
		}
		else if(WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			return;
		}else{
			return;
		}
	}
	return;
	
}
