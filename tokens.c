#include "main.h"
char **tokenize(char *line)
{
	int length = 0;
	int range = 16;
	char **tokens = malloc(range * sizeof(char *));
	char *delim = " \t\r\n|";
	char *token = strtok(line, delim);
	
	while (token != NULL)
	{
		tokens[length] = token;
		length++;
	
		if (length >= range)
		{
			range = (int) (range * 1.5);
			tokens = realloc(tokens, range * sizeof(char *));
		}
		token = strtok(NULL, delim);
	}
	tokens[length] = NULL;
	return tokens;
}
