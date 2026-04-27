/* 
 * Write a function named newer() that returns 1 if the file pathname1 was
 * last modified no earlier than the pathname2 and otherwise returns 0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int newer(const char *pathname1, const char *pathname2) {

	struct stat sb;
	long modtime1_ns, modtime2_ns;
	time_t modtime1_s, modtime2_s;

	if ( lstat(pathname1, &sb) == -1 ) {
		fprintf(stderr, "Error in lstat(): %s\n", strerror(errno));
		return -1;
	}

	modtime1_s = sb.st_mtim.tv_sec;
	modtime1_ns = sb.st_mtim.tv_nsec;

	if ( lstat(pathname2, &sb) == -1 ) {
		fprintf(stderr, "Error in lstat(): %s\n", strerror(errno));
		return -1;
	}

	modtime2_s = sb.st_mtim.tv_sec;
	modtime2_ns = sb.st_mtim.tv_nsec;

	/* printf("Time for pathname 1: %d, %lld\nTime for pathname 2: %d, %lld\n", modtime1_s, modtime1_ns, modtime2_s, modtime2_ns); */

	if ( modtime1_s == modtime2_s ) {

		if ( modtime1_ns >= modtime2_ns ) {
			return 1;
		} else {
			return 0;
		}

	} else if (modtime1_ns > modtime2_ns) {
		return 1;
	} else {
		return 0;
	}

}

int main(int argc, char *argv[]) {

	if ( argc != 3 ) {
		fprintf(stdout, "Usage: ./newer <pathname1> <pathname2>\n");
		exit(EXIT_FAILURE);
	}

	switch ( newer(argv[1], argv[2]) ) {
		case 1:
			printf("Newer file: %s\n", argv[2]);
			break;
		case 0:
			printf("Newer file: %s\n", argv[1]);
			break;
		default:
			printf("Error\n");
			break;
	}
	
	exit(EXIT_SUCCESS);
}

