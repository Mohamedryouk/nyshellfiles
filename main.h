#ifndef MAIN_H
#define MAIN_H
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
extern char **environ;
struct builtin {
	char *name;
	int (*func)(char **args);
};
void execute_builtins(char **args);
extern struct builtin builtins[];
char *getpath(char *command);
char **tokenize(char *line);
int main(int __attribute__((unused)) ac, char **av __attribute__((unused)));
char *read_input();
void execmd(char **argv);
int help(char **args);
int cd(char **args);
int shell_exit(char **args);
int num_builtins();
#endif
