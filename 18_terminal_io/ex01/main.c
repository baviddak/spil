/* Write a function int istty(int fd) that returns 1 if the file descriptor is
 * that of a terminal and 0 if it isn't.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

int istty (int fd) {
	struct termios mytermstr;

	if ( -1 == tcgetattr(fd, &mytermstr) ) {
		return 0;
	} else {
		return 1;
	}
	
}

int main ( int argc, char *argv[] ) {
	
	if ( argc != 2 || strcmp(argv[1], "--help") == 0 ) {
		fprintf(stderr, "Usage: ./test <filename>\n");
		exit(EXIT_FAILURE);
	}
	
	int flags = O_RDWR;	
	int fd = open(argv[1], flags);

	if ( fd == -1 ) {
		fprintf(stderr, "Error in open(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "istty() returned: %d\n", istty(fd) );

	exit(EXIT_SUCCESS);
}
