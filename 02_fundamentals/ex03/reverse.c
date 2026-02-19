/* 
 * Write a program that prints out the words it receives on the command line
 * in reverse order, one per line.
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{

	for (int i = argc - 1; i > 0; i--) {
		printf("%s\n", argv[i]);
	}

	return 0;
}
