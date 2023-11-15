#include "main.h"
char *getpath(char *command)
{
	char *full_path, *token;
	char *path = getenv("PATH");
	int access_result;

	if (path == NULL)
	{
		perror("Failed to get PATH");
		exit(1);
	}
	token = strtok(path, ":");

	while (token != NULL)
	{
		full_path = (char *)malloc(strlen(token) + 1 + strlen(command) + 1);
		if (full_path == NULL)
		{
			perror("Memory allocation error");
			exit(1);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);
		
		access_result = access(full_path, X_OK);
		if (access_result == 0)
		{
			return (full_path);
		}
		else if (access_result == -1 && errno != ENOENT)
		{
			perror("Error checking access");
			exit(1);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	return (NULL);
}
