#include "main.h"
char *read_input()
{
	char *line = NULL;
	ssize_t not_read;
	size_t buflen = 0;

	not_read = getline(&line, &buflen, stdin);
	if (not_read == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
