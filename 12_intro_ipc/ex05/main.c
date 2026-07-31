/* 
 * Write a program that, given the name of any POSIX message queue, prints how
 * many unread messages are in the queue at 1-second intervals until the 
 * message queue is removed. The program should terminate automatically when
 * the queue no longer exists.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main( int argc, char * argv[] ) {

	if ( argc != 2 ) {
		fprintf(stderr, "Usage: %s <message_queue_name>\n", argv[0] );
		exit(EXIT_FAILURE);
	}

	mqd_t mqdes;
	if ( (mqd_t)-1 == (mqdes = mq_open(argv[1], O_RDONLY)) ) {
		fprintf(stderr, "Error in mq_open(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);	
	}
	
	struct mq_attr queue_attr;	
	while ( 1 ) {
		
		if ( mq_getattr(mqdes, &queue_attr) == -1 ) {
			fprintf(stderr, "Error in mq_getattr(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		fprintf(stdout, "\rThe current number of in message queue %s is %ld", argv[1], queue_attr.mq_curmsgs);
		fflush(stdout);

		sleep(1);

	}	
	exit(EXIT_SUCCESS);
}

