/* 
 * The seq command prints out sequences of numbers. In the simplest case, seq
 * num1 num2 prints every number from num1 through num2. Write a program that
 * implements this simple form of the command. If any arguments are missing, 
 * if they are not two integers such that the first is less than or equal to
 * the second, it should print an error message. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

int main ( int argc, char * argv[] ) 
{
	/* Check the number of args */
	if ( argc != 3 ) {
		fprintf(stderr, "Usage: %s num1 num2\n", argv[0]);
		return -1;
	}

	char *endptr;
	long num1;

	errno = 0;
	num1 = strtol(argv[1], &endptr, 0);

	if ( errno != 0 ) {
		perror("strtol");
		exit(EXIT_FAILURE);
	}

	if ( endptr == argv[1] ) {
		fprintf(stderr, "No digits were found\n");
		exit(EXIT_FAILURE);
	}

	if ( *endptr != '\0' ) {
		printf("Characters following the number: \"%s\"\n", endptr);
	}

	long num2;

	errno = 0;
	num2 = strtol(argv[2], &endptr, 0);

	if ( errno != 0 ) {
		perror("strtol");
		exit(EXIT_FAILURE);
	}

	if ( endptr == argv[2] ) {
		fprintf(stderr, "No digits were found\n");
		exit(EXIT_FAILURE);
	}

	if ( *endptr != '\0' ) {
		printf("Characters following the number: \"%s\"\n", endptr);
	}

	/* Validate second argument is greater than the first */
	if ( num2 < num1 ) {
		fprintf(stderr, "Second argument must be equal or larger to the first.\n");
		exit(EXIT_FAILURE);
	}


	/* Print the sequence out */
	for (long i = num1; i <= num2; i++) {
		printf("%ld\n", i);
	}

	exit(EXIT_SUCCESS);
}
