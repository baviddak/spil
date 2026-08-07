/* The logger command lets a user write a message to the system logfile from 
 * the command line. Read its man page and write an implementation that 
 * accepts the -i option.
 */

/* 
 * On systems with systemd, you can test this with the a similar command:
 * 
 * sudo journalctl --facility=user --since "2026-08-06 21:15:18"
 */

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <getopt.h>

int main( int argc, char * argv[] ) {

	int opt;
	int option = 0;
	char *message;

	while ( ( opt = getopt(argc, argv, ":i") ) != -1 ) {
		switch(opt) {
			case 'i':
				/* set the log pid option */
				option |= LOG_PID;
				break;
			default:
				fprintf(stderr, "Usage: %s [-i] <message>\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	
	/* Save the message */	
	if ( optind < argc ) {
		message = argv[optind];
	} else {
		message = argv[1];
	}

	openlog(argv[0], option, LOG_USER);

	syslog(LOG_USER | LOG_INFO, message);

	exit(EXIT_SUCCESS);
}
