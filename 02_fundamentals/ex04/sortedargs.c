/* 
 * Write a program that prints out the words it receives on the command line
 * sorted by their lengths, from shortest to longest, one per line. Words of
 * the same length can be in any order.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] ) 
{

	/* Simple bubble sort */
	char *p;

	for (int i = 1; i < argc - 1; i++ ) {

		for (int j = i + 1; j < argc; j++) {

			if ( strlen(argv[i]) > strlen(argv[j]) ) {
				p = argv[i];
				argv[i] = argv[j];
				argv[j] = p;
			}
		}
	}

	for (int i = 0; i < argc; i++ ) {
		printf("%s\n", argv[i]);
	}

	return 0;
}
