/* Implement a command named transcript so that when a user enters transcript
 * myfile, all of its standard input will be copied to both its standard 
 * output and to the file named myfile.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BUFMAX 64

int main ( int argc, char * argv[] ) {

	if ( argc != 2 || strcmp(argv[1], "--help") == 0 ) {
		fprintf(stderr, "Usage: ./transcript filename\n");
		exit(EXIT_FAILURE);
	}


	int flags = O_RDWR | O_CREAT | O_APPEND;
	mode_t openmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	int outputfd = open(argv[1], flags, openmode);

	if ( outputfd == -1 ) {
		fprintf(stderr, "Error in open(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	char buffer[BUFMAX];
	ssize_t numread;

	while ( (numread = read(STDIN_FILENO, buffer, sizeof(buffer))) >= 0 ) {
		if ( numread == 0 ) {
			/* EOF */
			break;
		}

		if ( write(STDOUT_FILENO, buffer, numread) < numread ) {
			fprintf(stderr, "Less bytes written than expected\n");
			exit(EXIT_FAILURE);
		}

		if ( write(outputfd, buffer, numread) < numread ) {
			fprintf(stderr, "Less bytes written than expected.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	exit(EXIT_SUCCESS);
}
