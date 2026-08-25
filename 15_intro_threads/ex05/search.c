/*
 * Write a multithreaded program named search.c ... 
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/sysinfo.h>
#include <pthread.h>

#define MAX_FILE_LENGTH 8192
#define MAX_NUMBERS 4096
#define MAX_THREADS 128

/* From the book */
typedef struct _task_data {
	pthread_t tid;
	int id;
	int first;
	int last;
	int *array;
	int target;
	int result;
} task_data;

void *search_array(void *arg) {
	/* Write the result to the result value in the struct */

	task_data *td = (task_data *)arg;	
	td->result = -1;

	for (int i = td->first; i < td->last; i++) {
		if ( td->array[i] == td->target ) {
			
			td->result = i;
			/* Set the global var */
			
		}
		
	}
	pthread_exit((void *)td);
}



int main(int argc, char *argv[] ) {

	if ( argc != 3 ) { fprintf(stderr, "Usage: %s <number filename> <number>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	ssize_t num_read;
	int fd;

	if ( (fd = open(argv[1], O_RDONLY)) == -1 ) {
		fprintf(stderr, "Error in open(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	int target = strtol(argv[2], NULL, 0);
	/* Error handling for strtol() */

	char buffer[MAX_FILE_LENGTH];
	memset(buffer, '\0', MAX_FILE_LENGTH);

	while ( 1 ) {
		num_read = read(fd, buffer, MAX_FILE_LENGTH);
		if ( num_read <= 0 ) {
			break;
		}
	}

	buffer[MAX_FILE_LENGTH] = '\0';
	int numbers[MAX_NUMBERS];

	if ( num_read == -1 ) {
		fprintf(stderr, "Error in read(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	char *current = strtok(buffer, " ");
	int i = 0;

	while ( current != NULL ) {

		if ( i >= MAX_NUMBERS ) {
			fprintf(stderr, "Too many numbers in the file!\n");
			exit(EXIT_FAILURE);
		}

		numbers[i] = strtol(current, NULL, 0);
		if ( ( numbers[i] == LONG_MIN || numbers[i] == LONG_MAX ) && errno == ERANGE) {
			fprintf(stderr, "Error int strtol(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		i++;
		current = strtok(NULL, " ");
	}


	int nthreads = get_nprocs() - 2; /* Don't actually use all threads haha */
	
	task_data thread_data[MAX_THREADS];	

	/* Strategy from the book */	
	for ( int t = 0; t < nthreads; t++ ) {
		thread_data[t].first = (t * i) / nthreads;
		thread_data[t].last = (((t + 1) * i ) / nthreads) - 1;
		thread_data[t].id = t;
		thread_data[t].target = target;
		thread_data[t].array = numbers;
		
		if ( 0 != pthread_create(&(thread_data[t].tid), NULL, search_array, (void *) &(thread_data[t]))) {
			fprintf(stderr, "Error in creating thread\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	/* Incomplete! Unsure about this one */
	
	
	exit(EXIT_SUCCESS);
}
