#include "main.h"
#include <stdio.h>
#include <unistd.h>
int main(int __attribute__((unused)) ac, char **av __attribute__((unused)))
{
	char **args;
	char *prompt = "~$ ";
	char **tokens;
	char *line;
	int mode = 1;
	if (isatty(STDIN_FILENO))
	{
		while (mode)
		{
			write(STDOUT_FILENO, prompt, strlen(prompt));
			line = read_input();
			if (line == NULL)
			{
				break;
			}
			tokens = tokenize(line);
			if (tokens[0] != NULL)
			{
				execmd(tokens);
				execute_builtins(tokens);
			}
			free(tokens);
			free(line);
		}
	}
	else
	{
		while (mode)
		{
			line = read_input();
			if (line == NULL)
			{
				break;
			}
			tokens = tokenize(line);
			if (tokens[0] != NULL)
			{
				execmd(tokens);
			}
			free(tokens);
			free(line);
		}
	}
	return (0);
}
