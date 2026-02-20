/* 
 * The program perror_demo.c in Listing 2-3 purposely used an array of 
 * characters too small for the hostname. Read the man page that describes the
 * limits.h header file, find the system constant that specifies the maximum
 * hostname length, and rewrite the program so that error cannot occur.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

void main () 
{
	char name[HOST_NAME_MAX];
	int returnvalue;

	returnvalue = gethostname(name, HOST_NAME_MAX);
	if ( -1 == returnvalue ) {
		fprintf(stderr, "gethostname(): %s\n", strerror(errno));
		return;
	}
	else {
		printf("%s\n", name);
	}
}
