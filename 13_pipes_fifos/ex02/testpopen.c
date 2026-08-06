/* 
 * This exercise explores possible implementations of the popen() and pclose()
 * functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "mypopenclose.h"

#define BUF_MAX 32

int main(int argc, char *argv[]) {

	/* First test popen() */
	/* FILE *pp = popen("ls", "r");

	size_t num_read;
	char buffer[BUF_MAX];

	while ( (num_read = fread(buffer, sizeof(char), BUF_MAX, pp)) > 0 ) {
		printf("Here is some data from ls command\n");
		printf(buffer);
	} */
	

	size_t num_written;
	FILE *ppp = mypopen("grep cat", "w");

	char *animal_list = "dog\nshark\nfish\nlion\ncat\nvehicle\n";
	
	while (  (num_written = fwrite(animal_list, sizeof(char), strlen(animal_list), ppp) ) > 0) {

		fprintf(stdout, "Wrote %d bytes\n", num_written);
		if (num_written >= strlen(animal_list)) {
			break;
		}
	}

	printf("The exit status is %d\n", mypclose(ppp) );

	exit(EXIT_SUCCESS);
}
