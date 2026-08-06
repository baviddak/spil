#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "mypopenclose.h"

static struct child_pipe *cpipes[CHILD_PIPES_MAX];

static void add_cpipe(int fd, pid_t pd) {

	for ( int i = 0; i < CHILD_PIPES_MAX; i++ ) {
		if ( cpipes[i] == NULL ) {
			/* Debug */
			printf("Adding fd %d and pid %d to the list\n", fd, pd);
			cpipes[i] = (struct child_pipe *)malloc(sizeof(struct child_pipe));
			cpipes[i]->fd = fd;
			cpipes[i]->pd = pd;
			break;
		}
	}
	
}

static pid_t findpd(int fd) {
	
	for ( int i = 0; i < CHILD_PIPES_MAX; i++ ) {
		if ( cpipes[i] != NULL ) {
			if ( cpipes[i]->fd == fd ) {
				return cpipes[i]->pd;
			}	
		}
	}
	return (pid_t)-1;
}

static void remove_cpipe(int fd) {
	
	for ( int i = 0; i < CHILD_PIPES_MAX; i++ ) {
		if ( cpipes[i] != NULL ) {
			if ( cpipes[i]->fd == fd ) {
				free(cpipes[i]);
			}	
		}
	}
}

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
			
				/* Add the file descriptor and pid association to our tracker */
				add_cpipe(pfd[1], pd);

				nfp = fdopen(pfd[1], "w");
				return nfp;

			} else if (strcmp(type, "r") == 0 ) {

				/* Close the write end of the parent */
				close(pfd[1]);
	
				/* Add the file descriptor and pid association to our tracker */
				add_cpipe(pfd[0], pd);

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

	int child_fd;
	
	/* find the fd of pipe */
	if ( -1 == (child_fd = fileno(stream) ) ) {
		fprintf(stderr, "Error in fileno(): %s\n", strerror(errno));
	}

	/* find the associated pid */

	int exit_status;
	pid_t child_pid;

	child_pid = findpd(child_fd);

	if ( kill(child_pid, SIGKILL) == -1 ) {
		fprintf(stderr, "Error in kill(): %s\n", strerror(errno));
		return -1;
	}

	if ( waitpid(child_pid, &exit_status, 0) == -1 ) {
		fprintf(stderr, "Error in wait(): %s\n", strerror(errno));
		return -1;
	}

	remove_cpipe(child_fd);
	
	return exit_status;
}
