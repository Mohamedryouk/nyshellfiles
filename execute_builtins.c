#include "main.h"
void execute_builtins(char **args)
{
	int i;
	if (args)
	{
		for (i = 0; i < num_builtins(); i++)
		{
			if (strcmp(args[0], builtins[i].name) == 0)
			{
				builtins[i].func(args);
				return;
			}
		}
	}
	else
	{
		perror("Error command not found");
	}

}
