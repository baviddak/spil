#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

/* This is a comment */

#define MAX_CHILDREN 128

struct child_list {
	pid_t children[MAX_CHILDREN];
	int size;
};

void add_list_child(pid_t child_pid, struct child_list *ch_list) {

	if ( ch_list->size == MAX_CHILDREN - 1 ) {
		fprintf(stderr, "Too many children created!\n");
		exit(EXIT_FAILURE);
	}

	ch_list->children[ch_list->size] = child_pid;
	ch_list->size++;
	return;
}


/* Exit function to print good-bye message */
void goodbye(int signo, siginfo_t *info, void *context) {
	fprintf(stdout, "Process %d terminated\n", getpid());

	_exit(EXIT_SUCCESS);
}


int main (int argc, char *argv[]) {

	long val;
	pid_t current_pid;

	if ( argc != 2 || strcmp(argv[1], "--help") == 0 ) {
		fprintf(stderr, "Usage: ./cascade N\n\nWhere N = number of processes. N must be less than or equal to 128.\n");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	val = strtol(argv[1], NULL, 10);

	if ( errno == ERANGE ) {
		fprintf(stderr, "%s is not a valid number: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ( val > 128 || val < 0 ) {
		fprintf(stderr, "%ld is not a valid number\n", val);
		exit(EXIT_FAILURE);
	}


	struct child_list new_cl;
	new_cl.size = 0;

	for (int i = 0; i < val; i++ ) {
		switch ( (current_pid = fork() )) {
			case -1:
				fprintf(stderr, "Error in fork(): %s\n", strerror(errno));
				exit(EXIT_FAILURE);
				break;
			case 0:
				/* Child process */
				fprintf(stdout, "PID child %d: %d\n", i, getpid());

				struct sigaction sa;
				sa.sa_flags = SA_SIGINFO;
				sa.sa_sigaction = &goodbye;

				if ( -1 == sigaction(SIGTERM, &sa, NULL) ) {
					fprintf(stderr, "Error in sigaction(): %s\n", strerror(errno));
				}

				pause();
				break;
			default:
				/* Parent process */
				add_list_child(current_pid, &new_cl);
				break;
		}

	}

	sleep(10);

	/* Send SIGTERM to all children */
	for (int i = 0; i < new_cl.size; i++ ) {
		kill(new_cl.children[i], SIGTERM);
	}

	exit(EXIT_SUCCESS);
}
