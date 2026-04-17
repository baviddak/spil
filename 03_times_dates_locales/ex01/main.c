/* Write a program that expects one or more hexadecimal numbers on the command
 * line and, for each number, prints its value as a decimal integer, one per
 * line.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define HEXBASE 16

int main ( int argc, char *argv[] ) {

	/* Basic options validation */
	if ( argc < 2 || strcmp(argv[1], "--help") == 0) {
		fprintf(stderr, "Usage: ./hex2int <hexvalue> ...\n");
		exit(EXIT_FAILURE);
	}

	char *eptr;
	long result;

	errno = 0; 
	for (int i = 1; i < argc; i++) {
		
		result = strtol(argv[i], &eptr, HEXBASE);

		if ( errno == ERANGE ) {
			fprintf(stderr, "Error: strtol() set errno to %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if ( *eptr != '\0' ) {
			fprintf(stdout, "%s: not a valid number\n", argv[i]);
			continue;
		}

		fprintf(stdout, "%s = %ld\n", argv[i], result);

		/* Reset some values */
		eptr = NULL;
		errno = 0;
	}

	exit(EXIT_SUCCESS);
}
