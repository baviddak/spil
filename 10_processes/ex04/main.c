#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "getparentid.h"

int main(int argc, char *argv[]) {

	/* Validate command line args */
	if ( argc != 2 || strcmp(argv[1], "--help") == 0 ) {
		fprintf(stderr, "Usage: ./psiblings pid\n");
		exit(EXIT_FAILURE);
	}

	long input_proc_id = strtol(argv[1], NULL, 10);
	if ( (input_proc_id == LONG_MIN || input_proc_id == LONG_MAX) && errno == ERANGE ) {
		fprintf(stderr, "%s is not a valid proc id\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	pid_t target_parent = getparentid(input_proc_id);
	pid_t current_parent_id;

	DIR *dp = opendir("/proc");
	struct dirent *dnt;
	long current_proc_id;

	while ( NULL != ( dnt = readdir(dp) ) ) {

		/* Only proceed if it is a directory */
		if ( dnt->d_type != DT_DIR ) {
			continue;
		}

		/* Validate the process id */
		current_proc_id = strtol(dnt->d_name, NULL, 10);

		if ( (current_proc_id == LONG_MIN || current_proc_id == LONG_MAX) && errno == ERANGE) {
			continue;
		}

		if ( current_proc_id == 0 ) {
			continue;
		}

		/* Utilize the getparentid() function */

		current_parent_id = getparentid(current_proc_id);

		if ( current_parent_id == target_parent ) {
			fprintf(stdout, "%d\n", current_proc_id);
		}

	}

	/* fprintf(stderr, "readdir() returned NULL: %s\n", strerror(errno)); */
	exit(EXIT_SUCCESS);
}

