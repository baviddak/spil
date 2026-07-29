/*
 * Write a program that determines the maximum value that a POSIX semaphore
 * can attain on your computer.
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>

int main () {

	sem_t sem;
	int current_sem_val;
	
	if ( sem_init(&sem, 1, 0) == -1) {
		fprintf(stderr, "Failed to init a semaphore: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		fprintf(stdout, "Semaphore successfully initialized\n");
	}
	
	/* Loop until sem_post gets an overflow error - then we have reached the limit */
	while ( 1 ) {
		if ( sem_post(&sem) == -1 && errno == EOVERFLOW ) {
			fprintf(stderr, "Error in sem_post(): %s\n", strerror(errno));
			break;
		} else {
			fprintf(stdout, "\rCurrent sem value: %d", current_sem_val);
			fflush(stdout);
		}
		if ( sem_getvalue(&sem, &current_sem_val) == -1 ) {
			fprintf(stderr, "Error in sem_getvalue(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}	
	
	fprintf(stdout, "\nThe maximum value that a semaphore can have on this system is %d\n", current_sem_val);

	exit(EXIT_SUCCESS);
}
