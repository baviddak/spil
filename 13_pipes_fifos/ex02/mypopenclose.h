#ifndef MYPOPENCLOSE_H_
#define MYPOPENCLOSE_H_

#include <stdio.h>
#include <stdbool.h>

#define SHELL_PATH "/bin/sh"
#define CHILD_PIPES_MAX 32

struct child_pipe {
	int fd;
	pid_t pd;
};

FILE *mypopen(const char *command, const char *type);
int mypclose(FILE *stream);

#endif // MYPOPENCLOSE_H_
