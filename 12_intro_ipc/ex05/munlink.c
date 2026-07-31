/*
 * This program is used to test the currmsgs program by unlinking the message
 * queue specified in the command line arg.
 */

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>

int main ( int argc, char * argv[] ) {

	if ( argc != 2 ) {
		fprintf(stderr, "Usage: %s <message_queue_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ( mq_unlink(argv[1]) == -1 ) {
		fprintf(stderr, "Error in mq_unlink(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		fprintf(stdout, "Message queue successfully unlinked.\n");
	}
	
	exit(EXIT_SUCCESS);
}
