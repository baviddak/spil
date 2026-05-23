/* Use SA_RESETHAND */

/* The abort() library function terminates the calling process by sending it 
 * a SIGABRT signal. However, because the caller might have a signal handler
 * for SIGABRT, it has to do more than simply raise this signal... write an
 * implementation of it.
 */

/* The abort function first unblocks the SIGABRT signal, and then raises that 
 * signal for the calling process. This results in the abnormal termination of
 * the process unless the SIGABRT signal is caught and the signal handler does
 * not return
 *
 * If the SIGABRT signal is ignored or caught by a handler that returns, 
 * the abort() function will still terminal the process. It does this by 
 * restoring the default disposition for SIGABRT and then raising the signal
 * for a second time.
 */


#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

static volatile int my_counter = 0;

void abrt_handler() {
	my_counter++;
}

void my_abort() {

	/* Unblock the SIGABRT signal and raise it */
	sigset_t abortsig;

	if ( sigemptyset(&abortsig) == -1 ) {
		fprintf(stderr, "Error in sigemptyset(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ( sigaddset(&abortsig, SIGABRT) == -1 ) {
		fprintf(stderr, "Error in sigaddset(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ( sigprocmask(SIG_UNBLOCK, &abortsig, NULL) == -1 ) {
		fprintf(stderr, "Error in sigprocmask(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	raise(SIGABRT);

	/* Reset the handler and call again */

	struct sigaction dflact;
	dflact.sa_handler = SIG_DFL;

	if ( sigaction(SIGABRT, &dflact, NULL) == -1 ) {
		fprintf(stderr, "Error in sigaction(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	raise(SIGABRT);

}

int main() {

	/* Set a signal handler for SIGABRT to test */

	struct sigaction handleract;
	handleract.sa_handler = abrt_handler;

	if ( sigaction(SIGABRT, &handleract, NULL) == -1 ) {
		fprintf(stderr, "Error in sigaction(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Raise SIGABRT to test the default action */
	// raise(SIGABRT);

	/* Call the my_abort() to test */
	my_abort();

	printf("Reached end of program\n");
	exit(EXIT_SUCCESS);
}
