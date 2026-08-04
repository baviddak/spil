#ifndef MYPOPENCLOSE_H_
#define MYPOPENCLOSE_H_

#include <stdio.h>

#define SHELL_PATH "/bin/sh"

FILE *mypopen(const char *command, const char *type);
int mypclose(FILE *stream);

#endif // MYPOPENCLOSE_H_
