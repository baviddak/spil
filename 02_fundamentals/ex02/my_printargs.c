/* 
 * The printargs2.c program in Listing 2-5 used an integer to iterate through
 * the argv[] array. Write a version of it that does not print the argument 
 * numbers and does not use any local variables.
 */

#include <stdio.h>

int main (int argc, char *argv[])
{

	*(argv)++;
	while ( *argv != NULL ) {
		printf("%s\n", *(argv)++);
	}

	return 0;
}
