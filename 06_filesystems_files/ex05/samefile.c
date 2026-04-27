/* 
 * Write a function named samefile() that returns 1 if pathname1 and pathname2
 * are links to the same file, and 0 if they are not.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int samefile(const char *pathname1, const char *pathname2) {

	struct stat sb;

	if ( lstat(pathname1, &sb) == -1 ) {
		fprintf(stderr, "Error in lstat(): %s\n", strerror(errno));
		return -1;
	}

	if (!S_ISLNK(sb.st_mode) ) {
		fprintf(stderr, "Not a link\n");
		return -1;
	}

	if ( stat(pathname1, &sb) == -1 ) {
		fprintf(stderr, "Error in stat(): %s\n", strerror(errno));
		return -1;
	}

	ino_t path1_ino = sb.st_ino;

	if ( lstat(pathname2, &sb) == -1 ) {
		fprintf(stderr, "Error in lstat(): %s\n", strerror(errno));
		return -1;
	}

	if (!S_ISLNK(sb.st_mode) ) {
		fprintf(stderr, "Not a link\n");
		return -1;
	}

	if ( stat(pathname2, &sb) == -1 ) {
		fprintf(stderr, "Error in stat(): %s\n", strerror(errno));
		return -1;
	}
	
	ino_t path2_ino = sb.st_ino;

	if ( path2_ino == path1_ino ) {
		return 1;
	} else {
		return 0;
	}
}

int main( int argc, char *argv[] ) {

	if ( argc != 3 ) {
		fprintf(stderr, "Usage: ./samefile <file1> <file2>\n");
		exit(EXIT_FAILURE);
	}

	printf("Answer: %d\n", samefile(argv[1], argv[2]));

	exit(EXIT_SUCCESS);
}
