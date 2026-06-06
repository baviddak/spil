/*
 * Implement a command named snooze that behaves like sleep...
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[]) {

	double waittime = atof(argv[1]);

	int cycles = waittime * 10;

	struct timespec my_timespec;

	my_timespec.tv_sec = 0; 
	my_timespec.tv_nsec = 100000000;

	printf("Delaying for %f seconds...\n", waittime);
	fflush(stdout);

	for (int i = 0; i < cycles; i++) {

		nanosleep(&my_timespec, NULL);

		if ( i % 2 == 1 ) {
			printf("\\");
		} else {
			printf("/");
		}
		fflush(stdout);

	}

	printf("\r\e[KDone\n");

	exit(EXIT_SUCCESS);
}
