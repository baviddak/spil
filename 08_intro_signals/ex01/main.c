/* 
 * Write a function with the prototype int printsigset(sigset_t set); that
 * prints, on a single line of standard output, a list of the numbers of all
 * standard signals in the set set or prints empty set.
 */


#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

int printsigset(sigset_t set) {

	bool is_empty = true;

	/* Standard signals are from 1 - 31 */

	for ( int i = 1; i <= 31; i++ ) {

		switch ( sigismember(&set, i) ) {
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
		printf("empty set\n");
	}

	return 0;
}


int main () {

	/* Use sigemptyset(), sigfillset(), sigaddset(), and sigdelset() to test */


	/* Test with an empty set */
	sigset_t mysigset;
	sigemptyset(&mysigset);

	printsigset(mysigset);

	/* Test with a full set */
	sigfillset(&mysigset);

	printsigset(mysigset);

	/* Remove some signals and retest */
	sigdelset(&mysigset, 5);
	sigdelset(&mysigset, 10);
	sigdelset(&mysigset, 15); 
	sigdelset(&mysigset, 20);

	printsigset(mysigset);

	exit(EXIT_SUCCESS);

}
