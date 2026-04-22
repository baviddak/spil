/* 
 * Write a program named yearday2date that, when given an integer argument, 
 * returns the date in the current year that it represents in the format
 * <Monthname><dayofmonth>, <current year>. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define DECIMALBASE 10
#define BUFMAX 64

int main ( int argc, char *argv[] ) {

	/* Check input arguments */
	if ( argc != 2 || strcmp(argv[1], "--help") == 0 ) { 
		fprintf(stderr, "Usage: ./yearday2date <int>\n");
		exit(EXIT_FAILURE);
	}

	/* Use strtol to convert the input arg to an int */
	char *eptr;
	long daynum = strtol(argv[1], &eptr, DECIMALBASE);

	if ( errno == EINVAL || errno == ERANGE ) {
		fprintf(stderr, "Error in strtol(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ( *eptr != '\0' || eptr == argv[1] ) {
		fprintf(stderr, "%s is not a valid number.\n", argv[1]);
		exit(EXIT_SUCCESS);
	}

	/* Generate the date stamp */
	char outstr[BUFMAX];
	struct tm tmp;
	time_t t = time(NULL);

	if ( localtime_r(&t, &tmp) == NULL ) {
		fprintf(stderr, "Error in localetime()\n");
		exit(EXIT_FAILURE);
	}

	tmp.tm_sec = 0;
	tmp.tm_min = 0;
	tmp.tm_hour = 0;
	tmp.tm_mday = daynum;
	tmp.tm_mon = 0;
	/* leave tmp.tm_year as is */
	/* tmp.tm_wday is ignored */
	/* tmp.tm_yday is ignored */
	time_t newtime = mktime(&tmp);

	/* Get the new time */
	if ( localtime_r(&newtime, &tmp) == NULL ) {
		fprintf(stderr, "Error in localtime()\n");
		exit(EXIT_FAILURE);
	}

	/* fprintf(stdout, "Size of outstr: %d\n", sizeof(outstr)); */

	if ( strftime(outstr, sizeof(outstr), "%B %d, %Y", &tmp) < 0 ) {
		fprintf(stderr, "Error in strftime()\n");
		exit(EXIT_FAILURE);
	}

	puts(outstr);

	exit(EXIT_SUCCESS);
}
