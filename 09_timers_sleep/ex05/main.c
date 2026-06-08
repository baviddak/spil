/* 
 * Write a program named wallclock that clears the screen and displays the 
 * current wall clock time, using the user's LC_TIME locale setting.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main() {

	if ( setlocale(LC_TIME, "") == NULL ) {
		fprintf(stderr, "Error in setlocale()\n");
		exit(EXIT_FAILURE);
	}

	time_t curr_time;
	struct tm *ltime;

	char datebuf[32];
	memset(datebuf, '\0', sizeof(datebuf));

	printf("\33[2J");

	while ( 1 ) {

		// Use %c
		curr_time = time(NULL);
		ltime = localtime(&curr_time);
		if ( strftime(datebuf, sizeof(datebuf), "%c", ltime) == 0 ) {
			fprintf(stderr, "Error in strftime()\n");
			exit(EXIT_FAILURE);
		}

		printf("\r%s", datebuf);
		fflush(stdout);

		memset(datebuf, '\0', sizeof(datebuf));

		sleep(1);
	}

}
