#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#include "mypopenclose.h"

FILE *mypopen(const char *command, const char *type) {
	
	FILE *nfp;

	int pfd[2];
	if ( pipe(pfd) == -1 ) {
		fprintf(stderr, "Error in pipe(): %s\n", strerror(errno));
		return NULL;
	}
	
	pid_t pd = fork();

	switch ( pd ) {
		case -1: 
			fprintf(stderr, "Error in fork(): %s\n", strerror(errno));
			return NULL;
		case 0:
			/* Child process */
			if ( strcmp(type, "w") == 0 ) {

				/* Close the write end of the pipe in the child */
				close(pfd[1]);

				/* Adjust STDIN_FILENO so that it refers to the same open file description as pfd[0] */
				if ( dup2(pfd[0], STDIN_FILENO) == -1 ) {
					fprintf(stderr, "Error in dup2(): %s\n", strerror(errno));
					return NULL;
				}

				/* Execve the supplied command */
				if ( -1 == execl(SHELL_PATH, "sh", "-c", command, (char *)NULL) ) {
					fprintf(stderr, "Error in execl(): \n");
				}
				
			} else if ( strcmp(type, "r") == 0 ) {

				/* Close the read end of the pipe in the child */
				close(pfd[0]);
			
				if ( dup2(pfd[1], STDOUT_FILENO) == -1 ) {
					fprintf(stderr, "Error in dup2(): %s\n", strerror(errno));
					return NULL;
				}

				/* Execve the supplied command */
				if ( -1 == execl(SHELL_PATH, "sh", "-c", command, (char *)NULL) ) {
					fprintf(stderr, "Error in exec(): %s\n", strerror(errno));
				}
				
				
			} else {
				fprintf(stderr, "Error in determining mode\n");
				return NULL;
			}

			break;
		default: 
			/* Parent process */
			if ( strcmp(type, "w") == 0 ) {

				/* Close the read end in the parent */
				close(pfd[0]);

				nfp = fdopen(pfd[1], "w");
				return nfp;

			} else if (strcmp(type, "r") == 0 ) {

				/* Close the write end of the parent */
				close(pfd[1]);

				nfp = fdopen(pfd[0], "r");
				return nfp;
			} else {
				fprintf(stderr, "Error in determining read or write\n");
				return NULL;
			}
			break;
	}

	return NULL;
}

int mypclose(FILE *stream) {

	int exit_status;
	pid_t child_id;

	if ( -1 == ( child_id = wait(&exit_status) ) ) {
		fprintf(stderr, "Error in wait(): %s\n", strerror(errno));
		return -1;
	}
	return exit_status;
}
