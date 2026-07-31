/* 
 * This program is used to test the currmsgs program, which reports on the
 * current number of messages in a POSIX queue.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MSG_SIZE 32

int main ( int argc, char * argv[] ) {

	if ( argc != 3 ) {
		fprintf(stderr, "Usage: %s <message_queue_name> <message>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ( strlen(argv[2]) > MSG_SIZE ) {
		fprintf(stderr, "message must be smaller that %d chars\n", MSG_SIZE);
		exit(EXIT_FAILURE);
	}

	mqd_t mqdes;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

	struct mq_attr attrib;
	attrib.mq_maxmsg = 25;
	attrib.mq_msgsize = MSG_SIZE;

	if ( (mqd_t)-1 == (mqdes = mq_open(argv[1], O_WRONLY | O_CREAT, mode, attrib))) {
		fprintf(stderr, "Error in mq_open(): %s\n", strerror(errno));
		exit(EXIT_SUCCESS);
	}

	/* Initialize the message buffer */
	char buf[MSG_SIZE];	
	memset(buf, '\0', MSG_SIZE);

	snprintf(buf, MSG_SIZE, argv[2]);
	buf[MSG_SIZE] = '\0';

	if (  mq_send(mqdes, buf, MSG_SIZE, 0) == -1 ) {
		fprintf(stderr, "Error in mq_send(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		fprintf(stdout, "Message successfully sent!\n");
	}
	
	exit(EXIT_SUCCESS);
}
