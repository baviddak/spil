/* 
 * The cat command can be used to concatenate files. For example, cat f1 f2 f3
 * concatenates files f1, f2, and f3 and displays their concatenation on 
 * standard output. Implement this command.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFMAX 16

void mycat ( char * pathname ) {

	int flags = O_RDONLY;
	int fd;
	ssize_t numread;
	char buffer[BUFMAX];

	if ( (fd = open(pathname, flags)) == -1 ) {
		fprintf(stderr, "Error in open(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	while ( (numread = read(fd, buffer, sizeof(buffer))) >= 0 ) {

		if ( numread == 0 ) {
			/* EOF */
			break;
		}

		if ( write(STDOUT_FILENO, buffer, numread) < numread ) {
			fprintf(stderr, "Less bytes written than expected\n");
			exit(EXIT_FAILURE);
		}
	}

	/* Is this necessary? */
	close(fd);
}

int main ( int argc, char *argv[] ) {

	if ( argc < 2 || strcmp(argv[1], "--help") == 0 ) {
		fprintf(stderr, "Usage: mycat <file1> <file2> ...\n");
		exit(EXIT_FAILURE);
	}

	for ( int i = 1; i < argc; i++ ) {
		mycat(argv[i]);
	}

	exit(EXIT_SUCCESS);
}
