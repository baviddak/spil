/* 
 * Write a program that sorts the words entered on the connand line and prints
 * them on the standard output, one per line.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

int main (int argc, char *argv[] ) {

	if ( argc < 3 || strcmp(argv[1], "--help") == 0 ) {
		fprintf(stderr, "Usage: %s <string> <string> ...\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ( setlocale(LC_COLLATE, "") == NULL ) {
		fprintf(stderr, "setlocale() returned NULL\n");
		exit(EXIT_FAILURE);
	}

	/* use strcoll() instead of strcmp; utilize a simple bubble sort */
	char *p;

	for ( int i = 1; i < argc - 1; i++ ) {

		for ( int j = i + 1; j < argc; j++ ) {

			if ( strcoll(argv[i], argv[j]) > 0 ) {
				p = argv[i];
				argv[i] = argv[j];
				argv[j] = p;
			}
		}
	}

	for ( int i = 1; i < argc; i++ ) {
		printf("%s\n", argv[i]);
	}

	exit(EXIT_SUCCESS);
}
