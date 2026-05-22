/* 
 * One function that we didn't explore is sigpending(). Read its man page and
 * then write a function that prints on a single line of standard output a
 * list of the numbers of all pending signals or prints no pending signals
 * if there are none.
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

int printpendingsignals() {

	sigset_t blocked_sigs;

	if ( sigpending(&blocked_sigs)  == -1 ) { 
		fprintf(stderr, "Error in sigpending(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	bool is_empty = true;

	/* Standard signals are from 1 - 31 */

	for ( int i = 1; i <= 31; i++ ) {

		switch ( sigismember(&blocked_sigs, i) ) {
			case 1:
				is_empty = false;
				printf("%d ", i);
				break;
			case 0:
				break;
			case -1:
				fprintf(stderr, "Error in sigismember()\n");
				return -1;
		}
	}


	if (!is_empty) {
		printf("\n");
	} else {
		printf("no pending signals\n");
	}

	return 0;
}

int main () {

	/* Use sigprocmask to test */
	sigset_t myblockedsigset;

	if ( sigfillset(&myblockedsigset) == -1 ) {
		fprintf(stderr, "Error in sigemptyset(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ( sigprocmask(SIG_BLOCK, &myblockedsigset, NULL) == -1 ) {
		fprintf(stderr, "Error in sigprocmask(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* raise(10);
	raise(15);
	raise(20); */

	printpendingsignals();

	exit(EXIT_SUCCESS);

}
