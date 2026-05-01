/* 
 * The find command is a very powerful command. Write a limited version of
 * find named findlinks that searches in the directory tree rooted at dirpath
 * for all filenames that are links to the same file as pathname.
 */

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdio.h>
#include <ftw.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

static ino_t target_inode;
static int dirpathsz;

static int compare_and_print(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {

	if ( typeflag != FTW_SL ) {
		return 0;
	}

	/* Run stat() on the link filepath to get information on the target */
	struct stat sb_sym;
	if ( stat(fpath, &sb_sym) == -1 ) {
		fprintf(stderr, "fpath: %s Error in stat(): %s\n", fpath, strerror(errno));
		return -1;
	}

	if ( sb_sym.st_ino == target_inode ) {
		fprintf(stdout, "%s\n", fpath + dirpathsz);
	}

	return 0;
}

int main ( int argc, char * argv[] ) {

	if ( argc != 3 ) {
		fprintf(stderr, "Usage: ./findlinks <dirpath> <filename>\n");
		exit(EXIT_FAILURE);

	}

	struct stat sb;

	if ( stat(argv[1], &sb) == -1 ) {
		fprintf(stderr, "Error in stat(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ( !S_ISDIR(sb.st_mode) /* sb.st_mode & S_IFMT != S_IFDIR */ ) {
		fprintf(stderr, "%s is not a directory!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	if ( stat(argv[2], &sb) == -1 ) {
		fprintf(stderr, "Error in stat(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* set the target i-node number */
	target_inode = sb.st_ino;
	dirpathsz = strlen(argv[1]);

	int maxfd = 20;

	/* Call nftw with PHYS flag - */
	nftw(argv[1], compare_and_print, maxfd, FTW_PHYS);

	exit(EXIT_SUCCESS);
}
